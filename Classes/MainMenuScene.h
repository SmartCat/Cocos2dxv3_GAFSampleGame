#pragma once 

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    MainMenuScene();
    ~MainMenuScene();

    virtual bool init();  
    
    CREATE_FUNC(MainMenuScene);

    void advanceToGame(cocos2d::Ref* pSender);
};
