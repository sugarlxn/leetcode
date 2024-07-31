#include <iostream>
#include "RCLString.hpp"
using namespace std;


int main(int argc, char * argv[]){

    cout << "hello world" << endl;
    RCL::String str1("hello");
    RCL::String str2("world");
    cout << str1[0] << endl;
    cout << str2[0] << endl;
    
    return 0;
}