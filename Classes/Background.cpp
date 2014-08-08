#include "Background.h"
#include "GAFAsset.h"
#include "GAFAnimatedObject.h"

USING_NS_CC;

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

		/*if (m_scale == 0.0f)
		{
			int tileHeight = tile->getContentSize().height;
			m_scale = visibleSize.height / tile->getContentSize().height;
		}*/
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

	int newPos = static_cast<int>(position.x) % m_tileWidth;
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

void Background::repositionTilesStartingFrom(int startX)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int totalSize = 0;
	for each (GAFAnimatedObject* obj in m_tiles)
	{
		obj->setPosition(totalSize + startX, (visibleSize.height + obj->getContentSize().height) / 2);
		totalSize += m_tileWidth - 1;
	}
}