/*
**	UIMapQuickMagic.cpp
**	UI of map quick magics.
**
**	Jack, 2002/09/13.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "CRange.h"
#include "ErrorMsg.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "UIInfoBar.h"
#include "UIMagicIcon.h"
#include "UIMapQuickMagic.h"
#include "CmdEvent.h"
#include "Map.h"


/******************************************************************************************************************/
/* UI MAP QUICK MAGICS FUNCTIONS                                                                                  */
/******************************************************************************************************************/
void    redraw_map_ui_left_quick_magics(BMP *bitmap)
{
    enum
    {   LINE_OTHER_MAGICS   =   4,  //magics count per line(for others magics).
    };
    SLONG   common_magics[MAX_CHARACTER_SKILLS][2];    //[0] as magic_no, [1] as quick_index, for under_list magics.
    SLONG   others_magics[MAX_CHARACTER_SKILLS][2];    //[0] as magic_no, [1] as quick_index
    SLONG   i, total_common, total_others;
    SLONG   magic_no, icon_index, quick_index;
    SLONG   sx, sy, x, y;
    SLONG   is_fight;
	SLONG	on_the_sea;

    LOCK_CHARACTER(g_lPlayerIndex);
    is_fight = IsCharacterOnFightState(g_lPlayerIndex);
	on_the_sea = IsCharacterOnTheSea(g_lPlayerIndex);
	if(on_the_sea)
	{
		total_common = 0;
		total_others = 0;
		for(i=0; i<MAX_CHARACTER_SKILLS; i++)
		{
			magic_no = GetCharacterSkillNo(g_lPlayerIndex, i);
			if(IsSeaSkill(magic_no, 0) && IsLeftHandSkill(magic_no, 0))
			{
				if(IsUnderListSkill(magic_no, 0))
				{
					common_magics[total_common][0] = magic_no;
					common_magics[total_common++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, LEFT_HAND);
				}
				else
				{
					others_magics[total_others][0] = magic_no;
					others_magics[total_others++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, LEFT_HAND);
				}
			}
		}
	}
	else
	{
		total_common = 0;
		total_others = 0;
		for(i=0; i<MAX_CHARACTER_SKILLS; i++)
		{
			magic_no = GetCharacterSkillNo(g_lPlayerIndex, i);
			if(IsLandSkill(magic_no, 0) && IsLeftHandSkill(magic_no, 0))
			{
				if(IsUnderListSkill(magic_no, 0))
				{
					common_magics[total_common][0] = magic_no;
					common_magics[total_common++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, LEFT_HAND);
				}
				else
				{
					others_magics[total_others][0] = magic_no;
					others_magics[total_others++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, LEFT_HAND);
				}
			}
		}
	}
    UNLOCK_CHARACTER(g_lPlayerIndex);

    //under_list left magics
    sx = UIMAP_LEFT_QUICK_MAGICS_SX;
    sy = UIMAP_LEFT_QUICK_MAGICS_SY;
    for(i=0; i<total_common; i++)
    {
        magic_no = common_magics[i][0];
        quick_index = common_magics[i][1];
        icon_index = GetSkillIconIndex(magic_no);

        if ( (is_fight && IsFightSkill(magic_no, 0)) || ((!is_fight) && IsPeaceSkill(magic_no, 0)) )
            redraw_magic_icon_image(sx + MAGIC_ICON_WIDTH/2, sy + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_NORMAL);
        else
            redraw_magic_icon_image(sx + MAGIC_ICON_WIDTH/2, sy + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_INVALID);
        redraw_map_ui_magic_quick_info(sx, sy, quick_index, bitmap);

        game_range.add(sx, sy, MAGIC_ICON_WIDTH, MAGIC_ICON_HEIGHT, UIMAP_EVENT, UIMAP_ID_QUICK_MAGIC_0 + magic_no);
        sx += UIMAP_LEFT_QUICK_MAGICS_DX;
    }

    //others left magics
    sx = UIMAP_LEFT_QUICK_MAGICS_SX;
    sy = UIMAP_LEFT_QUICK_MAGICS_SY + UIMAP_LEFT_QUICK_MAGICS_DY;
    for(i=0; i<total_others; i++)
    {
        x = sx + (i % LINE_OTHER_MAGICS) * UIMAP_LEFT_QUICK_MAGICS_DX;
        y = sy + (i / LINE_OTHER_MAGICS) * UIMAP_LEFT_QUICK_MAGICS_DY;
        magic_no = others_magics[i][0];
        quick_index = others_magics[i][1];
        icon_index = GetSkillIconIndex(magic_no);

        if ( (is_fight && IsFightSkill(magic_no, 0)) || ((!is_fight) && IsPeaceSkill(magic_no, 0)) )
            redraw_magic_icon_image(x + MAGIC_ICON_WIDTH/2, y + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_NORMAL);
        else
            redraw_magic_icon_image(x + MAGIC_ICON_WIDTH/2, y + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_INVALID);

        redraw_map_ui_magic_quick_info(x, y, quick_index, bitmap);

        game_range.add(x, y, MAGIC_ICON_WIDTH, MAGIC_ICON_HEIGHT, UIMAP_EVENT, UIMAP_ID_QUICK_MAGIC_0 + magic_no);
    }
}


