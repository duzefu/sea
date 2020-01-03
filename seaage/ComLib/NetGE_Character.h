/*
**	NetGE_Character.h 
**	character functions header.
**
**	Jack, 2002.12.9
**
**	Jack, 2003.5.14.
**		-- Added CareerLevel to character structure.
**
*/
#pragma once
#include "NetGE_Item.h"

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_CHARACTER_PER_ZONE			1000		//�C��ZONE������e�Ǫ��H��(NPC, PLAYER, ...)
//
#define	MAX_CHARACTER_BAG_ITEMS			27			//�H���I�]���~�ƶq
#define	MAX_CHARACTER_SASH_ITEMS		4			//�H���y�]���~�ƶq
#define	MAX_CHARACTER_TRANS_ITEMS		3			//�H���ǰe���~�ƶq
#define	MAX_CHARACTER_BANK_ITEMS		36			//�H���Ȧ檫�~�ƶq
#define	MAX_CHARACTER_SKILLS			36			//�H���ޯ�ƶq
#define	MAX_CHARACTER_FN_SKILLS			8			//�H���ֱ���ޯ�
#define	MAX_CHARACTER_DEFAULT_SKILLS	12			//�H���q�{�ޯ�
#define	MAX_CHARACTER_DEFAULT_ITEMS		1			//�H���q�{���~
#define	MAX_CHARACTER_TEAM_MEMBERS		8			//�H���P���H��, ������0. 
#define	MAX_CHARACTER_ENEMY_MEMBERS		8		 	//�H�����ĤH�C��
#define	MAX_CHARACTER_PARTS				7			//�H���ե�ƥ�
#define	MAX_CHARACTER_QUESTS			16			//�H������������̦h���ȼƥ�


//(���⪺1/0���A) POS_CHARACTER_STATE::BitState
#define	CHARACTER_BAG_OPENED			0x00000001	//�H���I�]�b���}���A
#define	CHARACTER_ON_FIGHT				0x00000002	//�H���ثe�b�԰����A
#define	CHARACTER_IS_DEAD				0x00000004	//�H���w�g���`
#define	CHARACTER_ON_SEA				0x00000008	//�H���ثe�b���W
//�M���Ԧ��������A
#define	CHARACTER_ON_DEFENCE			0x00000010	//�H���b���m���A
#define	CHARACTER_DODGE       			0x00000020	//�H�����פ�...���ʱa�ݼv
#define CHARACTER_ON_BLOCK              0X00000040  //����(����npc�����ɾ��v)
#define CHARACTER_MAGIC_REBOUND         0X00000080  //�]�k�ϼu(���@�w�������k�N)
#define CHARACTER_SHOW_SUBTIL           0X00000100  //����(�ۤv�H�i��,�ĤH���i��)
#define CHARACTER_SPEED_DELAY1          0X00000200  //��w1(�u���b���ʪ��ɭ�..�t���ܺC,�ʵe����t���ܺC)
#define CHARACTER_SPEED_DELAY2          0X00000400  //��w2��w2(�ʵe�t�׼���[��,���ʳt���ܺC)
#define CHARACTER_WITHOUT_EQUAL         0X00000800  //�L��(�H���W�ϻݭn�{�{)
#define CHARACTER_BLACK_NPC             0X00001000  //�¤H���A
#define CHARACTER_NPC_FAINT             0X00002000  //NPC�L�˪��A
#define CHARACTER_NPC_STAND_UP          0X00004000  //NPC���_��

#define CHARACTER_HEAD_SLEEP            0X00008000  //�Y��
#define CHARACTER_ON_SLEEP              0X00010000  //�ίv
#define CHARACTER_ON_SWIVET             0X00020000  //�g��
#define CHARACTER_ON_BLIND              0X00040000  //����
#define CHARACTER_UP_DEFENCE            0X00080000  //�W�[���m
//�M���Ԧ����Y�����A
#define CHARACTER_BOAT_ROTATE           0X00100000  //����(�Q��)�
#define CHARACTER_BOAT_FIRE             0X00200000  //�ۤ�(�Q��)�
#define CHARACTER_BOAT_EXPLODE          0X00400000  //�z��(�Q��)�
#define CHARACTER_BOAT_SAILHURT         0X00800000  //�|�l�` (�Q��)	�
#define CHARACTER_BOAT_RUDDERHURT       0X01000000  //��l�` (�Q��)	�
#define CHARACTER_BOAT_PRETEND          0X02000000  //���� (�D��)	�
#define CHARACTER_BOAT_HALFDOWN         0X04000000  //�b�I	�
#define CHARACTER_BOAT_OCTOPUS          0X08000000  //���� (�Q��)	�
//
#define	CHARACTER_IS_PAUSE				0x40000000	//�H�����b�Ȱ���Ӱʧ@��
#define	CHARACTER_SPECIAL_ITEM			0x80000000	//��a�S�w���~(�Ω�Ǫ�,���`���X)
//------------------------------------------------------------
//NPC���O(NPC KIND)
//-------------------------
#define NPC_KIND_EMPLACEMENT			0   //���x
#define NPC_KIND_GUIDEPOST				1   //���P
#define NPC_KIND_NORMAL_MONSTER			2   //���q�Ǫ�
#define NPC_KIND_HEADER_MONSTER			3   //�Y�ةǪ�
#define NPC_KIND_BOSS_MONSTER			4   //BOSS�Ǫ�
#define NPC_KIND_THIEF_MONSTER			5   //�p����
#define NPC_KIND_TREASURE_MONSTER		6   //�_����
#define NPC_KIND_GUARD					7   //ĵ��
#define NPC_KIND_NPC					8   //���H(���H)
#define NPC_KIND_PLAYER					9   //���a
#define NPC_KIND_TREASURE				10  //�_��(�p�q)
#define NPC_KIND_MERMAID				11  //���H��(�|���ܭI������)
#define NPC_KIND_TRAP					12  //����
#define NPC_KIND_SUBMERGED_ROCK			13  //�t�G
#define NPC_KIND_BURBLE					14  //�x��
#define NPC_KIND_STATUARY				15  //�J��
#define	NPC_KIND_CORPSE					16	//����
#define MAX_NPC_KINDS				    17  //�`�����O�ƥ�

//--------------------------------------------------------------
//TEAM MEMBER FLAGS
//------------------------------
#define	TEAM_MEMBER_IN_SAME_ZONE		0x00000001	//�b�P�@��ZONE��
//
//
//---------------------------------------------------------------
//QUEST PAYTYPE DEFINES (TPOS_QUEST_INFO::PayType)
//---------------------------------------------------------------
#define	QUEST_PAY_NONE					0	//�L���S
#define	QUEST_PAY_PRESTIGE				1	//�n����S
#define	QUEST_PAY_MONEY					2	//�������S
#define	QUEST_PAY_ITEM					3	//���~���S
#define	QUEST_PAY_STR					4	//�O�q
#define	QUEST_PAY_INT					5	//���z
#define	QUEST_PAY_WIT					6	//���
#define	QUEST_PAY_LUCKY					7	//�B��
#define	QUEST_PAY_KEEPITEM				8	//�H��
//
//---------------------------------------------------------------
//QUEST TYPE DEFINES (TPOS_QUEST_INFO::QuestType)
//---------------------------------------------------------------
#define	QUEST_TYPE_NONE					0	//�L����
#define	QUEST_TYPE_DELIVER				1	//�e�f���� (deliver goods)
#define	QUEST_TYPE_SCRIPT				2	//�@������ (be written in script file)


// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma pack(1)


//
//Level 0 Structures ----------------------
//

//
//������U��Ƶ��c
typedef	struct POS_CHARACTER_REG
{
	CHAR	ID[32];			//�b���W��
	CHAR	MainName[32];	//����W��
	CHAR	NickName[32];	//����ʺ�
	CHAR	Country;		//���ݰ�a
	CHAR	Eyes;			//����
	CHAR	Mouth;			//�L
	CHAR	Color;			//�C��
	DWORD	Index;			//����
	DWORD	DefaultIndex;	//�q�{����
} TPOS_CHARACTER_REG, *LPTPOS_CHARACTER_REG;


//
//�����q�{��Ƶ��c
typedef	struct POS_CHARACTER_DEFAULT 
{
	UHINT	Index;			//�������
	SLONG	FileIndex;		//����v��������
	CHAR	Sex;			//�ʧO
	CHAR	Career;			//¾�~
	CHAR	Color;			//�C��
	CHAR	Eyes;			//����
	CHAR	Mouth;			//�L
	CHAR	Country;		//���ݰ�a
	UHINT	Str;			//�O�q
	UHINT	Ins;			//��ı
	UHINT	Wis;			//���O
	UHINT	Lucky;			//�B��
	UHINT	Hp;				//�ͩR�O
	UHINT	Mp;				//�k�O
	UHINT	Mspeed;			//���ʳt��
	UHINT	Attack;			//�����O
	UHINT	Defence;		//���m�O
	SLONG	Sight;			//����
	SHINT		Skill[MAX_CHARACTER_DEFAULT_SKILLS];	//�ޯ�
	POS_ITEM	Item[MAX_CHARACTER_DEFAULT_ITEMS];		//���~
} TPOS_CHARACTER_DEFAULT, *LPTPOS_CHARACTER_DEFAULT;


