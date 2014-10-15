#pragma once 

#include "cocos2d.h"

namespace gaf
{
    class GAFAnimatedObject;
}

class Projectile : public cocos2d::Node
{
public:
    Projectile();
    virtual ~Projectile();
    virtual bool init(gaf::GAFAnimatedObject* model, float damage, float velocity, cocos2d::Node* parent);
    static Projectile* create(gaf::GAFAnimatedObject* model, float damage, float velocity, cocos2d::Node* parent);

    bool onCollided(cocos2d::PhysicsContact& contact);
    void destroy();
    void update(float dt);
private:
    float m_damage = 0;
    cocos2d::Vec2  m_velocity = cocos2d::Vec2::ZERO;
    float m_ttl = 5;
};
