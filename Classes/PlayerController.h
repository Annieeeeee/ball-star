#ifndef _playerController_h_
#define _playerController_h_
#include <iostream>
#include "cocos2d.h"
#include "json/document.h"
#include <stdio.h>
#include "../Data/Role.h"
#include "../Scene/GameScene.h"
USING_NS_CC;
/**
* @brief Player�� �̳���cocos2d:cocos2d
* ����Player�Ŀ�����,������Զ����һ��Ǳ������,���Ƕ������һ����ͬ�Ĳٿػ���,����ָ����вٿ�,����������ν�Ĵ�����
*/
class Player :public cocos2d::Node
{
protected:

	std::string         _role;                                                           /// ��ҵĽ�ɫ����
	int                  _actor;
	Vec2                _bornPosition[2];                                                /// ��ҵĳ���λ��
public:
	/**
	* @brief Player��create����
	* @param role  �����ɫ����
	* @param scene Game����
	* @return  Player*
	*/
	static Player* create(std::string role, Game &scene, int actor)
	{
		Player *player = new Player();
		if (player)
		{
			player->setRole(role);
			player->setActor(actor);
			player->initLocalPlayer(role, scene);
			player->initRemotePlayer(role, scene);

			return player;
		}
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	/**
	* @brief ��ʼ����������
	* @param roleName  �����ɫ����
	* @param scene Game����
	* @return  void
	*/
	void   initLocalPlayer(std::string roleName, Game &scene);
	/**
	* @brief ��ʼ��Զ������
	* @param oleName  �����ɫ����
	* @param scene Game����
	* @return  void
	*/
	void    initRemotePlayer(std::string roleName, Game& scene);
	/**
	* @brief ÿһ֡������Player��Ϣ
	* @param delta UpdateĬ�ϲ���
	* @param scene Game����
	* @patam code ������Ϣ
	* @return  void
	*/
	void     updatePlayerPerFrame(int delta, Game &scene, EventKeyboard::KeyCode code);
	/**
	* @brief ���������ɫ
	* @param role  �����ɫ����
	* @return void
	*/
	void     setRole(std::string role) { _role = role; }
	/**
	* @brief �����������
	* @param roleName  �����ɫ
	* @param scene     Game����
	* @return  void
	*/
	void     setPlayerDied(std::string roleName, Game &scene);
	/**
	* @brief �õ���ɫ��Ϣ
	* @return  string
	*/
	std::string       getRole() { return _role; }

	void     setActor(int actor) { _actor = actor; }
	int     getActor() { return _actor; }

};
#endif /*PLAYER_CONTROLLER_H*/
