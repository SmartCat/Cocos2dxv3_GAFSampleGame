#include "Enemy.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFSprite.h"
#include "Player.h"

USING_NS_CC;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
    CC_SAFE_RELEASE(m_model);
}

bool Enemy::init()
{
    bool ret = true;
    {

        Director::getInstance()->getScheduler()->scheduleUpdateForTarget(this, 1, false);
        m_model = GAFAnimatedObject::createAndRun("robot_enemy/robot_enemy.gaf", true);
        CCASSERT(m_model, "Error. Not found player model.");
        if (m_model == nullptr)
            return false;

        m_model->pause();
        addChild(m_model);
        m_model->retain();
        Size screen = Director::getInstance()->getVisibleSize();
        m_model->setPosition(100, 500);
        m_model->setScale(1);
        walkLeft();


        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(Enemy::onCollided, this);
        _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
    }
    return ret;
}

void Enemy::update(float dt)
{
    do
    {
        Vec2 newPos = getPosition();
        if (m_state == EWalkLeft)
        {
            newPos += dt * m_speed * Vec2(-1, 0);
        }
        else if (m_state == EWalkRight)
        {
            newPos += dt * m_speed * Vec2(1, 0);
        }
        else
        {
            break;
        }
        setPosition(newPos);
    } while (0);

    Rect rect = m_model->realBoundingBoxForCurrentFrame();
    Vec3 scale, pos; Quaternion rot;
    getNodeToWorldTransform().decompose(&scale, &rot, &pos);

    Size boxSize(rect.size.width * scale.x, rect.size.height * scale.y);
    Vec2 boxPos(rect.origin.x * scale.x + boxSize.width / 2, rect.origin.y * scale.y + boxSize.height / 2);

    auto body = PhysicsBody::createBox(boxSize, PHYSICSBODY_MATERIAL_DEFAULT);
    body->setPositionOffset(boxPos);
    setPhysicsBody(body);
    body->setContactTestBitmask(0x2);

}

void Enemy::damage(float value)
{
    m_health -= value;
    if (m_health <= 0)
    {
        die();
    }
}

void Enemy::die()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    _eventDispatcher->dispatchCustomEvent("enemy_killed");
    setPhysicsBody(nullptr);
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    removeAllChildrenWithCleanup(true);
    removeFromParentAndCleanup(true);
}

void Enemy::walkLeft()
{
    if (m_state == EWalkLeft)
        return;

    m_model->playSequence("walk_left", true);
    m_state = EWalkLeft;
}

void Enemy::walkRight()
{
    if (m_state == EWalkRight)
        return;

    m_model->playSequence("walk_right", true);
    m_state = EWalkRight;
}

bool Enemy::onCollided(PhysicsContact& contact)
{
    if (getPhysicsBody() == nullptr)
        return false;

    if (contact.getShapeA()->getBody() == getPhysicsBody() || contact.getShapeB()->getBody() == getPhysicsBody())
    {
        Player* p = dynamic_cast<Player*>(contact.getShapeA()->getBody()->getNode());
        if (p)
        {
            die();
            return true;
        }
        p = dynamic_cast<Player*>(contact.getShapeB()->getBody()->getNode());
        if (p)
        {
            die();
            return true;
        }
        return true;
    }
    return false;
}
