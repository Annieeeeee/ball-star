#include "PlayerController.h"
void Player::initLocalPlayer(std::string roleName, Game &scene)
{

	//_bornPosition[0] = Vec2(scene._visibleSize.width / 2, scene._visibleSize.height / 2);
	//_bornPosition[1] = Vec2(scene._visibleSize.width / 2+64, scene._visibleSize.height / 2);

	
	scene._localPlayer = Role::create(scene._inputData->getData());
	

	/*Vec2 bornPosition;
	for (int i = 0; i < scene._playerList.size(); i++)
	{
		if (scene._localPlayerName == scene._playerList.at(i).player_name)
		{
			bornPosition = _bornPosition[scene._playerList.at(i).player_id - 1];
		}
	}*/
	if (roleName=="mySteven")
	{
		scene._localPlayer->setPosition(scene._visibleSize.width / 2, scene._visibleSize.height / 2-64-16);
	}
	else
	{
		scene._localPlayer->setPosition(scene._visibleSize.width / 2 + 48, scene._visibleSize.height / 2-64-16);
	}
	scene._localPlayer->setRoleName(roleName);
	scene._localPlayer->setPlayerName(scene._localPlayerName);
	//scene._localPlayer->setPosition(scene._originSize.x + bornPosition.x, bornPosition.y + scene._originSize.y);
	scene._localPlayer->setAnchorPoint(Vec2(scene._localPlayer->getContentSize().width / 2 / scene._localPlayer->getContentSize().width, scene._tileMap->getTileSize().height / 2 / scene._localPlayer->getContentSize().height));
	scene._tileMap->addChild(scene._localPlayer, 4);
	/*
	Vec2 curPosition = scene._localPlayer->getPosition();
	if (scene.bGravityAir(curPosition) && !scene.bnoMove(Vec2(curPosition.x, curPosition.y - 16)))
	{
		scene._localPlayer->setPosition(Vec2(scene._localPlayer->getPosition().x, scene._localPlayer->getPosition().y - 3.2));
	}*/
}
void Player::initRemotePlayer(std::string roleName, Game &scene)
{

	Vec2 bornPosition;
	for (int i = 0; i < scene._playerList.size(); i++)
	{
		if (scene._localPlayerName == scene._playerList.at(i).player_name)
			continue;
		//bornPosition = _bornPosition[scene._playerList.at(i).player_id /*- 1*/];
		auto RoleName = scene._playerList.at(i).player_role;

		scene._remotePlayer[scene._playerList.at(i).player_name] = Role::create(RoleName+".png");


		
		auto tempPlayer = scene._remotePlayer[scene._playerList.at(i).player_name];
		
		if(roleName == "mySteven")
		{
			tempPlayer->setPosition(scene._visibleSize.width / 2 + 48, scene._visibleSize.height / 2-64-16);
		}
		else
		{
			tempPlayer->setPosition(scene._visibleSize.width / 2, scene._visibleSize.height / 2-64-16);
		}
		tempPlayer->setRoleName(RoleName);
		tempPlayer->setPlayerName(scene._playerList.at(i).player_name);
		//tempPlayer->setPosition(scene._originSize.x + bornPosition.x, bornPosition.y + scene._originSize.y);
		tempPlayer->setAnchorPoint(Vec2(tempPlayer->getContentSize().width / 2 / tempPlayer->getContentSize().width, scene._tileMap->getTileSize().height / 2 / tempPlayer->getContentSize().height));
		scene._tileMap->addChild(tempPlayer, 4);
		/*
		Vec2 curPosition = tempPlayer->getPosition();
		if (scene.bGravityAir(curPosition) && !scene.bnoMove(Vec2(curPosition.x, curPosition.y - 16)))
		{
			tempPlayer->setPosition(Vec2(tempPlayer->getPosition().x, tempPlayer->getPosition().y - 3.2));
		}*/
	}
}

