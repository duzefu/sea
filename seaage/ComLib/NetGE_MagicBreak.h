/*
**	NetGE_MagicBreak.h 
**	magic break functions header. 
**
**	Jack, 2003.1.26.
*/
#pragma once
//-------------------------------------------------------------------------
#define     MAX_MAGIC_UNIT          256     //最多能有的魔法組件..單元的類型
#define     MAX_MAGIC_BREAK         256     //最多能有的魔法物件的炸開方式
//
#define     MAX_MAGIC_DIR           32      //法術組件做多能有的方向  
                                            // 0 --- 31  衝  12點開始順時針
//----
//  法術組件炸開的類型
//----                
#define     MAGIC_BREAK_TYPE_TAG        0
#define     MAGIC_BREAK_TYPE_SELF       1
#define     MAGIC_BREAK_TYPE_EFF        2
//----
//  定義魔法物件的生存方式
//----
#define     MAGIC_SURVIAL_TIME            0x00000001  //該魔法物件在一段時間後會消失
#define     MAGIC_SURVIAL_FRAME_ONE_TIME  0x00000002  //該魔法物件在動畫播放到最後一幀會消失
#define     MAGIC_SURVIAL_PATH            0x00000004  //該魔法物件在完成自己的運動距離後消失
#define     MAGIC_SURVIAL_ALPHA_DISAPPEAR 0x00000008  //該魔法物件alpha出現..後消失
#define     MAGIC_SURVIAL_ALPHA_APPEAR    0x00000010  //該魔法物件 alpha消失..後消失
//----
//MAGIC PATHS(法術路徑)
//      該ai定義了魔法組件的於動..軌跡..
//----
#define     MAGIC_PATH_DUMP             0           //
#define     MAGIC_PATH_LINE             1		    //線性路徑..就是該魔法物件是按照直線移動...
#define     MAGIC_PATH_UP               2           //座標..從下往上升
#define     MAGIC_PATH_CURVE            3		    //曲線型路徑, 部件依照時間按照自己既定軌跡運動
#define     MAGIC_PATH_MISSILE          2		    //導彈型路徑, 部件跟蹤目標運動
#define     MAGIC_PATH_STAY             5		    //停留原地, 循環播放
#define     MAGIC_PATH_LINK             6		    //連接在NPC上
#define     MAGIC_PATH_FALL             7		    //從空中落下
#define     MAGIC_PATH_MOVE             8		    //線性移動, 遇到阻擋後消失
#define     MAGIC_PATH_TRACE            9		    //跟蹤目標, 遇到阻擋自動繞過
#define     MAGIC_PATH_STAY_ONCE        10          //停留原地, 播放完後消失
#define     MAGIC_PATH_ROLL             11		    //滾動, 遇到 NPC 彈開, 如果為敵方同時還扣血
#define     MAGIC_PATH_SHAKE            12		    //震開並攻擊圓形範圍內的敵人
#define     MAGIC_PATH_DIFFUSE          13		    //攻擊圓形範圍內的敵人
#define     MAGIC_PATH_SCREW            14		    //螺旋線方式前進
#define     MAGIC_PATH_EDDY             15		    //風車螺線, 圍繞施法者旋轉
#define	    MAGIC_PATH_PARABOLA			16		    //拋物線
//----
//  魔法組件具有的屬性
//----
#define     MAGIC_UNIT_ATTRIB_DIR_CHANGE        0x00000001  //在不不是正上方向(0度)的時候..數據是否需要.做相應的改變
#define     MAGIC_UNIT_ATTRIB_COOR_RAND         0x00000002  //隨機座標的..標誌_
//----
//  魔法炸開方式的屬性
//----
#define     MAGIC_BREAK_ATTRIB_TAG_BREAK        0x00000001  //在目標位置炸開的屬性
//----
//廣於該magic break時候的屏幕效果
//----
#define     MAGIC_BREAK_SCREEN_QUAKE            0x00000001  //地圖震動
//----
//  定義該物件的上圖方式
//----
#define     MAGIC_EFF_SHADOW                    0x00000001  //該物件上圖是否要畫影子
#define     MAGIC_EFF_INVERT_IMAGE              0x00000002  //該物件上圖是否需要倒影的標誌(水中的影子)
#define     MAGIC_EFF_BLEND                     0x00000010  //該物件上圖是否需要 融合的alpha上圖方式 (沒有的話用普通的put 使用alpha 通道來控制)
#define     MAGIC_EFF_TRACK_DUST                0x00000100  //該物件在移動過程中會留下灰塵的尾跡
//----
//  魔法物件動畫控制函數
//----
#define     MAGIC_FRAME_LOOP                    0x00000001  //循環播放標誌
#define     MAGIC_FRAME_ORDER                   0x00000002  //正常順序播放標誌
//
//-------------------------------------------------------------------------
//該結構定義的是一些法術組件..行為…定義的是最小的法術組件
typedef struct POS_MAGIC_UNIT
{
    SLONG   AppearImgId;    //出現動畫 (沒有該動畫 用 -1) 物體.在播放動畫的時候..不會有該過程
    SLONG   ProcImagId;     //過程動畫
    SLONG   DisAppearImgId; //消失動畫 (沒有該動畫 用 -1) 物體.在播放動畫的時候..不會有該過程
    SLONG   DirNum;			//方向數據
    SLONG   Path;           //運動的軌跡
    SLONG   Survial;        //生存的方式
    SLONG   FrameType;      //動畫幀的控制函數
    SLONG   DrawEff;        //上圖的效果
    SLONG   Stop;           //相關的阻擋類型
    double  Speed;          //移動的速度
    double  VertSpeed;      //垂直方向上的..速度
}TPOS_MAGIC_UNIT,*LPTOPS_MAGIC_UNIT;
//
//定義的是如何使用那些MAGIC_UNIT
typedef struct POS_MAGIC_BREAK_PARAMETER
{
    SLONG   UnitId;          //使用的 MAGIC_UNIT 的ID
    SLONG   Attrib;          //表示MAGIC_BREAK整個改變方向,該MAGIC_UNIT是否需要改變方向
    SLONG   ox,oy,oz;        //座標偏差    
    SLONG   Dir;             //方向偏差...在該組合效果中...該unit的方向是否需要做適當的調整(最多32方向  0--32)
    SLONG   SleepTime;       //前置等待時間
    SLONG   SurvialTime;     //生存時間(-1表示的是該法術組件會用遠存在)
    SLONG   DirLockNum;      //該法術組件是不是你能有固定的幾個方向(-1代表能有所有的方向)
    union
    {
        SLONG   MoveStep;   //表示該法術組件的最多移動步數目
        SLONG   MoveDist;   //該法術組件能移動的距離
    };
}TPOS_MAGIC_BREAK_PARAMETER,*LTPOS_MAGIC_BREAK_PARAMETER;
//定義的是一些,所有的MAGIC_BREAK共用的書據
typedef struct POS_MAGIC_BREAK
{
    SLONG   UnitNum;        //該break包含有的magic_action的數目
    SLONG   Attrib;         //屬性
    SLONG   ox, oy, oz;     //整個魔法炸開效果的座標偏差
    SLONG   MaxDir;         //該炸開方式能夠有的最多方向數目(-1代表是任意方向)
    //
    SLONG   lBreakParamentBegin;    //數據開始....的位置
}TPOS_MAGIC_BREAK,*LPTOPS_MAGIC_BREAK;
//
//-------------------------------------------------------------------------
SLONG	DummyBreakMagicFunction( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
//
SLONG   BreakMagic_FireBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireDragon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireWall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireArmor( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireBroken( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireAerolite( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireWard( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_IceBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceBow( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceMirror( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceCoagulate( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceCircle( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceFall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceBlade( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_LightStrike( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBless( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBlade( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBaptism( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightThundering( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_DustUnderStick( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustArrayStones( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustDiffuseWave( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustXirang( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustRollStone( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustVirusGas( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_ArcChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_SeriesChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_SteelSever( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BallyragCircle( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_WindfallChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_ThrowDragon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_EvilBomb( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_CleanseLight( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BlestBarrier( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_Blessing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_Prayer( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FastWind( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_HolyPhotosphere( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_VitalWind( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_RevengeAngel( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_JusticeAngel( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_AresDance( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BrokenBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DemonHowl( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_WindBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BrokenArmor( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_ArhatBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_GasBarrier( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BloodEddies( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_ShipCannon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
//出現動畫 (沒有該動畫 用 -1) 物體.在播放動畫的時候..不會有該過程
SLONG   GetMagicUnitAppearImgId(SLONG lIndex);
//過程動畫
SLONG   GetMagicUnitProcImgId(SLONG lIndex);
//消失動畫 (沒有該動畫 用 -1) 物體.在播放動畫的時候..不會有該過程
SLONG   GetMagicUnitDisAppearImgId(SLONG lIndex);
//方向數據
SLONG   GetMagicUnitDirNum(SLONG lIndex);
//運動的軌跡
SLONG   GetMagicUnitPath(SLONG lIndex);
//生存的方式
SLONG   GetMagicUnitSurvial(SLONG lIndex);
//上圖的效果
SLONG   GetMagicUnitDrawEff(SLONG lIndex);
//相關的阻擋類型
SLONG   GetMagicUnitStop(SLONG lIndex);
//移動的速度
double  GetMagicUnitSpeed(SLONG lIndex);
//-------------------------------------------------------------------------
//  初始化法術炸開的...數據
//-------------------------------------------------------------------------
SLONG	InitMagicBreakSystem(void);
//-------------------------------------------------------------------------
//  關於法術炸開的一些控制函數
//-------------------------------------------------------------------------
SLONG   BreakMagic_CommonBreak( SLONG skill_no, SLONG npc_no, SLONG type, SLONG dest_x, SLONG dest_y, SLONG dest_no);
SLONG   MagicBreakProc(SLONG break_no, SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_z, SLONG dest_npc);
