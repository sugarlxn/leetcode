#pragma once
///@brief auto_ptr class
namespace SmartPtr{
template <class T>
class auto_ptr{
public:
    /// @brief 默认构造函数
    /// @param p 
    explicit auto_ptr(T* p=0): pointee(p){};

    /// @brief 拷贝构造函数
    /// @tparam U 
    /// @param rhs 
    template <class U>
    auto_ptr(auto_ptr<U>& rhs): pointee(rhs.release()){};

    /// @brief 析构函数
    ~auto_ptr(){
        delete pointee;
    };

    /// @brief 赋值操作符
    /// @tparam U 
    /// @param rhs 
    /// @return 
    template <class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs){
        if(this != &rhs){
            reset(rhs.release());
        }
        return *this;
    };

    /// @brief 操作符*
    /// @return 
    T& operator*() const{
        return *pointee;
    };

    /// @brief 操作符->
    /// @return
    T* operator->() const{
        return pointee;
    };

    /// @brief 返回dump pointer
    /// @return 
    T* get() const{
        return pointee;
    };

    /// @brief 撤回dump pointer的拥有权，并返回其值
    /// @return 
    T* release(){
        T* oldPointee = pointee;
        pointee = 0;
        return oldPointee;
    };

    /// @brief 将拥有的指针删除，并承担p的拥有权
    /// @param p 
    void reset(T* p=0){
        if(pointee != p){
            delete pointee;
            pointee = p;
        }
    };


private:
    /// @brief dump pointer
    T* pointee;
    
    /// @brief 让所有的auto_ptr类模板实例都成为友元
    /// @tparam U 
    // BUG{ error: specialization of ‘template<class T> class SmartPtr::auto_ptr’ must appear at namespace scope}
    // template <class U>
    // friend class auto_ptr<U>;

};

};//namespace SmartPtr
