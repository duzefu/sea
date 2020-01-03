/*
**	ServerCharacterDoing.h
**	server character doing functions.
**
**	Jack, 2002/10/30.
*/
#ifndef _SERVERCHARACTERDOING_H_
#define _SERVERCHARACTERDOING_H_


//--------------------------------------------------------------------------------------
//NPC的狀態(STATE)
//------------------------------
#define NPC_STATE_FIGHT             0x00000001  //NPC處於戰鬥狀態下
#define NPC_STATE_DEFENCE           0x00000002  //NPC處於格擋狀態(移動速度減半)
#define NPC_STATE_SHADOW_MOVE       0x00000004  //帶殘影移動
#define NPC_STATE_INVINCIBLE        0x00000010  //無敵(不會被任何招式打中)
#define NPC_STATE_RESIST            0x00000020  //增加抵抗
#define NPC_STATE_ADD_MAX_HP        0x00000040  //增加HP上限
#define NPC_STATE_POWER_ATTACK      0x00000080  //攻擊增強(同時會增加膛爆)
#define NPC_STATE_ANTI_HIDE         0x00000100  //反隱形
#define NPC_STATE_ANTI_POSE         0x00000200  //反偽裝
//


//--------------------------------------------------------------------------------------
//NPC的異常狀態
//------------------------------
//頭部
#define NPC_HEAD_SLEEP_STATE_NORMAL         0   //正常
#define NPC_HEAD_SLEEP_STATE_SWIRL          1   //頭暈
#define NPC_HEAD_SLEEP_STATE_SLEEP          2   //睡眠
//
#define NPC_HEAD_PREDICT_STATE_NORMAL       0   //正常
#define NPC_HEAD_PREDICT_STATE_PREDICT      1   //預知(反隱形, 反偽裝, 反陷阱)
//
#define NPC_HEAD_DEFENCE_STATE_NORMAL       0   //正常
#define NPC_HEAD_DEFENCE_STATE_DEFENCE      1   //防禦加強
//
#define NPC_HEAD_MAGIC_STATE_NORMAL         0   //正常
#define NPC_HEAD_MAGIC_STATE_REBOUND        1   //魔法反彈
//
#define NPC_HEAD_BLIND_STATE_NORMAL         0   //正常
#define NPC_HEAD_BLIND_STATE_BLIND          1   //失明
//
#define NPC_HEAD_ATTRACT_STATE_NORMAL       0   //正常
#define NPC_HEAD_ATTRACT_STATE_FASCINATE    1   //魅惑
#define NPC_HEAD_ATTRACT_STATE_ATTRACT      2   //吸引
//
//身體
#define NPC_BODY_DODGE_STATE_NORMAL         0   //正常
#define NPC_BODY_DODGE_STATE_DODGE          1   //躲閃
//
#define NPC_BODY_VIRUS_STATE_NORMAL         0   //正常
#define NPC_BODY_VIRUS_STATE_VIRUS          1   //中毒
//
#define NPC_BODY_HIDE_STATE_NORMAL          0   //正常
#define NPC_BODY_HIDE_STATE_SUCKED          1   //被吸血
#define NPC_BODY_HIDE_STATE_HIDE            2   //隱形
//
//腳下
#define NPC_FOOT_SPEED_STATE_NORMAL         0   //正常
#define NPC_FOOT_SPEED_STATE_TARDY          1   //遲緩1,行走速度下降,跳幀處理(動作頻率快),貼動畫.
#define NPC_FOOT_SPEED_STATE_TIRED          2   //遲緩2,行走速度下降,續幀處理(動作頻率慢),不貼動畫(被打腳或者在惡魔區域內).
//
//死亡或活著
#define NPC_LIVE                            0   //活著或重生
#define NPC_DEAD                            1	//死亡
#define NPC_DISAPPEAR						2   //死亡消失 


