#pragma once

#include "cocos2d.h"

NS_CC_BEGIN

class DoubleTriggerMenuItemLabel : public cocos2d::MenuItemLabel
{
public:
    static DoubleTriggerMenuItemLabel * create(Node*label, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onActivateCallback);
    virtual void selected() override;

CC_CONSTRUCTOR_ACCESS:
    DoubleTriggerMenuItemLabel()
        : _onSelectedCallback(nullptr)
    {}
    virtual ~DoubleTriggerMenuItemLabel() {}
    bool initWithLabel(Node* label, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onActivateCallback);

private:
    ccMenuCallback _onSelectedCallback;
};

NS_CC_END