//�����Ƽ��Y
typedef	struct POS_CHARACTER_HEADER 
{
	UHINT	Type;			//����
	UHINT	Index;			//����
} TPOS_CHARACTER_HEADER, *LPTPOS_CHARACTER_HEADER;


//����m�W
typedef	struct POS_CHARACTER_NAME 
{
	CHAR	ID[32];			//�b��
	CHAR	MainName[32];	//����W�r
	CHAR	NickName[32];	//�ʺ�
	ULONG	QQID;			//QQ�ߤ@ID
	SLONG	Index;			//���b�����ĴX�Ө���, 0~3
} TPOS_CHARACTER_NAME, *LPTPOS_CHARACTER_NAME;


//����~�[
typedef	struct POS_CHARACTER_STYLE 
{
	CHAR	Picture;		//�~�[
	CHAR	Color;			//�C��
	CHAR	Eyes;			//����
	CHAR	Mouth;			//�L��
	CHAR	MainNameColor;	//�W�r�C��
	CHAR	NickNameColor;	//�ʺ��C��
	CHAR	MessageColor;	//�T���C��
	CHAR	TalkBackColor;	//��ѰT���I���C��
	ULONG	Logo;			//�u�|�лx
	SLONG	FileIndex;		//��e�Ϲ�����
	SLONG	LandFileIndex;	//���a�Ϲ�����
	SLONG	SeaFileIndex;	//���v�Ϲ�����
	ULONG	PartRGB[MAX_CHARACTER_PARTS];	//�ո˳����C��, ARGB.
	ULONG	NameColorTicks;	//�����H��
} TPOS_CHARACTER_STYLE, *LPTPOS_CHARACTER_STYLE;


//�����m
typedef	struct POS_CHARACTER_POSITION 
{
	CHAR	ZoneName[32];	//�Ҧb�ϰ�
	SLONG	X;				//��e�y��
	SLONG	Y;				//��e�y��
	SLONG	Z;				//��e�y��
	UCHAR	Dir;			//�H����V
	SLONG	DirFrame;		//�Y�Ӥ�V�V
	SLONG	Frame;			//��Ӱʵe�Ϲ��V
	SLONG	StopRadius;		//���ץb�|
	union
	{
		SLONG	DestX;				//����: �ؼЮy�� X
		SLONG	SequentialStep;		//�s��: �O�_�i��U�@�ӳs�򪺰ʧ@
		SLONG	BeatedBy;			//�Q��: �֧����� ?
	};
	union
	{
		SLONG	DestY;				//����: �ؼЮy�� Y
		SLONG	IdleTicks;			//�ݾ�: �ݾ����ɶ�
		SLONG	MuseTicks;			//�߷Q: �C�j�h���ɶ��i��@���ƭȭp��
		SLONG	BeatedWith;			//�Q��: �Q�ƻ�ޯ���� ?
	};
	union
	{
		SLONG	DestZ;				//����: �ؼЮy�� Z
		SLONG	PantTicks;			//�Q����: ���˦b�a�W�P���_�Ӥ������ݮ��ɶ�
		SLONG	DeadTicks;			//���`: ���`�F�h���ɶ�
		SLONG	DeadAlpha;			//���`: ���`����������ALPHA��
	};
	union
	{
		SLONG	DestID;				//�ؼ�ID
		SLONG	ClashSteps;			//�ļ�: �ļ����B��
		SLONG	PatrolTicks;		//����: ����IDLE����e�ɶ�
	};
	union
	{
		SLONG	OrigX;				//�_�l�y��
		SLONG	GadTotalTicks;		//�H������: IDLE���`�ɶ�
		SLONG	BeatedX;			//�Q��,���`,�Q����: ������ x�y��
	};
	union
	{
		SLONG	OrigY;				//�_�l�y��
		SLONG	GadTicks;			//�H������: IDLE����e�ɶ�
		SLONG	BeatedY;			//�Q��,���`,�Q����: ������ y�y��
	};
	union
	{
		SLONG	OrigZ;					//�_�l�y��
		SLONG	AttackPantTicks;		//����: ������ݮ��ɶ�
	};
	union
	{
		ULONG	OrigID;					//�_�lID
		SLONG	PatrolTotalTicks;		//����: ����IDLE���`�ɶ�
		SLONG	AttackPantTotalTicks;	//����: ������ݮ��`�ɶ�
	};
	union
	{
		SLONG	DialogWithCount;		//���: �Q��NPC�P�ɻP�X�Ӫ��a�b���
		SLONG	DialogDestIndex;		//���: ���a�P����NPC�b���
	};
} TPOS_CHARACTER_POSITION, *LPTPOS_CHARACTER_POSITION;


//����t��
typedef	struct POS_CHARACTER_SPEED 
{
	SLONG	Mspeed;			//�H�����ʳt��
	SLONG	FSpeedX;		//��X�b�t��
	SLONG	FSpeedY;		//��Y�b�t��
	UHINT	SailSize;		//��|�Y�������n
	UHINT	Turn;			//����V�O
	UHINT	Weight;			//��q
	SLONG	DegreeDir;		//���V
	SLONG	OldDegreeDir;	//���Ӥ�V
} TPOS_CHARACTER_SPEED, *LPTPOS_CHARACTER_SPEED;


//���⪬�A
typedef	struct POS_CHARACTER_STATE 
{
	ULONG	BitState;				//1/0���A(�O�_�b�԰����A, �]�]�O�_���}, �b���W�γ��a, �O�_���`...)

	SHINT	ReliveTicks;			//�A�ͪ��ɶ�
	SHINT	DeadState;				//���`�����A

	SHINT	RMagicState;			//�k��ޯબ�A
	SHINT	RMagicTotalTicks;		//�k��ޯ��`�ɶ�
	SHINT	RMagicCurrentTicks;		//�k��ޯ��e�ɶ�

	SHINT	HeadSleepState;			//�Y�w, �ίv(�Q��)
	SHINT	HeadSleepTicks;			//�Y�w, �ίv �ɶ�
	SHINT	HeadSleepLevel;			//�Y�w, �ίv ����

	SHINT	HeadDefenceState;		//���m�[�j(�Q�ʩΥD��)
	SHINT	HeadDefenceTicks;		//���m�[�j �ɶ�
	SHINT	HeadDefenceLevel;		//���m�[�j ����

	SHINT	HeadMagicState;			//�]�k�ϼu
	SHINT	HeadMagicTimes;			//�]�k�ϼu����	
	SHINT	HeadMagicLevel;			//�]�k�ϼu����

	SHINT	HeadBlindState;			//����(�Q��)	
	SHINT	HeadBlindTicks;			//���� �ɶ�	
	SHINT	HeadBlindLevel;			//���� ����	

	SHINT	BodyDodgeState;			//���{(�D�ʥ�����)

	SHINT	BodyVirusState;			//���r(�Q��)	
	SHINT	BodyVirusTicks;			//���r �ɶ�	
	SHINT	BodyVirusLevel;			//���r ����	

	SHINT	BodyHideState;			//�Q�l��(�Q��), ����1, ����2(�D��)	
	SHINT	BodyHideTicks;			//�Q�l��(�Q��), ����1, ����2 �ɶ�	
	SHINT	BodyHideLevel;			//�Q�l��(�Q��), ����1, ����2 ����

	SHINT	FootSpeedState;			//��w1, ��w2(�Q�ʩΪ̦b�d��)	
	SHINT	FootSpeedTicks;			//��w1, ��w2 �ɶ�	
	SHINT	FootSpeedLevel;			//��w1, ��w2 ����	

	SHINT	RotateState;			//����(�Q��)�
	SHINT	RotateTicks;			//���� �ɶ�	�
	SHINT	RotateLevel;			//���� ����	�

	SHINT	FireState;				//�ۤ�(�Q��)�
	SHINT	FireTicks;				//�ۤ� �ɶ�	�
	SHINT	FireLevel;				//�ۤ� ����	�

	SHINT	ExplodeState;			//�z��(�Q��)�
	SHINT	ExplodeTicks;			//�z�� �ɶ�	�
	SHINT	ExplodeLevel;			//�z�� ����	�

	SHINT	SailHurtState;			//�|�l�` (�Q��)	�
	SHINT	RudderHurtState;		//��l�` (�Q��)	�

	SHINT	PretendState;			//���� (�D��)	�
	SHINT	PretendOldFileIndex;	//���˫e���Ϲ�	�
	SHINT	PretendToFileIndex;		//���˫᪺�Ϲ�	�

	SHINT	HalfDownState;			//�b�I	�

	SHINT	OctopusState;			//���� (�Q��)	�
	SHINT	OctopusTicks;			//���� �ɶ�	�
	SHINT	OctopusLevel;			//���� ����	�

	ULONG	TotalOnlineTicks;		//�`�b�u�ɶ�

    // mark by lijun 2003-06-19
	//ULONG	AI;						//�H���԰�AI
} TPOS_CHARACTER_STATE, *LPTPOS_CHARACTER_STATE;
//���⪺AI�ƾڶ�
typedef	struct POS_CHARACTER_AI
{
    ULONG   AI;                 //�H�����欰AI..�b�}�����]�w
    ULONG   AIBlock;            //�H���ҳB�b��AI��
}TPOS_CHARACTER_AI, *LPTPOS_CHARACTER_AI;


