#include "MainMenuScene.h"
#include "GameplayScene.h"

USING_NS_CC;


bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Label* text = Label::create("Start Game", "Courier.ttf", 35);
    MenuItem* startButton = MenuItemLabel::create(text, CC_CALLBACK_1(MainMenuScene::advanceToGame, this));
    startButton->setPosition(visibleSize / 2);
    Menu* menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    return true;
}


void MainMenuScene::advanceToGame(cocos2d::Ref* pSender)
{
    Scene* gameplay = GameplayScene::create();
    Director::getInstance()->pushScene(gameplay);
}

