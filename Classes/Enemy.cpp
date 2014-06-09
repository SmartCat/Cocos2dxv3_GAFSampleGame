#include "Enemy.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFSprite.h"

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
    auto body = PhysicsBody::createBox(rect.size, PHYSICSBODY_MATERIAL_DEFAULT);
    body->setPositionOffset(rect.origin + rect.size / 2);
    setPhysicsBody(body);
    body->setContactTestBitmask(0x3);
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

void Enemy::stop()
{
    if (m_state == EStandLeft || m_state == EStandRight)
        return;

    if (m_state == EWalkRight)
    {
        m_model->playSequence("stand_right", true);
        m_state = EStandRight;
    }
    else if (m_state == EWalkLeft)
    {
        m_model->playSequence("stand_left", true);
        m_state = EStandLeft;
    }
    else
    {
        m_model->playSequence("stand_right", true);
        m_state = EStandRight;
    }
}
