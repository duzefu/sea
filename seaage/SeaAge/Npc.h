/*
**      NPC.H
**      npc functions header.
**
**      ZJian,2000.11.22.
*/
#ifndef NPC_H_INCLUDE
#define NPC_H_INCLUDE
#include "map.h"


// D E F I N E S //////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_GAME_MAP        1           //�@�ɦa�ϼƶq

//------------------------------------------------------------------------
//�H����ܰϤj�p
//------------------------------------------------------------------------
#define NPC_MASK_WIDTH      60          //�ƹ�����ɪ��e��
#define NPC_MASK_HEIGHT     80          //�ƹ�����ɪ�����
//

//------------------------------------------------------------------------
//�H���лx(NPC FLAGS)
//------------------------------------------------------------------------
#define NPC_USED            0x00000001  //���b�ϥ�
#define NPC_ACTIVE          0x00000002  //�B�󬡰ʪ��A(�S���b�ϥ�)
#define NPC_BUSY            0x00000004  //���b����()
#define NPC_PAUSE           0x00000008  //�Ȱ���Ӫ��ʧ@
#define NPC_DIED            0x00000010  //�w�g���`

//
/*
//------------------------------------------------------------------------
//NPC���O(NPC KIND)
//------------------------------------------------------------------------
#define NPC_KIND_EMPLACEMENT        0   //���x
#define NPC_KIND_GUIDEPOST          1   //���P
#define NPC_KIND_NORMAL_MONSTER     2   //���q�Ǫ�
#define NPC_KIND_HEADER_MONSTER     3   //�Y�ةǪ�
#define NPC_KIND_BOSS_MONSTER       4   //BOSS�Ǫ�
#define NPC_KIND_THIEF_MONSTER      5   //�p����
#define NPC_KIND_TREASURE_MONSTER   6   //�_����
#define NPC_KIND_GUARD              7   //ĵ��
#define NPC_KIND_NPC                8   //���H(���H)
#define NPC_KIND_PLAYER             9   //���a
#define NPC_KIND_TREASURE           10  //�_��(�p�q)
#define NPC_KIND_MERMAID            11  //���H��(�|���ܭI������)
#define NPC_KIND_TRAP               12  //����
#define NPC_KIND_SUBMERGED_ROCK     13  //�t�G
#define NPC_KIND_BURBLE             14  //�x��
#define NPC_KIND_STATUARY           15  //�J��
#define	NPC_KIND_CORPSE		        16	//����
#define MAX_NPC_KINDS               17  //�`�����O�ƥ�
*/

//------------------------------------------------------------------------
//RELATIONS(NPC�PNPC�����Y) 
//------------------------------------------------------------------------
#define RELATION_NEUTRAL            0x00000001  //�P��褤��
#define RELATION_ALLY               0x00000002  //�P����p��
#define RELATION_OPPOSE             0x00000004  //�P���Ĺ�

//------------------------------------------------------------------------
//NPC��ܼаO(NPC_SHOW FLAGS)
//------------------------------------------------------------------------
#define	NPC_SHOW_ENABLE_VIEW		0x00000001	//�i�H�ݨ�
#define NPC_SHOW_ENABLE_RANGE       0x00000002  //�i�H�I�����
//
#define MAX_SHOW_SHADOWS            5           //�H�����ݼv�ƥ�

