#ifndef NetScene_H
#define NetScene_H
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "json/document.h"
#include "GameMenu.h"
#include "ui/CocosGUI.h"
#include "../NetWork/LocalServer.h"
#include "RoomScene.h"
#include "SearchScene.h"
#include "../NetWork/Client.h"
USING_NS_CC_EXT;
using namespace ui;
/**
* @brief    ����ѡ�����
*        ������->client����
*        ������->client(&server)����
*        ��������/��������
*           Room***Search
*/
class NetMenu : public cocos2d::Layer, public EditBoxDelegate
{
protected:
	std::string     _playerName;            ///�������

	Button *        _nameStartButton;       ///ָ��������ָ��
	Button *        _pleaseStartButton;     ///ָ��ȷ�����밴ť��ָ��

public:
	/**
	* @brief    �������󴴽�����
	*
	* @return   ָ������˵�������ָ��
	*/
	static cocos2d::Scene* createScene();

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
	* @brief    ��������ı仯
	*
	* @param    psender         ָ��, ָ����ûص�������CCObject
	* @param    type            Ҫ��Ӧ���¼�����
	*/
	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);

	/**
	* @brief    ��������ʼ��ʱ����õĺ���
	*
	* @param    editBox         ָ�룬ָ�򱻲�������������
	*/
	void editBoxEditingDidBegin(EditBox* editBox);

	/**
	* @brief    ���뿪������ʱ����õĺ���
	*
	* @param    editBox         ָ�룬ָ�򱻲�������������
	*/
	void editBoxEditingDidEnd(EditBox* editBox);

	/**
	* @brief    ������������ݱ��ı��ʱ����õĺ���
	*
	* @param    editBox         ָ�룬ָ�򱻲�������������
	* @param    text            ������ַ���
	*/
	void editBoxTextChanged(EditBox* editBox, const std::string& text);

	/**
	* @brief    ���»س�ʱ���õĺ���
	*
	* @param    editBox         ָ�룬ָ�򱻲�������������
	*/
	void editBoxReturn(EditBox* editBox);
	

	/**
	* @brief    ��create()�����init(), ������Ӧ�������cocos�Զ��ڴ����ϵͳ
	*/
	CREATE_FUNC(NetMenu);
};
#endif /*NetScene_H*/
