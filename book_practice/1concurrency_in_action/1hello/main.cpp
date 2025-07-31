#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello, Concurrency!" << std::endl;
}

void hello2()
{
    std::cout << "Hello, Concurrency from a second thread!" << std::endl;
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
    // 构造函数接受一个 std::thread 引用, explicit 防止隐式转换 防止编译器 将 std::thread 对象转换为 thread_guard 对象
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

    //所有权转换 std::move
    std::thread t1(hello);
    std::thread t2 = std::move(t1); // 转移所有权
    t1 = std::thread(hello2); // 重新赋值，创建新的线程 std::move 会隐式调用
    std::thread t3;
    t3 = std::move(t2); // 转移所有权
    //t1 = std::move(t3); // 再次转移所有权 会出现报错 t1 已经关联了一个线程 
    //不能再关联另一个线程 系统会调用 std::terminate() 终止程序
    if(t3.joinable()) {
        t3.join(); // 等待线程结束
    }
    if(t1.joinable()) {
        t1.join(); // 等待线程结束
    }
    return 0;
}