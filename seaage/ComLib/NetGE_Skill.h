/*
**	NetGE_Skill.h 
**	skill functions header.
**
**	Jack, 2003.1.4
*/
#pragma once

//
// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_GAME_SKILL_BASES            256         //遊戲中的技能數目
// mark by lijun 2003-04-21
//#define MAX_SKILL_LEVELS                200         //技能升級的最大等級數
#define MAX_SKILL_LEVELS                40           //技能升級的最大等級數
//

//------------
//法術屬性標誌
//------------
#define MAGIC_ATTRIB_LIST_VISIBLE       0x00000001  //地圖技能列表上會顯示本技能
#define MAGIC_ATTRIB_UNDER_LIST         0x00000002  //顯示在地圖快捷圖標列的最底下
#define MAGIC_ATTRIB_FOR_LAND           0x00000010  //陸地上使用的技能
#define MAGIC_ATTRIB_FOR_SEA            0x00000020  //海洋上使用的技能
#define MAGIC_ATTRIB_PEACE              0x00000040  //和平模式下使用的技能
#define MAGIC_ATTRIB_FIGHT              0x00000080  //戰鬥模式下使用的技能
#define MAGIC_ATTRIB_LEFT_HAND          0x00000100  //可以裝備在左手上
#define MAGIC_ATTRIB_RIGHT_HAND         0x00000200  //可以裝備在右手上
//
#define MAGIC_ATTRIB_MAGIC_AREA_SELF    0x00001000  //在NPC的位置上出現魔法陣...要是沒有就是出現在mouse的位置上(需要蓄力)
// mark by lijun 2003-04-21
//#define MAGIC_ATTRIB_PASSIVE            0x00001000  //本技能是被動技(學會後就一直有作用)
//#define MAGIC_ATTRIB_NEED_PREPARE       0x00010000  //本技能需要前置時間
//#define MAGIC_ATTRIB_NEED_SPOWER        0x00020000  //本技能需要先蓄力
//--------
//  法術使用的目標定義
//--------
#define MAGIC_TAG_NORMAL_NPC            0x00000001  //普通npc.
#define MAGIC_TAG_FRIEND_NPC            0x00000002  //朋友npc隊友
#define MAGIC_TAG_ENEMY_NPC             0x00000004  //敵人npc
#define MAGIC_TAG_SELF                  0x00000008  //自己
#define MAGIC_TAG_DEAD_NPC              0x00000010  //目標要求是死人(沒有該項就是對活人)
#define MAGIC_TAG_NEED_NPC              0x00000100  //目標需要(npc目標.更具上面..活人或者死人)...有該標誌表示..在沒有目標的時候技能無法使用
#define MAGIC_TAG_POSITION              0x00000200  //目標不需要(npc),,可以對著空地使用
//--------
//命中方式...技能的結算方式
//--------
#define     MAGIC_HIT_TYPE_RANGE            0x00000001  //範圍命中
#define     MAGIC_HIT_TYPE_SINGLE_ALWAYS    0x00000002  //當體..攻擊一定命中
#define     MAGIC_HIT_TYPE_SINGLE_MISS      0x00000004  //當體..攻擊可能會MISS
//----
//  技能的攻擊類型
//----
#define     MAGIC_ATTACK_TYPE_PHYSICS       0   //物理攻擊類型
#define     MAGIC_ATTACK_TYPE_MAGIC         1   //法術攻擊類型
#define     MAGIC_ATTACK_TYPE_SPECIAL       2   //特殊攻擊類型
//----
//法術編號定義
//----
//common magic no defines ---------------------------------------------------------
#define MAGIC_NO_JOIN_TEAM              0   //組隊
#define MAGIC_NO_LEAVE_TEAM             1   //離隊
#define MAGIC_NO_TRADE                  2   //交易
#define MAGIC_NO_FOLLOW                 3   //跟隨
#define MAGIC_NO_IDENTIFY               4   //鑒定
//
//land magic no defines -----------------------------------------------------------
#define MAGIC_NO_WALK                   20  //行走
#define MAGIC_NO_MUSE                   21  //冥想
#define MAGIC_NO_ESCRIME                22	//劍術
#define MAGIC_NO_SEQUENTIAL_ESCRIME     23  //連擊
#define MAGIC_NO_STRONG                 24	//強壯
#define MAGIC_NO_DEFENCE                25	//格擋
#define MAGIC_NO_CLASH                  26	//衝撞
#define MAGIC_NO_PENETRABLE_ESCRIME     27	//劍氣
#define MAGIC_NO_KNOCK_TO_DIZZY         28	//敲暈
#define MAGIC_NO_FATAL_ESCRIME          29  //必殺劍
//
#define MAGIC_NO_SHOOT                  30  //射擊
#define MAGIC_NO_SEQUENTIAL_SHOOT       31  //連射
#define MAGIC_NO_EYES_SHOOT             32  //打眼睛
#define MAGIC_NO_DODGE                  33	//躲閃
#define MAGIC_NO_PENETRABLE_SHOOT       34  //穿透彈
#define MAGIC_NO_DOUBLE_SHOOT           35  //雙倍彈藥
#define MAGIC_NO_FEET_SHOOT             36	//打腳
#define MAGIC_NO_DIFFUSE_SHOOT          37  //掃射
//
#define MAGIC_NO_BOOK_READ              38  //讀書
#define MAGIC_NO_CURE                   39  //治療
#define MAGIC_NO_DEFEND_MIRROR          40  //防禦鏡
#define MAGIC_NO_RELIVE                 41  //復活
#define MAGIC_NO_BAPTISM                42  //洗禮
#define MAGIC_NO_MAGIC_MIRROR           43  //魔法鏡
#define MAGIC_NO_ENRICH_BLOOD           44  //大補血
#define MAGIC_NO_INFINITE_KINDNESS      45  //神恩浩蕩
//
#define MAGIC_NO_DARK_STAR              46  //暗星
#define MAGIC_NO_SLEEP                  47	//睡眠技
#define MAGIC_NO_TORTOISE               48  //烏龜技
#define MAGIC_NO_RESIST                 49  //抵抗
#define MAGIC_NO_DARK_BALL              50	//暗球
#define MAGIC_NO_BEELINE_MAGIC          51  //直線魔法
#define MAGIC_NO_AZRAEL                 52  //死神
#define MAGIC_NO_DEVIL                  53  //惡魔
//
#define MAGIC_NO_THONG                  54  //皮鞭
#define MAGIC_NO_CIRRUS_TRAP            55  //藤蔓陷阱
#define MAGIC_NO_BEAST_TRAP             56	//捕獸夾
#define MAGIC_NO_ERUPTIVE_THONG         57  //皮鞭蓄力
#define MAGIC_NO_RAVEL_TRAP             58  //解除陷阱
#define MAGIC_NO_PREDICT                59  //預感
#define MAGIC_NO_STONE_TRAP             60  //巨石陷阱
#define MAGIC_NO_PRETEND                61  //偽裝
#define MAGIC_NO_LANDMINE               62  //地雷
//
#define MAGIC_NO_DAGGER                 63  //匕首
#define MAGIC_NO_BEHIND_DAGGER          64  //背刺
#define MAGIC_NO_STEAL                  65  //偷竊
#define MAGIC_NO_UNLOCK                 66  //開鎖
#define MAGIC_NO_HIDE                   67  //隱形
#define MAGIC_NO_POISON                 68  //下毒
#define MAGIC_NO_GOLD                   69  //金幣
#define MAGIC_NO_NEGOTIATE              70  //談判
#define MAGIC_NO_ATTRACT_MONSTER        71  //吸引怪物
#define MAGIC_NO_BOX_TRAP               72  //寶箱陷阱
#define MAGIC_NO_CONTROL_MONSTER        73  //怪物控制
//
#define MAGIC_NO_CHOP                   74  //砍殺
#define MAGIC_NO_TOXOPHILY              75  //射箭
#define MAGIC_NO_RELIVE_2               76  //復活二
#define MAGIC_NO_SUCK_BLOOD             77  //吸血
#define MAGIC_NO_SUCK_MAGIC             78  //吸魔
#define MAGIC_NO_DESTROY_ARMOR          79  //防具破壞
#define MAGIC_NO_RELIVE_3               80  //復活三
#define MAGIC_NO_HIDE_2                 81  //隱身二
#define MAGIC_NO_FIRE_BALL              82  //火球
#define MAGIC_NO_EXPLODE                83  //自爆一
#define MAGIC_NO_EXPLODE_2              84  //自爆二
#define MAGIC_NO_BREAK_EQUIP            85  //打裝備
#define MAGIC_NO_RECALL                 86  //召喚
#define MAGIC_NO_CHANGE_FORM            87  //變身
#define MAGIC_NO_INSURANCE              88  //保險
#define MAGIC_NO_INSURANCE_2            89  //保險二
#define MAGIC_NO_INSURANCE_3            90  //保險三
#define MAGIC_NO_INSURANCE_4            91  //保險四
#define MAGIC_NO_INSURANCE_5            92  //保險五
//
//sea magic no defines -----------------------------------------------------------
#define MAGIC_NO_SEAWALK                120 //海上的移動
#define MAGIC_NO_SEA_PRETEND            121 //海上偽裝
#define MAGIC_NO_ARMOUR_PIERCING_BALL   122 //穿甲彈
#define MAGIC_NO_LINK_BALL              123 //鏈彈
#define MAGIC_NO_BURNT_BALL             124 //燃燒彈
#define MAGIC_NO_EMANATORY_BALL         125 //散彈
#define MAGIC_NO_REPAIR_BOAT            126 //修理


