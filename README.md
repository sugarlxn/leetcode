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
.
├── 10single_queue  # 单链表实现队列
├── 11binary_tree   # 二叉树
├── 12boost_lib     # boost库的使用
├── 13queue         # 队列 
├── 14heap_test     # 堆的测试
├── 15slist_test    # 单链表的测试
├── 16test_set      # set的测试
├── 17test_map      # map的测试
├── 18test_hash     # hash的测试
├── 19memcopy       # 内存拷贝 memcopy 实现
├── 1smart_pointer  # 智能指针
├── 20variadic_template  # 可变参数模板
├── 21json_project  # json解析项目
├── 22functor       # 仿函数
├── 23adapter       # 适配器 <STL源码剖析>
├── 24getsum        # leetcode 两数之和
├── 25fork          # 系统调用 fork 函数
├── 2reference_counter # 引用计数 <STL源码剖析>
├── 3proxy_class    # 代理类 <STL源码剖析>
├── 4virtual_function  # 虚函数 <STL源码剖析>
├── 5externC        # extern "C" <STL源码剖析>
├── 6auto_ptr       # auto_ptr <STL源码剖析>       
├── 7kmp_algorithm  # KMP算法 leetcode 
├── 8link_list      # 链表 leetcode
├── 9queue_from_stack  # 用栈实现队列 leetcode
├── Makefile
├── README.md
├── acm_template
├── cmake_ws
├── include
├── notebooks
├── script
└── src


31 directories, 2 files

```

## 贡献

PRs accepted.

## 许可证

MIT © Richard McRichface