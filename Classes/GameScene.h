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
* @brief Game�� �̳���cocos2d:Layer
* ����������Ϸ����ʵ�ֵ���
* �ո����а����˹����manager��,�����˱���������Զ������,
* �����˵�ͼ�Ĳٿ�,�Լ������һЩת��.
*
* cocos���������͵���Ϸ��ֱ̫�����ˣ����ݵ�������
*
* д�����ģ�������������
*/
class Game :public Layer
{
private:
	Size              _visibleSize;                       ///�Ӵ���С    
	Vec2              _originSize;                        ///ԭʼ��С             
	int               _screenWidth;                       ///�Ӵ����
	int               _screenHeight;                      ///�Ӵ��߶�
	
	LevelData*                _inputData;                 ///ѡ������ʱ������
	Game*                     _thisScene;                 ///����Thisָ��
	std::vector<PlayerData>   _playerList;                ///����Զ����ҵ���Ϣ

	TMXTiledMap*              _tileMap;                   ///��Ƭ��ͼ
	TMXLayer*                 _diamondLayer;                ///��ʯ��
	TMXLayer*                 _soilLayer;                ///�����㣬����
	TMXLayer*                 _stoneLayer;               ///��ʯ�㣬������
	TMXLayer*                 _airLayer;                 ///�����㣬Ball�ڿ����д���
	TMXLayer*                 _etherLayer;                 ///��̫�㣬Star����̫�д���
	TMXLayer*                 _GladderLayer;             ///���ݲ�
	TMXLayer*                 _borderLayer;             ///�߽��
	TMXLayer*                 _borderUpLayer;             ///�Ͻ��
	EventKeyboard::KeyCode    _code;                      ///ÿ�ΰ��µļ�����Ϣ
	
	/*
	public:
	static MyMapBall * create(const std::string& tmxFile);
	MyMapBall();
	bool init();
	bool bnoMove(cocos2d::Vec2 position);
	bool bGravity(cocos2d::Vec2 position);
	void isRemoviable(cocos2d::Vec2 position);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);//��������
	cocos2d::Vec2 positionFromTileCoord(cocos2d::Point position);
	int m_gid_soil,m_gid_stone,m_gid_air,m_gid_border;
	cocos2d::TMXLayer *m_soilLayer, *m_stoneLayer, *m_airLayer,*m_borderLayer;
	*/

	Vector<Sprite*>           _diamondVector;             ///bonusVector
	Vector<Button*>           _endButton;                 ///������Ϸ��ť

	Role*                              _player;           ///��ǰ���ٿص����
	Role*                              _localPlayer;      ///�������
	Client*                            _client;           ///�����ָ��
	std::string                        _localPlayerName;  ///������ҵ�����
	Player*                            _playerManager;    ///��Ҳٿ�Manager
	Manager*                           _sceneManager;     ///scene Manager
	std::map<std::string, Role*>       _remotePlayer;     ///Զ����ҵļ���

	std::map<std::string, EventKeyboard::KeyCode>      _keyPressesedOrder;   ///���̰��µİ���
	std::map<std::string, EventKeyboard::KeyCode>      _keyReleasedOrder;    ///�����ɿ��İ���
	std::map<EventKeyboard::KeyCode, std::string>      _keyPressesedOrders;  ///���̰��µİ���
	std::map<EventKeyboard::KeyCode, std::string>      _keyReleasedOrders;   ///�����ɿ��İ���
	std::map<EventKeyboard::KeyCode, bool>            _keys;                ///��¼�����Ƿ���
	std::queue<std::string>                           _command;             ///ÿ�ζ�ȡ������

public:
	int bonusNumber = 0;
	int ladderNumber = 0;
	int rank = 0;

	friend class Manager;
	friend class Player;
	friend class Pop;
	friend class Client;

	/**
	* @brief ��ʼ��������Ϣ
	* @return bool
	*/

	virtual bool init();

	/**
	* @brief ��ʼ����Ƭ��ͼ
	* @return bool
	*/
	void initTileMap();

	/**
	* @brief ��ʼ�����紫��������
	* @return void
	*/
	void initKeyCommand();
	/**
	* @brief Game��create����
	* @param data ����1
	* @param client ����2
	* @param playerName ����3
	* @return  Scene*
	*/
	static Scene* createScene(LevelData &data, Client* client, std::string playerName);
	/**
	* @brief ����������tileCoord����֮���ת��
	* @param Const position ����1
	* @return  Vec2
	*/
	Point tileCoordFromPosition(Point pos);  //��Ļ����ת��Ƭ����
	/**
	* @brief ����������tileCoord����֮���ת��
	* @param Const position ����1
	* @return  Vec2
	*/
	Vec2 Game::positionFromTileCoord(Point pos);  //��Ƭ����ת��Ļ����
	/**
	* @brief �Ƿ�Press��
	* @param code ����1
	* @return  bool
	*/
	bool isKeyPressed(EventKeyboard::KeyCode code);
	/**
	* @brief �жϴ������Ƿ����ײ
	* @param tileCoord ����1
	* @param type ����2
	* @return  bool
	*/
	bool collidable(Vec2 tileCoord, int type);

	/**
	* @brief ���ڻ����ÿһ֡��������
	* @param delta ����1
	* @return  void
	*/
	void update(float delta);
	/**
	* @brief ��ʼ��DiamondVector
	* @return  void
	*/
	void initDiamondLadder();
	bool isTouchDiamond(Vec2 position);
	bool isTouchFinalLadder(cocos2d::Vec2 position);
	/**
	* @brief �Ƿ�Ӵ�������ʯ
	* @param tileCoord �Ƿ�Ӵ�������
	* @param type      ��Star�Ӵ�����ʯ����Ball
	* @return  void
	*/
	void DiamondCollidableTest(Vec2 tileCoord);
	/**
	* @brief �Ƿ���ƶ�
	* @param tileCoord �Ƿ�Ӵ�������
	* @param ����
	* @return  bool
	*/
	bool bnoMove(Vec2 position);

	void isRemoviable(cocos2d::Vec2 position);

	bool bGravity(Vec2 position, int actor);

	void myBlockUpdate(float delta);

	CREATE_FUNC(Game);
};

#endif /*GameScene_H*/
