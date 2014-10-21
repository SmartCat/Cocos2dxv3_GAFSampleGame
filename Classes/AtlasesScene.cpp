#include "AtlasesScene.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"

#include "CCDoubleTriggerMenuItemSprite.h"

USING_NS_CC;
USING_NS_GAF;

AtlasesScene::AtlasesScene()
{
    m_assetsToLoad.push_back("roboprogrm");
    m_assetsToLoad.push_back("robot_enemy");
    m_assetsToLoad.push_back("gun_1");
    m_assetsToLoad.push_back("gun_2");
    m_assetsToLoad.push_back("back_1");
    m_currentAssetName = m_assetsToLoad.begin();
}

AtlasesScene::~AtlasesScene()
{
    removeAllChildrenWithCleanup(true);
}

bool AtlasesScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    {
        MenuItem* leftButton = MenuItemSprite::create(
            Sprite::create("right_idle.png"),
            Sprite::create("right_selected.png"),
            CC_CALLBACK_1(AtlasesScene::leftButtonCallback, this));


        MenuItem* rightButton = MenuItemSprite::create(
            Sprite::create("right_idle.png"),
            Sprite::create("right_selected.png"),
            CC_CALLBACK_1(AtlasesScene::rightButtonCallback, this));

        leftButton->setScaleX(-1);
        rightButton->setPosition(Size(leftButton->getContentSize().width + 40, 0));
        Menu* menu = Menu::create(leftButton, rightButton, NULL);
        menu->setPosition(leftButton->getContentSize() + Size(0, -10));
        addChild(menu, 1);
    }

    MenuItem* closeButton = MenuItemSprite::create(
        Sprite::create("fire_idle.png"),
        Sprite::create("fire_selected.png"),
        CC_CALLBACK_1(AtlasesScene::advanceToGame, this));
    Menu* menu = Menu::create(closeButton, NULL);
    closeButton->setPosition(visibleSize - closeButton->getContentSize());
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);
	
	glClearColor(1, 1, 1, 1.0);

    m_label = Label::create("", "arial", 20);
    m_label->setColor(Color3B::RED);
    m_label->setPosition(visibleSize.width / 2, 50);
    addChild(m_label, 1);
    
    return true;
}
void AtlasesScene::leftButtonCallback(cocos2d::Ref* pSender)
{

}

void AtlasesScene::rightButtonCallback(cocos2d::Ref* pSender)
{

}

void AtlasesScene::advanceToGame(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
    glClearColor(0, 0, 0, 1.0); // quick fix for black bg in game
}

