#pragma once 

#include "cocos2d.h"
#include "GAFDelegates.h"

namespace gaf
{
    class GAFAnimatedObject;
}

class Enemy : public cocos2d::Node, public gaf::GAFSequenceDelegate
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
    virtual bool init(gaf::GAFAnimatedObject* model);
    
    static Enemy* create(gaf::GAFAnimatedObject* model);

    void update(float dt);
    void damage(float);

    void walkLeft();
    void walkRight();

    void die();
    void onDieAnimationFinished();

    virtual void onFinishSequence(gaf::GAFAnimatedObject * object, const std::string& sequenceName) override;

    bool onCollided(cocos2d::PhysicsContact& contact);
private:
    EState m_state = ENone;
    gaf::GAFAnimatedObject* m_model = nullptr;
    float m_speed = 400;
    float m_health = 2;
    bool m_readyForCleanup = false;
};
