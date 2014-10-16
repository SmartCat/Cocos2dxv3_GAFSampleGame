#include "Enemy.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFSprite.h"
#include "Player.h"

USING_NS_CC;
using namespace gaf;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
    CC_SAFE_RELEASE(m_model);
}

Enemy* Enemy::create(GAFAnimatedObject* model)
{
    Enemy* ret = new Enemy();
    if (ret && ret->init(model))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

cocos2d::Size Enemy::getSize() const
{
    return m_size;
}

bool Enemy::init(GAFAnimatedObject* model)
{
    bool ret = true;
    {

        Director::getInstance()->getScheduler()->scheduleUpdateForTarget(this, 1, false);
        m_model = model;
        CCASSERT(m_model, "Error. Not found player model.");
        if (m_model == nullptr)
            return false;

        m_model->pause();
        addChild(m_model);
        m_model->retain();
        m_model->setPosition(100, 500);
        m_model->setScale(1);

        m_size = m_model->realBoundingBoxForCurrentFrame().size;

        walkLeft();
    }
    return ret;
}

void Enemy::update(float dt)
{
    if (m_readyForCleanup)
    {
        onDieAnimationFinished();
        return;
    }

    if (m_health <= 0)
    {
        return;
    }

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

    m_size = Size(rect.size.width * scale.x, rect.size.height * scale.y);

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
    m_model->setSequenceDelegate(this);
    if (m_state == EWalkLeft)
    {
        m_state = EDieLeft;
        m_model->playSequence("die_left", false);
    }
    else if (m_state == EWalkRight)
    {
        m_state = EDieRight;
        m_model->playSequence("die_right", false);
    }
}

bool Enemy::isDying() const
{
    return m_state == EDieLeft || m_state == EDieRight;
}

void Enemy::onDieAnimationFinished()
{
    _eventDispatcher->dispatchCustomEvent("enemy_killed");
    m_model->setSequenceDelegate(nullptr);
    _eventDispatcher->removeEventListenersForTarget(this);
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    //removeAllChildrenWithCleanup(true);
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

void Enemy::onFinishSequence(GAFAnimatedObject * object, const std::string& sequenceName)
{
    if (sequenceName == "die_right" && m_state == EDieRight)
    {
        m_readyForCleanup = true;
    }
    if (sequenceName == "die_left" && m_state == EDieLeft)
    {
        m_readyForCleanup = true;
    }
}
