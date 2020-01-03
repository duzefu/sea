
/*
 *    2003-05-29
 */


//-------------------------------------------------------------------------
// 戰鬥數值結算
//-------------------------------------------------------------------------
#define     MAX_SKILL_PROCESS_UNIT          1024        //最多能 有的..數值結算的單元的數目
#define     MAX_GAME_SKILL_PROCESS          10240       //作多能有的SKILL_PROCESS的數目
//
#define     SKILL_PROCESS_ZONE_TYPE_DUMP        0   //空...就是說不會結算
#define     SKILL_PROCESS_ZONE_TYPE_CIRCLE      1   //園    (data0, data1) 中心點   data2 半徑
#define     SKILL_PROCESS_ZONE_TYPE_BOLON       2   //長方形(data0, data1) 頂點1 -- (data2, data3) 頂點2
//-
#define     SKILL_PROCESS_SURVIAL_MAGIC         0x00000001   //和物件一樣的生存時間...(同時出現..同時消失)..(沒有該項..出現一下馬上消失)
#define     SKILL_PROCESS_SURVIAL_ATTACH        0x00000002   //粘在對應的物件上面...和物件一起運動(就是物件動的時候也要動)
//
typedef struct POS_SKILL_PROCESS_UNIT
{
    SLONG   ZoneType;      //技能結算的區域類型
    SLONG   ZoneData0;     //技能結算的區域..數據
    SLONG   ZoneData1;     
    SLONG   ZoneData2;
    SLONG   ZoneData3;
    //
    SLONG   SurvialType;    //生存類型
    //    
}TPOS_SKILL_PROCESS_UNIT, *LPTPOS_SKILL_PROCESS_UNIT;

//---
//
//---
typedef struct POS_SKILL_VAL_PROCESS
{
    union
    {
        SLONG   Flag;      //使用標誌
        SLONG   Tail;      //鏈尾指標
    };
    SLONG   Next;          //後繼指標
    //
    SLONG   AttachMagic;    //連接的MAGIC_PART的編號    
    SLONG   x, y, z;        //座標    
    //
    TPOS_SKILL_PROCESS_UNIT     UnitData;  //初始化的數據
}TPOS_SKILL_VAL_PROCESS, *LPTPOS_SKILL_VAL_PROCESS;
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
extern  TPOS_SKILL_VAL_PROCESS      g_ZoneSkillProcess[MAX_GAME_SKILL_PROCESS];
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
extern  SLONG   GetZoneSkillProcessFlag(SLONG lIndex);
extern  void    SetZoneSkillProcessFlag(SLONG lIndex, SLONG lFlag);
extern  SLONG   GetZoneSkillProcessTail(SLONG lIndex);
extern  void    SetZoneSkillProcessTail(SLONG lIndex, SLONG lTail);
extern  SLONG   GetZoneSkillProcessNext(SLONG lIndex);
extern  void    SetZoneSkillProcessNext(SLONG lIndex, SLONG lNext);
extern  SLONG   GetZoneSkillProcessAttachMagic(SLONG lIndex);
extern  void    SetZoneSkillProcessAttachMagic(SLONG lIndex, SLONG lAttachMagic);
extern  void    GetZoneSkillProcessPosition(SLONG lIndex, SLONG *x, SLONG *y, SLONG *z);
extern  void    SetZoneSkillProcessPosition(SLONG lIndex, SLONG x, SLONG y, SLONG z);
extern  SLONG   GetZoneSkillProcessZoneType(SLONG lIndex);
extern  void    SetZoneSkillProcessZoneType(SLONG lIndex, SLONG lZoneType);
extern  SLONG   GetZoneSkillProcessZoneData0(SLONG lIndex);
extern  void    SetZoneSkillProcessZoneData0(SLONG lIndex, SLONG lZoneData0);
extern  SLONG   GetZoneSkillProcessZoneData1(SLONG lIndex);
extern  void    SetZoneSkillProcessZoneData1(SLONG lIndex, SLONG lZoneData1);
extern  SLONG   GetZoneSkillProcessZoneData2(SLONG lIndex);
extern  void    SetZoneSkillProcessZoneData2(SLONG lIndex, SLONG lZoneData2);
extern  SLONG   GetZoneSkillProcessZoneData3(SLONG lIndex);
extern  void    SetZoneSkillProcessZoneData3(SLONG lIndex, SLONG lZoneData3);
extern  SLONG   GetZoneSkillProcessSurvialType(SLONG lIndex);
extern  void    SetZoneSkillProcessSurvialType(SLONG lIndex, SLONG lSurvialType);
//-------------------------------------------------------------------------
//  .End.
//-------------------------------------------------------------------------
 