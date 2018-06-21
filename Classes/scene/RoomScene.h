#ifndef _RoomScene_h_
#define _RoomScene_h_

#include <iostream>
#include "cocos2d.h"
#include "../Data/LevelData.h"
//#include "GameScene.h"
#include "../NetWork/Client.h"
#include "../Data/ExternData.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
#include "../NetWork/MessageCode.h"
#include "NetScene.h"
//--------
#include "GameMenu.h"
//--------
using namespace ui;
/**
* @brief **ROOM**
*        �����Ӱ�˹��
* ���﷿����Ϣ����ʵʱ����,��ҿ����������
*/
class RoomScene : public cocos2d::Layer
{
protected:
	Vector<Sprite*>     _exist_player;             ///Ŀǰ�������Player
	Sprite*             _room_ptr;                 ///���䱳��
	std::string         _owner_player_name;        ///����������
	PlayerData*         _owner_player_data;        ///�����ĸ�����Ϣ
	Button*             _start_game_button;        ///��ʼ��Ϸ��ť
	std::string         _chatString;               ///������Ϣ
	TextField*          _chatWindow;               ///���������
public:
	LevelData*          _game_data;                ///��Ϸ��Ϣ

	/**
	* @brief                    Room��static create����
	* @param    c               �ͻ���ָ��
	* @param    mode            �����or�ͻ���
	* @param    _playerName     �������
	* @return   Scene*
	*/
	static cocos2d::Scene* createScene(Client* c, int mode, std::string _playerName);

	/**
	* @brief ��һЩ��ʼ���Ĺ���
	* @return  bool
	*/
	virtual bool init();
	/**
	* @brief �������������
	* @param type �������
	* @param pSender ��Ϣ����ָ��
	* @return  void
	*/
	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);
	/**
	* @brief ��ʼ�������
	* @return  void
	*/
	bool initForServer(void);
	/**
	* @brief ��ʼ���ͻ���
	* @return  void
	*/
	bool initForClient(void);
	/**
	* @brief �ҵ����ID
	* @return  int
	*/
	int  findPlayerId();
	/**
	* @brief ÿ֡�Է�����и���
	* @return  void
	*/
	void update(float delta);

	CREATE_FUNC(RoomScene);
};

#endif /* _RoomScene_h_ */
