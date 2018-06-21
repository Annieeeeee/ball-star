#include "LittleSillyBox.h"
#include"cocos2d.h"

USING_NS_CC;

LittleSillyBox::LittleSillyBox()
{
	
}

LittleSillyBox* LittleSillyBox:: create(const char* filename)
{
	LittleSillyBox* sprite = new LittleSillyBox(filename);
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

LittleSillyBox::LittleSillyBox(const char* filename)
{
	mySprite = Sprite::create(filename);
	m_life = 1;
	scheduleUpdate();
}


void LittleSillyBox::update(float delta)
{
	if (m_life == 0)
	{
		removeFromParent();
		return;
	}
}






