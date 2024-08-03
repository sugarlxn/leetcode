#include <iostream>
using namespace std;

/// @brief 链表节点namespace
namespace my_linklist{

    /// @brief 链表类 模板类
    /// @tparam T 
    template <typename T>
    class Linklist
    {
    public:
        /// @brief 链表节点
        struct LinkNode
        {
            T val;
            LinkNode* next;
            /// @brief LinkNode的构造函数
            /// @brief struct中如果添加一个构造函数，需要再添加默认构造函数
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
        /// @brief 链表长度
        int _size;
        /// @brief 虚拟头节点
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

int main(int argc, char * argv[]){

    cout << "Hello, World!" << endl;
    my_linklist::Linklist<int> linklist;
    linklist.addAtHead(1);
    linklist.addAtTail(3);
    linklist.addAtIndex(1, 2);
    linklist.printLinklist();
    cout << linklist.get(1) << endl;
    linklist.deleteAtIndex(1);
    linklist.printLinklist();
    
    return 0;
}