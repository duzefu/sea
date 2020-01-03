/*
**	NetGE_Magic.h 
**	magic part functions.
**
**	Jack, 2003.1.24.
*/
#pragma once
#include    "NetGE_MagicBreak.h" 

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_GAME_MAGIC_PART			10240   //遊戲中法術組件的數目
#define HEAD_GAME_MAGIC_PART		1       //用作頭接點的法術組件數目, 1對應一個ZONE.
#define MAX_BREAK_MAGIC_PART		512		//單一法術時產生的法術組件



//
//MAGIC STATE(法術目前狀態)-----------------
//
#define MAGIC_STATE_SLEEP           1		//休眠狀態中
#define MAGIC_STATE_SHIFT           2		//移動中
#define MAGIC_STATE_EXPLODE         3		//爆炸中
//
#define MAX_MAGIC_DELAY_TICK        99999   //
#define	MAGIC_VOICE_BROKEN			1		//法術組件爆炸

//
//MAGIC FRAME TYPES(法術關鍵幀定義) --------
//
#define MAGIC_KEY_FRAME_NONE		0		//非關鍵幀
#define MAGIC_KEY_FRAME_HEAD		1		//關鍵幀(第一幀)
#define MAGIC_KEY_FRAME_HALF		2		//中間幀
#define MAGIC_KEY_FRAME_TAIL		3		//最後幀
#define MAGIC_KEY_FRAME_OVER		4		//剛好超過最後幀

//
#define	GRAVITY_ACCELERATION		(-3.5)	//重力加速度

//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
//MAGIC PART STRUCT(法術部件結構定義)---------------------------------------
//
typedef struct  POS_MAGIC_PART
{
    //-
    union
    {
        SLONG   Flag;      //使用標誌
        SLONG   Tail;      //鏈尾指標
    };
    SLONG   Next;          //後繼指標
    //和技能相關的數據項
    SLONG   SkillIndex;		//法術數據索引...紀錄..該法術代表的是那個技能
    SLONG   SkillLevel;     //    
    SLONG   SourceNo;		//施法者
    SLONG   TargetNo;		//施法對象
    //和座標相關的數據項
    SLONG   DestX;			//目標位置
    SLONG   DestY;			//
    SLONG   DestZ;			//    
    SLONG   OrigX;			//起始位置
    SLONG   OrigY;			//
    SLONG   OrigZ;			//
    SLONG   CurrX;          //當前位置
    SLONG   CurrY;          //
    SLONG   CurrZ;          //    
    //和組件屬性相關的數據項...物件本生身行為相關的項目
    SLONG   State;          //目前狀態
    //
    SLONG   SleepTick;		//休眠期, 發出後先休眠的時間    
    SLONG   LifeTick;		//生命期
    SLONG   DelayTick;		//執行後的延時時間....用於數值計算的間隔時間
    //
    SLONG   Step;           //距離起始點的步數
    //
    //和上圖相關的數據區
    SLONG   ImgDir;         //物件的當前方向...(使用...該物件最多方向所對應的編號)
    SLONG   ObjectIndex;	//物件指標...該magic_part 在地圖object 中的編號
    SLONG   ImageID;		//物件影像ID
    SLONG   ImageFrame;     //物件影像幀
    //
    POS_MAGIC_UNIT   unit_data; //物件的一些其他的控制函數

}TPOS_MAGIC_PART, *LPTPOS_MAGIC_PART;
//
typedef struct  POS_MAGIC_PIPE
{
    SLONG   lDestNo;		//目標 NPC
} TPOS_MAGIC_PIPE, *LPTPOS_MAGIC_PIPE;
//
typedef	SLONG	(*FNBREAKMAGIC) ( SLONG skill_no, SLONG npc_no, SLONG type, SLONG dest_x, SLONG dest_y, SLONG dest_no);
////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS 
////////////////////////////////////////////////////////////////////////////////////////////////////
extern  TPOS_MAGIC_PART		ZoneMagicPart[MAX_GAME_MAGIC_PART];
extern  TPOS_MAGIC_PART		BreakMagicPart[MAX_BREAK_MAGIC_PART];
extern  SLONG				g_lMaxBreakMagicParts;
extern  TPOS_MAGIC_PIPE		g_MagicPipe;


