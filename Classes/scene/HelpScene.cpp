#include<iostream>
#include<vector>
#include<array>
#include "HelpScene.h"
#include"cocos2d.h"
#include"MyMap.h"
#include"LittleSillyBox.h"
#include"GameMenu.h"
#include<cmath>
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene* HelpScene::createScene()
{
	return HelpScene::create();
}

bool HelpScene::init()
{
		if (!Scene::init())
		{
			return false;
		}

		
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//创建返回的按钮，并在该位置加入文本
	//	auto back = MenuItemImage::create(
	//		"button_normal.png",
	//		"button_selected.png",
		//	CC_CALLBACK_1(HelpScene::sceneBackCallBack, this));

		//float X = origin.x + back->getContentSize().width /2;
	//	float Y = origin.y + visibleSize.height  - back->getContentSize().height /2;
	//	back->setPosition(Vec2(X, Y));

	//	auto label = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 24);
	//	label->setPosition(Vec2(X, Y));
	//	this->addChild(label, 1001);

	//	auto menu = Menu::create(back, NULL);
	//	menu->setPosition(Vec2::ZERO);
	//	this->addChild(menu, 1000);
		
		//创建地图
		m_map = MyMap::create("map.tmx");
		m_map->init();
		this->addChild(m_map, 0);

		//创建主角精灵
		mySprite = LittleSillyBox::create("N1.png");
		mySprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		mySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
		this->addChild(mySprite, 2,1);
		bones = 1;
		isSpriteDead = true;
		

		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event)
		{
			
			keys[EventKeyboard::KeyCode::KEY_A] = false, keys[EventKeyboard::KeyCode::KEY_S] = false, keys[EventKeyboard::KeyCode::KEY_D] = false,keys[EventKeyboard::KeyCode::KEY_W]=false;
			keys[keyCode] = true;
		};
		listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event * event)
		{
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		
		

		//启用帧更新函数，会自动调用下面的update函数
		scheduleUpdate();
		auto return_button = Button::create("back_button.png");

		return_button->cocos2d::Node::setScale((visibleSize.width * 0.1 / return_button->getContentSize().width));
		return_button->setPosition(Vec2(origin.x + visibleSize.width - return_button->getContentSize().width / 2, origin.y + return_button->getContentSize().height / 2));
		return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});

		this->addChild(return_button);

		return true;
}

//返回按钮的回调函数
void HelpScene::sceneBackCallBack(Ref* pSender)
{
	auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());
	Director::getInstance()->replaceScene(transition);
}

//更新函数，检测wasd是否被按下，默认似乎是0.1s
void HelpScene::update(float delta)
{
	if (isSpriteDead)
	{
		Node::update(delta);
		auto a = EventKeyboard::KeyCode::KEY_A, d = EventKeyboard::KeyCode::KEY_D, w = EventKeyboard::KeyCode::KEY_W, s = EventKeyboard::KeyCode::KEY_S;
		if (isKeyPressed(a)) {
			keyPressedDuration(a);
		}
		else if (isKeyPressed(d)) {
			keyPressedDuration(d);
		}
		else if (isKeyPressed(w)) {
			keyPressedDuration(w);
		}
		else if (isKeyPressed(s)) {
			keyPressedDuration(s);
		}
	}
}

//检测按钮是否被按下，按下后存到map里
bool HelpScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else
	{
		return false;
	}
}

//当wasd被按下后会执行什么动作
void HelpScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	float offsetX = 0, offsetY = 0;
	Vec2 pos;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = -4;
		pos = Vec2(mySprite->getPosition().x  + offsetX - mySprite->getContentSize().width / 2, mySprite->getPosition().y  + offsetY );
		curPositionX = mySprite->getPosition().x + offsetX - mySprite->getContentSize().width / 2;
		curPositionY = mySprite->getPosition().y + offsetY;
		count.a++;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = 4;
		pos = Vec2(mySprite->getPosition().x   + mySprite->getContentSize().width / 2, mySprite->getPosition().y  + offsetY );
		curPositionX = mySprite->getPosition().x + mySprite->getContentSize().width / 2;
		curPositionY = mySprite->getPosition().y + offsetY;
		count.d++;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		offsetY = 4;
		pos = Vec2(mySprite->getPosition().x  + offsetX , mySprite->getPosition().y   + mySprite->getContentSize().height / 2);
		curPositionX = mySprite->getPosition().x + offsetX;
		curPositionY = mySprite->getPosition().y + mySprite->getContentSize().height / 2;
		count.w++;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		offsetY = -4;
		pos = Vec2(mySprite->getPosition().x  + offsetX , mySprite->getPosition().y  - mySprite->getContentSize().height / 2);
		curPositionX = mySprite->getPosition().x + offsetX;
		curPositionY = mySprite->getPosition().y - mySprite->getContentSize().height / 2;
		count.s++;
		break;
	default:
		offsetY = offsetX = 0;
		pos = Vec2(0, 0);
		break;
		
	}

	if (count.w == 4 || count.a == 4 || count.s == 4 || count.d == 4)
	{
		x = x - 3 * offsetX;
		y = y - 3 * offsetY;
		pos2 = Vec2(x, y);
		bones++;
		auto sprite = LittleSillyBox::create("N1_PATH.png");
		sprite->setPosition(pos2);
		this->addChild(sprite, 1,bones);

		count.w = 0, count.a = 0, count.s = 0, count.d = 0;
	}

	isMovible = isMove(curPositionX, curPositionY);

	if (!m_map->bnoMove(pos) && isMovible)
	{
		mySprite->setPosition(Vec2(mySprite->getPosition().x + offsetX, mySprite->getPosition().y + offsetY));
		x = mySprite->getPosition().x;
		y = mySprite->getPosition().y;
	}
	else
	{
		for (int i = 1; i <= bones; i++)
		{
			removeChildByTag(i);
		}
		isSpriteDead = false;

	}


}


bool HelpScene::isMove(float row,float col)
{
	float distanceX,distanceY;
	for (int i = 2; i <= bones; i++)
	{
		auto it = getChildByTag(i);
		distanceX = abs(row - it->getPosition().x);
		distanceY = abs(col - it->getPosition().y);
		if (distanceX > 15 || distanceY > 15)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}