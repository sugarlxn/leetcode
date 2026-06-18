#include <iostream>
#include <iterator>

using namespace std;

//通用版本 
template<typename T, typename I>
struct Foo
{
    void Print()
    {
        cout << "通用版本" << endl;
    }
};


//偏特化版本
template<typename T>
struct Foo<T, int>
{
    void Print()
    {
        cout << "偏特化版本" << endl;
    }
};

//全特化
template<>
struct Foo<int, int>
{
    void Print()
    {
        cout << "全特化版本" << endl;
    }
};

int main(int argc, char * argv[]){

    Foo<double, double> f1; //通用版本
    Foo<double, int> f2; //偏特化版本
    Foo<int, int> f3; //全特化版本

    f1.Print();
    f2.Print();
    f3.Print();

    return 0;
}   