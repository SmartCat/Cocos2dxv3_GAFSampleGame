#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "CCDoubleTriggerMenuItemLabel.h"
#include "Player.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "Gun.h"

USING_NS_CC;

bool GameplayScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
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

    m_player = Player::create();

    Gun* gun = Gun::create("gun_1.plist");
    m_player->setGun(gun);
    addChild(m_player, 1);

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
