#ifndef _LevelData_h_
#define _LevelData_h_

#include "cocos2d.h"
#include <iostream>
#include "ExternData.h"

USING_NS_CC;

/**
* @brief 存储开始游戏的时候需要传入的数据
*        背景图片名称、人物图片名称、房间内参与游戏的人物信息
*/

class LevelData : public Node
{
protected:

	std::string 	_data; 	//地图对应.data文件的名称
	std::string 	_role; 	//人物对应的图片名称

public:

	std::vector<PlayerData> player_list;	//房间内现存的玩家数据

	/**
	* @brief 			单例对象创建函数
	*
	* @param data		人物缩略图的名称
	* @param role 		人物角色名称
	*
	* @return 			指向LevelData对象的指针
	*/
	static LevelData* create(std::string data, std::string role)
	{
		LevelData *sprite = new LevelData();
		if (sprite)
		{
			sprite->autorelease();
			sprite->setData(data);
			sprite->setRole(role);

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}


	/**
	* @brief 			设置人物缩略图的名称
	* @param data    	背景图片对应的名称
	*/
	void setData(std::string data) { _data = data; }

	/**
	* @brief            获得人物缩略图的名称
	* @return           背景图片对应的名称
	*/
	std::string getData() { return _data; }

	/**
	* @brief 			设置人物角色名称
	* @param role   	人物角色名称
	*/
	void setRole(std::string role) { _role = role; }

	/**
	* @brief            获得人物角色名称
	* @return           人物角色名称
	*/
	std::string getRole() { return _role; }

};

#endif /* _LevelData_h_ */
