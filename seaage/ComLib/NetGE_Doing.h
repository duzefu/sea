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
#define MAX_NPC_STEP_COUNT          2   //�H�����ʮɨC�V���Ʀ���

//����V�Ʊ�����
#define NPC_KEY_FRAME_NONE          0   //�D����V
#define NPC_KEY_FRAME_HEAD          1   //����V(�Ĥ@�V)
#define NPC_KEY_FRAME_HALF          2   //�����V
#define NPC_KEY_FRAME_TAIL          3   //�̫�V
#define NPC_KEY_FRAME_BACK          4   //���۴V
//NPC�ʵeID�O�_���ܪ��лx
#define NPC_ID_CHANGE_NONE          0   //�Ϲ�id�S������
#define NPC_ID_CHANGE_YES           1   //�Ϲ�id�o�ͤF����
//�����ʪ��w�q
#define NPC_MOVE_MOVEING            0   //npc���ʦb���ʹL�{��
#define NPC_MOVE_ARRIVE             1   //npc���ʨ�F�F�ؼ�
#define NPC_MOVE_CANT_ARRIVE        2   //npc���ʤ����F
//����npc�v�k�ʧ@���w�q
#define NPC_MAGIC_DOING             0   //�b�I�k�L�{��
#define NPC_MAGIC_START             1   //�}�l�I�k
#define NPC_MAGIC_FIRE              2   //��F�����V
#define NPC_MAGIC_OVER              3   //�I�k�ʧ@����
//-----------------------------------------------------------
//�H�����b�i�檺�ư�����(NPC DOING KINDS), �ھڪ��a���ާ@�w�q
//
//   �`�N��...!!!!!
//          �b�W�[�@��DOING_KIND �@�w�n�b  
//                  �Ȥ��   
//                          npc.cpp    set_npc_doing  �W�[�N��
//                  �A�Ⱦ���
//                          ServerCharacterDoing.cpp SetCharacterDoing �W�[�N��
//-----------------------------------------------------------
//�L����ާ@�ɡA���d�b��a��
#define DOING_KIND_IDLE                         0   //���H��a����(idle)
#define DOING_KIND_MUSE                         1   //�߷Q
#define DOING_KIND_SPOWER                       2   //�W�O��
#define DOING_KIND_CHANGEMAP                    3   //�����a�Ϥ�
#define	DOING_KIND_STAND						5	//��a����(���ܤ�V)
#define DOING_KIND_UPGRADE                      6   //�ɯ�...(npc���Ŵ��@)
//
//�I���a�ϤW���ťհϰ�A�a�ϤW����
#define DOING_KIND_MOVE_TO                      10  //�樫��ؼ��I(trend)(moveto)

#define DOING_KIND_CLASH                        12  //�ļ���ؼ��I
// mark by lijun 2003-05-21
/*
#define	DOING_KIND_FIGHT_IDLE					4	//�԰��ݾ�
#define DOING_KIND_MAGIC_POSITION               11  //��ؼ��I�I�k
#define DOING_KIND_GAD                          13  //�a�ϤW�H���樫
#define DOING_KIND_PATROL                       14  //�a�ϤW���I��������
#define	DOING_KIND_FIGHT_GAD					15	//�԰��H���樫
#define	DOING_KIND_FIGHT_PATROL					16	//�԰��a�ϤW���I��������
#define DOING_KIND_ATTACK_NPC                   31  //��H������
#define DOING_KIND_MAGIC_NPC                    32  //��H���I�k
*/

