///////////////////////////////////////////////////////////////////
//
//	Team.cpp	
//
//	Zhang Zhaohui	2003/4/22
//
//	組隊控制.
//
//	Copyright (c) Rays Multimedia. All rights reserved.
//
//////////////////////////////////////////////////////////////////


#include "mainfun.h"
#include "ClientMain.h"
#include "Team.h"
#include "UIIconMessage.h"
#include "CmdEvent.h"
#include "crange.h"
#include "mousehand.h"
#include "map.h"

//////////////////////////////////////////////////////////////////////////

static VOID team_remove_team_member( CHAR * name );
static VOID team_clear_team_member( VOID );
static VOID team_add_team_member( TPOS_EVENT_NOTIFYMAKETEAM *param );

//////////////////////////////////////////////////////////////////////////

VOID team_want_join( TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM* param )
{
    ICONMSG_PARA p;
    strcpy( p.str[0], param->MemberMainName );
    strcpy( p.str[1], param->MemberZoneName );

    add_iconmsg( TEAM_WANT_JOIN_ID, IM_YESNO, &p, TEAM_WANT_JOIN );

}


VOID team_target_full( TPOS_EVENT_NOTIFYJOINTEAMFULL *param )
{
    ICONMSG_PARA  p;
    strcpy( p.str[0], param->LeaderMainName );

    add_iconmsg( TEAM_TARGET_FULL_ID, IM_HINT, &p, TEAM_TARGET_FULL );
}


VOID team_already_in_team( VOID )
{
    ICONMSG_PARA p;
    CHAR *pname = NULL;
    
    LOCK_CHARACTER( g_lPlayerIndex );
    pname = GetCharacterTeamMemberMainName( g_lPlayerIndex, 0 );
    UNLOCK_CHARACTER( g_lPlayerIndex );
    
    if ( !pname )
        return;

    strcpy( p.str[0], pname );
    add_iconmsg( TEAM_ALREADY_IN_TEAM_ID, IM_HINT, &p, TEAM_ALREADY_IN_TEAM );
}


VOID team_join( TPOS_EVENT_NOTIFYSOMEONEJOINTEAM *param )
{
    ICONMSG_PARA p;
    SLONG count;

    strcpy( p.str[0], param->MainName );
    add_iconmsg( TEAM_SOMEONE_JOIN_ID, IM_HINT, &p, TEAM_JOIN );

    
    LOCK_CHARACTER( g_lPlayerIndex );

    count = GetCharacterTeamMaxMembers( g_lPlayerIndex );

    if ( count < MAX_CHARACTER_TEAM_MEMBERS )
    {
        SetCharacterTeamMemberMainName( g_lPlayerIndex, count, param->MainName );
        SetCharacterTeamMemberHp( g_lPlayerIndex, count, param->Hp );
        SetCharacterTeamMemberMaxHp( g_lPlayerIndex, count, param->MaxHp );
        SetCharacterTeamMemberLevel( g_lPlayerIndex, count, param->Level );
        SetCharacterTeamMemberEyes( g_lPlayerIndex, count, param->Eyes );
        SetCharacterTeamMemberMouth( g_lPlayerIndex, count, param->Mouth );
        SetCharacterTeamMemberCareer( g_lPlayerIndex, count, param->Career );
        SetCharacterTeamMemberSex( g_lPlayerIndex, count, param->Sex );
        SetCharacterTeamMemberZoneName( g_lPlayerIndex, count, param->ZoneName );
        count ++;
    }

    SetCharacterTeamMaxMembers( g_lPlayerIndex, count );

    UNLOCK_CHARACTER( g_lPlayerIndex );
}


VOID team_exit( TPOS_EVENT_NOTIFYSOMEONEEXITTEAM *param )
{
    ICONMSG_PARA p;
    CHAR *p_name;

    if ( strcmp( param->MemberMainName, g_szPlayerMainName) == 0 )
    {
        LOCK_CHARACTER( g_lPlayerIndex );
        p_name = GetCharacterTeamMemberMainName( g_lPlayerIndex, 0 );
        strcpy( p.str[0], p_name );
        UNLOCK_CHARACTER( g_lPlayerIndex );

        team_clear_team_member( );
        add_iconmsg( TEAM_EXIT_ID, IM_HINT, &p, TEAM_EXIT );
    }
    else
    {
        team_remove_team_member( param->MemberMainName );
        strcpy( p.str[0], param->MemberMainName );
        add_iconmsg( TEAM_SOMEONE_EXIT_ID, IM_HINT, &p, TEAM_SOMEONE_EXIT );
    }
}


