#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello, Concurrency!" << std::endl;
}

//仿函数
class background_task
{
public:
    // operator() 是重载的函数调用运算符 () 参数列表
    void operator()() const{
        std::cout << "Hello, Concurrency from a functor!" << std::endl;
    }

};

//使用RAII（Resource Acquisition Is Initialization）原则，
//在构造函数中创建线程，在析构函数中等待线程结束
//避免了手动管理线程的生命周期，减少了资源泄漏的风险
class thread_guard
{
public:
    // 构造函数接受一个 std::thread 引用
    explicit thread_guard(std::thread &t) : t_(t) {}
    // 析构函数在对象销毁时调用 join()，等待线程结束
    ~thread_guard() {
        if (t_.joinable()) {
            t_.join();
        }
    }   
    
    // 禁止拷贝构造和赋值操作
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;

private:
    std::thread &t_; // 引用，避免复制线程对象
};

int main()
{
    //NOTE 
    //使用双重括号避免most vexing parse 问题， 
    //也可以使用统一格式的花括号初始化： std::thread my_bg_task{background_task()};  
    std::thread my_bg_task((background_task()));
    std::thread t(hello);
    my_bg_task.join();
    t.join();
    return 0;
}