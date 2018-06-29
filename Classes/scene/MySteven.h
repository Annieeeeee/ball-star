#pragma once
#include"cocos2d.h"
USING_NS_CC;
class MySteven :public cocos2d::Sprite
{
public:
	int steven;
	MySteven();
	static MySteven* create(const char* filename);
	MySteven(const char* filename);
	cocos2d::Sprite* mySprite;
	void update(float delta);
	int m_life;
	int whoIam();
	void isdead(bool deadOrAlive);
};
