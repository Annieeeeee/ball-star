#include "RoomScene.h"
USING_NS_CC;
using namespace ui;

#define CLIENT_MODE 1
#define SERVER_MODE 2

bool    finish_create;
int     player_count;
int     current_count;
int     loop_you_in;
bool    if_initial;
bool    if_self_joined;

static int      roomMode;
static Client*  client = nullptr;

static int loop;

std::vector<PlayerData> player_list;
std::map<int, Button*>  chatMessage;

static std::string player_name;
Scene* RoomScene::createScene(Client* c, int mode, std::string _playerName)
{
	// create a scene object, which is auto-realeased by the pool
	auto scene = Scene::create();
	client = c;
	roomMode = mode;
	player_name = _playerName;

	// create a layer object, which is auto-realeased by the pool
	auto layer = RoomScene::create();

	// add layer as a child to the scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool RoomScene::init()
{
	if_initial = false;
	loop = 0;
	_owner_player_name = player_name;
	if (roomMode == SERVER_MODE) {
		this->initForServer();
	}
	else {
		this->initForClient();
	}
	//   this->addChild(client);
	this->scheduleUpdate();

	return true;
}
bool RoomScene::initForClient()
{
	if_self_joined = false;
	// call the base-class init function ˝
	if (!Layer::init())
	{
		return false;
	}
	finish_create = false;
	player_count = 0;
	current_count = 0;
	// get the visiblesize in opengl coordinate
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// get the origin's position in opengl coordinate
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg.png");
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//====================================room list==============================
	auto room = Sprite::create("Room.png");
	room->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(room);
	room->setVisible(false);
	_room_ptr = room;

	//Add a translucent black layer
	Color4B black = Color4B(0, 0, 0, 100);
	auto role_layer = LayerColor::create(black, 680, 680);
	role_layer->setPosition(Vec2(origin.x, origin.y));

	this->addChild(role_layer, 2);

	//Add roleSelectore menu
	auto role_selector = Sprite::create("roleSelector.png");
	role_selector->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	role_layer->addChild(role_selector);

	auto back_button = Button::create("xButton.png");

	auto N1_player_button = Button::create("N1.png");
	auto N2_player_button = Button::create("N2.png");
	auto N3_player_button = Button::create("N3.png");
	auto N4_player_button = Button::create("N4.png");
	//Add role select button and back button
	role_layer->addChild(N1_player_button);
	role_layer->addChild(N2_player_button);
	role_layer->addChild(N3_player_button);
	role_layer->addChild(N4_player_button);
	role_layer->addChild(back_button);

	float widthMargin = visibleSize.width / 2 - role_selector->getContentSize().width / 2;
	float heightMargin = visibleSize.height / 2 - role_selector->getContentSize().height / 2;


	N1_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width / 4, origin.y + role_layer->getContentSize().height / 4));

	N2_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width * 3 / 4, origin.y + role_layer->getContentSize().height / 4));

	N3_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width / 4, origin.y + role_layer->getContentSize().height / 4 * 3));

	N4_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width * 3 / 4, origin.y + role_layer->getContentSize().height / 4 * 3));

	//Choose N1 role
	N1_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) 
	{
		if (type == Widget::TouchEventType::ENDED) 
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N1", 1);
			_owner_player_data = temp;

			char buffer[2];
			buffer[0] = 1 + '0';
			buffer[1] = '\0';
			std::string msg(buffer);
			msg.append(temp->player_role);
			msg.append("|");
			msg.append(temp->player_name);
			client->sendMessage(JOIN_ROOM, msg);

			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create( "N1.png", "N1");
			this->addChild(playerData);
			_game_data = playerData;
		}
	});

	//Choose N2 role
	N2_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N2", 1);
			_owner_player_data = temp;

			char buffer[2];
			buffer[0] = 1 + '0';
			buffer[1] = '\0';
			std::string msg(buffer);
			msg.append(temp->player_role);
			msg.append("|");
			msg.append(temp->player_name);
			client->sendMessage(JOIN_ROOM, msg);

			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create("N2.png", "N2");
			this->addChild(playerData);
			_game_data = playerData;
		}
	});
	//Choose N3 role
	N3_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N3", 1);
			_owner_player_data = temp;

			char buffer[2];
			buffer[0] = 1 + '0';
			buffer[1] = '\0';
			std::string msg(buffer);
			msg.append(temp->player_role);
			msg.append("|");
			msg.append(temp->player_name);
			client->sendMessage(JOIN_ROOM, msg);

			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create("N3.png", "N3");
			this->addChild(playerData);
			_game_data = playerData;
		}
	});
	//Choose N4 role
	N4_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N4", 1);
			_owner_player_data = temp;

			char buffer[2];
			buffer[0] = 1 + '0';
			buffer[1] = '\0';
			std::string msg(buffer);
			msg.append(temp->player_role);
			msg.append("|");
			msg.append(temp->player_name);
			client->sendMessage(JOIN_ROOM, msg);

			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create("N4.png", "N4");
			this->addChild(playerData);
			_game_data = playerData;
		}
	});
	_chatWindow = cocos2d::ui::TextField::create("input words here", "Arial", 30);
	_chatWindow->setMaxLengthEnabled(true);
	_chatWindow->setMaxLength(20);
	_chatWindow->setPosition(Point(_room_ptr->getContentSize().width / 3 * 1.2,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	_chatWindow->addEventListener(CC_CALLBACK_2(RoomScene::textFieldEvent, this));

	room->addChild(_chatWindow, 2);

	auto send_message_button = Button::create("button.png");
	room->addChild(send_message_button);
	send_message_button->cocos2d::Node::setScale(0.7);
	send_message_button->setPosition(Vec2(
		_room_ptr->getContentSize().width / 2 * 1.7,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	send_message_button->setTitleText("send message");
	send_message_button->setTitleFontSize(20);
	send_message_button->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			std::string message = std::to_string(findPlayerId()) + _chatWindow->getString();
			client->sendMessage(CHAT_MESSAGE, message);
			_chatWindow->setString("");
		}
	});
	auto inputBar = Sprite::create("InputBar.png");
	inputBar->setPosition(Point(_room_ptr->getContentSize().width / 3 * 1.2,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	room->addChild(inputBar, 1);

	return true;
}

bool RoomScene::initForServer()
{
	if_self_joined = true;
	// call the base-class init function ˝
	if (!Layer::init())
	{
		return false;
	}

	finish_create = false;
	player_count = 0;
	current_count = 0;

	// get the visiblesize in opengl coordinate
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// get the origin's position in opengl coordinate
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg.png");
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//====================================room list==============================
	auto room = Sprite::create("Room.png");
	room->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(room);
	room->setVisible(false);
	_room_ptr = room;

	_chatWindow = cocos2d::ui::TextField::create("input words here", "Arial", 30);
	_chatWindow->setMaxLengthEnabled(true);
	_chatWindow->setMaxLength(20);
	_chatWindow->setPosition(Point(_room_ptr->getContentSize().width / 3 * 1.2,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	_chatWindow->addEventListener(CC_CALLBACK_2(RoomScene::textFieldEvent, this));

	room->addChild(_chatWindow, 2);

	auto start_game_button = Button::create("button.png");
	room->addChild(start_game_button);
	start_game_button->cocos2d::Node::setScale(0.7);
	start_game_button->setPosition(Vec2(
		_room_ptr->getContentSize().width / 2,
		(_room_ptr->getContentSize().height - 90) / 6 * 0.35));
	start_game_button->setTitleText("START GAME");
	start_game_button->setTitleFontSize(20);


	auto send_message_button = Button::create("button.png");
	room->addChild(send_message_button);
	send_message_button->cocos2d::Node::setScale(0.7);
	send_message_button->setPosition(Vec2(
		_room_ptr->getContentSize().width / 2 * 1.7,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	send_message_button->setTitleText("send message");
	send_message_button->setTitleFontSize(20);
	send_message_button->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			std::string message = std::to_string(findPlayerId()) + _chatWindow->getString();
			client->sendMessage(CHAT_MESSAGE, message);
			_chatWindow->setString("");
		}
	});
	auto inputBar = Sprite::create("InputBar.png");
	inputBar->setPosition(Point(_room_ptr->getContentSize().width / 3 * 1.2,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	room->addChild(inputBar, 1);

	//====================================return_button==============================
	//return button
	auto return_button = Button::create("return.png");
	return_button->setScale(1.0);

	return_button->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height*0.2));

	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInR::create(0.5, NetMenu::createScene());

			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button, 1);

	//==============================================================================
	auto thisObject = this;
	auto start_button = Button::create("button.png");
	//====================================choose role==============================
	start_button->setTitleText("role");
	start_button->setTitleFontSize(30);
	start_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.2));
	start_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{

			//Add a translucent black layer
			Color4B black = Color4B(0, 0, 0, 100);
			auto role_layer = LayerColor::create(black, 680, 680);
			role_layer->setPosition(Vec2(origin.x, origin.y));

			thisObject->addChild(role_layer, 2);

			//Make the original button unvisible
			start_button->setVisible(false);
			return_button->setVisible(false);

			//Add roleSelectore menu
	auto role_selector = Sprite::create("roleSelector.png");
	role_selector->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	role_layer->addChild(role_selector);

	auto back_button = Button::create("xButton.png");

	auto N1_player_button = Button::create("N1.png");
	auto N2_player_button = Button::create("N2.png");
	auto N3_player_button = Button::create("N3.png");
	auto N4_player_button = Button::create("N4.png");
	//Add role select button and back button
	role_layer->addChild(N1_player_button);
	role_layer->addChild(N2_player_button);
	role_layer->addChild(N3_player_button);
	role_layer->addChild(N4_player_button);
	role_layer->addChild(back_button);

	float widthMargin = visibleSize.width / 2 - role_selector->getContentSize().width / 2;
	float heightMargin = visibleSize.height / 2 - role_selector->getContentSize().height / 2;


	N1_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width / 4, origin.y + role_layer->getContentSize().height / 4));

	N2_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width * 3 / 4, origin.y + role_layer->getContentSize().height / 4));

	N3_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width / 4, origin.y + role_layer->getContentSize().height / 4 * 3));

	N4_player_button->setPosition(Vec2(origin.x + widthMargin + role_selector->getContentSize().width * 3 / 4, origin.y + role_layer->getContentSize().height / 4 * 3));

	//Choose N1 role
	N1_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N1", 1);
			_owner_player_data = temp;
			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create( "N1.png", "N1");
			this->addChild(playerData);
			_game_data = playerData;

			start_game_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

				if (player_list.size() == 1) {
					start_game_button->setTitleText("Nobody together？");
					start_game_button->setTitleFontSize(20);
				}
				else {
					client->sendMessage(START_GAME, "start_game");
				}


			});
		}
	});
	//Choose N2 role
	N2_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N2", 1);
			_owner_player_data = temp;
			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create("N2.png", "N2");
			this->addChild(playerData);
			_game_data = playerData;

			start_game_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

				if (player_list.size() == 1) {
					start_game_button->setTitleText("No ghost in the shell!");
					start_game_button->setTitleFontSize(20);
				}
				else {
					client->sendMessage(START_GAME, "start_game");
				}


			});
		}
	});
	//Choose N3 role
	N3_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N3", 1);
			_owner_player_data = temp;
			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create("N3.png", "N3");
			this->addChild(playerData);
			_game_data = playerData;

			start_game_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

				if (player_list.size() == 1) {
					start_game_button->setTitleText("Don't you play wiht me?");
					start_game_button->setTitleFontSize(20);
				}
				else {
					client->sendMessage(START_GAME, "start_game");
				}


			});
		}
	});
	//Choose N4 role
	N4_player_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			// the transition effect

			auto temp = new PlayerData(_owner_player_name, "N4", 1);
			_owner_player_data = temp;
			player_count++;
			role_layer->setVisible(false);

			auto playerData = LevelData::create("N4.png", "N4");
			this->addChild(playerData);
			_game_data = playerData;

			start_game_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {

				if (player_list.size() == 1) {
					start_game_button->setTitleText("Hey,Mushroom!");
					start_game_button->setTitleFontSize(20);
				}
				else {
					client->sendMessage(START_GAME, "start_game");
				}

			});
		}
	});
		}
	});
	this->addChild(start_button, 1);

	return true;
}
void RoomScene::update(float delta)
{
	if (player_count == 1) {
		_room_ptr->setVisible(true);
	}

	loop++;
	if (loop / 100 > 1) {
		loop = 0;
		system("ping -c 1 255.255.255.255");
	}


	if (roomMode == CLIENT_MODE && if_initial == false && player_count != 0)
	{
		if_initial = true;
		client->sendMessage(QUERY_FOR_PLAYERS_IN_ROOM, "whoin?");
		player_count--;
	}

	if (current_count != player_count && roomMode == SERVER_MODE) {
		current_count = player_count;
		auto board = Button::create("PlayerBar.png", "PlayerBar.png");
		player_list.push_back(*_owner_player_data);

		std::string show_string;
		show_string.append(_owner_player_data->player_name);
		//                show_string.append("1# : ");
		//                show_string[0] = temp[1];
		//                show_string.append(player.player_name + "   Role: ");
		//                show_string.append(player.player_role);

		auto serial_num = Sprite::create("1.png");
		board->addChild(serial_num);
		serial_num->setPosition(Vec2(serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

		auto chat_bar = Button::create("ChatBar.png", "ChatBar.png");
		serial_num->addChild(chat_bar);
		chat_bar->setPosition(Vec2(serial_num->getContentSize().width * 2.5, serial_num->getContentSize().height * 1.3));
		chatMessage[1] = chat_bar;
		chat_bar->setVisible(false);


		auto player_icon = Sprite::create(StringUtils::format("%s.png", _owner_player_data->player_role.c_str()));
		board->addChild(player_icon);
		player_icon->setPosition(Vec2(board->getContentSize().width - serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

		board->setTitleText(show_string);

		board->setTitleFontSize(30);
		_room_ptr->addChild(board);
		board->setPosition(Vec2(
			_room_ptr->getContentSize().width / 2,
			(_room_ptr->getContentSize().height - 90) / 6 * (6 - player_count)));
	}

	std::string temp = client->executeOrder();

	if (temp != "no") {

		//        std::cout << "room: " << "\t" <<temp << std::endl;

		if (temp[0] == QUERY_FOR_ROOM[0] && roomMode == SERVER_MODE) {
			client->sendMessage(ANSWER_FOR_ROOM, _owner_player_name);
		}

		if (temp[0] == QUERY_FOR_PLAYERS_IN_ROOM[0] && roomMode == SERVER_MODE)
		{
			std::string players_in_room;
			std::string number;
			number.append("0");
			number[0] += 1;
			client->sendMessage(MAP_SELECT, number);
			for (int i = 0; i < player_list.size(); i++) {
				char buffer[2];
				buffer[0] = i + 1 + '0';
				buffer[1] = '\0';
				std::string msg(buffer);
				msg.append(player_list.at(i).player_role);
				msg.append("|");
				msg.append(player_list.at(i).player_name);
				client->sendMessage(ANSWER_FOR_PLAYERS_IN_ROOM, msg);
			}
		}

		if (temp[0] == ANSWER_FOR_PLAYERS_IN_ROOM[0] && roomMode == CLIENT_MODE)
		{
			std::string players_in_room;
			int i = player_list.size();
			if (player_list.size() == 0)
			{
				player_count++;
				int i = temp.find('|');
				std::string role = temp.substr(2, i - 2);
				std::string player_name = temp.substr(i + 1, temp.size() - i - 1);

				PlayerData player(player_name, role, temp[1] - '0');
				player_list.push_back(player);
				auto board = Button::create("PlayerBar.png", "PlayerBar.png");
				std::string show_string;
				show_string.append(player.player_name);
				//                show_string.append("1# : ");
				//                show_string[0] = temp[1];
				//                show_string.append(player.player_name + "   Role: ");
				//                show_string.append(player.player_role);

				if (temp[1] > '4') {
					temp[1] = '4';
				}

				auto serial_num = Sprite::create(StringUtils::format("%c.png", temp[1]));
				board->addChild(serial_num);
				serial_num->setPosition(Vec2(serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

				auto chat_bar = Button::create("ChatBar.png", "ChatBar.png");
				serial_num->addChild(chat_bar);
				chatMessage[temp[1] - '0'] = chat_bar;
				chat_bar->setPosition(Vec2(serial_num->getContentSize().width * 2.5, serial_num->getContentSize().height * 1.3));
				chat_bar->setVisible(false);


				auto player_icon = Sprite::create(StringUtils::format("%s.png", player.player_role.c_str()));
				board->addChild(player_icon);
				player_icon->setPosition(Vec2(board->getContentSize().width - serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

				board->setTitleText(show_string);
				board->setTitleFontSize(30);
				_room_ptr->addChild(board);
				board->setPosition(Vec2(
					_room_ptr->getContentSize().width / 2,
					(_room_ptr->getContentSize().height - 90) / 6 * (6 - player_count)));
			}
			else {
				bool if_exist = false;
				int i = temp.find('|');
				std::string role = temp.substr(2, i - 2);
				std::string player_name = temp.substr(i + 1, temp.size() - i - 1);
				for (int i = 0; i < player_list.size(); i++)
				{
					if (player_name == player_list.at(i).player_name) {
						if_exist = true;
					}
				}
				if (!if_exist)
				{
					int i = temp.find('|');
					std::string role = temp.substr(2, i - 2);
					std::string player_name = temp.substr(i + 1, temp.size() - i - 1);

					player_count++;
					PlayerData player(player_name, role, temp[1] - '0');
					player_list.push_back(player);
					auto board = Button::create("PlayerBar.png", "PlayerBar.png");
					std::string show_string;
					show_string.append(player.player_name);
					//                    show_string.append("1# : ");
					//                    show_string[0] = temp[1];
					//                    show_string.append(player.player_name + "   Role: ");
					//                    show_string.append(player.player_role);

					if (temp[1] > '4') {
						temp[1] = '4';
					}

					auto serial_num = Sprite::create(StringUtils::format("%c.png", temp[1]));
					board->addChild(serial_num);
					serial_num->setPosition(Vec2(serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

					auto chat_bar = Button::create("ChatBar.png", "ChatBar.png");

					serial_num->addChild(chat_bar);
					chat_bar->setPosition(Vec2(serial_num->getContentSize().width * 2.5, serial_num->getContentSize().height * 1.3));
					chat_bar->setVisible(false);
					chatMessage[temp[1] - '0'] = chat_bar;
					auto player_icon = Sprite::create(StringUtils::format("%s.png", player.player_role.c_str()));
					board->addChild(player_icon);
					player_icon->setPosition(Vec2(board->getContentSize().width - serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

					board->setTitleText(show_string);
					board->setTitleFontSize(30);
					_room_ptr->addChild(board);
					board->setPosition(Vec2(
						_room_ptr->getContentSize().width / 2,
						(_room_ptr->getContentSize().height - 90) / 6 * (6 - player_count)));
				}
			}
		}


		if (temp[0] == START_GAME[0]) {
			for (int i = 0; i < player_list.size(); i++)
			{
				_game_data->player_list.push_back(player_list.at(i));
			}
			//--------------------------------------------------------------------------
			auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());
			//--------------------------------------------------------------------------
			Director::getInstance()->replaceScene(transition);
			//--------------------------------------------------------------------------
		}

		if (temp[0] == JOIN_ROOM[0] && if_self_joined == false) {
			if_self_joined = true;
			return;
		}

		if (temp[0] == CHAT_MESSAGE[0]) {
			DelayTime * delay = DelayTime::create(2.5f);
			auto callFunc1 = CallFunc::create([=] {
				chatMessage[temp[1] - '0']->setVisible(false);
			});
			chatMessage[temp[1] - '0']->setVisible(true);
			chatMessage[temp[1] - '0']->setTitleText(std::string(&temp[2]));
			chatMessage[temp[1] - '0']->setTitleFontSize(30);
			auto sequence = Sequence::create(delay, callFunc1, NULL);
			chatMessage[temp[1] - '0']->runAction(sequence);
		}
		if (temp[0] == JOIN_ROOM[0]) {
			player_count++;
			current_count = player_count;
			int i = temp.find('|');
			std::string role = temp.substr(2, i - 2);
			std::string player_name = temp.substr(i + 1, temp.size() - i - 1);


			PlayerData player(player_name, role, player_count);
			player_list.push_back(player);
			auto board = Button::create("PlayerBar.png", "PlayerBar.png");
			std::string show_string;

			show_string.append(player.player_name);

			if (temp[1] > '4') {
				temp[1] = '4';
			}

			auto serial_num = Sprite::create(StringUtils::format("%c.png", player_count + '0'));
			board->addChild(serial_num);
			serial_num->setPosition(Vec2(serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

			auto chat_bar = Button::create("ChatBar.png", "ChatBar.png");
			serial_num->addChild(chat_bar);
			chat_bar->setPosition(Vec2(serial_num->getContentSize().width * 2.5, serial_num->getContentSize().height * 1.3));

			chat_bar->setVisible(false);
			chatMessage[player_count] = chat_bar;
			auto player_icon = Sprite::create(StringUtils::format("%s.png", player.player_role.c_str()));
			board->addChild(player_icon);
			player_icon->setPosition(Vec2(board->getContentSize().width - serial_num->getContentSize().width * 1, board->getContentSize().height / 2));

			board->setTitleText(show_string);
			board->setTitleFontSize(30);
			_room_ptr->addChild(board);
			board->setPosition(Vec2(
				_room_ptr->getContentSize().width / 2,
				(_room_ptr->getContentSize().height - 90) / 6 * (6 - player_count)));

		}
	}
}
void RoomScene::textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		Size screenSize = CCDirector::getInstance()->getWinSize();

		//_pleaseStartButton->setVisible(true);
	}
	break;

	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);

		// _playerName = textField->getString();
		// _pleaseStartButton->setVisible(true);
	}
	break;

	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		// _pleaseStartButton->setVisible(false);
		//_playerName = textField->getString();
		//_nameStartButton->setVisible(true);

	}
	break;

	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);

		// _playerName = textField->getString();
	}
	break;

	default:
		break;
	}
}
int RoomScene::findPlayerId()
{
	for (int i = 0; i < player_list.size(); i++)
	{
		if (_owner_player_name == player_list.at(i).player_name)
			return player_list.at(i).player_id;
	}

	return 1;
}