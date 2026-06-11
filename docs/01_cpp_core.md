# C++ 核心语言特性复习

本篇覆盖仓库中关于 C++ 语言本身的实例（主要源自《More Effective C++》《STL 源码剖析》的实践代码），
按面试/笔试考察频率排序。每节给出：**原理 → 仓库例子 → 面试常问点**。

---

## 1. 智能指针（高频 ⭐⭐⭐）

**仓库例子**：`1smart_pointer/main_acm.cpp`、`6auto_ptr/main.cpp`

### 原理

智能指针的本质是 **RAII**（Resource Acquisition Is Initialization）：用栈上对象的生命周期管理堆上资源。
构造时接管裸指针，析构时自动 `delete`，从而杜绝内存泄漏。

最小实现（`1smart_pointer` 中的写法）：

```cpp
template <class T>
class SmartPointer {
public:
    SmartPointer(T* p = nullptr) : pointer(p) {}
    ~SmartPointer() { if (pointer) delete pointer; }
    T* operator->() const { return pointer; }   // 重载 -> 实现 sp->member
    T& operator*()  const { return *pointer; }  // 重载 * 实现 (*sp).member
private:
    T* pointer;
};
```

关键点：
- 必须重载 `operator->` 和 `operator*`，让它"用起来像指针"。
- **不要**提供 `operator T*()` 隐式转换——裸指针泄露出去后可能被外部 delete，造成双重释放（例子代码里注释掉的那段就是反面教材）。
- `auto_ptr`（`6auto_ptr`）是 C++98 的方案，拷贝时**转移所有权**（拷贝后源指针置空），语义反直觉，C++11 起被废弃。

### 面试常问

| 问题 | 答案要点 |
|------|----------|
| `unique_ptr` vs `shared_ptr` | unique 独占、零开销、只能 move；shared 引用计数、控制块、线程安全的计数 |
| `weak_ptr` 作用 | 打破 shared_ptr 循环引用；观察不拥有，用 `lock()` 提升 |
| 为什么废弃 auto_ptr | 拷贝即转移所有权，放进容器后行为不可预测 |

---

## 2. 引用计数（高频 ⭐⭐⭐）

**仓库例子**：`2reference_counter/reference_conter.cpp`（《More Effective C++》条款 29 的完整实现）

### 原理

多个对象共享同一份数据，数据内部维护 `refCount`：
- 新增引用 `++refCount`；
- 解除引用 `--refCount`，减到 0 时 `delete this` 自毁。

仓库实现分三层，这正是 `shared_ptr` + 写时复制（COW）的手工版：

```
RCObject        // 基类：refCount + shareable 标志，addReference/removeReference
RCPtr<T>        // 智能指针：构造/拷贝时 addReference，析构时 removeReference
String::StringValue : RCObject   // 真正的数据（char*），被多个 String 共享
```

关键点：
- `removeReference()` 中 `if (--refCount == 0) delete this;` —— 这就是 shared_ptr 析构的核心逻辑。
- `shareable` 标志处理"有人拿到了内部数据的非 const 指针"的情况：一旦暴露就标记不可共享，之后的拷贝必须深拷贝（写时复制）。
- 赋值运算符要先对新值 addReference、再对旧值 removeReference（防自赋值）。

### 配套：代理类（proxy class）

**仓库例子**：`3proxy_class/proxy_class.cpp` + 其 `RCLString.hpp`

`String::operator[]` 无法区分读还是写（`cout << s[0]` 和 `s[0] = 'x'` 都调用它），
而写操作必须触发深拷贝。解决方案：`operator[]` 返回一个**代理对象 CharProxy**，
代理对象的 `operator char()`（读）和 `operator=`（写）分别处理两种情况——这就是"区分读写"的代理类技术。

---

## 3. 虚函数与多重分发（高频 ⭐⭐⭐）

**仓库例子**：`4virtual_function/virtual_function.cpp`（《More Effective C++》条款 31）

### 原理

虚函数只能根据 `this` 的动态类型做**单分发**。碰撞问题 `collide(GameObject& other)`
需要根据**两个**对象的动态类型决定行为（双重分发），C++ 没有原生支持，例子中用
**成员函数指针 + map** 模拟：

```cpp
typedef void (SpaceShip::*HitFunctionPtr)(GameObject&);
typedef map<string, HitFunctionPtr> HitMap;   // typeid(other).name() -> 处理函数

virtual void collide(GameObject& other) {
    HitFunctionPtr hfp = lookup(other);       // 用 typeid 查表
    if (hfp) (this->*hfp)(other);             // 成员函数指针调用语法
    else throw "Unknown object collision";
}
```

### 面试常问

- 虚函数机制：每个含虚函数的类有一张 vtable，对象头部存 vptr；调用时 `vptr -> vtable[index]` 间接跳转。
- 构造函数不能是虚函数（vptr 还没建立）；析构函数在作为基类时**必须**是虚函数。
- 纯虚函数 `= 0` 使类成为抽象类；纯虚析构函数也要提供定义（见 `2reference_counter` 里 `RCObject::~RCObject(){}`）。
- `dynamic_cast` 依赖 RTTI，向下转型失败时：指针返回 nullptr，引用抛 `bad_cast`。

