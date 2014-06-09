#include "Projectile.h"

USING_NS_CC;

Projectile::Projectile()
{}

Projectile::~Projectile()
{

}

bool Projectile::init(cocos2d::Node* model, float damage, const Vec2& velocity)
{
    retain();
    addChild(model);
    m_damage = damage;
    m_velocity = velocity;
    
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);

    return true;
}

Projectile* Projectile::create(cocos2d::Node* model, float damage, const Vec2& velocity)
{
    Projectile* ret = new Projectile();
    if (ret && ret->init(model, damage, velocity))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void Projectile::destroy()
{
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    removeAllChildrenWithCleanup(true);
    release();
}

void Projectile::update(float dt)
{
    Vec2 pos = getPosition();
    pos += m_velocity * dt;
    setPosition(pos);
    m_ttl -= dt;
    if (m_ttl < 0)
    {
        destroy();
    }
}
