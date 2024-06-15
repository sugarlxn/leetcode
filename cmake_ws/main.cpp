#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "linklist.hpp"
using namespace std;

//单链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {} //节点构造函数，此时不再有默认构造函数
    ListNode(): val(0), next(NULL) {} //默认构造函数, 在为struct添加构造函数时，需要添加默认构造函数
};

vector<int> test1(vector<int>& nums){
    vector<int> res = nums;
    res[res.size()-1] = 8;
    return res;
}

/// @brief  打印vector
/// @tparam T 
/// @param nums 
/// @param flag 
template <typename T>
void my_printf_vector(const vector<T>& nums, bool flag = 0){
    //横向打印
    if(flag == 0){
        for(T i : nums){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    //纵向打印
    else{
        for(T i : nums){
            std::cout << i << std::endl;
        }
    }
}

/// @brief 打印matrix
/// @tparam T 
/// @param matrix 
template <typename T>
void my_printf_matrix(const vector<vector<T>>& matrix){
    for(vector<T> v : matrix){
        for(T i : v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void my_printf_args(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
}


int main(int argc, char *argv[])
{


    printf("Hello World\n");
    vector<int> v = {3, 7, 1, 4, 5};
    vector<int> res = test1(v);
    std::sort(v.begin(), v.end());
    my_printf_vector<int>(v);
    my_printf_vector<int>(res);

    vector<float> c = {0.0,1.5,2.4,8,9};
    std::sort(c.begin(), c.end());
    my_printf_vector<float>(c,1);

    int int_max = INT32_MAX;
    //以HEX显示 int_max
    printf("int_max = %x\n", int_max);
    printf("int_max = %d\n", int_max);
    unsigned int uint_max = UINT32_MAX;
    printf("uint_max = %x\n", uint_max);
    printf("uint_max = %d\n", uint_max);

    //
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    //初始化一个大小为n*n的matrix，初值为0
    int n = 3;
    auto a = int(1);
    vector<vector<int>> matrix2(n, vector<int>(n, 0));
    //打印该matrix
    my_printf_matrix<int>(matrix);
    my_printf_matrix<int>(matrix2);

    //float 类型的matrix
    vector<vector<float>> matrix3(n, vector<float>(n, 0.0));
    my_printf_matrix<float>(matrix3);

    vector<float> vf(10, 0.0);
    my_printf_vector<float>(vf);

    //测试boost::shared_ptr
    boost::shared_ptr<int> p(new int(10));
    cout << *p << endl;

    //创建一个int类型的链表，并加入元素 1 3 5 7 9
    my_linklist::Linklist<int> linklist;
    linklist.addAtHead(1);
    linklist.addAtTail(3);
    linklist.addAtIndex(1, 5);
    linklist.addAtIndex(3, 7);
    linklist.addAtIndex(4, 9);
    linklist.printLinklist();
    //删除第2个元素
    linklist.deleteAtIndex(2);
    linklist.printLinklist();
    //删除第4个元素
    linklist.deleteAtIndex(4);
    linklist.printLinklist();
    //添加10 到链表尾部
    linklist.addAtTail(10);
    linklist.printLinklist();

    return 0;


}
