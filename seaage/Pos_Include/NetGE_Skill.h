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
#define MAX_GAME_SKILL_BASES            256         //�C�������ޯ�ƥ�
// mark by lijun 2003-04-21
//#define MAX_SKILL_LEVELS                200         //�ޯ�ɯŪ��̤j���ż�
#define MAX_SKILL_LEVELS                40           //�ޯ�ɯŪ��̤j���ż�
//

//------------
//�k�N�ݩʼлx
//------------
#define MAGIC_ATTRIB_LIST_VISIBLE       0x00000001  //�a�ϧޯ�C��W�|��ܥ��ޯ�
#define MAGIC_ATTRIB_UNDER_LIST         0x00000002  //��ܦb�a�ϧֱ��ϼЦC���̩��U
#define MAGIC_ATTRIB_FOR_LAND           0x00000010  //���a�W�ϥΪ��ޯ�
#define MAGIC_ATTRIB_FOR_SEA            0x00000020  //���v�W�ϥΪ��ޯ�
#define MAGIC_ATTRIB_PEACE              0x00000040  //�M���Ҧ��U�ϥΪ��ޯ�
#define MAGIC_ATTRIB_FIGHT              0x00000080  //�԰��Ҧ��U�ϥΪ��ޯ�
#define MAGIC_ATTRIB_LEFT_HAND          0x00000100  //�i�H�˳Ʀb����W
#define MAGIC_ATTRIB_RIGHT_HAND         0x00000200  //�i�H�˳Ʀb�k��W
//
#define MAGIC_ATTRIB_MAGIC_AREA_SELF    0x00001000  //�bNPC����m�W�X�{�]�k�}...�n�O�S���N�O�X�{�bmouse����m�W(�ݭn�W�O)
// mark by lijun 2003-04-21
//#define MAGIC_ATTRIB_PASSIVE            0x00001000  //���ޯ�O�Q�ʧ�(�Ƿ|��N�@�����@��)
//#define MAGIC_ATTRIB_NEED_PREPARE       0x00010000  //���ޯ�ݭn�e�m�ɶ�
//#define MAGIC_ATTRIB_NEED_SPOWER        0x00020000  //���ޯ�ݭn���W�O
//--------
//  �k�N�ϥΪ��ؼЩw�q
//--------
#define MAGIC_TAG_NORMAL_NPC            0x00000001  //���qnpc.
#define MAGIC_TAG_FRIEND_NPC            0x00000002  //�B��npc����
#define MAGIC_TAG_ENEMY_NPC             0x00000004  //�ĤHnpc
#define MAGIC_TAG_SELF                  0x00000008  //�ۤv
#define MAGIC_TAG_DEAD_NPC              0x00000010  //�ؼЭn�D�O���H(�S���Ӷ��N�O�ﬡ�H)
#define MAGIC_TAG_NEED_NPC              0x00000100  //�ؼлݭn(npc�ؼ�.���W��..���H�Ϊ̦��H)...���Ӽлx���..�b�S���ؼЪ��ɭԧޯ�L�k�ϥ�
#define MAGIC_TAG_POSITION              0x00000200  //�ؼФ��ݭn(npc),,�i�H��۪Ŧa�ϥ�
//--------
//�R���覡...�ޯ઺����覡
//--------
#define     MAGIC_HIT_TYPE_RANGE            0x00000001  //�d��R��
#define     MAGIC_HIT_TYPE_SINGLE_ALWAYS    0x00000002  //����..�����@�w�R��
#define     MAGIC_HIT_TYPE_SINGLE_MISS      0x00000004  //����..�����i��|MISS
//----
//  �ޯ઺��������
//----
#define     MAGIC_ATTACK_TYPE_PHYSICS       0   //���z��������
#define     MAGIC_ATTACK_TYPE_MAGIC         1   //�k�N��������
#define     MAGIC_ATTACK_TYPE_SPECIAL       2   //�S���������
//----
//�k�N�s���w�q
//----
//common magic no defines ---------------------------------------------------------
#define MAGIC_NO_JOIN_TEAM              0   //�ն�
#define MAGIC_NO_LEAVE_TEAM             1   //����
#define MAGIC_NO_TRADE                  2   //���
#define MAGIC_NO_FOLLOW                 3   //���H
#define MAGIC_NO_IDENTIFY               4   //ų�w
//
//land magic no defines -----------------------------------------------------------
#define MAGIC_NO_WALK                   20  //�樫
#define MAGIC_NO_MUSE                   21  //�߷Q
#define MAGIC_NO_ESCRIME                22	//�C�N
#define MAGIC_NO_SEQUENTIAL_ESCRIME     23  //�s��
#define MAGIC_NO_STRONG                 24	//�j��
#define MAGIC_NO_DEFENCE                25	//���
#define MAGIC_NO_CLASH                  26	//�ļ�
#define MAGIC_NO_PENETRABLE_ESCRIME     27	//�C��
#define MAGIC_NO_KNOCK_TO_DIZZY         28	//�V�w
#define MAGIC_NO_FATAL_ESCRIME          29  //�����C
//
#define MAGIC_NO_SHOOT                  30  //�g��
#define MAGIC_NO_SEQUENTIAL_SHOOT       31  //�s�g
#define MAGIC_NO_EYES_SHOOT             32  //������
#define MAGIC_NO_DODGE                  33	//���{
#define MAGIC_NO_PENETRABLE_SHOOT       34  //��z�u
#define MAGIC_NO_DOUBLE_SHOOT           35  //�����u��
#define MAGIC_NO_FEET_SHOOT             36	//���}
#define MAGIC_NO_DIFFUSE_SHOOT          37  //���g
//
#define MAGIC_NO_BOOK_READ              38  //Ū��
#define MAGIC_NO_CURE                   39  //�v��
#define MAGIC_NO_DEFEND_MIRROR          40  //���m��
#define MAGIC_NO_RELIVE                 41  //�_��
#define MAGIC_NO_BAPTISM                42  //�~§
#define MAGIC_NO_MAGIC_MIRROR           43  //�]�k��
#define MAGIC_NO_ENRICH_BLOOD           44  //�j�ɦ�
#define MAGIC_NO_INFINITE_KINDNESS      45  //�����E��
//
#define MAGIC_NO_DARK_STAR              46  //�t�P
#define MAGIC_NO_SLEEP                  47	//�ίv��
#define MAGIC_NO_TORTOISE               48  //�Q�t��
#define MAGIC_NO_RESIST                 49  //���
#define MAGIC_NO_DARK_BALL              50	//�t�y
#define MAGIC_NO_BEELINE_MAGIC          51  //���u�]�k
#define MAGIC_NO_AZRAEL                 52  //����
#define MAGIC_NO_DEVIL                  53  //�c�]
//
#define MAGIC_NO_THONG                  54  //���@
#define MAGIC_NO_CIRRUS_TRAP            55  //�ý�����
#define MAGIC_NO_BEAST_TRAP             56	//���~��
#define MAGIC_NO_ERUPTIVE_THONG         57  //���@�W�O
#define MAGIC_NO_RAVEL_TRAP             58  //�Ѱ�����
#define MAGIC_NO_PREDICT                59  //�w�P
#define MAGIC_NO_STONE_TRAP             60  //���۳���
#define MAGIC_NO_PRETEND                61  //����
#define MAGIC_NO_LANDMINE               62  //�a�p
//
#define MAGIC_NO_DAGGER                 63  //�P��
#define MAGIC_NO_BEHIND_DAGGER          64  //�I��
#define MAGIC_NO_STEAL                  65  //����
#define MAGIC_NO_UNLOCK                 66  //�}��
#define MAGIC_NO_HIDE                   67  //����
#define MAGIC_NO_POISON                 68  //�U�r
#define MAGIC_NO_GOLD                   69  //����
#define MAGIC_NO_NEGOTIATE              70  //�ͧP
#define MAGIC_NO_ATTRACT_MONSTER        71  //�l�ީǪ�
#define MAGIC_NO_BOX_TRAP               72  //�_�c����
#define MAGIC_NO_CONTROL_MONSTER        73  //�Ǫ�����
//
#define MAGIC_NO_CHOP                   74  //���
#define MAGIC_NO_TOXOPHILY              75  //�g�b
#define MAGIC_NO_RELIVE_2               76  //�_���G
#define MAGIC_NO_SUCK_BLOOD             77  //�l��
#define MAGIC_NO_SUCK_MAGIC             78  //�l�]
#define MAGIC_NO_DESTROY_ARMOR          79  //����}�a
#define MAGIC_NO_RELIVE_3               80  //�_���T
#define MAGIC_NO_HIDE_2                 81  //�����G
#define MAGIC_NO_FIRE_BALL              82  //���y
#define MAGIC_NO_EXPLODE                83  //���z�@
#define MAGIC_NO_EXPLODE_2              84  //���z�G
#define MAGIC_NO_BREAK_EQUIP            85  //���˳�
#define MAGIC_NO_RECALL                 86  //�l��
#define MAGIC_NO_CHANGE_FORM            87  //�ܨ�
#define MAGIC_NO_INSURANCE              88  //�O�I
#define MAGIC_NO_INSURANCE_2            89  //�O�I�G
#define MAGIC_NO_INSURANCE_3            90  //�O�I�T
#define MAGIC_NO_INSURANCE_4            91  //�O�I�|
#define MAGIC_NO_INSURANCE_5            92  //�O�I��
//
//sea magic no defines -----------------------------------------------------------
#define MAGIC_NO_SEAWALK                120 //���W������
#define MAGIC_NO_SEA_PRETEND            121 //���W����
#define MAGIC_NO_ARMOUR_PIERCING_BALL   122 //��Ҽu
#define MAGIC_NO_LINK_BALL              123 //��u
#define MAGIC_NO_BURNT_BALL             124 //�U�N�u
#define MAGIC_NO_EMANATORY_BALL         125 //���u
#define MAGIC_NO_REPAIR_BOAT            126 //�ײz


