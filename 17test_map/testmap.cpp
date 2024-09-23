#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(int argc, char * argv[]){

    cout << "hello map!" << endl;
    map<string, int> simap;
    // NOTE : 初始化方式一
    simap[string("lxn")] = 1;
    simap[string("jxd")] = 2;
    simap[string("zj")] = 3;
    simap[string("qwer")] = 4;
    //NOTE: 初始化方式二
    pair<string, int> value(string("Rudy"), 5);
    simap.insert(value);

    map<string, int>::iterator simap_iter = simap.begin();
    for(;simap_iter != simap.end(); ++simap_iter){
        cout << simap_iter->first << " " << simap_iter->second << endl;
    }

    //查找
    int number = simap[string("Rudy")];
    cout << "Rudy = " << number << endl;

    map<string ,int>::iterator ite1;
    //面对关联式容器，应该使用其所提供的find函数搜索元素，会比STL
    //算法find 更有效率，因为STL算法find只是循序搜寻
    ite1 = simap.find(string("lxn1"));
    if(ite1 == simap.end()){
        cout << "lxn1 not found" << endl;
    }

    ite1 = simap.find(string("lxn"));
    if(ite1 != simap.end()){
        cout << "lxn found" << endl;
    }

    ite1->second = 9; //企图通过迭代器改变map中的元素，是被允许的
    cout << "lxn = " << simap[string("lxn")] << endl;

    

    return 0;
}