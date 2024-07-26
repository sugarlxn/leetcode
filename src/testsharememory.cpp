#include <string>
#include <iostream>
 
using namespace std;
 
int main()
{
    string str1("hello world");
    string str2(str1);
 
    printf ("Sharing the memory:\n");
    printf ("str1's address: %p\n", str1.c_str());
    printf ("str2's address: %p\n", str2.c_str());
 
    // str1[1]='q';
    // str2[1]='w';
 
    // printf ("After Copy-On-Write:\n");
    // printf ("str1's address: %p\n",str1.c_str());
    // printf ("str2's address: %p\n",str2.c_str());
 
    printf("Hello world!");
    return 0;
}