VOID team_kick( VOID )
{
    ICONMSG_PARA p;
    CHAR *pname = NULL;

    LOCK_CHARACTER( g_lPlayerIndex );
    pname = GetCharacterTeamMemberMainName( g_lPlayerIndex, 0 );
    UNLOCK_CHARACTER( g_lPlayerIndex );

    if ( !pname )
        return;
    
    team_clear_team_member( );

    
    strcpy( p.str[0], pname );
    
    add_iconmsg( TEAM_EXIT_ID, IM_HINT, &p, TEAM_KICK );
}


VOID team_set_info( TPOS_EVENT_NOTIFYTEAMMEMBERINFO *param )
{
    ICONMSG_PARA p;
    CHAR *pname = NULL;
    
    if ( !param->TeamMemberInfo[0].MainName[0] )
        return;

    team_clear_team_member();

    team_add_team_member( (TPOS_EVENT_NOTIFYMAKETEAM*)param );

    LOCK_CHARACTER( g_lPlayerIndex );
    pname = GetCharacterTeamMemberMainName( g_lPlayerIndex, 0 );
    UNLOCK_CHARACTER( g_lPlayerIndex );
    
    if ( !pname )
        return;

    strcpy( p.str[0], pname );

    add_iconmsg( TEAM_JOIN_ID, IM_HINT, &p, TEAM_JOIN );

}


VOID team_change_zone( TPOS_EVENT_ZONENOTIFYTEAMMEMBERCHANGEZONE *param )
{
}


VOID team_make_team( TPOS_EVENT_NOTIFYMAKETEAM *param )
{
    ICONMSG_PARA p;

    team_clear_team_member();
    team_add_team_member( param );

    if ( strcmp( param->TeamMemberInfo[0].MainName, g_szPlayerMainName ) == 0 )
    {
        strcpy( p.str[0], param->TeamMemberInfo[1].MainName );
        add_iconmsg( TEAM_SOMEONE_JOIN_ID, IM_HINT, &p, TEAM_SOMEONE_JOIN );
    }
    else
    {
        strcpy( p.str[0], param->TeamMemberInfo[0].MainName );
        add_iconmsg( TEAM_JOIN_ID, IM_HINT, &p, TEAM_JOIN );
    }
}


VOID team_kill_team( VOID )
{
    ICONMSG_PARA p;
    team_clear_team_member( );
    add_iconmsg( TEAM_KILL_TEAM_ID, IM_HINT, &p, TEAM_KILL_TEAM );
}


VOID team_change_leader( TPOS_EVENT_NOTIFYCHANGELEADER *param )
{
    team_clear_team_member();
    team_add_team_member( (TPOS_EVENT_NOTIFYMAKETEAM*)param );
}

//////////////////////////////////////////////////////////////////////////

VOID team_request_join( DWORD npc_id )
{
    CHAR *leader_name;

    if ( npc_id >= 0 && npc_id < MAX_ZONE_PLAYERS )
    {
        LOCK_CHARACTER( g_lPlayerIndex );
        leader_name = GetCharacterMainName( npc_id );
        UNLOCK_CHARACTER( g_lPlayerIndex );

        if ( leader_name )
        {
            client_cmd_request_join_team( leader_name, g_szPlayerZone );
        }
    }
}


VOID team_agree_join( CHAR *name, CHAR *zone_name )
{
    client_cmd_request_agree_join_team( name, zone_name );
}


VOID team_request_exit( VOID )
{
    CHAR *leader_name = NULL;

    // 獲得隊長的名字
    LOCK_CHARACTER( g_lPlayerIndex );
    leader_name = GetCharacterTeamMemberMainName( g_lPlayerIndex, 0 );
    UNLOCK_CHARACTER( g_lPlayerIndex );

    if ( leader_name && strlen( leader_name ) > 0 )
        client_cmd_request_exit_team( leader_name );
}


VOID team_request_kick( CHAR *name )
{
//    CHAR *zone_name;
//    client_cmd_request_kick_team_member( name, zone_name );
}


//////////////////////////////////////////////////////////////////////////
VOID team_remove_team_member( CHAR * name )
{
    SLONG i, j, count;
    CHAR *p = NULL;

    LOCK_CHARACTER( g_lPlayerIndex );

    count = GetCharacterTeamMaxMembers( g_lPlayerIndex );
    for ( i = 0; i < count; i++ )
    {
        p = GetCharacterTeamMemberMainName( g_lPlayerIndex, i );

        if ( strcmp( name, p ) == 0 )
        {
            memset( &ZoneCharacter[g_lPlayerIndex].Team.Member[i], 0, sizeof( TPOS_CHARACTER_TEAM_MEMBER ) );
            break;
        }
    }
    
    if ( i < count )
    {
        count--;
        for ( j = i; j < count; j++ )
        {
            ZoneCharacter[g_lPlayerIndex].Team.Member[j] = ZoneCharacter[g_lPlayerIndex].Team.Member[j+1];
        }
        memset( &ZoneCharacter[g_lPlayerIndex].Team.Member[count], 0, sizeof( TPOS_CHARACTER_TEAM_MEMBER ) );
        SetCharacterTeamMaxMembers( g_lPlayerIndex, count );
    }

    UNLOCK_CHARACTER( g_lPlayerIndex );
}


