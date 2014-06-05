#pragma once 

#include "cocos2d.h"

class Gun : public cocos2d::Node
{
public:
    Gun();
    virtual ~Gun();
    virtual bool init();  
    
    CREATE_FUNC(Gun);

    void shoot();

private:
    float m_reloadTime = 0;
    float m_bulletSpeed = 1;
    float m_bulletDamage = 1;
    cocos2d::String m_bullet;
};
