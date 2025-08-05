#include <iostream>
#include <future>
#include <thread>

int find_the_answer_to_ltuae() {
    std::cout << "Calculating the answer to life, the universe, and everything..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate a long computation
    return 42; // The answer
}

void do_something(){
    std::cout << "Doing something else while waiting for the answer..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate some work
}

int main(int argc, char* argv[]) {

    std::future<int> the_answer = std::async(std::launch::async, find_the_answer_to_ltuae);
    do_something(); // Do something else while the answer is being calculated
    std::cout << "The answer is: " << the_answer.get() << std::endl; // Get the result, blocking if necessary
    
    return 0;
}