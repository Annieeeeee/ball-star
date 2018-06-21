#include "GameMenu.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);

	return scene;
}
bool GameMenu::init()
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
	//==============================StartButton===========================
	auto start_button = Button::create("buttonBar.png");
	start_button->setScale(1.0);
	start_button->setTitleText("Start");
	start_button->setTitleFontSize(30);
	start_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 * 2));

	start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInL::create(0.5, NetMenu::createScene());//add something
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(start_button);
	//==============================HelpButton========================
	auto set_button = Button::create("buttonBar.png");
	set_button->setScale(1.0);
	set_button->setTitleText("Help/DEMO");
	set_button->setTitleFontSize(30);
	set_button->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 3*1 ));

	set_button->addTouchEventListener([](Ref* psender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInL::create(0.5, HelpScene::create());
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(set_button);
	//==============================QuitButton===========================
	auto close_button = Button::create("buttonBar.png");
	close_button->setScale(1.0);
	close_button->setTitleText("Quit");
	close_button->setTitleFontSize(30);
	close_button->setPosition(Vec2(origin.x + visibleSize.width / 4*3, origin.y + visibleSize.height / 3 * 1));

	close_button->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif

		}
	});
	this->addChild(close_button);

}