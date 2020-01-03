/*
**      NPC.H
**      npc functions header.
**
**      ZJian,2000.11.22.
*/
#ifndef NPC_H_INCLUDE
#define NPC_H_INCLUDE
#include "map.h"


// D E F I N E S //////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_GAME_MAP        1           //世界地圖數量

//------------------------------------------------------------------------
//人物選擇區大小
//------------------------------------------------------------------------
#define NPC_MASK_WIDTH      60          //滑鼠選取時的寬度
#define NPC_MASK_HEIGHT     80          //滑鼠選取時的高度
//

//------------------------------------------------------------------------
//人物標誌(NPC FLAGS)
//------------------------------------------------------------------------
#define NPC_USED            0x00000001  //正在使用
#define NPC_ACTIVE          0x00000002  //處於活動狀態(沒有在使用)
#define NPC_BUSY            0x00000004  //正在忙著()
#define NPC_PAUSE           0x00000008  //暫停原來的動作
#define NPC_DIED            0x00000010  //已經死亡

//
/*
//------------------------------------------------------------------------
//NPC類別(NPC KIND)
//------------------------------------------------------------------------
#define NPC_KIND_EMPLACEMENT        0   //砲台
#define NPC_KIND_GUIDEPOST          1   //路牌
#define NPC_KIND_NORMAL_MONSTER     2   //普通怪物
#define NPC_KIND_HEADER_MONSTER     3   //頭目怪物
#define NPC_KIND_BOSS_MONSTER       4   //BOSS怪物
#define NPC_KIND_THIEF_MONSTER      5   //小偷怪
#define NPC_KIND_TREASURE_MONSTER   6   //寶物怪
#define NPC_KIND_GUARD              7   //警衛
#define NPC_KIND_NPC                8   //閒人(村人)
#define NPC_KIND_PLAYER             9   //玩家
#define NPC_KIND_TREASURE           10  //寶藏(小島)
#define NPC_KIND_MERMAID            11  //美人魚(會改變背景音樂)
#define NPC_KIND_TRAP               12  //陷阱
#define NPC_KIND_SUBMERGED_ROCK     13  //暗礁
#define NPC_KIND_BURBLE             14  //漩渦
#define NPC_KIND_STATUARY           15  //雕像
#define	NPC_KIND_CORPSE		        16	//屍體
#define MAX_NPC_KINDS               17  //總的類別數目
*/

//------------------------------------------------------------------------
//RELATIONS(NPC與NPC的關係) 
//------------------------------------------------------------------------
#define RELATION_NEUTRAL            0x00000001  //與對方中立
#define RELATION_ALLY               0x00000002  //與對方聯盟
#define RELATION_OPPOSE             0x00000004  //與對方敵對

//------------------------------------------------------------------------
//NPC顯示標記(NPC_SHOW FLAGS)
//------------------------------------------------------------------------
#define	NPC_SHOW_ENABLE_VIEW		0x00000001	//可以看見
#define NPC_SHOW_ENABLE_RANGE       0x00000002  //可以點擊選擇
//
#define MAX_SHOW_SHADOWS            5           //人物的殘影數目

