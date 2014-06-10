#pragma once 

#include "cocos2d.h"
#include "GAFDelegates.h"

class GAFAnimatedObject;

class Enemy : public cocos2d::Node, public GAFSequenceDelegate
{
    enum EState
    {
        ENone = -1,
        EWalkLeft,
        EWalkRight,
        EDieLeft,
        EDieRight
    };

public:
    Enemy();
    virtual ~Enemy();
    virtual bool init(GAFAnimatedObject* model);
    
    static Enemy* create(GAFAnimatedObject* model);

    void update(float dt);
    void damage(float);

    void walkLeft();
    void walkRight();

    void die();
    void onDieAnimationFinished();

    virtual void onFinishSequence(GAFAnimatedObject * object, const std::string& sequenceName) override;

    bool onCollided(cocos2d::PhysicsContact& contact);
private:
    EState m_state = ENone;
    GAFAnimatedObject* m_model = nullptr;
    float m_speed = 350;
    float m_health = 1;
    bool m_readyForCleanup = false;
};
