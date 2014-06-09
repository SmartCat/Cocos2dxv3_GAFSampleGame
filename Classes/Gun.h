#pragma once 
#include "GAFPrecompiled.h"
#include "GAFDelegates.h"
#include "cocos2d.h"

class GAFAnimatedObject;
class GAFAsset;

class Gun : public cocos2d::Node, public GAFSequenceDelegate
{
public:
    Gun();
    virtual ~Gun();
    virtual bool init(const std::string& name);
    static Gun* create(const std::string& name);

    void shoot();
    void update(float dt);
    virtual void onFinishSequence(GAFAnimatedObject * object, const std::string& sequenceName);
private:
    void emitProjectile();
    float m_reloadTime = 0;
    float m_projectileSpeed = 1;
    float m_shootDelay = 1;
    float m_projectileDamage = 1;
    cocos2d::Vec2 m_projectileOffset = cocos2d::Vec2::ZERO;
    GAFAnimatedObject* m_model = nullptr;
    GAFAsset* m_projectile = nullptr;

    float m_cooldown = 0;
    float m_loadingTime = 0;
    bool m_shooting = false;
};
