#include<iostream>
#include<vector>
#include "HelpSceneBall.h"
#include"cocos2d.h"
#include"MyMapBall.h"
#include"HelpSelect.h"
#include<cmath>
USING_NS_CC;


Scene* HelpSceneBall::createScene()
{
	return HelpSceneBall::create();
}

bool HelpSceneBall::init()
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

	//�������صİ�ť�����ڸ�λ�ü����ı�
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

	//������ͼ
	m_map = MyMapBall::create("mapNew.tmx");
	m_map->init();
	this->addChild(m_map, 0);
	bonusNumber = 0, ladderNumber = 0;
	rank = 0;		//��ǰ�Ե�����ʯ����
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
	}				//����layer������ʯ��

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
	}				//����layer�������ӣ������Σ�+20�Ǻ���tag��ͻ

					//�������Ǿ��飬��ʱ���ݹ㲥���յĶ�����ͬ���ɲ�ͬ�����Ǿ���
	mySprite = MySteven::create("mySteven.png");
	x = visibleSize.width / 2 + origin.x;
	y = visibleSize.height / 2 + origin.y;
	mySprite->setPosition(Vec2(x, y));
	mySprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(mySprite, 3, 100);		//100ͬ������tag��ͻ

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

	//����֡���º��������Զ����������update����
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

//���ذ�ť�Ļص�����
void HelpSceneBall::sceneBackCallBack(Ref* pSender)
{
	auto transition = TransitionSlideInL::create(0.5, HelpSelect::createScene());
	Director::getInstance()->replaceScene(transition);
}

//���º��������wasd�Ƿ񱻰��£�Ĭ���ƺ���0.1s
void HelpSceneBall::update(float delta)
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
		if (m_map->bGravityAir(curPosition) && !m_map->bnoMove(Vec2(curPosition.x, curPosition.y - 16)))
		{
			mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y - 3.2));
		}				//��⾫�鵱ǰ����λ���Ƿ��ڿ������У�����У��ҽ���û�в����ƶ���ͼ�飬�������ƶ�8���ص㣨ÿ֡��
				/*if ((curPosition.y + 16) >= 700)
				{
				auto Catcher_button = Button::create("buttonBar.png");
				Catcher_button->setScale(1.0);
				Catcher_button->setTitleText("Back");
				Catcher_button->setTitleFontSize(30);
				Catcher_button->setPosition(Vec2(512,384));

				Catcher_button->addTouchEventListener([](Ref* psender, Widget::TouchEventType type) {
				if (type == Widget::TouchEventType::ENDED) {

				auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());//Ҫ�޸ģ�
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
	}			//��⾫�鵱ǰ����λ���Ƿ�����̫���У�����У��ҽ���û�в����ƶ���ͼ�飬�������ƶ�8���ص㣨ÿ֡��

	if (rank == bonusNumber - 1)
	{
		for (int i = 1; i <= ladderNumber; ++i)
		{
			auto it = getChildByTag(i + 20);			//�õ����ӵ�tag,��ʹ������	
			it->setVisible(true);
		}
	}

}

//��ⰴť�Ƿ񱻰��£����º�浽map��
bool HelpSceneBall::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else
	{
		return false;
	}
}

//��wasd�����º��ִ��ʲô����
void HelpSceneBall::keyPressedDuration(EventKeyboard::KeyCode code) {
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
		//�����������ʯ�飬������Ƿ����Σ������������һ��������������
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
		//��������ƶ������ߵ���λ��
		mySprite->setPosition(Vec2(mySprite->getPosition().x + offsetX, mySprite->getPosition().y + offsetY));
	}
}

//�Ƴ����½����������½�����
void HelpSceneBall::removeDuration(EventKeyboard::KeyCode code)
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
	//�Ƴ�����ˢ�º���������myUpdate���������ʱ��Ϊ3��
	schedule(schedule_selector(HelpSceneBall::myUpdate), 3.0f);
}

//�Ƴ���ǰ��layer��������һ��ȫ�µ����
void HelpSceneBall::myUpdate(float tmd)
{
	m_map->removeFromParent();
	m_map = MyMapBall::create("mapNew.tmx");
	m_map->init();
	this->addChild(m_map, 0);
	unschedule(schedule_selector(HelpSceneBall::myUpdate));		//�ر����Ƴ��������õ�ˢ�º���
}




