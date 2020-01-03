///////////////////////////////////////////////////////////////////
//
//	Team.h	
//
//	Zhang Zhaohui	2003/4/22
//
//	²Õ¶¤±±¨î.
//
//	Copyright (c) Rays Multimedia. All rights reserved.
//
//////////////////////////////////////////////////////////////////


#pragma once
#include "NetGE_MainFunc.h"
#include "NetGE_Event_Def.h"
#include "NetGE_Event_Struct_Def.h"

//////////////////////////////////////////////////////////////////////////

#define MAX_ZONE_PLAYERS        500

enum TEAM_EVENT
{
//    TEAM_WANT_JOIN          = 100,
//    TEAM_TARGET_FULL        = 101,
//    TEAM_ALREADY_IN_TEAM    = 102,
//    TEAM_JOIN               = 103,
//    TEAM_EXIT               = 104,
//    TEAM_KICK               = 105,


    TEAM_WANT_JOIN                  = 100,
    TEAM_WANT_EXIT                  = 101,
    TEAM_SOMEONE_JOIN               = 102,
    TEAM_SOMEONE_EXIT               = 103,
    TEAM_SOMEONE_EXIT_ZONE          = 104,
    TEAM_JOIN                       = 105,
    TEAM_EXIT                       = 106,
    TEAM_KICK                       = 107,
    TEAM_CANNOT_JOIN_OTHER_TEAM     = 108,
    TEAM_TARGET_FULL                = 109,
    TEAM_ALREADY_IN_TEAM            = 110, 
    TEAM_KILL_TEAM                  = 111,
//    TEAM_CHANGE_ZONE                = 106,
};

enum TEAM_ICONMSG_ID
{
    TEAM_WANT_JOIN_ID               = 0,
    TEAM_WANT_EXIT_ID               = 1,
    TEAM_SOMEONE_JOIN_ID            = 2,
    TEAM_SOMEONE_EXIT_ID            = 3,
    TEAM_SOMEONE_EXIT_ZONE_ID       = 4,
    TEAM_JOIN_ID                    = 5,
    TEAM_EXIT_ID                    = 6,
    TEAM_KICK_ID                    = 7,
    TEAM_CANNOT_JOIN_OTHER_TEAM_ID  = 8,
    TEAM_TARGET_FULL_ID             = 9,
    TEAM_ALREADY_IN_TEAM_ID         = 10, 
    TEAM_KILL_TEAM_ID               = 11,
//   TEAM_CHANGE_ZONE_ID        = 106,
};


//////////////////////////////////////////////////////////////////////////

extern VOID team_want_join( TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM* param );
extern VOID team_target_full( TPOS_EVENT_NOTIFYJOINTEAMFULL *param );
extern VOID team_already_in_team( VOID );
extern VOID team_join( TPOS_EVENT_NOTIFYSOMEONEJOINTEAM *param );
extern VOID team_exit( TPOS_EVENT_NOTIFYSOMEONEEXITTEAM *param );
extern VOID team_kick( VOID );
extern VOID team_set_info( TPOS_EVENT_NOTIFYTEAMMEMBERINFO *param );
extern VOID team_change_zone( TPOS_EVENT_ZONENOTIFYTEAMMEMBERCHANGEZONE *param );
extern VOID team_make_team( TPOS_EVENT_NOTIFYMAKETEAM *param );
extern VOID team_kill_team( VOID );
extern VOID team_change_leader( TPOS_EVENT_NOTIFYCHANGELEADER *param );

extern VOID team_request_join( DWORD npc_id );
extern VOID team_agree_join( CHAR *name, CHAR *zone_name );
extern VOID team_request_exit( VOID );

extern VOID team_request_kick( CHAR *name );

extern SLONG team_handle_message( UINT msg, WPARAM wParam, LPARAM lParam );