//---------------------------------------------
//人物法術當前狀態
//----------------
#define MAGIC_STATE_OK              0       //法術OK,可以使用.
#define MAGIC_STATE_PREPARE         1       //法術前置時間進行中
#define MAGIC_STATE_WAIT_SPOWER     2       //等待蓄力中
#define MAGIC_STATE_SPOWER          3       //法術正在蓄力中
#define MAGIC_STATE_WAIT_BREAK      4       //法術等待釋放

//
// STRUCTURES /////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct POS_SKILL_BS 
{
    //1.技能的基本屬性
    CHAR    Name[32];			//名稱    
    SLONG   IconIndex;			//圖標編號    
    SLONG   MpConsume;          //使用該技能的mp消耗(當蓄力時間為0 ,)
    SLONG   MpConsumeTick;      //都少次心跳
    SLONG   UseTag;             //法術適用的目標(隊友0,敵人1)
    SLONG   Attrib;				//技能的屬性
    SLONG   Kind;               //技能類型(被動機能0,釋放類型1,光環2)
    
    SLONG   Penetrate;          //穿透(0,1)
    SLONG   HitType;            //法術命中結算範圍(多人0,當體移動中1,當體可能會MISS 2)
    //2.和npc動作相關的技能數據
    SLONG   ActionCount;        //npc動作的播放次數
    SLONG   ActionId;           //使用該技能需要使用的npc動作的編號
    //3.技能的效果數值  
    SLONG   AttackType;         //機能的傷害類型(物理 0,法術 1,特殊 2)
    SLONG   AttackRatio;        //攻擊改變的百分率

    SLONG   AttachMaxHp;        //改變生命上限
    SLONG   AttachMaxMp;        //改變法力上限
    SLONG   AttachNowHp;        //改變當前的生命上限
    SLONG   AttachNowMp;        //改變當前的法力上限
    
    SLONG   AttackRatioChange;  //改變攻擊力的百分係數(所有類型的攻擊力)
    SLONG   PhysicAttackReduceRatio;//物理傷害減少率
    SLONG   PhysicDefence;      //改變物理防禦的數值
    SLONG   MagicDefence;       //改變魔法防率
    SLONG   ExplodeRatio;       //改變的膛爆的機率
        
    SLONG   TagAction;          //目標需要改變到的動作
    SLONG   TagActionRatio;     //目標會改變到該動作的機率
    //4.法術的附加效果
    SLONG   SelfStatus;          //自己會改變的狀態
    SLONG   SelfStatusRatio;     //自己會改變到該狀態的機率
    
    SLONG   TagStatus;           //目標會改變的狀態
    SLONG   TagStatusRatio;      //目標會改變到該狀態的機率

    SLONG   Dispel;               //消除不良狀態能力
    SLONG   Resurgent;            //復活

    //5.法術和範圍相關的數值
    SLONG   MagicDisChargeDistance; //法術釋放距離....施法者需要距離走近目標多少後才能..釋放法術
    SLONG   MagicBrokenDistance;    //法術命中的判定距離...就是法術和npc的距離差多少算命中
    SLONG   MagicHitDistance;       //法術命中後數值結算距離
    SLONG   MagicFlyDistance;       //法術飛行的距離
    SLONG   MagicEffRange;          //面積法術的作用範圍(對魔法陣適用)
    //6.和法術施放相關的時間數值
    SLONG   SpowerTick;             //蓄力時間
    SLONG   DamageTick;             //延時期(多次傷害的間隔時間,)
    SLONG   DeleyTick;              //技能的持續時間
    SLONG   PantTick;               //施法完成後需要的喘息時間
    //7.和法術組件相關的數值
    SLONG   HeightLeve;             //法術組件的高度(地表法術0 ,中層1,高層2)
    //
    SLONG   SelfBreakId;            //從自己身上炸出的法術效果的編號
    SLONG   TagBreakId;             //在目標點炸開的法術效果的編號
    SLONG   EffBreakId;             //命中後的法術效果的編號
    //8.魔法陣相關的數據
    SLONG   MagicId;                //魔法陣..使用的圖檔
    //
} TPOS_SKILL_BS, *LPTPOS_SKILL_BS;
//
// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern  TPOS_SKILL_BS   GameSkillBase[MAX_GAME_SKILL_BASES][MAX_SKILL_LEVELS];  //[技能的編號][技能的等級]

