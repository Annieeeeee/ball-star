#ifndef _GameManager_h_
#define _GameManager_h_

#include <iostream>
#include "cocos2d.h"
#include "json/document.h"
#include "PlayerController.h"
#include "PopController.h"

USING_NS_CC;


/**
* @brief Manager�� �̳���Node
* ��ȡ������Message�Լ�����Message��������в���
*/
class Manager :public cocos2d::Node
{

protected:

	std::string     _role;                  /// ����Ľ�ɫ
	Player*         _playerManager;         /// PlayerManager����
	Vec2            _playerCurrentPosition; /// ���ﵱǰ��λ��
	Vec2            _bornPosition[2];       /// ���������λ��
	std::string     _command;               /// ��ȡ��Զ����Ϣ
	std::string     _code;                  /// �������ߵķ���
	std::string     _playerName;            /// ����Name

public:

	/**
	* @brief Manager��create����
	* @param mapIndex ����1
	* @param role ����2
	* @param scene ����3
	* @param Game  scene(Game���������,���Դ˶�GameScene���и���)
	* @return  nullptr
	*/

	static Manager* create(std::string role, Game &scene��int actor)
	{
		Manager *sceneManager = new Manager();
		if (sceneManager)
		{
			sceneManager->setRole(role);
			sceneManager->playerInit(role, scene,int actor);

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
	* @brief ִ��Player�����ƶ��Ķ���
	* @param code  ����1 �ƶ��ķ���
	* @param scene ����2 Game���������,���Դ˶�GameScene���и���
	*
	* @return void
	*/
	bool isExecuteForeverMove(EventKeyboard::KeyCode code, Game& scene);
	/**
	* @brief ��ʼ��player
	* @param player  ����1 ��ʼ��������
	* @param scene ����2 Game���������,���Դ˶�GameScene���и���
	*
	* @return void
	*/
	void playerInit(std::string player, Game & scene,int actor);

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




#endif /* _GameManager_h_ */
