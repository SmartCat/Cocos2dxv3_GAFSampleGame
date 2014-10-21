#include "Projectile.h"

#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "Enemy.h"

USING_NS_CC;
USING_NS_GAF;

Projectile::Projectile()
{}

Projectile::~Projectile()
{

}

bool Projectile::init(GAFAnimatedObject* model, float damage, float velocity, Node* parent)
{
    retain();
    m_damage = damage;
    
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);

    model->setFrame(0);

    Mat4 transform = parent->getNodeToWorldTransform();
    Vec3 position, scale;
    Quaternion rotation;
    transform.decompose(&scale, &rotation, &position);
    Rect rect = model->realBoundingBoxForCurrentFrame();
    Size boxSize(rect.size.width * scale.x, rect.size.height * scale.y);
    Vec2 boxPos(rect.origin.x * scale.x + boxSize.width / 2, rect.origin.y * scale.y + boxSize.height / 2);
    
    rotation.normalize();
    float angle = 2.0f * acos(rotation.w);

    Node* c = Node::create();
    //c->setNodeToParentTransform(transform);
    c->setScale(scale.x, scale.y);
    c->setPosition(position.x, position.y);
    c->setRotation(180 * angle / M_PI);
    c->addChild(model);
    addChild(c);

    m_velocity = velocity * Vec2::forAngle(angle);

    return true;
}

Projectile* Projectile::create(GAFAnimatedObject* model, float damage, float velocity, Node* parent)
{
    Projectile* ret = new Projectile();
    if (ret && ret->init(model, damage, velocity, parent))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void Projectile::destroy()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

    removeFromParentAndCleanup(true);
    //release();
}

void Projectile::update(float dt)
{
    m_ttl -= dt;
    if (m_ttl < 0)
    {
        destroy();
    }
    else
    {
        Vec2 newPos = getPosition();
        newPos += dt * m_velocity;
        setPosition(newPos);
    }
}

float const Projectile::getDamage() const
{
    return m_damage;
}