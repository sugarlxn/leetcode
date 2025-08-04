# Leetcode work space

**[中文](./README.md) / [English](./README.md)**

这是一个用于平时WSL中测试CPP、python、shell等各种代码的测试目录，包括leetcode代码记录，所以它的内容分布会显得很杂，


## 如何使用

这个工作目录主要代码有main.cpp、main.py, 可以通过makefile很方便对这个工作区运行和测试
1. 编译运行CPP程序，查看makefile不难发现，可以使用`make run` 一键编译和运行main.cpp
```
make run
```
2. 运行python程序，也可如此，这些像快捷方法一样的`make` 命令，能够在测试过程中最快的启动测试代码
```
make runpy
```
3. 当然，如果你不知道makefile该怎么写，或者说该如何使用，我强烈建议你看这个tutorial：[https://makefiletutorial.com/](https://makefiletutorial.com/)

4. 该工作空间还添加了`cmake_ws`，使用`CMakeLists.txt` 比编写一个`makefile` 更快捷，更方便，也更有效，我也强烈建议你使用`CMakeLists.txt` 来构建C++项目，如果你不知道如何编写一个`CMakeLists.txt` ，我建议你去看这个tutorial：[https://cmake.org/cmake/help/latest/guide/tutorial/index.html](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)。使用CMake构建C++项目也很简单，只需要以下这几个步骤：①编写C++源文件。②编写CMakeLists.txt。③执行cmake，make。以reference_counter为例子

```
#git clone this project
#if dir build is not exit, then you can create a dir named build by "mkdir build"
cd 2reference_counter/build
cmake ..
make 
#到此在build目录下将会生成项目的可执行文件target
```

## 目录
```shell
1smart_pointer     #智能指针
2reference_counter #引用计数
3proxy_class       #代理类
4virtual_function  #虚函数
5externC           #C语言extern "C" <STL 源码剖析>
6auto_ptr          #自动指针 auto_ptr <STL 源码剖析>
7kmp_algorithm     #KMP算法
8link_list         #链表
9queue_from_stack  #使用栈实现队列 leetcode
10single_queue     #单链表实现队列
11binary_tree      #二叉树
12boost_lib        #boost库的使用
13queue            #队列
14heap_test        #堆测试
15slist_test       #单链表的测试
16test_set         #测试set容器 <STL 源码剖析>
17test_map         #测试map容器 <STL 源码剖析>
18test_hash        #测试hash容器 <STL 源码剖析>
19memcopy          #memcpy函数的实现 
20variadic_template #可变参数模板
21json_project     #json解析项目的使用
22functor          #仿函数
23adapter          #适配器 <STL 源码剖析>
24getsum           #两数之和 leetcode
25fork             #系统调用 fork 函数
26backtracking     #回溯算法
27dnamicPramming   #动态规划
28graph            #图的相关操作
29IO_template      #IO模板 ACM IO 模板
30nums             #leetcode 的某个题目
31dijkstra         #Dijkstra算法
32attribute_test   #属性测试
```

```shell
book_practice
└── 1concurrency_in_action #并发编程实践
```

```shell
1concurrency_in_action:
    1hello      #并发编程简单测试
    2jthread    #jthread的使用
    3share_data #共享数据的线程安全栈
```

## 贡献

PRs accepted.

## 许可证
[MIT © Richard McRichface](./LICENSE)