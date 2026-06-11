# C++ 并发编程复习

本篇覆盖 `book_practice/1concurrency_in_action/`（《C++ Concurrency in Action》实践）、
`33promise/`、`34ninja_build/`（并行快排）。并发是面试加分大项，核心抓四件事：
**线程生命周期（RAII）、共享数据加锁、线程间传值（future/promise）、任务并行（async）**。

---

## 1. 线程基础与 RAII 管理（⭐⭐⭐）

**仓库例子**：`book_practice/1concurrency_in_action/1hello/`、`2jthread/jthread.hpp`

### 原理

`std::thread` 析构时如果还是 joinable 状态（既没 join 也没 detach），程序直接 `std::terminate`。
解决方案是 RAII 封装——析构时自动 join，这就是 `2jthread` 里手写的 `joining_thread`（等价于 C++20 的 `std::jthread`）：

```cpp
class joining_thread {
    std::thread t;
public:
    // 万能引用 + 完美转发，接受任意可调用对象和参数
    template<typename Callable, typename... Args>
    explicit joining_thread(Callable&& func, Args&&... args)
        : t(std::forward<Callable>(func), std::forward<Args>(args)...) {}

    joining_thread& operator=(std::thread t_) noexcept {
        if (t.joinable()) t.join();    // 先收掉旧线程
        t = std::move(t_);
        return *this;
    }
    ~joining_thread() { if (t.joinable()) t.join(); }   // 析构自动 join
};
```

考点：
- `std::thread` 只能 move 不能 copy（线程所有权唯一）。
- `Callable&&` 是**万能引用**，配 `std::forward` 完美转发，保持左值/右值属性。
- join（等待结束）vs detach（放飞为后台线程，再也管不了）。

---

## 2. 用 mutex 保护共享数据（⭐⭐⭐）

**仓库例子**：`3share_data/safe_stack.hpp`、`safe_queue.hpp`

### 原理

线程安全栈的设计要点不只是"加锁"，而是**消除接口固有的竞态**：
普通 stack 的 `empty()` + `top()` + `pop()` 是三个调用，两个线程交错执行就会崩——
所以线程安全版本把它们合并成一个原子操作：

```cpp
template<typename T>
class threadsafe_stack {
    std::stack<T> data;
    mutable std::mutex m;       // mutable：允许 const 成员函数里加锁
public:
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lock(other.m);  // 拷贝也要锁源对象
        data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }
    std::shared_ptr<T> pop() {                      // empty 检查 + 取值 + 弹出，一锁到底
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();
        auto res = std::make_shared<T>(std::move(data.top()));
        data.pop();
        return res;
    }
};
```

考点：
- `lock_guard` 是 mutex 的 RAII 包装；需要中途解锁/转移用 `unique_lock`；C++17 多锁防死锁用 `scoped_lock`。
- `mutable mutex`：锁不属于对象逻辑状态，const 函数里也要能加锁。
- pop 返回 `shared_ptr<T>` 而不是 `T`：如果按值返回时拷贝构造抛异常，元素已弹出就丢了（异常安全）。
- 死锁四条件 & 预防：固定加锁顺序、`std::lock` 同时锁多个、不要在持锁时调用用户代码。

---

## 3. promise / future：线程间传值（⭐⭐⭐）

**仓库例子**：`33promise/main.cpp`

### 原理

`promise` 是值的"写端"，`future` 是"读端"，二者由一个共享状态连接。
工作线程算完 `set_value`，主线程 `get()` 阻塞等待：

```cpp
void worker(std::promise<int> p) {
    // ...干活...
    p.set_value(42);                       // 写入结果，唤醒等待方
}

std::promise<int> p;
std::future<int> f = p.get_future();       // 先取 future
std::thread t(worker, std::move(p));        // promise 只能 move 进线程
int result = f.get();                       // 阻塞直到 set_value；get 只能调一次
t.join();
```

考点：
- `future::get()` 只能调用一次（取走共享状态）；多个读者用 `shared_future`。
- promise 析构时还没 set 值，future 端会收到 `broken_promise` 异常。
- 三种拿到 future 的途径：`std::async`、`packaged_task`、`promise`（灵活度依次升高）。

---

## 4. async：基于任务的并行（⭐⭐⭐）

**仓库例子**：`4future/main.cpp`、`34ninja_build/test.cpp`（并行快排）

### 基本用法

```cpp
std::future<int> the_answer = std::async(std::launch::async, find_the_answer);
do_something();              // 主线程同时干别的
the_answer.get();            // 需要结果时再取
```

启动策略：`std::launch::async` 强制新线程；`std::launch::deferred` 延迟到 get 时在调用线程同步执行；默认二者皆可（由库决定）。

### 实战：并行快速排序（`34ninja_build/test.cpp`）

函数式快排 + async 把左半部分丢给别的线程：

```cpp
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
    if (input.empty()) return input;
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());   // 取首元素为 pivot（splice 零拷贝）
    T const& pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(),
                                       [&](T const& t){ return t < pivot; });
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    // 左半部分异步排（可能新线程），右半部分当前线程递归
    std::future<std::list<T>> new_lower(
        std::async(&parallel_quick_sort<T>, std::move(lower_part)));
    auto new_higher = parallel_quick_sort(std::move(input));

    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());        // get() 处汇合
    return result;
}
```

值得记住的三个工具：
- `list::splice`：链表节点搬移，O(1) 零拷贝。
- `std::partition`：按谓词把区间分成两段，返回分界迭代器——这就是快排 partition 的库实现。
- 递归 + async 会指数级开线程（递归 10 层 ≈ 1024 个任务）；库在超额时会自动转为同步执行，但生产代码应该用线程池/限制深度。

---

## 5. 复习清单（并发八股自查）

1. `std::thread` 没 join 就析构会怎样？→ terminate。
2. `lock_guard` / `unique_lock` / `scoped_lock` 区别？
3. 为什么线程安全栈要把 empty+top+pop 合成一个 pop？→ 接口竞态。
4. promise / packaged_task / async 三者关系？
5. `future::get` 调两次会怎样？→ 抛异常（状态已被取走），需要 `shared_future`。
6. 条件变量为什么要配 while（虚假唤醒）？（仓库暂无例子，自行补一个 `condition_variable` 的生产者消费者）
