#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <iostream>
#include "cocos2d.h"
#include "../Scene/GameLocalScene.h"
#include "../Data/Role.h"
#include<stdio.h>
USING_NS_CC;
class Game;
class Player :public cocos2d::Node
{
protected:

	std::string         _role;// 玩家的角色类型
	//Vec2                _bornPosition[2];// 玩家的出生位置
public:
	/**
	* @brief Player的create函数
	* @param role  人物角色类型
	* @param scene Game场景
	* @return  Player*
	*/
	static Player* create(std::string role, Game &scene)
	{
		Player *player = new Player();
		if (player)
		{
			player->setRole(role);
			player->initLocalPlayer(role, scene);
			player->initRemotePlayer(role, scene);

			return player;
		}
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	/**
	* @brief 初始化本地人物
	* @param roleName  人物角色类型
	* @param scene Game场景
	* @return  void
	*/
	void   initLocalPlayer(std::string roleName, Game &scene);
	/**
	* @brief 初始化远程人物
	* @param oleName  人物角色类型
	* @param scene Game场景
	* @return  void
	*/
	void    initRemotePlayer(std::string roleName, Game& scene);
	/**
	* @brief 每一帧来更新Player信息
	* @param delta Update默认参数
	* @param scene Game场景
	* @patam code 按键信息
	* @return  void
	*/
	void     updatePlayerPerFrame(int delta, Game &scene, EventKeyboard::KeyCode code);
	/**
	* @brief 设置人物角色
	* @param role  人物角色类型
	* @return void
	*/
	void     setRole(std::string role) 
	{
		_role = role; 
	}
	/**
	* @brief 设置玩家死亡
	* @param roleName  人物角色
	* @param scene     Game场景
	* @return  void
	*/
	void     setPlayerDied(std::string roleName, Game &scene);
	/**
	* @brief 得到角色信息
	* @return  string
	*/
	std::string getRole() 
	{ 
		return _role; 
	}
	/**
	* @brief 移动操作
	* @return  void
	*/
	void keyPressedDuration(EventKeyboard::KeyCode code,Game &scene);//Control
	/**
	* @brief 技能操作
	* @return  void
	*/
	void removeDuration(EventKeyboard::KeyCode code,Game& scene);//Control

	
};
#endif /*PLAYERCONTROLLER_H*/