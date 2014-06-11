#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "CCDoubleTriggerMenuItemLabel.h"
#include "CCDoubleTriggerMenuItemSprite.h"
#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "Gun.h"
#include "Enemy.h"
#include "GAFAsset.h"

USING_NS_CC;

GameplayScene* GameplayScene::create()
{
    GameplayScene *pRet = new GameplayScene();
    if (pRet && pRet->init())
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

bool GameplayScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    
    m_enemyAsset = GAFAsset::create("robot_enemy/robot_enemy.gaf");
    _eventDispatcher->addCustomEventListener("enemy_killed", CC_CALLBACK_1(GameplayScene::onEnemyKilled, this));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    {
        Label* text = Label::create("Menu", "Courier.ttf", 35);
        MenuItem* menuButton = MenuItemLabel::create(text, CC_CALLBACK_1(GameplayScene::advanceToMenu, this));
        menuButton->setPosition(visibleSize - menuButton->getContentSize());
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

        toggleGunButton->setPosition(Size(- toggleGunButton->getContentSize().width - fireButton->getContentSize().width - 40, fireButton->getContentSize().height));

        fireButton->setPosition(Size(-fireButton->getContentSize().width, fireButton->getContentSize().height));
        Menu* menu = Menu::create(fireButton, toggleGunButton, NULL);
        menu->setPosition(Size(visibleSize.width - 50, -10));
        addChild(menu, 1);
    }

    {
        Vec2 levelScale(0.5, 0.5);
        Vec2 levelPosition(250, 200);

        m_level = Node::create();
        m_level->retain();
        addChild(m_level, 1, 1);

        m_player = Player::create();
        Gun* gun = Gun::create("gun_1.plist");
        m_player->setGun(gun);
        m_player->setPosition(levelPosition);
        m_player->setScale(levelScale.x, levelScale.y);
        addChild(m_player, 1, 2);

        m_level->setScale(levelScale.x, levelScale.y);
        m_level->setPosition(levelPosition);
        spawnEnemy();

        getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

        //getPhysicsWorld()->setDebugDrawMask(0xFF);
    }
    return true;
}

void GameplayScene::advanceToMenu(cocos2d::Ref* pSender)
{
    Scene* menu = MainMenuScene::create();
    Director::getInstance()->pushScene(menu);
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

void GameplayScene::spawnEnemy()
{
    Enemy* e = Enemy::create(m_enemyAsset->createObjectAndRun());
    bool left = rand() % 2;
    if (left)
    {
        Vec2 pos(m_player->getPositionX() + 900, m_player->getPositionY());
        pos = m_level->convertToNodeSpace(pos);
        e->setPosition(pos);
        e->walkLeft();
        m_level->addChild(e);
    }
    else
    {
        Vec2 pos(m_player->getPositionX() - 900, m_player->getPositionY());
        pos = m_level->convertToNodeSpace(pos);
        e->setPosition(pos);
        e->walkRight();
        m_level->addChild(e);
    }
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
