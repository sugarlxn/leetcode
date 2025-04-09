#include<iostream>
#include<fstream>
#include<chrono>

using namespace std;
#define LOCAL

int main(int argc, char * argv[]){
    //关闭cin cout 缓存同步 不能同时使用 cin cout 和 scanf printf
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    ifstream infile("../in.txt");
    ofstream outfile("../out.txt"); 
#define cin infile
#define cout outfile
#endif

    //开始计时
    auto start = chrono::high_resolution_clock::now();
    
    cout << "good day today!" << endl;
    cout << "it is outfile!" << endl;

    int x=0;
    for(int i=0; i < 1000000; i++){
        cin >> x;
        cout << x << endl;
    }

    //结束计时
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cerr << "Time taken: " << elapsed.count() << " seconds" << endl;
     
    return 0;
}