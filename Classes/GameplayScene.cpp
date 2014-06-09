#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "CCDoubleTriggerMenuItemLabel.h"
#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "Gun.h"
#include "Enemy.h"

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
        Label* left = Label::create("<-", "Courier.ttf", 70);
        Label* right = Label::create("->", "Courier.ttf", 70);
        MenuItem* leftButton = DoubleTriggerMenuItemLabel::create(left,
            CC_CALLBACK_1(GameplayScene::leftButtonCallback, this, false),
            CC_CALLBACK_1(GameplayScene::leftButtonCallback, this, true));


        MenuItem* rightButton = DoubleTriggerMenuItemLabel::create(right,
            CC_CALLBACK_1(GameplayScene::rightButtonCallback, this, false),
            CC_CALLBACK_1(GameplayScene::rightButtonCallback, this, true));

        rightButton->setPosition(Size(leftButton->getContentSize().width + 40, 0));
        Menu* menu = Menu::create(leftButton, rightButton, NULL);
        menu->setPosition(leftButton->getContentSize() + Size(0, 10));
        addChild(menu, 1);
    }

    {
        Label* fire = Label::create("><", "Courier.ttf", 70);
        MenuItem* fireButton = MenuItemLabel::create(fire, CC_CALLBACK_1(GameplayScene::fireButtonCallback, this));
        fireButton->setPosition(Size(visibleSize.width - fireButton->getContentSize().width, fireButton->getContentSize().height - 10));
        Menu* menu = Menu::create(fireButton, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 1);
    }

    {
        Label* one = Label::create("Gun 1", "Courier.ttf", 35);
        Label* two = Label::create("Gun 2", "Courier.ttf", 35);
        MenuItem* oneButton = MenuItemLabel::create(one,
            CC_CALLBACK_1(GameplayScene::setGunCallback, this, "gun_1.plist"));

        MenuItem* twoButton = MenuItemLabel::create(two,
            CC_CALLBACK_1(GameplayScene::setGunCallback, this, "gun_2.plist"));

        twoButton->setPosition(Size(0, - oneButton->getContentSize().height + 10));
        Menu* menu = Menu::create(oneButton, twoButton, NULL);
        menu->setPosition(Size(oneButton->getContentSize().width, visibleSize.height - oneButton->getContentSize().height));
        addChild(menu, 1);
    }

    Node* level = Node::create();
    addChild(level, 1, 1);
    {
        m_player = Player::create();

        //Enemy* e = Enemy::create();
        //level->addChild(e);
        spawnEnemy();

        getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

        //getPhysicsWorld()->setDebugDrawMask(0xFF);


        auto body = PhysicsBody::createEdgeBox(Size(100, 100), PHYSICSBODY_MATERIAL_DEFAULT, 3);
        body->setPositionOffset(Vec2(50, 50));
        body->setContactTestBitmask(0x3);

        Gun* gun = Gun::create("gun_1.plist");
        m_player->setGun(gun);
        level->addChild(m_player, 1, 2);
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

void GameplayScene::setGunCallback(cocos2d::Ref* pSender, const std::string& name)
{
    m_player->setGun(Gun::create(name));
}

void GameplayScene::onEnemyKilled(void*)
{
    spawnEnemy();
}

void GameplayScene::spawnEnemy()
{
    Node* level = getChildByTag(1);

    if (level == nullptr)
        return;

    Enemy* e = Enemy::create();
    bool left = rand() % 2;
    if (left)
    {
        e->setPosition(m_player->getPositionX() + 900, 0);
        e->walkLeft();
        level->addChild(e);
    }
    else
    {
        e->setPosition(m_player->getPositionX() - 900, 0);
        e->walkRight();
        level->addChild(e);
    }
}
