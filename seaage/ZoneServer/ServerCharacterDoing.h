/*
**	ServerCharacterDoing.h
**	server character doing functions.
**
**	Jack, 2002/10/30.
*/
#ifndef _SERVERCHARACTERDOING_H_
#define _SERVERCHARACTERDOING_H_


//--------------------------------------------------------------------------------------
//NPC�����A(STATE)
//------------------------------
#define NPC_STATE_FIGHT             0x00000001  //NPC�B��԰����A�U
#define NPC_STATE_DEFENCE           0x00000002  //NPC�B���ת��A(���ʳt�״�b)
#define NPC_STATE_SHADOW_MOVE       0x00000004  //�a�ݼv����
#define NPC_STATE_INVINCIBLE        0x00000010  //�L��(���|�Q����ۦ�����)
#define NPC_STATE_RESIST            0x00000020  //�W�[���
#define NPC_STATE_ADD_MAX_HP        0x00000040  //�W�[HP�W��
#define NPC_STATE_POWER_ATTACK      0x00000080  //�����W�j(�P�ɷ|�W�[���z)
#define NPC_STATE_ANTI_HIDE         0x00000100  //������
#define NPC_STATE_ANTI_POSE         0x00000200  //�ϰ���
//


//--------------------------------------------------------------------------------------
//NPC�����`���A
//------------------------------
//�Y��
#define NPC_HEAD_SLEEP_STATE_NORMAL         0   //���`
#define NPC_HEAD_SLEEP_STATE_SWIRL          1   //�Y�w
#define NPC_HEAD_SLEEP_STATE_SLEEP          2   //�ίv
//
#define NPC_HEAD_PREDICT_STATE_NORMAL       0   //���`
#define NPC_HEAD_PREDICT_STATE_PREDICT      1   //�w��(������, �ϰ���, �ϳ���)
//
#define NPC_HEAD_DEFENCE_STATE_NORMAL       0   //���`
#define NPC_HEAD_DEFENCE_STATE_DEFENCE      1   //���m�[�j
//
#define NPC_HEAD_MAGIC_STATE_NORMAL         0   //���`
#define NPC_HEAD_MAGIC_STATE_REBOUND        1   //�]�k�ϼu
//
#define NPC_HEAD_BLIND_STATE_NORMAL         0   //���`
#define NPC_HEAD_BLIND_STATE_BLIND          1   //����
//
#define NPC_HEAD_ATTRACT_STATE_NORMAL       0   //���`
#define NPC_HEAD_ATTRACT_STATE_FASCINATE    1   //�y�b
#define NPC_HEAD_ATTRACT_STATE_ATTRACT      2   //�l��
//
//����
#define NPC_BODY_DODGE_STATE_NORMAL         0   //���`
#define NPC_BODY_DODGE_STATE_DODGE          1   //���{
//
#define NPC_BODY_VIRUS_STATE_NORMAL         0   //���`
#define NPC_BODY_VIRUS_STATE_VIRUS          1   //���r
//
#define NPC_BODY_HIDE_STATE_NORMAL          0   //���`
#define NPC_BODY_HIDE_STATE_SUCKED          1   //�Q�l��
#define NPC_BODY_HIDE_STATE_HIDE            2   //����
//
//�}�U
#define NPC_FOOT_SPEED_STATE_NORMAL         0   //���`
#define NPC_FOOT_SPEED_STATE_TARDY          1   //��w1,�樫�t�פU��,���V�B�z(�ʧ@�W�v��),�K�ʵe.
#define NPC_FOOT_SPEED_STATE_TIRED          2   //��w2,�樫�t�פU��,��V�B�z(�ʧ@�W�v�C),���K�ʵe(�Q���}�Ϊ̦b�c�]�ϰ줺).
//
//���`�ά���
#define NPC_LIVE                            0   //���۩έ���
#define NPC_DEAD                            1	//���`
#define NPC_DISAPPEAR						2   //���`���� 


