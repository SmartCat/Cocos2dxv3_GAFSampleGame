#pragma once 

#include "cocos2d.h"

class AtlasesScene : public cocos2d::Scene
{
public:
    AtlasesScene();
    ~AtlasesScene();

    virtual bool init();  
    
    CREATE_FUNC(AtlasesScene);

    void advanceToGame(cocos2d::Ref* pSender);

    void leftButtonCallback(cocos2d::Ref* pSender);
    void rightButtonCallback(cocos2d::Ref* pSender);
    
private:
    cocos2d::Label* m_label;
    cocos2d::Image* m_currentAtlas;

    typedef std::vector<std::string> AssetsNames_t;
    AssetsNames_t m_assetsToLoad;
    AssetsNames_t::iterator m_currentAssetName;
};
