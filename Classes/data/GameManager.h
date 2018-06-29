#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include"../Scene/GameLocalScene.h"
#include "cocos2d.h"
#include "PlayerController.h"
USING_NS_CC;
class Game;
class Player;
class Manager :public cocos2d::Node
{
	std::string     _role;                  // 人物的角色
	Player* _playerManager;
											//Player*         _playerManager;         // PlayerManager对象
	Vec2            _playerCurrentPosition; // 人物当前的位置
	std::string     _command;               // 读取的远程信息
	std::string     _code;                  // 人物行走的方向
	std::string     _playerName;            // 人物Name
public:
	/**
	* @brief Manager的create函数
	* @param mapIndex 参数1
	* @param role 参数2
	* @param scene 参数3
	* @param Game  scene(Game对象的引用,并以此对GameScene进行更新)
	* @return  nullptr
	*/

	static Manager* create(std::string role, Game &scene)
	{
		Manager *sceneManager = new Manager();
		if (sceneManager)
		{
			sceneManager->setRole(role);
			sceneManager->playerInit(role, scene);

			return sceneManager;
		}
		CC_SAFE_DELETE(sceneManager);
		return nullptr;
	}
	/**
	* @brief 每一帧对于GameScene进行更新
	* @param int   delta
	* @param Game  scene(Game对象的引用,并以此对GameScene进行更新)
	* @return  void
	*/
	void updatePerFrame(int delta, Game &scene);
	/**
	* @brief 初始化player
	* @param player  参数1 初始化的人物
	* @param scene 参数2 Game对象的引用,并以此对GameScene进行更新
	*
	* @return void
	*/
	void playerInit(std::string player, Game & scene);
	/**
	* @brief 具体对player的所处的状态进行改变
	* @param delta 参数1 update默认参数
	* @param scene 参数2 Game对象的引用,并以此对GameScene进行更新
	*
	* @return void
	*/
	void executePlayer(int delta, Game & scene);
	/**
	* @brief 读取收取的指令
	*
	* @return int
	*/
	void readCommand();
	/**
	* @brief 设置人物的的种类
	* @param role 参数1 人物的种类
	* @return void
	*/
	void setRole(std::string role) { _role = role; }
	/**
	* @brief 读取人物的种类
	*
	* @return std::string
	*/
	std::string getRole() { return _role; }
};
#endif /*GAMEMANAGER_H*/