//�H���O�q
typedef	struct POS_CHARACTER_PROPERTY_STR
{
	UHINT	FinalStr;			//�̫�O�q
	UHINT	InitStr;			//��l�Ʈɳ]�w���O�q��
	UHINT	LevUpStr;			//�֭p�ɯŮɤ��t���O�q��
	UHINT	PointStr;			//��e�ۤv�հt�W�[���O�q
} TPOS_CHARACTER_PROPERTY_STR, *LPTPOS_CHARACTER_PROPERTY_STR;



//�H����ı
typedef	struct POS_CHARACTER_PROPERTY_INS 
{
	UHINT	FinalIns;			//�̫᪽ı
	UHINT	InitIns;			//��l�Ʈɳ]�w����ı��
	UHINT	LevUpIns;			//�֭p�ɯŮɤ��t����ı��
	UHINT	PointIns;			//��e�ۤv�հt�W�[����ı
} TPOS_CHARACTER_PROPERTY_INS, *LPTPOS_CHARACTER_PROPERTY_INS;


//�H�����z
typedef	struct POS_CHARACTER_PROPERTY_WIT
{
	UHINT	FinalWit;			//�̫ᴼ�z
	UHINT	InitWit;			//��l�Ʈɳ]�w�����z��
	UHINT	LevUpWit;			//�֭p�ɯŮɤ��t�����z��
	UHINT	PointWit;			//��e�ۤv�հt�W�[�����z
} TPOS_CHARACTER_PROPERTY_WIT, *LPTPOS_CHARACTER_PROPERTY_WIT;


//�H���B��
typedef	struct POS_CHARACTER_PROPERTY_LUCKY
{
	UHINT	FinalLucky;			//�̫ᩯ�B
	UHINT	InitLucky;			//��l�Ʈɳ]�w�����B��
	UHINT	LevUpLucky;			//�֭p�ɯŮɤ��t�����B��
	UHINT	PointLucky;			//��e�ۤv�հt�W�[�����B
} TPOS_CHARACTER_PROPERTY_LUCKY, *LPTPOS_CHARACTER_PROPERTY_LUCKY;


//�H�������O
typedef	struct POS_CHARACTER_PROPERTY_ATTACK
{
	UHINT	FinalPhysicAtt;		//�H���̲ת��z�����O(�P�ޯ�B���)
	UHINT	FinalMagicAtt;		//�H���̲תk�N�����O(�P�ޯ�B���)
	UHINT	FinalSpecAtt;		//�H���̲ׯS������O(�P�ޯ�B���)
	//
	UHINT	FinalAtt;				//�H���̲װ򥻧����O = EquipBaseAtt * AttribAttRatio %
	UHINT	AttribAttRatio;			//���ݩʼv�T�����O���ʤ���
	//
	UHINT	EquipBaseAtt;			//�˳Ƨ����O��
	UHINT	EquipAddedMagicAtt;		//�˳ƪ��[���k�N�����O
	UHINT	EquipAddedSpecAtt;		//�˳ƪ��[���S������O
	//
	UHINT	SkillAttackRatio;		//�Ҧ��ޯ���[��������O���v�T�ʤ����`�M
	//
	UHINT	AttackRange;		//�����d��
	UHINT	AttackRate;			//�R���v
	UHINT	SightRange;			//�����d��
	//
	UHINT 	FinalExplodeRate;	//���z�v
	UHINT	EquipExplodeRate;	//�˳ƪ����z�v
	UHINT	SkillExplodeRate;	//����ޯध���[���z�v
} TPOS_CHARACTER_PROPERTY_ATTACK, *LPTPOS_CHARACTER_PROPERTY_ATTACK;


//�H�����m�O
typedef	struct  POS_CHARACTER_PROPERTY_DEFENCE
{
	UHINT	FinalDefence;		//�̲ר��m�O
	UHINT	BaseDefence;		//���ݩʹB��o�Ӫ����m�O��
	UHINT	EquipDefence;		//�˳ƨ��m�O��
	UHINT	SkillDefence;		//�ޯਾ�m�O��
	UHINT	SkillDefenceTicks;	//�ޯਾ�m�O���Įɶ�
	//
	union
	{
		UHINT	EquipResistRatio;	//�˳Ʃ�ܦʤ���
		UHINT	FinalResist;		//�̲ש�ܤO
	};
	//
	UHINT	DodgeRate;			//���ײv
	UHINT	ParryRate;			//��ײv
} TPOS_CHARACTER_PROPERTY_DEFENCE, *LPTPOS_CHARACTER_PROPERTY_DEFENCE;


//�����ݩ�
typedef	struct POS_CHARACTER_PROPERTY 
{
	UHINT	PropertyPoint;							//�ݩʼW�[�Ѿl�I��
	TPOS_CHARACTER_PROPERTY_STR			Str;		//�O�q
	TPOS_CHARACTER_PROPERTY_INS			Ins;		//��ı
	TPOS_CHARACTER_PROPERTY_WIT			Wit;		//���z
	TPOS_CHARACTER_PROPERTY_LUCKY		Lucky;		//�B��
	TPOS_CHARACTER_PROPERTY_ATTACK		Attack;		//����
	TPOS_CHARACTER_PROPERTY_DEFENCE		Defence;	//���m�O
} TPOS_CHARACTER_PROPERTY, *LPTPOS_CHARACTER_PROPERTY;


//���ⵥ�Ÿg��
typedef	struct POS_CHARACTER_EXPLEV 
{
	ULONG	Exp;			//�g���
	ULONG	NextExp;		//�U�@�Ÿg���
	UHINT	Level;			//����
} TPOS_CHARACTER_EXPLEV, *LPTPOS_CHARACTER_EXPLEV;


//����ͩR�]�k
typedef	struct POS_CHARACTER_HPMP 
{
	UHINT	Hp;				//��e�ͩR�O
	UHINT	MaxHp;			//�ͩR�O�W��
	UHINT	AttribHp;		//���ݩʹB��o�Ӫ��ͩR�O�W��
	UHINT	LevelUpHp;		//�ɯ���o���ͩR�O�W����
	UHINT	EquipHp;		//�˳ƪ��[���ͩR�O�W����
	UHINT	SkillHp;		//�ޯ�v�T���ͩR�O�W����
	UHINT	HpRes;			//�ͩR�^�_�O
	UHINT	Mp;				//��e���O
	UHINT	MaxMp;			//���O�W��
	UHINT	AttribMp;		//���ݩʹB��o�Ӫ����O�W��
	UHINT	LevelUpMp;		//�ɯ���o�����O�W����
	UHINT	EquipMp;		//�˳ƪ��[�����O�W����
	UHINT	SkillMp;		//�ޯ�v�T�����O�W����
	UHINT	MpRes;			//���O�^�_�O
} TPOS_CHARACTER_HPMP, *LPTPOS_CHARACTER_HPMP;


//����ޯ�
typedef	struct POS_CHARACTER_SKILLEXP
{
	SHINT	Skill[MAX_CHARACTER_SKILLS];	//�ޯ�s��
	UHINT	Level[MAX_CHARACTER_SKILLS];	//�ޯ൥��
} TPOS_CHARACTER_SKILLEXP, *LPTPOS_CHARACTER_SKILLEXP;


//����˳�
typedef	struct POS_CHARACTER_EQUIPMENT 
{
	TPOS_ITEM	EquHead;		//�Y��
	TPOS_ITEM	EquNeck;		//�V��
	TPOS_ITEM	EquBody;		//����
	TPOS_ITEM	EquWaist;		//�y��
	TPOS_ITEM	EquGlove;		//��M
	TPOS_ITEM	EquWeapon;		//�Z��
	TPOS_ITEM	EquWrist;		//����
	TPOS_ITEM	EquFeet;		//�}��
	TPOS_ITEM	EquOtherA;		//��LA
	TPOS_ITEM	EquOtherB;		//��LB
	TPOS_ITEM	EquOtherC;		//��LC
} TPOS_CHARACTER_EQUIPMENT, *LPCHARACTER_EQUIPMENT;


