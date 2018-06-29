#pragma once
#include"cocos2d.h"
#include<iostream>
#include"MyMapBall.h"
#include<vector>
#include<array>
#include"MySteven.h"
USING_NS_CC;
class HelpSceneBallA :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	MySteven *mySprite;
	MyMapBall *m_map;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//
	float x, y;//����sprite��ʼ����
	int bonusNumber, ladderNumber;//
	int rank;//
	Point curPosition;//

	virtual bool init();
	void sceneBackCallBack(cocos2d::Ref* pSender);
	void update(float delta);
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);

	void keyPressedDuration(EventKeyboard::KeyCode code);//Control
	void removeDuration(EventKeyboard::KeyCode code);//Control
	void myUpdate(float tmd);//д��gameScene�Ҫ�Ƴ����
	CREATE_FUNC(HelpSceneBallA);
};
