#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    if(!fork()) {
        while (true)
        {
            std::cout << " child ";
        }
    } 
    if(!fork()) {
        while (true)    
        {
            std::cout << " parent ";
        }
    }
    wait(NULL);
    return 0;
}
