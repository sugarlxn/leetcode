#include <iostream>
#include "safe_stack.hpp"

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

    return 0;
}