//���⨭�W���~����
typedef	struct POS_CHARACTER_BODY_IM 
{
	TPOS_ITEM	BagItem[MAX_CHARACTER_BAG_ITEMS];		//�I�]�����~
	TPOS_ITEM	SashItem[MAX_CHARACTER_SASH_ITEMS];		//�y�]�����~
	TPOS_ITEM	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ�ǰe�檫�~
	TPOS_ITEM	OnMouseItem;	//�b�ƹ��W�����~
	TPOS_ITEM	TreasureItem;	//���_�Ϫ��~
	ULONG		Money;			//���W������
} TPOS_CHARACTER_BODY_IM, *LPTPOS_CHARACTER_BODY_IM;


//����Ȧ檫�~����
typedef	struct POS_CHARACTER_BANK_IM 
{
	TPOS_ITEM	Item[MAX_CHARACTER_BANK_ITEMS];		//�Ȧ檺���~
	ULONG		Money;			//�Ȧ檺�s��
} TPOS_CHARACTER_BANK_IM, *LPTPOS_CHARACTER_BANK_IM;

//���ⶤ���
typedef	struct POS_CHARACTER_TEAM_MEMBER
{
	ULONG	Flags;			//�аO
	CHAR	MainName[32];	//�W��
	UHINT	Hp;				//��eHP
	UHINT	MaxHp;			//��eHP�W��
	UHINT	Level;			//��e����
	CHAR	Eyes;			//�����Ϲ�����
	CHAR	Mouth;			//�f�Ϲ�����
	CHAR	Career;			//�H��¾�~
	CHAR	Sex;			//�H���ʧO
	CHAR	ZoneName[32];	//�Ҧb�ϰ�
} TPOS_CHARACTER_TEAM_MEMBER, *LPTPOS_CHARACTER_TEAM_MEMBER;

//����ն�
typedef	struct POS_CHARACTER_TEAM 
{
	SLONG	MaxMembers;		//��e����H���ƥ�
	TPOS_CHARACTER_TEAM_MEMBER	Member[MAX_CHARACTER_TEAM_MEMBERS];		//��������
} TPOS_CHARACTER_TEAM, *LPTPOS_CHARACTER_TEAM;


//����ĤH����
typedef	struct POS_CHARACTER_ENEMY_MEMBER 
{
	UHINT	HitHp;			//���F�h��HP
	ULONG	Flag;			//�ĤH���лx, 0 = ��@���a, 1 = ����
	CHAR	MainName[32];	//�ĤH���W��
} TPOS_CHARACTER_ENEMY_MEMBER, *LPTPOS_CHARACTER_ENEMY_MEMBER;

//����ĤH
typedef	struct POS_CHARACTER_ENEMY 
{
	SLONG	MaxMembers;
	TPOS_CHARACTER_ENEMY_MEMBER	Member[MAX_CHARACTER_ENEMY_MEMBERS];
} TPOS_CHARACTER_ENEMY, *LPTPOS_CHARACTER_ENEMY;


//������|���Y
typedef	struct POS_CHARACTER_SOCIETY 
{
	CHAR	Sex;				//�ʧO
	CHAR	Country;			//��a
	CHAR	Guild[32];			//�u�|
	CHAR	Spouse[32];			//�t��
	CHAR	Career;				//¾�~����
	UCHR	CareerLevel;		//¾�~����
	ULONG	Office;				//�u�|��¾��
	CHAR	Nobility[16];		//���
	SLONG	GoodEvil;			//���c��
	SLONG	Prestige;			//�n��
	ULONG	PkCount;			//PK���O�H���h�֤H
	ULONG	PkedCount;			//�Q�HPK��������
	UHINT	Kind;				//����	
} TPOS_CHARACTER_SOCIETY, *LPTPOS_CHARACTER_SOCIETY;


//����ֱ�����
typedef	struct POS_CHARACTER_QUICKBUTTON 
{
	SHINT	LandLeftSkill;		//���a�ƹ�����ޯ�
	SHINT	LandRightSkill;		//���a�ƹ��k��ޯ�
	SHINT	LandFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//���a����F1~F8�����ޯ�s��
	CHAR	LandFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//���a����F1~F8�����ޯ�]�m�b���u��
	//
	SHINT	SeaLeftSkill;		//���v�ƹ�����ޯ�
	SHINT	SeaRightSkill;		//���v�ƹ��k��ޯ�
	SHINT	SeaFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//���v����F1~F8�����ޯ�s��
	CHAR	SeaFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//���v����F1~F8�����ޯ�]�m�b���u��
} TPOS_CHARACTER_QUICKBUTTON, *LPTPOS_CHARACTER_QUICKBUTTON;



//����ʧ@����
typedef	struct POS_CHARACTER_ACTION 
{
	SLONG	DoingKind;			//�ư�����
	SLONG	DoingStep;			//�ưȶi��{��
	//
	SHINT	DoingMagic;			//��e�ϥΪ��k�N�ޯ�s��
	SHINT	MagicTimes;			//��e�ϥΪ��k�N�ޯ୫�Ʀ���
	SHINT	FightTicks;			//�԰��ϥΪ��p��
	UCHAR	ImageAction;		//���ɰʧ@����
	ULONG	ImageID;			//���ɤ��Х�
} TPOS_CHARACTER_ACTION, *LPTPOS_CHARACTER_ACTION;


// Jack, quest related data [5/8/2003]
typedef	struct POS_QUEST_INFO 
{
	UCHR	QuestType;			//�������O (QUEST_TYPE_$$)
	CHAR	PublishZone[32];	//�o�_�a�I(�ϰ�)
	CHAR	PublishNpc[32];		//�o�_�H
	CHAR	TargetZone[32];		//�ؼЦa�I(�ϰ�)
	CHAR	TargetNpc[32];		//�ؼФH
	ULONG	AcceptTime;			//���a�������Ȫ��ɶ�
	ULONG	Deadline;			//���ȧ������̲״���
	UCHR	PayType;			//�������Ȫ����S���O (QUEST_PAY_$$)
	ULONG	PayData;			//�������Ȫ����S�ƭ� (�i�H�O�n��Prestidge, ����Money �Ϊ̪��~ItemBaseID )
	UCHR	PunishType;			//���������Ȫ��g�@���O
	ULONG	PunishData;			//���������Ȫ��g�@�ƭ�
	CHAR	Memo[64];			//���Ȼ���
} TPOS_QUEST_INFO, *LPTPOS_QUEST_INFO;


typedef	struct POS_CHARACTER_QUEST 
{
	TPOS_QUEST_INFO		QuestInfo[MAX_CHARACTER_QUESTS];
} TPOS_CHARACTER_QUEST, *LPTPOS_CHARACTER_QUEST;

//�����Ƶ��c
typedef	struct POS_CHARACTER 
{
	TPOS_CHARACTER_HEADER		Header;			//���Y
	TPOS_CHARACTER_NAME			Name;			//�m�W
	TPOS_CHARACTER_STYLE		Style;			//�~�[
	TPOS_CHARACTER_POSITION		Position;		//��m
	TPOS_CHARACTER_SPEED		Speed;			//�t��
	TPOS_CHARACTER_STATE		State;			//���A
    TPOS_CHARACTER_AI	        AI;             //AI
	TPOS_CHARACTER_PROPERTY		Property;		//�ݩ�
	TPOS_CHARACTER_EXPLEV		ExpLev;			//���Ÿg��
	TPOS_CHARACTER_HPMP			HpMp;			//�ͩR�]�k
	TPOS_CHARACTER_SKILLEXP		SkillExp;		//�ޯ�
	TPOS_CHARACTER_EQUIPMENT	Equipment;		//�˳�
	TPOS_CHARACTER_BODY_IM		BodyItemMoney;	//���W���~����
	TPOS_CHARACTER_BANK_IM		BankItemMoney;	//�Ȧ檫�~����
	TPOS_CHARACTER_TEAM			Team;			//�ն�
	TPOS_CHARACTER_ENEMY		Enemy;			//�ĤH
	TPOS_CHARACTER_SOCIETY		Society;		//���|���Y
	TPOS_CHARACTER_QUICKBUTTON	QuickButton;	//�ֱ�����
	TPOS_CHARACTER_ACTION		Action;			//�ʧ@����
	TPOS_CHARACTER_QUEST		Quest;			//���Ȭ���(Jack, [5/8/2003]) 
} TPOS_CHARACTER, *LPTPOS_CHARACTER;


//
//Level 1 Structures ----------------------
//

#pragma pack(pop)

