#include "MainMenuScene.h"
#include "GameplayScene.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"

USING_NS_CC;

MainMenuScene::MainMenuScene()
:m_enemies(1)
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

    GAFAnimatedObject* logo = GAFAnimatedObject::createAndRun("logo/logo.gaf", false);
    logo->setPosition(0, visibleSize.height);
    addChild(logo);

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

    m_label = Label::create("1 enemies", "arial", 20);
    m_label->setColor(Color3B::RED);
    MenuItem* toggleEnemiesCount = MenuItemLabel::create(m_label, CC_CALLBACK_1(MainMenuScene::toggleEnemiesCount, this));
    Menu* menu2 = Menu::create(toggleEnemiesCount, NULL);
    toggleEnemiesCount->setPosition(visibleSize.width - 60 , 50);
    menu2->setPosition(Vec2::ZERO);
    addChild(menu2);
    
    return true;
}

void MainMenuScene::toggleEnemiesCount(Ref*)
{
    switch (m_enemies)
    {
        case 1:
            m_enemies = 10;
            break;
        case 10:
            m_enemies = 20;
            break;
        case 20:
            m_enemies = 40;
            break;
        default:
            m_enemies = 1;
            break;
    }
    std::stringstream ss;
    ss << m_enemies << " enemies";
    m_label->setString(ss.str());
    
}

void MainMenuScene::advanceToGame(cocos2d::Ref* pSender)
{
    removeChildByTag(1);
    Scene* gameplay = GameplayScene::create(m_enemies);
    Director::getInstance()->replaceScene(gameplay);
}

