#include <iostream>
#include <string>

using namespace std;
/*
    memcopy 内存拷贝函数
    void * memcopy(void * dest, const void * src, size_t n);
    dest: 目标地址
    src: 源地址
    n: 拷贝字节数
    返回值: dest
    功能: 将src开始的n个字节拷贝到dest开始的n个字节

*/
namespace C_lib{
/*
    最简单的方法是用指针按照字节顺序复制，但是这样效率太低，
    CPU地址总线一般为32位，一次能搬运四个字节，当内存区域重叠时会出现混乱情况
*/
//FIXME{}:something worng in this function 
void * memcopy_v1(void * dest, const void * src, size_t num){
    int nchunks = num/sizeof(dest); // 拷贝的块数 
    cout << "sizeof(dest): " << sizeof(dest) << endl;
    int slice = num%sizeof(dest); // 拷贝的剩余字节数

    unsigned long * s = (unsigned long *)src;
    unsigned long * d = (unsigned long *)dest;
    // 拷贝整块
    while(nchunks--){
        *d++ = *s++;
    }
    // 拷贝剩余的字节
    while(slice--){
        *(char *)d++ = *(char *)s++;
    }
    return dest;
}


};//namespace C_lib

int main(int argc, char * argv[]){

    cout << "hello memcopy!" << endl;
    char a[20] = "hello world!";
    char b[30] = "hi, nice to meet you!";
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    C_lib::memcopy_v1(a, a, 2);
    cout << "b: " << b << endl;

    return 0;
}