#ifndef HelpSelect_H
#define HelpSelect_H
#include "cocos2d.h"
#include "GameMenu.h"
#include "HelpScene.h"
#include "HelpSceneBall.h"
USING_NS_CC;
/**
* 	@brief  3��demo
*           ������ȥ��Χ�Ǵ���ս
*           ����mode�Ĳ���ָ��
*/
class HelpSelect :public Layer
{
public:
	/**
	* 	@brief  ����ѡ�񳡾�
	*/
	static Scene* createScene();
	/**
	* @brief  	�Զ����initial����, �򳡾�����Ӹ�����ť��������صĻص�����
	*/
	virtual bool init();
	/**
	* @brief  	��create()�����init(), ������Ӧ�������cocos�Զ��ڴ����ϵͳ
	*/
	CREATE_FUNC(HelpSelect);
};
#endif /*HelpSelect_H*/
