#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFSprite.h"
#include "Gun.h"

USING_NS_CC;
using namespace gaf;

Player::Player()
{
}

Player::~Player()
{
    CC_SAFE_RELEASE(m_model);
    CC_SAFE_RELEASE(m_gun);
}

cocos2d::Size Player::getSize() const
{
    return m_size;
}

void Player::setGun(Gun* gun)
{

    m_model->captureControlOverSubobjectNamed("ROBOT.GUN", kGAFAnimatedObjectControl_ApplyState);
    int n = m_model->objectIdByObjectName("ROBOT.GUN");
    auto obj = m_model->subObjectForInnerObjectId(n);
    obj->removeChild(m_gun, true);
    CC_SAFE_RELEASE(m_gun);
    m_gun = gun;
    m_gun->retain();

    obj->setVisible(false);
    obj->addChild(m_gun, 1);

}

bool Player::init()
{
    bool ret = true;
    {
        Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);

        m_model = GAFAnimatedObject::createAndRun("roboprogrm/roboprogrm.gaf", true);
        m_model->setFps(m_model->getFps() * 1.4);
        CCASSERT(m_model, "Error. Not found player model.");
        if (m_model == nullptr)
            return false;

        m_model->pause();
        addChild(m_model);
        m_model->retain();
        m_model->setPosition(100, 500);
        m_model->setScale(1);
        stop();        
    }
    return ret;
}

void Player::update(float dt)
{
    Rect rect = m_model->realBoundingBoxForCurrentFrame();
    Vec3 scale, pos; Quaternion rot;
    getNodeToWorldTransform().decompose(&scale, &rot, &pos);

    m_size = Size(rect.size.width * scale.x, rect.size.height * scale.y);

    do
    {
        Node* level = Director::getInstance()->getRunningScene()->getChildByTag(1);
        if (level == nullptr)
        {
            break;
        }
        Vec2 position = level->getPosition();
        if (m_state == EWalkLeft)
        {
            position += dt * m_speed * Vec2(scale.x, 0);
        }
        else if (m_state == EWalkRight)
        {
            position += dt * m_speed * Vec2(-scale.x, 0);
        }
        else
        {
            break;
        }
        level->setPosition(position);

    } while (0);
}

void Player::shoot()
{
    if (m_gun)
    {
        m_gun->shoot();
    }
}

void Player::walkLeft()
{
    if (m_state == EWalkLeft)
        return;

    m_model->playSequence("walk_left", true);
    m_state = EWalkLeft;
}

void Player::walkRight()
{
    if (m_state == EWalkRight)
        return;

    m_model->playSequence("walk_right", true);
    m_state = EWalkRight;
}

void Player::stop()
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
