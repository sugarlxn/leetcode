#include <iostream>
#include <thread>

// class joining_thread RAII 封装累，自动管理线程的生命周期 RAII (Resource Acquisition Is Initialization)
class joining_thread {
    std::thread t;
public:
    //构造函数
    joining_thread()  noexcept = default; //指定不抛出异常

    //typename&& 万能引用, 可以接受左值引用和右值引用， expicit 防止隐式转换
    template<typename Callable, typename ... Args>
    explicit joining_thread(Callable&& func, Args&& ... args):
        t(std::forward<Callable>(func), std::forward<Args>(args)...) {
    }

    //所有权转换 拷贝构造函数
    explicit joining_thread(std::thread t_) noexcept:
        t(std::move(t_)) {
    }

    //赋值构造函数
    joining_thread& operator=(std::thread t_) noexcept {
        if (t.joinable()) {
            t.join();
        }
        t = std::move(t_);
        return *this;
    }

    joining_thread& operator=(joining_thread&& other) noexcept {
        if (t.joinable()) {
            t.join();
        }
        t = std::move(other.t);
        return *this;
    }

    //析构函数
    ~joining_thread() noexcept {
        if (t.joinable()) {
            t.join();
        }
    }

    void swap(joining_thread& other) noexcept {
        std::swap(t, other.t);
    }

    std::thread::id get_id() const noexcept {
        return t.get_id();
    }

    bool joinable() const noexcept {
        return t.joinable();
    }

    void join(){
        t.join();
    }

    void detach() {
        t.detach();
    }

    std::thread& as_thread() noexcept {
        return t;
    }

    const std::thread& as_thread() const noexcept {
        return t;
    }

};