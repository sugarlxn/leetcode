#include <iostream>
#include <deque>
#include <vector>
using namespace std;

namespace SQ{
template<typename T>
class SingleQueue{
public:
    ///@brief 构造函数
    SingleQueue(){};
    ///@brief 析构函数
    ~SingleQueue(){};
    ///@brief 入队
    void push(T x){
        while(!sq.empty() && x > sq.back()){
            sq.pop_back();
        }
        sq.push_back(x);
    }
    ///@brief 出队
    void pop(T x){
        if(!sq.empty() && sq.front() == x){
            sq.pop_front();
        }
    }
    ///@brief 获取队首元素
    T front(){
        return sq.front();
    }
private:
    // 用deque实现队列
    deque<T> sq;

};//class SingleQueue

/// @brief 滑动窗口最大值
/// @param nums 
/// @param k 滑动窗口大小
/// @return 
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    SingleQueue<int> singleque;
    vector<int> result;
    for(int i=0; i < k; i++){
        singleque.push(nums[i]);
    }
    result.push_back(singleque.front());//记录前k个元素的最大值
    for(int i=k; i<nums.size();i++){
        singleque.pop(nums[i-k]);//滑动窗口移除最前面的元素
        singleque.push(nums[i]);//滑动窗口移除向前移动
        result.push_back(singleque.front());//记录该窗口的最大值
    }
    return result;
}

};//namespace SQ


int main(int argc, char *argv[])
{
    cout << "Hello, World!" << endl;
    SQ::SingleQueue<int> sq;
    sq.push(1);
    sq.push(2);
    sq.push(3);
    cout << sq.front() << endl;
    sq.pop(1);
    cout << sq.front() << endl;
    sq.pop(2);
    cout << sq.front() << endl;

    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> result = SQ::maxSlidingWindow(nums, k);
    for(auto i : result){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}