/*
 *	npc_state.h
 *  2003-04-08  lijun .
 *
 */
 #pragma once 
 
 
 #define    MAX_NPC_STATE       32      //NPC�̦h��㦳�����A..���骺�ƥذѦ�Netge_character.h
                                        //�̦h32�O�]���u��32bit 
 
typedef   struct NPC_STATE_EFFECT_CONTROL_STRUCT
 {
    //�Y�W���󪺽s��
    SLONG   head_id;
    //���骫��e�誫�󪺽s��
    SLONG   front_id;
    //���骫���誫�󪺽s��
    SLONG   back_id;
    //�}�U���󪺽s��
    SLONG   foot_id;
    //�ݭn������W�ϯS��
    SLONG   npc_efc;
 }NPC_STATE_EFFECT_CONTROL;
  
 
 //------------------------------------------------------------------------
 // End.
 //------------------------------------------------------------------------
 