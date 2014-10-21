#pragma once 

#include "cocos2d.h"

namespace gaf
{
    class GAFAsset;
}

class Player;
class Projectile;

class GameplayScene : public cocos2d::Scene
{
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

    void spawnEnemy();
    void addProjectile(Projectile* p);
    void onEnemyKilled(void* data);
private:
    void checkCollisionsSimple();
    float checkForProjectilesDamage(const float enemyX, const float epsDistance);

    Player* m_player;
    int m_gunId = 0;
    cocos2d::Node* m_level;
    gaf::GAFAsset* m_enemyAsset;
    int m_robots;

    //constants
    enum CHILD_TAGS
    {
        TAG_LEVEL = 1,
        TAG_PLAYER,
        TAG_ENEMY,
        TAG_PROJECTILE
    };
};
