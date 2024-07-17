#include <iostream>
using namespace std;

int main(int argc, char * argv[]){

    //多组数据，每组第一行为n，之后输入n行两个整数
    int n,a,b;
    while(cin >> n){
        while(n--){
            cin >> a >> b;
            //cin >> a; cin >> b;
            cout << a+b << endl;
        }
    }

    return 0;
}