//------------------------------------------------------------------------
//NPC對話(NPC TALK ASSOCIATED)
//------------------------------------------------------------------------
#define NPC_NAME_LEN                16          //人物名稱長度
#define NPC_TALK_NUM                3           //人物對話行數
#define NPC_TALK_LEN                24          //每行對話長度
//
//NPC對話的類別
#define NPC_TALK_IS_DIALOG          1           //對話
#define NPC_TALK_IS_NAME            2           //人物名稱
//
//------------------------------------------------------------------------
//NPC的狀態(STATE)
//------------------------------------------------------------------------
// mark by lijun 
// 2003-04-08
/*
#define NPC_STATE_FIGHT             0x00000001  //NPC處於戰鬥狀態下
#define NPC_STATE_DEFENCE           0x00000002  //NPC處於格擋狀態(移動速度減半)
#define NPC_STATE_SHADOW_MOVE       0x00000004  //帶殘影移動
#define NPC_STATE_INVINCIBLE        0x00000010  //無敵(不會被任何招式打中)
#define NPC_STATE_RESIST            0x00000020  //增加抵抗
#define NPC_STATE_ADD_MAX_HP        0x00000040  //增加HP上限
#define NPC_STATE_POWER_ATTACK      0x00000080  //攻擊增強(同時會增加膛爆)
#define NPC_STATE_ANTI_HIDE         0x00000100  //反隱形
#define NPC_STATE_ANTI_POSE         0x00000200  //反偽裝
*/
//
//#define NEXT_NPC_FIGHT_STATE        1           //NPC的下一個戰鬥狀態
//#define PREV_NPC_FIGHT_STATE        2           //NPC的上一個戰鬥狀態

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
//--------------------------------------------------------------------------------------
//NPC的AI
//------------------------------
// Jack, todo [11:01,10/10/2002]



//--------------------------------------------------------------------------------------
//NPC的所在地層
//------------------------------
#define NPC_LAYER_EXERCISE                  0   //練功地層
#define NPC_LAYER_EXPLORE                   1   //探險地層


// S T R U C T S //////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

typedef struct  tagGAME_NPC
{
    //-----------------------------------------------------------
    SLONG   flag;               //標志
    SLONG   object_index;       //對應地圖物件索引
    //-----------------------------------------------------------
    SLONG   effect;             //影像特效
    //-----------------------------------------------------------    
    SLONG   ext_id;             //附加效果文件標示
    SLONG   ext_frame;          //附加效果影像幀
    //--------------------------------------------------------------------
    SLONG   foot_id;            //人物腳下狀態效果圖檔
    SLONG   foot_frame;         //人物腳下狀態效果圖像幀
    //--------------------------------------------------------------------
    SLONG   head_id;            //人物頭上的狀態效果圖檔
    SLONG   head_frame;         //人物頭上的狀態效果圖像幀
    //--------------------------------------------------------------------
    SLONG   body_front_id;      //人物身上的效果圖..npc前面的圖
    SLONG   body_back_id;       //人物身上的效果圖..npc後面的圖
    SLONG   body_frame;         //人物身上的幀數
    //-----------------------------------------------------------
    SLONG   talk_flags;        //對話標誌
    DWORD   talk_time;         //說對時間
    SLONG   talk_lines;        //對話行數
    SLONG   talk_sx;           //顯示對話的位置 x
    SLONG   talk_sy;           //顯示對話的位置 y
    CHAR	talk_text[NPC_TALK_NUM][NPC_TALK_LEN+4];    //對話文字
    //-----------------------------------------------------------
	UCHR	rgb_scroll[35];	    //人物色盤和效果
    //-----------------------------------------------------------
} GAME_NPC,*LPGAME_NPC;


#pragma pack(pop)

//和npc上圖效果相關的一些屬性
//!!!注意在定義變量的時候   NPC_SHOW  必須和  GAME_NPC 一樣的大小
typedef struct  tagNPC_SHOW
{
    SLONG   flag;           //標誌
    //--------------------------------------------------------------------
    SLONG   with_shadow;    //移動時帶殘影
    SLONG   last_x;         //人物上次座標 x
    SLONG   last_y;         //人物上次座標 y
    SLONG   last_z;         //人物上次座標 z
    SLONG   shadow_x[MAX_SHOW_SHADOWS]; //殘影座標 x
    SLONG   shadow_y[MAX_SHOW_SHADOWS]; //殘影座標 y
    SLONG   shadow_z[MAX_SHOW_SHADOWS]; //殘影座標 z
    //--------------------------------------------------------------------
    SLONG   ext_id;			//人物特殊效果圖檔ID.
    SLONG   ext_frame;		//人物特殊效果圖像幀
    //--------------------------------------------------------------------
    SLONG   foot_id;        //人物腳下狀態效果圖檔
    SLONG   foot_frame;     //人物腳下狀態效果圖像幀
    //--------------------------------------------------------------------
    SLONG   head_id;        //人物頭上的狀態效果圖檔
    SLONG   head_frame;     //人物頭上的狀態效果圖像幀
    //--------------------------------------------------------------------
    SLONG   body_front_id;  //人物身上的效果圖..npc前面的圖
    SLONG   body_back_id;   //人物身上的效果圖..npc後面的圖
    SLONG   body_frame;     //人物身上的幀數
    //
} NPC_SHOW, *LPNPC_SHOW;

