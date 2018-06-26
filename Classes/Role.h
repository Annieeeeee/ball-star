#ifndef ROLE_H
#define ROLE_H
#include <iostream>
#include <string>
#include "cocos2d.h"
USING_NS_CC;
class Role : public cocos2d::Sprite
{
private:
	std::string     _roleName;                         ///����Ľ�ɫ
	std::string     _playerName;                       ///��ҵ�����
	int             _actor;                            ///��Ұ��ݵĽ�ɫ
	bool            _isDead = false;                   ///����Ƿ�����
	bool            _alreadyDead = false;              ///����Ƿ�����������
	Vec2            _tileSize;                         ///��Ƭ��ͼ�Ĵ�С
	bool            _isHost;                           ///����Ƿ�������
	std::map<EventKeyboard::KeyCode, bool> _keys;      ///��ҵİ���
	std::map<EventKeyboard::KeyCode, bool> _realKeys;  ///��ҵ���������
public:
	/**
	* @brief Role��create����
	* @param filename�ļ�������
	* @return  Role*
	*/
	static Role* create(const std::string& filename)
	{
		Role *sprite = new Role();
		if (sprite && sprite->initWithFile(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	/**
	* @brief Role��create����
	* @param filename�ļ�������
	* @return  Role*
	*/
	static Role* createWithSpriteFrameName(const std::string& filename)
	{
		Role *sprite = new Role();
		if (sprite && sprite->initWithSpriteFrameName(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	/**
	* @brief ���������Ѿ�����
	* @return  void
	*/
	void setAlreadyDead()
	{
		_alreadyDead = true;
	}
	/**
	* @brief �õ�����Ƿ��Ѿ���������Ϣ
	* @return bool
	*/
	bool getAlreadyDead()
	{
		return _alreadyDead;
	}
	/**
	* @brief ������������İ���,���������ÿ���˽��вٿ�
	* @param code ������λ��
	* @param isPress �ǰ����˻���û�а���
	* @return  void
	*/
	void setKeys(EventKeyboard::KeyCode code, bool isPress)
	{
		_keys[code] = isPress;
		_realKeys[code] = !isPress;
	}
	/**
	* @brief ������������İ���,���������ÿ���˽��вٿأ�����������
	* @param code ������λ��
	* @param isPress �ǰ����˻���û�а���
	* @return  void
	*/
	void setRealKeys(EventKeyboard::KeyCode code, bool isPress)
	{
		_realKeys[code] = isPress;
	}
	/**
	* @brief �õ�����İ�����Ϣ
	* @param code ������λ��
	* @return bool
	*/
	bool getKeys(EventKeyboard::KeyCode code)
	{
		return _keys[code];
	}
	/**
	* @brief �õ����������ĵİ�����Ϣ
	* @param code ������λ��
	* @return bool
	*/
	bool getRealKeys(EventKeyboard::KeyCode code)
	{
		return _realKeys[code];
	}
	/**
	* @brief ������������
	* @return void
	*/
	void setPlayerDead()
	{
		_isDead = true;
	}
	/**
	* @brief ���������Ƿ���������
	* @return void
	*/
	bool isDead()
	{
		return _isDead;
	}
	/**
	* @brief ��������Ľ�ɫ����
	* @param name ����
	* @return void
	*/
	void setRoleName(std::string name)
	{
		_roleName = name;
	}
	/**
	* @brief �õ�����Ľ�ɫ����
	* @return std::string
	*/
	std::string getRoleName()
	{
		return _roleName;
	}
	/**
	* @brief �����������
	* @param playerName �������
	* @return void
	*/
	void setPlayerName(std::string playerName)
	{
		_playerName = playerName;
	}
	/**
	* @brief �õ��������
	* @return std::string
	*/
	std::string getPlayerName()
	{
		return _playerName;
	}
	/**
	* @brief �õ��������λ�ã�string��ʽ�õ���
	* @return std::string
	*/
	std::string getPlayerPosition()
	{
		std::stringstream ssx;
		std::stringstream ssy;
		std::string s1 = "(";
		ssx << this->getPositionX();
		std::string positionX = ssx.str();
		std::string s2 = ",";
		ssy << this->getPositionY();
		std::string positionY = ssy.str();
		std::string s3 = ")";

		return s1 + positionX + s2 + positionY + s3;

	}
	/**
	* @brief �����������
	* @param actor ���ݽ�ɫ
	* @return void
	*/
	void setActor(int actor)
	{
		_actor=actor;
	}
	/**
	* @brief �õ�����Ľ�ɫ����
	* @return std::string
	*/
	int getActor()
	{
		return _actor;
	}
};
#endif /*ROLE_H*/