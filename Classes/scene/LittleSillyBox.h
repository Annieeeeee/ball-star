#pragma once
#include"cocos2d.h"
#include"MyMap.h"
#include<vector>
USING_NS_CC;
class LittleSillyBox:public cocos2d::Sprite
{
public:
	struct BKeyPressed
	{
		bool w = false, s = false, d = false, a = false;
	};
	LittleSillyBox();
	static LittleSillyBox* create(const char* filename);
	LittleSillyBox(const char* filename);
	cocos2d::Sprite* mySprite;
	void update(float delta);
	int m_life;
	CREATE_FUNC(LittleSillyBox);
};

