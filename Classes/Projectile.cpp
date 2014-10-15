#include "Projectile.h"

#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "Enemy.h"

USING_NS_CC;
using namespace gaf;

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
    auto body = PhysicsBody::createBox(boxSize, PHYSICSBODY_MATERIAL_DEFAULT);

    rotation.normalize();
    float angle = 2.0f * acos(rotation.w);

    Node* c = Node::create();
    //c->setNodeToParentTransform(transform);
    c->setScale(scale.x, scale.y);
    c->setPosition(position.x, position.y);
    c->setRotation(180 * angle / M_PI);
    c->addChild(model);
    addChild(c);

    body->setVelocity(velocity * Vec2::forAngle(angle));
    body->setPositionOffset(Vec2(position.x, position.y));
    body->setRotationOffset(180 * angle / M_PI);
    body->setContactTestBitmask(0x1);
    body->setCollisionBitmask(0x0);
    setPhysicsBody(body);


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Projectile::onCollided, this);
    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);

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

bool Projectile::onCollided(PhysicsContact& contact)
{
    if (getPhysicsBody() == nullptr)
        return false;

    if (contact.getShapeA()->getBody() == getPhysicsBody() || contact.getShapeB()->getBody() == getPhysicsBody())
    {
        Enemy* enemy = dynamic_cast<Enemy*>(contact.getShapeA()->getBody()->getNode());
        if (enemy)
        {
            enemy->damage(m_damage);
        }
        enemy = dynamic_cast<Enemy*>(contact.getShapeB()->getBody()->getNode());
        if (enemy)
        {
            enemy->damage(m_damage);
        }

        destroy();
        return true;
    }
    return false;
}

void Projectile::destroy()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

    removeAllChildrenWithCleanup(true);
    setPhysicsBody(nullptr);
    release();
}

void Projectile::update(float dt)
{
    m_ttl -= dt;
    if (m_ttl < 0)
    {
        destroy();
    }
}
