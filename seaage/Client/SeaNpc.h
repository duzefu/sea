/*
**  seanpc
**  seanpc control model  
**  write by lijun 2002-11-22
*/
#ifndef	_INCLUDE_SEANPC_H_
#define _INCLUDE_SEANPC_H_		1


#define MAX_SEA_NPC_TRACK_FILE  100     //海上npc能具有的最多的軌跡種類的數目

//海洋NPC的行動方式( 正常移動,  還是帆船模式 0
#define SEA_NPC_MOVE_TYPE_SAIL      0   //航行  
#define SEA_NPC_MOVE_TYPE_NORMAL    1   //行走

//海洋NPC具有的狀態
#define SEA_NPC_STATE_FIGHT             0x00000001  //NPC處於戰鬥狀態下
#define SEA_NPC_STATE_SHADOW_MOVE       0x00000002  //帶殘影移動
#define SEA_NPC_STATE_INVINCIBLE        0x00000004  //無敵(不會被任何招式打中)
#define SEA_NPC_STATE_ANTI_HIDE         0x00000008  //反隱形
#define SEA_NPC_STATE_ANTI_POSE         0x00000010  //反偽裝
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
