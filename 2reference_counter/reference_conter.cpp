#include <iostream>
#include <string>
using namespace std;


int main(int argc, char * argv[]){

    string s1 = string("Hello");
    string s2 = s1;
    char * p = &s1[1];
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "p:" << *p << endl;

    *p = 'a';

    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "p:" << *p << endl;
    
    return 0;
}