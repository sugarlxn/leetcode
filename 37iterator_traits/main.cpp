#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template<class Iterator>
void inspect(Iterator it){
    using traits = iterator_traits<Iterator>;
    //萃取类型信息
    typename traits::value_type value = *it; //value_type是迭代器的值类型
    typename traits::difference_type diff = 0; //difference_type是迭代器的距离类型
    typename traits::pointer pointer = &(*it); //pointer是迭代器的指针类型
    cout << "Value: " << value << endl;
    cout << "Difference type: " << typeid(diff).name() << endl;
    cout << "Pointer type: " << typeid(pointer).name() << endl;
}


int main(int argc, char * argv[]){

    vector<int> v = {1, 2, 3, 4, 5};

    // using iterator_traits to get the value type of the iterator
    typedef iterator_traits<vector<int>::iterator>::value_type value_type;

    inspect(v.begin());
    inspect(&v[0]);

    return 0;
}