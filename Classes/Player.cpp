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
        m_model->gotoAndStop(0);
    }
    return ret;
}

void Player::shoot()
{

}

void Player::walkLeft()
{
    m_moving = true;
    m_right = false;
    m_model->setScale(-1, 1);
    m_model->setPosition(750, 500);
    m_model->resumeAnimation();
}

void Player::walkRight()
{
    m_moving = true;
    m_right = false;
    m_model->setScale(1, 1);
    m_model->setPosition(250, 500);
    m_model->resumeAnimation();
}

void Player::stop()
{
    m_moving = false;
    m_model->pauseAnimation();
}