// G L O B A L S //////////////////////////////////////////////////////////////////////////////////////////////////////
extern  SLONG       game_npc_max;

// F U N C T I O N S    P R O T O T Y P E /////////////////////////////////////////////////////////////////////////////
extern  int     init_npc(void);
extern  void    active_npc(int active);
extern  void    free_npc(void);
//
extern  void    init_one_game_npc(SLONG npc_no);
extern  void    clear_one_game_npc(SLONG npc_no);
extern  void    init_all_game_npc(void);

extern  void    set_npc_ext_id(SLONG npc_no, SLONG id);
extern  void    set_npc_ext_frame(SLONG npc_no, SLONG frame);

extern  void    clear_npc_ext_effect(SLONG npc_no);
extern  void    abort_npc_doing(SLONG npc_no);
extern  void    set_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    change_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
//
extern  void    refresh_map_npc(void);
extern  void    refresh_one_npc(SLONG npc_no);
extern  void    refresh_npc_state_lapse(SLONG npc_no);
extern  void    debug_show_map_npc_data(SLONG npc_no, BMP *bitmap);
//
extern  void    update_map_npc_object(void);
//
extern  void    active_map_npc(SLONG npc_no);
extern  void    del_map_npc(SLONG npc_no);
extern  void    clear_all_map_npc(void);
//
extern  SLONG   get_npc_magic_standpoint_relation( SLONG src_npc, SLONG dest_npc);
//
extern  void    clear_npc_talk(SLONG npc_no);
extern  SLONG   add_npc_talk(SLONG npc_no, DWORD talk_time, USTR* text);
extern  void    set_npc_talk_position(SLONG npc_no, SLONG talk_x, SLONG talk_y);
extern  void    redraw_npc_talk(SLONG sx, SLONG sy, SLONG npc_no, BMP *bitmap);
extern  void    redraw_npc_name(SLONG top_cx, SLONG top_cy, SLONG npc_no, BMP *bitmap);
extern  void    local_refresh_npc_talk(void);
extern  SLONG   get_npc_talk_flag(SLONG npc_no);
extern  void    set_npc_talk_flag(SLONG npc_no, SLONG flag);
//
extern  void    init_npc_talk_list(void);
extern  void    clear_npc_talk_list(void);
extern  void    add_npc_to_npc_talk_list(SLONG npc_no);
extern  void    sort_npc_talk_list(void);
extern  void    redraw_map_npc_talk(SLONG map_no, SLONG map_sx, SLONG map_sy, BMP *bitmap);

