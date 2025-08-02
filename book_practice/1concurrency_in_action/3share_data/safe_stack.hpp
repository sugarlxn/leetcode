#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception {
    const char* what() const noexcept override { //不抛出异常 
        return "empty stack";
    }
};

//模板类
template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data; //存储数据的栈
    mutable std::mutex m; //互斥锁，保护数据访问
public:
    threadsafe_stack() : data(std::stack<T>()) {};

    //拷贝构造函数
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data; //拷贝数据 拷贝赋值
    }

    //禁止赋值操作
    threadsafe_stack& operator=(const threadsafe_stack&) = delete; 

    //按值传递 已经对变量拷贝一次 
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m); //锁定互斥量
        data.push(std::move(new_value)); //将新值压入栈中 使用移动语义 避免不必要的拷贝（避免第二次拷贝）
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m); //锁定互斥量
        if (data.empty()) {
            throw empty_stack(); //如果栈为空，抛出异常
        }
        //使用移动语义获取栈顶元素
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop(); //弹出栈顶元素
        return res; //返回栈顶元素的智能指针
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m); //锁定互斥量
        if (data.empty()) {
            throw empty_stack(); //如果栈为空，抛出异常
        }
        value = std::move(data.top()); //将栈顶元素移动到 value 中
        data.pop(); //弹出栈顶元素
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m); //锁定互斥量
        return data.empty(); //检查栈是否为空
    }

};
