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

## 贡献

PRs accepted.

## 许可证

MIT © Richard McRichface