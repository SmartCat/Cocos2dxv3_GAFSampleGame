#include "SpeechBubble.h"
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
        m_model = GAFAnimatedObject::create(GAFAsset::create("speech_bubble/speech_bubble.gaf"));
        m_model->pause();
        addChild(m_model);
        m_model->retain();      
    }

    _eventDispatcher->addCustomEventListener(getEventName(IS_GameStarted), CC_CALLBACK_1(SpeechBubble::onGameStarted, this));
    _eventDispatcher->addCustomEventListener(getEventName(IS_PlayerMoved), CC_CALLBACK_1(SpeechBubble::onPlayerMoved, this));
    _eventDispatcher->addCustomEventListener(getEventName(IS_WeaponSwitched), CC_CALLBACK_1(SpeechBubble::onWeaponSwitched, this));
    _eventDispatcher->addCustomEventListener(getEventName(IS_EnemyKilled), CC_CALLBACK_1(SpeechBubble::onEnemyKilled, this));

    return ret;
}

void SpeechBubble::update(float dt)
{
    if (!isTimerDisabled())
    {
        m_countdown -= dt;
        if (isTimerDisabled())
        {
            setFrame(m_awaitingForStep);
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

void SpeechBubble::setFrame(uint16_t frame)
{
    m_model->gotoAndStop(frame);
}

bool SpeechBubble::isTimerDisabled() const
{
    return m_countdown <= 1e-8;
}