//
// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	SLONG	InitSkillSystem(void);
extern	void	FreeSkillSystem(void);
//
extern	void	InitGameSkillBase(void);
extern	SLONG   LoadGameSkillBase(CHAR* szFileName);
extern	void	DebugLogGameSkillBase(void);
extern	void	FreeGameSkillBase(void);
//------------------------------------------------------------------------
//名稱    
CHAR*	GetSkillName(SLONG lSkillNo);
//圖標編號
SLONG   GetSkillIconIndex(SLONG lSkillNo);
//使用該技能的mp消耗(當蓄力時間為0 ,)
SLONG   GetSkillMpConsume(SLONG lSkillNo, SLONG lLevel);
//都少次心跳
SLONG   GetSkillMpConsumeTick(SLONG lSkillNo, SLONG lLevel);
//法術適用的目標(隊友0,敵人1)
SLONG   GetSkillUseTag(SLONG lSkillNo, SLONG lLevel);
//技能的屬性
SLONG   GetSkillAttrib(SLONG lSkillNo, SLONG lLevel);
//技能類型(被動機能0,釋放類型1,光環2)
SLONG   GetSkillKind(SLONG lSkillNo, SLONG lLevel);
//穿透(0,1)
SLONG   GetSkillPenetrate(SLONG lSkillNo, SLONG lLevel);
//法術命中結算範圍(當體0,多人1)
SLONG   GetSkillHitType(SLONG lSkillNo, SLONG lLevel);
//2.和npc動作相關的技能數據
//npc動作的播放次數
SLONG   GetSkillActionCount(SLONG lSkillNo, SLONG lLevel);
//使用該技能需要使用的npc動作的編號
SLONG   GetSkillActionId(SLONG lSkillNo, SLONG lLevel);
//3.技能的效果數值  
//機能的傷害類型(物理 0,法術 1,特殊 2)
SLONG   GetSkillAttackType(SLONG lSkillNo, SLONG lLevel);
//攻擊改變的百分率
SLONG   GetSkillAttackRatio(SLONG lSkillNo, SLONG lLevel);

