#include "GameplayScene.h"
#include "MainMenuScene.h"
#include "CCDoubleTriggerMenuItemLabel.h"

USING_NS_CC;

bool GameplayScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    {
        Label* text = Label::createWithSystemFont("Menu", "Arial", 25);
        MenuItem* menuButton = MenuItemLabel::create(text, CC_CALLBACK_1(GameplayScene::advanceToMenu, this));
        menuButton->setPosition(visibleSize - menuButton->getContentSize());
        Menu* menu = Menu::create(menuButton, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 1);
    }

    {
        Label* left = Label::createWithSystemFont("<-", "Courier", 70);
        Label* right = Label::createWithSystemFont("->", "Courier", 70);
        MenuItem* leftButton = DoubleTriggerMenuItemLabel::create(left,
            CC_CALLBACK_1(GameplayScene::leftButtonCallback, this, false),
            CC_CALLBACK_1(GameplayScene::leftButtonCallback, this, true));


        MenuItem* rightButton = DoubleTriggerMenuItemLabel::create(right,
            CC_CALLBACK_1(GameplayScene::rightButtonCallback, this, false),
            CC_CALLBACK_1(GameplayScene::rightButtonCallback, this, true));

        rightButton->setPosition(Size(leftButton->getContentSize().width + 40, 0));
        Menu* menu = Menu::create(leftButton, rightButton, NULL);
        menu->setPosition(leftButton->getContentSize() + Size(0, 30));
        addChild(menu, 1);
    }

    {
        Label* fire = Label::createWithSystemFont("><", "Courier", 70);
        MenuItem* fireButton = MenuItemLabel::create(fire, CC_CALLBACK_1(GameplayScene::fireButtonCallback, this));
        fireButton->setPosition(Size(visibleSize.width - fireButton->getContentSize().width, fireButton->getContentSize().height + 30));
        Menu* menu = Menu::create(fireButton, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 1);
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
    CCLOG("shoot");
}

void GameplayScene::leftButtonCallback(cocos2d::Ref* pSender, bool pressed)
{
    if (pressed)
        CCLOG("right start");
    else
        CCLOG("right end");
}

void GameplayScene::rightButtonCallback(cocos2d::Ref* pSender, bool pressed)
{
    if (pressed)
        CCLOG("left start");
    else
        CCLOG("left end");
}
