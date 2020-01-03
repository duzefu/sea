/*
**	NetGE_Doing.h 
**	character doing functions header.
**
**	Jack, 2003.1.7
*/
#pragma once


//
//DEFINES /////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_NPC_STEP_COUNT          2   //人物移動時每幀重複次數

//關於幀數控制的函數
#define NPC_KEY_FRAME_NONE          0   //非關鍵幀
#define NPC_KEY_FRAME_HEAD          1   //關鍵幀(第一幀)
#define NPC_KEY_FRAME_HALF          2   //中間幀
#define NPC_KEY_FRAME_TAIL          3   //最後幀
#define NPC_KEY_FRAME_BACK          4   //收招幀
//NPC動畫ID是否改變的標誌
#define NPC_ID_CHANGE_NONE          0   //圖像id沒有改變
#define NPC_ID_CHANGE_YES           1   //圖像id發生了改變
//關移動的定義
#define NPC_MOVE_MOVEING            0   //npc移動在移動過程中
#define NPC_MOVE_ARRIVE             1   //npc移動到達了目標
#define NPC_MOVE_CANT_ARRIVE        2   //npc移動不能到達
//關於npc師法動作的定義
#define NPC_MAGIC_DOING             0   //在施法過程中
#define NPC_MAGIC_START             1   //開始施法
#define NPC_MAGIC_FIRE              2   //到了攻擊幀
#define NPC_MAGIC_OVER              3   //施法動作結束
//-----------------------------------------------------------
//人物正在進行的事務類型(NPC DOING KINDS), 根據玩家的操作定義
//
//   注意阿...!!!!!
//          在增加一個DOING_KIND 一定要在  
//                  客戶端   
//                          npc.cpp    set_npc_doing  增加代嗎
//                  服務器端
//                          ServerCharacterDoing.cpp SetCharacterDoing 增加代嗎
//-----------------------------------------------------------
//無任何操作時，停留在原地時
#define DOING_KIND_IDLE                         0   //閒人原地不動(idle)
#define DOING_KIND_MUSE                         1   //冥想
#define DOING_KIND_SPOWER                       2   //蓄力中
#define DOING_KIND_CHANGEMAP                    3   //切換地圖中
#define	DOING_KIND_STAND						5	//原地站立(改變方向)
#define DOING_KIND_UPGRADE                      6   //升級...(npc等級提昇)
//
//點擊地圖上的空白區域，地圖上移動
#define DOING_KIND_MOVE_TO                      10  //行走到目標點(trend)(moveto)

#define DOING_KIND_CLASH                        12  //衝撞到目標點
// mark by lijun 2003-05-21
/*
#define	DOING_KIND_FIGHT_IDLE					4	//戰鬥待機
#define DOING_KIND_MAGIC_POSITION               11  //對目標點施法
#define DOING_KIND_GAD                          13  //地圖上隨機行走
#define DOING_KIND_PATROL                       14  //地圖上兩點之間走動
#define	DOING_KIND_FIGHT_GAD					15	//戰鬥隨機行走
#define	DOING_KIND_FIGHT_PATROL					16	//戰鬥地圖上兩點之間走動
#define DOING_KIND_ATTACK_NPC                   31  //對人物攻擊
#define DOING_KIND_MAGIC_NPC                    32  //對人物施法
*/

