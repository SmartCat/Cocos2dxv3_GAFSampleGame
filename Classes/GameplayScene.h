#pragma once 

#include "cocos2d.h"

class GAFAsset;
class Player;

class GameplayScene : public cocos2d::Scene
{
public:
    virtual bool init();  
    
    // Creates with physics
    static GameplayScene* create();

    void advanceToMenu(cocos2d::Ref* pSender);

    void fireButtonCallback(cocos2d::Ref* pSender);
    void leftButtonCallback(cocos2d::Ref* pSender, bool pressed);
    void rightButtonCallback(cocos2d::Ref* pSender, bool pressed);
    void toggleGunButtonCallback(cocos2d::Ref* pSender);

    void spawnEnemy();
    void onEnemyKilled(void* data);
private:
    Player* m_player;
    int m_gunId = 0;
    cocos2d::Node* m_level;
    GAFAsset* m_enemyAsset;
};
