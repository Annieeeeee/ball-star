#ifndef TIP_1_H
#define TIP_1_H
#include "cocos2d.h"
#include "HelpSelect.h"
#include "HelpScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
/**
* 	@brief  ����˵������
*/
class Tip_1 :public Layer
{
public:
	/**
	* 	@brief  ����tip
	*/
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Tip_1::create();
		scene->addChild(layer);

		return scene;
	}
	/**
	* @brief  	�Զ����initial����, �򳡾�����Ӹ�����ť��������صĻص�����
	*/
	virtual bool init()
	{
		if (!Layer::init())
		{
			return false;
		}
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("bg.png");
		this->addChild(bg);
		bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

		//==============================tipSet==================================
		auto tipBoard1 = Sprite::create("tip1.png");
		tipBoard1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3*2));
		this->addChild(tipBoard1);
		//==============================StartButton==================================
		auto start_button = Button::create("start_button.png");
		start_button->setScale(1.0);
		start_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
		start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {

				auto transition = TransitionSlideInL::create(0.5, HelpScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(start_button);
		/*
		//==============================BackButton==================================
		auto back_button = Button::create("back_button_type.png");
		back_button->setScale(1.0);
		back_button->setPosition(Vec2(origin.x + visibleSize.width / 3 * 4, origin.y + visibleSize.height / 4));
		this->addChild(back_button, 2);
		back_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {

				auto transition = TransitionSlideInL::create(0.5, HelpSelect::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(back_button, 1);
		*/
	}
	/**
	* @brief  	��create()�����init(), ������Ӧ�������cocos�Զ��ڴ����ϵͳ
	*/
	CREATE_FUNC(Tip_1);
};
#endif /*TIP_1_H*/
