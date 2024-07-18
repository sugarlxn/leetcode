#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[]){
    //多组测试⽤例，第⼀⾏为正整数n, 第⼆⾏为n个正整数，n=0
    //时，结束输⼊，每组输出结果的下⾯都输出⼀个空⾏
    int n;
    while(cin >> n){
        if(n == 0) break;
        //创建vector
        vector<int> nums = vector<int>(n,0);
        //输入一组数据
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        //遍历
        for(int i = 0; i < n; i++){
            cout << nums[i] << " ";
        }
        cout << endl;
    }
    return 0;
}