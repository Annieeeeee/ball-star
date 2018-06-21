/***********
������������
***********/
#ifndef MessageCode_h
#define MessageCode_h

/**
* @name ѯ���������Ƿ�����Ѿ������õ���Ϸ����
* @{
*/
#define QUERY_FOR_ROOM  "a"
/** @} */

/**
* @name ��ӦQUERY_FOR_ROOM, ���ṩ���������Ϣ
* @{
*/
#define ANSWER_FOR_ROOM "b"
/** @} */

/**
* @name ����client��filter mode, ��������˹ؼ���
* @{
*/
#define KEY_ORDER       "c"
/** @} */

/**
* @name �㲥��ʼ��Ϸָ��
* @{
*/
#define START_GAME      "d"
/** @} */

/**
* @name �򷿼���������Ҵ����¼��뷿��������Ϣ
* @{
*/
#define JOIN_ROOM       "e"
/** @} */

/**
* @name �¼��뷿�������򷿼�ӵ�������󷿼���������ҵ���Ϣ
* @{
*/
#define QUERY_FOR_PLAYERS_IN_ROOM "f"
/** @} */

/**
* @name QUERY_FOR_PLAYERS_IN_ROOM, ����������\n
* 		���¼����ߴ��䷿����������ҵ���Ϣ
* @{
*/
#define ANSWER_FOR_PLAYERS_IN_ROOM "g"
/** @} */

/**
* @name �򷿼���������Ҵ���������Ϣ
* @{
*/
#define CHAT_MESSAGE    "h"
/** @} */

/**
* @name �򷿼���������Ҵ��䷿����ѡ��ĵ�ͼ����
* @{
*/
#define MAP_SELECT      "i"
/** @} */

/**
* @name ����Ϸ��������ҹ㲥������Ϣ��ȷ��ͬ������
* @{
*/
#define DEAD_MESSAGE    "j"
/** @} */


#endif /* MessageCode_h */