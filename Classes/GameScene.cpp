#include "GameScene.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RoomScene.h"
#include "SearchScene.h"

using namespace std;
static std::string splayerName;
static Client* clients;
//a static pointer which is gong to be used to make LevelData oject reference count nonzero
static LevelData* ptr = NULL;
static int Ball_Life = 3;
static bool isStarReborn = true;


Scene*Game::createScene(LevelData &data, Client* client, std::string playerName)
{
	auto scene = Scene::create();
	data.retain();

	clients = client;
	splayerName = playerName;
	//Make LevelData oject reference count nonzero
	ptr = &data;

	auto layer = Game::create();

	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_thisScene = this;
	_client = clients;
	_inputData = ptr;

	//initThings
	initTileMap();
	initDiamondLadder();
	initKeyCommand();

	//==============================QuitButton===========================
	auto close_button = Button::create("button.png");
	close_button->setScale(1.0);
	close_button->setTitleText("Quit");
	close_button->setTitleFontSize(20);
	close_button->setPosition(Vec2(_originSize.x + _visibleSize.width / 2, _originSize.y + _visibleSize.height / 7 * 2));

	close_button->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif

		}
	});
	this->addChild(close_button);
	close_button->setVisible(false);
	_endButton.pushBack(close_button);


	if (ptr != nullptr)
	{
		_sceneManager = Manager::create( ptr->getRole(), *this);
		this->addChild(_sceneManager);
	}
	else {
		_sceneManager = Manager::create( "player", *this);
		this->addChild(_sceneManager);
	}


	// create keyBoardListener
	auto keyBoardListener = EventListenerKeyboard::create();

	//key value is true when it is pressed
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event)
	{

		if (_localPlayer->isDead())
		{
			return;
		}
		if (!(code == EventKeyboard::KeyCode::KEY_A ||
			code == EventKeyboard::KeyCode::KEY_D ||
			code == EventKeyboard::KeyCode::KEY_W ||
			code == EventKeyboard::KeyCode::KEY_S ||
			code == EventKeyboard::KeyCode::KEY_J ||
			code == EventKeyboard::KeyCode::KEY_K))
		{
			return;
		}
		_localPlayer->setKeys(code, true);
		_client->sendMessage(KEY_ORDER, _keyPressesedOrders[code] + _localPlayerName + _localPlayer->getPlayerPosition());
	};

	//key value is false when it is not pressed
	keyBoardListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		if (_localPlayer->isDead())
		{
			return;
		}
		if (!(code == EventKeyboard::KeyCode::KEY_A ||
			code == EventKeyboard::KeyCode::KEY_D ||
			code == EventKeyboard::KeyCode::KEY_W ||
			code == EventKeyboard::KeyCode::KEY_S ||
			code == EventKeyboard::KeyCode::KEY_J ||
			code == EventKeyboard::KeyCode::KEY_K))
		{
			return;
		}
		_localPlayer->setKeys(code, false);

		_client->sendMessage(KEY_ORDER, _keyReleasedOrders[code] + _localPlayerName + _localPlayer->getPlayerPosition());

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	this->scheduleUpdate();
	return true;
}


//=======================地图初始化===========================
void Game::initTileMap()
{
	//get the height and width of the screen(window)
	_visibleSize = Director::getInstance()->getVisibleSize();
	_originSize = Director::getInstance()->getVisibleOrigin();
	_screenWidth = _visibleSize.width;
	_screenHeight = _visibleSize.height;
	//create the scene via the map file
	_tileMap = TMXTiledMap::create("mapNew.tmx");
	_tileMap->setAnchorPoint(Vec2::ZERO);
	_tileMap->setPosition(Vec2::ZERO + Vec2(_originSize.x, _originSize.y));
	this->addChild(_tileMap);

	//get the different layer
	_diamondLayer = _tileMap->getLayer("Bonus");
	_soilLayer = _tileMap->getLayer("Soil");
	_stoneLayer = _tileMap->getLayer("Stone");
	_airLayer = _tileMap->getLayer("Air");
	_etherLayer = _tileMap->getLayer("Ether");
	_GladderLayer = _tileMap->getLayer("LadderFinal");
	_borderLayer = _tileMap->getLayer("Border");
	_borderUpLayer = _tileMap->getLayer("BorderUp");

	//make the layer unvisible
	_diamondLayer->setVisible(false);
	_GladderLayer->setVisible(false);
	_borderLayer->setVisible(false);

}

void Game::initDiamondLadder()
{
	for (int i = 1; i < 34; i++)
	{
		for (int j = 1; j < 24; j++)
		{
			if (isTouchDiamond(Vec2(16 + i * 32, 16 + j * 32)))
			{
				auto bonus = Sprite::create("myBonus.png");
				bonus->setPosition(Vec2(16 + i * 32, 16 + j * 32));
				bonusNumber++;
				this->addChild(bonus, 1, bonusNumber);
			}
		}
	}
	for (int i = 1; i < 34; i++)
	{
		for (int j = 1; j < 24; j++)
		{
			if (isTouchFinalLadder(Vec2(16 + i * 32, 16 + j * 32)))
			{
				auto ladder = Sprite::create("myLadderG.png");
				ladder->setPosition(Vec2(16 + i * 32, 16 + j * 32));
				++ladderNumber;
				ladder->setVisible(false);
				this->addChild(ladder, 2, 20 + ladderNumber);
			}
		}
	}
}

bool Game::isTouchDiamond(Vec2 position)
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = _diamondLayer->getTileGIDAt(tileCoord);
	if (gid > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Game::isTouchFinalLadder(cocos2d::Vec2 position)
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = _GladderLayer->getTileGIDAt(tileCoord);
	if (gid > 0)	return true;
	else return false;
}

