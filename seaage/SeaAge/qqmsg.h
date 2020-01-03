/*
 *    QQmsg.h
 *    
 *    show message in uiqq
 *
 *    Zhang Zhaohui, 2002/11/01.
 *    
 */

#pragma once

#include "ErrorMsg.h"


/***************************************
 *
 *
 *  Text for different version
 *
 *
 **************************************/

#ifdef  BIG5_VERSION

#define QQTXT_HIDE_LOGIN            "留ō"
#define QQTXT_HIDE_LOGIN_INFO       "~C0留ō~C0"
#define QQTXT_ONLINE_LOGIN          "絬"
#define QQTXT_ONLINE_LOGIN_INFO     "~C0絬~C0"
#define QQTXT_SYSSET                "把计砞竚"
#define QQTXT_SYSSET_INFO           "~C0把计砞竚~C0"
#define QQTXT_MESSAGE               "╰参魁"
#define QQTXT_MESSAGE_INFO          "~C0╰参魁~C0"
#define QQTXT_SEARCH                "穓"
#define QQTXT_SEARCH_INFO           "~C0穓~C0"
#define QQTXT_CALLGM                "㊣恨瞶"
#define QQTXT_CALLGM_INFO           "~C0㊣恨瞶~C0"
#define QQTXT_TIME_STR              "%d%dる%dら %d:%d"
#define QQTXT_STRANGER_NAME         "ネ"
#define QQTXT_RECEIVE_ITEM          "  "

#define QQMB_TITLE_WARNING          "猔種"
#define QQMB_TITLE_ERROR            "岿粇"
#define QQMB_TEXT_SEARCH1           "叫匡拒產"
#define QQMB_TEXT_SEARCH2           "叫块ぶ穓兵ン"
#define QQMB_TEXT_INPUT_EMPTY       "ぃ祇癳"
#define QQMB_TEXT_CANOT_ADD_SELF    "ぃ盢ね"
#define QQMB_TEXT_ALREADY_ADDED     "竒睰硂ね"
#define QQMB_TEXT_DEL_FRIEND        "絋﹚璶盢¨%s〃埃"

#define QQERR_SUCCESS               "ΘЧΘ癸ね巨"
#define QQERR_QF_ALREADY_ADDED      "竒睰硂ね"
#define QQERR_QF_MAX_COUNT          "ね竒程计ぃ膥尿睰"
#define QQERR_NO_ENOUGH_MEM         "⊿Τì镑癘拘砰ㄓЧΘ癸ね巨"
#define QQERR_SEND_ITEM_FAILED      "肚癳珇ア毖"

#endif  /* BIG5_VERSION */

#ifdef GB_VERSION

#define QQTXT_HIDE_LOGIN            "隐身"
#define QQTXT_HIDE_LOGIN_INFO       "~C0隐身~C0"
#define QQTXT_ONLINE_LOGIN          "在线"
#define QQTXT_ONLINE_LOGIN_INFO     "~C0在线~C0"
#define QQTXT_SYSSET                "参数设置"
#define QQTXT_SYSSET_INFO           "~C0参数设置~C0"
#define QQTXT_MESSAGE               "系统纪录"
#define QQTXT_MESSAGE_INFO          "~C0系统纪录~C0"
#define QQTXT_SEARCH                "搜索"
#define QQTXT_SEARCH_INFO           "~C0搜索~C0"
#define QQTXT_CALLGM                "呼叫管理员"
#define QQTXT_CALLGM_INFO           "~C0呼叫管理员~C0"
#define QQTXT_TIME_STR              "%d年%d月%d日 %d:%d"
#define QQTXT_STRANGER_NAME         "陌生人"
#define QQTXT_RECEIVE_ITEM          "  "

#define QQMB_TITLE_WARNING          "注意"
#define QQMB_TITLE_ERROR            "错误"
#define QQMB_TEXT_SEARCH1           "请选择一个玩家"
#define QQMB_TEXT_SEARCH2           "请输入至少一个搜索条件"
#define QQMB_TEXT_INPUT_EMPTY       "不能发送空消息"
#define QQMB_TEXT_CANOT_ADD_SELF    "不能将自己加为好友"
#define QQMB_TEXT_ALREADY_ADDED     "你已经将此人加为好友"
#define QQMB_TEXT_DEL_FRIEND        "确定要将“%s”删除么？"

#define QQERR_SUCCESS               "成功完成对好友的操作"
#define QQERR_QF_ALREADY_ADDED      "你已经添加了这个好友"
#define QQERR_QF_MAX_COUNT          "你的好友已经到了最大数，不能再继续添加了"
#define QQERR_NO_ENOUGH_MEM         "没有足够的内存来完成对好友的操作"
#define QQERR_SEND_ITEM_FAILED      "传送物品失败"
#endif  /* GB_VERSION */


