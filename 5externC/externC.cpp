#include <iostream>
#include <string>
#include "externCLib.hpp"
using namespace std;

extern "C"{
    void print_lxn();
}

int main(int argc, char * argv[]){
    string str = "I am a string!";
    cout << "Hello World!" << endl;
    printHelloWorld();
    printHi();
    printBye();
    printfLxn();
    print_lxn(); //
    return 0;
}