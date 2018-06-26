#ifndef GameScene_H
#define GameScene_H
enum Character
{
	BALL = 1,
    STAR = 2
};
#include <iostream>
#include "../NetWork/Client.h"
#include "cocos2d.h"
#include "json/document.h"
#include "ui/CocosGUI.h"
#include "../Data/ExternData.h"
#include "../Data/LevelData.h"
#include "../Manager/GameManager.h"
#include "../Data/Role.h"
#include "../NetWork/MessageCode.h"
USING_NS_CC;
using namespace ui;
/**
* @brief Game类 继承自cocos2d:Layer
* 这是整个游戏具体实现的类
* 收个类中包括了管理的manager类,包括了本地人物与远程人物,
* 包括了地图的操控,以及坐标的一些转换.
*
* cocos做这种类型的游戏简直太安逸了！安逸到哭泣！
*
* 写出这个模板的人真是神仙
*/
class Game :public Layer
{
private:
	Size              _visibleSize;                       ///视窗大小    
	Vec2              _originSize;                        ///原始大小             
	int               _screenWidth;                       ///视窗宽度
	int               _screenHeight;                      ///视窗高度
	
	LevelData*                _inputData;                 ///选择人物时的数据
	Game*                     _thisScene;                 ///等于This指针
	std::vector<PlayerData>   _playerList;                ///所有远程玩家的信息

	TMXTiledMap*              _tileMap;                   ///瓦片地图
	TMXLayer*                 _diamondLayer;                ///钻石层
	TMXLayer*                 _soilLayer;                ///泥土层，可挖
	TMXLayer*                 _stoneLayer;               ///岩石层，不可挖
	TMXLayer*                 _airLayer;                 ///空气层，Ball在空气中传播
	TMXLayer*                 _etherLayer;                 ///以太层，Star在以太中传播
	TMXLayer*                 _GladderLayer;             ///天梯层
	TMXLayer*                 _borderLayer;             ///边界层
	TMXLayer*                 _borderUpLayer;             ///上界层
	EventKeyboard::KeyCode    _code;                      ///每次按下的键盘信息
	
	/*
	public:
	static MyMapBall * create(const std::string& tmxFile);
	MyMapBall();
	bool init();
	bool bnoMove(cocos2d::Vec2 position);
	bool bGravity(cocos2d::Vec2 position);
	void isRemoviable(cocos2d::Vec2 position);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);//就是坐标
	cocos2d::Vec2 positionFromTileCoord(cocos2d::Point position);
	int m_gid_soil,m_gid_stone,m_gid_air,m_gid_border;
	cocos2d::TMXLayer *m_soilLayer, *m_stoneLayer, *m_airLayer,*m_borderLayer;
	*/

	Vector<Sprite*>           _diamondVector;             ///bonusVector
	Vector<Button*>           _endButton;                 ///结束游戏按钮

	Role*                              _player;           ///当前被操控的玩家
	Role*                              _localPlayer;      ///本地玩家
	Client*                            _client;           ///服务端指针
	std::string                        _localPlayerName;  ///本地玩家的名字
	Player*                            _playerManager;    ///玩家操控Manager
	Manager*                           _sceneManager;     ///scene Manager
	std::map<std::string, Role*>       _remotePlayer;     ///远程玩家的集合

	std::map<std::string, EventKeyboard::KeyCode>      _keyPressesedOrder;   ///键盘按下的按键
	std::map<std::string, EventKeyboard::KeyCode>      _keyReleasedOrder;    ///键盘松开的按键
	std::map<EventKeyboard::KeyCode, std::string>      _keyPressesedOrders;  ///键盘按下的按键
	std::map<EventKeyboard::KeyCode, std::string>      _keyReleasedOrders;   ///键盘松开的按键
	std::map<EventKeyboard::KeyCode, bool>            _keys;                ///记录按键是否按下
	std::queue<std::string>                           _command;             ///每次读取的命令

public:
	int bonusNumber = 0;
	int ladderNumber = 0;
	int rank = 0;

	friend class Manager;
	friend class Player;
	friend class Pop;
	friend class Client;

	/**
	* @brief 初始化各种信息
	* @return bool
	*/

	virtual bool init();

	/**
	* @brief 初始化瓦片地图
	* @return bool
	*/
	void initTileMap();

	/**
	* @brief 初始化网络传来的命令
	* @return void
	*/
	void initKeyCommand();
	/**
	* @brief Game的create函数
	* @param data 参数1
	* @param client 参数2
	* @param playerName 参数3
	* @return  Scene*
	*/
	static Scene* createScene(LevelData &data, Client* client, std::string playerName);
	/**
	* @brief 像素坐标与tileCoord坐标之间的转变
	* @param Const position 参数1
	* @return  Vec2
	*/
	Point tileCoordFromPosition(Point pos);  //屏幕坐标转瓦片坐标
	/**
	* @brief 像素坐标与tileCoord坐标之间的转变
	* @param Const position 参数1
	* @return  Vec2
	*/
	Vec2 Game::positionFromTileCoord(Point pos);  //瓦片坐标转屏幕坐标
	/**
	* @brief 是否Press了
	* @param code 参数1
	* @return  bool
	*/
	bool isKeyPressed(EventKeyboard::KeyCode code);
	/**
	* @brief 判断此坐标是否会碰撞
	* @param tileCoord 参数1
	* @param type 参数2
	* @return  bool
	*/
	bool collidable(Vec2 tileCoord, int type);

	/**
	* @brief 对于画面的每一帧进行升级
	* @param delta 参数1
	* @return  void
	*/
	void update(float delta);
	/**
	* @brief 初始化DiamondVector
	* @return  void
	*/
	void initDiamondLadder();
	bool isTouchDiamond(Vec2 position);
	bool isTouchFinalLadder(cocos2d::Vec2 position);
	/**
	* @brief 是否接触到了钻石
	* @param tileCoord 是否接触到人物
	* @param type      是Star接触到钻石还是Ball
	* @return  void
	*/
	void DiamondCollidableTest(Vec2 tileCoord);
	/**
	* @brief 是否可移动
	* @param tileCoord 是否接触到人物
	* @param 坐标
	* @return  bool
	*/
	bool bnoMove(Vec2 position);

	void isRemoviable(cocos2d::Vec2 position);

	bool bGravity(Vec2 position, int actor);

	void myBlockUpdate(float delta);

	CREATE_FUNC(Game);
};

#endif /*GameScene_H*/