//改變生命上限
SLONG   GetSkillAttachMaxHp(SLONG lSkillNo, SLONG lLevel);
//改變法力上限
SLONG   GetSkillAttachMaxMp(SLONG lSkillNo, SLONG lLevel);
//改變當前的生命上限
SLONG   GetSkillAttachNowHp(SLONG lSkillNo, SLONG lLevel);
//改變當前的法力上限
SLONG   GetSkillAttachNowMp(SLONG lSkillNo, SLONG lLevel);
//改變攻擊力的百分係數(所有類型的攻擊力)
SLONG   GetSkillAttackRatioChange(SLONG lSkillNo, SLONG lLevel);
//物理傷害減少率
SLONG   GetSkillPhysicAttackReduceRatio(SLONG lSkillNo, SLONG lLevel);
//改變物理防禦的數值
SLONG   GetSkillPhysicDefence(SLONG lSkillNo, SLONG lLevel);
//改變魔法防率
SLONG   GetSkillMagicDefence(SLONG lSkillNo, SLONG lLevel);
//改變的膛爆的機率
SLONG   GetSkillExplodeRatio(SLONG lSkillNo, SLONG lLevel);
//目標需要改變到的動作
SLONG   GetSkillTagAction(SLONG lSkillNo, SLONG lLevel);
//目標會改變到該動作的機率
SLONG   GetSkillTagActionRatio(SLONG lSkillNo, SLONG lLevel);
//4.法術的附加效果
//自己會改變的狀態
SLONG   GetSkillSelfStatus(SLONG lSkillNo, SLONG lLevel);
    