---

## 4. extern "C" 与混合编译（⭐⭐）

**仓库例子**：`5externC/`（`externC.cpp` + `math.c` + 编译出的 `mymath.so`）

### 原理

C++ 编译器会对函数名做 **name mangling**（把参数类型编进符号名以支持重载），C 编译器不会。
`extern "C"` 告诉 C++ 编译器：这个符号按 C 规则命名，从而能链接到 C 编译出的目标文件/动态库。

```cpp
extern "C" {
    void print_lxn();   // 该函数实现在 math.c 中，编译进 mymath.so
}
```

常见写法是头文件里用宏包裹，让同一头文件 C/C++ 都能用：

```c
#ifdef __cplusplus
extern "C" {
#endif
/* ... 声明 ... */
#ifdef __cplusplus
}
#endif
```

---

## 5. 可变参数模板（⭐⭐）

**仓库例子**：`20variadic_template/variadic_template.cpp`

### 原理

模板参数包 `typename... Args` 可匹配任意数量、任意类型的参数。经典展开方式是**递归 + 终止函数**：

```cpp
void log() { cout << endl; }                  // 终止：0 个参数

template<typename T, typename... Args>
void log(T first, Args... args) {             // 每次剥掉一个参数
    cout << first << " ";
    log(args...);
}
```

替代方案（同文件方法二）：参数类型相同时用 `initializer_list<T>`；
C++17 起还可用折叠表达式 `((cout << args << " "), ...);` 一行展开。

---

## 6. memcpy 的实现与内存重叠（高频手写题 ⭐⭐⭐）

**仓库例子**：`19memcopy/test.c`（正确版）、`19memcopy/memcopy.cpp`（按机器字拷贝的尝试版）

### 原理

手写 memcpy 是笔试经典题，考点是**内存重叠**：当 `dst` 落在 `[src, src+len)` 内时，
从低地址正向拷贝会先覆盖还没读到的源数据。正确做法（即 `memmove` 的语义）：

```c
void* my_memcpy(void* dst, const void* src, size_t len) {
    if (!dst || !src) return NULL;
    void* ret = dst;
    if (dst <= src || (char*)dst >= (char*)src + len) {
        // 无重叠（或 dst 在 src 前）：从低地址正向拷贝
        while (len--) { *(char*)dst = *(char*)src; dst = (char*)dst+1; src = (char*)src+1; }
    } else {
        // dst 落在 src 区间内：从高地址反向拷贝
        src = (char*)src + len - 1;
        dst = (char*)dst + len - 1;
        while (len--) { *(char*)dst = *(char*)src; dst = (char*)dst-1; src = (char*)src-1; }
    }
    return ret;
}
```

加分项：按 `unsigned long` 整字拷贝提升效率（`memcopy.cpp` 的思路），剩余字节再逐字节补齐；
注意 `sizeof(指针)` 是指针大小而不是数据大小（该文件中 FIXME 的 bug 正是这个）。

---

## 7. 位运算实现加法（笔试题 ⭐⭐）

**仓库例子**：`24getsum/main.cpp`（LeetCode 371 两整数之和）

### 原理

不用 `+` 实现加法：异或 = 无进位和，与后左移 = 进位，循环到进位为 0。

```cpp
int getSum(int a, int b) {
    while (b != 0) {
        int sum = a ^ b;                              // 无进位加
        unsigned carry = (unsigned)(a & b) << 1;      // 进位（转 unsigned 避免负数左移 UB）
        a = sum; b = carry;
    }
    return a;
}
```

---

## 8. 进程与系统调用（⭐⭐）

**仓库例子**：`25fork/fork.cpp`、`32attribute_test/main.cpp`

- **fork**：调用一次返回两次——子进程中返回 0，父进程中返回子进程 pid。`if(!fork())` 进入的是子进程分支。连续两个 `fork()` 会产生 4 个进程（笔试常考"打印多少次"）。`wait(NULL)` 回收子进程，避免僵尸进程。
- **`__attribute__((constructor/destructor))`**：GCC 扩展，标记的函数在 `main` 之前/之后自动执行。`atexit(f)` 注册的函数在 `main` 返回后按**注册的逆序**执行（先 func2 后 func1——栈式）。

---

## 9. 其他散点

- **`#pragma GCC optimize(2)`**（`20variadic_template` 开头）：笔试中给单文件强开 O2 的小技巧。
- **nanobind 扩展**（`35nanobindpy/`）：C++ 类通过 nanobind 暴露为 Python 模块 `tenant_py`，用 scikit-build-core + uv 构建，`uv sync && uv run python main.py`。
- **boost**（`12boost_lib/`）：`boost::accumulators` 统计框架的用法，`accumulator_set<double, stats<tag::mean, tag::max>>` 声明要算什么，喂数据后取结果。