//NPC���԰������欰���q
#define DOING_KIND_SKILL_ACTION                 17  //�q�Ϊ�..�b�԰���������ӧޯ઺�ʧ@...�S���S�O�h�g..�԰��ޯ઺�ʧ@���O�ϥγo��
//
//�I���a�ϤW�����~
#define DOING_KIND_PICK_ITEM                    20  //�B���a�W���~(pick item)
//
//�I���a�ϤW�� NPC
#define DOING_KIND_TALK_WITH_NPC                30  //�P�H�����(talk)
#define DOING_KIND_SEQUENTIAL_ATTACK_NPC        33  //��H���i��s�����
//
//�Q�ʵo��
#define DOING_KIND_BEATED                       40  //�H���Q��
#define DOING_KIND_DEAD                         41  //�H�����`
#define DOING_KIND_DOWN_AND_OUT                 42  //�H���Q����
#define DOING_KIND_DEFENCE                      43  //�H�����
#define DOING_KIND_DEFENCED                     44  //�H���Q���
//
//�H�����ʧ@
//#define DOING_KIND_CHEER                        50  //�w�I
#define DOING_KIND_ANGRY                        51  //�ͮ�
#define DOING_KIND_BECKON                       52  //�ۤ�
//#define DOING_KIND_COURT                        53  //�D�R
#define DOING_KIND_FAINT                        54  //�w��
#define DOING_KIND_SAY_NO                       55  //����
#define DOING_KIND_BOW                          56  //���`
#define DOING_KIND_WIN                          57  //�ӧQ
#define DOING_KIND_SWASH                        58  //�~��
#define DOING_KIND_XXPOWER                      59  //���˻W�O
#define DOING_KIND_XXBEATED                     60  //���˳Q��
//
#define CHARACTER_DOING_MAX_LAND                64  //���anpc�̦h��(AI)�欰�ƥ�
#define MAX_CHARACTER_DOING_KINDS               128 //NPC�ư��������`��
//
#define DOING_KIND_SEA_ACC_MOVE_TO              (CHARACTER_DOING_MAX_LAND+0)  //���Wnpc���L�[�t�ׯ��
#define DOING_KIND_SEA_IDLE                     (CHARACTER_DOING_MAX_LAND+2)  //���Wnpc���A��a���ݾ�
#define DOING_KIND_SEA_SAIL_TO                  (CHARACTER_DOING_MAX_LAND+3)  //���W�����
#define DOING_KIND_SEA_WALK_TO                  (CHARACTER_DOING_MAX_LAND+4)  //���Wnpc���樫��


//--------------------
//�H���ʧ@(NPC ACTION)
//--------------------
#define     CHARACTER_ACTION_BLOCK_NORMAL       0   //���q�ʧ@��
#define     CHARACTER_ACTION_BLOCK_FIGHT        1   //�԰��ʧ@��
#define     CHARACTER_ACTION_BLOCK_WARD         2   //��װʧ@��
//���aNPC���欰
#define AC_WAIT_0       0   //�ݾ�0
#define AC_WAIT_1       1   //�ݾ�1
#define AC_RUN          2   //�b�]
#define AC_BEATED       3   //�Q��
#define AC_WARD         4   //���
#define AC_FAINT        5   //���`�˦a, �w��
#define AC_ATTACK_0     6   //����0
#define AC_ATTACK_1     7   //����1	
#define AC_CLIMB        8   //���_	
#define AC_WIN          9   //�ӧQ	
#define AC_ANGRY        10  //�ͮ�	
#define AC_BECKON       11  //�ۤ�	
#define AC_BOW          12  //��§	
#define AC_SAY_NO       13  //����	
#define AC_SPOWER       14  //�W�O	
#define AC_MAGIC        15  //�I�k	
#define AC_FCHANGE      16  //�԰�����
#define AC_SPECIAL_0    17  //�S��0
#define AC_SPECIAL_1    18  //�S��1	
#define AC_SPECIAL_2    19  //�S��2	
#define AC_SPECIAL_3    20  //�S��3	
#define AC_SPECIAL_4    21  //�S��4	
#define AC_SPECIAL_5    22  //�S��5	
#define AC_SPECIAL_6    23  //�S��6
//���vNPC���欰
#define AC_SEA_WALK                 0	//���W�樫
#define AC_SEA_IDLE                 1   //���W�ݾ�

//-----------------
//�H����V(NPC DIR)
//-----------------
#define NPC_DIRS                    8    //�H���@����V��

//�����ˤ��e����V�w�q�A�ФŧR���I
/*
#define NPC_UP                      0    //�W
#define NPC_DOWN                    1    //�U
#define NPC_LEFT                    2    //��
#define NPC_RIGHT                   3    //�k
#define NPC_RIGHT_UP                4    //�k�W
#define NPC_LEFT_DOWN               5    //���U
#define NPC_LEFT_UP                 6    //���W
#define NPC_RIGHT_DOWN              7    //�k�U
*/
//���˫᪺���a�H����V�w�q
#define NPC_UP                      0    //�W
#define NPC_RIGHT_UP                1    //�k�W
#define NPC_RIGHT                   2    //�k
#define NPC_RIGHT_DOWN              3    //�k�U
#define NPC_DOWN                    4    //�U
#define NPC_LEFT_DOWN               5    //���U
#define NPC_LEFT                    6    //��
#define NPC_LEFT_UP                 7    //���W
//
//���˫᪺���V�w�q(�P���˫e��NPC�ۦP)
#define SEANPC_UP                   0    //�W
#define SEANPC_DOWN                 1    //�U
#define SEANPC_LEFT                 2    //��
#define SEANPC_RIGHT                3    //�k
#define SEANPC_RIGHT_UP             4    //�k�W
#define SEANPC_LEFT_DOWN            5    //���U
#define SEANPC_LEFT_UP              6    //���W
#define SEANPC_RIGHT_DOWN           7    //�k�U

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

