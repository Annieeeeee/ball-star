#include "HelpSelect.h"
#include "ui/CocosGUI.h"
#include "Tip_1.h"
#include "Tip_2.h"
#include "Tip_3.h"
USING_NS_CC;
using namespace ui;
Scene* HelpSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpSelect::create();
	scene->addChild(layer);

	return scene;
}
bool HelpSelect::init()
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
	/*
	//==============================tipsSet==================================
	auto tipBoard1 = Sprite::create("tip1.png");
	tipBoard1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(tipBoard1);
	tipBoard1->setVisible(false);

	auto tipBoard2 = Sprite::create("tip2.png");
	tipBoard2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(tipBoard2);
	tipBoard2->setVisible(false);

	auto tipBoard3 = Sprite::create("tip3.png");
	tipBoard3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(tipBoard3);
	tipBoard3->setVisible(false);
	*/
	//==============================EncircleButton===========================
	auto start_button = Button::create("buttonBar.png");
	start_button->setScale(1.0);
	start_button->setTitleText("BoxRunner");
	start_button->setTitleFontSize(30);
	start_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10*7));

	start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(0.5, Tip_1::createScene());
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(start_button);
	//==============================CollectorButton========================
	auto Collect_button = Button::create("buttonBar.png");
	Collect_button->setScale(1.0);
	Collect_button->setTitleText("Collector");
	Collect_button->setTitleFontSize(30);
	Collect_button->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 2 ));

	Collect_button->addTouchEventListener([](Ref* psender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInL::create(0.5, Tip_2::createScene());
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(Collect_button);
	//==============================CatcherButton========================
	auto Catcher_button = Button::create("buttonBar.png");
	Catcher_button->setScale(1.0);
	Catcher_button->setTitleText("Catcher");
	Catcher_button->setTitleFontSize(30);
	Catcher_button->setPosition(Vec2(origin.x + visibleSize.width / 4*3, origin.y + visibleSize.height / 2));

	Catcher_button->addTouchEventListener([](Ref* psender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInL::create(0.5, Tip_3::createScene());//ÒªÐÞ¸Ä£¡
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(Catcher_button);
	//==============================QuitButton===========================
	auto close_button = Button::create("buttonBar.png");
	close_button->setScale(1.0);
	close_button->setTitleText("Quit");
	close_button->setTitleFontSize(30);
	close_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10 * 3));

	close_button->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(close_button);
}