#ifndef _LevelData_h_
#define _LevelData_h_

#include "cocos2d.h"
#include <iostream>
#include "ExternData.h"

USING_NS_CC;

/**
* @brief �洢��ʼ��Ϸ��ʱ����Ҫ���������
*        ����ͼƬ���ơ�����ͼƬ���ơ������ڲ�����Ϸ��������Ϣ
*/

class LevelData : public Node
{
protected:

	std::string 	_data; 	//��ͼ��Ӧ.data�ļ�������
	std::string 	_role; 	//�����Ӧ��ͼƬ����

public:

	std::vector<PlayerData> player_list;	//�������ִ���������

	/**
	* @brief 			�������󴴽�����
	*
	* @param data		��������ͼ������
	* @param role 		�����ɫ����
	*
	* @return 			ָ��LevelData�����ָ��
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
	* @brief 			������������ͼ������
	* @param data    	����ͼƬ��Ӧ������
	*/
	void setData(std::string data) { _data = data; }

	/**
	* @brief            �����������ͼ������
	* @return           ����ͼƬ��Ӧ������
	*/
	std::string getData() { return _data; }

	/**
	* @brief 			���������ɫ����
	* @param role   	�����ɫ����
	*/
	void setRole(std::string role) { _role = role; }

	/**
	* @brief            ��������ɫ����
	* @return           �����ɫ����
	*/
	std::string getRole() { return _role; }

};

#endif /* _LevelData_h_ */