//---------------------------------------------
//�H���k�N��e���A
//----------------
#define MAGIC_STATE_OK              0       //�k�NOK,�i�H�ϥ�.
#define MAGIC_STATE_PREPARE         1       //�k�N�e�m�ɶ��i�椤
#define MAGIC_STATE_WAIT_SPOWER     2       //���ݻW�O��
#define MAGIC_STATE_SPOWER          3       //�k�N���b�W�O��
#define MAGIC_STATE_WAIT_BREAK      4       //�k�N��������

//
// STRUCTURES /////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct POS_SKILL_BS 
{
    //1.�ޯ઺���ݩ�
    CHAR    Name[32];			//�W��    
    SLONG   IconIndex;			//�ϼнs��    
    SLONG   MpConsume;          //�ϥθӧޯ઺mp����(��W�O�ɶ���0 ,)
    SLONG   MpConsumeTick;      //���֦��߸�
    SLONG   UseTag;             //�k�N�A�Ϊ��ؼ�(����0,�ĤH1)
    SLONG   Attrib;				//�ޯ઺�ݩ�
    SLONG   Kind;               //�ޯ�����(�Q�ʾ���0,��������1,����2)
    
    SLONG   Penetrate;          //��z(0,1)
    SLONG   HitType;            //�k�N�R������d��(�h�H0,���鲾�ʤ�1,����i��|MISS 2)
    //2.�Mnpc�ʧ@�������ޯ�ƾ�
    SLONG   ActionCount;        //npc�ʧ@�����񦸼�
    SLONG   ActionId;           //�ϥθӧޯ�ݭn�ϥΪ�npc�ʧ@���s��
    //3.�ޯ઺�ĪG�ƭ�  
    SLONG   AttackType;         //���઺�ˮ`����(���z 0,�k�N 1,�S�� 2)
    SLONG   AttackRatio;        //�������ܪ��ʤ��v

    SLONG   AttachMaxHp;        //���ܥͩR�W��
    SLONG   AttachMaxMp;        //���ܪk�O�W��
    SLONG   AttachNowHp;        //���ܷ�e���ͩR�W��
    SLONG   AttachNowMp;        //���ܷ�e���k�O�W��
    
    SLONG   AttackRatioChange;  //���ܧ����O���ʤ��Y��(�Ҧ������������O)
    SLONG   PhysicAttackReduceRatio;//���z�ˮ`��ֲv
    SLONG   PhysicDefence;      //���ܪ��z���m���ƭ�
    SLONG   MagicDefence;       //�����]�k���v
    SLONG   ExplodeRatio;       //���ܪ����z�����v
        
    SLONG   TagAction;          //�ؼлݭn���ܨ쪺�ʧ@
    SLONG   TagActionRatio;     //�ؼз|���ܨ�Ӱʧ@�����v
    //4.�k�N�����[�ĪG
    SLONG   SelfStatus;          //�ۤv�|���ܪ����A
    SLONG   SelfStatusRatio;     //�ۤv�|���ܨ�Ӫ��A�����v
    
    SLONG   TagStatus;           //�ؼз|���ܪ����A
    SLONG   TagStatusRatio;      //�ؼз|���ܨ�Ӫ��A�����v

    SLONG   Dispel;               //�������}���A��O
    SLONG   Resurgent;            //�_��

    //5.�k�N�M�d��������ƭ�
    SLONG   MagicDisChargeDistance; //�k�N����Z��....�I�k�̻ݭn�Z������ؼЦh�֫�~��..����k�N
    SLONG   MagicBrokenDistance;    //�k�N�R�����P�w�Z��...�N�O�k�N�Mnpc���Z���t�h�ֺ�R��
    SLONG   MagicHitDistance;       //�k�N�R����ƭȵ���Z��
    SLONG   MagicFlyDistance;       //�k�N���檺�Z��
    SLONG   MagicEffRange;          //���n�k�N���@�νd��(���]�k�}�A��)
    //6.�M�k�N�I��������ɶ��ƭ�
    SLONG   SpowerTick;             //�W�O�ɶ�
    SLONG   DamageTick;             //���ɴ�(�h���ˮ`�����j�ɶ�,)
    SLONG   DeleyTick;              //�ޯ઺����ɶ�
    SLONG   PantTick;               //�I�k������ݭn���ݮ��ɶ�
    //7.�M�k�N�ե�������ƭ�
    SLONG   HeightLeve;             //�k�N�ե󪺰���(�a��k�N0 ,���h1,���h2)
    //
    SLONG   SelfBreakId;            //�q�ۤv���W���X���k�N�ĪG���s��
    SLONG   TagBreakId;             //�b�ؼ��I���}���k�N�ĪG���s��
    SLONG   EffBreakId;             //�R���᪺�k�N�ĪG���s��
    //8.�]�k�}�������ƾ�
    SLONG   MagicId;                //�]�k�}..�ϥΪ�����
    //
} TPOS_SKILL_BS, *LPTPOS_SKILL_BS;
//
// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern  TPOS_SKILL_BS   GameSkillBase[MAX_GAME_SKILL_BASES][MAX_SKILL_LEVELS];  //[�ޯ઺�s��][�ޯ઺����]

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
//�W��    
CHAR*	GetSkillName(SLONG lSkillNo);
//�ϼнs��
SLONG   GetSkillIconIndex(SLONG lSkillNo);
//�ϥθӧޯ઺mp����(��W�O�ɶ���0 ,)
SLONG   GetSkillMpConsume(SLONG lSkillNo, SLONG lLevel);
//���֦��߸�
SLONG   GetSkillMpConsumeTick(SLONG lSkillNo, SLONG lLevel);
//�k�N�A�Ϊ��ؼ�(����0,�ĤH1)
SLONG   GetSkillUseTag(SLONG lSkillNo, SLONG lLevel);
//�ޯ઺�ݩ�
SLONG   GetSkillAttrib(SLONG lSkillNo, SLONG lLevel);
//�ޯ�����(�Q�ʾ���0,��������1,����2)
SLONG   GetSkillKind(SLONG lSkillNo, SLONG lLevel);
//��z(0,1)
SLONG   GetSkillPenetrate(SLONG lSkillNo, SLONG lLevel);
//�k�N�R������d��(����0,�h�H1)
SLONG   GetSkillHitType(SLONG lSkillNo, SLONG lLevel);
//2.�Mnpc�ʧ@�������ޯ�ƾ�
//npc�ʧ@�����񦸼�
SLONG   GetSkillActionCount(SLONG lSkillNo, SLONG lLevel);
//�ϥθӧޯ�ݭn�ϥΪ�npc�ʧ@���s��
SLONG   GetSkillActionId(SLONG lSkillNo, SLONG lLevel);
//3.�ޯ઺�ĪG�ƭ�  
//���઺�ˮ`����(���z 0,�k�N 1,�S�� 2)
SLONG   GetSkillAttackType(SLONG lSkillNo, SLONG lLevel);
//�������ܪ��ʤ��v
SLONG   GetSkillAttackRatio(SLONG lSkillNo, SLONG lLevel);