void Game::myBlockUpdate(float delta)
{
	_tileMap->removeFromParent();
	initTileMap();
	unschedule(schedule_selector(Game::myBlockUpdate));
}
//===============地图部分==================================

//===============坐标转换==================================
Point Game::tileCoordFromPosition(Point pos)  //屏幕坐标转瓦片坐标
{
	Size mapSize = _tileMap->getMapSize();
	Size tileSize = _tileMap->getTileSize();
	int x = pos.x / tileSize.width;
	int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
	return Vec2(x, y);

}
Vec2 Game::positionFromTileCoord(Point pos)  //瓦片坐标转屏幕坐标
{
	Size mapSize = _tileMap->getMapSize();
	Size tileSize = _tileMap->getTileSize();
	int x = pos.x * tileSize.width + tileSize.width / 2;
	int y = (mapSize.height - pos.y) * tileSize.height - tileSize.height / 2;
	return Vec2(x, y);
}
//===============坐标转换==================================

//==============键盘检测与按键==================================
bool Game::isKeyPressed(EventKeyboard::KeyCode code)
{
	return _player->getKeys(code);
}

void Game::initKeyCommand()
{
	_keyPressesedOrders[EventKeyboard::KeyCode::KEY_A] = "pl";
	_keyPressesedOrders[EventKeyboard::KeyCode::KEY_D] = "pr";
	_keyPressesedOrders[EventKeyboard::KeyCode::KEY_W] = "pu";
	_keyPressesedOrders[EventKeyboard::KeyCode::KEY_S] = "pd";
	_keyPressesedOrders[EventKeyboard::KeyCode::KEY_J] = "pj";
	_keyPressesedOrders[EventKeyboard::KeyCode::KEY_K] = "pk";

	_keyReleasedOrders[EventKeyboard::KeyCode::KEY_A] = "rl";
	_keyReleasedOrders[EventKeyboard::KeyCode::KEY_D] = "rr";
	_keyReleasedOrders[EventKeyboard::KeyCode::KEY_W] = "ru";
	_keyReleasedOrders[EventKeyboard::KeyCode::KEY_S] = "rd";
	_keyReleasedOrders[EventKeyboard::KeyCode::KEY_J] = "rj";
	_keyReleasedOrders[EventKeyboard::KeyCode::KEY_K] = "rk";

	_keyPressesedOrder["pl"] = EventKeyboard::KeyCode::KEY_A;
	_keyPressesedOrder["pr"] = EventKeyboard::KeyCode::KEY_D;
	_keyPressesedOrder["pu"] = EventKeyboard::KeyCode::KEY_W;
	_keyPressesedOrder["pd"] = EventKeyboard::KeyCode::KEY_S;
	_keyPressesedOrder["pj"] = EventKeyboard::KeyCode::KEY_J;
	_keyPressesedOrder["pk"] = EventKeyboard::KeyCode::KEY_K;

	_keyReleasedOrder["rl"] = EventKeyboard::KeyCode::KEY_A;
	_keyReleasedOrder["rr"] = EventKeyboard::KeyCode::KEY_D;
	_keyReleasedOrder["ru"] = EventKeyboard::KeyCode::KEY_W;
	_keyReleasedOrder["rd"] = EventKeyboard::KeyCode::KEY_S;
	_keyReleasedOrder["rj"] = EventKeyboard::KeyCode::KEY_J;
	_keyReleasedOrder["rk"] = EventKeyboard::KeyCode::KEY_K;

}
//===============键盘设置===================================

//==============可移动检测==================================
bool Game::bnoMove(Vec2 position)
{
	Point tileCoord = tileCoordFromPosition(position);

	unsigned int gid1 = _soilLayer->getTileGIDAt(tileCoord);
	unsigned int gid2 = _stoneLayer->getTileGIDAt(tileCoord);
	unsigned int gid3 = _borderLayer->getTileGIDAt(tileCoord);
	if (gid1 > 0 || gid2>0 || gid3>0) return true;
	return false;
}
//==============可移动检测==================================

//==============技能JK==========================================
void Game::isRemoviable(cocos2d::Vec2 position)
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = _soilLayer->getTileGIDAt(tileCoord);
	if (gid > 0)
	{
		_soilLayer->removeTileAt(tileCoord);
	}
}
//==============技能JK==========================================

//==============重力检测========================================
bool Game::bGravity(Vec2 position,int actor)		
{
	
	Point tileCoord = tileCoordFromPosition(position);
	if (actor == 2)
	{
		unsigned int gid = _etherLayer->getTileGIDAt(tileCoord);
		if (gid > 0) return true;
		return false;
	}
	else
	{
		unsigned int gid = _airLayer->getTileGIDAt(tileCoord);
		if (gid > 0) return true;
		return false;
	}
}
//==============重力检测========================================

//===============刷新检测=======================================无人生还
void Game::update(float delta) {
	Node::update(delta);

	bool if_all_dead = false;

	auto it = _remotePlayer.begin();
	while (it != _remotePlayer.end())
	{
		if (it->first == _localPlayerName)
			continue;
		if (it->second->isDead() == true) {
			if_all_dead = true;
		}
		else {
			if_all_dead = false;
			break;
		}
		it++;
	}

	if (_localPlayer->isDead() == true || if_all_dead == true) {
		for (auto i : _endButton) {
			i->setVisible(true);
		}
	}

	//update the player's Position and check whether to put the pop
	_sceneManager->updatePerFrame(delta, *this);
}
//===============刷新检测=======================================无人生还
