#include <iostream>
#include <string>
using namespace std;

class Person{
public:
    Person(int age, string name){
        this->age = age;
        this->name = name;
    }
    ~Person(){};
    void show_info(){
        cout<< this->age << " " << this->name << endl;
    }

private:
    int age;
    string name;
};

/// @brief 智能指针
/// @tparam T 
template <class T>
class SmartPointer{
public:
    SmartPointer(T * pointer=nullptr){
        this->pointer = pointer;
    }
    ~SmartPointer(){
        if(this->pointer != nullptr){
            delete this->pointer;
        }
    }
    T* operator->() const{
        return this->pointer;
    }
    T& operator*() const{
        return *(this->pointer);
    }

private:
    T * pointer;
};

int main(int * argc, char * argv[]){

    std::cout << "holle word!!" << std::endl;

    Person * person = new Person(12,"lxn");
    SmartPointer<Person>  s_p = SmartPointer<Person>(person);
    s_p->show_info();
    //(s_P->)->show_info(); //错误
    (*s_p).show_info();
    //(s_p*).show_info(); //错误

    return 0;
}

