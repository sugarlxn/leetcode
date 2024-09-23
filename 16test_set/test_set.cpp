#include <iostream>
#include <set>
using namespace std;

int main(int argc, char * argv[]){
    cout << "test set!" << endl;
    int i;
    int ia[5] = {0,1,2,3,4};
    set<int> iset(ia,ia+5);
    cout << "size = " << iset.size() << endl;
    cout << "3 count = " << iset.count(3) << endl; //计算3出现的次数
    iset.insert(3);
    cout << "size = " << iset.size() << endl;
    cout << "3 count = " << iset.count(3) << endl; //计算3出现的次数
    iset.insert(5);
    cout << "size = " << iset.size() << endl;
    cout << "3 count = " << iset.count(3) << endl; //计算3出现的次数i
    iset.erase(1);
    cout << "size = " << iset.size() << endl;

    set<int>::iterator ite1 = iset.begin();
    set<int>::iterator ite2 = iset.end();
    for(;ite1 != ite2; ++ite1){
        cout << *ite1 << " ";
    }
    cout << endl;

    //使用STL算法find()查找元素，可以有效运作，但不是好方法
    //事实上不能正常运作
/*
    ite1 = find(iset.begin(),iset.end(),3);
    if(ite1 != iset.end()){
        cout << "3 found" << endl;
    }
    ite1 = find(iset.begin(),iset.end(),1);
    if(ite1 == iset.end()){
        cout << "1 not found" << endl;
    }
*/

    //面对关联式容器，应该使用其所提供的find函数来搜索元素
    ite1 = iset.find(3);
    if(ite1 != iset.end()){
        cout << "3 found" << endl;
    }
    ite1 = iset.find(1);
    if(ite1 == iset.end()){
        cout << "1 not found" << endl;
    }

    //企图通过迭代器改变set中的元素，是不被允许的
    // *ite1 = 9; //错误
/*
    /home/lxn/leetcode/16test_set/test_set.cpp:50:11: error: assignment of read-only location ‘ite1.std::_Rb_tree_const_iterator<int>::operator*()’
   50 |     *ite1 = 9; //错误
      |     ~~~~~~^~~
*/

    return 0;
}