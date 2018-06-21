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
* 	@brief  故事就从这里开始啦
*           虽然这部分是我最后才学会的
*           anyway，nice to meet u.
*           特别鸣谢：宋天佑，李坤，孙允鑫学长
*           以及此过程中帮助我的常同学
*           没有他们就没有这个项目
*                 GameMenu
*/
class GameMenu :public Layer
{
public:
	/**
	* 	@brief  创建主菜单场景
	*/
	static Scene* createScene();
	/**
	* @brief  	自定义的initial函数, 向场景中添加各个按钮并定义相关的回调函数
	*/
	virtual bool init();
	/**
	* @brief  	在create()后调用init(), 并让相应对象加入cocos自动内存管理系统
	*/
	CREATE_FUNC(GameMenu);
};
#endif /*GameMenu_H*/
