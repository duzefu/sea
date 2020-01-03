/*
 *	ljun 2003-04-14
 */
 
#pragma once 


//-------------------------------------------------------------------------
//  關於動畫播放函數
//-------------------------------------------------------------------------
//  播放動畫一次

extern  SLONG   MinKind_NpcActionOneTime(SLONG npc_no, SLONG action, SLONG no_play_frame=0);
extern  SLONG   MinKind_NpcImgIdOneTime(SLONG npc_no, SLONG id, SLONG no_play_frame=0);
//  播放動畫循環
extern  SLONG   MinKind_NpcActionLoop(SLONG npc_no, SLONG action);
extern  SLONG   MinKind_NpcImgIdLoop(SLONG npc_no, SLONG id);
//-------------------------------------------------------------------------
//  一些 客戶端..最小分塊行(MinKind)為的過程函數 
//-------------------------------------------------------------------------
//移動過程(帶路徑搜索)
extern  SLONG    MinKind_NpcMoveFindPath(SLONG npc_no,SLONG dest_x,SLONG dest_y);
extern  SLONG   MinKind_NpcMagicDischarge(SLONG npc_no);
 //------------------------------------------------------------------------
 // End.
 //------------------------------------------------------------------------
 
 