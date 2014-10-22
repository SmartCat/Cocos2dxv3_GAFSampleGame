#pragma once 

#include "cocos2d.h"

namespace gaf
{
    class GAFAnimatedObject;
}

class SpeechBubble : public cocos2d::Node
{
    
public:
    enum InfoState
    {
        IS_GameStarted = 0,    // game_started
        IS_PlayerMoved,        // player_moved
        IS_WeaponSwitched,     // weapon_switched
        IS_EnemyKilled,        // enemy_hitted

        IS_COUNT
    };

    static std::string getEventName(InfoState state);

    // callbacks
    void onGameStarted(void* data);
    void onPlayerMoved(void* data);
    void onWeaponSwitched(void* data);
    void onEnemyKilled(void* data);

    SpeechBubble();
    virtual ~SpeechBubble();
    virtual bool init();  
    
    CREATE_FUNC(SpeechBubble);

    void update(float dt);

private:
    void checkState(InfoState state);

    void setFrame(uint16_t frame);
    bool isTimerDisabled() const;

    const static float k_deltaTime;
    float m_countdown;

    InfoState m_awaitingForStep;

    gaf::GAFAnimatedObject* m_model = nullptr;    
    cocos2d::Size m_size;
};
