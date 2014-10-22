#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "CCDoubleTriggerMenuItemLabel.h"
#include "CCDoubleTriggerMenuItemSprite.h"
#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "Gun.h"
#include "Enemy.h"
#include "Background.h"
#include "GAFAsset.h"
#include "Projectile.h"
#include "AtlasesScene.h"
#include "SpeechBubble.h"

USING_NS_CC;
USING_NS_GAF;
typedef cocos2d::Vector<cocos2d::Node*> Nodes_t;

GameplayScene::GameplayScene()
:m_robots(0)
{

}
GameplayScene::~GameplayScene()
{
    removeAllChildrenWithCleanup(true);
    _eventDispatcher->removeCustomEventListeners("enemy_killed");
}

GameplayScene* GameplayScene::create(int enemies)
{
    GameplayScene *pRet = new GameplayScene();
    if (pRet && pRet->init(enemies))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void GameplayScene::update(float dt)
{
    checkCollisionsSimple();
}

bool GameplayScene::init(int enemies)
{    
    m_robots = enemies;
    
    m_enemyAsset = GAFAsset::create("robot_enemy/robot_enemy.gaf");
    _eventDispatcher->addCustomEventListener("enemy_killed", CC_CALLBACK_1(GameplayScene::onEnemyKilled, this));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    {
        Label* text = Label::create("Menu", "Courier.ttf", 35);
        text->setColor(Color3B(255, 255, 255));
        MenuItem* menuButton = MenuItemLabel::create(text, CC_CALLBACK_1(GameplayScene::advanceToMenu, this));
        menuButton->setPosition(visibleSize - menuButton->getContentSize());
        Menu* menu = Menu::create(menuButton, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 1);
    }

    {
        Label* text = Label::create("Atlases", "Courier.ttf", 35);
        text->setColor(Color3B(255, 255, 255));
        MenuItem* menuButton = MenuItemLabel::create(text, CC_CALLBACK_1(GameplayScene::showAtlases, this));
        menuButton->setPosition(Vec2(menuButton->getContentSize().width / 2 + 40, visibleSize.height - menuButton->getContentSize().height));
        Menu* menu = Menu::create(menuButton, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 1);
    }

    {

        MenuItem* leftButton = DoubleTriggerMenuItemSprite::create(
            Sprite::create("right_idle.png"),
            Sprite::create("right_selected.png"),
            nullptr,
            CC_CALLBACK_1(GameplayScene::leftButtonCallback, this, false),
            CC_CALLBACK_1(GameplayScene::leftButtonCallback, this, true));


        MenuItem* rightButton = DoubleTriggerMenuItemSprite::create(
            Sprite::create("right_idle.png"),
            Sprite::create("right_selected.png"),
            nullptr,
            CC_CALLBACK_1(GameplayScene::rightButtonCallback, this, false),
            CC_CALLBACK_1(GameplayScene::rightButtonCallback, this, true));

        leftButton->setScaleX(-1);
        rightButton->setPosition(Size(leftButton->getContentSize().width + 40, 0));
        Menu* menu = Menu::create(leftButton, rightButton, NULL);
        menu->setPosition(leftButton->getContentSize() + Size(0, -10));
        addChild(menu, 1);
    }

    {
        MenuItem* toggleGunButton = MenuItemSprite::create(
            Sprite::create("gun_idle.png"),
            Sprite::create("gun_pressed.png"),
            CC_CALLBACK_1(GameplayScene::toggleGunButtonCallback, this));

        MenuItem* fireButton = MenuItemSprite::create(
            Sprite::create("fire_idle.png"),
            Sprite::create("fire_selected.png"),
            CC_CALLBACK_1(GameplayScene::fireButtonCallback, this));

        toggleGunButton->setPosition(Size(-toggleGunButton->getContentSize().width - fireButton->getContentSize().width - 40, fireButton->getContentSize().height));

        fireButton->setPosition(Size(-fireButton->getContentSize().width, fireButton->getContentSize().height));
        Menu* menu = Menu::create(fireButton, toggleGunButton, NULL);
        menu->setPosition(Size(visibleSize.width, -10));
        addChild(menu, 1);
    }

    {
        m_speechBubble = SpeechBubble::create();
        m_speechBubble->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - m_speechBubble->getContentSize().height));
        addChild(m_speechBubble, 1);
        m_speechBubble->setVisible(false);
    }

    {
        Vec2 levelScale(0.5, 0.5);
        Vec2 levelPosition(250, 200);

        m_level = Node::create();
        addChild(m_level, 1, TAG_LEVEL);

		Background* bg = Background::create();
		addChild(bg);

        m_player = Player::create();
        Gun* gun = Gun::create("gun_1.plist");
        m_player->setGun(gun);
        m_player->setPosition(levelPosition);
        m_player->setScale(levelScale.x, levelScale.y);
        addChild(m_player, 1, TAG_PLAYER);

        m_level->setScale(levelScale.x, levelScale.y);
        m_level->setPosition(levelPosition);
        for(int i = 0; i < m_robots; ++i)
            spawnEnemy();
    }

    Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
	
	glClearColor(0, 0, 0, 1.0);
	
    return true;
}

