//线程安全队列
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class threadsafe_queue{
private:
    mutable std::mutex mut;  // 互斥锁，保护队列的访问
    std::queue<T> data_queue; // 线程安全的队列 
    std::condition_variable data_cond; // 条件变量，用于通知等待的线程
public:
    threadsafe_queue() {};
    threadsafe_queue(const threadsafe_queue& other) {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue = other.data_queue;
    }

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(new_value));
        data_cond.notify_one(); // 通知一个等待的线程
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [&data_queue = this->data_queue] { return !data_queue.empty(); }); // 等待直到队列不为空
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut); 
        if (data_queue.empty()) {
            return false; // 如果队列为空，返回 false
        }
        value = std::move(data_queue.front());
        data_queue.pop();
        return true; // 成功弹出元素
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()) {
            return std::shared_ptr<T>(); // 如果队列为空，返回空指针
        }
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res; // 返回弹出的元素
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty(); // 检查队列是否为空
    }

};