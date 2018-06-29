#ifndef HelpSelect_H
#define HelpSelect_H
#include "cocos2d.h"
#include "GameMenu.h"
#include "HelpScene.h"
#include "HelpSceneBall.h"
USING_NS_CC;
/**
* 	@brief  3个demo
*           纪念死去的围城大作战
*           两个mode的操作指南
*/
class HelpSelect :public Layer
{
public:
	/**
	* 	@brief  创建选择场景
	*/
	static Scene* createScene();
	/**
	* @brief  	自定义的initial函数, 向场景中添加各个按钮并定义相关的回调函数
	*/
	virtual bool init();
	/**
	* @brief  	在create()后调用init(), 并让相应对象加入cocos自动内存管理系统
	*/
	CREATE_FUNC(HelpSelect);
};
#endif /*HelpSelect_H*/
