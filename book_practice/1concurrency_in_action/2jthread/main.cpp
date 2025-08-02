#include <iostream>
#include "jthread.hpp"

void thread_function(int id) {
    std::cout << "Thread " << id << " is running." << std::endl;
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " has finished." << std::endl;
}



int main(int argc, char* argv[]) {

    joining_thread t1(thread_function, 1);
    joining_thread t2(thread_function, 2);
    joining_thread t3(thread_function, 3);
    joining_thread t4(thread_function, 4);
    joining_thread t5(thread_function, 5);


    // joining thread auto join
    std::cout << "All threads have been created." << std::endl;

    //hardware_concurrency
    unsigned int num_threads = std::thread::hardware_concurrency();
    std::cout << "Number of concurrent threads supported: " << num_threads << std::endl;

    
    //this thread id
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "Main thread ID: " << this_id << std::endl;
    
    //sleep 1 sec
    std::this_thread::sleep_for(std::chrono::microseconds(1500));
    return 0;
}