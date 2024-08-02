#include <iostream>
#include <string>
#include "externCLib.hpp"
using namespace std;


int main(int argc, char * argv[]){
    string str = "I am a string!";
    cout << "Hello World!" << endl;
    printHelloWorld();
    printHi();
    printBye();
    printfLxn();
    return 0;
}