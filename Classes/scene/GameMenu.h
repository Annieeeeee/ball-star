/************
*Hello,World*
************/
#ifndef GameMenu_H
#define GameMenu_H
#include "cocos2d.h"
#include "HelpScene.h"
#include "NetScene.h"

USING_NS_CC;
/**
* 	@brief  ���¾ʹ����￪ʼ��
*           ��Ȼ�ⲿ����������ѧ���
*           anyway��nice to meet u.
*           �ر���л�������ӣ�������������ѧ��
*           ʮ�ָ�л�˹����а����ҵĳ�ͬѧ
*           û�����Ǿ�û�������Ŀ
*                 GameMenu
*/
class GameMenu :public Layer
{
public:
	/**
	* 	@brief  �������˵�����
	*/
	static Scene* createScene();
	/**
	* @brief  	�Զ����initial����, �򳡾�����Ӹ�����ť��������صĻص�����
	*/
	virtual bool init();
	/**
	* @brief  	��create()�����init(), ������Ӧ�������cocos�Զ��ڴ����ϵͳ
	*/
	CREATE_FUNC(GameMenu);
};
#endif /*GameMenu_H*/
