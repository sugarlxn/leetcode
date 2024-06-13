#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
using namespace std;


//单链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {} //节点构造函数，此时不再有默认构造函数
    ListNode(): val(0), next(NULL) {} //默认构造函数, 在为struct添加构造函数时，需要添加默认构造函数
};

namespace my_linklist{

    template <typename T>
    class Linklist
    {
    public:
        struct LinkNode
        {
            T val;
            LinkNode* next;
            LinkNode();
            LinkNode(T x);
            ~LinkNode();
        };

        Linklist();
        ~Linklist();
        /// @brief 获取第index个节点的值，index从0开始，如果index大于链表长度，返回-1
        /// @param index 
        /// @return 
        T get(int index);
        /// @brief 在链表前面插入一个结点，val为结点的值
        /// @param val 
        bool addAtHead(T val);
        /// @brief 在链表后面添加一个节点
        /// @param val 
        bool addAtTail(T val);
        /// @brief 在index之前插入一个节点
        /// @param index 
        /// @param val 
        bool addAtIndex(int index, T val);
        /// @brief 删除第index个节点
        /// @param index 
        bool deleteAtIndex(int index);
        /// @brief 打印链表
        void printLinklist();

    private:
        int _size;
        LinkNode * _dummyHead;

    };

    /// @brief Linklist的构造函数
    /// @tparam T 
    template <typename T>
    Linklist<T>::Linklist()
    {
        _size = 0;
        _dummyHead = new LinkNode();
    }
    
    template <typename T>
    Linklist<T>::~Linklist()
    {
    }

    /// @brief LinkNode的构造函数
    /// @tparam T 
    template <typename T>
    Linklist<T>::LinkNode::LinkNode()
    {
        val = 0;
        next = nullptr;
    }

    template <typename T>
    Linklist<T>::LinkNode::LinkNode(T x)
    {
        val = x;
        next = nullptr;
    }

    template <typename T>
    Linklist<T>::LinkNode::~LinkNode()
    {
    }   
    
    template <typename T>
    T Linklist<T>::get(int index){
        if (index > (_size -1) || index < 0){return -1;}
        LinkNode * cur = _dummyHead->next;
        while (index--){cur = cur->next;}
        return cur->val;
    }

    template <typename T>
    bool Linklist<T>::addAtHead(T val){
        LinkNode * newNode = new LinkNode();
        if(newNode==nullptr){return false;}
        newNode->val = val;
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size++;
        return true;
    }

    template <typename T>
    bool Linklist<T>::addAtTail(T val){
        LinkNode * newNode = new LinkNode();
        if(newNode == nullptr){return false;}
        newNode->val = val;
        LinkNode * cur = _dummyHead;
        while (cur->next != nullptr){cur = cur->next;}
        cur->next = newNode;
        _size++;
        return true;
    }

    template <typename T>
    bool Linklist<T>::addAtIndex(int index, T val){
        if(index > _size){return false;}
        LinkNode * newNode = new LinkNode();
        if(newNode == nullptr){return false;}
        newNode->val = val;
        LinkNode * cur = _dummyHead;
        while (index--){cur = cur->next;}
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
        return true;
    }

    template <typename T>
    bool Linklist<T>::deleteAtIndex(int index){
        if(index >= _size){return false;}
        LinkNode * cur = _dummyHead;
        while (index--){cur = cur->next;}
        LinkNode * tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        _size--;
        return true;
    }

    template <typename T>
    void Linklist<T>::printLinklist(){
        LinkNode * cur = _dummyHead->next;
        while (cur != nullptr){
            std::cout << cur->val << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }

}


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
