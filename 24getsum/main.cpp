#include <iostream>

using namespace std;

int getSum(int a, int b) {
    int sum;
    cout << "a:" << dec << a << ", b:" << dec << b << endl;
    cout << "a:0x" << hex << a << ", b:0x" << hex << b << endl;
    while(b!=0) {
        sum = a ^ b;
        unsigned int carry =(unsigned int)(a & b) << 1;
        cout << "sum:0x" << hex << sum << ", carry:0x" << hex  << carry << endl;
        a = sum;
        b = carry;
    }
    return sum;
}

int main() {
    cout << "Waiting for order!" << endl;
    int sum = getSum(-2, -3);
    cout << "sum:0x" << hex << sum << "(" << dec << sum << ")" << endl;
    return 0;
}
