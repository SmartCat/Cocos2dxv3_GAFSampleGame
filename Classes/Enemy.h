#pragma once 

#include "cocos2d.h"

class GAFAnimatedObject;

class Enemy : public cocos2d::Node
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
    Enemy();
    virtual ~Enemy();
    virtual bool init();  
    
    CREATE_FUNC(Enemy);

    void update(float dt);
    void damage(float);

    void walkLeft();
    void walkRight();
    void stop();

    void die();
private:
    EState m_state = ENone;
    GAFAnimatedObject* m_model = nullptr;
    float m_speed = 200;
    float m_health = 1;
};
