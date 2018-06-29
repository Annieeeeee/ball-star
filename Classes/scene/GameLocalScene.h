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
* @brief Game�� �̳���cocos2d:Layer
*        ����������������Ǹ�ʲôjer������
*        ����ϴ�����Ŀ
*            *Ϸ̨*
*/
class Manager;
class Player;
class Game :public Layer
{
private:
	Size              _visibleSize; //�Ӵ���С
	Vec2              _originSize; //ԭʼ��С

	int               _bonusNumber;//��ʯ����
	int               _ladderNumber;//��������
	int               _rank;//��ǰ�Ե�����ʯ��

	LevelData*        _inputData;//������ʼ���Ĳ������������������
	std::vector<PlayerData> _playerList;//�������Ϣ��֮����name���˱���list
	Game*             _thisScene;//����thisָ��

	Role*             _player;//��ǰ�ٿص����
	Role*             _localPlayer;//�������
	Client*           _client;//�����û��ͻ���
	std::string       _localPlayerName;//�����������������name���ˣ�
	Manager* _sceneManager;
	//Manager*          _sceneManager;//�������﷢�������ܶ������ı�scene
	Player* _playerManager;
	//Player*           _playerManager;//��ʼ������
	std::map<std::string, Role*>   _remotePlayer;//����player������name���ˣ�

	TMXTiledMap*              _tileMap;                   //��Ƭ��ͼ
	TMXLayer*                 _diamondLayer;              //��ʯ��
	TMXLayer*                 _soilLayer;                //�����㣬����
	TMXLayer*                 _stoneLayer;               //��ʯ�㣬������
	TMXLayer*                 _airLayer;                 //�����㣬Ball�ڿ����д���
	TMXLayer*                 _etherLayer;               //��̫�㣬Star����̫�д���
	TMXLayer*                 _GladderLayer;            //���ݲ�
	TMXLayer*                 _borderLayer;             //�߽��
	TMXLayer*                 _borderUpLayer;           //�Ͻ��

	std::map<std::string, EventKeyboard::KeyCode>      _keyPressesedOrder;//press���뱨����stringӳ�䵽code
	std::map<std::string, EventKeyboard::KeyCode>      _keyReleasedOrder;//release���뱨����stringӳ�䵽code
	std::map<EventKeyboard::KeyCode, std::string>      _keyPressesedOrders;//press���ͱ���codeӳ��Ϊstring
	std::map<EventKeyboard::KeyCode, std::string>      _keyReleasedOrders;//release���ͱ���codeӳ��Ϊstring
	std::queue<std::string>                           _command;//�����յ���ָ�� FIFO

	Vector<Button*>           _endButton;
public:
	friend class Manager;
	friend class Player;
	friend class Client;

	/**
	* @brief Game��create����
	* @param data ����1
	* @param client ����2
	* @param playerName ����3
	* @return  Scene*
	*/
	static Scene* createScene(LevelData &data, Client* client, std::string playerName);
	/**
	* @brief �����ƶ����
	* @param posCode
	* @return  bool
	*/
	bool bnoMove(cocos2d::Vec2 position);
	/**
	* @brief �������
	* @param posCode
	* @return  bool
	*/
	bool bGravityAir(cocos2d::Vec2 position);
	/**
	* @brief �Ƴ�����
	* @param posCode
	* @return  void
	*/
	void isRemoviable(cocos2d::Vec2 position);
	/**
	* @brief �Ƴ�������Ļָ�
	* @param delta
	* @return  void
	*/
	void myBlockUpdate(float delta);
	/**
	* @brief ������ʯ��⣨��ʼ���Լ�֮�����ʯ
	* @param posCode
	* @return  bool
	*/
	bool isTouchDiamond(cocos2d::Vec2 position);
	/**
	* @brief �������Ӽ�⣨��ʼ��
	* @param posCode
	* @return  bool
	*/
	bool isTouchFinalLadder(cocos2d::Vec2 position);
	/**
	* @brief ��Ļ����ת��Ƭ����
	* @param posCode
	* @return  point
	*/
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	/**
	* @brief ��Ƭ����ת��Ļ����
	* @param posCode
	* @return  point
	*/
	cocos2d::Vec2 positionFromTileCoord(cocos2d::Point position);
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
	* @brief ��ʼ����ʯ����
	* @return void
	*
	*/
	void initDiamondLadder();

	/**
	* @brief ��ʼ�����紫��������
	* @return void
	*/
	void initKeyCommand();
	/**
	* @brief �Ƿ�Press��
	* @param code ����1
	* @return  bool
	*/
	bool isKeyPressed(EventKeyboard::KeyCode code);
	/**
	* @brief ���ڻ����ÿһ֡��������
	* @param delta ����1
	* @return  void
	*/
	void update(float delta);
	/**
	* @brief ���óԵ�����ʯ��Ŀ
	*/
	void setRank(int rank)
	{
		_rank = rank;
	}
	/**
	* @brief ���سԵ�����ʯ��Ŀ
	* @return int
	*/
	int getRank()
	{
		return _rank;
	}
	/**
	* @brief ������Ϸ���õ���ʯ����
	* @return int
	*/
	int getBonus()
	{
		return _bonusNumber;
	}
	/**
	* @brief ������Ϸ���õ���������
	* @return int
	*/
	int getLadder()
	{
		return _ladderNumber;
	}
	/**
	* @brief �����������������
	* @return void
	*/
	void encounter();
	/**
	* @brief �����Ƿ�����
	* @return void
	*/
	void LadderVisible();
	CREATE_FUNC(Game);
};
#endif /*GAMELOCALSCENE_H*/
