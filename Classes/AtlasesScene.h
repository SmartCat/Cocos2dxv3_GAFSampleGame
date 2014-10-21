#pragma once 

#include "cocos2d.h"

class AtlasesScene : public cocos2d::Scene
{
public:
    AtlasesScene();
    ~AtlasesScene();

    virtual bool init();  
    
    CREATE_FUNC(AtlasesScene);

    void advanceToGame(Ref* pSender);

    void leftButtonCallback(Ref* pSender);
    void rightButtonCallback(Ref* pSender);
    
private:
    void reloadSprite();

    cocos2d::Label* m_label;
    cocos2d::Sprite* m_currentAtlas;

    typedef std::vector<std::string> AssetsNames_t;
    AssetsNames_t m_assetsToLoad;
    AssetsNames_t::iterator m_currentAssetName;
};
