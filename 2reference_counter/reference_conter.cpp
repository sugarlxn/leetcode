#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/// @brief RCL,Reference Counter Library
namespace RCL{
    ///base class,用于 reference counter object
    class RCObject{
    protected:
        ///@brief 默认构造函数
        RCObject():refCount(0),shareable(true){};
        ///@brief 拷贝构造函数
        RCObject(const RCObject& rhs):refCount(0),shareable(true){};
        ///@brief 赋值操作符
        RCObject& operator=(const RCObject& rhs){
            return *this;
        }
        ///@brief 析构函数，纯虚函数
        virtual ~RCObject() = 0;

    public:
        ///@brief 增加引用计数
        void addReference(){
            ++refCount;
        }
        ///@brief 减少引用计数
        void removeReference(){
            if(--refCount == 0){
                delete this;
            }
        }
        /// @brief 标记为不可共享
        void markUnshareable(){
            shareable = false;
        }
        ///@brief 判断是否可共享
        bool isShareable() const{
            return shareable;
        }
        ///@brief 判断是否已经被共享
        ///@param void
        ///@return bool
        bool isShared() const{
            return refCount > 1;
        }

    private:
        ///@brief 引用计数器
        int refCount;
        ///@brief 是否可共享
        bool shareable;
    };

    /// @brief template class 用于smart pointer-to-Tobjects;
    /// T 必须继承自RCObject
    template <class T>
    class RCPtr{
    public:
        ///@brief 构造函数
        RCPtr(T* realPtr = 0): pointee(realPtr){
            init();
        };
        ///@brief 拷贝构造函数
        RCPtr(const RCPtr& rhs): pointee(rhs.pointee){
            init();
        };
        ///@brief 析构函数
        ~RCPtr(){
            if(pointee){
                pointee->removeReference();
            }
        };
        ///@brief 赋值操作符
        RCPtr& operator=(const RCPtr& rhs){
            if(pointee != rhs.pointee){
                pointee->removeReference();
            }
            pointee = rhs.pointee;
            init();
            return *this;
        };
        ///@brief const 操作符->
        T* operator->() const{
            return pointee;
        };
        ///@brief const 操作符*
        T& operator*() const{
            return *pointee;
        };
    private:
        /// @brief 指向T的指针
        T* pointee;
        /// @brief 共同的初始化动作
        void init(){
            if(pointee == 0){
                return;
            }
            if(pointee->isShareable() == false){
                pointee = new T(*pointee);
            }
            pointee->addReference();
        };

    };

    /// @brief 应用性class,这是应用程序开发人员接触的层面
    class String{
    public:
        /// @brief 默认构造函数
        /// @param value 
        String(const char* initValue): value(new StringValue(initValue)){};
        /// @brief const 操作符[]
        /// @param index 
        /// @return  
        const char& operator[] (int index) const{
            return value->data[index];
        };
        /// @brief non-const 操作符[]
        /// @param index 
        /// @return 
        char& operator[] (int index){
            if(value->isShared()){
                value = new StringValue(value->data);
            }
            value->markUnshareable();
            return value->data[index];
        };
    private:
        /// @brief struct 用于保存字符串的值
        struct StringValue: public RCObject{
            char * data;
            /// @brief 默认构造函数
            /// @param initValue 
            StringValue(const char * initValue){
                init(initValue);
            };
            /// @brief 拷贝构造函数
            /// @param rhs 
            StringValue(const StringValue& rhs){
                init(rhs.data);
            };
            /// @brief 初始化函数
            /// @param initvalue 
            void init(const char* initvalue){
                data = new char[strlen(initvalue) + 1];
                strcpy(data, initvalue);
            };
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