//------------------------------------------------------------------------
//NPC���(NPC TALK ASSOCIATED)
//------------------------------------------------------------------------
#define NPC_NAME_LEN                16          //�H���W�٪���
#define NPC_TALK_NUM                3           //�H����ܦ��
#define NPC_TALK_LEN                24          //�C���ܪ���
//
//NPC��ܪ����O
#define NPC_TALK_IS_DIALOG          1           //���
#define NPC_TALK_IS_NAME            2           //�H���W��
//
//------------------------------------------------------------------------
//NPC�����A(STATE)
//------------------------------------------------------------------------
// mark by lijun 
// 2003-04-08
/*
#define NPC_STATE_FIGHT             0x00000001  //NPC�B��԰����A�U
#define NPC_STATE_DEFENCE           0x00000002  //NPC�B���ת��A(���ʳt�״�b)
#define NPC_STATE_SHADOW_MOVE       0x00000004  //�a�ݼv����
#define NPC_STATE_INVINCIBLE        0x00000010  //�L��(���|�Q����ۦ�����)
#define NPC_STATE_RESIST            0x00000020  //�W�[���
#define NPC_STATE_ADD_MAX_HP        0x00000040  //�W�[HP�W��
#define NPC_STATE_POWER_ATTACK      0x00000080  //�����W�j(�P�ɷ|�W�[���z)
#define NPC_STATE_ANTI_HIDE         0x00000100  //������
#define NPC_STATE_ANTI_POSE         0x00000200  //�ϰ���
*/
//
//#define NEXT_NPC_FIGHT_STATE        1           //NPC���U�@�Ӿ԰����A
//#define PREV_NPC_FIGHT_STATE        2           //NPC���W�@�Ӿ԰����A

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
//--------------------------------------------------------------------------------------
//NPC��AI
//------------------------------
// Jack, todo [11:01,10/10/2002]



//--------------------------------------------------------------------------------------
//NPC���Ҧb�a�h
//------------------------------
#define NPC_LAYER_EXERCISE                  0   //�m�\�a�h
#define NPC_LAYER_EXPLORE                   1   //���I�a�h


// S T R U C T S //////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

typedef struct  tagGAME_NPC
{
    //-----------------------------------------------------------
    SLONG   flag;               //�Ч�
    SLONG   object_index;       //�����a�Ϫ������
    //-----------------------------------------------------------
    SLONG   effect;             //�v���S��
    //-----------------------------------------------------------    
    SLONG   ext_id;             //���[�ĪG���Х�
    SLONG   ext_frame;          //���[�ĪG�v���V
    //--------------------------------------------------------------------
    SLONG   foot_id;            //�H���}�U���A�ĪG����
    SLONG   foot_frame;         //�H���}�U���A�ĪG�Ϲ��V
    //--------------------------------------------------------------------
    SLONG   head_id;            //�H���Y�W�����A�ĪG����
    SLONG   head_frame;         //�H���Y�W�����A�ĪG�Ϲ��V
    //--------------------------------------------------------------------
    SLONG   body_front_id;      //�H�����W���ĪG��..npc�e������
    SLONG   body_back_id;       //�H�����W���ĪG��..npc�᭱����
    SLONG   body_frame;         //�H�����W���V��
    //-----------------------------------------------------------
    SLONG   talk_flags;        //��ܼлx
    DWORD   talk_time;         //����ɶ�
    SLONG   talk_lines;        //��ܦ��
    SLONG   talk_sx;           //��ܹ�ܪ���m x
    SLONG   talk_sy;           //��ܹ�ܪ���m y
    CHAR	talk_text[NPC_TALK_NUM][NPC_TALK_LEN+4];    //��ܤ�r
    //-----------------------------------------------------------
	UCHR	rgb_scroll[35];	    //�H����L�M�ĪG
    //-----------------------------------------------------------
} GAME_NPC,*LPGAME_NPC;


#pragma pack(pop)

