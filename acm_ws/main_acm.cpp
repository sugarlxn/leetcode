#include <iostream>

int main(int * argc, char * argv[]){

    std::cout << "holle word!!" << std::endl;
    int a,b;
    while (std::cin >> a >> b)
    {
        std::cout << a + b << std::endl;
    }
    return 0;
}