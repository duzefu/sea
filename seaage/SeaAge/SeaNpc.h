/*
**  seanpc
**  seanpc control model  
**  write by lijun 2002-11-22
*/
#ifndef	_INCLUDE_SEANPC_H_
#define _INCLUDE_SEANPC_H_		1


#define MAX_SEA_NPC_TRACK_FILE  100     //���Wnpc��㦳���̦h���y��������ƥ�

//���vNPC����ʤ覡( ���`����,  �٬O�|��Ҧ� 0
#define SEA_NPC_MOVE_TYPE_SAIL      0   //���  
#define SEA_NPC_MOVE_TYPE_NORMAL    1   //�樫

//���vNPC�㦳�����A
#define SEA_NPC_STATE_FIGHT             0x00000001  //NPC�B��԰����A�U
#define SEA_NPC_STATE_SHADOW_MOVE       0x00000002  //�a�ݼv����
#define SEA_NPC_STATE_INVINCIBLE        0x00000004  //�L��(���|�Q����ۦ�����)
#define SEA_NPC_STATE_ANTI_HIDE         0x00000008  //������
#define SEA_NPC_STATE_ANTI_POSE         0x00000010  //�ϰ���
//
//
typedef struct tagSEA_NPC_TRACK_FILE_INFO
{
    SLONG   move[NPC_DIRS];
    SLONG   idle[NPC_DIRS];
}SEA_NPC_TRACK_FILE_INFO;
//------------------------------------------------------------------------------------------------------------------------------
//  V A R I A B L E 
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  F U N C T I O N
//------------------------------------------------------------------------------------------------------------------------------
void    init_sea_npc_track_file_info(void);
void    debug_log_sea_npc_track_file_info(void);
SLONG   load_sea_npc_track_file_info(void);
void    add_sea_npc_track(SLONG track_id,SLONG x,SLONG y,SLONG dir,SLONG state);

#endif;//_INCLUDE_SEANPC_H_
//------------------------------------------------------------------------------------------------------------------------------
//  .End
//------------------------------------------------------------------------------------------------------------------------------
