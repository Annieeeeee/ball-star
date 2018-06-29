#pragma once
#include "cocos2d.h"

class MyMapBall :public cocos2d::TMXTiledMap
{
public:
	static MyMapBall * create(const std::string& tmxFile);
	MyMapBall();
	bool init();
	bool bnoMove(cocos2d::Vec2 position);
	bool bGravityAir(cocos2d::Vec2 position);
	bool bGravityEther(cocos2d::Vec2 position);
	void isRemoviable(cocos2d::Vec2 position);
	bool isTouchDiamond(cocos2d::Vec2 position);
	bool isTouchFinalLadder(cocos2d::Vec2 position);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	cocos2d::Vec2 positionFromTileCoord(cocos2d::Point position);
	int m_gid_soil, m_gid_stone, m_gid_air, m_gid_border, m_gid_diamond, m_gid_ladder, m_gid_ether;
	cocos2d::TMXLayer *m_soilLayer,
		*m_stoneLayer, *m_airLayer, *m_borderLayer, *m_diamondLayer, *m_ladderLayer, *m_etherLayer;
};


