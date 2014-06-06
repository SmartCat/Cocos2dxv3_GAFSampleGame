#include "Gun.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFAsset.h"

USING_NS_CC;

Gun::Gun()
{
}

Gun::~Gun()
{
}

bool Gun::init()
{
    bool ret = true;
    {
        
    }
    return ret;
}

void Gun::shoot()
{
    if (m_model)
    {
        m_model->playSequence("fire_right", false);
    }
}

void Gun::load(const std::string& name)
{
    if (m_model)
    {
        removeChild(m_model, true);
    }

    GAFAsset* asset = GAFAsset::create(name);
    m_model = asset->createObjectAndRun();
    Rect frame = asset->getHeader().frameSize;
    m_model->setPosition(Vec2(-185, 370));

    if (m_model)
    {
        m_model->playSequence("idle_right", true);
        addChild(m_model);
    }
}
