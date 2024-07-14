/// @brief  测试C++的一些特性
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "linklist.hpp"
#include <new>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
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

class Node{
private:
    const int size = 10;
public:
    int val;
    Node(int x, const int size = 10): val(x), size(size){}
    Node(const int size = 10): val(0),size(size){}

    int getValue() const{
        return val;
    }


};


///两个数组的并集
vector<int> intersection(vector<int>& num1, vector<int>& num2){
    unordered_set<int> set1(num1.begin(), num1.end());
    unordered_set<int> result;
    for(int num : num2){
        //如果num在set1中，将num加入到result中
        //set1.find(num) if num is located, return the iterator, else return set1.end()
        if(set1.find(num) != set1.end()){
            result.insert(num);
        }
    }

    return vector<int>(result.begin(), result.end());

}

/// @brief 取数值各个位上的单数之和
/// @param n 
/// @return sum
int getsum(int n){
    int sum = 0;
    while (n > 0)
    {
        sum += (n % 10) * (n % 10);
        n = n / 10;
    }
    return sum;
}

/// @brief 判断一个数是否是快乐数
/// @param n 
/// @return Bool
bool isHappy(int n){
    unordered_set<int> set;
    while (true)
    {
        int sum = getsum(n);
        if(sum == 1){
            return true;
        }
        if(set.find(sum) != set.end()){
            return false;
        }
        set.insert(sum);
        n = sum;
    }
    
}

vector<int> returnvecter(bool flag = true){
#if true
    if(flag){
        return {1,2,3,4,5};
    }else{
        return {};
    }
#else
    vector<int> v = {1,2,3,4};
    if(flag){
        return v;
    }
    else{
        return vector<int>();  
    }
#endif
}

int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D){
    unordered_map<int,int> umap;//key: A[i] + B[j], value: count, 数值a+b出现的次数
    //遍历大A和大B数组，统计两个数组元素之和，和出现的次数，存放到map中
    for(int a : A){
        for(int b : B){
            umap[a+b]++;
        }
    }
    int count = 0; //统计a + b + c + d = 0 出现的次数
    for(int c : C){
        for(int d : D){
            if(umap.find(0 - (c+d)) != umap.end()){
                count += umap[0 - (c+d)];
            }
        }
    }
    return count;

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

    Node nodea = Node(10,20);
    int value = nodea.getValue();
    cout << value << endl;
    value = 30;
    cout << nodea.getValue() << endl;

    int temp_a = 10;
    int temp_b = 20;

    int * const ptr_c = &temp_a;
    *ptr_c = 30;
    cout << *ptr_c << endl;
    //ptr_c = &temp_b; //error

    const int * ptr_d = &temp_a;
    ptr_d = &temp_b;
    // *ptr_d = 30; //error
    
    //set 
    std::set<int> s;
    s.insert(0);
    s.insert(1);
    cout << "s size " << s.size() << std::endl;
    cout << "s.end() " << *s.end() << endl;

    //set find , if num is located, return the iterator, else return s.end()
    cout << "s.find(1)" << (s.find(1) == s.end()) << endl;
    cout << "s.find(2)" << (s.find(2) == s.end()) << endl;

    //map
    std::map<int, int> m;
    m[0] = 1;
    m[1] = 2;
    cout << "m size " << m.size() << std::endl;


    vector<int> v1 = {13,1,2,3,4,5,9,10,12};
    vector<int> v2 = {13,1,3,5,6,9,11,12};
    //查找v1与v2的并集
    vector<int> v3 = intersection(v1, v2);
    cout << "v3:"; 
    my_printf_vector<int>(v3);


    pair<int,int>(1,2);
    
    cout << "return vector " ;
    my_printf_vector(returnvecter());

    cout << "===========================" << endl;

    string str1 = "hello";
    cout << str1.length() << endl;
    cout << str1.size() << endl;
    cout << *str1.begin() << endl;

    cout << "==========================" << endl;
    
    my_printf_vector(vector<int>{1,2,3,4,5,6,0});


    return 0;


}
