#ifndef GAMELOCALSCENE_H
#define GAMELOCALSCENE_H
#include <iostream>
#include "../NetWork/Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Data/ExternData.h"
#include "../Data/LevelData.h"
#include "../Manager/GameManager.h"
#include "../Manager/PlayerController.h"
#include "../Data/Role.h"
#include "../NetWork/MessageCode.h"
USING_NS_CC;
using namespace ui;
/**
* @brief Game类 继承自cocos2d:Layer
*        我终于理清楚到底是个什么jer玩意了
*        以泪洗面祭项目
*            *戏台*
*/
class Manager;
class Player;
class Game :public Layer
{
private:
	Size              _visibleSize; //视窗大小
	Vec2              _originSize; //原始大小

	int               _bonusNumber;//钻石总数
	int               _ladderNumber;//梯子总数
	int               _rank;//当前吃到的钻石数

	LevelData*        _inputData;//用来初始化的参数，今后借此生成人物
	std::vector<PlayerData> _playerList;//人物的信息表，之后用name找人遍历list
	Game*             _thisScene;//等于this指针

	Role*             _player;//当前操控的玩家
	Role*             _localPlayer;//本地玩家
	Client*           _client;//本地用户客户端
	std::string       _localPlayerName;//本地玩家姓名（基于name找人）
	Manager* _sceneManager;
	//Manager*          _sceneManager;//经由人物发挥主观能动性来改变scene
	Player* _playerManager;
	//Player*           _playerManager;//初始化人物
	std::map<std::string, Role*>   _remotePlayer;//所有player（基于name找人）

	TMXTiledMap*              _tileMap;                   //瓦片地图
	TMXLayer*                 _diamondLayer;              //钻石层
	TMXLayer*                 _soilLayer;                //泥土层，可挖
	TMXLayer*                 _stoneLayer;               //岩石层，不可挖
	TMXLayer*                 _airLayer;                 //空气层，Ball在空气中传播
	TMXLayer*                 _etherLayer;               //以太层，Star在以太中传播
	TMXLayer*                 _GladderLayer;            //天梯层
	TMXLayer*                 _borderLayer;             //边界层
	TMXLayer*                 _borderUpLayer;           //上界层

	std::map<std::string, EventKeyboard::KeyCode>      _keyPressesedOrder;//press破译报文是string映射到code
	std::map<std::string, EventKeyboard::KeyCode>      _keyReleasedOrder;//release破译报文是string映射到code
	std::map<EventKeyboard::KeyCode, std::string>      _keyPressesedOrders;//press发送报文code映射为string
	std::map<EventKeyboard::KeyCode, std::string>      _keyReleasedOrders;//release发送报文code映射为string
	std::queue<std::string>                           _command;//所有收到的指令 FIFO

	Vector<Button*>           _endButton;
public:
	friend class Manager;
	friend class Player;
	friend class Client;

	/**
	* @brief Game的create函数
	* @param data 参数1
	* @param client 参数2
	* @param playerName 参数3
	* @return  Scene*
	*/
	static Scene* createScene(LevelData &data, Client* client, std::string playerName);
	/**
	* @brief 不可移动检测
	* @param posCode
	* @return  bool
	*/
	bool bnoMove(cocos2d::Vec2 position);
	/**
	* @brief 重力检测
	* @param posCode
	* @return  bool
	*/
	bool bGravityAir(cocos2d::Vec2 position);
	/**
	* @brief 移出泥土
	* @param posCode
	* @return  void
	*/
	void isRemoviable(cocos2d::Vec2 position);
	/**
	* @brief 移除泥土后的恢复
	* @param delta
	* @return  void
	*/
	void myBlockUpdate(float delta);
	/**
	* @brief 触碰钻石检测（初始化以及之后吃钻石
	* @param posCode
	* @return  bool
	*/
	bool isTouchDiamond(cocos2d::Vec2 position);
	/**
	* @brief 触碰梯子检测（初始化
	* @param posCode
	* @return  bool
	*/
	bool isTouchFinalLadder(cocos2d::Vec2 position);
	/**
	* @brief 屏幕坐标转瓦片坐标
	* @param posCode
	* @return  point
	*/
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	/**
	* @brief 瓦片坐标转屏幕坐标
	* @param posCode
	* @return  point
	*/
	cocos2d::Vec2 positionFromTileCoord(cocos2d::Point position);
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
	* @brief 初始化钻石梯子
	* @return void
	*
	*/
	void initDiamondLadder();

	/**
	* @brief 初始化网络传来的命令
	* @return void
	*/
	void initKeyCommand();
	/**
	* @brief 是否Press了
	* @param code 参数1
	* @return  bool
	*/
	bool isKeyPressed(EventKeyboard::KeyCode code);
	/**
	* @brief 对于画面的每一帧进行升级
	* @param delta 参数1
	* @return  void
	*/
	void update(float delta);
	/**
	* @brief 设置吃到的钻石数目
	*/
	void setRank(int rank)
	{
		_rank = rank;
	}
	/**
	* @brief 返回吃到的钻石数目
	* @return int
	*/
	int getRank()
	{
		return _rank;
	}
	/**
	* @brief 返回游戏设置的钻石总数
	* @return int
	*/
	int getBonus()
	{
		return _bonusNumber;
	}
	/**
	* @brief 返回游戏设置的梯子总数
	* @return int
	*/
	int getLadder()
	{
		return _ladderNumber;
	}
	/**
	* @brief 人物与人物相遇检测
	* @return void
	*/
	void encounter();
	/**
	* @brief 梯子是否现形
	* @return void
	*/
	void LadderVisible();
	CREATE_FUNC(Game);
};
#endif /*GAMELOCALSCENE_H*/