void    redraw_map_ui_right_quick_magics(BMP *bitmap)
{
    enum
    {   LINE_OTHER_MAGICS   =   4,  //magics count per line(for others magics).
    };
    SLONG   common_magics[MAX_CHARACTER_SKILLS][2];    //[0] as magic_no, [1] as quick_index, for under_list magics.
    SLONG   others_magics[MAX_CHARACTER_SKILLS][2];    //[0] as magic_no, [1] as quick_index
    SLONG   i, total_common, total_others;
    SLONG   magic_no, icon_index, quick_index;
    SLONG   sx, sy, x, y;
    SLONG   is_fight;
	SLONG	on_the_sea;

    LOCK_CHARACTER(g_lPlayerIndex);
    is_fight = IsCharacterOnFightState(g_lPlayerIndex);
	on_the_sea = IsCharacterOnTheSea(g_lPlayerIndex);
	if(on_the_sea)
	{
		total_common = 0;
		total_others = 0;
		for(i=0; i<MAX_CHARACTER_SKILLS; i++)
		{
			magic_no = GetCharacterSkillNo(g_lPlayerIndex, i);
			if(IsSeaSkill(magic_no, 0) && IsRightHandSkill(magic_no, 0))
			{
				if(IsUnderListSkill(magic_no, 0))
				{
					common_magics[total_common][0] = magic_no;
					common_magics[total_common++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, RIGHT_HAND);
				}
				else
				{
					others_magics[total_others][0] = magic_no;
					others_magics[total_others++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, RIGHT_HAND);
				}
			}
		}
	}
	else
	{
		total_common = 0;
		total_others = 0;
		for(i=0; i<MAX_CHARACTER_SKILLS; i++)
		{
			magic_no = GetCharacterSkillNo(g_lPlayerIndex, i);
			if(IsLandSkill(magic_no, 0) && IsRightHandSkill(magic_no, 0))
			{
				if(IsUnderListSkill(magic_no, 0))
				{
					common_magics[total_common][0] = magic_no;
					common_magics[total_common++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, RIGHT_HAND);
				}
				else
				{
					others_magics[total_others][0] = magic_no;
					others_magics[total_others++][1] = 
						FindCharacterFnSkillIndex(g_lPlayerIndex, magic_no, RIGHT_HAND);
				}
			}
		}
	}
    UNLOCK_CHARACTER(g_lPlayerIndex);

    //under_list right magics
    sx = UIMAP_RIGHT_QUICK_MAGICS_SX;
    sy = UIMAP_RIGHT_QUICK_MAGICS_SY;
    for(i=0; i<total_common; i++)
    {
        magic_no = common_magics[i][0];
        quick_index = common_magics[i][1];
        icon_index = GetSkillIconIndex(magic_no);
        if ( (is_fight && IsFightSkill(magic_no, 0)) || ((!is_fight) && IsPeaceSkill(magic_no, 0)) )
            redraw_magic_icon_image(sx + MAGIC_ICON_WIDTH/2, sy + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_NORMAL);
        else
            redraw_magic_icon_image(sx + MAGIC_ICON_WIDTH/2, sy + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_INVALID);
        redraw_map_ui_magic_quick_info(sx, sy, quick_index, bitmap);

        game_range.add(sx, sy, MAGIC_ICON_WIDTH, MAGIC_ICON_HEIGHT, UIMAP_EVENT, UIMAP_ID_QUICK_MAGIC_0 + magic_no);
        sx += UIMAP_RIGHT_QUICK_MAGICS_DX;
    }

    //others right magics
    sx = UIMAP_RIGHT_QUICK_MAGICS_SX;
    sy = UIMAP_RIGHT_QUICK_MAGICS_SY + UIMAP_RIGHT_QUICK_MAGICS_DY;
    for(i=0; i<total_others; i++)
    {
        x = sx + (i % LINE_OTHER_MAGICS) * UIMAP_RIGHT_QUICK_MAGICS_DX;
        y = sy + (i / LINE_OTHER_MAGICS) * UIMAP_RIGHT_QUICK_MAGICS_DY;
        magic_no = others_magics[i][0];
        quick_index = others_magics[i][1];
        icon_index = GetSkillIconIndex(magic_no);
        if ( (is_fight && IsFightSkill(magic_no, 0)) || ((!is_fight) && IsPeaceSkill(magic_no, 0)) )
            redraw_magic_icon_image(x + MAGIC_ICON_WIDTH/2, y + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_NORMAL);
        else
            redraw_magic_icon_image(x + MAGIC_ICON_WIDTH/2, y + MAGIC_ICON_HEIGHT/2, icon_index, bitmap, MAGIC_ICON_INVALID);
        redraw_map_ui_magic_quick_info(x, y, quick_index, bitmap);

        game_range.add(x, y, MAGIC_ICON_WIDTH, MAGIC_ICON_HEIGHT, UIMAP_EVENT, UIMAP_ID_QUICK_MAGIC_0 + magic_no);
    }
}


