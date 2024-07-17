#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    //若干行输入，每行输入两个整数，特殊条件时终止
    int a,b;
    while(cin >> a >> b){
        if(a==0 && b==0){
            break;
        }
        cout << a+b << endl;
    }

    return 0;
}