///////////////////////////////////////////////////////////////////////////
// FUNCTIONS 
///////////////////////////////////////////////////////////////////////////

//
// zone magic part base functions -------------------------------
//
void	SetZoneMagicPartFlag(SLONG lIndex, SLONG lFlag);
SLONG	GetZoneMagicPartFlag(SLONG lIndex);
void	SetZoneMagicPartTail(SLONG lIndex, SLONG lTail);
SLONG	GetZoneMagicPartTail(SLONG lIndex);
void	SetZoneMagicPartNext(SLONG lIndex, SLONG lNext);
SLONG	GetZoneMagicPartNext(SLONG lIndex);
void	SetZoneMagicPartSkillIndex(SLONG lIndex, SLONG lSkillIndex);
SLONG	GetZoneMagicPartSkillIndex(SLONG lIndex);
void	SetZoneMagicPartSkillLevel(SLONG lIndex, SLONG SkillLevel);
SLONG	GetZoneMagicPartSkillLevel(SLONG lIndex);
void	SetZoneMagicPartState(SLONG lIndex, SLONG lState);
SLONG	GetZoneMagicPartState(SLONG lIndex);
//
void	SetZoneMagicPartSourceNo(SLONG lIndex, SLONG lNo);
SLONG	GetZoneMagicPartSourceNo(SLONG lIndex);
void	SetZoneMagicPartTargetNo(SLONG lIndex, SLONG lNo);
SLONG	GetZoneMagicPartTargetNo(SLONG lIndex);
void	SetZoneMagicPartLifeTick(SLONG lIndex, SLONG lTick);
SLONG	GetZoneMagicPartLifeTick(SLONG lIndex);
void	SetZoneMagicPartDelayTick(SLONG lIndex, SLONG lTick);
SLONG	GetZoneMagicPartDelayTick(SLONG lIndex);
void	SetZoneMagicPartSleepTick(SLONG lIndex, SLONG lTick);
SLONG	GetZoneMagicPartSleepTick(SLONG lIndex);
//
void	SetZoneMagicPartOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
void	GetZoneMagicPartOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
void	SetZoneMagicPartCurrPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
void	GetZoneMagicPartCurrPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
void	SetZoneMagicPartDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
void	GetZoneMagicPartDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
void	SetZoneMagicPartStep(SLONG lIndex, SLONG lStep);
SLONG	GetZoneMagicPartStep(SLONG lIndex);
//
void	SetZoneMagicPartObjectIndex(SLONG lIndex, SLONG lObjectIndex);
SLONG	GetZoneMagicPartObjectIndex(SLONG lIndex);
void	SetZoneMagicPartImageID(SLONG lIndex, SLONG lID);
SLONG	GetZoneMagicPartImageID(SLONG lIndex);
void	SetZoneMagicPartImageFrame(SLONG lIndex, SLONG lFrame);
SLONG	GetZoneMagicPartImageFrame(SLONG lIndex);

SLONG	GetBreakMagicPartAppearImgId(SLONG lIndex);
void 	SetBreakMagicPartAppearImgId(SLONG lIndex, SLONG lAppearImgId);

void    SetZoneMagicPartImgDir(SLONG lIndex, SLONG lDir);
SLONG   GetZoneMagicPartImgDir(SLONG lIndex);
//過程動畫
SLONG	GetZoneMagicPartProcImagId(SLONG lIndex);
void 	SetZoneMagicPartProcImagId(SLONG lIndex, SLONG lProcImagId);
//消失動畫 (沒有該動畫 用 -1) 物體.在播放動畫的時候..不會有該過程
SLONG	GetZoneMagicPartDisAppearImgId(SLONG lIndex);
void 	SetZoneMagicPartDisAppearImgId(SLONG lIndex, SLONG lDisAppearImgId);
SLONG	GetZoneMagicPartAppearImgId(SLONG lIndex);
void 	SetZoneMagicPartAppearImgId(SLONG lIndex, SLONG lAppearImgId);

