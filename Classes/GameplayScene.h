#pragma once 

#include "cocos2d.h"

class GameplayScene : public cocos2d::Scene
{
public:
    virtual bool init();  
    
    CREATE_FUNC(GameplayScene);

    void advanceToMenu(cocos2d::Ref* pSender);

    void fireButtonCallback(cocos2d::Ref* pSender);
    void leftButtonCallback(cocos2d::Ref* pSender);
    void rightButtonCallback(cocos2d::Ref* pSender);
};
