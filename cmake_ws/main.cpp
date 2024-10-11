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


/// @brief 代码随想录的KMP写法
class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = -1;
        next[0] = j;
        for(int i = 1; i < s.size(); i++) { // 注意i从1开始
            while (j >= 0 && s[i] != s[j + 1]) { // 前后缀不相同了
                j = next[j]; // 向前回退
            }
            if (s[i] == s[j + 1]) { // 找到相同的前后缀
                j++;
            }
            next[i] = j; // 将j（前缀的长度）赋给next[i]
        }
    }
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }
		vector<int> next(needle.size());
		getNext(&next[0], needle);
        cout << "next[]:" << endl;
        for(int i=0; i<needle.size(); i++){
            cout << next[i] << " ";
        }
        cout << endl;
        int j = -1; // // 因为next数组里记录的起始位置为-1
        for (int i = 0; i < haystack.size(); i++) { // 注意i就从0开始
            while(j >= 0 && haystack[i] != needle[j + 1]) { // 不匹配
                j = next[j]; // j 寻找之前匹配的位置
            }
            if (haystack[i] == needle[j + 1]) { // 匹配，j和i同时向后移动
                j++; // i的增加在for循环里
            }
            if (j == (needle.size() - 1) ) { // 文本串s里出现了模式串t
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

/// @brief 计算next数组
/// @param next 
/// @param s 
void mygetNext(vector<int>& next, string& s){
    int j = 0;
    next[0] = 0;
    for(int i = 1; i < s.size(); i++){
        while(j > 0 && s[i] != s[j])
        {
            //回退
            j = next[j-1];
        }
        if(s[i] == s[j]){
            j++;
        }
        next[i] = j;
    }
}

int strStr(const string& haystack,const string& needle){
    if(needle.size() == 0){
        return 0;
    }
    vector<int> next(needle.size(), 0);
    mygetNext(next, const_cast<string&>(needle));
    cout << "next[]: ";
    for(int i=0; i<needle.size(); i++){
        cout << next[i] << " ";
    }
    cout << endl;
    int j = 0;
    for(int i = 0; i < haystack.size(); i++){
        while (j>0 && haystack[i] != needle[j])
        {   
            //回退
            j = next[j-1];
        }
        if(haystack[i] == needle[j]){
            j++;
        }
        if(j == needle.size()){
            return (i - needle.size() + 1);
        }
        
    }
    return -1;
}

class B{
public:
    explicit B(int num):num(num){}
    int get(){return num;}

private:
    int num;
    static const int NUMTrun = 5;
    int array[NUMTrun];
};

void dosomething(B b){
   cout << b.get() << endl;
}

class Data{
public:
    Data(int time = 0):time(time){};
    Data(const Data& rhs){
        this->time = rhs.time;
    };
    Data& operator=(const Data& rhs){
        if(this == &rhs){return *this;} //自赋值
        this->time = rhs.time; //复制rhs的数据
        return *this;

    };
    ~Data(){};

private:
    int time;
};

class Customer{
public:
    Customer(std::string name="hello", Data lastTransaction=Data()): name(name), lastTransaction(lastTransaction){}; //默认构造函数
    Customer(const Customer& rhs): name(rhs.name), lastTransaction(rhs.lastTransaction){};
    Customer& operator=(const Customer& rhs){
        if(this == &rhs){return *this;} //阻止自我赋值
        name = rhs.name;
        lastTransaction = rhs.lastTransaction;
        return *this;
    };
    ~Customer(){};
private:
    std::string name;
    Data lastTransaction; //数据成员
};

class PriorityCustomer: public Customer{ //一个derived class
public:
    //默认构造函数
    PriorityCustomer(std::string name="hello", Data lastTransaction = Data(), int priority = 0): 
    Customer(name, lastTransaction),  //调用base class的构造函数
    priority(priority){};
    //拷贝构造函数, 主意不能局部赋值
    PriorityCustomer(const PriorityCustomer& rhs): 
    Customer(rhs), //调用base class的copy构造函数
    priority(rhs.priority){};
    //operator=
    PriorityCustomer& operator=(const PriorityCustomer& rhs){
        if(this == &rhs){return *this;} //阻止自我赋值
        //调用base class的operator=, 注意不能局部赋值
        Customer::operator=(rhs); 
        priority = rhs.priority;
        return *this;
    };
    ~PriorityCustomer(){};
private:
    int priority;
};

class Window{
public:
    Window(int num, string name):num(num),name(name){};
    Window(const Window& rhs):num(rhs.num),name(rhs.name){};
    ~Window(){};
    Window& operator=(const Window& rhs){
        if(this == &rhs){return *this;}
        num = rhs.num;
        name = rhs.name;
        return *this;
    };
    int getNum() const{return num;}
    string getName() const{return name;}
    virtual void print_window() const{
        cout << "Window: " << num << " " << name << endl;
    }

private:
    int num;
    string name;
};

class SpecialWindow: public Window{
public:
    SpecialWindow(int num, string name, int special_num):Window(num, name), special_num(special_num){};
    SpecialWindow(const SpecialWindow& rhs):Window(rhs), special_num(rhs.special_num){};
    ~SpecialWindow(){};
    SpecialWindow& operator=(const SpecialWindow& rhs){
        if(this == &rhs){return *this;}
        Window::operator=(rhs);
        special_num = rhs.special_num;
        return *this;
    };
    virtual void print_window() const{
        cout << "SpecialWindow: " << Window::getName() << " " << Window::getNum() << " " << special_num << endl;
    }
private:
    int special_num;
};

void print_window(Window window){
    window.print_window();
}
void print_window_by_reference(const Window& window){
    window.print_window();
}

class Rational{
public:
    Rational(int numerator = 0, int demoninator = 1):n(numerator),d(demoninator){};
    //这里写的操作符重载函数，返回值是const Rational&，会改变原对象的值
    const Rational& operator*=(const Rational& rhs){
        this->n = this->n * rhs.n;
        this->d = this->d * rhs.d;
        return *this;
    }
    //这里写的操作符重载函数, 返回一个新的对象，不会改变原对象的值
    const Rational operator*(const Rational& rhs){
        return Rational(this->n * rhs.n, this->d * rhs.d);
    }
private:
    int n,d;
    //声明为友元函数，返回值是const Rational，不会改变原对象的值，返回一个新的对象存储运算结果
    friend  const Rational operator*(const Rational& lhs, const Rational& rhs);
};

inline const Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}

namespace my_wideget{
class Widget_swap{
public:
    Widget_swap(int a = 0, int b = 0):a(a),b(b){};
    Widget_swap(const Widget_swap& rhs):a(rhs.a),b(rhs.b){};
    ~Widget_swap(){};
    Widget_swap& operator=(const Widget_swap& rhs){
        if(this == &rhs){return *this;}
        a = rhs.a;
        b = rhs.b;
        return *this;
    };

    //定制化的swap函数 member function
    void swap(Widget_swap& other){
        cout << "Widget_swap::swap member function" << endl;
        Widget_swap temp(other);
        other.a = this->a;
        other.b = this->b;
        this->a = temp.a;
        this->b = temp.b;
    }

private:
    int a;
    int b;
};

//定制化的swap函数 non-member function
void swap(Widget_swap& a, Widget_swap& b){
    cout << "swap non-member function" << endl;
    a.swap(b);
}

}//namespace my_wideget

// 特例化std::swap  for Widget_swap
namespace std{
    template<>
    void swap<my_wideget::Widget_swap>(my_wideget::Widget_swap& a, my_wideget::Widget_swap& b){
        cout << "std::swap" << endl;
        a.swap(b);
    }

}//namespace std

//如何使用swap
template <typename T>
void dosomething(T& a, T& b){
    using std::swap;
    swap(a,b);
}

//functor
template <class T>
struct plus2{
    void operator()(T& x)const{
        std::cout << x << " ";
    }
};

//递归打印可变参数列表
void log(){
    cout << endl;
}   
//variadic template
template<typename T, typename... Args>
void log(T firstArg, Args... args){
    cout << firstArg << endl;
    log(args...);
}

int main(int argc, char *argv[])
{

    string s1 = "aabaabaaf";
    string s2 = "aabaaf";
    Solution solution;
    cout << solution.strStr(s1, s2) << endl;

    string s = "aabaaf";
    vector<int> next(s.size(), 0);
    mygetNext(next, s);
    cout << "next[]: ";
    for(int i=0; i<s.size(); i++){
        cout << next[i] << " ";
    }
    cout << endl;

    cout << strStr(s1, s2) << endl;

    
    B b(1);
    dosomething(b);
    dosomething(B(1));

    //创建一个special window    
    SpecialWindow special_window(1, "special_window", 2);
    //如果使用pass by value,导致部分赋值，数据切割 会调用基类的print_window, 
    print_window(special_window);
    //如果使用pass by reference, 会调用派生类的print_window
    print_window_by_reference(special_window);

    //创建widget_swap
    my_wideget::Widget_swap widget1(1,2);
    my_wideget::Widget_swap widget2(3,4);
    dosomething(widget1, widget2);

    cout << "================" << endl;
    int ia[] = {1,2,3,4,5};
    vector<int> ivec(ia, ia+5); //前闭后开，ivec包含5个元素
    for_each(ivec.begin(), ivec.end(), plus2<int>());
    cout << endl;
    cout << "================" << endl;
    log("a", 1, 2.0, 3.0f, "hello");

    return 0;
}
