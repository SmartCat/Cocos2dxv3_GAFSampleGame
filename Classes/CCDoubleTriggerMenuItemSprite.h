#pragma once 

#include "cocos2d.h"

NS_CC_BEGIN

class DoubleTriggerMenuItemSprite : public cocos2d::MenuItemSprite
{
public:
    static DoubleTriggerMenuItemSprite * create(Node* normal, Node* selected, Node* disabled, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onActivateCallback);
    virtual void selected() override;

CC_CONSTRUCTOR_ACCESS:
    DoubleTriggerMenuItemSprite()
        : _onSelectedCallback(nullptr)
    {}
    virtual ~DoubleTriggerMenuItemSprite() {}
    bool initWithNormalSprite(Node* normal, Node* selected, Node* disabled, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onActivateCallback);

private:
    ccMenuCallback _onSelectedCallback;
};

NS_CC_END
