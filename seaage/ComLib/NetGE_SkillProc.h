
/*
 *    2003-05-29
 */


//-------------------------------------------------------------------------
// �԰��ƭȵ���
//-------------------------------------------------------------------------
#define     MAX_SKILL_PROCESS_UNIT          1024        //�̦h�� ����..�ƭȵ��⪺�椸���ƥ�
#define     MAX_GAME_SKILL_PROCESS          10240       //�@�h�঳��SKILL_PROCESS���ƥ�
//
#define     SKILL_PROCESS_ZONE_TYPE_DUMP        0   //��...�N�O�����|����
#define     SKILL_PROCESS_ZONE_TYPE_CIRCLE      1   //��    (data0, data1) �����I   data2 �b�|
#define     SKILL_PROCESS_ZONE_TYPE_BOLON       2   //�����(data0, data1) ���I1 -- (data2, data3) ���I2
//-
#define     SKILL_PROCESS_SURVIAL_MAGIC         0x00000001   //�M����@�˪��ͦs�ɶ�...(�P�ɥX�{..�P�ɮ���)..(�S���Ӷ�..�X�{�@�U���W����)
#define     SKILL_PROCESS_SURVIAL_ATTACH        0x00000002   //�ߦb����������W��...�M����@�_�B��(�N�O����ʪ��ɭԤ]�n��)
//
typedef struct POS_SKILL_PROCESS_UNIT
{
    SLONG   ZoneType;      //�ޯ൲�⪺�ϰ�����
    SLONG   ZoneData0;     //�ޯ൲�⪺�ϰ�..�ƾ�
    SLONG   ZoneData1;     
    SLONG   ZoneData2;
    SLONG   ZoneData3;
    //
    SLONG   SurvialType;    //�ͦs����
    //    
}TPOS_SKILL_PROCESS_UNIT, *LPTPOS_SKILL_PROCESS_UNIT;

//---
//
//---
typedef struct POS_SKILL_VAL_PROCESS
{
    union
    {
        SLONG   Flag;      //�ϥμлx
        SLONG   Tail;      //�������
    };
    SLONG   Next;          //���~����
    //
    SLONG   AttachMagic;    //�s����MAGIC_PART���s��    
    SLONG   x, y, z;        //�y��    
    //
    TPOS_SKILL_PROCESS_UNIT     UnitData;  //��l�ƪ��ƾ�
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
 