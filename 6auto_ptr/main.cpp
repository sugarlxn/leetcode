#include <iostream>
#include "auto_ptr.hpp"
using namespace std;

int main(int argc, char * argv[]){

    cout << "Hi, auto Ptr!" << endl;
    SmartPtr::auto_ptr<int> p(new int(42));
    cout << *p << endl;
    SmartPtr::auto_ptr<string> str1(new string("Hi, I am auto ptr!"));
    cout << *str1 << endl;

    
    return 0;
}