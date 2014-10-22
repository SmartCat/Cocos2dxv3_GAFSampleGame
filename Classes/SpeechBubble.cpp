#include "SpeechBubble.h"
#include "GameplayScene.h"
#include "GAFPrecompiled.h"
#include "GAF.h"

USING_NS_CC;
USING_NS_GAF;

const float SpeechBubble::k_deltaTime = 1.f;

std::string SpeechBubble::getEventName(InfoState state)
{
    switch (state)
    {
    case IS_GameStarted:
        return "game_started";

    case IS_PlayerMoved:
        return "player_moved";

    case IS_WeaponSwitched:
        return "weapon_switched";

    case IS_EnemyKilled:
        return "enemy_hitted";
    
    default:
        return "";
    }
}

void SpeechBubble::onGameStarted(void* data)
{
    checkState(IS_GameStarted);
}

void SpeechBubble::onPlayerMoved(void* data)
{
    checkState(IS_PlayerMoved);
}

void SpeechBubble::onWeaponSwitched(void* data)
{
    checkState(IS_WeaponSwitched);
}

void SpeechBubble::onEnemyKilled(void* data)
{
    checkState(IS_EnemyKilled);
}

bool SpeechBubble::onTouchBegan(Touch* touch, Event* event)
{
    if (!isVisible())
    {
        return false;
    }

    Vec2 touchLocation = touch->getLocation();
    Vec2 local = m_model->convertToNodeSpace(touchLocation); // TODO: correct touches checking
    local.y = -local.y;
    Rect r = m_model->realBoundingBoxForCurrentFrame();
    r.origin = Vec2::ZERO;

    if (r.containsPoint(local))
    {
        return true;
    }

    return false;
}

void SpeechBubble::onTouchEnded(Touch* touch, Event* event)
{
    hideBubble();
}

SpeechBubble::SpeechBubble()
: m_awaitingForStep(IS_GameStarted)
, m_countdown(-1.f)
{
}

SpeechBubble::~SpeechBubble()
{
    for (int i = 0; i < IS_COUNT; i++)
    {
        _eventDispatcher->removeCustomEventListeners(getEventName(static_cast<InfoState>(i)));
    }

    CC_SAFE_RELEASE(m_model);
}

bool SpeechBubble::init()
{
    bool ret = true;
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();

        m_model = GAFAnimatedObject::create(GAFAsset::create("speech_bubble/speech_bubble.gaf"));
        m_model->pause();
        Vec2 deltaAncor;
        deltaAncor.x = m_model->getAnchorPointInPoints().x;
        deltaAncor.y = 100 - m_model->getAnchorPointInPoints().y; // TODO: hardcoded y coord
        m_model->setPosition(Vec2(visibleSize.width / 2, visibleSize.height) - deltaAncor);
        addChild(m_model);
        m_model->retain();      
    }

    Director::getInstance()->getScheduler()->scheduleUpdateForTarget(this, 1, false);
    _eventDispatcher->addCustomEventListener(getEventName(IS_GameStarted), CC_CALLBACK_1(SpeechBubble::onGameStarted, this));
    _eventDispatcher->addCustomEventListener(getEventName(IS_PlayerMoved), CC_CALLBACK_1(SpeechBubble::onPlayerMoved, this));
    _eventDispatcher->addCustomEventListener(getEventName(IS_WeaponSwitched), CC_CALLBACK_1(SpeechBubble::onWeaponSwitched, this));
    _eventDispatcher->addCustomEventListener(getEventName(IS_EnemyKilled), CC_CALLBACK_1(SpeechBubble::onEnemyKilled, this));

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(SpeechBubble::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(SpeechBubble::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return ret;
}

void SpeechBubble::update(float dt)
{
    if (!isTimerDisabled())
    {
        m_countdown -= dt;
        if (isTimerDisabled())
        {
            showBubble();
        }
    }
}

void SpeechBubble::checkState(InfoState state)
{
    if (!isTimerDisabled())
    {
        return;
    }

    if (m_awaitingForStep == state)
    {
        m_countdown = k_deltaTime;
    }
}

void SpeechBubble::showBubble()
{
    setFrame(m_awaitingForStep);
    setVisible(true);

    GameplayScene *scene = static_cast<GameplayScene*>(Director::getInstance()->getRunningScene());
    if (m_awaitingForStep == IS_GameStarted || m_awaitingForStep == IS_WeaponSwitched)
    {
        scene->disableHud();
    }

    if (m_awaitingForStep == IS_WeaponSwitched)
    {
        scene->enableWeaponSwitch();
    }
}

void SpeechBubble::hideBubble()
{
    setVisible(false);

    m_awaitingForStep = static_cast<InfoState>(static_cast<int>(m_awaitingForStep)+1);
    GameplayScene *scene = static_cast<GameplayScene*>(Director::getInstance()->getRunningScene());
    scene->enableAll();
}

void SpeechBubble::setFrame(uint16_t frame)
{
    m_model->gotoAndStop(frame);
}

bool SpeechBubble::isTimerDisabled() const
{
    return m_countdown <= 0.f;
}