//���ܥͩR�W��
SLONG   GetSkillAttachMaxHp(SLONG lSkillNo, SLONG lLevel);
//���ܪk�O�W��
SLONG   GetSkillAttachMaxMp(SLONG lSkillNo, SLONG lLevel);
//���ܷ�e���ͩR�W��
SLONG   GetSkillAttachNowHp(SLONG lSkillNo, SLONG lLevel);
//���ܷ�e���k�O�W��
SLONG   GetSkillAttachNowMp(SLONG lSkillNo, SLONG lLevel);
//���ܧ����O���ʤ��Y��(�Ҧ������������O)
SLONG   GetSkillAttackRatioChange(SLONG lSkillNo, SLONG lLevel);
//���z�ˮ`��ֲv
SLONG   GetSkillPhysicAttackReduceRatio(SLONG lSkillNo, SLONG lLevel);
//���ܪ��z���m���ƭ�
SLONG   GetSkillPhysicDefence(SLONG lSkillNo, SLONG lLevel);
//�����]�k���v
SLONG   GetSkillMagicDefence(SLONG lSkillNo, SLONG lLevel);
//���ܪ����z�����v
SLONG   GetSkillExplodeRatio(SLONG lSkillNo, SLONG lLevel);
//�ؼлݭn���ܨ쪺�ʧ@
SLONG   GetSkillTagAction(SLONG lSkillNo, SLONG lLevel);
//�ؼз|���ܨ�Ӱʧ@�����v
SLONG   GetSkillTagActionRatio(SLONG lSkillNo, SLONG lLevel);
//4.�k�N�����[�ĪG
//�ۤv�|���ܪ����A
SLONG   GetSkillSelfStatus(SLONG lSkillNo, SLONG lLevel);
    
