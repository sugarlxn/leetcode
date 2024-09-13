#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
file heap_test.cpp copy form 侯捷STL 4.7.4 heap测试实例
底层以 vector 完成
*/

int main(int argc, char * argv[]){
    int ia[9] = {0,1,2,3,4,8,9,3,5};
    vector<int> iv(ia, ia+9); 
    make_heap(iv.begin(), iv.end());
    for(int i = 0; i < iv.size(); i++){
        cout << iv[i] << ' ';
    }
    cout << endl;

    iv.push_back(7);
    push_heap(iv.begin(), iv.end());
    for(int i = 0; i < iv.size(); i++){
        cout << iv[i] << ' ';
    }
    cout << endl;

    pop_heap(iv.begin(), iv.end());
    cout << iv.back() << endl;  // 9 return but no remove
    iv.pop_back();

    for(int i = 0; i < iv.size(); i++){
        cout << iv[i] << ' ';
    }
    cout << endl;

    sort_heap(iv.begin(), iv.end());
    for(int i = 0; i < iv.size(); i++){
        cout << iv[i] << ' ';
    }
    cout << endl;

    return 0;
}


