#pragma once 

#include "cocos2d.h"

namespace gaf
{
    class GAFAsset;
}

class Player;
class Projectile;
class SpeechBubble;

class GameplayScene : public cocos2d::Scene
{
    //constants
    enum CHILD_TAGS
    {
        TAG_LEVEL = 1,
        TAG_PLAYER,
        TAG_ENEMY,
        TAG_PROJECTILE
    };

    enum BUTTONS
    {
        BTN_MENU = 0,
        BTN_ATLASES,
        BTN_MOVE,
        BTN_GUN,
        BTN_FIRE,

        BTN_COUNT
    };

public:
    GameplayScene();
    ~GameplayScene();
    virtual bool init(int enemies);
    
    static GameplayScene* create(int enemies);

    void update(float dt);

    void advanceToMenu(cocos2d::Ref* pSender);
    void showAtlases(cocos2d::Ref* pSender);

    void fireButtonCallback(cocos2d::Ref* pSender);
    void leftButtonCallback(cocos2d::Ref* pSender, bool pressed);
    void rightButtonCallback(cocos2d::Ref* pSender, bool pressed);
    void toggleGunButtonCallback(cocos2d::Ref* pSender);

    void disableHud();
    void enableWeaponSwitch();
    void enableAll();

    void spawnEnemy();
    void addProjectile(Projectile* p);
    void onEnemyKilled(void* data);
private:
    void checkCollisionsSimple();
    float checkForProjectilesDamage(const float enemyX, const float epsDistance);

    bool m_isFirstUpdate;

    Player* m_player;
    int m_gunId = 0;
    cocos2d::Node* m_level;
    gaf::GAFAsset* m_enemyAsset;
    int m_robots;

    SpeechBubble* m_speechBubble;

    cocos2d::Menu* m_buttons[BTN_COUNT];

};
