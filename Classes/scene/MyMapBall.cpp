#include "MyMapBall.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


MyMapBall::MyMapBall()
{
}

MyMapBall * MyMapBall::create(const std::string& tmxFile)
{
	MyMapBall *ret = new (std::nothrow) MyMapBall();
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MyMapBall::init()
{
	//������ͼ�������ֵõ���
	m_soilLayer = getLayer("Soil");
	m_stoneLayer = getLayer("Stone");
	m_airLayer = getLayer("Air");
	m_borderLayer = getLayer("Border");
	m_diamondLayer = getLayer("Bonus");
	m_ladderLayer = getLayer("LadderFinal");
	m_etherLayer = getLayer("Ether");
	//���ò�ľ���λ��
	m_gid_soil = m_soilLayer->getTileGIDAt(Vec2(0, 0));
	m_gid_stone = m_stoneLayer->getTileGIDAt(Vec2(0, 0));
	m_gid_air = m_airLayer->getTileGIDAt(Vec2(0, 0));
	m_gid_border = m_borderLayer->getTileGIDAt(Vec2(0, 0));
	m_gid_diamond = m_diamondLayer->getTileGIDAt(Vec2(0, 0));
	m_gid_ladder = m_ladderLayer->getTileGIDAt(Vec2(0, 0));
	m_gid_ether = m_etherLayer->getTileGIDAt(Vec2(0, 0));

	m_diamondLayer->setVisible(false);
	m_ladderLayer->setVisible(false);
	
	return true;
}

Point MyMapBall::tileCoordFromPosition(Point pos)  //��Ļ����ת��Ƭ����
{
	Size mapSize = getMapSize();
	Size tileSize = getTileSize();
	int x = pos.x / tileSize.width;
	int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
	return Vec2(x, y);

}

Vec2 MyMapBall::positionFromTileCoord(Point pos)  //��Ƭ����ת��Ļ����
{
	Size mapSize = getMapSize();
	Size tileSize = getTileSize();
	int x = pos.x * tileSize.width + tileSize.width / 2;
	int y = (mapSize.height - pos.y) * tileSize.height - tileSize.height / 2;
	return Vec2(x, y);
}


bool MyMapBall::bnoMove(Vec2 position)    //�жϿɷ��ƶ�
{
	Point tileCoord = tileCoordFromPosition(position);
	//gidΪ�������괦�Ƿ��иò�ĸ�ͼ�飬����У������ƶ�
	unsigned int gid1 = m_soilLayer->getTileGIDAt(tileCoord);	//���������ƶ�
	unsigned int gid2 = m_stoneLayer->getTileGIDAt(tileCoord);	//ʯͷ�����ƶ�
	unsigned int gid3 = m_borderLayer->getTileGIDAt(tileCoord);	//�߽粻���ƶ�
	if (gid1 > 0 || gid2>0 || gid3>0) return true;
	return false;
}

bool MyMapBall::bGravityAir(Vec2 position)		//�������������λ���п��������̫�㣬��ô�������
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_airLayer->getTileGIDAt(tileCoord);
	if (gid > 0) return true;
	return false;
}

void MyMapBall::isRemoviable(cocos2d::Vec2 position)  //������������괦������������ֱ���Ƴ���û���򲻱�
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_soilLayer->getTileGIDAt(tileCoord);
	if (gid > 0)
	{
		m_soilLayer->removeTileAt(tileCoord);
	}
}

bool MyMapBall::isTouchDiamond(Vec2 position)
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_diamondLayer->getTileGIDAt(tileCoord);
	if (gid > 0)	return true;
	else return false;
}

bool MyMapBall::isTouchFinalLadder(cocos2d::Vec2 position)
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_ladderLayer->getTileGIDAt(tileCoord);
	if (gid > 0)	return true;
	else return false;
}


bool MyMapBall::bGravityEther(Vec2 position)		//�������������λ���п����㣬��ô�������
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_etherLayer->getTileGIDAt(tileCoord);
	if (gid > 0) return true;
	return false;
}