//--------------------------------------------------------------------------------------
//NPC的AI
//------------------------------
// Jack, todo [11:01,10/10/2002]
//NPC AI KIND(怪物NPC 人工智能的種類) ------------------------------------------------------
#define AI_KIND_MASK_MOVE_TYPE          0x0000000f  //移動方式AI
#define AI_KIND_MASK_WHEN_MOVE          0x000000f0  //移動時的戰鬥AI
#define AI_KIND_MASK_AFTER_ATTACK       0x00000f00  //物理攻擊敵方後的AI
#define AI_KIND_MASK_AFTER_MAGIC        0x0000f000  //法術攻擊敵方後的AI
#define AI_KIND_MASK_AFTER_BEATED       0x000f0000  //被攻擊後的AI
#define AI_KIND_MASK_AFTER_DODGE        0x00f00000  //躲避完後的AI
//#define	AI_KIND_MASK_AFTER_DEFENCE		0x0f000000	//格檔後的AI
//#define	AI_KIND_MASK_AFTER_DEFENCED		0xf0000000	//被格檔後的AI
//
#define AI_KIND_IDLE_MOVE_TYPE          0x00000001  //原地不動
#define AI_KIND_GAD_MOVE_TYPE           0x00000002  //隨機移動
#define	AI_KIND_TREND_MOVE_TYPE			0x00000003	//趨向出生點的移動
#define	AI_KIND_PATROL_MOVE_TYPE		0x00000004	//巡邏
//
#define AI_KIND_NONE_WHEN_MOVE          0x00000010  //移動時碰到敵人沒有反應(會繼續自己的移動)
#define AI_KIND_ATTACK_WHEN_MOVE        0x00000020  //移動時碰到敵人行走物理攻擊
#define AI_KIND_MAGIC_WHEN_MOVE         0x00000030  //移動時碰到敵人法術攻擊
#define AI_KIND_MIXED_WHEN_MOVE         0x00000040  //移動時碰到敵人混合攻擊(物理攻擊或者法術攻擊)
#define AI_KIND_DODGE_WHEN_MOVE         0x00000050  //移動時碰到敵人躲避
#define AI_KIND_RUN_ATTACK_WHEN_MOVE    0x00000060  //移動時碰到敵人跑步物理攻擊
#define	AI_KIND_TRANCE_WHEN_MOVE        0x00000070	//移動時碰到敵人會發呆
//
#define AI_KIND_NONE_AFTER_ATTACK       0x00000100  //物理攻擊敵人後沒有後續反應(會根據移動AI自行移動)
#define AI_KIND_ATTACK_AFTER_ATTACK     0x00000200  //物理攻擊敵人後還會繼續物理攻擊
#define AI_KIND_MAGIC_AFTER_ATTACK      0x00000300  //物理攻擊敵人後會採用法術攻擊
#define AI_KIND_MIXED_AFTER_ATTACK      0x00000400  //物理攻擊敵人後會採用混合攻擊
#define AI_KIND_DODGE_AFTER_ATTACK      0x00000500  //物理攻擊敵人後馬上躲避
#define AI_KIND_RUN_ATTACK_AFTER_ATTACK 0x00000600  //物理攻擊敵人後還會繼續跑步物理攻擊
#define	AI_KIND_TRANCE_AFTER_ATTACK     0x00000700	//物理攻擊敵人後會發呆
//
#define AI_KIND_NONE_AFTER_MAGIC        0x00001000  //法術攻擊完後沒有後續反應(會根據移動AI自行移動)
#define AI_KIND_ATTACK_AFTER_MAGIC      0x00002000  //法術攻擊完後採用物理攻擊
#define AI_KIND_MAGIC_AFTER_MAGIC       0x00003000  //法術攻擊完後繼續法術攻擊
#define AI_KIND_MIXED_AFTER_MAGIC       0x00004000  //法術攻擊完後採用混合攻擊
#define AI_KIND_DODGE_AFTER_MAGIC       0x00005000  //法術攻擊完後馬上躲避
#define AI_KIND_RUN_ATTACK_AFTER_MAGIC  0x00006000  //法術攻擊完後採用跑步物理攻擊
#define	AI_KIND_TRANCE_AFTER_MAGIC      0x00007000	//法術攻擊完會發呆
//
#define AI_KIND_NONE_AFTER_BEATED       0x00010000  //被擊後沒有反應, 會根據移動AI自行移動
#define AI_KIND_ATTACK_AFTER_BEATED     0x00020000  //被擊後會物理攻擊
#define AI_KIND_MAGIC_AFTER_BEATED      0x00030000  //被擊後會法術攻擊
#define AI_KIND_MIXED_AFTER_BEATED      0x00040000  //被擊後會混合攻擊
#define AI_KIND_DODGE_AFTER_BEATED      0x00050000  //被擊後會躲避
#define AI_KIND_RUN_ATTACK_AFTER_BEATED 0x00060000  //被擊後會跑步物理攻擊
#define	AI_KIND_TRANCE_AFTER_BEATED     0x00070000	//被擊後會發呆
//
#define AI_KIND_NONE_AFTER_DODGE        0x00100000  //躲避完後沒有其他反應(會根據移動AI自行移動)
#define AI_KIND_ATTACK_AFTER_DODGE      0x00200000  //躲避完後會物理攻擊
#define AI_KIND_MAGIC_AFTER_DODGE       0x00300000  //躲避完後會法術攻擊
#define AI_KIND_MIXED_AFTER_DODGE       0x00400000  //躲避完後會混合攻擊
#define AI_KIND_DODGE_AFTER_DODGE       0x00500000  //躲避完後會繼續躲避
#define AI_KIND_RUN_ATTACK_AFTER_DODGE  0x00600000  //躲避完後會跑步物理攻擊
#define	AI_KIND_TRANCE_AFTER_DODGE      0x0070000	//躲避完後會發呆
//
//
extern  void    server_set_npc_AI_functions(void);
extern  void    server_set_npc_doing_functions(void);
extern	void    ServerChangeCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    ServerChangeCharacterAiBlock(SLONG npc_no, SLONG ai_block, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    ServerCreateMagicArea(SLONG type, SLONG npc_no, SLONG mx, SLONG my, SLONG magic_no, SLONG magic_level);
extern  void    server_refresh_character(void);
extern	void	server_save_character_data(void);
extern	void	server_exec_talk_with_npc(SLONG	player_index, SLONG	dest_npc);


#endif//_SERVERCHARACTERDOING_H_