//�ۤv�|���ܨ�Ӫ��A�����v
SLONG   GetSkillSelfStateRatio(SLONG lSkillNo, SLONG lLevel);
    
//�ؼз|���ܪ����A
SLONG   GetSkillTagStatus(SLONG lSkillNo, SLONG lLevel);
//�ؼз|���ܨ�Ӫ��A�����v
SLONG   GetSkillTagStatusRatio(SLONG lSkillNo, SLONG lLevel);
//�������}���A��O
SLONG   GetSkillDispel(SLONG lSkillNo, SLONG lLevel);
//�_��
SLONG   GetSkillResurgent(SLONG lSkillNo, SLONG lLevel);
//5.�k�N�M�d��������ƭ�
//�k�N����Z��....�I�k�̻ݭn�Z������ؼЦh�֫�~��..����k�N
SLONG   GetSkillMagicDisChargeDistance(SLONG lSkillNo, SLONG lLevel);
//�k�N�R�����P�w�Z��...�N�O�k�N�Mnpc���Z���t�h�ֺ�R��
SLONG   GetSkillMagicBrokenDistance(SLONG lSkillNo, SLONG lLevel);
//�k�N�R����ƭȵ���Z��
SLONG   GetSkillMagicHitDistance(SLONG lSkillNo, SLONG lLevel);
//�k�N���檺�Z��
SLONG   GetSkillMagicFlyDistance(SLONG lSkillNo, SLONG lLevel);
//���n�k�N���@�νd��(���]�k�}�A��)
SLONG   GetSkillMagicEffRange(SLONG lSkillNo, SLONG lLevel);
//6.�M�k�N�I��������ɶ��ƭ�
SLONG   GetSkillSpowerTick(SLONG lSkillNo, SLONG lLevel);
//���ɴ�(�h���ˮ`�����j�ɶ�,)
SLONG   GetSkillDamageTick(SLONG lSkillNo, SLONG lLevel);
//�ޯ઺����ɶ�
SLONG   GetSkillDeleyTick(SLONG lSkillNo, SLONG lLevel);
//�I�k������ݭn���ݮ��ɶ�
SLONG   GetSkillPantTick(SLONG lSkillNo, SLONG lLevel);
//7.�M�k�N�ե�������ƭ�
//�k�N�ե󪺰���(�a��k�N0 ,���h1,���h2)
SLONG   GetSkillHeightLeve(SLONG lSkillNo, SLONG lLevel);
//�k�N�ĪG�s��.
SLONG   GetSkillSelfBreakId(SLONG lSkillNo, SLONG lLevel);
SLONG   GetSkillTagBreakId(SLONG lSkillNo, SLONG lLevel);
SLONG   GetSkillEffBreakId(SLONG lSkillNo, SLONG lLevel);
//�]�k�}�������ƾ�
SLONG   GetSkillMagicId(SLONG lSkillNo, SLONG lLevel);
//���o�ޯ��ݩʪ��P�w���
//�ӧޯ�i�_�˳Ʀb����
SLONG   IsLeftHandSkill(SLONG lSkillNo, SLONG lLevel);
//�ӧޯ�i�_�˳Ʀb�k��
SLONG   IsRightHandSkill(SLONG lSkillNo, SLONG lLevel);
//�ӧޯ�O�_�I���ԧޯ�
SLONG   IsLandSkill(SLONG lSkillNo, SLONG lLevel);
//�ӧޯ�O�_�O���v�ޯ�
SLONG   IsSeaSkill(SLONG lSkillNo, SLONG lLevel);
//�ӧޯ� �b�a�ϧޯ�C��W�|��ܥ��ޯ�
SLONG   IsListVisibleSkill(SLONG lSkillNo, SLONG lLevel);
//�P�_�O�_�O�q�� �ޯ�.. �b���v..�M���a���i�H�ϥ�
SLONG   IsCommonSkill(SLONG lSkillNo, SLONG lLevel);
//��ܦb�a�ϧֱ��ϼЦC���̩��U
SLONG   IsUnderListSkill(SLONG lSkillNo, SLONG lLevel);
//�M���Ҧ��U�ϥΪ��ޯ�
SLONG   IsPeaceSkill(SLONG lSkillNo, SLONG lLevel);
//�԰��Ҧ��U�ϥΪ��ޯ�
SLONG   IsFightSkill(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ�O�_�ݭn�W�O�q
SLONG   IsSkillNeedSpower(SLONG lSkillNo, SLONG lLevel);
//�P�_�ϥΪ��]�k�}������
SLONG   IsSkillNeedSelfMagicArea(SLONG lSkillNo, SLONG lLevel);
//
SLONG   IsSkillNeedTagNpc(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ�O�_�i�H��۪Ŧa�ϥ�
SLONG   IsSkillUsePosition(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ઺�ؼЬO�_�O���qnpc
SLONG   IsSkillUseTagNormalNpc(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ઺�ؼЬO�B��..����
SLONG   IsSkillUseTagFriend(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ઺�ؼЬO�ĤH
SLONG   IsSkillUseTagEnemy(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ઺�ؼЬO�ۤv
SLONG   IsSkillUseTagSelf(SLONG lSkillNo, SLONG lLevel);
//�P�_�ӧޯ઺�ϥΥؼЬO���H
SLONG   IsSkillUseTagDeadNpc(SLONG lSkillNo, SLONG lLevel);
//�P�_�b���Ъ�������U���ɭԲ��ӧޯ�i�_�ϥ�
SLONG   IsSkillMouseDownCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc);
//�P�_�b���Ъ���}���ɭԲ��ӧޯ�i�_�ϥ�...�D�n���O..�ݭn�W�O���ޯ�;
SLONG   IsSkillMouseUpCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc);
//�ɹ��Ъ�������U���ɭԧP�w..�ݭn���ӧޯ�ݭn���ܨ쪺doingkind 
SLONG   GetSkillMosueDownDoingKind(SLONG lSkillNo, SLONG lLevel);

//mark by lijun 2003-04-21
/*
typedef	struct POS_SKILL_BS 
{
    CHAR    Name[32];			//�W��
    SLONG   Attrib;				//�ݩ�
    SLONG   IconIndex;			//�ϼнs��

    SLONG   PrepareTicks;		//�e�m�ɶ�
    SLONG   SpowerTicks;		//�W�O�ɶ�
    SLONG   DelayTicks;			//���ɴ�(�h���ˮ`�����j�ɶ�)
	SLONG	PersistTicks;		//�\�����ɶ�
	SLONG	PantTicks;			//�I�k������ݭn���ݮ��ɶ�

	SLONG	DoTimes;			//�k�N�ʧ@����
	SLONG	NeedMp;				//�ݭn�k�O��
	SLONG	Abnormity;			//���`���A
	SLONG	Relation;			//�A�Υؼ�

	SLONG	ExplodeRange;		//�z�����᪺ͫ���ħ����d��
    SLONG   ExplodeDistance;    //�z�����ͮɻݭn�k�N�ե󱵪�ؼЪ��Z��
    SLONG   TargetDistance;     //�I�k�̦b�i��I�k�ʧ@�ɻݭn����ؼЪ��Z��

	SLONG	SpecialID;			//���� NPC ���S��v�����ID

	SLONG	HitType;			//�R���覡
	SLONG	PhysicAttackRatio;	//�v�T���z�����O(%)
	SLONG	MagicAttackRatio;	//�v�T�k�N�����O(%)
	SLONG	SpecialAttackRatio;	//�v�T�S������O(%)
	SLONG	AttachDefenceData;	//���[���m�O�ƭ�
	SLONG	AttachDefenceTicks;	//���[���m�O�ɶ�
	SLONG	DodgeRate;			//���ײv(%)
	SLONG	ExplodeRate;		//���z�v(%)
	SLONG	ChangeRate;			//�ܶ¤H,�ܯQ�t,�ܽު����v
	SLONG	LevelQuotiety;		//���P���żv�T�����O(%)���Y��, ��ڼv�T(%) = 1 + Level * LevelQuotiety.
	SLONG	AttackQuotiety;		//�v�T�`������O���Y��
	SLONG	AttachMaxHp;		//���[�ͩR�W��
	SLONG	AttachMaxMp;		//���[���O�W��

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
