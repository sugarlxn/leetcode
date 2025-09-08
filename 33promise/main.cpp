#include <iostream>
#include <thread>
#include <future>

void worker(std::promise<int> p) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟一些工作
    p.set_value(42); // 设置结果
}


int main(int argc, char * argv[]){

    std::promise<int> p; // 创建一个 promise 对象
    std::future<int> f = p.get_future(); // 获取与 promise 关联的

    std::thread t(worker, std::move(p)); // 启动线程并传递 promise

    std::cout << "Waiting for the result..." << std::endl;
    int result = f.get(); // 等待结果 
    std::cout << "Result: " << result << std::endl; 

    t.join(); // 等待线程结束
    std::cout << "Thread finished." << std::endl;


    return 0;
}