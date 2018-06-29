#include<iostream>
#include<vector>
#include "HelpSceneBallA.h"
#include"cocos2d.h"
#include"MyMapBall.h"
#include"HelpSelect.h"
#include<cmath>
USING_NS_CC;


Scene* HelpSceneBallA::createScene()
{
	return HelpSceneBallA::create();
}

bool HelpSceneBallA::init()
{
	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg1.png");
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
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
	m_map = MyMapBall::create("mapSecond.tmx");
	m_map->init();
	this->addChild(m_map, 0);
	bonusNumber = 0, ladderNumber = 0;
	rank = 0;		//当前吃到的钻石块数
	for (int i = 1; i < 34; i++)
	{
		for (int j = 1; j < 24; j++)
		{
			if (m_map->isTouchDiamond(Vec2(16 + i * 32, 16 + j * 32)))
			{
				auto bonus = Sprite::create("myBonus.png");
				bonus->setPosition(Vec2(16 + i * 32, 16 + j * 32));
				bonusNumber++;
				this->addChild(bonus, 1, bonusNumber);
			}
		}
	}				//根据layer生成钻石块

	for (int i = 1; i < 34; i++)
	{
		for (int j = 1; j < 24; j++)
		{
			if (m_map->isTouchFinalLadder(Vec2(16 + i * 32, 16 + j * 32)))
			{
				auto ladder = Sprite::create("myLadderG.png");
				ladder->setPosition(Vec2(16 + i * 32, 16 + j * 32));
				++ladderNumber;
				ladder->setVisible(false);
				this->addChild(ladder, 2, 20 + ladderNumber);
			}
		}
	}				//根据layer生成梯子，并隐形，+20是害怕tag冲突

					//创建主角精灵，到时根据广播接收的东西不同生成不同的主角精灵
	mySprite = MySteven::create("mySteven.png");
	x = visibleSize.width / 2 + origin.x;
	y = visibleSize.height / 2 + origin.y;
	mySprite->setPosition(Vec2(x, y));
	mySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(mySprite, 3, 100);		//100同理，害怕tag冲突

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event)
	{
		keys[keyCode] = true;
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event * event)
	{
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//启用帧更新函数，会自动调用下面的update函数
	scheduleUpdate();
	auto return_button = Button::create("back_button.png");

	return_button->cocos2d::Node::setScale((visibleSize.width * 0.1 / return_button->getContentSize().width));
	return_button->setPosition(Vec2(origin.x + visibleSize.width - return_button->getContentSize().width / 2, origin.y + return_button->getContentSize().height / 2));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(0.5, HelpSelect::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});

	this->addChild(return_button);

	return true;
}

//返回按钮的回调函数
void HelpSceneBallA::sceneBackCallBack(Ref* pSender)
{
	auto transition = TransitionSlideInL::create(0.5, HelpSelect::createScene());
	Director::getInstance()->replaceScene(transition);
}

//更新函数，检测wasd是否被按下，默认似乎是0.1s
void HelpSceneBallA::update(float delta)
{
	Node::update(delta);
	auto a = EventKeyboard::KeyCode::KEY_A, d = EventKeyboard::KeyCode::KEY_D, w = EventKeyboard::KeyCode::KEY_W, s = EventKeyboard::KeyCode::KEY_S, j = EventKeyboard::KeyCode::KEY_J, k = EventKeyboard::KeyCode::KEY_K;
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

	if (isKeyPressed(j))
	{
		removeDuration(j);
	}
	else if (isKeyPressed(k))
	{
		removeDuration(k);
	}

	curPosition = mySprite->getPosition();
	if (mySprite->whoIam() == 1)
	{
		if (m_map->bGravityAir(curPosition) && m_map->bGravityAir(Vec2(curPosition.x, curPosition.y - 9.6)) && !m_map->bnoMove(Vec2(curPosition.x, curPosition.y - 23.8)))
		{
			mySprite->setPosition(Vec2(curPosition.x, curPosition.y - 9.6));
		}				//检测精灵当前所在位置是否处在空气层中，如果有，且脚下没有不可移动的图块，则向下移动8像素点（每帧）
						/*if ((curPosition.y + 16) >= 700)
						{
						auto Catcher_button = Button::create("buttonBar.png");
						Catcher_button->setScale(1.0);
						Catcher_button->setTitleText("Back");
						Catcher_button->setTitleFontSize(30);
						Catcher_button->setPosition(Vec2(512,384));

						Catcher_button->addTouchEventListener([](Ref* psender, Widget::TouchEventType type) {
						if (type == Widget::TouchEventType::ENDED) {

						auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());//要修改！
						Director::getInstance()->replaceScene(transition);

						}
						});
						this->addChild(Catcher_button,3,10000000000);
						}*/
	}
	else
	{
		if (m_map->bGravityEther(curPosition) && !m_map->bnoMove(Vec2(curPosition.x, curPosition.y - 16)))
		{
			mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y - 3.2));
		}
	}			//检测精灵当前所在位置是否处在以太层中，如果有，且脚下没有不可移动的图块，则向下移动8像素点（每帧）

	if (rank == bonusNumber - 1)
	{
		for (int i = 1; i <= ladderNumber; ++i)
		{
			auto it = getChildByTag(i + 20);			//得到梯子的tag,并使其显形	
			it->setVisible(true);
		}
	}

}