//ui npc functions ---------------------------------------------------------
extern	void    refresh_ui_npc(void);
extern	void    ui_redraw_one_npc_object(SLONG npc_no, BMP *bitmap);
extern	void    loop_ui_npc_dir(SLONG npc_no);
extern	void    update_ui_npc_object(void);
extern	void    free_ui_npc_object(void);
//
extern  void    init_npc_show(void);
extern  void    update_npc_show_shadow_move(SLONG index, SLONG x, SLONG y, SLONG z, SLONG with_shadow);
extern  void    set_npc_show_ext_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_ext_id(SLONG index);
extern  void    set_npc_show_ext_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_ext_frame(SLONG index);
extern  void    set_npc_show_head_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_head_id(SLONG index);
extern  void    set_npc_show_head_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_head_frame(SLONG index);
extern  void    set_npc_show_foot_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_foot_id(SLONG index);
extern  void    set_npc_show_foot_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_foot_frame(SLONG index);
extern  void    set_npc_show_body_front_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_body_front_id(SLONG index);
extern  void    set_npc_show_body_back_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_body_back_id(SLONG index);
extern  void    set_npc_show_body_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_body_frame(SLONG index);
//
extern  void    set_npc_effect(SLONG npc_no, SLONG effect);
extern	SLONG	get_npc_effect(SLONG npc_no);
extern  SLONG   get_npc_flag(SLONG npc_no);
extern  void    set_npc_flag(SLONG npc_no, SLONG flag);
extern	void	set_npc_object_index(SLONG npc_no, SLONG index);
extern	SLONG	get_npc_object_index(SLONG npc_no);
extern	void	set_npc_ext_id(SLONG npc_no, SLONG ext_id);
extern	SLONG	get_npc_ext_id(SLONG npc_no);
extern	void	set_npc_ext_frame(SLONG npc_no, SLONG ext_frame);
extern	SLONG	get_npc_ext_frame(SLONG npc_no);
extern	void    set_npc_foot_id(SLONG npc_no,SLONG foot_id);
extern	SLONG   get_npc_foot_id(SLONG npc_no);
extern	void    set_npc_foot_frame(SLONG npc_no,SLONG foot_frame);
extern	SLONG   get_npc_foot_frame(SLONG npc_no);
extern	void    set_npc_head_id(SLONG npc_no,SLONG head_id);
extern	SLONG   get_npc_head_id(SLONG npc_no);
extern	void    set_npc_head_frame(SLONG npc_no,SLONG head_frame);
extern	SLONG   get_npc_head_frame(SLONG npc_no);
extern	void    set_npc_body_front_id(SLONG npc_no,SLONG body_id);
extern	SLONG   get_npc_body_front_id(SLONG npc_no);
extern	void    set_npc_body_back_id(SLONG npc_no,SLONG body_id);
extern	SLONG   get_npc_body_back_id(SLONG npc_no);
extern	void    set_npc_body_frame(SLONG npc_no,SLONG body_frame);
extern	SLONG   get_npc_body_frame(SLONG npc_no);
//
extern	SLONG	get_npc_talk_lines(SLONG npc_no);
extern	CHAR*	get_npc_talk_text(SLONG npc_no, SLONG line_index);
extern	void	set_npc_talk_time(SLONG npc_no, ULONG talk_time);
extern	ULONG	get_npc_talk_time(SLONG npc_no);
extern	void	set_npc_talk_position(SLONG npc_no, SLONG sx, SLONG sy);
extern	void	get_npc_talk_position(SLONG npc_no, SLONG *sx, SLONG *sy);
//
extern  void    loop_npc_ext_frame(SLONG npc_no);
//
extern  void    ClientChangeCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    set_npc_ai_function(void);
extern	void    set_npc_doing_functions(void);
//
extern	void	set_npc_rgb_scroll(SLONG npc_no, UCHR *buffer);
extern	UCHR*	get_npc_rgb_scroll(SLONG npc_no);

//
// Map npc object functions:
//
SLONG	add_map_npc_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick);
SLONG	del_map_npc_object(SLONG object_index);
void	draw_map_npc_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_npc_object(SLONG object_index);
SLONG	change_map_npc_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_npc_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
									   SLONG *ex, SLONG *ey, POLY **poly);
//讀取需要的npc的圖檔管理機制
extern  void    npc_effect_id_manage(SLONG *npc_id,SLONG *npc_show_id,SLONG *npc_frame,SLONG *npc_show_frame);
//
#endif//NPC_H_INCLUDE
