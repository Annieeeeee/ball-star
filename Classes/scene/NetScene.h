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
* @brief    网络选择界面
*        互联网->client启动
*        局域网->client(&server)启动
*        创建房间/搜索房间
*           Room***Search
*/
class NetMenu : public cocos2d::Layer, public EditBoxDelegate
{
protected:
	std::string     _playerName;            ///玩家名称

	Button *        _nameStartButton;       ///指向输入框的指针
	Button *        _pleaseStartButton;     ///指向确认输入按钮的指针

public:
	/**
	* @brief    单例对象创建函数
	*
	* @return   指向网络菜单场景的指针
	*/
	static cocos2d::Scene* createScene();

	/**
	* @brief    自定义的初始化函数
	*
	* @return   初始化的结果
	*        -<em>false</em>    初始化失败
	*        -<em>true</em>     初始化成功
	*/
	virtual bool init();
	/**
	* @brief    关闭游戏的回调函数
	*
	* @param    psender         指针, 指向调用回调函数的CCObject
	*
	*/
	void menuCloseCallback(cocos2d::Ref* pSender);

	/**
	* @brief    检测输入框的变化
	*
	* @param    psender         指针, 指向调用回调函数的CCObject
	* @param    type            要响应的事件类型
	*/
	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);

	/**
	* @brief    当动作开始的时候调用的函数
	*
	* @param    editBox         指针，指向被操作的输入框对象
	*/
	void editBoxEditingDidBegin(EditBox* editBox);

	/**
	* @brief    当离开输入框的时候调用的函数
	*
	* @param    editBox         指针，指向被操作的输入框对象
	*/
	void editBoxEditingDidEnd(EditBox* editBox);

	/**
	* @brief    当输入框中内容被改变的时候调用的函数
	*
	* @param    editBox         指针，指向被操作的输入框对象
	* @param    text            输入的字符串
	*/
	void editBoxTextChanged(EditBox* editBox, const std::string& text);

	/**
	* @brief    按下回车时调用的函数
	*
	* @param    editBox         指针，指向被操作的输入框对象
	*/
	void editBoxReturn(EditBox* editBox);
	

	/**
	* @brief    在create()后调用init(), 并让相应对象加入cocos自动内存管理系统
	*/
	CREATE_FUNC(NetMenu);
};
#endif /*NetScene_H*/
