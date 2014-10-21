#pragma once 

#include "cocos2d.h"

namespace gaf
{
    class GAFAnimatedObject;
}

class SpeechBubble : public cocos2d::Node
{

public:
    SpeechBubble();
    virtual ~SpeechBubble();
    virtual bool init();  
    
    CREATE_FUNC(SpeechBubble);

    void detachFromParent();
    void attachToParent(cocos2d::Node* parent);
    void setFrame(uint16_t frame);

    cocos2d::Size getSize() const;

    void stop();

private:
    gaf::GAFAnimatedObject* m_model = nullptr;
    cocos2d::Size m_size;
};
