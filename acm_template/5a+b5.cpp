#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    //若干行输入，每行输入两个整数a b，由空格分隔，每行输出后接一个空行
    int a,b;
    while(cin >> a >> b){
        cout << a + b << endl << endl;
    }
    return 0;
}