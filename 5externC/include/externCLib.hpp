#pragma once
#include <cstdio>

///NOTE{extern ＂C＂ 的运用可以简化“必须同时被 C 和 C++使用”的头文件维护工作。当这个文件用于C++时，
///你希望含有 extern ＂C＂；用于 C 时，你不希望如此。由于预处理器（preprocessor）符号__cplusplus 只针对 C++才有定义，
///所以这种“通用于数种语言”的头文件可以架构如下：}

/// @brief extern "C" 函数块
#ifdef __cplusplus
extern "C" {
#endif

void printHelloWorld(){
    printf("Hello World!\n");
}
void printHi(){
    printf("Hi!\n");
}
void printBye(){
    printf("Bye!\n");
}

#ifdef __cplusplus
}
#endif

///@brief 单个函数的 extern "C" 声明
#ifdef __cplusplus
extern "C" 
#endif
void printfLxn(){
    printf("Lxn\n");
};
