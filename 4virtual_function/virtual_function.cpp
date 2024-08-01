#include <iostream>
#include <map>
#include <string>
#include <memory>
using namespace std;

/// @brief base class
class GameObject{
public:
    /// @brief 纯虚函数 collide
    virtual void collide(GameObject& otherObject) = 0;
};

class SpaceShip : public GameObject{
public:
    /// @brief 重写 collide 函数
    virtual void collide(GameObject& otherObject){
        // 找出调用的对象（一个函数）
        HitFunctionPtr hfp = lookup(otherObject);
        if(hfp){
            // 如果找到目标 就调用之
            (this->*hfp)(otherObject);
        }else{
            // 未知对象碰撞 抛出异常
            throw "Unknown object collision";
        }
    };

    /// @brief 碰撞处理函数
    virtual void hitSpaceShip(GameObject& spaceShip){
        // 将对象转换为SpaceShip
        SpaceShip& otherShip = dynamic_cast<SpaceShip&>(spaceShip);
        // 处理碰撞...
    };
    virtual void hitSpaceStation(GameObject& spaceStation){
        // 将对象转换为SpaceStation
        SpaceStation& station = dynamic_cast<SpaceStation&>(spaceStation);
        // 处理碰撞...
    };
    virtual void hitAsteroid(GameObject& asteroid){
        // 将对象转换为Asteroid
        Asteroid& theAsteroid = dynamic_cast<Asteroid&>(asteroid);
        // 处理碰撞...
    };


private:
    /// @brief 函数指针类型 HitFunctionPtr
    typedef void (SpaceShip::*HitFunctionPtr)(GameObject&);
    /// @brief 函数指针映射表 HitMap
    typedef map<string, HitFunctionPtr> HitMap;

    /// @brief 初始化函数指针映射表
    /// @return  
    static HitMap* initializeCollisionMap(){
        // 为每个可能的碰撞对象添加一个映射
        HitMap* phm = new HitMap;
        (*phm)["SpaceShip"] = &SpaceShip::hitSpaceShip;
        (*phm)["SpaceStation"] = &SpaceShip::hitSpaceStation;
        (*phm)["Asteroid"] = &SpaceShip::hitAsteroid;
    };

    /// @brief 函数指针查找函数
    static HitFunctionPtr lookup(const GameObject& whatWeHit){
        // 初始化函数指针映射表
        static shared_ptr<HitMap> collisionMap(initializeCollisionMap());
        
        //为whatWeHit 寻找碰撞处理函数，返回值是一个类似指针的对象，我们称之为iterator
        HitMap::iterator mapEntry = collisionMap->find(typeid(whatWeHit).name());
        // 这是标准的map行为
        if(mapEntry == collisionMap->end()) return nullptr;
        // 如果查找成功，此时mapEntry 指向一个完整的map条目，
        // 那是一个（string, HitFunctionPtr）的pair，我们需要第二个成分作为返回值
        return (*mapEntry).second;
    };
};

class SpaceStation : public GameObject{
public:
    /// @brief 重写 collide 函数
    virtual void collide(GameObject& otherObject){};
};

class Asteroid : public GameObject{
public:
    virtual void collide(GameObject& otherObject){};
};

int main(int argc, char * argv[]){
    cout << "hello world" << endl;

    return 0;
}