//方向數據
SLONG	GetZoneMagicPartDirNum(SLONG lIndex);
void 	SetZoneMagicPartDirNum(SLONG lIndex, SLONG lDirNum);
//運動的軌跡
SLONG	GetZoneMagicPartPath(SLONG lIndex);
void 	SetZoneMagicPartPath(SLONG lIndex, SLONG lPath);
//生存的方式
SLONG	GetZoneMagicPartSurvial(SLONG lIndex);
void 	SetZoneMagicPartSurvial(SLONG lIndex, SLONG lSurvial);
//上圖的效果
SLONG	GetZoneMagicPartDrawEff(SLONG lIndex);
void 	SetZoneMagicPartDrawEff(SLONG lIndex, SLONG lDrawEff);
//相關的阻擋類型
SLONG	GetZoneMagicPartStop(SLONG lIndex);
void 	SetZoneMagicPartStop(SLONG lIndex, SLONG lStop);

//設置移動速度
void	SetZoneMagicPartSpeed(SLONG lIndex, double fSpeed);
double	GetZoneMagicPartSpeed(SLONG lIndex);

void	SetZoneMagicPartVertSpeed(SLONG lIndex, double fVertSpeed);
double	GetZoneMagicPartVertSpeed(SLONG lIndex);

//
// zone magic misc parts functions --------------------
//
void	InitZoneMagicPart(void);
void	ResetZoneMagicPart(void);
void	ClearZoneMagicPartObjectIndex(void);
SLONG	IsZoneMagicPartUnused(SLONG index);
SLONG	FindUnusedZoneMagicPart(void);
SLONG	AddZoneMagicPart(TPOS_MAGIC_PART *MP);
void	DeleteZoneMagicPart(SLONG lIndex);
void	CopyMagicPartData(TPOS_MAGIC_PART *pDest, TPOS_MAGIC_PART *pSrc);
void	ReduceVoidZoneMagicPart(void);
SLONG	CountZoneMagicPart(void);
void	AppendBreakMagicParts(void);
//
void	LoopZoneMagicPartFrame(SLONG p);
SLONG	OverZoneMagicPartFrame(SLONG p);
SLONG	KeyPlayZoneMagicPartFrame(SLONG p);
void	PrepareZoneMagicPartForExplode(SLONG p);
void	PrepareZoneMagicPartForShift(SLONG p);

//
// magic pipe functions -------------------------------
//
void	SetMagicPipeDestNo(SLONG lDestNo);
SLONG	GetMagicPipeDestNo(void);

//
// break magic part functions -------------------------
//
void	SetBreakMagicPartsCount(SLONG lCounts);
SLONG	GetBreakMagicPartsCount(void);
//
void	SetBreakMagicPartFlag(SLONG lIndex, SLONG lFlag);
SLONG	GetBreakMagicPartFlag(SLONG lIndex);
void	SetBreakMagicPartSkillIndex(SLONG lIndex, SLONG lSkillIndex);
SLONG	GetBreakMagicPartSkillIndex(SLONG lIndex);
void	SetBreakMagicPartSkillLevel(SLONG lIndex, SLONG SkillLevel);
SLONG	GetBreakMagicPartSkillLevel(SLONG lIndex);
void	SetBreakMagicPartState(SLONG lIndex, SLONG lState);
SLONG	GetBreakMagicPartState(SLONG lIndex);
//
void	SetBreakMagicPartSourceNo(SLONG lIndex, SLONG lNo);
SLONG	GetBreakMagicPartSourceNo(SLONG lIndex);
void	SetBreakMagicPartTargetNo(SLONG lIndex, SLONG lNo);
SLONG	GetBreakMagicPartTargetNo(SLONG lIndex);
void	SetBreakMagicPartLifeTick(SLONG lIndex, SLONG lTick);
SLONG	GetBreakMagicPartLifeTick(SLONG lIndex);
void	SetBreakMagicPartDelayTick(SLONG lIndex, SLONG lTick);
SLONG	GetBreakMagicPartDelayTick(SLONG lIndex);
void	SetBreakMagicPartSleepTick(SLONG lIndex, SLONG lTick);
SLONG	GetBreakMagicPartSleepTick(SLONG lIndex);
//
void	SetBreakMagicPartOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
void	GetBreakMagicPartOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
void	SetBreakMagicPartCurrPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
void	GetBreakMagicPartCurrPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
void	SetBreakMagicPartDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
void	GetBreakMagicPartDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
void	SetBreakMagicPartStep(SLONG lIndex, SLONG lStep);
SLONG	GetBreakMagicPartStep(SLONG lIndex);
//
//
void	SetBreakMagicPartObjectIndex(SLONG lIndex, SLONG lObjectIndex);
SLONG	GetBreakMagicPartObjectIndex(SLONG lIndex);
void	SetBreakMagicPartImageID(SLONG lIndex, SLONG lID);
SLONG	GetBreakMagicPartImageID(SLONG lIndex);
void	SetBreakMagicPartImageFrame(SLONG lIndex, SLONG lFrame);
SLONG	GetBreakMagicPartImageFrame(SLONG lIndex);
//
SLONG	GetBreakMagicPartAppearImgId(SLONG lIndex);
void 	SetBreakMagicPartAppearImgId(SLONG lIndex, SLONG lAppearImgId);

