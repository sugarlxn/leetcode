#include <iostream>
using namespace std;

int main(int * argc, char * argv[]){

    std::cout << "holle word!!" << std::endl;
    int a,b;
    try
    {
        std::cin >> a;
        std::cout << a << std::endl; 
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;


    }
    // while (std::cin >> a >> b)
    // {
    //     std::cout << a + b << std::endl;
    // }
    
    return 0;
}

