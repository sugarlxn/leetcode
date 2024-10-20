#include <iostream>
#include <functional>
using namespace std;


//functor unary_function 一元函数
template <typename T>
struct negate: public unary_function<T, T>{
    T operator()(const T& x) const{
        return -x;
    }
};

//functor binary_function 二元函数
template <typename T>
struct plus: public binary_function<T, T, T>{
    T operator()(const T& x, const T& y) const{
        return x + y;
    }
};


int main(int argc, char * argv[]){

    cout << "Hello functor! (｡･∀･)ﾉﾞ嗨!" << endl;

    return 0;
}   