//NPC的戰鬥中的行為分段
#define DOING_KIND_SKILL_ACTION                 17  //通用的..在戰鬥中執行莫個技能的動作...沒有特別去寫..戰鬥技能的動作都是使用這個
//
//點擊地圖上的物品
#define DOING_KIND_PICK_ITEM                    20  //拾取地上物品(pick item)
//
//點擊地圖上的 NPC
#define DOING_KIND_TALK_WITH_NPC                30  //與人物對話(talk)
#define DOING_KIND_SEQUENTIAL_ATTACK_NPC        33  //對人物進行連續攻擊
//
//被動發生
#define DOING_KIND_BEATED                       40  //人物被擊
#define DOING_KIND_DEAD                         41  //人物死亡
#define DOING_KIND_DOWN_AND_OUT                 42  //人物被擊倒
#define DOING_KIND_DEFENCE                      43  //人物格擋
#define DOING_KIND_DEFENCED                     44  //人物被格擋
//
//人物表情動作
//#define DOING_KIND_CHEER                        50  //歡呼
#define DOING_KIND_ANGRY                        51  //生氣
#define DOING_KIND_BECKON                       52  //招手
//#define DOING_KIND_COURT                        53  //求愛
#define DOING_KIND_FAINT                        54  //暈倒
#define DOING_KIND_SAY_NO                       55  //說不
#define DOING_KIND_BOW                          56  //鞠躬
#define DOING_KIND_WIN                          57  //勝利
#define DOING_KIND_SWASH                        58  //嚇唬
#define DOING_KIND_XXPOWER                      59  //假裝蓄力
#define DOING_KIND_XXBEATED                     60  //假裝被擊
//
#define CHARACTER_DOING_MAX_LAND                64  //陸地npc最多的(AI)行為數目
#define MAX_CHARACTER_DOING_KINDS               128 //NPC事務類型的總數
//
#define DOING_KIND_SEA_ACC_MOVE_TO              (CHARACTER_DOING_MAX_LAND+0)  //海上npc的無加速度航行
#define DOING_KIND_SEA_IDLE                     (CHARACTER_DOING_MAX_LAND+2)  //海上npc的再原地的待機
#define DOING_KIND_SEA_SAIL_TO                  (CHARACTER_DOING_MAX_LAND+3)  //海上船的航行到
#define DOING_KIND_SEA_WALK_TO                  (CHARACTER_DOING_MAX_LAND+4)  //海上npc的行走到


//--------------------
//人物動作(NPC ACTION)
//--------------------
#define     CHARACTER_ACTION_BLOCK_NORMAL       0   //普通動作類
#define     CHARACTER_ACTION_BLOCK_FIGHT        1   //戰鬥動作類
#define     CHARACTER_ACTION_BLOCK_WARD         2   //格擋動作類
//陸地NPC的行為
#define AC_WAIT_0       0   //待機0
#define AC_WAIT_1       1   //待機1
#define AC_RUN          2   //奔跑
#define AC_BEATED       3   //被擊
#define AC_WARD         4   //格擋
#define AC_FAINT        5   //死亡倒地, 暈倒
#define AC_ATTACK_0     6   //攻擊0
#define AC_ATTACK_1     7   //攻擊1	
#define AC_CLIMB        8   //爬起	
#define AC_WIN          9   //勝利	
#define AC_ANGRY        10  //生氣	
#define AC_BECKON       11  //招手	
#define AC_BOW          12  //行禮	
#define AC_SAY_NO       13  //說不	
#define AC_SPOWER       14  //蓄力	
#define AC_MAGIC        15  //施法	
#define AC_FCHANGE      16  //戰鬥切換
#define AC_SPECIAL_0    17  //特殊0
#define AC_SPECIAL_1    18  //特殊1	
#define AC_SPECIAL_2    19  //特殊2	
#define AC_SPECIAL_3    20  //特殊3	
#define AC_SPECIAL_4    21  //特殊4	
#define AC_SPECIAL_5    22  //特殊5	
#define AC_SPECIAL_6    23  //特殊6
//海洋NPC的行為
#define AC_SEA_WALK                 0	//海上行走
#define AC_SEA_IDLE                 1   //海上待機

//-----------------
//人物方向(NPC DIR)
//-----------------
#define NPC_DIRS                    8    //人物共有方向數

//未換裝之前的方向定義，請勿刪除！
/*
#define NPC_UP                      0    //上
#define NPC_DOWN                    1    //下
#define NPC_LEFT                    2    //左
#define NPC_RIGHT                   3    //右
#define NPC_RIGHT_UP                4    //右上
#define NPC_LEFT_DOWN               5    //左下
#define NPC_LEFT_UP                 6    //左上
#define NPC_RIGHT_DOWN              7    //右下
*/
//換裝後的陸地人物方向定義
#define NPC_UP                      0    //上
#define NPC_RIGHT_UP                1    //右上
#define NPC_RIGHT                   2    //右
#define NPC_RIGHT_DOWN              3    //右下
#define NPC_DOWN                    4    //下
#define NPC_LEFT_DOWN               5    //左下
#define NPC_LEFT                    6    //左
#define NPC_LEFT_UP                 7    //左上
//
//換裝後的船隻方向定義(與換裝前的NPC相同)
#define SEANPC_UP                   0    //上
#define SEANPC_DOWN                 1    //下
#define SEANPC_LEFT                 2    //左
#define SEANPC_RIGHT                3    //右
#define SEANPC_RIGHT_UP             4    //右上
#define SEANPC_LEFT_DOWN            5    //左下
#define SEANPC_LEFT_UP              6    //左上
#define SEANPC_RIGHT_DOWN           7    //右下

