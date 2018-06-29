#include "MySteven.h"
#include"cocos2d.h"

USING_NS_CC;

MySteven::MySteven()
{

}

MySteven* MySteven::create(const char* filename)
{
	MySteven* sprite = new MySteven(filename);
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

MySteven::MySteven(const char* filename)
{
	mySprite = Sprite::create(filename);
	m_life = 1;
	scheduleUpdate();
}


void MySteven::update(float delta)
{
	if (m_life == 0)
	{
		removeFromParent();
		return;
	}
}

int MySteven::whoIam()
{
	steven = 1;
	return steven;
}

void MySteven::isdead(bool deadOrAlive)
{
	m_life = 0;
}