//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_CHARACTER	ZoneCharacter[MAX_CHARACTER_PER_ZONE];

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void	InitAllZoneCharacters(void);
extern	void	ClearOneCharacter(SLONG lIndex);
extern	void	ClearCharacterSkills(SLONG lIndex);
extern	SLONG	IsCharacterAvailable(SLONG lIndex);
//
// Level 0 functions ------------------------------------------------
extern	void	SetCharacterType(SLONG lIndex, UHINT uType);
extern	UHINT	GetCharacterType(SLONG lIndex);
extern	void	SetCharacterAccount(SLONG lIndex, CHAR *szAccout);
extern	CHAR*	GetCharacterAccount(SLONG lIndex);
extern	void	SetCharacterMainName(SLONG lIndex, CHAR *szMainName);
extern	CHAR*	GetCharacterMainName(SLONG lIndex);
extern	void	SetCharacterNickName(SLONG lIndex, CHAR *szNickName);
extern	CHAR*	GetCharacterNickName(SLONG lIndex);
extern	void	SetCharacterQQID(SLONG lIndex, ULONG uID);
extern	ULONG	GetCharacterQQID(SLONG lIndex);
extern	void	SetCharacterIndex(SLONG lCharIndex, SLONG lIndex);
extern	SLONG	GetCharacterIndex(SLONG lCharIndex);
//
extern	void	SetCharacterPicture(SLONG lIndex, SLONG lPicture);
extern	SLONG	GetCharacterPicture(SLONG lIndex);
extern	void	SetCharacterColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterColor(SLONG lIndex);
extern	void	SetCharacterEyes(SLONG lIndex, SLONG lEyes);
extern	SLONG	GetCharacterEyes(SLONG lIndex);
extern	void	SetCharacterMouth(SLONG lIndex, SLONG lMouth);
extern	SLONG	GetCharacterMouth(SLONG lIndex);
extern	void	SetCharacterMainNameColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterMainNameColor(SLONG lIndex);
extern	void	SetCharacterNickNameColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterNickNameColor(SLONG lIndex);
extern	void	SetCharacterMessageColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterMessageColor(SLONG lIndex);
extern	void	SetCharacterTalkBackColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterTalkBackColor(SLONG lIndex);
extern	void	SetCharacterLogo(SLONG lIndex, ULONG lLogo);
extern	ULONG	GetCharacterLogo(SLONG lIndex);
extern	void	SetCharacterFileIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetCharacterFileIndex(SLONG lIndex);
extern	void	SetCharacterLandFileIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetCharacterLandFileIndex(SLONG lIndex);
extern	void	SetCharacterSeaFileIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetCharacterSeaFileIndex(SLONG lIndex);
extern	void	SetCharacterPartRGB(SLONG lIndex, SLONG lPart, ULONG uRGB);
extern	ULONG	GetCharacterPartRGB(SLONG lIndex, SLONG lPart);
extern	void	SetCharacterNameColorTicks(SLONG lIndex, ULONG uTicks);
extern	ULONG	GetCharacterNameColorTicks(SLONG lIndex);

//
extern	void	SetCharacterZoneName(SLONG lIndex, CHAR *szName);
extern	CHAR *	GetCharacterZoneName(SLONG lIndex);
extern	void	SetCharacterPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetCharacterPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetCharacterDir(SLONG lIndex, SLONG lDir);
extern	SLONG	GetCharacterDir(SLONG lIndex);
extern	void	SetCharacterDirFrame(SLONG lIndex, SLONG lFrame);
extern	SLONG	GetCharacterDirFrame(SLONG lIndex);
extern	void	SetCharacterFrame(SLONG lIndex, SLONG lFrame);
extern	SLONG	GetCharacterFrame(SLONG lIndex);
extern	void	SetCharacterDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetCharacterDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetCharacterDestID(SLONG lIndex, SLONG uID);
extern	SLONG	GetCharacterDestID(SLONG lIndex);
extern	void	SetCharacterOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetCharacterOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetCharacterOrigID(SLONG lIndex, ULONG uID);
extern	ULONG	GetCharacterOrigID(SLONG lIndex);
extern	void	SetCharacterStopRadius(SLONG lIndex, SLONG lRadius);
extern	SLONG	GetCharacterStopRadius(SLONG lIndex);
extern	void	SetCharacterDialogWithCount(SLONG lIndex, SLONG lCount);
extern	SLONG	GetCharacterDialogWithCount(SLONG lIndex);
extern	void	SetCharacterDialogDestIndex(SLONG lIndex, SLONG lDestIndex);
extern	SLONG	GetCharacterDialogDestIndex(SLONG lIndex);

