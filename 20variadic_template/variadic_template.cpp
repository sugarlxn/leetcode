#pragma GCC optimize(2, 3, "Ofast", "inline")
#include <iostream>
#include <initializer_list>
using namespace std;

///方法一
//递归打印可变参数列表
void log(){
    cout << endl;
}   
//variadic template
template<typename T, typename... Args>
void log(T firstArg, Args... args){
    cout << firstArg << " ";
    log(args...);
}

//方法二
//使用 initializer_list
template <typename T>
void log2(initializer_list<T> args){
    for(auto i : args){
        cout << i << " ";
    }
    cout << endl;
}

int main(int argc, char * argv[]){

    cout << "varidic_template" << endl;
    log("a", 1, 2.0, 3.0f, "hello","good day today!");

    log2<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    int i,j,m,n;
    i=j=m=n=0;
    cout << "begin" << endl;
    log(i,j,m,n);
    cout << "end" << endl;

    return 0;
}