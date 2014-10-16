#pragma once 

#include "cocos2d.h"

namespace gaf
{
    class GAFAnimatedObject;
}
class Gun;

class Player : public cocos2d::Node
{
    enum EState
    {
        ENone = -1,
        EStandLeft,
        EStandRight,
        EWalkLeft,
        EWalkRight
    };

public:
    Player();
    virtual ~Player();
    virtual bool init();  
    
    CREATE_FUNC(Player);

    cocos2d::Size getSize() const;

    void setGun(Gun* gun);

    void update(float dt);
    void shoot();
    void walkLeft();
    void walkRight();
    void stop();

private:
    EState m_state = ENone;
    Gun*   m_gun = nullptr;
    gaf::GAFAnimatedObject* m_model = nullptr;
    cocos2d::Size m_size;
    float m_speed = 350;
};
