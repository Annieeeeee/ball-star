#include "MyMap.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


MyMap::MyMap()
{
}

MyMap * MyMap::create(const std::string& tmxFile)
{
	MyMap *ret = new (std::nothrow) MyMap();
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MyMap::init()
{
	//������ͼ
	m_nomoveLayer = getLayer("nomove");
	m_backgroundLayer = getLayer("background");

	m_gid_nomove = m_nomoveLayer->getTileGIDAt(Vec2(0,0));

	//������������Ͳ�
	m_backgroundLayer->removeFromParent();
	addChild(m_backgroundLayer, -1);
	return true;
}

Point MyMap::tileCoordFromPosition(Point pos)  //��Ļ����ת��Ƭ����
{
	float x = pos.x / getTileSize().width;

	float y = ((getMapSize().height * getTileSize().height) - pos.y) /
		getTileSize().height;   
	return Point(x, y);

}

Vec2 MyMap::positionFromTileCoord(Point pos)  //��Ƭ����ת��Ļ����
{
	int x = (pos.x+0.5) * getTileSize().width;
	int y = (getMapSize().height- pos.y-0.5) * getTileSize().height;
	return Vec2(x, y);
}


bool MyMap::bnoMove(Vec2 position)    //�жϿɷ��ƶ�
{
	Point tileCoord = tileCoordFromPosition(position);

	unsigned int gid = m_nomoveLayer->getTileGIDAt(tileCoord);
    if (gid > 0) return true;
	return false;
}

