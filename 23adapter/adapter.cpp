#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char * argv[]){

    cout << "===============" << endl;
    cout << "Hello adapter! (｡･∀･)ﾉﾞ嗨!" << endl;

    //将outite 绑定到cout, 每次对outite指派一个元素，就后接一个','
    ostream_iterator<int> outite(cout, ",");

    int ia[] = {0, 1, 2, 3, 4, 5};
    deque<int> id(ia, ia + 6);

    //将id的每个元素拷贝到outite指向的位置
    copy(id.begin(), id.end(), outite);
    cout << endl;

    copy(ia+3, ia+4, back_inserter(id));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    copy(ia+3, ia+4, front_inserter(id));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    deque<int>::iterator ite = find(id.begin(), id.end(), 3);
    copy(ia+0, ia+3, inserter(id, ite));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    return 0;
}