//检测按钮是否被按下，按下后存到map里
bool HelpSceneBallA::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else
	{
		return false;
	}
}

//当wasd被按下后会执行什么动作
void HelpSceneBallA::keyPressedDuration(EventKeyboard::KeyCode code) {
	float offsetX = 0, offsetY = 0;
	Vec2 pos;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = -3.2;
		pos = Vec2(mySprite->getPosition().x + offsetX - mySprite->getContentSize().width / 2, mySprite->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = 3.2;
		pos = Vec2(mySprite->getPosition().x + offsetX + mySprite->getContentSize().width / 2, mySprite->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		offsetY = 3.2;
		pos = Vec2(mySprite->getPosition().x, mySprite->getPosition().y + offsetY + mySprite->getContentSize().height / 2);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		offsetY = -3.2;
		pos = Vec2(mySprite->getPosition().x, mySprite->getPosition().y + offsetY - mySprite->getContentSize().height / 2);
		break;
	default:
		offsetY = offsetX = 0;
		pos = Vec2(0, 0);
		break;
	}

	if (!m_map->bnoMove(pos))
	{
		//如果碰到了钻石块，检测其是否隐形，如否，则代表吃了一个，并将其隐形
		if (m_map->isTouchDiamond(pos))
		{
			for (int i = 1; i <= bonusNumber; i++)
			{
				auto it = getChildByTag(i);
				if (abs(pos.x - it->getPosition().x) < 12 && abs(pos.y - it->getPosition().y) < 12)
				{
					if (it->isVisible() == true)
					{
						it->setVisible(false);
						++rank;
					}
				}
			}
		}
		//如果可以移动，则走到该位置
		mySprite->setPosition(Vec2(mySprite->getPosition().x + offsetX, mySprite->getPosition().y + offsetY));
	}
}

//移除左下角泥土或右下角泥土
void HelpSceneBallA::removeDuration(EventKeyboard::KeyCode code)
{
	Vec2 pos;
	pos = mySprite->getPosition();
	Point tileCoord;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_J:
		tileCoord = m_map->tileCoordFromPosition(Vec2(pos.x - 32, pos.y - 16));
		pos = m_map->positionFromTileCoord(tileCoord);
		m_map->isRemoviable(pos);
		break;
	case EventKeyboard::KeyCode::KEY_K:
		tileCoord = m_map->tileCoordFromPosition(Vec2(pos.x + 32, pos.y - 16));
		pos = m_map->positionFromTileCoord(tileCoord);
		m_map->isRemoviable(pos);
		break;
	default:
		pos = Vec2(0, 0);
		tileCoord = pos;
		break;

		keys[code] = false;
	}
	//移除后开启刷新函数，调用myUpdate函数，间隔时间为3秒
	schedule(schedule_selector(HelpSceneBallA::myUpdate), 3.0f);
}

//移除当前旧layer，并建立一个全新的替代
void HelpSceneBallA::myUpdate(float tmd)
{
	m_map->removeFromParent();
	m_map = MyMapBall::create("mapSecond.tmx");
	m_map->init();
	this->addChild(m_map, 0);
	unschedule(schedule_selector(HelpSceneBallA::myUpdate));
}//关闭因移除泥土调用的刷新函数