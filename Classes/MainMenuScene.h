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

    void toggleEnemiesCount(cocos2d::Ref*);

private:
    int m_enemies;
    cocos2d::Label* m_label;
};