//自己會改變到該狀態的機率
SLONG   GetSkillSelfStateRatio(SLONG lSkillNo, SLONG lLevel);
    
//目標會改變的狀態
SLONG   GetSkillTagStatus(SLONG lSkillNo, SLONG lLevel);
//目標會改變到該狀態的機率
SLONG   GetSkillTagStatusRatio(SLONG lSkillNo, SLONG lLevel);
//消除不良狀態能力
SLONG   GetSkillDispel(SLONG lSkillNo, SLONG lLevel);
//復活
SLONG   GetSkillResurgent(SLONG lSkillNo, SLONG lLevel);
//5.法術和範圍相關的數值
//法術釋放距離....施法者需要距離走近目標多少後才能..釋放法術
SLONG   GetSkillMagicDisChargeDistance(SLONG lSkillNo, SLONG lLevel);
//法術命中的判定距離...就是法術和npc的距離差多少算命中
SLONG   GetSkillMagicBrokenDistance(SLONG lSkillNo, SLONG lLevel);
//法術命中後數值結算距離
SLONG   GetSkillMagicHitDistance(SLONG lSkillNo, SLONG lLevel);
//法術飛行的距離
SLONG   GetSkillMagicFlyDistance(SLONG lSkillNo, SLONG lLevel);
//面積法術的作用範圍(對魔法陣適用)
SLONG   GetSkillMagicEffRange(SLONG lSkillNo, SLONG lLevel);
//6.和法術施放相關的時間數值
SLONG   GetSkillSpowerTick(SLONG lSkillNo, SLONG lLevel);
//延時期(多次傷害的間隔時間,)
SLONG   GetSkillDamageTick(SLONG lSkillNo, SLONG lLevel);
//技能的持續時間
SLONG   GetSkillDeleyTick(SLONG lSkillNo, SLONG lLevel);
//施法完成後需要的喘息時間
SLONG   GetSkillPantTick(SLONG lSkillNo, SLONG lLevel);
//7.和法術組件相關的數值
//法術組件的高度(地表法術0 ,中層1,高層2)
SLONG   GetSkillHeightLeve(SLONG lSkillNo, SLONG lLevel);
//法術效果編號.
SLONG   GetSkillSelfBreakId(SLONG lSkillNo, SLONG lLevel);
SLONG   GetSkillTagBreakId(SLONG lSkillNo, SLONG lLevel);
SLONG   GetSkillEffBreakId(SLONG lSkillNo, SLONG lLevel);
//魔法陣相關的數據
SLONG   GetSkillMagicId(SLONG lSkillNo, SLONG lLevel);
//取得技能屬性的判定函數
//該技能可否裝備在左手
SLONG   IsLeftHandSkill(SLONG lSkillNo, SLONG lLevel);
//該技能可否裝備在右手
SLONG   IsRightHandSkill(SLONG lSkillNo, SLONG lLevel);
//該技能是否施陸戰技能
SLONG   IsLandSkill(SLONG lSkillNo, SLONG lLevel);
//該技能是否是海洋技能
SLONG   IsSeaSkill(SLONG lSkillNo, SLONG lLevel);
//該技能 在地圖技能列表上會顯示本技能
SLONG   IsListVisibleSkill(SLONG lSkillNo, SLONG lLevel);
//判斷是否是通用 技能.. 在海洋..和陸地都可以使用
SLONG   IsCommonSkill(SLONG lSkillNo, SLONG lLevel);
//顯示在地圖快捷圖標列的最底下
SLONG   IsUnderListSkill(SLONG lSkillNo, SLONG lLevel);
//和平模式下使用的技能
SLONG   IsPeaceSkill(SLONG lSkillNo, SLONG lLevel);
//戰鬥模式下使用的技能
SLONG   IsFightSkill(SLONG lSkillNo, SLONG lLevel);
//判斷該技能是否需要蓄力量
SLONG   IsSkillNeedSpower(SLONG lSkillNo, SLONG lLevel);
//判斷使用的魔法陣的類型
SLONG   IsSkillNeedSelfMagicArea(SLONG lSkillNo, SLONG lLevel);
//
SLONG   IsSkillNeedTagNpc(SLONG lSkillNo, SLONG lLevel);
//判斷該技能是否可以對著空地使用
SLONG   IsSkillUsePosition(SLONG lSkillNo, SLONG lLevel);
//判斷該技能的目標是否是普通npc
SLONG   IsSkillUseTagNormalNpc(SLONG lSkillNo, SLONG lLevel);
//判斷該技能的目標是朋友..隊友
SLONG   IsSkillUseTagFriend(SLONG lSkillNo, SLONG lLevel);
//判斷該技能的目標是敵人
SLONG   IsSkillUseTagEnemy(SLONG lSkillNo, SLONG lLevel);
//判斷該技能的目標是自己
SLONG   IsSkillUseTagSelf(SLONG lSkillNo, SLONG lLevel);
//判斷該技能的使用目標是死人
SLONG   IsSkillUseTagDeadNpc(SLONG lSkillNo, SLONG lLevel);
//判斷在鼠標的左鍵按下的時候莫個技能可否使用
SLONG   IsSkillMouseDownCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc);
//判斷在鼠標的放開的時候莫個技能可否使用...主要都是..需要蓄力的技能;
SLONG   IsSkillMouseUpCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc);
//檔鼠標的左鍵按下的時候判定..需要莫個技能需要改變到的doingkind 
SLONG   GetSkillMosueDownDoingKind(SLONG lSkillNo, SLONG lLevel);


