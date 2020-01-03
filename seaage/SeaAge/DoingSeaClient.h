/*
    2002-11-25
    海洋NPC在聯機的時候的處理
 */
#ifndef     _INCLUDE_DOINGSEACLIENT_H_
#define     _INCLUDE_DOINGSEACLIENT_H_  1

//  在聯機的時候,對海上npc待機的處理 
SLONG   client_do_sea_npc_idle( SLONG npc_no );
//
SLONG   client_do_sea_npc_sail_to(SLONG npc_no);
SLONG   client_do_sea_npc_walk_to(SLONG npc_no);
//-
#endif
//------------------------------------------------------------------------------------------------------------
//      .End
//------------------------------------------------------------------------------------------------------------
