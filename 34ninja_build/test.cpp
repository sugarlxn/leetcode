#include <iostream>
#include <chrono>
#include <list>
#include <future>
#include <algorithm>

/*。通过递归调用parallel_quick_sort()，可以使用硬件并
发。 std::async() 会启动一个新线程，这样当递归三次时，就会有八个线程在运行了。当递归十次(对于大约
有1000个元素的列表)，如果硬件能处理这十次递归调用，将会创建1024个执行线程。当运行库认为产生了太
多的任务时(也许是因为数量超过了硬件并发的最大值)，可能会同步的切换新产生的任务。当任务过多时(已
影响性能)，为了避免任务传递的开销，这些任务应该在使用get()获取结果的线程上运行，而不是在新线程上
运行。这也符合 std::async 的行为，为每一个任务启动一个线程(甚至是在任务超额时，也就是
在 std::launch::deferred 没有明确规定的情况下)，或为了同步执行所有任务( std::launch::async 有明确规定的
情况下)。当运行库自动裁剪线程时，建议去查看一下运行库的实现文档，了解一下将会有怎样的行为表现。*/


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
    //返回一个iterator，指向第一个不满足条件的元素，即大于等于 pivot 的元素
    auto divide_point = std::partition(input.begin(),input.end(),[&](T const& t){return t<pivot;});

    std::list<T> lower_part;
    //将 input 链表中从 input.begin() 到 divide_point 之间的元素移动到 lower_part 链表的末尾（lower_part.end()）
    //这样lower_part 就包含了所有小于 pivot 的元素, spice iterator in the range [ input.begin(), divide_point )

    //NOTE 1 划分lower and higher
    lower_part.splice(lower_part.end(),input,input.begin(),divide_point);
    //使用 std::async 异步地调用 parallel_quick_sort 函数，对 lower_part 这部分链表进行并行快速排序。

    //NOTE 2 将lower 部分排序, 使用async 开启一个异步调用线程
    std::future<std::list<T>> new_lower(
        std::async(&parallel_quick_sort<T>,std::move(lower_part))
    );

    //NOTE 3 将higher 部分排序
    auto new_higher = parallel_quick_sort(std::move(input));
    //NOTE 4 拼接两部分list
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