extern	void	SetCharacterMoveSpeed(SLONG lIndex, SLONG lSpeed);
extern	SLONG	GetCharacterMoveSpeed(SLONG lIndex);
extern	void	SetCharacterShipSpeedX(SLONG lIndex, SLONG lSpeedX);
extern	SLONG	GetCharacterShipSpeedX(SLONG lIndex);
extern	void	SetCharacterShipSpeedY(SLONG lIndex, SLONG lSpeedY);
extern	SLONG	GetCharacterShipSpeedY(SLONG lIndex);
extern	void	SetCharacterShipSailSize(SLONG lIndex, SLONG lSize);
extern	SLONG	GetCharacterShipSailSize(SLONG lIndex);
extern	void	SetCharacterShipTurn(SLONG lIndex, SLONG lTurn);
extern	SLONG	GetCharacterShipTurn(SLONG lIndex);
extern	void	SetCharacterShipWeight(SLONG lIndex, SLONG lWeight);
extern	SLONG	GetCharacterShipWeight(SLONG lIndex);
extern	void	SetCharacterShipDegreeDir(SLONG lIndex, SLONG lDegreeDir);
extern	SLONG	GetCharacterShipDegreeDir(SLONG lIndex);
extern	void	SetCharacterShipOldDegreeDir(SLONG lIndex, SLONG lDegreeDir);
extern	SLONG	GetCharacterShipOldDegreeDir(SLONG lIndex);
//
extern	SLONG	IsCharacterOnFightState(SLONG lIndex);
extern	void	SetCharacterOnFightState(SLONG lIndex, SLONG lFlag);
extern  SLONG	IsCharacterOnBlockState(SLONG lIndex);
extern  void	SetCharacterOnBlockState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterBagOpened(SLONG lIndex);
extern	void	SetCharacterBagOpened(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnTheSea(SLONG lIndex);
extern	void	SetCharacterOnTheSea(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnDeadState(SLONG lIndex);
extern	void	SetCharacterOnDeadState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnDefenceState(SLONG lIndex);
extern	void	SetCharacterOnDefenceState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterDodge(SLONG lIndex);
extern	void	SetCharacterDodge(SLONG lIndex, SLONG lFlag);
extern	SLONG   IsCharacterOnBlock(SLONG lIndex);
extern	void    SetCharacterOnBlock(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterMagicRebound(SLONG lIndex);
extern	void    SetCharacterMagicRebound(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterShowSubtil(SLONG lIndex);
extern	void    SetCharacterShowSubtil(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterSpeedDelay1(SLONG lIndex);
extern	void    SetCharacterSpeedDelay1(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterSpeedDelay2(SLONG lIndex);
extern	void    SetCharacterSpeedDelay2(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterWithoutEqual(SLONG lIndex);
extern	void    SetCharacterWithoutEqual(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterBlackNpc(SLONG lIndex);
extern	void    SetCharacterBlackNpc(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterNpcFaint(SLONG lIndex);
extern	void    SetCharacterNpcFaint(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterNpcStandUp(SLONG lIndex);
extern	void    SetCharacterNpcStandUp(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterHeadSleep(SLONG lIndex);
extern	void    SetCharacterHeadSleep(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterOnSleep(SLONG lIndex);
extern	void    SetCharacterOnSleep(SLONG lIndex,SLONG lFlag);
extern	SLONG	IsCharacterOnPauseState(SLONG lIndex);
extern	void	SetCharacterOnPauseState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnSpecialItem(SLONG lIndex);
extern	void	SetCharacterOnSpecialItem(SLONG lIndex, SLONG lFlag);
//
extern	void	SetCharacterBitState(SLONG lIndex, ULONG uState);
extern	ULONG	GetCharacterBitState(SLONG lIndex);
extern	void	SetCharacterReliveTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterReliveTicks(SLONG lIndex);
extern	void	SetCharacterDeadState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterDeadState(SLONG lIndex);
extern	void	SetCharacterRightHandMagicState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterRightHandMagicState(SLONG lIndex);
extern	void	SetCharacterRightHandMagicTotalTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterRightHandMagicTotalTicks(SLONG lIndex);
extern	void	SetCharacterRightHandMagicCurrentTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterRightHandMagicCurrentTicks(SLONG lIndex);
extern	void	SetCharacterHeadSleepState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadSleepState(SLONG lIndex);
extern	void	SetCharacterHeadSleepTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterHeadSleepTicks(SLONG lIndex);
extern	void	SetCharacterHeadSleepLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadSleepLevel(SLONG lIndex);
extern	void	SetCharacterHeadPredictState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadPredictState(SLONG lIndex);
extern	void	SetCharacterHeadPredictLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadPredictLevel(SLONG lIndex);
extern	void	SetCharacterHeadDefenceState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadDefenceState(SLONG lIndex);
extern	void	SetCharacterHeadDefenceTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterHeadDefenceTicks(SLONG lIndex);
extern	void	SetCharacterHeadDefenceLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadDefenceLevel(SLONG lIndex);
extern	void	SetCharacterHeadMagicState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadMagicState(SLONG lIndex);
extern	void	SetCharacterHeadMagicTimes(SLONG lIndex, SHINT lTimes);
extern	SHINT	GetCharacterHeadMagicTimes(SLONG lIndex);
extern	void	SetCharacterHeadMagicLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadMagicLevel(SLONG lIndex);
extern	void	SetCharacterHeadBlindState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadBlindState(SLONG lIndex);
extern	void	SetCharacterHeadBlindTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterHeadBlindTicks(SLONG lIndex);
extern	void	SetCharacterHeadBlindLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadBlindLevel(SLONG lIndex);
extern	void	SetCharacterBodyDodgeState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterBodyDodgeState(SLONG lIndex);
extern	void	SetCharacterBodyVirusState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterBodyVirusState(SLONG lIndex);
extern	void	SetCharacterBodyVirusTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterBodyVirusTicks(SLONG lIndex);
extern	void	SetCharacterBodyVirusLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterBodyVirusLevel(SLONG lIndex);
extern	void	SetCharacterBodyHideState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterBodyHideState(SLONG lIndex);
extern	void	SetCharacterBodyHideTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterBodyHideTicks(SLONG lIndex);
extern	void	SetCharacterBodyHideLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterBodyHideLevel(SLONG lIndex);
extern	void	SetCharacterFootSpeedState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterFootSpeedState(SLONG lIndex);
extern	void	SetCharacterFootSpeedTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterFootSpeedTicks(SLONG lIndex);
extern	void	SetCharacterFootSpeedLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterFootSpeedLevel(SLONG lIndex);
//
extern	void	SetCharacterShipRotateState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipRotateState(SLONG lIndex);
extern	void	SetCharacterShipRotateTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipRotateTicks(SLONG lIndex);
extern	void	SetCharacterShipRotateLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipRotateLevel(SLONG lIndex);
extern	void	SetCharacterShipFireState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipFireState(SLONG lIndex);
extern	void	SetCharacterShipFireTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipFireTicks(SLONG lIndex);
extern	void	SetCharacterShipFireLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipFireLevel(SLONG lIndex);
extern	void	SetCharacterShipExplodeState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipExplodeState(SLONG lIndex);
extern	void	SetCharacterShipExplodeTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipExplodeTicks(SLONG lIndex);
extern	void	SetCharacterShipExplodeLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipExplodeLevel(SLONG lIndex);
extern	void	SetCharacterShipSailHurtState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipSailHurtState(SLONG lIndex);
extern	void	SetCharacterShipRudderHurtState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipRudderHurtState(SLONG lIndex);
// 
extern	void	SetCharacterShipPretendState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipPretendState(SLONG lIndex);
extern	void	SetCharacterShipPretendOldFileIndex(SLONG lIndex, SHINT lFileIndex);
extern	SHINT	GetCharacterShipPretendOldFileIndex(SLONG lIndex);
extern	void	SetCharacterShipPretendToFileIndex(SLONG lIndex, SHINT lFileIndex);
extern	SHINT	GetCharacterShipPretendToFileIndex(SLONG lIndex);
extern	void	SetCharacterShipHalfDownState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipHalfDownState(SLONG lIndex);
extern	void	SetCharacterShipOctopusState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipOctopusState(SLONG lIndex);
extern	void	SetCharacterShipOctopusTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipOctopusTicks(SLONG lIndex);
extern	void	SetCharacterShipOctopusLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipOctopusLevel(SLONG lIndex);
extern	void	SetCharacterAI(SLONG lIndex, ULONG uAI);
extern	ULONG	GetCharacterAI(SLONG lIndex);
extern  void	SetCharacterAIBlock(SLONG lIndex, ULONG uAIBlock);
extern  ULONG	GetCharacterAIBlock(SLONG lIndex);
extern	void	SetCharacterTotalOnlineTicks(SLONG lIndex, ULONG uTicks);
extern	ULONG	GetCharacterTotalOnlineTicks(SLONG lIndex);
//
extern	void	SetCharacterFinalStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterFinalStr(SLONG lIndex);
extern	void	SetCharacterInitStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterInitStr(SLONG lIndex);
extern	void	SetCharacterLevelUpStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterLevelUpStr(SLONG lIndex);
extern	void	SetCharacterPointStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterPointStr(SLONG lIndex);
//
extern	void	SetCharacterFinalIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterFinalIns(SLONG lIndex);
extern	void	SetCharacterInitIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterInitIns(SLONG lIndex);
extern	void	SetCharacterLevelUpIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterLevelUpIns(SLONG lIndex);
extern	void	SetCharacterPointIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterPointIns(SLONG lIndex);
//
extern	void	SetCharacterFinalWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterFinalWit(SLONG lIndex);
extern	void	SetCharacterInitWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterInitWit(SLONG lIndex);
extern	void	SetCharacterLevelUpWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterLevelUpWit(SLONG lIndex);
extern	void	SetCharacterPointWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterPointWit(SLONG lIndex);
//
extern	void	SetCharacterFinalLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterFinalLucky(SLONG lIndex);
extern	void	SetCharacterInitLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterInitLucky(SLONG lIndex);
extern	void	SetCharacterLevelUpLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterLevelUpLucky(SLONG lIndex);
extern	void	SetCharacterPointLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterPointLucky(SLONG lIndex);
//
extern	void	SetCharacterFinalAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalAtt(SLONG lIndex);
extern	void	SetCharacterFinalPhysicAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalPhysicAtt(SLONG lIndex);
extern	void	SetCharacterFinalMagicAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalMagicAtt(SLONG lIndex);
extern	void	SetCharacterFinalSpecAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalSpecAtt(SLONG lIndex);
extern	void	SetCharacterEquipBaseAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterEquipBaseAtt(SLONG lIndex);
extern	void	SetCharacterEquipAddedMagicAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterEquipAddedMagicAtt(SLONG lIndex);
extern	void	SetCharacterEquipAddedSpecAtt(SLONG lIndex, UHINT uAtt);
extern	SLONG	GetCharacterEquipAddedSpecAtt(SLONG lIndex);
extern	void	SetCharacterAttribAttRatio(SLONG lIndex, UHINT uRatio);
extern	UHINT	GetCharacterAttribAttRatio(SLONG lIndex);
extern	void	SetCharacterSkillAttackRatio(SLONG lIndex, UHINT uRatio);
extern	UHINT	GetCharacterSkillAttackRatio(SLONG lIndex);
extern	void	SetCharacterAttackRange(SLONG lIndex, UHINT uRange);
extern	UHINT	GetCharacterAttackRange(SLONG lIndex);
extern	void	SetCharacterAttackRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterAttackRate(SLONG lIndex);
extern	void	SetCharacterSightRange(SLONG lIndex, UHINT uRange);
extern	UHINT	GetCharacterSightRange(SLONG lIndex);
extern	void	SetCharacterFinalExplodeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterFinalExplodeRate(SLONG lIndex);
extern	void	SetCharacterEquipExplodeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterEquipExplodeRate(SLONG lIndex);
extern	void	SetCharacterSkillExplodeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterSkillExplodeRate(SLONG lIndex);
//
extern	void	SetCharacterFinalDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterFinalDefence(SLONG lIndex);
extern	void	SetCharacterBaseDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterBaseDefence(SLONG lIndex);
extern	void	SetCharacterEquipDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterEquipDefence(SLONG lIndex);
extern	void	SetCharacterSkillDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterSkillDefence(SLONG lIndex);
extern	void	SetCharacterSkillDefenceTicks(SLONG lIndex, UHINT uTicks);
extern	UHINT	GetCharacterSkillDefenceTicks(SLONG lIndex);
extern	void	SetCharacterEquipResistRatio(SLONG lIndex, UHINT uRatio);
extern	UHINT	GetCharacterEquipResistRatio(SLONG lIndex);
extern	void	SetCharacterFinalResist(SLONG lIndex, UHINT uResist);
extern	UHINT	GetCharacterFinalResist(SLONG lIndex);
extern	void	SetCharacterDodgeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterDodgeRate(SLONG lIndex);
extern	void	SetCharacterParryRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterParryRate(SLONG lIndex);
//
extern	void	SetCharacterPropertyPoint(SLONG lIndex, UHINT uPoint);
extern	UHINT	GetCharacterPropertyPoint(SLONG lIndex);
extern	void	AffectCharacterPropertyPoint(SLONG lIndex);
//
extern	void	SetCharacterExp(SLONG lIndex, ULONG uExp);
extern	ULONG	GetCharacterExp(SLONG lIndex);
extern	void	SetCharacterNextExp(SLONG lIndex, ULONG uExp);
extern	ULONG	GetCharacterNextExp(SLONG lIndex);
extern	void	SetCharacterLevel(SLONG lIndex, UHINT uLevel);
extern	UHINT	GetCharacterLevel(SLONG lIndex);
//
extern	void	SetCharacterHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterHp(SLONG lIndex);
extern	void	SetCharacterMaxHp(SLONG lIndex, UHINT uMaxHp);
extern	UHINT	GetCharacterMaxHp(SLONG lIndex);
extern	void	SetCharacterAttribHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterAttribHp(SLONG lIndex);
extern	void	SetCharacterLevelUpHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterLevelUpHp(SLONG lIndex);
extern	void	SetCharacterEquipHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterEquipHp(SLONG lIndex);
extern	void	SetCharacterSkillHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterSkillHp(SLONG lIndex);
extern	void	SetCharacterHpRes(SLONG lIndex, UHINT uRes);
extern	UHINT	GetCharacterHpRes(SLONG lIndex);
extern	void	SetCharacterMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterMp(SLONG lIndex);
extern	void	SetCharacterMaxMp(SLONG lIndex, UHINT uMaxMp);
extern	UHINT	GetCharacterMaxMp(SLONG lIndex);
extern	void	SetCharacterAttribMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterAttribMp(SLONG lIndex);
extern	void	SetCharacterLevelUpMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterLevelUpMp(SLONG lIndex);
extern	void	SetCharacterEquipMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterEquipMp(SLONG lIndex);
extern	void	SetCharacterSkillMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterSkillMp(SLONG lIndex);
extern	void	SetCharacterMpRes(SLONG lIndex, UHINT uRes);
extern	UHINT	GetCharacterMpRes(SLONG lIndex);
//
extern	void	SetCharacterSkillNo(SLONG lCharIndex, SLONG lSkillIndex, SLONG lSkillNo);
extern	SLONG	GetCharacterSkillNo(SLONG lCharIndex, SLONG lSkillIndex);
extern	void	SetCharacterSkillLevel(SLONG lCharIndex, SLONG lSkillIndex, UHINT uLevel);
extern	UHINT	GetCharacterSkillLevel(SLONG lCharIndex, SLONG lSkillIndex);
//  npc �ھ�skill_no �M npc_no  ���o������skill ������..�p�G..���|..��^ 0����
extern  SLONG   GetCharacterSpecialSkillLevel(SLONG lCharIndex, SLONG lSkillNo);
//
extern	void	SetCharacterEquipHead(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipHead(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipNeck(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipNeck(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipBody(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipBody(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipWaist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipWaist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipGlove(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipGlove(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipWeapon(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipWeapon(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipWrist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipWrist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipFeet(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipFeet(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipOtherA(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipOtherA(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipOtherB(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipOtherB(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipOtherC(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipOtherC(SLONG lIndex, TPOS_ITEM *lpItem);
//
extern	void	SetCharacterBagItem(SLONG lCharIndex, SLONG lBagIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterBagItem(SLONG lCharIndex, SLONG lBagIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterSashItem(SLONG lCharIndex, SLONG lSashIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterSashItem(SLONG lCharIndex, SLONG lSashIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterTransItem(SLONG lCharIndex, SLONG lTransIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterTransItem(SLONG lCharIndex, SLONG lTransIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterOnMouseItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterOnMouseItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterTreasureItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterTreasureItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterBodyMoney(SLONG lIndex, ULONG uMoney);
extern	ULONG	GetCharacterBodyMoney(SLONG lIndex);
//
extern	void	SetCharacterBankItem(SLONG lCharIndex, SLONG lItemIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterBankItem(SLONG lCharIndex, SLONG lItemIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterBankMoney(SLONG lIndex, ULONG uMoney);
extern	ULONG	GetCharacterBankMoney(SLONG lIndex);
//
extern	void	SetCharacterTeamMaxMembers(SLONG lCharIndex, SLONG lMaxMembers);
extern	SLONG	GetCharacterTeamMaxMembers(SLONG lCharIndex);
extern	void	SetCharacterTeamMemberFlag(SLONG lCharIndex, SLONG lMemberIndex, ULONG uFlag);
extern	ULONG	GetCharacterTeamMemberFlag(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberMainName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szMainName);
extern	CHAR*	GetCharacterTeamMemberMainName(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uHp);
extern	UHINT	GetCharacterTeamMemberHp(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberMaxHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uMaxHp);
extern	UHINT	GetCharacterTeamMemberMaxHp(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberLevel(SLONG lCharIndex, SLONG lMemberIndex, UHINT uLevel);
extern	UHINT	GetCharacterTeamMemberLevel(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberEyes(SLONG lCharIndex, SLONG lMemberIndex, SLONG lEyes);
extern	SLONG	GetCharacterTeamMemberEyes(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberMouth(SLONG lCharIndex, SLONG lMemberIndex, SLONG lMouth);
extern	SLONG	GetCharacterTeamMemberMouth(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberCareer(SLONG lCharIndex, SLONG lMemberIndex, SLONG lCareer);
extern	SLONG	GetCharacterTeamMemberCareer(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberSex(SLONG lCharIndex, SLONG lMemberIndex, SLONG lSex);
extern	SLONG	GetCharacterTeamMemberSex(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberZoneName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szZoneName);
extern	CHAR*	GetCharacterTeamMemberZoneName(SLONG lCharIndex, SLONG lMemberIndex);
//
extern	void	SetCharacterEnemyMaxMembers(SLONG lCharIndex, SLONG lMaxMembers);
extern	SLONG	GetCharacterEnemyMaxMembers(SLONG lCharIndex);
extern	void	SetCharacterEnemyMemberHitHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT lHp);
extern	UHINT	GetCharacterEnemyMemberHitHp(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterEnemyMemberMainName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szMainName);
extern	CHAR*	GetCharacterEnemyMemberMainName(SLONG lCharIndex, SLONG lMemberIndex);
//
extern	void	SetCharacterSex(SLONG lIndex, SLONG lSex);
extern	SLONG	GetCharacterSex(SLONG lIndex);
extern	void	SetCharacterCountry(SLONG lIndex, SLONG lCountry);
extern	SLONG	GetCharacterCountry(SLONG lIndex);
extern	void	SetCharacterGuildName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetCharacterGuildName(SLONG lIndex);
extern	void	SetCharacterSpouseName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetCharacterSpouseName(SLONG lIndex);
extern	void	SetCharacterCareer(SLONG lIndex, SLONG lCareer);
extern	SLONG	GetCharacterCareer(SLONG lIndex);
extern	void	SetCharacterCareerLevel(SLONG lIndex, SLONG lLevel);
extern	SLONG	GetCharacterCareerLevel(SLONG lIndex);
extern	void	SetCharacterOffice(SLONG lIndex, ULONG uOffice);
extern	ULONG	GetCharacterOffice(SLONG lIndex);
extern	void	SetCharacterNobilityName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetCharacterNobilityName(SLONG lIndex);
extern	void	SetCharacterGoodEvil(SLONG lIndex, SLONG lData);
extern	SLONG	GetCharacterGoodEvil(SLONG lIndex);
extern	void	SetCharacterPrestige(SLONG lIndex, SLONG lPres);
extern	SLONG	GetCharacterPrestige(SLONG lIndex);
extern	void	SetCharacterPkCount(SLONG lIndex, ULONG uCount);
extern	ULONG	GetCharacterPkCount(SLONG lIndex);
extern	void	SetCharacterPkedCount(SLONG lIndex, ULONG uCount);
extern	ULONG	GetCharacterPkedCount(SLONG lIndex);
extern	void	SetCharacterKind(SLONG lIndex, SLONG lKind);
extern	SLONG	GetCharacterKind(SLONG lIndex);
//
extern	void	SetCharacterLandLeftSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterLandLeftSkill(SLONG lIndex);
extern	void	SetCharacterLandRightSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterLandRightSkill(SLONG lIndex);
extern	void	SetCharacterLandFnSkillNo(SLONG lIndex, SLONG lFnIndex, SHINT lSkill);
extern	SHINT	GetCharacterLandFnSkillNo(SLONG lIndex, SLONG lFnIndex);
extern	void	SetCharacterLandFnSkillHand(SLONG lIndex, SLONG lFnIndex, SLONG lHand);
extern	SLONG	GetCharacterLandFnSkillHand(SLONG lIndex, SLONG lFnIndex);
//
extern	void	SetCharacterSeaLeftSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterSeaLeftSkill(SLONG lIndex);
extern	void	SetCharacterSeaRightSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterSeaRightSkill(SLONG lIndex);
extern	void	SetCharacterSeaFnSkillNo(SLONG lIndex, SLONG lFnIndex, SHINT lSkill);
extern	SHINT	GetCharacterSeaFnSkillNo(SLONG lIndex, SLONG lFnIndex);
extern	void	SetCharacterSeaFnSkillHand(SLONG lIndex, SLONG lFnIndex, SLONG lHand);
extern	SLONG	GetCharacterSeaFnSkillHand(SLONG lIndex, SLONG lFnIndex);
//
extern	void	SetCharacterDoingKind(SLONG lIndex, SLONG lKind);
extern	SLONG	GetCharacterDoingKind(SLONG lIndex);
extern	void	SetCharacterDoingStep(SLONG lIndex, SLONG lStep);
extern	SLONG	GetCharacterDoingStep(SLONG lIndex);
extern	void	SetCharacterDoingKindStep(SLONG lIndex, SLONG lDoingKind, SLONG lDoingStep);
extern	void	SetCharacterDoingMagic(SLONG lIndex, SHINT lMagic);
extern	SHINT	GetCharacterDoingMagic(SLONG lIndex);
extern	void	SetCharacterMagicTimes(SLONG lIndex, SHINT lTimes);
extern	SHINT	GetCharacterMagicTimes(SLONG lIndex);
extern	void	SetCharacterFightTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterFightTicks(SLONG lIndex);
extern	void	SetCharacterImageAction(SLONG lIndex, SLONG lAction);
extern	SLONG	GetCharacterImageAction(SLONG lIndex);
extern	void	SetCharacterImageID(SLONG lIndex, ULONG uID);
extern	ULONG	GetCharacterImageID(SLONG lIndex);
extern	void	SetCharacterIdleTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterIdleTicks(SLONG lIndex);
extern	void	SetCharacterSequentialStep(SLONG lIndex, SLONG lStep);
extern	SLONG	GetCharacterSequentialStep(SLONG lIndex);
extern	void	SetCharacterBeatedBy(SLONG lIndex, SLONG lBy);
extern	SLONG	GetCharacterBeatedBy(SLONG lIndex);
extern	void	SetCharacterBeatedWith(SLONG lIndex, SLONG lWith);
extern	SLONG	GetCharacterBeatedWith(SLONG lIndex);
extern	void	SetCharacterPantTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterPantTicks(SLONG lIndex);
extern	void	SetCharacterBeatedX(SLONG lIndex, SLONG lX);
extern	SLONG	GetCharacterBeatedX(SLONG lIndex);
extern	void	SetCharacterBeatedY(SLONG lIndex, SLONG lY);
extern	SLONG	GetCharacterBeatedY(SLONG lIndex);
extern	void	SetCharacterBeatedXY(SLONG lIndex, SLONG lX, SLONG lY);
extern	void	GetCharacterBeatedXY(SLONG lIndex, SLONG *lX, SLONG *lY);
extern	void	SetCharacterMuseTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterMuseTicks(SLONG lIndex);
extern	void	SetCharacterClashSteps(SLONG lIndex, SLONG lSteps);
extern	SLONG	GetCharacterClashSteps(SLONG lIndex);
extern	void	SetCharacterPatrolTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterPatrolTicks(SLONG lIndex);
extern	void	SetCharacterPatrolTotalTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterPatrolTotalTicks(SLONG lIndex);
extern	void	SetCharacterGadTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterGadTicks(SLONG lIndex);
extern	void	SetCharacterGadTotalTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterGadTotalTicks(SLONG lIndex);
extern	void	SetCharacterDeadTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterDeadTicks(SLONG lIndex);
extern	void	SetCharacterDeadAlpha(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterDeadAlpha(SLONG lIndex);
extern	void	SetCharacterAttackPantTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterAttackPantTicks(SLONG lIndex);
extern	void	SetCharacterAttackPantTotalTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterAttackPantTotalTicks(SLONG lIndex);

//
//
// Level 1 functions ------------------------------------------------
extern	void	SetCharacterLeftSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterLeftSkill(SLONG lIndex);
extern	void	SetCharacterRightSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterRightSkill(SLONG lIndex);
extern	void	SetCharacterFnSkill(SLONG lIndex, SLONG lFnIndex, SLONG lSkill, SLONG lHand);
extern	void	GetCharacterFnSkill(SLONG lIndex, SLONG lFnIndex, SLONG *lSkill, SLONG *lHand);
extern	SLONG	FindCharacterBagItemRoom(SLONG lIndex);
extern	SLONG	FindCharacterSashItemRoom(SLONG lIndex);
extern	SLONG	FindCharacterTransItemRoom(SLONG lIndex);
extern	SLONG	FindCharacterByMainName(CHAR *szMainName);
extern	SLONG   FindCharacterLandFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand);
extern	SLONG   FindCharacterSeaFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand);
extern	SLONG	FindCharacterFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand);
extern	SLONG	FindCharacterSkillIndex(SLONG lIndex, SLONG lSkillNo);
extern	SLONG	SetupCharacterHandQuickSkill(SLONG lIndex, SLONG lQuickIndex, SLONG lHand, SLONG lSkillNo);
//
extern	void    InitCharacterRightSkillState(SLONG lIndex);
extern	void    RefreshCharacterRightHandMagicState(SLONG lIndex);
extern	void    SetCharacterRightHandMagicStartSpower(SLONG lIndex);
extern	SLONG   IsCharacterRightHandMagicCanBreak(SLONG lIndex);

//  �Ǫ�..�Ψ��˴�..����npc�i�_����
extern  SLONG   IsCharacterCanAttackMonsterCheck(SLONG lIndex);
//----
//  �@�ǤH���欰���P�w���
//----
//�P�w�H���O�_���`
extern  SLONG   IsCharacterDead(SLONG lIndex);
//�P�_����ӤH�����O�_�O����
extern  SLONG   IsCharacterTeamMember(SLONG lNpcSc, SLONG lNpcTag);
//
//  npc�ۤv..�i�H�ۤv���_�ۤv���ʧ@
SLONG   IsCharacterSelfDoingKindBreak(SLONG lIndex);
//  npc�i�H�Q..�j�椤�_���ʧ@
SLONG   IsCharacterOtherDoingBreak(SLONG lIndex);
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

// Jack, quest related functions [5/8/2003]
//-------------------------------------------------------------------------
extern	void	SetQuestType(TPOS_QUEST_INFO *lpQI, SLONG lType);
extern	SLONG	GetQuestType(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestPublishZone(TPOS_QUEST_INFO *lpQI, CHAR* szZoneName);
extern	CHAR*	GetQuestPublishZone(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestPublishNpc(TPOS_QUEST_INFO *lpQI, CHAR* szNpcName);
extern	CHAR*	GetQuestPublishNpc(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestTargetZone(TPOS_QUEST_INFO *lpQI, CHAR *szZoneName);
extern	CHAR*	GetQuestTargetZone(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestTargetNpc(TPOS_QUEST_INFO *lpQI, CHAR *szNpcName);
extern	CHAR*	GetQuestTargetNpc(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestAcceptTime(TPOS_QUEST_INFO *lpQI, ULONG uTime);
extern	ULONG	GetQuestAcceptTime(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestDeadline(TPOS_QUEST_INFO *lpQI, ULONG uDeadline);
extern	ULONG	GetQuestDeadline(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestPay(TPOS_QUEST_INFO *lpQI, SLONG lPayType, ULONG uPayData);
extern	void	GetQuestPay(TPOS_QUEST_INFO *lpQI, SLONG *lPayType, ULONG *uPayData);
extern	void	SetQuestPunish(TPOS_QUEST_INFO *lpQI, SLONG lPunishType, ULONG uPunishData);
extern	void	GetQuestPunish(TPOS_QUEST_INFO *lpQI, SLONG *lPunishType, ULONG *uPunishData);
extern	void	SetQuestMemo(TPOS_QUEST_INFO *lpQI, CHAR *szMemo);
extern	CHAR*	GetQuestMemo(TPOS_QUEST_INFO *lpQI);
//
extern	void	SetCharacterQuestInfo(SLONG lCharIndex, SLONG lQuestIndex, TPOS_QUEST_INFO *lpInfo);
extern	void	GetCharacterQuestInfo(SLONG lCharIndex, SLONG lQuestIndex, TPOS_QUEST_INFO *lpInfo);
extern	SLONG	FindCharacterEmptyQuestIndex(SLONG lCharIndex);
