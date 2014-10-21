#include "Background.h"
#include "GAFAsset.h"
#include "GAFAnimatedObject.h"

USING_NS_CC;
USING_NS_GAF;

Background::Background()
{
}

Background::~Background()
{
	removeAllChildrenWithCleanup(true);
}

bool Background::init()
{
	m_masterTile = GAFAsset::create("back_1/back_1.gaf");
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	const int visibleSizeWidth = visibleSize.width;
	int totalSize = 0;

	do
	{
		GAFAnimatedObject* tile = m_masterTile->createObjectAndRun();
		tile->retain();

		if (m_tileWidth == 0)
		{
			m_tileWidth = tile->getContentSize().width;
		}

		tile->setScale(1);
		m_tiles.push_back(tile);
		addChild(tile);
		
		totalSize += m_tileWidth;
	} while (totalSize < visibleSizeWidth + m_tileWidth);

	repositionTilesStartingFrom(0);
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);

	return true;
}

void Background::update(float dt)
{
	Node* level = Director::getInstance()->getRunningScene()->getChildByTag(1);
	if (level == nullptr)
	{
		return;
	}

	Vec2 position = level->getPosition();

	float newPos = fmodf(position.x, m_tileWidth);
	if (position.x > 0.f)
	{
		newPos -= m_tileWidth;
	}
	repositionTilesStartingFrom(newPos);
}

void Background::cleanupTiles()
{
	//TODO: variant #2
}

void Background::repositionTilesStartingFrom(float startX)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float totalSize = 0.f;
    std::deque<GAFAnimatedObject*>::iterator it;
	for (it = m_tiles.begin(); it != m_tiles.end(); it++)
	{
		(*it)->setPosition(totalSize + startX, visibleSize.height);
		totalSize += m_tileWidth - 1.0f;
        
	}
}