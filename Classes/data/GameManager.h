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
	std::string     _role;                  // ����Ľ�ɫ
	Player* _playerManager;
											//Player*         _playerManager;         // PlayerManager����
	Vec2            _playerCurrentPosition; // ���ﵱǰ��λ��
	std::string     _command;               // ��ȡ��Զ����Ϣ
	std::string     _code;                  // �������ߵķ���
	std::string     _playerName;            // ����Name
public:
	/**
	* @brief Manager��create����
	* @param mapIndex ����1
	* @param role ����2
	* @param scene ����3
	* @param Game  scene(Game���������,���Դ˶�GameScene���и���)
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
	* @brief ÿһ֡����GameScene���и���
	* @param int   delta
	* @param Game  scene(Game���������,���Դ˶�GameScene���и���)
	* @return  void
	*/
	void updatePerFrame(int delta, Game &scene);
	/**
	* @brief ��ʼ��player
	* @param player  ����1 ��ʼ��������
	* @param scene ����2 Game���������,���Դ˶�GameScene���и���
	*
	* @return void
	*/
	void playerInit(std::string player, Game & scene);
	/**
	* @brief �����player��������״̬���иı�
	* @param delta ����1 updateĬ�ϲ���
	* @param scene ����2 Game���������,���Դ˶�GameScene���и���
	*
	* @return void
	*/
	void executePlayer(int delta, Game & scene);
	/**
	* @brief ��ȡ��ȡ��ָ��
	*
	* @return int
	*/
	void readCommand();
	/**
	* @brief ��������ĵ�����
	* @param role ����1 ���������
	* @return void
	*/
	void setRole(std::string role) { _role = role; }
	/**
	* @brief ��ȡ���������
	*
	* @return std::string
	*/
	std::string getRole() { return _role; }
};
#endif /*GAMEMANAGER_H*/
