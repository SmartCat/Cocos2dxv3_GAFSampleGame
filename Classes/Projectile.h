#pragma once 

#include "cocos2d.h"


class Projectile : public cocos2d::Node
{
public:
    Projectile();
    virtual ~Projectile();
    virtual bool init(cocos2d::Node* model, float damage, const cocos2d::Vec2& velocity, float delay);
    static Projectile* create(cocos2d::Node* model, float damage, const cocos2d::Vec2& velocity, float delay);

    void destroy();
    void update(float dt);
private:
    float m_damage = 0;
    cocos2d::Vec2  m_velocity = cocos2d::Vec2::ZERO;
    float m_ttl = 5;
    float m_delay;
};
