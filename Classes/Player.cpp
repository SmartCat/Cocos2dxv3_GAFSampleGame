#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"

USING_NS_CC;

Player::Player()
{
}

Player::~Player()
{
    CC_SAFE_RELEASE(m_model);
}

void Player::setGun(cocos2d::Node* gun)
{
    int n = m_model->objectIdByObjectName("GUN");
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
        m_model->setPosition(250, 500);
        m_model->playSequence("walk_right", true);
    }
    return ret;
}

void Player::shoot()
{

}

void Player::walkLeft()
{
    if (m_right)
    {
        m_right = false;
        m_model->playSequence("walk_left", true);
    }
    else
    {
        m_model->resumeAnimation();
    }
    m_moving = true;
}

void Player::walkRight()
{
    if (!m_right)
    {
        m_right = true;
        m_model->playSequence("walk_right", true);
    }
    else
    {
        m_model->resumeAnimation();
    }
    m_moving = true;
}

void Player::stop()
{
#if 0
    if (!m_moving)
        return;

    if (m_right)
    {
        m_model->playSequence("stand_right", true);
    }
    else
    {
        m_model->playSequence("stand_left", true);
    }
    m_moving = false;
#else
    m_model->pauseAnimation();
#endif
}