void    redraw_map_ui_quick_magic_mouse_point_info(SLONG id, BMP *bitmap)
{
    SLONG   magic_no, magic_index, magic_level;
    INFO_BAR    info_bar;
    SLONG   sx, sy, xl, yl;
    USTR    name[128], info[128];

    magic_no = id - UIMAP_ID_QUICK_MAGIC_0;
    LOCK_CHARACTER(g_lPlayerIndex);
    magic_index = FindCharacterSkillIndex(g_lPlayerIndex, magic_no);
    if(magic_index >= 0)
	{
        //magic_no = GetCharacterSkillNo(g_lPlayerIndex, magic_index);
		magic_level = GetCharacterSkillLevel(g_lPlayerIndex, magic_index);
	}
    UNLOCK_CHARACTER(g_lPlayerIndex);

    if(magic_index < 0)
        return;

    clear_info_bar(&info_bar);

    sprintf((char *)name, "%s", GetSkillName(magic_no));
    sprintf((char *)info, "~C0%s~C0", GetSkillName(magic_no));
    add_info_bar_string(&info_bar, name, info);

    sprintf((char *)name, "%s:%d.%d", TEXTMSG_NAME_LEVEL, magic_level/10, magic_level%10);
    sprintf((char *)info, "~C0%s:%d.%d~C0", TEXTMSG_NAME_LEVEL, magic_level/10, magic_level%10);
    add_info_bar_string(&info_bar, name, info);

    game_range.get_range(UIMAP_EVENT, id, &sx, &sy, &xl, &yl);
    set_info_bar_range(&info_bar, sx, sy, xl, yl);
    set_info_bar_gap(&info_bar, 8, 8 );
    redraw_info_bar(&info_bar, bitmap);
}


void    redraw_map_ui_magic_quick_info(SLONG sx, SLONG sy, SLONG quick_index, BMP *bitmap)
{
    char    info[16];

    if(quick_index >= 0)
    {
        sprintf((char *)info, "~C0F%d~C0", quick_index+1);
        print12(sx+1, sy+1, (USTR*)info, COPY_PUT_COLOR(SYSTEM_BLUE), bitmap);
    }
}


SLONG   filter_map_quick_magics(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
    SLONG   map_x, map_y;
    SLONG   filter_ok;

    if( (!is_left_quick_magics_ui_visible()) && (!is_right_quick_magics_ui_visible()))
        return  0;

    filter_ok = FALSE;
    switch(message)
    {
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            map_x = map_data.map_sx + mouse_x;
            map_y = map_data.map_sy + mouse_y;
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            set_mouse_hand_position(mouse_x, mouse_y);
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            if(event_type == UIMAP_EVENT && event_id >= UIMAP_ID_QUICK_MAGIC_0 
                && event_id < UIMAP_ID_QUICK_MAGIC_0 + MAX_GAME_SKILL_BASES )
            {
                SLONG   magic_no;
                
                magic_no = mouse_hand.point_no - UIMAP_ID_QUICK_MAGIC_0;
                if( is_left_quick_magics_ui_visible())
                {/*set this magic as current left quick magic*/

                    client_cmd_set_lhand_magic(magic_no);
                    hide_left_quick_magics_ui();
                }
                else if(is_right_quick_magics_ui_visible())
                {/*set this magic as current right quick magic*/

                    client_cmd_set_rhand_magic(magic_no);
                    hide_right_quick_magics_ui();
                }
                filter_ok = TRUE;
            }
            else
            {
                hide_left_quick_magics_ui();
                hide_right_quick_magics_ui();
                filter_ok = FALSE;
            }
        }
        break;
    }
    return  filter_ok;
}


SLONG   is_left_quick_magics_ui_visible(void)
{
    if(uimap_data.show_quick_magics == SHOW_LEFT_QUICK_MAGICS)
        return  TRUE;
    return  FALSE;
}


SLONG   is_right_quick_magics_ui_visible(void)
{
    if(uimap_data.show_quick_magics == SHOW_RIGHT_QUICK_MAGICS)
        return  TRUE;
    return  FALSE;
}


void    show_left_quick_magics_ui(void)
{
    uimap_data.show_quick_magics = SHOW_LEFT_QUICK_MAGICS;
}


void    hide_left_quick_magics_ui(void)
{
    uimap_data.show_quick_magics = SHOW_NONE_QUICK_MAGICS;
}


void    show_right_quick_magics_ui(void)
{
    uimap_data.show_quick_magics = SHOW_RIGHT_QUICK_MAGICS;
}


void    hide_right_quick_magics_ui(void)
{
    uimap_data.show_quick_magics = SHOW_NONE_QUICK_MAGICS;
}


