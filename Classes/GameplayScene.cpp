#include "GameplayScene.h"
#include "MainMenuScene.h"

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

}

void GameplayScene::leftButtonCallback(cocos2d::Ref* pSender)
{

}

void GameplayScene::rightButtonCallback(cocos2d::Ref* pSender)
{

}
