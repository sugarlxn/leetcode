#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    //若干行输入，遇到0终止，每行第一个数为n, 表示接下来有n个数
    int n,a;
    while(cin >> n){
        if(n == 0){
            return 0;
        }
        while(n--){
            cin >> a;
            if(a == 0){
                break;
            }
            cout << a << endl;
        }
    }
    return 0;
}