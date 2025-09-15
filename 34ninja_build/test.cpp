#include <iostream>
#include <chrono>
#include <list>
#include <future>
#include <algorithm>

//快速排序 并行版
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input){
    if(input.empty()){
        return input;
    }
    std::list<T> result;
    //将 input 链表的第一个元素（input.begin()）移动到 result 链表的开头（result.begin()），
    //不会进行元素的拷贝或构造，只是指针操作，效率很高
    result.splice(result.begin(),input,input.begin());
    T const& pivot = *result.begin();
    //std::partition：标准库算法，按条件分组，满足条件的在前面，不满足的在后面。
    //lambda 表达式，[&] 表示捕获所有在当前作用域可用的外部变量的引用
    auto divide_point = std::partition(input.begin(),input.end(),[&](T const& t){return t<pivot;});

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(),input,input.begin(),divide_point);
    //使用 std::async 异步地调用 parallel_quick_sort 函数，对 lower_part 这部分链表进行并行快速排序。
    std::future<std::list<T>> new_lower(
        std::async(&parallel_quick_sort<T>,std::move(lower_part))
    );

    auto new_higher = parallel_quick_sort(std::move(input));
    result.splice(result.end(),new_higher);

    result.splice(result.begin(),new_lower.get());
    return result;

}

int main(int argc, char * argv[]){

    std::cout << "Good day today!" << std::endl;
    const std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&now_c) << std::endl <<std::flush;
    //定义一个乱序链表，类型为int
    std::list<int> ilist = {7,5,16,8,12,4,9,3,13,6,2,10,15,1,14,11};
    //调用并行快速排序函数
    ilist = parallel_quick_sort(ilist);
    for(auto i:ilist){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}