//
typedef	SLONG   (*FNDOING)(SLONG lIndex);
typedef	void    (*FNCHANGEDOING)(SLONG lIndex,SLONG lDoingKind, SLONG lDoingStep, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);

//
//GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////
//

//
//FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////
//
extern  void    DirLoopCharacterFrame(SLONG lIndex);
extern  SLONG   DirKeyLoopCharacterFrame(SLONG lIndex);
extern  SLONG   DirTailCharacterFrame(SLONG lIndex);
extern  void    DirHeadCharacterFrame(SLONG lIndex);
extern  SLONG   DirHalfCharacterFrame(SLONG lIndex);
extern  SLONG   DirCharacterFrame(SLONG lIndex, SLONG no_play_frame);
extern  void    DirFastLoopCharacterFrame(SLONG lIndex);
extern  SLONG   DirFastKeyLoopCharacterFrame(SLONG lIndex);
extern  SLONG   DirFastTailCharacterFrame(SLONG lIndex);
extern  SLONG   DirFastHalfCharacterFrame(SLONG lIndex);
extern  void    DirSkipLoopCharacterFrame(SLONG lIndex);
extern  SLONG   DirSequentialCharacterFrame(SLONG lIndex);
//
extern	SLONG	ClockwiseLoopCharacterDir(SLONG dir);
extern	SLONG	AntiClockwiseLoopCharacterDir(SLONG dir);
extern	SLONG   ApproachCharacterDir(SLONG dx,SLONG dy);
//
/*
extern  SLONG   GetIdleAction(SLONG is_fight);
extern  SLONG   GetSpecialIdleAction(SLONG is_fight);
extern  SLONG   GetRunAction(SLONG is_fight);
extern	SLONG	GetMagicAction(void);
*/
extern  SLONG   GetSequentialAttackAction(SLONG attack_step);
//
extern	void	InitCharacterDoingSomethingFunction(void);
extern	void	SetCharacterDoingSomethingFunction(SLONG lDoingKind, FNDOING pFunc);
extern  void    SetChangeCharacterDoingSomethingFun(SLONG lIndex, FNCHANGEDOING pFunc);
extern	SLONG   ExecCharacterDoingSomething(SLONG lIndex, SLONG lDoingKind);
extern  void    ExecChangeCharacterDoingSomethingFun(SLONG lIndex,SLONG lDoingKind, SLONG lDoingStep, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);

extern  SLONG   GetSkillNeedDoingKind(SLONG lIndex);
//
extern  void    InitCharacterDoingPriority(void);
extern	SLONG   LoadCharacterDoingPriority(CHAR *szFileName);
extern  void    FreeCharacterDoingPriority(void);
extern  SLONG   IsHighPriorityDoingKind(SLONG cur_doing, SLONG new_doing);
extern  void    DebugLogCharacterDoingPriority(void);
//
extern  void    InitObjectImageInfo(void);
extern  SLONG   LoadObjectImageInfo(CHAR *szFileName);
extern  void    FreeObjectImageInfo(void);
extern  SLONG   GetObjectImageTotalFrames(SLONG ID);
extern	void	SetObjectImageTotalFrames(SLONG ID, SLONG frames);
//
extern	void    InitCharacterFileInfo(void);
extern	SLONG   LoadCharacterFileInfo(CHAR *szFileName);
extern	void    FreeCharacterFileInfo(void);
extern  SLONG   GetCharacterFileActionImageID( SLONG file_index, SLONG action_block, SLONG action);
extern	void    DebugLogCharacterFileInfo(void);
//
extern	void    InitSeaCharacterFileInfo(void);
extern	SLONG   LoadSeaCharacterFileInfo(CHAR *szFileName);
extern	void    DebugLogSeaCharacterFileInfo(void);
extern	SLONG   GetSeaCharacterFileSailType(SLONG file_index);
extern	SLONG   GetSeaCharacterFileTrackID(SLONG file_index );
extern	SLONG   GetSeaCharacterFileActionImageID(SLONG file_index, SLONG action);
//
extern	SLONG   GetOnSeaIdleAction(SLONG fight_flag);
extern	SLONG   GetOnSeaMoveAction(SLONG fight_flag);
//
extern	void    DirHeadSeaCharacterFrame(SLONG npc_no, SLONG old_dir);
extern	void    DirFastLoopSeaCharacterFrame(SLONG npc_no);
extern	SLONG   ApproachSeaCharacterDir(FLOAT dir[3]);
//
SLONG   StatuseToActionBlocks(SLONG fight_flag, SLONG block_flag);
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

