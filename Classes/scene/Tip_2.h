#ifndef TIP_2_H
#define TIP_2_H
#include "cocos2d.h"
#include "HelpSelect.h"
#include "HelpSceneBall.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
/**
* 	@brief  ����˵������
*/
class Tip_2 :public Layer
{
public:
	/**
	* 	@brief  ����tip
	*/
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Tip_2::create();
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
		auto tipBoard2 = Sprite::create("tip2.png");
		tipBoard2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 * 2));
		this->addChild(tipBoard2);
		//==============================StartButton==================================
		auto start_button = Button::create("start_button.png");
		start_button->setScale(1.0);
		start_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
		
		

		start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {

				auto transition = TransitionSlideInL::create(0.5, HelpSceneBall::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(start_button);
		/*
		//==============================BackButton==================================
		auto back_button = Button::create("back_button_type.png");
		back_button->setScale(1.0);
		back_button->setPosition(Vec2(origin.x + visibleSize.width / 3 * 4, origin.y + visibleSize.height / 4));
		
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
	CREATE_FUNC(Tip_2);
};
#endif /*TIP_2_H*/