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

    cocos2d::Size getSize() const;

    void update(float dt);
    void damage(float);

    void walkLeft();
    void walkRight();

    void die();
    bool isDying() const;
    void onDieAnimationFinished();

    virtual void onFinishSequence(gaf::GAFAnimatedObject * object, const std::string& sequenceName) override;
private:
    EState m_state = ENone;
    gaf::GAFAnimatedObject* m_model = nullptr;
    cocos2d::Size m_size;
    float m_speed = 400;
    float m_health = 2;
    bool m_readyForCleanup = false;
};
