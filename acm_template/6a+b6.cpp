#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    //多组n⾏数据，每⾏先输⼊⼀个整数N，然后在同⼀⾏内输⼊
    //M个整数,每组输出之间输出⼀个空⾏
    int n,m,a;
    int sum;
    //每组n行数据
    while(cin >> n){
        while(n--){
            cin >> m;
            while(m--){
                cin >> a;
                sum += a;
            }
        }
        cout << sum << endl << endl;
        sum = 0;
    }
    return 0;
}