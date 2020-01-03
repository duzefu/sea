/*
 *	npc_state.h
 *  2003-04-08  lijun .
 *
 */
 #pragma once 
 
 
 #define    MAX_NPC_STATE       32      //NPC最多能具有的狀態..具體的數目參考Netge_character.h
                                        //最多32是因為只有32bit 
 
typedef   struct NPC_STATE_EFFECT_CONTROL_STRUCT
 {
    //頭上物件的編號
    SLONG   head_id;
    //身體物件前方物件的編號
    SLONG   front_id;
    //身體物件後方物件的編號
    SLONG   back_id;
    //腳下物件的編號
    SLONG   foot_id;
    //需要的身體上圖特效
    SLONG   npc_efc;
 }NPC_STATE_EFFECT_CONTROL;
  
 
 //------------------------------------------------------------------------
 // End.
 //------------------------------------------------------------------------
 