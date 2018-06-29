#ifndef TIP_1_H
#define TIP_1_H
#include "cocos2d.h"
#include "HelpSelect.h"
#include "HelpScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
/**
* 	@brief  操作说明界面
*/
class Tip_1 :public Layer
{
public:
	/**
	* 	@brief  创建tip
	*/
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Tip_1::create();
		scene->addChild(layer);

		return scene;
	}
	/**
	* @brief  	自定义的initial函数, 向场景中添加各个按钮并定义相关的回调函数
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
	* @brief  	在create()后调用init(), 并让相应对象加入cocos自动内存管理系统
	*/
	CREATE_FUNC(Tip_1);
};
#endif /*TIP_1_H*/
