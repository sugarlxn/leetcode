# STL 容器与组件复习

本篇覆盖仓库中《STL 源码剖析》（侯捷）的实践代码。STL 六大组件：**容器、算法、迭代器、仿函数、适配器、分配器**，
仓库的例子正好打中前五个。每节：**原理 → 仓库例子 → 关键结论**。

---

## 1. set / map：底层红黑树（高频 ⭐⭐⭐)

**仓库例子**：`16test_set/test_set.cpp`、`17test_map/testmap.cpp`

### 原理

`set`/`map`/`multiset`/`multimap` 底层都是**红黑树**（一种自平衡二叉搜索树），
中序遍历有序，增删查都是 O(log n)。

从例子代码里能得出的关键结论（都是面试考点）：

```cpp
set<int> iset(ia, ia+5);
iset.insert(3);              // 已存在则插入失败，size 不变（set 元素唯一）
iset.count(3);               // 只能是 0 或 1

// 查找：用成员函数 find，不要用 std::find
iset.find(3);                // O(log n)，走树
std::find(iset.begin(), iset.end(), 3);  // O(n)，循序搜索，蠢

*ite1 = 9;                   // ❌ 编译错误：set 迭代器是 const 的
                             // 改值会破坏树的有序性，所以禁止
```

map 的差异：

```cpp
map<string,int> simap;
simap["lxn"] = 1;            // operator[]：不存在则插入默认值再返回引用
                             // （所以 const map 不能用 []）
simap.insert(pair<string,int>("Rudy", 5));   // 另一种插入

ite1->second = 9;            // ✅ 允许：map 只有 key 是 const，value 可改
```

| 对比 | set/map | unordered_set/map |
|------|---------|-------------------|
| 底层 | 红黑树 | 哈希表（开链法） |
| 有序 | 是（中序） | 否 |
| 复杂度 | O(log n) | 平均 O(1)，最坏 O(n) |
| 迭代器失效 | 删除仅失效被删元素 | rehash 时全部失效 |

**仓库例子** `18test_hash/test_hash.cpp` 记录了一个事实：SGI 的 `hash_set/hash_map` 是非标准的旧扩展（`<hash_set>` 已弃用），现代代码用 `unordered_set/unordered_map`。

---

## 2. heap：建立在 vector 上的算法（⭐⭐⭐）

**仓库例子**：`14heap_test/heap_test.cpp`（侯捷 4.7.4）

### 原理

STL 的 heap 不是容器，而是**作用在随机访问区间上的一组算法**，默认大顶堆（完全二叉树，数组下标 `i` 的孩子是 `2i+1`/`2i+2`）：

```cpp
vector<int> iv = {0,1,2,3,4,8,9,3,5};
make_heap(iv.begin(), iv.end());   // O(n) 建堆
iv.push_back(7);
push_heap(iv.begin(), iv.end());   // 新元素上浮 O(log n)，前提：前 n-1 个已是堆
pop_heap(iv.begin(), iv.end());    // 堆顶换到末尾并下沉，⚠️ 不删除
iv.pop_back();                     // 真正删除要自己 pop_back
sort_heap(iv.begin(), iv.end());   // 反复 pop_heap → 升序，即堆排序 O(n log n)
```

`priority_queue` 就是用这组算法包装 vector 的适配器（见 `31dijkstra` 的实战用法，配自定义比较器实现小顶堆）。

---

## 3. queue / stack：容器适配器（⭐⭐⭐）

**仓库例子**：`13queue/queue.cpp`（手抄侯捷 4.6.2 的 mini 实现）

### 原理

queue 和 stack 都**没有自己的数据结构**，它们把底层容器（默认 `deque`）的接口剪裁一下：

```cpp
template<class T, class Sequence = deque<T>>
class queue {
protected:
    Sequence c;                                  // 底层容器
public:
    void push(const value_type& x) { c.push_back(x); }   // 只允许队尾进
    void pop()                     { c.pop_front(); }    // 队首出
    reference front()              { return c.front(); }
    // 没有迭代器！不允许遍历
};
```

关键结论：
- queue/stack 被归类为 **adapter（配接器）** 而非容器。
- 它们不提供迭代器（遍历会破坏先进先出/后进先出语义）。
- 底层容器可换：`stack<int, vector<int>>` 也合法；queue 不能用 vector（没有 `pop_front`）。
- `deque` 本身是"分段连续"结构：一个中控 map 指向多段缓冲区，因此头尾插入都是 O(1)，但迭代器比 vector 重。

---

## 4. 仿函数 functor（⭐⭐）

**仓库例子**：`22functor/functor.cpp`

### 原理

仿函数 = 重载了 `operator()` 的类对象，行为像函数但**可携带状态、可作为模板参数内联**（这是它比函数指针快的原因）：

```cpp
template <typename T>
struct negate : public unary_function<T, T> {     // 一元仿函数
    T operator()(const T& x) const { return -x; }
};

template <typename T>
struct plus : public binary_function<T, T, T> {   // 二元仿函数
    T operator()(const T& x, const T& y) const { return x + y; }
};
```

- `unary_function`/`binary_function` 是 C++98 用来声明参数/返回类型 typedef 的基类，让仿函数能被绑定器（bind1st 等）使用；**C++17 已移除**，现代等价物是 lambda + `std::function`。
- STL 里大量使用：`sort(v.begin(), v.end(), greater<int>())`、`priority_queue` 的比较器（`31dijkstra` 中的 `edge_greater` 就是手写仿函数实战）。

---

## 5. 迭代器适配器（⭐⭐）

**仓库例子**：`23adapter/adapter.cpp`

### 原理

插入迭代器把"赋值"动作改写成"插入"，配合 `copy` 等算法把输出导到容器/流：

```cpp
ostream_iterator<int> outite(cout, ",");       // 绑定到 cout，每写一个元素跟一个 ','
copy(id.begin(), id.end(), outite);            // 容器 → 屏幕

copy(ia+3, ia+4, back_inserter(id));           // 改写为 push_back
copy(ia+3, ia+4, front_inserter(id));          // 改写为 push_front（容器需支持）
copy(ia+0, ia+3, inserter(id, ite));           // 改写为 insert(ite, x)，在指定位置前插入
```

如果直接 `copy` 到一个空间不够的位置会写越界——插入迭代器正是为了解决这个问题。

---

## 6. slist 单向链表（⭐）

**仓库例子**：`15slist_test/slist_test.cpp`（侯捷 4.9）

SGI 的 `slist` 是非标准容器；C++11 标准化为 **`forward_list`**：单向、只支持 `push_front`、
没有 `size()`（为了 O(1) splice），插入删除要用 `insert_after`/`erase_after`。

---

## 7. boost 库初步（⭐）

**仓库例子**：`12boost_lib/`

- `test_boost.cpp`：用 `BOOST_VERSION` 宏验证安装（major = /100000，minor = /100%1000）。
- `accumulator1.cpp`：`boost::accumulators` 统计框架——声明式地组合统计量：

```cpp
accumulator_set<double, stats<tag::mean, tag::moment<2>>> acc;
acc(1.2); acc(2.3);                  // 像函数一样喂数据
mean(acc); moment<2>(acc);           // 取结果
acc = std::for_each(v.begin(), v.end(), acc);   // 配合 STL 算法批量喂
```

注意 `max`/`min` 与 `std::max` 冲突时要写全 `boost::accumulators::max(acc)`。
