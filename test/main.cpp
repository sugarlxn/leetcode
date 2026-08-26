#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
// #include <cmath>
#include <iomanip>
using namespace std;


#define LOCAL 1
#if LOCAL
    std::ifstream in("../input.txt");
    std::ofstream out("../output.txt");
#define cin in
#define cout out
#endif

int main(int argc, char *argv[]) {
    
    int i,j;
    cin >> i >> j;
    cout << "i:" << i << " j:" << j << endl;
    double ans = 650.0005;

    //输出ans 并且保留3位小数精度
    cout << fixed << setprecision(3) << ans << endl;


    return 0;
}