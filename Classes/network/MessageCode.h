/***********
定义命令类型
***********/
#ifndef MessageCode_h
#define MessageCode_h

/**
* @name 询问网络中是否存在已经建立好的游戏房间
* @{
*/
#define QUERY_FOR_ROOM  "a"
/** @} */

/**
* @name 回应QUERY_FOR_ROOM, 并提供房间基本信息
* @{
*/
#define ANSWER_FOR_ROOM "b"
/** @} */

/**
* @name 开启client的filter mode, 并传输过滤关键词
* @{
*/
#define KEY_ORDER       "c"
/** @} */

/**
* @name 广播开始游戏指令
* @{
*/
#define START_GAME      "d"
/** @} */

/**
* @name 向房间内所有玩家传输新加入房间的玩家信息
* @{
*/
#define JOIN_ROOM       "e"
/** @} */

/**
* @name 新加入房间的玩家向房间拥有者请求房间内所有玩家的信息
* @{
*/
#define QUERY_FOR_PLAYERS_IN_ROOM "f"
/** @} */

/**
* @name QUERY_FOR_PLAYERS_IN_ROOM, 房间所有者\n
* 		向新加入者传输房间内所有玩家的信息
* @{
*/
#define ANSWER_FOR_PLAYERS_IN_ROOM "g"
/** @} */

/**
* @name 向房间内所有玩家传输聊天信息
* @{
*/
#define CHAT_MESSAGE    "h"
/** @} */



/**
* @name 向游戏内其他玩家广播死亡消息，确保同步死亡
* @{
*/
#define DEAD_MESSAGE    "j"
/** @} */


#endif /* MessageCode_h */