//mark by lijun 2003-04-21
/*
typedef	struct POS_SKILL_BS 
{
    CHAR    Name[32];			//名稱
    SLONG   Attrib;				//屬性
    SLONG   IconIndex;			//圖標編號

    SLONG   PrepareTicks;		//前置時間
    SLONG   SpowerTicks;		//蓄力時間
    SLONG   DelayTicks;			//延時期(多次傷害的間隔時間)
	SLONG	PersistTicks;		//功能持續時間
	SLONG	PantTicks;			//施法完成後需要的喘息時間

	SLONG	DoTimes;			//法術動作次數
	SLONG	NeedMp;				//需要法力值
	SLONG	Abnormity;			//異常狀態
	SLONG	Relation;			//適用目標

	SLONG	ExplodeRange;		//爆炸產生後的有效攻擊範圍
    SLONG   ExplodeDistance;    //爆炸產生時需要法術組件接近目標的距離
    SLONG   TargetDistance;     //施法者在進行施法動作時需要接近目標的距離

	SLONG	SpecialID;			//對應 NPC 的特殊影像文件ID

	SLONG	HitType;			//命中方式
	SLONG	PhysicAttackRatio;	//影響物理攻擊力(%)
	SLONG	MagicAttackRatio;	//影響法術攻擊力(%)
	SLONG	SpecialAttackRatio;	//影響特殊攻擊力(%)
	SLONG	AttachDefenceData;	//附加防禦力數值
	SLONG	AttachDefenceTicks;	//附加防禦力時間
	SLONG	DodgeRate;			//躲避率(%)
	SLONG	ExplodeRate;		//膛爆率(%)
	SLONG	ChangeRate;			//變黑人,變烏龜,變豬的機率
	SLONG	LevelQuotiety;		//不同等級影響攻擊力(%)的係數, 實際影響(%) = 1 + Level * LevelQuotiety.
	SLONG	AttackQuotiety;		//影響總體攻擊力的係數
	SLONG	AttachMaxHp;		//附加生命上限
	SLONG	AttachMaxMp;		//附加內力上限

} TPOS_SKILL_BS, *LPTPOS_SKILL_BS;

extern	CHAR*	GetSkillName(SLONG lSkillNo);
extern	SLONG   GetSkillAttrib(SLONG lSkillNo);
extern	SLONG   GetSkillIconIndex(SLONG lSkillNo);
extern	SLONG   GetSkillPrepareTicks(SLONG lSkillNo);
extern	SLONG   GetSkillSpowerTicks(SLONG lSkillNo);
extern	SLONG   GetSkillDelayTicks(SLONG lSkillNo);
extern	SLONG	GetSkillPersistTicks(SLONG lSkillNo);
extern	SLONG	GetSkillPantTicks(SLONG lSkillNo);
extern	SLONG	GetSkillDoTimes(SLONG lSkillNo);
extern	SLONG	GetSkillNeedMp(SLONG lSkillNo);
extern	SLONG	GetSkillAbnormity(SLONG lSkillNo);
extern	SLONG	GetSkillRelation(SLONG lSkillNo);
extern	SLONG	GetSkillExplodeRange(SLONG lSkillNo);
extern	SLONG   GetSkillExplodeDistance(SLONG lSkillNo);
extern	SLONG   GetSkillTargetDistance(SLONG lSkillNo);
extern	SLONG	GetSkillSpecialID(SLONG lSkillNo);
extern	SLONG	GetSkillHitType(SLONG lSkillNo);
extern	SLONG	GetSkillPhysicAttackRatio(SLONG lSkillNo);
extern	SLONG	GetSkillMagicAttackRatio(SLONG lSkillNo);
extern	SLONG	GetSkillSpecialAttackRatio(SLONG lSkillNo);
extern	SLONG	GetSkillAttachDefenceData(SLONG lSkillNo);
extern	SLONG	GetSkillAttachDefenceTicks(SLONG lSkillNo);
extern	SLONG	GetSkillDodgeRate(SLONG lSkillNo);
extern	SLONG	GetSkillExplodeRate(SLONG lSkillNo);
extern	SLONG	GetSkillChangeRate(SLONG lSkillNo);
extern	SLONG	GetSkillLevelQuotiety(SLONG lSkillNo);
extern	SLONG	GetSkillAttackQuotiety(SLONG lSkillNo);
extern	SLONG	GetSkillAttachMaxHp(SLONG lSkillNo);
extern	SLONG	GetSkillAttachMaxMp(SLONG lSkillNo);
//
extern	SLONG   IsLeftHandSkill(SLONG lSkillNo);
extern	SLONG   IsRightHandSkill(SLONG lSkillNo);
extern	SLONG   IsLandSkill(SLONG lSkillNo);
extern	SLONG   IsSeaSkill(SLONG lSkillNo);
extern	SLONG   IsListVisibleSkill(SLONG lSkillNo);
extern	SLONG   IsCommonSkill(SLONG lSkillNo);
extern	SLONG   IsUnderListSkill(SLONG lSkillNo);
extern	SLONG   IsPeaceSkill(SLONG lSkillNo);
extern	SLONG   IsFightSkill(SLONG lSkillNo);
extern	SLONG   IsSkillNeedPrepare(SLONG lSkillNo);
extern	SLONG   IsSkillNeedSpower(SLONG lSkillNo);
extern	SLONG	IsPassiveSkill(SLONG lSkillNo);
*/
//
