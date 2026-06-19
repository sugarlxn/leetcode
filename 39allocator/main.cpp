#include <memory>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){

    allocator<int> alloc;

    int * p = alloc.allocate(5); //分配内存，返回指向第一个元素的指针

    //构造前3个元素
    allocator_traits<allocator<int>>::construct(alloc, p, 1); //在p指向的内存位置构造一个值为1的对象
    allocator_traits<allocator<int>>::construct(alloc, p + 1, 2);
    allocator_traits<allocator<int>>::construct(alloc, p + 2, 3);

    cout << p[0] << " " << p[1] << " " << p[2] << endl; //输出构造的元素
    //销毁前3个元素
    allocator_traits<allocator<int>>::destroy(alloc, p); 
    allocator_traits<allocator<int>>::destroy(alloc, p + 1); 
    allocator_traits<allocator<int>>::destroy(alloc, p + 2);

    //返回内存
    alloc.deallocate(p, 5); //释放之前分配的内存


    return 0;
}