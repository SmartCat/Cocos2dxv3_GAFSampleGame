#include "CCDoubleTriggerMenuItemLabel.h"

NS_CC_BEGIN

bool DoubleTriggerMenuItemLabel::initWithLabel(Node* label, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onSelectedCallback)
{
    _onSelectedCallback = onSelectedCallback;
    return MenuItemLabel::initWithLabel(label, onReleasedCallback);
}

DoubleTriggerMenuItemLabel * DoubleTriggerMenuItemLabel::create(Node*label, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onSelectedCallback)
{
    DoubleTriggerMenuItemLabel *ret = new DoubleTriggerMenuItemLabel();
    ret->initWithLabel(label, onReleasedCallback, onSelectedCallback);
    ret->autorelease();
    return ret;
}

void DoubleTriggerMenuItemLabel::selected()
{
    MenuItemLabel::selected();
    if (_enabled)
    {
        if (_onSelectedCallback)
        {
            _onSelectedCallback(this);
        }
    }
}

NS_CC_END
