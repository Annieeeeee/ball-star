#pragma once
#include"cocos2d.h"
#include<iostream>
#include"MyMap.h"
#include<vector>
#include<array>
#include"LittleSillyBox.h"
USING_NS_CC;
class HelpScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Sprite *mySprite;
	MyMap *m_map;
	virtual bool init();
	void sceneBackCallBack(cocos2d::Ref* pSender);
	void update(float delta);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	Vec2 pos2;
	void keyPressedDuration(EventKeyboard::KeyCode code);
	CREATE_FUNC(HelpScene);
	struct Bcount
	{
		int w = 0, s = 0, d = 0, a = 0;
	};
	Bcount count;
	float x, y;
	
	std::vector<float> row;
	std::vector<float> col;
	int bones;
	bool isSpriteDead;
	bool isMove(float row,float col);
	float curPositionX, curPositionY;
	bool isMovible;
};

