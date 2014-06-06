#include "Gun.h"
#include "GAFPrecompiled.h"
#include "GAFAnimatedObject.h"
#include "GAFAsset.h"
#include "Projectile.h"


USING_NS_CC;

Gun::Gun()
{
}

Gun::~Gun()
{
    m_model->setSequenceDelegate(nullptr);
    CC_SAFE_RELEASE(m_model);
    CC_SAFE_RELEASE(m_projectile);
}

void Gun::shoot()
{
    if (m_cooldown > 0)
        return;

    if (m_model)
    {
        m_model->playSequence("fire", false);
        m_cooldown = m_reloadTime;
    }

    Node* model = m_projectile->createObjectAndRun(true);
    Vec2 pos = getPosition();
    Vec3 pos3(pos.x, pos.y, 0);
    Mat4 transform = getNodeToWorldTransform();
    transform.transformPoint(&pos3);
    cocos2d::Quaternion quat;
    transform.getRotation(&quat);
    quat.normalize();
    float rotation = 2.0f * acos(quat.w);
    Vec2 direction = Vec2::forAngle(rotation);
    Projectile* p = Projectile::create(model, m_projectileDamage, direction * m_projectileSpeed, m_shootDelay);
    p->setNodeToParentTransform(getNodeToWorldTransform());
    Director::getInstance()->getRunningScene()->addChild(p);
    p->setPosition(Vec2(pos3.x, pos3.y) + m_projectileOffset);

}

void Gun::update(float dt)
{
    if (m_cooldown > 0)
        m_cooldown -= dt;
}

void Gun::onFinishSequence(GAFAnimatedObject * object, const std::string& sequenceName)
{
    if (sequenceName == "fire")
    {
        m_model->playSequence("idle");
    }
}

Gun* Gun::create(const std::string& name)
{
    Gun* ret = new Gun();
    if (ret && ret->init(name))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool Gun::init(const std::string& name)
{
    bool ret = true;
    {
        cocos2d::__Dictionary* params = cocos2d::__Dictionary::createWithContentsOfFile(name.c_str());

        if (!params)
            return false;

        std::string modelName = params->valueForKey("model")->_string;

        GAFAsset* asset = GAFAsset::create(modelName);
        if (!asset)
            return false;

        m_model = asset->createObjectAndRun();
        m_model->retain();
        Vec2 position(Vec2(params->valueForKey("pivot_x")->floatValue(), params->valueForKey("pivot_y")->floatValue()));
        m_model->setPosition(position);
        m_model->playSequence("idle", true);
        m_model->setSequenceDelegate(this);
        addChild(m_model);

        std::string projectileName = params->valueForKey("projectile")->_string;
        m_projectile = GAFAsset::create(projectileName);
        if (m_projectile)
            m_projectile->retain();

        m_shootDelay = params->valueForKey("shoot_delay")->floatValue();
        m_projectileSpeed = params->valueForKey("projectile_speed")->floatValue();
        m_projectileDamage = params->valueForKey("damage")->floatValue();
        m_reloadTime = params->valueForKey("reload_time")->floatValue();

        m_projectileOffset = Vec2(params->valueForKey("projectile_pivot_x")->floatValue(), params->valueForKey("projectile_pivot_y")->floatValue());

        Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
    }
    return true;
}