void Player::updatePlayerPerFrame(int delta, Game &scene, EventKeyboard::KeyCode code)
{
	auto a = EventKeyboard::KeyCode::KEY_A, d = EventKeyboard::KeyCode::KEY_D, w = EventKeyboard::KeyCode::KEY_W, s = EventKeyboard::KeyCode::KEY_S,
		j = EventKeyboard::KeyCode::KEY_J, k = EventKeyboard::KeyCode::KEY_K;
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
		keyPressedDuration(a, scene);
		break;
	case  EventKeyboard::KeyCode::KEY_D:
		keyPressedDuration(d, scene);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		keyPressedDuration(w, scene);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		keyPressedDuration(s, scene);
		break;
	case EventKeyboard::KeyCode::KEY_J:
		removeDuration(j, scene);
		break;
	case EventKeyboard::KeyCode::KEY_K:
		removeDuration(k, scene);
		break;
	}
	Vec2 curPosition = scene._player->getPosition();
	if (scene.bGravityAir(curPosition) && !scene.bnoMove(Vec2(curPosition.x, curPosition.y - 16)))
	{
		scene._player->setPosition(Vec2(scene._player->getPosition().x, scene._player->getPosition().y - 3.2));
	}
	scene.LadderVisible();
	scene.encounter();
}
void Player::keyPressedDuration(EventKeyboard::KeyCode code, Game &scene)
{
	float offsetX = 0, offsetY = 0;
	Vec2 pos;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = -3.2;
		pos = Vec2(scene._player->getPosition().x + offsetX - scene._player->getContentSize().width / 2, scene._player->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = 3.2;
		pos = Vec2(scene._player->getPosition().x + offsetX + scene._player->getContentSize().width / 2, scene._player->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		offsetY = 3.2;
		pos = Vec2(scene._player->getPosition().x, scene._player->getPosition().y + offsetY + scene._player->getContentSize().height / 2);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		offsetY = -3.2;
		pos = Vec2(scene._player->getPosition().x, scene._player->getPosition().y + offsetY - scene._player->getContentSize().height / 2);
		break;
	default:
		offsetY = offsetX = 0;
		pos = Vec2(0, 0);
		break;
	}

	if (!scene.bnoMove(pos))
	{
		//如果碰到了钻石块，检测其是否隐形，如否，则代表吃了一个，并将其隐形
		if (scene.isTouchDiamond(pos))
		{
			int bonus = scene.getBonus();
			for (int i = 1; i <= bonus; i++)
			{
				auto it = getChildByTag(i);
				if (abs(pos.x - it->getPosition().x) < 12 && abs(pos.y - it->getPosition().y) < 12)
				{
					if (it->isVisible() == true)
					{
						it->setVisible(false);
						int rank = scene.getRank();
						rank += 1;
						scene.setRank(rank);
					}
				}
			}
		}
		//如果可以移动，则走到该位置
		scene._player->setPosition(Vec2(scene._player->getPosition().x + offsetX, scene._player->getPosition().y + offsetY));
	}
}

void Player::removeDuration(EventKeyboard::KeyCode code, Game& scene)
{
	Vec2 pos;
	pos = scene._player->getPosition();
	Point tileCoord;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_J:
		tileCoord = scene.tileCoordFromPosition(Vec2(pos.x - 32, pos.y - 16));
		pos =scene.positionFromTileCoord(tileCoord);
		scene.isRemoviable(pos);
		break;
	case EventKeyboard::KeyCode::KEY_K:
		tileCoord = scene.tileCoordFromPosition(Vec2(pos.x + 32, pos.y - 16));
		pos = scene.positionFromTileCoord(tileCoord);
		scene.isRemoviable(pos);
		break;
	default:
		pos = Vec2(0, 0);
		tileCoord = pos;
		break;

	}
	//移除后开启刷新函数，调用myUpdate函数，间隔时间为3秒
	schedule(schedule_selector(Game::myBlockUpdate), 3.0f);
}

void Player::setPlayerDied(std::string roleName, Game &scene)
{
	scene._player->stopAllActions();
}