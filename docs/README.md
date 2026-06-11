# 复习文档总览

本目录把仓库中的教程与实例代码系统化整理，目标是**最快速度复习 C++ 知识点和笔试算法题**。
每篇文档都标注了对应的仓库目录，可以直接 `cd` 进去编译运行，边看边练。

## 文档索引

| 文档 | 内容 | 对应仓库目录 |
|------|------|--------------|
| [01_cpp_core.md](./01_cpp_core.md) | C++ 核心语言特性：智能指针、引用计数、虚函数、extern "C"、模板、内存拷贝、位运算等 | 1~6, 19, 20, 24, 25, 32 |
| [02_stl.md](./02_stl.md) | STL 容器与组件：set/map/hash、heap、queue、仿函数、适配器、boost | 12~18, 22, 23 |
| [03_concurrency.md](./03_concurrency.md) | 并发编程：thread/jthread、mutex、promise/future/async、并行快排 | 33, 34, book_practice |
| [04_algorithms.md](./04_algorithms.md) | **笔试算法题分类**：原理 + 模板 + 仓库例子 + 推荐练习题 | 7~11, 26~28, 30, 31 |
| [05_acm_io.md](./05_acm_io.md) | ACM 笔试输入输出模板（牛客/笔试机考必备） | 29IO_template, acm_template |

## 推荐复习路线（按优先级）

笔试前时间有限时，按这个顺序过：

1. **[05_acm_io.md](./05_acm_io.md)**（30 分钟）— 笔试 ACM 模式输入输出不熟会直接 0 分，先把 `while(cin >> n)` 这套肌肉记忆找回来。
2. **[04_algorithms.md](./04_algorithms.md)**（重点，1~2 天）— 笔试题分 10 大类，每类记住一个模板：哈希、双指针/滑动窗口、链表、栈队列、二叉树、回溯、动态规划、图 DFS/BFS、最短路、排序与位运算。
3. **[02_stl.md](./02_stl.md)**（半天）— 笔试中 STL 是工具，面试中 STL 底层是考点（红黑树 vs 哈希表、deque 结构、heap 算法）。
4. **[01_cpp_core.md](./01_cpp_core.md)**（半天）— C++ 面试八股核心：智能指针怎么实现、虚函数机制、引用计数、memcpy 内存重叠。
5. **[03_concurrency.md](./03_concurrency.md)**（半天）— 并发是加分项：线程安全栈、future/promise、async。

## 如何运行仓库中的例子

每个编号目录都是独立的 CMake 小项目：

```bash
cd <目录名>            # 例如 cd 26backtracking
mkdir -p build && cd build
cmake .. && make
./<target>             # target 名见该目录的 CMakeLists.txt
```

带输入数据的题目（`28graph`、`31dijkstra`、`29IO_template`）的输入在目录下的 `in.txt`，
程序通过 `freopen`/`ifstream` 重定向读取，输出写到 `out.txt`。

顶层 `src/main.cpp` 是临时草稿区，`make run` 一键编译运行；`make runpy` 运行 `script/main.py`。
