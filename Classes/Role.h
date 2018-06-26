#ifndef ROLE_H
#define ROLE_H
#include <iostream>
#include <string>
#include "cocos2d.h"
USING_NS_CC;
class Role : public cocos2d::Sprite
{
private:
	std::string     _roleName;                         ///人物的角色
	std::string     _playerName;                       ///玩家的姓名
	int             _actor;                            ///玩家扮演的角色
	bool            _isDead = false;                   ///玩家是否死亡
	bool            _alreadyDead = false;              ///玩家是否真正的死亡
	Vec2            _tileSize;                         ///瓦片地图的大小
	bool            _isHost;                           ///玩家是否是主机
	std::map<EventKeyboard::KeyCode, bool> _keys;      ///玩家的按键
	std::map<EventKeyboard::KeyCode, bool> _realKeys;  ///玩家的真正按键
public:
	/**
	* @brief Role的create函数
	* @param filename文件的名字
	* @return  Role*
	*/
	static Role* create(const std::string& filename)
	{
		Role *sprite = new Role();
		if (sprite && sprite->initWithFile(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	/**
	* @brief Role的create函数
	* @param filename文件的名字
	* @return  Role*
	*/
	static Role* createWithSpriteFrameName(const std::string& filename)
	{
		Role *sprite = new Role();
		if (sprite && sprite->initWithSpriteFrameName(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	/**
	* @brief 设置人物已经死亡
	* @return  void
	*/
	void setAlreadyDead()
	{
		_alreadyDead = true;
	}
	/**
	* @brief 得到玩家是否已经死亡的信息
	* @return bool
	*/
	bool getAlreadyDead()
	{
		return _alreadyDead;
	}
	/**
	* @brief 设置人物独立的按键,这样方便对每个人进行操控
	* @param code 按键的位置
	* @param isPress 是按下了还是没有按下
	* @return  void
	*/
	void setKeys(EventKeyboard::KeyCode code, bool isPress)
	{
		_keys[code] = isPress;
		_realKeys[code] = !isPress;
	}
	/**
	* @brief 设置人物独立的按键,这样方便对每个人进行操控（真正按键）
	* @param code 按键的位置
	* @param isPress 是按下了还是没有按下
	* @return  void
	*/
	void setRealKeys(EventKeyboard::KeyCode code, bool isPress)
	{
		_realKeys[code] = isPress;
	}
	/**
	* @brief 得到人物的按键信息
	* @param code 按键的位置
	* @return bool
	*/
	bool getKeys(EventKeyboard::KeyCode code)
	{
		return _keys[code];
	}
	/**
	* @brief 得到人物真正的的按键信息
	* @param code 按键的位置
	* @return bool
	*/
	bool getRealKeys(EventKeyboard::KeyCode code)
	{
		return _realKeys[code];
	}
	/**
	* @brief 设置人物死亡
	* @return void
	*/
	void setPlayerDead()
	{
		_isDead = true;
	}
	/**
	* @brief 返回人物是否人物死亡
	* @return void
	*/
	bool isDead()
	{
		return _isDead;
	}
	/**
	* @brief 设置人物的角色名字
	* @param name 名字
	* @return void
	*/
	void setRoleName(std::string name)
	{
		_roleName = name;
	}
	/**
	* @brief 得到人物的角色名字
	* @return std::string
	*/
	std::string getRoleName()
	{
		return _roleName;
	}
	/**
	* @brief 设置玩家姓名
	* @param playerName 玩家姓名
	* @return void
	*/
	void setPlayerName(std::string playerName)
	{
		_playerName = playerName;
	}
	/**
	* @brief 得到玩家姓名
	* @return std::string
	*/
	std::string getPlayerName()
	{
		return _playerName;
	}
	/**
	* @brief 得到玩家坐标位置（string方式得到）
	* @return std::string
	*/
	std::string getPlayerPosition()
	{
		std::stringstream ssx;
		std::stringstream ssy;
		std::string s1 = "(";
		ssx << this->getPositionX();
		std::string positionX = ssx.str();
		std::string s2 = ",";
		ssy << this->getPositionY();
		std::string positionY = ssy.str();
		std::string s3 = ")";

		return s1 + positionX + s2 + positionY + s3;

	}
	/**
	* @brief 设置人物扮演
	* @param actor 扮演角色
	* @return void
	*/
	void setActor(int actor)
	{
		_actor=actor;
	}
	/**
	* @brief 得到人物的角色名字
	* @return std::string
	*/
	int getActor()
	{
		return _actor;
	}
};
#endif /*ROLE_H*/