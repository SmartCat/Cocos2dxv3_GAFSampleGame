#pragma once 

#include "cocos2d.h"

class GAFAnimatedObject;
class Gun;

class Player : public cocos2d::Node
{
    enum EState
    {
        ENone = -1,
        EStandLeft,
        EStandRight,
        EWalkLeft,
        EWalkRight
    };

public:
    Player();
    virtual ~Player();
    virtual bool init();  
    
    CREATE_FUNC(Player);

    void setGun(Gun* gun);

    void update(float dt);
    void shoot();
    void walkLeft();
    void walkRight();
    void stop();

private:
    EState m_state = ENone;
    Gun*   m_gun = nullptr;
    GAFAnimatedObject* m_model = nullptr;
    float m_speed = 350;
};
