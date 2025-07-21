#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

//attribute test
__attribute__((constructor))
void init(){
    // cout << "init" << endl;
    write(1, "init\n", 5);
}

__attribute__((destructor))
void destroy(){
    // cout << "destroy" << endl;
    write(1, "destroy\n", 8);
}

void func1(){
    std::cout << "func1" << std::endl;
    //write(1, "func1\n", 6);
}

void func2(){
    std::cout << "func2" << std::endl;
    //write(1, "func2\n", 6);
}

int main(int argc, char** argv) {

    //使用atexit注册函数
    atexit(func1);
    atexit(func2);

    cout << "main" << endl;
    //系统调用
    mkdir("test", 0777);

    return 0;
}