void    SetBreakMagicPartImgDir(SLONG lIndex, SLONG lDir);
SLONG   GetBreakMagicPartImgDir(SLONG lIndex);

//過程動畫
SLONG	GetBreakMagicPartProcImagId(SLONG lIndex);
void 	SetBreakMagicPartProcImagId(SLONG lIndex, SLONG lProcImagId);
//消失動畫 (沒有該動畫 用 -1) 物體.在播放動畫的時候..不會有該過程
SLONG	GetBreakMagicPartDisAppearImgId(SLONG lIndex);
void 	SetBreakMagicPartDisAppearImgId(SLONG lIndex, SLONG lDisAppearImgId);
//方向數據
SLONG	GetBreakMagicPartDirNum(SLONG lIndex);
void 	SetBreakMagicPartDirNum(SLONG lIndex, SLONG lDirNum);
//運動的軌跡
SLONG	GetBreakMagicPartPath(SLONG lIndex);
void 	SetBreakMagicPartPath(SLONG lIndex, SLONG lPath);
//生存的方式
SLONG	GetBreakMagicPartSurvial(SLONG lIndex);
void 	SetBreakMagicPartSurvial(SLONG lIndex, SLONG lSurvial);
//上圖的效果
SLONG	GetBreakMagicPartDrawEff(SLONG lIndex);
void 	SetBreakMagicPartDrawEff(SLONG lIndex, SLONG lDrawEff);
//相關的阻擋類型
SLONG	GetBreakMagicPartStop(SLONG lIndex);
void 	SetBreakMagicPartStop(SLONG lIndex, SLONG lStop);
//移動速度
void	SetBreakMagicPartSpeed(SLONG lIndex, double fSpeed);
double	GetBreakMagicPartSpeed(SLONG lIndex);

void	SetBreakMagicPartVertSpeed(SLONG lIndex, double fVertSpeed);
double	GetBreakMagicPartVertSpeed(SLONG lIndex);

//  把魔法組件的方向..改變到..外邊圖檔的方向
//----
SLONG   MagicDirToImgDir(SLONG lMagicDir, SLONG MaxDir);
//拷貝MAGIC_PART中的TPOS_MAGIC_UNIT子塊
void    SetBreakMagicPartMagicUnit(SLONG lIndex, TPOS_MAGIC_UNIT *p_unit);

// break magic functions
//
void	InitBreakMagicFunctions(void);
void	SetBreakMagicFunction(SLONG lSkillNo, FNBREAKMAGIC pFunc);
void	ExecBreakMagic(SLONG lSkillNo, SLONG lSrcNo, SLONG lType, SLONG lDestX, SLONG lDestY, SLONG lDestNo);


