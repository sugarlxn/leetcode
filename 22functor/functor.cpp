#include <iostream>
#include <functional>
using namespace std;

/*
functor function 仿函数，也称为函数对象，可以像函数一样被调用对象
*/

//NOTE functor unary_function 一元仿函数，STL中定义了一元仿函数的基类，建议你去继承它
/*
unary_function<typename Arg_type, typename return_type>
*/
template <typename T>
struct negate: public unary_function<T, T>{
    T operator()(const T& x) const{
        return -x;
    }
};

//NOTE functor binary_function 二元仿函数，STL中定义了二元仜函数的基类，建议你去继承它
/*
binary_function<typename arg_type_1, typename arg_type_2, typename return_type>
*/
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