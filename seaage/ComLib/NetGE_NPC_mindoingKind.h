/*
 *	ljun 2003-04-14
 */
 
#pragma once 


//-------------------------------------------------------------------------
//  ����ʵe������
//-------------------------------------------------------------------------
//  ����ʵe�@��

extern  SLONG   MinKind_NpcActionOneTime(SLONG npc_no, SLONG action, SLONG no_play_frame=0);
extern  SLONG   MinKind_NpcImgIdOneTime(SLONG npc_no, SLONG id, SLONG no_play_frame=0);
//  ����ʵe�`��
extern  SLONG   MinKind_NpcActionLoop(SLONG npc_no, SLONG action);
extern  SLONG   MinKind_NpcImgIdLoop(SLONG npc_no, SLONG id);
//-------------------------------------------------------------------------
//  �@�� �Ȥ��..�̤p������(MinKind)�����L�{��� 
//-------------------------------------------------------------------------
//���ʹL�{(�a���|�j��)
extern  SLONG    MinKind_NpcMoveFindPath(SLONG npc_no,SLONG dest_x,SLONG dest_y);
extern  SLONG   MinKind_NpcMagicDischarge(SLONG npc_no);
 //------------------------------------------------------------------------
 // End.
 //------------------------------------------------------------------------
 
 