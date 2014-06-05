#pragma once 

#include "cocos2d.h"

class GAFAnimatedObject;

class Player : public cocos2d::Node
{
public:
    Player();
    virtual ~Player();
    virtual bool init();  
    
    CREATE_FUNC(Player);

    void setGun(cocos2d::Node* gun);

    void shoot();
    void walkLeft();
    void walkRight();
    void stop();

private:
    bool m_moving = false;
    bool m_right = true;
    GAFAnimatedObject* m_model = nullptr;
    GAFAnimatedObject* m_gun = nullptr;
};