void GameplayScene::advanceToMenu(cocos2d::Ref* pSender)
{
    auto* scene = MainMenuScene::create();
    Director::getInstance()->replaceScene(scene);
}

void GameplayScene::showAtlases(cocos2d::Ref* pSender)
{
    auto* scene = AtlasesScene::create();
    Director::getInstance()->pushScene(scene);
}

void GameplayScene::fireButtonCallback(cocos2d::Ref* pSender)
{
    m_player->shoot();
}

void GameplayScene::leftButtonCallback(cocos2d::Ref* pSender, bool pressed)
{
    if (pressed)
    {
        m_player->walkLeft();
    }
    else
    {
        m_player->stop();
    }
}

void GameplayScene::rightButtonCallback(cocos2d::Ref* pSender, bool pressed)
{
    if (pressed)
    {
        m_player->walkRight();
    }
    else
    {
        m_player->stop();
    }
}

void GameplayScene::onEnemyKilled(void*)
{
    spawnEnemy();
}

void GameplayScene::checkCollisionsSimple()
{
    Nodes_t nodes = m_level->getChildren();

    const double playerHalfWidth = m_player->getSize().width / 2;
    
    for (Nodes_t::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        if ((*it)->getTag() == TAG_ENEMY)
        {
            Enemy *e = reinterpret_cast<Enemy*>(*it);
            if (e->isDying())
            {
                continue;
            }

            const double enemyHalfWidth = e->getSize().width / 2;
            const double distCollisionPlayerEnemy = playerHalfWidth + enemyHalfWidth;
            const double distCollisionProjectileEnemy = enemyHalfWidth;

            const double enemyX = m_level->convertToWorldSpace(e->getPosition()).x;
            
            double distToPlayer = fabs(m_player->getPositionX() + playerHalfWidth - enemyX - enemyHalfWidth);
            if (distToPlayer <= distCollisionPlayerEnemy)
            {
                e->die();
            }
            
            float damage = checkForProjectilesDamage(enemyX, distCollisionProjectileEnemy);
            if (damage > 0.f && !e->isDying())
            {
                e->damage(damage);
            }
        }
    }
}

float GameplayScene::checkForProjectilesDamage(const float enemyX, const float epsDistance)
{
    Nodes_t nodes = getChildren();

    for (Nodes_t::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        if ((*it)->getTag() == TAG_PROJECTILE)
        {
            Projectile *p = reinterpret_cast<Projectile*>(*it);

            double distToProjectile = fabs(p->getPositionX() - enemyX);
            if (distToProjectile <= epsDistance)
            {
                p->destroy();
                return p->getDamage();
            }
        }
    }

    return 0.f;
}

void GameplayScene::spawnEnemy()
{
    Enemy* e = Enemy::create(m_enemyAsset->createObjectAndRun());
    bool left = rand() % 2;
    float position = 800 + (rand() % 200);
    if (left)
    {
        Vec2 pos(m_player->getPositionX() + position, m_player->getPositionY());
        pos = m_level->convertToNodeSpace(pos);
        e->setPosition(pos);
        e->walkLeft();
    }
    else
    {
        Vec2 pos(m_player->getPositionX() - position, m_player->getPositionY());
        pos = m_level->convertToNodeSpace(pos);
        e->setPosition(pos);
        e->walkRight();
    }
    m_level->addChild(e, 1, TAG_ENEMY);
}

void GameplayScene::addProjectile(Projectile* p)
{
    addChild(p, 1, TAG_PROJECTILE);
}

void GameplayScene::toggleGunButtonCallback(cocos2d::Ref* pSender)
{
    int GUNS = 2;

    m_gunId += 1;
    if (m_gunId > GUNS - 1)
        m_gunId = 0;

    if (m_gunId == 0)
    {
        m_player->setGun(Gun::create("gun_1.plist"));
    }
    else if (m_gunId == 1)
    {
        m_player->setGun(Gun::create("gun_2.plist"));
    }
}
