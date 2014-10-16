#pragma once
#include "GAFPrecompiled.h"
#include "cocos2d.h"

namespace gaf
{
class GAFAsset;
class GAFAnimatedObject;
}

class Background : public cocos2d::Node
{
public:
    Background();
    virtual ~Background();

    virtual bool init();
    CREATE_FUNC(Background);

    void update(float dt);

private:
    void repositionTilesStartingFrom(float startX);
    void cleanupTiles();

    std::deque<gaf::GAFAnimatedObject*> m_tiles;
    gaf::GAFAsset* m_masterTile;
    int m_tileWidth = 0;
};
