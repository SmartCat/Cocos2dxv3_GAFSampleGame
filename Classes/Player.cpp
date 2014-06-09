#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFSprite.h"
#include "Gun.h"

USING_NS_CC;

Player::Player()
{
}

Player::~Player()
{
    CC_SAFE_RELEASE(m_model);
    CC_SAFE_RELEASE(m_gun);
}

void Player::setGun(Gun* gun)
{

    m_model->captureControlOverSubobjectNamed("ROBOT.GUN", kGAFAnimatedObjectControl_ApplyState);
    int n = m_model->objectIdByObjectName("ROBOT.GUN");
    auto obj = m_model->subObjectForInnerObjectId(n);
    obj->removeChild(m_gun, true);
    m_gun = gun;
    m_gun->retain();

    obj->setVisible(false);
    obj->addChild(m_gun, 1);

}

bool Player::init()
{
    bool ret = true;
    {
        m_model = GAFAnimatedObject::createAndRun("roboprogrm/roboprogrm.gaf", true);
        CCASSERT(m_model, "Error. Not found player model.");
        if (m_model == nullptr)
            return false;

        m_model->pause();
        addChild(m_model);
        m_model->retain();
        Size screen = Director::getInstance()->getVisibleSize();
        m_model->setPosition(100, 500);
        m_model->setScale(0.5);
        stop();
    }
    return ret;
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
