#include "AtlasesScene.h"
#include "GAFPrecompiled.h"
#include "GAF.h"

#include "CCDoubleTriggerMenuItemSprite.h"

USING_NS_CC;
USING_NS_GAF;

AtlasesScene::AtlasesScene() :
m_currentAtlas(nullptr)
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
	
    glClearColor(0.5f, 0.5f, 0.5f, 1.0);

    m_label = Label::create("", "arial", 20);
    m_label->setColor(Color3B::RED);
    m_label->setPosition(visibleSize.width / 2, 50);
    addChild(m_label, 1);

    reloadSprite();
    
    return true;
}
void AtlasesScene::leftButtonCallback(Ref* pSender)
{
    if (m_currentAssetName == m_assetsToLoad.begin())
    {
        m_currentAssetName = m_assetsToLoad.end() - 1;
    }
    else
    {
        --m_currentAssetName;
    }
    reloadSprite();
}

void AtlasesScene::reloadSprite()
{
    if (m_currentAtlas)
    {
        removeChild(m_currentAtlas);
    }

    std::string name = *m_currentAssetName;
    name.append("/");
    name.append(*m_currentAssetName);
    name.append(".gaf");

    auto asset = GAFAsset::create(name);
    auto texture = static_cast<Texture2D*>(asset->getTextureAtlas()->textures()->getObjectAtIndex(0));
    m_currentAtlas = Sprite::createWithTexture(texture);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_currentAtlas->setPosition(visibleSize / 2);
    addChild(m_currentAtlas);
}

void AtlasesScene::rightButtonCallback(Ref* pSender)
{
    ++m_currentAssetName;
    if (m_currentAssetName == m_assetsToLoad.end())
    {
        m_currentAssetName = m_assetsToLoad.begin();
    }
    reloadSprite();
}

void AtlasesScene::advanceToGame(Ref* pSender)
{
    Director::getInstance()->popScene();
    glClearColor(0, 0, 0, 1.0); // quick fix for black bg in game
}

