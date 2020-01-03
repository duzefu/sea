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
#define MAX_GAME_MAGIC_PART			10240   //�C�����k�N�ե󪺼ƥ�
#define HEAD_GAME_MAGIC_PART		1       //�Χ@�Y���I���k�N�ե�ƥ�, 1�����@��ZONE.
#define MAX_BREAK_MAGIC_PART		512		//��@�k�N�ɲ��ͪ��k�N�ե�



//
//MAGIC STATE(�k�N�ثe���A)-----------------
//
#define MAGIC_STATE_SLEEP           1		//��v���A��
#define MAGIC_STATE_SHIFT           2		//���ʤ�
#define MAGIC_STATE_EXPLODE         3		//�z����
//
#define MAX_MAGIC_DELAY_TICK        99999   //
#define	MAGIC_VOICE_BROKEN			1		//�k�N�ե��z��

//
//MAGIC FRAME TYPES(�k�N����V�w�q) --------
//
#define MAGIC_KEY_FRAME_NONE		0		//�D����V
#define MAGIC_KEY_FRAME_HEAD		1		//����V(�Ĥ@�V)
#define MAGIC_KEY_FRAME_HALF		2		//�����V
#define MAGIC_KEY_FRAME_TAIL		3		//�̫�V
#define MAGIC_KEY_FRAME_OVER		4		//��n�W�L�̫�V

//
#define	GRAVITY_ACCELERATION		(-3.5)	//���O�[�t��

//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
//MAGIC PART STRUCT(�k�N���󵲺c�w�q)---------------------------------------
//
typedef struct  POS_MAGIC_PART
{
    //-
    union
    {
        SLONG   Flag;      //�ϥμлx
        SLONG   Tail;      //�������
    };
    SLONG   Next;          //���~����
    //�M�ޯ�������ƾڶ�
    SLONG   SkillIndex;		//�k�N�ƾگ���...����..�Ӫk�N�N���O���ӧޯ�
    SLONG   SkillLevel;     //    
    SLONG   SourceNo;		//�I�k��
    SLONG   TargetNo;		//�I�k��H
    //�M�y�Ь������ƾڶ�
    SLONG   DestX;			//�ؼЦ�m
    SLONG   DestY;			//
    SLONG   DestZ;			//    
    SLONG   OrigX;			//�_�l��m
    SLONG   OrigY;			//
    SLONG   OrigZ;			//
    SLONG   CurrX;          //��e��m
    SLONG   CurrY;          //
    SLONG   CurrZ;          //    
    //�M�ե��ݩʬ������ƾڶ�...���󥻥ͨ��欰����������
    SLONG   State;          //�ثe���A
    //
    SLONG   SleepTick;		//��v��, �o�X�����v���ɶ�    
    SLONG   LifeTick;		//�ͩR��
    SLONG   DelayTick;		//����᪺���ɮɶ�....�Ω�ƭȭp�⪺���j�ɶ�
    //
    SLONG   Step;           //�Z���_�l�I���B��
    //
    //�M�W�Ϭ������ƾڰ�
    SLONG   ImgDir;         //���󪺷�e��V...(�ϥ�...�Ӫ���̦h��V�ҹ������s��)
    SLONG   ObjectIndex;	//�������...��magic_part �b�a��object �����s��
    SLONG   ImageID;		//����v��ID
    SLONG   ImageFrame;     //����v���V
    //
    POS_MAGIC_UNIT   unit_data; //���󪺤@�Ǩ�L��������

}TPOS_MAGIC_PART, *LPTPOS_MAGIC_PART;
//
typedef struct  POS_MAGIC_PIPE
{
    SLONG   lDestNo;		//�ؼ� NPC
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
//�L�{�ʵe
SLONG	GetZoneMagicPartProcImagId(SLONG lIndex);
void 	SetZoneMagicPartProcImagId(SLONG lIndex, SLONG lProcImagId);
//�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG	GetZoneMagicPartDisAppearImgId(SLONG lIndex);
void 	SetZoneMagicPartDisAppearImgId(SLONG lIndex, SLONG lDisAppearImgId);
SLONG	GetZoneMagicPartAppearImgId(SLONG lIndex);
void 	SetZoneMagicPartAppearImgId(SLONG lIndex, SLONG lAppearImgId);

//��V�ƾ�
SLONG	GetZoneMagicPartDirNum(SLONG lIndex);
void 	SetZoneMagicPartDirNum(SLONG lIndex, SLONG lDirNum);
//�B�ʪ��y��
SLONG	GetZoneMagicPartPath(SLONG lIndex);
void 	SetZoneMagicPartPath(SLONG lIndex, SLONG lPath);
//�ͦs���覡
SLONG	GetZoneMagicPartSurvial(SLONG lIndex);
void 	SetZoneMagicPartSurvial(SLONG lIndex, SLONG lSurvial);
//�W�Ϫ��ĪG
SLONG	GetZoneMagicPartDrawEff(SLONG lIndex);
void 	SetZoneMagicPartDrawEff(SLONG lIndex, SLONG lDrawEff);
//��������������
SLONG	GetZoneMagicPartStop(SLONG lIndex);
void 	SetZoneMagicPartStop(SLONG lIndex, SLONG lStop);

//�]�m���ʳt��
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

//�L�{�ʵe
SLONG	GetBreakMagicPartProcImagId(SLONG lIndex);
void 	SetBreakMagicPartProcImagId(SLONG lIndex, SLONG lProcImagId);
//�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG	GetBreakMagicPartDisAppearImgId(SLONG lIndex);
void 	SetBreakMagicPartDisAppearImgId(SLONG lIndex, SLONG lDisAppearImgId);
//��V�ƾ�
SLONG	GetBreakMagicPartDirNum(SLONG lIndex);
void 	SetBreakMagicPartDirNum(SLONG lIndex, SLONG lDirNum);
//�B�ʪ��y��
SLONG	GetBreakMagicPartPath(SLONG lIndex);
void 	SetBreakMagicPartPath(SLONG lIndex, SLONG lPath);
//�ͦs���覡
SLONG	GetBreakMagicPartSurvial(SLONG lIndex);
void 	SetBreakMagicPartSurvial(SLONG lIndex, SLONG lSurvial);
//�W�Ϫ��ĪG
SLONG	GetBreakMagicPartDrawEff(SLONG lIndex);
void 	SetBreakMagicPartDrawEff(SLONG lIndex, SLONG lDrawEff);
//��������������
SLONG	GetBreakMagicPartStop(SLONG lIndex);
void 	SetBreakMagicPartStop(SLONG lIndex, SLONG lStop);
//���ʳt��
void	SetBreakMagicPartSpeed(SLONG lIndex, double fSpeed);
double	GetBreakMagicPartSpeed(SLONG lIndex);

void	SetBreakMagicPartVertSpeed(SLONG lIndex, double fVertSpeed);
double	GetBreakMagicPartVertSpeed(SLONG lIndex);

//  ���]�k�ե󪺤�V..���ܨ�..�~����ɪ���V
//----
SLONG   MagicDirToImgDir(SLONG lMagicDir, SLONG MaxDir);
//����MAGIC_PART����TPOS_MAGIC_UNIT�l��
void    SetBreakMagicPartMagicUnit(SLONG lIndex, TPOS_MAGIC_UNIT *p_unit);

// break magic functions
//
void	InitBreakMagicFunctions(void);
void	SetBreakMagicFunction(SLONG lSkillNo, FNBREAKMAGIC pFunc);
void	ExecBreakMagic(SLONG lSkillNo, SLONG lSrcNo, SLONG lType, SLONG lDestX, SLONG lDestY, SLONG lDestNo);


