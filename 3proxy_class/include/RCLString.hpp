#pragma once

/// \file RCLString.hpp
/// \brief This file contains the definition of the RCL_string class.
/// \author Rudy^
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#define USE_ProxyChar 1
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

    ///@brief 纯虚析构函数的实现
    RCObject::~RCObject(){};

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

#if !USE_ProxyChar
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
#else
        class CharProxy{
        public:
            /// @brief 构造函数
            /// @param str 
            /// @param index 
            CharProxy(String& str, int index): theString(str), charIndex(index){};
            /// @brief 操作符重载，左值运用
            /// @param rhs 
            /// @return 
            CharProxy& operator=(const CharProxy& rhs){};
            /// @brief 操作符重载，右值运用
            /// @param c 
            /// @return 
            CharProxy& operator=(char c){};

            //NOTE {这个函数以by value的方式返回一个字符，并且由于C++限制只能在右值情景下使用这样的by value返回方式，
            // 所以这个函数只能够用于右值合法之处}
            /// @brief 隐式转换操作 右值运用
            /// @return char 
            operator char() const{
                return theString.value->data[charIndex];
            }

            //NOTE {此函数需要处理String的private data member value, 这就是为什么稍后出现的String Class定义中
            // 将CharProxy声明为friend的原因}
            /// @brief 第一个assignment操作符 ，左值运用, 即该proxy对象将被作为赋值动作的目标
            CharProxy& operator=(const CharProxy& rhs){
                //如果字符串是共享的，那么我们需要创建一个新的字符串
                //将实值复制一份，供本字符串单独使用
                if(theString.value->isShared()){
                    theString.value = new StringValue(theString.value->data);
                }
                //进行赋值动作,将右边的字符赋值给左边的字符
                theString.value->data[charIndex] = rhs.theString.value->data[rhs.charIndex];
                return *this;
            }

            /// @brief 第二个assignment操作符，左值运用，即该proxy对象将被作为赋值动作的目标
            /// @param c
            CharProxy& operator=(char c){
                if(theString.value->isShared()){
                    theString.value = new StringValue(theString.value->data);
                }
                theString.value->data[charIndex] = c;
                return *this;
            }
            /// @brief 取地址操作符重载 non-const
            /// @return 
            char * operator&(){
                //确定字符串是否是共享的，如果是，我们需要创建一个新的字符串，作为本字符串的副本
                if(theString.value->isShared()){
                    theString.value = new StringValue(theString.value->data);
                }
                //我们不知道client 会将本函数返回的指针保存多久，所以“目标字符”
                //不能够被共享
                theString.value->markUnshareable();
                //返回字符的地址
                return &(theString.value->data[charIndex]);
            };
            /// @brief 取地址操作符重载 const
            const char * operator&() const{
                return &(theString.value->data[charIndex]);
            };

        private:
            /// @brief 引用String对象,这个proxy所附属的字符串
            String& theString;
            /// @brief 字符的索引，这个proxy所代表的字符串字符的索引
            int charIndex;
        };

        friend class CharProxy;
        //NOTE 为什么const版本的operator[] 需要将*this转换为const_cast<String&>类型，而non-const版本不需要{
        //请注意，当 const operator[] 产生一个 CharProxy 对象准备返回时，作用于 ＊this 身上的const_cast（见条款 2）。
        //为了满足 CharProxy constructor的限制，那是必要的，因为 CharProxy constructor 只接受 non-const String。}
        /// @brief caonst 操作符[]
        /// @param index 
        /// @return 
        const String::CharProxy operator[](int index) const{
            return CharProxy(const_cast<String&>(*this), index);
        };
        /// @brief non-const 操作符[]
        /// @param index
        String::CharProxy operator[](int index){
            return CharProxy(*this, index);
        };
#endif
    private:

        /// @brief 声明一个struct 用于保存字符串的值
        struct StringValue: public RCObject{
            /// @brief 字符串数据
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

        /// @brief 指向StringValue的智能指针，类型为struct StringVlaue的带Reference counter的智能指针
        RCPtr<StringValue> value;

    };

}
