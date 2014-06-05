#pragma once 

#include "cocos2d.h"

class Player;

class GameplayScene : public cocos2d::Scene
{
public:
    virtual bool init();  
    
    CREATE_FUNC(GameplayScene);

    void advanceToMenu(cocos2d::Ref* pSender);

    void fireButtonCallback(cocos2d::Ref* pSender);
    void leftButtonCallback(cocos2d::Ref* pSender, bool pressed);
    void rightButtonCallback(cocos2d::Ref* pSender, bool pressed);

private:
    Player* m_player;
};
