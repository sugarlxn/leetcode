#include <iostream>
#include <stack>
#include <deque>
#include <queue>
using namespace std;

namespace QFS{
class MyQueue {
public:
    //构造函数
    MyQueue(){};
    //拷贝构造函数
    MyQueue(const MyQueue& rhs){
        stack_in = rhs.stack_in;
        stack_out = rhs.stack_out;
    };
    //赋值操作符
    MyQueue& operator=(const MyQueue& rhs){
        if(this == &rhs){return *this;}
        stack_in = rhs.stack_in;
        stack_out = rhs.stack_out;
        return *this;
    };
    //析构函数 
    ~MyQueue(){};

    //push
    void push(int x){
        stack_in.push(x);
    }

    //pop
    int pop(){
        exchange();
        int x = stack_out.top();
        stack_out.pop();
        return x;
    }

    //peek 
    int peek(){
        exchange();
        return stack_out.top();
    }

    //empty
    bool isEmpty(){
        return stack_in.empty() && stack_out.empty();
    }


private:
    //两个栈，一个用于入队，一个用于出队
    stack<int, deque<int>> stack_in;
    stack<int, deque<int>> stack_out;
    //exchange,将stack_in中的元素转移到stack_out中
    void exchange(){
        if(stack_out.empty()){
            while(!stack_in.empty()){
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }
    }

};

};//namespace QFS

namespace SFQ{
class MyStack{
public:
    MyStack(){};
    MyStack(const MyStack& rhs){
        q = rhs.q;
    };
    MyStack& operator=(const MyStack& rhs){
        if(this == &rhs){return *this;}
        q= rhs.q;
        return *this;
    }
    ~MyStack(){};

    //push
    void push(int x){
        q.push(x);
        int n = q.size();
        while(n > 1){
            q.push(q.front());
            q.pop();
            n--;
        }
    }
    //pop
    int pop(){
        int x = q.front();
        q.pop();
        return x;
    }
    //top
    int top(){
        return q.front();
    }
    //empty
    bool empty(){
        return q.empty();
    }

private:
    //一个队列
    queue<int, deque<int>> q;
};
};//namespace SFQ

int main(int argc, char * argv[]){
    cout << "queue from stack" << endl;

    QFS::MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.pop() << endl;
    cout << q.peek() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.isEmpty() << endl;

    cout << "stack from queue" << endl;
    SFQ::MyStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.pop() << endl;
    cout << s.top() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.empty() << endl;
    return 0;
}