//--------------------------------------------------------------------------------------
//NPC��AI
//------------------------------
// Jack, todo [11:01,10/10/2002]
//NPC AI KIND(�Ǫ�NPC �H�u���઺����) ------------------------------------------------------
#define AI_KIND_MASK_MOVE_TYPE          0x0000000f  //���ʤ覡AI
#define AI_KIND_MASK_WHEN_MOVE          0x000000f0  //���ʮɪ��԰�AI
#define AI_KIND_MASK_AFTER_ATTACK       0x00000f00  //���z�����Ĥ�᪺AI
#define AI_KIND_MASK_AFTER_MAGIC        0x0000f000  //�k�N�����Ĥ�᪺AI
#define AI_KIND_MASK_AFTER_BEATED       0x000f0000  //�Q�����᪺AI
#define AI_KIND_MASK_AFTER_DODGE        0x00f00000  //���ק��᪺AI
//#define	AI_KIND_MASK_AFTER_DEFENCE		0x0f000000	//���ɫ᪺AI
//#define	AI_KIND_MASK_AFTER_DEFENCED		0xf0000000	//�Q���ɫ᪺AI
//
#define AI_KIND_IDLE_MOVE_TYPE          0x00000001  //��a����
#define AI_KIND_GAD_MOVE_TYPE           0x00000002  //�H������
#define	AI_KIND_TREND_MOVE_TYPE			0x00000003	//�ͦV�X���I������
#define	AI_KIND_PATROL_MOVE_TYPE		0x00000004	//����
//
#define AI_KIND_NONE_WHEN_MOVE          0x00000010  //���ʮɸI��ĤH�S������(�|�~��ۤv������)
#define AI_KIND_ATTACK_WHEN_MOVE        0x00000020  //���ʮɸI��ĤH�樫���z����
#define AI_KIND_MAGIC_WHEN_MOVE         0x00000030  //���ʮɸI��ĤH�k�N����
#define AI_KIND_MIXED_WHEN_MOVE         0x00000040  //���ʮɸI��ĤH�V�X����(���z�����Ϊ̪k�N����)
#define AI_KIND_DODGE_WHEN_MOVE         0x00000050  //���ʮɸI��ĤH����
#define AI_KIND_RUN_ATTACK_WHEN_MOVE    0x00000060  //���ʮɸI��ĤH�]�B���z����
#define	AI_KIND_TRANCE_WHEN_MOVE        0x00000070	//���ʮɸI��ĤH�|�o�b
//
#define AI_KIND_NONE_AFTER_ATTACK       0x00000100  //���z�����ĤH��S���������(�|�ھڲ���AI�ۦ沾��)
#define AI_KIND_ATTACK_AFTER_ATTACK     0x00000200  //���z�����ĤH���ٷ|�~�򪫲z����
#define AI_KIND_MAGIC_AFTER_ATTACK      0x00000300  //���z�����ĤH��|�ĥΪk�N����
#define AI_KIND_MIXED_AFTER_ATTACK      0x00000400  //���z�����ĤH��|�ĥβV�X����
#define AI_KIND_DODGE_AFTER_ATTACK      0x00000500  //���z�����ĤH�ᰨ�W����
#define AI_KIND_RUN_ATTACK_AFTER_ATTACK 0x00000600  //���z�����ĤH���ٷ|�~��]�B���z����
#define	AI_KIND_TRANCE_AFTER_ATTACK     0x00000700	//���z�����ĤH��|�o�b
//
#define AI_KIND_NONE_AFTER_MAGIC        0x00001000  //�k�N��������S���������(�|�ھڲ���AI�ۦ沾��)
#define AI_KIND_ATTACK_AFTER_MAGIC      0x00002000  //�k�N��������ĥΪ��z����
#define AI_KIND_MAGIC_AFTER_MAGIC       0x00003000  //�k�N���������~��k�N����
#define AI_KIND_MIXED_AFTER_MAGIC       0x00004000  //�k�N��������ĥβV�X����
#define AI_KIND_DODGE_AFTER_MAGIC       0x00005000  //�k�N�������ᰨ�W����
#define AI_KIND_RUN_ATTACK_AFTER_MAGIC  0x00006000  //�k�N��������ĥζ]�B���z����
#define	AI_KIND_TRANCE_AFTER_MAGIC      0x00007000	//�k�N�������|�o�b
//
#define AI_KIND_NONE_AFTER_BEATED       0x00010000  //�Q����S������, �|�ھڲ���AI�ۦ沾��
#define AI_KIND_ATTACK_AFTER_BEATED     0x00020000  //�Q����|���z����
#define AI_KIND_MAGIC_AFTER_BEATED      0x00030000  //�Q����|�k�N����
#define AI_KIND_MIXED_AFTER_BEATED      0x00040000  //�Q����|�V�X����
#define AI_KIND_DODGE_AFTER_BEATED      0x00050000  //�Q����|����
#define AI_KIND_RUN_ATTACK_AFTER_BEATED 0x00060000  //�Q����|�]�B���z����
#define	AI_KIND_TRANCE_AFTER_BEATED     0x00070000	//�Q����|�o�b
//
#define AI_KIND_NONE_AFTER_DODGE        0x00100000  //���ק���S����L����(�|�ھڲ���AI�ۦ沾��)
#define AI_KIND_ATTACK_AFTER_DODGE      0x00200000  //���ק���|���z����
#define AI_KIND_MAGIC_AFTER_DODGE       0x00300000  //���ק���|�k�N����
#define AI_KIND_MIXED_AFTER_DODGE       0x00400000  //���ק���|�V�X����
#define AI_KIND_DODGE_AFTER_DODGE       0x00500000  //���ק���|�~�����
#define AI_KIND_RUN_ATTACK_AFTER_DODGE  0x00600000  //���ק���|�]�B���z����
#define	AI_KIND_TRANCE_AFTER_DODGE      0x0070000	//���ק���|�o�b
//
//
extern  void    server_set_npc_AI_functions(void);
extern  void    server_set_npc_doing_functions(void);
extern	void    ServerChangeCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    ServerChangeCharacterAiBlock(SLONG npc_no, SLONG ai_block, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    ServerCreateMagicArea(SLONG type, SLONG npc_no, SLONG mx, SLONG my, SLONG magic_no, SLONG magic_level);
extern  void    server_refresh_character(void);
extern	void	server_save_character_data(void);
extern	void	server_exec_talk_with_npc(SLONG	player_index, SLONG	dest_npc);


#endif//_SERVERCHARACTERDOING_H_
