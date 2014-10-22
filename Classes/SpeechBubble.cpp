#include "SpeechBubble.h"
#include "GAFPrecompiled.h"
#include "GAF.h"

USING_NS_CC;
USING_NS_GAF;

SpeechBubble::SpeechBubble()
{
}

SpeechBubble::~SpeechBubble()
{
    CC_SAFE_RELEASE(m_model);
}

cocos2d::Size SpeechBubble::getSize() const
{
    return m_size;
}

bool SpeechBubble::init()
{
    bool ret = true;
    {
        m_model = GAFAnimatedObject::create(GAFAsset::create("speech_bubble/speech_bubble.gaf"));
        m_model->pause();
        m_model->retain();      
    }
    return ret;
}

void SpeechBubble::detachFromParent()
{
    auto p = m_model->getParent();
    if(p)
    {
        p->removeChild(m_model, false);
    }
}

void SpeechBubble::attachToParent(cocos2d::Node* parent)
{
    parent->addChild(m_model);
}

void SpeechBubble::setFrame(uint16_t frame)
{
    m_model->gotoAndStop(frame);
}

void SpeechBubble::stop()
{
}