//�Mnpc�W�ϮĪG�������@���ݩ�
//!!!�`�N�b�w�q�ܶq���ɭ�   NPC_SHOW  �����M  GAME_NPC �@�˪��j�p
typedef struct  tagNPC_SHOW
{
    SLONG   flag;           //�лx
    //--------------------------------------------------------------------
    SLONG   with_shadow;    //���ʮɱa�ݼv
    SLONG   last_x;         //�H���W���y�� x
    SLONG   last_y;         //�H���W���y�� y
    SLONG   last_z;         //�H���W���y�� z
    SLONG   shadow_x[MAX_SHOW_SHADOWS]; //�ݼv�y�� x
    SLONG   shadow_y[MAX_SHOW_SHADOWS]; //�ݼv�y�� y
    SLONG   shadow_z[MAX_SHOW_SHADOWS]; //�ݼv�y�� z
    //--------------------------------------------------------------------
    SLONG   ext_id;			//�H���S��ĪG����ID.
    SLONG   ext_frame;		//�H���S��ĪG�Ϲ��V
    //--------------------------------------------------------------------
    SLONG   foot_id;        //�H���}�U���A�ĪG����
    SLONG   foot_frame;     //�H���}�U���A�ĪG�Ϲ��V
    //--------------------------------------------------------------------
    SLONG   head_id;        //�H���Y�W�����A�ĪG����
    SLONG   head_frame;     //�H���Y�W�����A�ĪG�Ϲ��V
    //--------------------------------------------------------------------
    SLONG   body_front_id;  //�H�����W���ĪG��..npc�e������
    SLONG   body_back_id;   //�H�����W���ĪG��..npc�᭱����
    SLONG   body_frame;     //�H�����W���V��
    //
} NPC_SHOW, *LPNPC_SHOW;

// G L O B A L S //////////////////////////////////////////////////////////////////////////////////////////////////////
extern  SLONG       game_npc_max;

// F U N C T I O N S    P R O T O T Y P E /////////////////////////////////////////////////////////////////////////////
extern  int     init_npc(void);
extern  void    active_npc(int active);
extern  void    free_npc(void);
//
extern  void    init_one_game_npc(SLONG npc_no);
extern  void    clear_one_game_npc(SLONG npc_no);
extern  void    init_all_game_npc(void);

extern  void    set_npc_ext_id(SLONG npc_no, SLONG id);
extern  void    set_npc_ext_frame(SLONG npc_no, SLONG frame);

extern  void    clear_npc_ext_effect(SLONG npc_no);
extern  void    abort_npc_doing(SLONG npc_no);
extern  void    set_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    change_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
//
extern  void    refresh_map_npc(void);
extern  void    refresh_one_npc(SLONG npc_no);
extern  void    refresh_npc_state_lapse(SLONG npc_no);
extern  void    debug_show_map_npc_data(SLONG npc_no, BMP *bitmap);
//
extern  void    update_map_npc_object(void);
//
extern  void    active_map_npc(SLONG npc_no);
extern  void    del_map_npc(SLONG npc_no);
extern  void    clear_all_map_npc(void);
//
extern  SLONG   get_npc_magic_standpoint_relation( SLONG src_npc, SLONG dest_npc);
//
extern  void    clear_npc_talk(SLONG npc_no);
extern  SLONG   add_npc_talk(SLONG npc_no, DWORD talk_time, USTR* text);
extern  void    set_npc_talk_position(SLONG npc_no, SLONG talk_x, SLONG talk_y);
extern  void    redraw_npc_talk(SLONG sx, SLONG sy, SLONG npc_no, BMP *bitmap);
extern  void    redraw_npc_name(SLONG top_cx, SLONG top_cy, SLONG npc_no, BMP *bitmap);
extern  void    local_refresh_npc_talk(void);
extern  SLONG   get_npc_talk_flag(SLONG npc_no);
extern  void    set_npc_talk_flag(SLONG npc_no, SLONG flag);
//
extern  void    init_npc_talk_list(void);
extern  void    clear_npc_talk_list(void);
extern  void    add_npc_to_npc_talk_list(SLONG npc_no);
extern  void    sort_npc_talk_list(void);
extern  void    redraw_map_npc_talk(SLONG map_no, SLONG map_sx, SLONG map_sy, BMP *bitmap);

