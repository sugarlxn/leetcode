#include<iostream>
#include<fstream>

using namespace std;
#define LOCAL

int main(int argc, char * argv[]){
#ifdef LOCAL
    ifstream infile("../in.txt");
    ofstream outfile("../out.txt"); 
#endif
    
    cout << "good day today!" << endl;
    outfile << "it is outfile!" << endl;

    int i,j;
    infile >> i >> j;
    outfile << "i:" << i << "j:" << j <<endl;
     
    return 0;
}