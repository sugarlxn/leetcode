#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
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
    
    int n,H,P;
    char d;
    cin >> n >> H >> P >> d;
    vector<int> x(n);
    for(int i=0;i<n;i++){
        cin >> x[i];
    }

    if( P ==0 && d == 'L'){
        d = 'R';
    }
    if(P == H && d == 'R'){
        d = 'L';
    }

    long long y;
    if(d == 'R'){
        y =P;
    }else{
        y = 2*H - P;
    }

    long long collisions = 0;

    for(int i=0;i<n;i++){
       long long nextY = y + x[i];
       collisions += nextY / H - y /H;
        
       y = nextY % (2*H);
    }

    if(y == 0){
        P=0;
        d = 'R';
    }else if(y < H){
        P = y;
        d = 'R';
    }else if(y == H){
        P = H;
        d = 'L';
    }else{
        P = 2*H - y;
        d = 'L';
    }

    cout << collisions << " " << P << " " << d << endl;

    return 0;
}