#include <iostream>
#include <string>
using namespace std;

/// @brief RCL,Reference Counter Library
namespace RCL{
    ///base class,用于 reference counter object
    class RCObject{
    protected:
        ///默认构造函数
        RCObject():refCount(0),shareable(true){};
        ///拷贝构造函数
        RCObject(const RCObject& rhs):refCount(0),shareable(true){};
        ///赋值操作符
        RCObject& operator=(const RCObject& rhs){
            return *this;
        }
        ///析构函数，纯虚函数
        virtual ~RCObject() = 0;

    public:
        ///增加引用计数
        void addReference(){
            ++refCount;
        }
        ///减少引用计数
        void removeReference(){
            if(--refCount == 0){
                delete this;
            }
        }
        ///返回是否可共享
        bool isShareable() const{
            return shareable;
        }
        ///返回是否已经被共享
        bool isShared() const{
            return refCount > 1;
        }

    private:
        ///引用计数器
        int refCount;
        ///是否可共享
        bool shareable;
    };

    /// @brief template class 用于smart pointer-to-Tobjects;
    /// T 必须继承自RCObject
    template <class T>
    class RCPtr{
    public:
        ///构造函数
        RCPtr(T* realPtr = 0){};
        ///拷贝构造函数
        RCPtr(const RCPtr& rhs){};
        ///析构函数
        ~RCPtr(){};
        ///赋值操作符
        RCPtr& operator=(const RCPtr& rhs){};
        ///重载操作符
        T* operator->() const{};
        T& operator*() const{};
    private:
        /// @brief 指向T的指针
        T* pointee;
        /// @brief 共同的初始化动作
        void init(){};

    };
    /// @brief 应用性class,这是应用程序开发人员接触的层面
    class String{
    public:
        /// @brief 默认构造函数
        /// @param value 
        String(const char *value = ""){};
        /// @brief const 操作符[]
        /// @param index 
        /// @return  
        const char& operator[] (int index) const{};
        /// @brief non-const 操作符[]
        /// @param index 
        /// @return 
        char& operator[] (int index){};
    private:
        /// @brief struct 用于保存字符串的值
        struct StringValue: public RCObject{
            char * data;
            /// @brief 默认构造函数
            /// @param initValue 
            StringValue(const char * initValue){};
            /// @brief 拷贝构造函数
            /// @param rhs 
            StringValue(const StringValue& rhs){};
            /// @brief 初始化函数
            /// @param initvalue 
            void init(const char* initvalue){};
            /// @brief 析构函数
            ~StringValue(){
                delete [] data;
            }
        };
        /// @brief 指向StringValue的智能指针
        RCPtr<StringValue> value;

    };

}

int main(int argc, char * argv[]){

    string s1 = string("Hello");
    string s2 = s1;
    char * p = &s1[1];
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "p:" << *p << endl;

    *p = 'a';

    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "p:" << *p << endl;
    
    return 0;
}