VOID team_clear_team_member( VOID )
{
    LOCK_CHARACTER( g_lPlayerIndex );
    memset( &ZoneCharacter[g_lPlayerIndex].Team, 0, sizeof( TPOS_CHARACTER_TEAM ) );
    UNLOCK_CHARACTER( g_lPlayerIndex );
}


//VOID team_add_team_member( TPOS_CHARACTER_TEAM_MEMBER *member )
VOID team_add_team_member( TPOS_EVENT_NOTIFYMAKETEAM *member )
{
    SLONG i, count = 0;
    TPOS_EVENT_NOTIFYSOMEONEJOINTEAM *one;

    one = member->TeamMemberInfo;

    LOCK_CHARACTER( g_lPlayerIndex );

    for ( i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i ++ )
    {
        if ( member->TeamMemberInfo[i].MainName[0] )
        {
            SetCharacterTeamMemberMainName( g_lPlayerIndex, i, one[i].MainName );
            SetCharacterTeamMemberHp( g_lPlayerIndex, i, one[i].Hp );
            SetCharacterTeamMemberMaxHp( g_lPlayerIndex, i, one[i].MaxHp );
            SetCharacterTeamMemberLevel( g_lPlayerIndex, i, one[i].Level );
            SetCharacterTeamMemberEyes( g_lPlayerIndex, i, one[i].Eyes );
            SetCharacterTeamMemberMouth( g_lPlayerIndex, i, one[i].Mouth );
            SetCharacterTeamMemberCareer( g_lPlayerIndex, i, one[i].Career );
            SetCharacterTeamMemberSex( g_lPlayerIndex, i, one[i].Sex );
            SetCharacterTeamMemberZoneName( g_lPlayerIndex, i, one[i].ZoneName );
            count ++;
        }
    }

    SetCharacterTeamMaxMembers( g_lPlayerIndex, count );

    UNLOCK_CHARACTER( g_lPlayerIndex );
}

//////////////////////////////////////////////////////////////////////////
// 響應組隊技能
SLONG team_handle_message( UINT msg, WPARAM wParam, LPARAM lParam )
{
    SLONG result = FALSE;
    SLONG magic_no = 0;
    static SLONG ActiveID = 0;
    SLONG event_type, event_id;
    SLONG mouse_x, mouse_y;

    switch ( msg )
    {
    case WM_LBUTTONDOWN:
        LOCK_CHARACTER( g_lPlayerIndex );
        magic_no = GetCharacterLeftSkill( g_lPlayerIndex );
        UNLOCK_CHARACTER( g_lPlayerIndex );

        switch ( magic_no )
        {
        case MAGIC_NO_JOIN_TEAM:
            mouse_x = GET_X_LPARAM( lParam );
            mouse_y = GET_Y_LPARAM( lParam );
            event_type = event_id = 0;
            game_range.mapping( mouse_x, mouse_y, &event_type, &event_id );
            if ( event_type == RT_NPC )
            {
                team_request_join( event_id );
                result = TRUE;
            }
            break;
        case MAGIC_NO_LEAVE_TEAM:
            mouse_x = GET_X_LPARAM( lParam );
            mouse_y = GET_Y_LPARAM( lParam );
            event_type = event_id = 0;
            game_range.mapping( mouse_x, mouse_y, &event_type, &event_id );
            if ( event_type == RT_MAP || event_type == RT_NPC )
            {
                team_request_exit();
                result = TRUE;
            }
            break;
        }
        break;
    case WM_RBUTTONDOWN:
        LOCK_CHARACTER( g_lPlayerIndex );
        magic_no = GetCharacterRightSkill( g_lPlayerIndex );
        UNLOCK_CHARACTER( g_lPlayerIndex );
        switch ( magic_no )
        {
        case MAGIC_NO_JOIN_TEAM:
            mouse_x = GET_X_LPARAM( lParam );
            mouse_y = GET_Y_LPARAM( lParam );
            event_type = event_id = 0;
            game_range.mapping( mouse_x, mouse_y, &event_type, &event_id );
            if ( event_type == RT_NPC )
            {
                team_request_join( event_id );
                result = TRUE;
            }
            break;
        case MAGIC_NO_LEAVE_TEAM:
            mouse_x = GET_X_LPARAM( lParam );
            mouse_y = GET_Y_LPARAM( lParam );
            event_type = event_id = 0;
            game_range.mapping( mouse_x, mouse_y, &event_type, &event_id );
            if ( event_type == RT_MAP || event_type == RT_NPC )
            {
                team_request_exit();
                result = TRUE;
            }
            break;
        }
        break;
    }
    
     return result;
}