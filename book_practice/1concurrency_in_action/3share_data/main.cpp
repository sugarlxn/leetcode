#include <iostream>
#include "safe_stack.hpp"
#include <thread>
#include <mutex>

//call once flag
std::once_flag flag;

void initialize() {
    std::cout << "Initializing once by thread " << std::this_thread::get_id() << std::endl;
}

void work(){
    std::call_once(flag, initialize); // 确保初始化函数只被调用一次
    std::cout << "Working in thread " << std::this_thread::get_id() << " finished work!" << std::endl;
}

int main(int argc, char* argv[]) {
    
    threadsafe_stack<int> safe_stack;
    // safe_stack.push(1);
    // safe_stack.push(2);
    // safe_stack.push(3);

    try {
        auto value = safe_stack.pop(); // 弹出栈顶元素
        std::cout << "Popped value: " << *value << std::endl; // 输出弹出的值
    } catch (const empty_stack& e) {
        std::cerr << e.what() << std::endl; // 如果栈为空，输出异常信息
    }

    //call once example
    std::thread t1(work);
    std::thread t2(work);
    std::thread t3(work);
    t1.join();
    t2.join();
    t3.join();


    return 0;
}