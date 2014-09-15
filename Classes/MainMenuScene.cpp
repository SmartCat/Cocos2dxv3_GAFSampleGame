#include "MainMenuScene.h"
#include "GameplayScene.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"

USING_NS_CC;

MainMenuScene::MainMenuScene()
{

}
MainMenuScene::~MainMenuScene()
{
    removeAllChildrenWithCleanup(true);
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto logo = GAFAnimatedObject::createAndRun("logo/logo.gaf", false);
    logo->setPosition(0, visibleSize.height);
    addChild(logo);
	logo->start();

	MenuItem* startButton = MenuItemSprite::create(
        Sprite::create("button_logo_idle.png"),
        Sprite::create("button_logo_selected.png"),
        CC_CALLBACK_1(MainMenuScene::advanceToGame, this));
    Menu* menu = Menu::create(startButton, NULL);

    startButton->setPosition(visibleSize.width / 2, 50);
    menu->setPosition(Vec2::ZERO);
    menu->setTag(1);
    addChild(menu, 1);
	
	glClearColor(1, 1, 1, 1.0);

    return true;
}


void MainMenuScene::advanceToGame(cocos2d::Ref* pSender)
{
    removeChildByTag(1);
    Scene* gameplay = GameplayScene::create();
    Director::getInstance()->replaceScene(gameplay);
}

