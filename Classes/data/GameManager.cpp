#include "GameManager.h"
#include <stdio.h>
static Manager* thisManager = nullptr;
template <class Type>
Type stringToNum(const std::string& str) {
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
void Manager::updatePerFrame(int delta, Game & scene)
{
	std::string tempCommand;
	while ((tempCommand = scene._client->executeOrder()) != "no")
	{
		scene._command.push(tempCommand);
		std::cout << "收到的信息:" << tempCommand << std::endl;
	}

	scene._player = scene._localPlayer;

	if (!scene._player->isDead())
	executePlayer(delta, scene);


	while (scene._command.size() != 0)
	{
		_command = scene._command.front();
		scene._command.pop();
		if (_command[0] == DEAD_MESSAGE[0])
		{
			std::string name = std::string(&_command[1]);
			if (name == scene._localPlayerName)
			{
				//                std::cout << "LocalPlayerDead message" << std::endl;
				scene._player = scene._localPlayer;
				scene._player->stopAllActions();
				scene._localPlayer->setPlayerDead();

				executePlayer(delta, scene);
			}
			else {
				//                std::cout << "RemotePlayerDead message" << std::endl;
				scene._player = scene._remotePlayer[name];
				scene._player->stopAllActions();
				scene._player->setPlayerDead();
				executePlayer(delta, scene);
			}

		}
		if (_command[0] != KEY_ORDER[0])
		{
			continue;
		}
		readCommand();

		// bool isPress;

		if (_playerName == scene._localPlayerName)
		
			continue;
		scene._player = scene._remotePlayer[_playerName];
		if (_code[0] == 'p')
		{
			scene._player->setKeys(scene._keyPressesedOrder[_code], true);
			if (((_code[1] == 'j') || (_code[1] == 'k')) && (scene._player->getActor() != 1))
				//此处锁死了star
			{
				scene._player->setKeys(scene._keyPressesedOrder[_code], false);
			}
		}
		else
		{
			scene._player->setKeys(scene._keyReleasedOrder[_code], false);
		}

		
		executePlayer(delta, scene);
		scene._player->setPosition(_playerCurrentPosition);
	}
	for (int i = 0; i < scene._playerList.size(); i++)
	{
		_playerName = scene._playerList.at(i).player_name;

		if (_playerName == scene._localPlayerName)
			continue;

		else {
			//std::cout << "PlayerName:" << _playerName << std::endl;
			scene._player = scene._remotePlayer[_playerName];
			executePlayer(delta, scene);
		}
	}
}

void Manager::readCommand()
{
	auto leftBracket = _command.find('(');
	auto comma = _command.find(',');
	auto rightBracket = _command.find(')');
	std::string code(_command.begin() + 1, _command.begin() + 3);
	std::string playerName(_command.begin() + 3, _command.begin() + leftBracket);
	std::string spositionX(_command.begin() + 1 + leftBracket, _command.begin() + comma);
	std::string spositionY(_command.begin() + 1 + comma, _command.begin() + rightBracket);


	float positionX = stringToNum<float>(spositionX);
	float positionY = stringToNum<float>(spositionY);

	_code = code;
	_playerName = playerName;
	_playerCurrentPosition = Vec2(positionX, positionY);

}

void Manager::playerInit(std::string player, Game & scene)
{

	_playerManager = Player::create(player, scene);
	scene.addChild(_playerManager);
	scene._playerManager = _playerManager;
}

void Manager::executePlayer(int delta, Game &scene)
{
	if (scene._player->isDead()) {
		if (!scene._player->getAlreadyDead())
		{
			scene._player->setAlreadyDead();

			_playerManager->setPlayerDied(scene._player->getRoleName(), scene);
		}
		else {

			return;
		}
	}

	auto a = EventKeyboard::KeyCode::KEY_A, d = EventKeyboard::KeyCode::KEY_D, w = EventKeyboard::KeyCode::KEY_W, s = EventKeyboard::KeyCode::KEY_S, j = EventKeyboard::KeyCode::KEY_J, k = EventKeyboard::KeyCode::KEY_K;
	int any_arrow = scene.isKeyPressed(a) +
		scene.isKeyPressed(d) +
		scene.isKeyPressed(w) +
		scene.isKeyPressed(s);

	
	if ((scene.isKeyPressed(j) && any_arrow)) {
		_playerManager->updatePlayerPerFrame(delta, scene, j);
		scene._player->setKeys(j, false);
	}
	if ((scene.isKeyPressed(k) && any_arrow)) {
		_playerManager->updatePlayerPerFrame(delta, scene, k);
		scene._player->setKeys(k, false);
	}

	//move when one of the direction is pressed 
	if (scene.isKeyPressed(a)) {
		_playerManager->updatePlayerPerFrame(delta, scene, a);
	}
	else if (scene.isKeyPressed(d)) {
		 
		_playerManager->updatePlayerPerFrame(delta, scene, d);
	}
	else if (scene.isKeyPressed(w)) {
		 
		_playerManager->updatePlayerPerFrame(delta, scene,w);
	}
	else if (scene.isKeyPressed(s)) {
	 
		_playerManager->updatePlayerPerFrame(delta, scene, s);
	}
	else if (scene.isKeyPressed(j)) {

		
		_playerManager->updatePlayerPerFrame(delta, scene, j);
	}
	else if (scene.isKeyPressed(k)) {


		_playerManager->updatePlayerPerFrame(delta, scene, k);
	}


}
