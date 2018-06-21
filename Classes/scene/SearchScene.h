#ifndef SearchScene_H
#define SearchScene_H
#include <iostream>
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
#include "../NetWork/MessageCode.h"
#include "../NetWork/Client.h"
#include "RoomScene.h"
using namespace ui;
/**
*   @brief  ��������
*/
class SearchScene : public cocos2d::Layer
{
private:

	Sprite*             _room_list_bg;          ///�����б�ı���ͼƬ����
	std::string         _player_name;           ///�������
	Vector<Button*>     button_list;            ///�洢���г��ķ������

public:
	/**
	* @brief    ���������б���
	*/
	static cocos2d::Scene* createScene(Client* client, std::string _playerName);

	/**
	* @brief    �Զ���ĳ�ʼ������
	*
	* @return   ��ʼ���Ľ��
	*        -<em>false</em>    ��ʼ��ʧ��
	*        -<em>true</em>     ��ʼ���ɹ�
	*/
	virtual bool init();

	/**
	* @brief    �ر���Ϸ�Ļص�����
	*
	* @param    psender         ָ��, ָ����ûص�������CCObject
	*
	*/
	void menuCloseCallback(cocos2d::Ref* pSender);

	/**
	* @brief    ÿ֡�����øú���
	*
	* @param    delta           update��Ĭ�ϲ���
	*
	*/
	void update(float delta);

	/**
	* @brief    ��create()�����init(), ������Ӧ�������cocos�Զ��ڴ����ϵͳ
	*/
	CREATE_FUNC(SearchScene);
};
#endif /*SearchScene_H*/
