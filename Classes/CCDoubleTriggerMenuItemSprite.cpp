#include "CCDoubleTriggerMenuItemSprite.h"

NS_CC_BEGIN

bool DoubleTriggerMenuItemSprite::initWithNormalSprite(Node* normal, Node* selected, Node* disabled, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onSelectedCallback)
{
    _onSelectedCallback = onSelectedCallback;
    return MenuItemSprite::initWithNormalSprite(normal, selected, disabled, onReleasedCallback);
}

DoubleTriggerMenuItemSprite * DoubleTriggerMenuItemSprite::create(Node* normal, Node* selected, Node* disabled, const ccMenuCallback& onReleasedCallback, const ccMenuCallback& onSelectedCallback)
{
    DoubleTriggerMenuItemSprite *ret = new DoubleTriggerMenuItemSprite();
    ret->initWithNormalSprite(normal, selected, disabled, onReleasedCallback, onSelectedCallback);
    ret->autorelease();
    return ret;
}

void DoubleTriggerMenuItemSprite::selected()
{
    MenuItemSprite::selected();
    if (_enabled)
    {
        if (_onSelectedCallback)
        {
            _onSelectedCallback(this);
        }
    }
}

NS_CC_END
