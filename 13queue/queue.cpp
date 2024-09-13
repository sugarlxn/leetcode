#include <iostream>
#include <deque>
#include <vector>
using namespace std;

/*
mini_stl queue implement
copy from 侯捷STL 4.6.2 queue定义完整列表
*/

namespace mini_STL{

#define __STL_NULL_TMPL_ARGS <>

template<class T, class Sequence = deque<T>>
class queue{
    //以下的__STL_NULL_TMPL_ARGS, 会展开为<> 见1.9.1节
    //FIXME: 这里似乎有点问题
    friend bool operator== __STL_NULL_TMPL_ARGS(const queue& x, const queue& y);
    friend bool operator< __STL_NULL_TMPL_ARGS(const queue& x, const queue& y);
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
protected:
    Sequence c; //底层容器
public:
    //以下完全利用Sequence c的操作，完成queue的操作
    bool empty() const {return c.empty();}
    size_type size() const {return c.size();}
    reference front() {return c.front();}
    const_reference front() const{return c.front();}
    reference back(){return c.back();}
    const_reference back() const{return c.back();}
    //queue 是先进先出，只允许在队尾插入元素，队首取出元素
    void push(const value_type& x){c.push_back(x);}
    void pop(){c.pop_front();}

};

template<class T, class Sequence>
bool operator==(const queue<T, Sequence>& x, const queue<T, Sequence>& y){
    return x.c == y.c;
}
template<class T, class Sequence>
bool operator < (const queue<T, Sequence>& x, const queue<T, Sequence>& y){
    return x.c < y.c;
}

};//namespace mini_STL


int main(int argc, char * argv[]){

    cout << "hello world" << endl;

    return 0;
}