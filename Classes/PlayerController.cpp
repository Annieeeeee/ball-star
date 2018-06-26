#include <stdio.h>
#include "PlayerController.h"
#include "../Data/Role.h"
#include "../Scene/GameScene.h"

void Player::initLocalPlayer(std::string roleName, Game &scene)
{

	_bornPosition[0] = (Vec2(528,400));
	_bornPosition[1] = (Vec2(112, 112));


	scene._localPlayer = Role::create(scene._inputData->getData());

	Vec2 bornPosition;
		if (scene._localPlayer->getActor()==1)
		{
			bornPosition = _bornPosition[0];
		}
		else
		{
			bornPosition = _bornPosition[1];
		}
	

	scene._localPlayer->setRoleName(roleName);
	scene._localPlayer->setPlayerName(scene._localPlayerName);
	scene._localPlayer->setPosition(scene._originSize.x + bornPosition.x, bornPosition.y + scene._originSize.y);
	scene._localPlayer->setAnchorPoint(Vec2(scene._localPlayer->getContentSize().width / 2 / scene._localPlayer->getContentSize().width, scene._tileMap->getTileSize().height / 2 / scene._localPlayer->getContentSize().height));
	scene._tileMap->addChild(scene._localPlayer, 4);

}
void Player::initRemotePlayer(std::string roleName, Game &scene)
{

	Vec2 bornPosition;
	for (int i = 0; i < scene._playerList.size(); i++)
	{
		if (scene._localPlayerName == scene._playerList.at(i).player_name)
			continue;
		
		auto RoleName = scene._playerList.at(i).player_role;
		if (RoleName == "mySteven")
		{
			scene._remotePlayer[scene._playerList.at(i).player_name] = Role::create("mySteven.png");
			bornPosition = _bornPosition[0];
		}

		else
			scene._remotePlayer[scene._playerList.at(i).player_name] = Role::create(RoleName+".png");

		auto tempPlayer = scene._remotePlayer[scene._playerList.at(i).player_name];
		tempPlayer->setRoleName(RoleName);
		tempPlayer->setPlayerName(scene._playerList.at(i).player_name);
		tempPlayer->setPosition(scene._originSize.x + bornPosition.x, bornPosition.y + scene._originSize.y);
		tempPlayer->setAnchorPoint(Vec2(tempPlayer->getContentSize().width / 2 / tempPlayer->getContentSize().width, scene._tileMap->getTileSize().height / 2 / tempPlayer->getContentSize().height));
		scene._tileMap->addChild(tempPlayer, 3);
	}
}
void Player::updatePlayerPerFrame(int delta, Game &scene, EventKeyboard::KeyCode code)
{
	auto a = EventKeyboard::KeyCode::KEY_A, d = EventKeyboard::KeyCode::KEY_D, w = EventKeyboard::KeyCode::KEY_W, s = EventKeyboard::KeyCode::KEY_S, j = EventKeyboard::KeyCode::KEY_J, k = EventKeyboard::KeyCode::KEY_K;
	float offsetX = 0, offsetY = 0;
	Vec2 pos;
		if (code==a) {
			offsetX = -3.2;
			pos = Vec2(scene._player->getPosition().x + offsetX - scene._player->getContentSize().width / 2, scene._player->getPosition().y);
		}
		else if (code == d) {
			offsetX = 3.2;
			pos = Vec2(scene._player->getPosition().x + offsetX + scene._player->getContentSize().width / 2, scene._player->getPosition().y);

		}
		else if (code == w) {
			offsetY = 3.2;
			pos = Vec2(scene._player->getPosition().x, scene._player->getPosition().y + offsetY + scene._player->getContentSize().height / 2);

		}
		else if (code == s) {
			offsetY = -3.2;
			pos = Vec2(scene._player->getPosition().x, scene._player->getPosition().y + offsetY - scene._player->getContentSize().height / 2);

		}
		else if (code == j&&scene._player->getActor()==1)
		{
			pos = scene._player->getPosition();
			Point tileCoord;
			tileCoord = scene.tileCoordFromPosition(Vec2(pos.x - 32, pos.y - 16));
			pos = scene.positionFromTileCoord(tileCoord);
			scene.isRemoviable(pos);
			schedule(schedule_selector(Game::myBlockUpdate), 3.0f);
		}
		else if (code == k&&scene._player->getActor() == 1)
		{
			pos = scene._player->getPosition();
			Point tileCoord;
			tileCoord = scene.tileCoordFromPosition(Vec2(pos.x + 32, pos.y - 16));
			pos = scene.positionFromTileCoord(tileCoord);
			scene.isRemoviable(pos);
			schedule(schedule_selector(Game::myBlockUpdate), 3.0f);
		}
		if(scene._player->getActor()==1)
		{
			if (scene.bnoMove(pos))
			{
				//如果碰到了钻石块，检测其是否隐形，如否，则代表吃了一个，并将其隐形
				if (scene.isTouchDiamond(pos))
				{
					for (int i = 1; i <= scene.bonusNumber; i++)
					{
						auto it = getChildByTag(i);
						if (abs(pos.x - it->getPosition().x) < 12 && abs(pos.y - it->getPosition().y) < 12)
						{
							if (it->isVisible() == true)
							{
								it->setVisible(false);
								++scene.rank;
							}
						}
					}
				}
			}
		}
			//如果可以移动，则走到该位置
		scene._player->setPosition(Vec2(scene._player->getPosition().x + offsetX, scene._player->getPosition().y + offsetY));
		
		Vec2 curPosition = scene._player->getPosition();
	
}
void Player::setPlayerDied(std::string roleName, Game &scene)
{
	scene._player->stopAllActions();
}
