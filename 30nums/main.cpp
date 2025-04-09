#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


string a;
int count = 0;
void com(int i, int j){
	cout << i << " " << j << endl;
    while(a[i]==a[j]&&i<j) {
        i++;
        j--;
    }
    if(i>=j)return;
    if(a[i]>a[j]){
        count++;
    }
    return;
}

int main(int argc, char** argv) {

	//输入num 
	getline(cin, a);
	int n = a.size();
	
	//双指针 二维遍历
	for(int i=0; i < n-1; i++){
		for(int j=i+1; j < n; j++){
			com(i,j);
		}
	} 
	cout << count;
	return 0;
}