//ui npc functions ---------------------------------------------------------
extern	void    refresh_ui_npc(void);
extern	void    ui_redraw_one_npc_object(SLONG npc_no, BMP *bitmap);
extern	void    loop_ui_npc_dir(SLONG npc_no);
extern	void    update_ui_npc_object(void);
extern	void    free_ui_npc_object(void);
//
extern  void    init_npc_show(void);
extern  void    update_npc_show_shadow_move(SLONG index, SLONG x, SLONG y, SLONG z, SLONG with_shadow);
extern  void    set_npc_show_ext_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_ext_id(SLONG index);
extern  void    set_npc_show_ext_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_ext_frame(SLONG index);
extern  void    set_npc_show_head_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_head_id(SLONG index);
extern  void    set_npc_show_head_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_head_frame(SLONG index);
extern  void    set_npc_show_foot_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_foot_id(SLONG index);
extern  void    set_npc_show_foot_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_foot_frame(SLONG index);
extern  void    set_npc_show_body_front_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_body_front_id(SLONG index);
extern  void    set_npc_show_body_back_id(SLONG index, SLONG id);
extern  SLONG   get_npc_show_body_back_id(SLONG index);
extern  void    set_npc_show_body_frame(SLONG index, SLONG frame);
extern  SLONG   get_npc_show_body_frame(SLONG index);
//
extern  void    set_npc_effect(SLONG npc_no, SLONG effect);
extern	SLONG	get_npc_effect(SLONG npc_no);
extern  SLONG   get_npc_flag(SLONG npc_no);
extern  void    set_npc_flag(SLONG npc_no, SLONG flag);
extern	void	set_npc_object_index(SLONG npc_no, SLONG index);
extern	SLONG	get_npc_object_index(SLONG npc_no);
extern	void	set_npc_ext_id(SLONG npc_no, SLONG ext_id);
extern	SLONG	get_npc_ext_id(SLONG npc_no);
extern	void	set_npc_ext_frame(SLONG npc_no, SLONG ext_frame);
extern	SLONG	get_npc_ext_frame(SLONG npc_no);
extern	void    set_npc_foot_id(SLONG npc_no,SLONG foot_id);
extern	SLONG   get_npc_foot_id(SLONG npc_no);
extern	void    set_npc_foot_frame(SLONG npc_no,SLONG foot_frame);
extern	SLONG   get_npc_foot_frame(SLONG npc_no);
extern	void    set_npc_head_id(SLONG npc_no,SLONG head_id);
extern	SLONG   get_npc_head_id(SLONG npc_no);
extern	void    set_npc_head_frame(SLONG npc_no,SLONG head_frame);
extern	SLONG   get_npc_head_frame(SLONG npc_no);
extern	void    set_npc_body_front_id(SLONG npc_no,SLONG body_id);
extern	SLONG   get_npc_body_front_id(SLONG npc_no);
extern	void    set_npc_body_back_id(SLONG npc_no,SLONG body_id);
extern	SLONG   get_npc_body_back_id(SLONG npc_no);
extern	void    set_npc_body_frame(SLONG npc_no,SLONG body_frame);
extern	SLONG   get_npc_body_frame(SLONG npc_no);
//
extern	SLONG	get_npc_talk_lines(SLONG npc_no);
extern	CHAR*	get_npc_talk_text(SLONG npc_no, SLONG line_index);
extern	void	set_npc_talk_time(SLONG npc_no, ULONG talk_time);
extern	ULONG	get_npc_talk_time(SLONG npc_no);
extern	void	set_npc_talk_position(SLONG npc_no, SLONG sx, SLONG sy);
extern	void	get_npc_talk_position(SLONG npc_no, SLONG *sx, SLONG *sy);
//
extern  void    loop_npc_ext_frame(SLONG npc_no);
//
extern  void    ClientChangeCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern  void    set_npc_ai_function(void);
extern	void    set_npc_doing_functions(void);
//
extern	void	set_npc_rgb_scroll(SLONG npc_no, UCHR *buffer);
extern	UCHR*	get_npc_rgb_scroll(SLONG npc_no);

//
// Map npc object functions:
//
SLONG	add_map_npc_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick);
SLONG	del_map_npc_object(SLONG object_index);
void	draw_map_npc_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_npc_object(SLONG object_index);
SLONG	change_map_npc_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_npc_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
									   SLONG *ex, SLONG *ey, POLY **poly);
//Ū���ݭn��npc�����ɺ޲z����
extern  void    npc_effect_id_manage(SLONG *npc_id,SLONG *npc_show_id,SLONG *npc_frame,SLONG *npc_show_frame);
//
#endif//NPC_H_INCLUDE
