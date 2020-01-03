/*
**  UIMap.cpp
**  ui for game map.
**
**  Jack, 2002.5.31.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "CRange.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "UI.h"
#include "qqmain.h"
#include "CChat.h"
#include "UIMagicIcon.h"
#include "PosData.h"
#include "UIMapQuickMagic.h"
#include "CmdEvent.h"
#include "Npc.h"
#include "Weather.h"
#include "House.h"
#include "UIMapChat.h"
#include "MainGame.h"
#include "Client_Item.h"
#include "UIShop.h"
#include "UIStore.h"
#include "UIQuitGame.h"
//
#include "NetGE_Mainfunc.h"
#include "uishowmap.h"

/******************************************************************************************************************/
/* DEFINES & STRUCTURES                                                                                           */
/******************************************************************************************************************/
typedef struct tagMINIMAP_DATA 
{
    SLONG   is_loaded;          //是否已經載入內存中
    SLONG   minimap_xl;         //寬度
    SLONG   minimap_yl;         //高度
    BMP*    minimap_bitmap;     //位圖指標
} MINIMAP_DATA, *LPMINIMAP_DATA;


/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
UIIMAGE     *ui_map_left = NULL;
UIIMAGE     *ui_map_right = NULL;
UIIMAGE     *ui_map_mini = NULL;
UIIMAGE     *ui_map_face = NULL;
UIIMAGE     *ui_map_winddir = NULL;
UIIMAGE     *ui_map_shipspeed = NULL;
//
UIMAP_DATA  uimap_data;
UI_HPBAR    ui_hpbar;
MINIMAP_DATA    minimap_data;

/******************************************************************************************************************/
/* MAP UI MAIN FUNCTIONS                                                                                          */
/******************************************************************************************************************/
int     init_map_ui(void)
{
    SLONG   result;

    set_data_file(packed_menu_file);
    result = load_ui_image((USTR*)"menu\\mapleft.cak", &ui_map_left);
    if(TTN_OK != result)
        return  -1;

    set_data_file(packed_menu_file);
    result = load_ui_image((USTR*)"menu\\mapright.cak", &ui_map_right);
    if(TTN_OK != result)
        return  -2;

    set_data_file(packed_menu_file);
    result = load_ui_image((USTR*)"menu\\mapmini.cak", &ui_map_mini);
    if(TTN_OK != result)
        return  -3;

    set_data_file(packed_menu_file);
    result = load_ui_image((USTR*)"menu\\mapface.cak", &ui_map_face);
    if(TTN_OK != result)
        return  -4;

    set_data_file(packed_menu_file);
    result = load_ui_image((USTR*)"menu\\winddir.cak", &ui_map_winddir);
    if(TTN_OK != result)
        return  -5;

    set_data_file(packed_menu_file);
    result = load_ui_image((USTR*)"menu\\shpspeed.cak", &ui_map_shipspeed);
    if(TTN_OK != result)
        return  -6;

    if(0 != init_ui_hpbar())
        return  -7;

    uimap_data.pchat = te_create( UIMAP_CHAT_INPUT_SX + 2, UIMAP_CHAT_INPUT_SY + 4, 
                                  UIMAP_CHAT_INPUT_XL, UIMAP_CHAT_INPUT_YL,
                                  CHAT_INPUT_LEN );
    if ( !uimap_data.pchat )
        return -8;
    
    te_set_single_line( uimap_data.pchat, TRUE );
    te_enable_v_scroll( uimap_data.pchat, TRUE );
    te_set_active( uimap_data.pchat, TRUE );
    return  0;
}


void    active_map_ui(int active)
{
}


void    free_map_ui(void)
{
    te_destroy( uimap_data.pchat );
    uimap_data.pchat = NULL;

    free_ui_image(&ui_map_left);
    free_ui_image(&ui_map_right);
    free_ui_image(&ui_map_mini);
    free_ui_image(&ui_map_face);
    free_ui_image(&ui_map_winddir);
    free_ui_image(&ui_map_shipspeed);
    free_ui_hpbar();
}


SLONG   load_ui_image(USTR *fname, UIIMAGE **ui)
{
    UIIMAGE *tmp = NULL;
    SLONG   result, i, frames, frames2;
    CAKE_FRAME_ANI  *cfa = NULL, *p = NULL;
    CAKE_FRAME  *cf = NULL;

    result = load_cake_frame_ani_from_file((USTR*)fname, &cfa);
    if(TTN_OK != result)
    {
        *ui = NULL;
        return  TTN_NOT_OK;
    }
    if(NULL == (tmp = (UIIMAGE*)malloc(sizeof(UIIMAGE))))
    {
        *ui = NULL;
        return  TTN_NOT_OK;
    }
    memset(tmp, 0, sizeof(UIIMAGE));
    tmp->cfa = cfa;
    frames = count_cake_frames(tmp->cfa);
    frames2 = min(frames, 256);
    for(i=0; i<frames2; i++)
    {
        p = get_specify_cake_frame_ani(tmp->cfa, i);
        tmp->cf[i] = p->cake_frame;
    }
        tmp->hilight_id = 0;
    tmp->active_id = 0;
    tmp->function_id = 0;
    *ui = tmp;

    return  TTN_OK;
}


void    free_ui_image(UIIMAGE **ui)
{
    if(*ui)
    {
        if((*ui)->cfa)
        {
            destroy_cake_frame_ani(&(*ui)->cfa);
        }
        (*ui)->cfa = NULL;
        free(*ui);
    }
    *ui = NULL;
}


void    redraw_map_ui(BMP *bitmap)
{
    UIMAP_DATA  *data = &uimap_data;

    if(g_lPlayerIndex < 0)
        return;

    switch(data->opened_submenu)
    {
    case SUBMENU_STATE:
        redraw_ui_mapstate(0, 0, bitmap);
        redraw_map_ui_left_title(0, 0, UIMAP_ID_TITLE_STATE, bitmap);
        break;
    case SUBMENU_ITEM:
        redraw_ui_mapitem(0, 0, bitmap);
        redraw_map_ui_left_title(0, 0, UIMAP_ID_TITLE_ITEM, bitmap);
        break;
    case SUBMENU_SKILL:
        redraw_ui_mapskill(0, 0, bitmap);
        redraw_map_ui_left_title(0, 0, UIMAP_ID_TITLE_MAGIC, bitmap);
        break;
    case SUBMENU_TASK:
        redraw_ui_maptask(0, 0, bitmap);
        redraw_map_ui_left_title(0, 0, UIMAP_ID_TITLE_TASK, bitmap);
        break;
    case SUBMENU_SHIP:
        redraw_ui_mapship(0, 0, bitmap);
        redraw_map_ui_left_title(0, 0, UIMAP_ID_TITLE_SHIP, bitmap);
        break;
    }
	redraw_ui_shop(0, 0, bitmap);
	redraw_ui_store(0, 0, bitmap);
	redraw_ui_quitgame(0, 0, bitmap);

    // 航海圖, 藏寶圖
    redraw_sm( bitmap );
    //人物肖像..MP..HP..money
    redraw_map_ui_left(bitmap);
    //左右鍵技能..輸入消息...
    redraw_map_ui_right(bitmap);
    //小地圖
    redraw_map_ui_minimap(bitmap);
    redraw_map_ui_manface(bitmap);
    //qq
    redraw_ui_qq(bitmap);

    switch(data->show_quick_magics)
    {
    case SHOW_LEFT_QUICK_MAGICS:
        //左邊快捷技能
        redraw_map_ui_left_quick_magics(bitmap);
        break;
    case SHOW_RIGHT_QUICK_MAGICS:
        //右邊快捷技能
        redraw_map_ui_right_quick_magics(bitmap);
        break;
    }

    if(data->show_chat_records)
    {
        game_chat.redraw(bitmap);
    }

    redraw_mouse_point_info(bitmap);
}


void    refresh_map_ui(void)
{
    UIMAP_DATA  *data = &uimap_data;

    switch(data->opened_submenu)
    {
    case SUBMENU_STATE:
        refresh_ui_mapstate();
        break;
    case SUBMENU_ITEM:
        refresh_ui_mapitem();
        break;
    case SUBMENU_SKILL:
        refresh_ui_mapskill();
        break;
    case SUBMENU_TASK:
        refresh_ui_maptask();
        break;
    case SUBMENU_SHIP:
        refresh_ui_mapship();
        break;
    }
    //
    refresh_ui_qq();
    refresh_map_ui_left();
    refresh_map_ui_right();
    refresh_map_ui_manface();
    refresh_map_ui_minimap();
    //
}


void    init_uimap_data(void)
{
    UIMAP_DATA  *data = &uimap_data;
    SLONG   wind_dir, wind_range;

    data->left_alpha = 255;
    data->left_alpha_update = 0;
    //
    data->right_alpha = 255;
    data->right_alpha_update = 0;
    //
    data->minimap_alpha = 255;
    data->minimap_alpha_update = 0;
    //
    data->manface_y = 0;
    data->manface_alpha = 255;
    data->manface_alpha_update = 0;
    //data->manface_y_update = 0;
    //data->manface_y_limited = -100;
    //
    data->hilight_id = 0;
    data->function_id = 0;
    data->active_id = 0;
    //
    clear_map_chat_input();
    set_maingame_enable_chat_ime(false);
    set_maingame_chat_ime_name((char *)"");
    //
    get_current_weather_wind(&wind_dir, &wind_range);
    get_current_weather_type();
    data->wind_dir = weather_wind_dir_to_ui_wind_dir(wind_dir);
    data->ship_speed = 12;
    set_map_dark(0);
    //
    data->opened_submenu = SUBMENU_NONE;
    //
    data->show_chat_records = FALSE;
    data->show_quick_magics = SHOW_NONE_QUICK_MAGICS;
    //
    //F10 backup flags --------------------------
    data->backuped = 0;
}


/******************************************************************************************************************/
/* MAP UI LEFT                                                                                                    */
/******************************************************************************************************************/
void    redraw_map_ui_left(BMP *bitmap)
{

    if(uimap_data.left_alpha == 255)
    {
        full_redraw_map_ui_left(bitmap);
    }
    else if(uimap_data.left_alpha == 0)
    {
        minimize_redraw_map_ui_left(bitmap);
    }
    else
    {
        fade_redraw_map_ui_left(bitmap);
    }

}

void    fade_redraw_map_ui_left(BMP *bitmap)
{
}


void    minimize_redraw_map_ui_left(BMP *bitmap)
{
    UIIMAGE *data = ui_map_left;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy;

    if(!data)
        return;
    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    id = UIMAP_ID_LEFT_MAXIMIZE;
    frame = UIMAP_LEFT_FRAME_SMALLICON;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


void    full_redraw_map_ui_left(BMP *bitmap)
{
    UIIMAGE *data = ui_map_left;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy, xl, yl;
    SLONG   clip_xl, clip_yl, fight_state;
	ULONG	gold;
    USTR    temp[256];

    if(!data)
        return;
    if(g_lPlayerIndex < 0)
        return;
    fight_state = IsCharacterOnFightState(g_lPlayerIndex);

    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    //(1) background ----------------------------------------------
    id = UIMAP_ID_BKGND;
    frame = UIMAP_LEFT_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    //game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    x = sx + UIMAP_LEFT_BKGND_SX;
    y = sy + UIMAP_LEFT_BKGND_SY;
    xl = UIMAP_LEFT_BKGND_XL;
    yl = UIMAP_LEFT_BKGND_YL;
    game_range.add(x, y, xl, yl, event, id);

    //(2) player's face ---------------------------------------------
    MANFACE_DATA    manface;

    id = UIMAP_ID_PLAYER_FACE;
    x = sx + UIMAP_PLAYER_FACE_SX;
    y = sy + UIMAP_PLAYER_FACE_SY;
    xl = UIMAP_PLAYER_FACE_XL;
    yl = UIMAP_PLAYER_FACE_YL;
    get_character_manface(g_lPlayerIndex, &manface);
    redraw_manface(x-6, y-12, &manface, bitmap);
    game_range.add(x, y, xl, yl, event, id);
    
    //face mask ---------------------
    frame = UIMAP_LEFT_FRAME_FACE_MASK;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);


    //(3) hp bkgnd & hp bar ---------------------------------------
    id = UIMAP_ID_HP;
    frame = UIMAP_LEFT_FRAME_HP_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    frame = UIMAP_LEFT_FRAME_HP_BAR;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(GetCharacterMaxHp(g_lPlayerIndex) <= 0)
        clip_xl = 0;
    else
        clip_xl = GetCharacterHp(g_lPlayerIndex) * cf->rle->w / GetCharacterMaxHp(g_lPlayerIndex);
    clip_yl = cf->rle->h;
    clip_direct_put_rle(x, y, x, y, clip_xl, clip_yl, cf->rle, bitmap);

    //(4) mp bkgnd & mp bar ----------------------------------------
    id = UIMAP_ID_MP;
    frame = UIMAP_LEFT_FRAME_MP_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    frame = UIMAP_LEFT_FRAME_MP_BAR;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(GetCharacterMaxMp(g_lPlayerIndex) <= 0)
        clip_xl = 0;
    else
        clip_xl = GetCharacterMp(g_lPlayerIndex) * cf->rle->w / GetCharacterMaxMp(g_lPlayerIndex);
    clip_yl = cf->rle->h;
    clip_direct_put_rle(x, y, x, y, clip_xl, clip_yl, cf->rle, bitmap);

    //(5) gold -----------------------------------------------------
    id = UIMAP_ID_GOLD;
    gold = GetCharacterBodyMoney(g_lPlayerIndex);
    sprintf((char*)temp, "~C3%-8d~C0", gold);
    x = sx + UIMAP_GOLD_BAR_SX;
    y = sy + UIMAP_GOLD_BAR_SY;
    xl = UIMAP_GOLD_BAR_XL;
    yl = UIMAP_GOLD_BAR_YL;
    print12(x + 48, y + 8, (USTR*)temp, PEST_PUT, bitmap);
    game_range.add(x, y, xl, yl, event, id);

    //(6) minimize button ------------------------------------------
    id = UIMAP_ID_LEFT_MINIMIZE;
    frame = UIMAP_LEFT_FRAME_MINIMIZE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);


    //(7a) fight state button --------------------------------------------
    id = UIMAP_ID_FIGHT_STATE;
    if(fight_state == FALSE)
        frame = UIMAP_LEFT_FRAME_FIGHT_OFF;
    else
        frame = UIMAP_LEFT_FRAME_FIGHT_ON;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(7b) next fight state button --------------------------------------
    id = UIMAP_ID_FIGHT_NEXT_STATE;
    frame = UIMAP_LEFT_FRAME_FIGHT_NEXT_STATE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(7c) previous fight state button ----------------------------------
    id = UIMAP_ID_FIGHT_PREV_STATE;
    frame = UIMAP_LEFT_FRAME_FIGHT_PREV_STATE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(8) state button ----------------------------------------------
    id = UIMAP_ID_STATE;
    frame = UIMAP_LEFT_FRAME_STATE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(9) item button ----------------------------------------------
    id = UIMAP_ID_ITEM;
    frame = UIMAP_LEFT_FRAME_ITEM;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(10) magic button ----------------------------------------------
    id = UIMAP_ID_MAGIC;
    frame = UIMAP_LEFT_FRAME_MAGIC;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(11) task button ----------------------------------------------
    id = UIMAP_ID_TASK;
    frame = UIMAP_LEFT_FRAME_TASK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(12) ship button ----------------------------------------------
    id = UIMAP_ID_SHIP;
    frame = UIMAP_LEFT_FRAME_SHIP;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

}


void    redraw_map_ui_left_title(SLONG sx, SLONG sy, SLONG active_id, BMP *bitmap)
{
    UIIMAGE *data = ui_map_left;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y;

    if(!data)
        return;
    if(g_lPlayerIndex < 0)
        return;

    event = UIMAP_EVENT;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    //title state -------------------------------------------------
    id = UIMAP_ID_TITLE_STATE;
    frame = UIMAP_LEFT_FRAME_TITLE_STATE;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(id == active_id)
        put_rle(x, y, cf->rle, bitmap);
    else
        gray_put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //title item --------------------------------------------------
    id = UIMAP_ID_TITLE_ITEM;
    frame = UIMAP_LEFT_FRAME_TITLE_ITEM;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(id == active_id)
        put_rle(x, y, cf->rle, bitmap);
    else
        gray_put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //title magic -------------------------------------------------
    id = UIMAP_ID_TITLE_MAGIC;
    frame = UIMAP_LEFT_FRAME_TITLE_MAGIC;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(id == active_id)
        put_rle(x, y, cf->rle, bitmap);
    else
        gray_put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //title task --------------------------------------------------
    id = UIMAP_ID_TITLE_TASK;
    frame = UIMAP_LEFT_FRAME_TITLE_TASK;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(id == active_id)
        put_rle(x, y, cf->rle, bitmap);
    else
        gray_put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //title ship --------------------------------------------------
    id = UIMAP_ID_TITLE_SHIP;
    frame = UIMAP_LEFT_FRAME_TITLE_SHIP;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(id == active_id)
        put_rle(x, y, cf->rle, bitmap);
    else
        gray_put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


void    refresh_map_ui_left(void)
{
    UIMAP_DATA  *data = &uimap_data;

    if(data->left_alpha_update == 1)
    {
        // Jack. [09:17,9/18/2002]
        /*
        data->left_alpha += 32;
        if(data->left_alpha >= 255)
        {
            data->left_alpha = 255;
            data->left_alpha_update = 0;
        }
        */
        data->left_alpha = 255;
        data->left_alpha_update = 0;
    }
    else if(data->left_alpha_update == -1)
    {
        // Jack. [09:17,9/18/2002]
        /*
        data->left_alpha -= 32;
        if(data->left_alpha <= 0)
        {
            data->left_alpha = 0;
            data->left_alpha_update = 0;
        }
        */
        data->left_alpha = 0;
        data->left_alpha_update = 0;
    }
}


void    minimize_map_ui_left(void)
{
    uimap_data.left_alpha_update = 0;
    uimap_data.left_alpha = 0;
}


void    maximize_map_ui_left(void)
{
    uimap_data.left_alpha_update = 0;
    uimap_data.left_alpha = 255;
}

/******************************************************************************************************************/
/* MAP UI RIGHT                                                                                                   */
/******************************************************************************************************************/
void    redraw_map_ui_right(BMP *bitmap)
{
    if(uimap_data.right_alpha == 255)
    {
        full_redraw_map_ui_right(bitmap);
    }
    else if(uimap_data.right_alpha == 0)
    {
        minimize_redraw_map_ui_right(bitmap);
    }
    else
    {
        fade_redraw_map_ui_right(bitmap);
    }
}

void    fade_redraw_map_ui_right(BMP *bitmap)
{
}


void    minimize_redraw_map_ui_right(BMP *bitmap)
{
    UIIMAGE *data = ui_map_right;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy;

    if(!data)
        return;
    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    //最大化按鈕
    id = UIMAP_ID_RIGHT_MAXIMIZE;
    frame = UIMAP_RIGHT_FRAME_SMALLICON;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //聊天輸入

    // ZZH 2003.5.9
    // 使用 qqedit 獲得輸入消息
    
/*
    if(is_map_chat_input_active())
    {
        x = sx + UIMAP_CHAT_INPUT_SX;
        y = sy + UIMAP_CHAT_INPUT_SY;
        xl = UIMAP_CHAT_INPUT_XL;
        yl = UIMAP_CHAT_INPUT_YL;
        alpha_put_bar(x, y, xl, yl, SYSTEM_BLUE, bitmap, 128);
        temp_char = uimap_data.chat_input[uimap_data.chat_show_index + uimap_data.chat_show_len];
        uimap_data.chat_input[uimap_data.chat_show_index + uimap_data.chat_show_len] = 0x00;
        sprintf((char *)info, "~C0%s~C0", &uimap_data.chat_input[uimap_data.chat_show_index]);
        print12(x + 4, y + 4, (USTR*)info, PEST_PUT, bitmap);
        if(is_map_chat_input_active())
        {
            put_bar(x + 4 + (uimap_data.chat_input_index-uimap_data.chat_show_index)*6 - 1, y+2, 2, 
                12 + 4, SYSTEM_RED, bitmap);
        }
        uimap_data.chat_input[uimap_data.chat_show_index + uimap_data.chat_show_len] = temp_char;
    }
*/

    redraw_te( uimap_data.pchat, bitmap );
}


void    full_redraw_map_ui_right(BMP *bitmap)
{
    UIIMAGE *data = ui_map_right;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy, xl, yl;
    SLONG   i, left_magic_no, right_magic_no, icon_index, left_quick_index, right_quick_index;
    SLONG   is_fight;
    SLONG   r_state, r_ticks, r_total;
    TPOS_ITEM	sash_item[MAX_CHARACTER_SASH_ITEMS];

    if(!data)
        return;
    if(g_lPlayerIndex < 0)
        return;

    LOCK_CHARACTER(g_lPlayerIndex);
    is_fight = IsCharacterOnFightState(g_lPlayerIndex);
    left_magic_no = GetCharacterLeftSkill(g_lPlayerIndex);
    right_magic_no = GetCharacterRightSkill(g_lPlayerIndex);
    left_quick_index = FindCharacterFnSkillIndex(g_lPlayerIndex, left_magic_no, LEFT_HAND);
    right_quick_index = FindCharacterFnSkillIndex(g_lPlayerIndex, right_magic_no, RIGHT_HAND);
    for(i=0; i<4; i++)
    {
        GetCharacterSashItem(g_lPlayerIndex, i, &sash_item[i]);
    }
	r_state = GetCharacterRightHandMagicState(g_lPlayerIndex);
	r_ticks = GetCharacterRightHandMagicCurrentTicks(g_lPlayerIndex);
	r_total = GetCharacterRightHandMagicTotalTicks(g_lPlayerIndex);
    UNLOCK_CHARACTER(g_lPlayerIndex);

    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    //(1) background ----------------------------------------------
    id = UIMAP_ID_BKGND;
    frame = UIMAP_RIGHT_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    //game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    x = sx + UIMAP_RIGHT_BKGND_SX;
    y = sy + UIMAP_RIGHT_BKGND_SY;
    xl = UIMAP_RIGHT_BKGND_XL;
    yl = UIMAP_RIGHT_BKGND_YL;
    game_range.add(x, y, xl, yl, event, id);

    //(2) left quick magic -----當前的左鍵使用的技能----------------------------------
    id = UIMAP_ID_LEFT_QUICK_MAGIC;
    x = sx + UIMAP_LEFT_QUICK_MAGIC_SX;
    y = sy + UIMAP_LEFT_QUICK_MAGIC_SY;
    xl = UIMAP_LEFT_QUICK_MAGIC_XL;
    yl = UIMAP_LEFT_QUICK_MAGIC_YL;
    game_range.add(x, y, xl, yl, event, id);
    icon_index = GetSkillIconIndex(left_magic_no);
    if( (is_fight && IsFightSkill(left_magic_no, 0)) ||
        (!is_fight) && IsPeaceSkill(left_magic_no, 0) )
    {
        redraw_magic_icon_image(x + xl/2, y + yl/2, icon_index, bitmap, MAGIC_ICON_NORMAL);
    }
    else
    {
        redraw_magic_icon_image(x + xl/2, y + yl/2, icon_index, bitmap, MAGIC_ICON_INVALID);
    }
    redraw_map_ui_magic_quick_info(x, y, left_quick_index, bitmap);

    //(3) right quick magic -----當前右鍵使用的技能----------------------------------
    id = UIMAP_ID_RIGHT_QUICK_MAGIC;
    x = sx + UIMAP_RIGHT_QUICK_MAGIC_SX;
    y = sy + UIMAP_RIGHT_QUICK_MAGIC_SY;
    xl = UIMAP_RIGHT_QUICK_MAGIC_XL;
    yl = UIMAP_RIGHT_QUICK_MAGIC_YL;
    game_range.add(x, y, xl, yl, event, id);
    icon_index = GetSkillIconIndex(right_magic_no);
    if( (is_fight && IsFightSkill(right_magic_no, 0)) ||
        (!is_fight) && IsPeaceSkill(right_magic_no, 0) )
    {
        redraw_magic_icon_image_with_state(x + xl/2, y + yl/2, icon_index, r_state, r_ticks, r_total, bitmap);
    }
    else
    {
        redraw_magic_icon_image(x + xl/2, y + yl/2, icon_index, bitmap, MAGIC_ICON_INVALID);
    }
    redraw_map_ui_magic_quick_info(x, y, right_quick_index, bitmap);

    //(4) chat input -----------------------------------------------
    // ZZH 2003.5.9
/*
    id = UIMAP_ID_CHAT_INPUT;
    x = sx + UIMAP_CHAT_INPUT_SX;
    y = sy + UIMAP_CHAT_INPUT_SY;
    xl = UIMAP_CHAT_INPUT_XL;
    yl = UIMAP_CHAT_INPUT_YL;
    temp_char = uimap_data.chat_input[uimap_data.chat_show_index + uimap_data.chat_show_len];
    uimap_data.chat_input[uimap_data.chat_show_index + uimap_data.chat_show_len] = 0x00;
    sprintf((char *)info, "~C3%s~C0", &uimap_data.chat_input[uimap_data.chat_show_index]);
    print12(x + 4, y + 4, (USTR*)info, PEST_PUT, bitmap);
    if(is_map_chat_input_active())
    {
        put_bar(x + 4 + (uimap_data.chat_input_index-uimap_data.chat_show_index)*6 - 1, y+2, 2, 
            12 + 4, SYSTEM_RED, bitmap);
    }
    uimap_data.chat_input[uimap_data.chat_show_index + uimap_data.chat_show_len] = temp_char;
    game_range.add(x, y, xl, yl, event, id);
*/
    redraw_te( uimap_data.pchat, bitmap );

    //(5) quick item 0 ---------------------------------------------
    id = UIMAP_ID_QUICK_ITEM_0;
    x = sx + UIMAP_QUICK_ITEM_0_SX;
    y = sy + UIMAP_QUICK_ITEM_0_SY;
    xl = UIMAP_QUICK_ITEM_0_XL;
    yl = UIMAP_QUICK_ITEM_0_YL;
    if(! IsItemNone(&sash_item[0]))
    {
        icon_index = GetItemIconIndex(&sash_item[0]);
        redraw_item_icon_image(x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon_index, bitmap);
    }
    game_range.add(x, y, xl, yl, event, id);

    //(6) quick item 1 ---------------------------------------------
    id = UIMAP_ID_QUICK_ITEM_1;
    x = sx + UIMAP_QUICK_ITEM_1_SX;
    y = sy + UIMAP_QUICK_ITEM_1_SY;
    xl = UIMAP_QUICK_ITEM_1_XL;
    yl = UIMAP_QUICK_ITEM_1_YL;
    if(! IsItemNone(&sash_item[1]))
    {
        icon_index = GetItemIconIndex(&sash_item[1]);
        redraw_item_icon_image(x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon_index, bitmap);
    }
    game_range.add(x, y, xl, yl, event, id);

    //(7) quick item 2 ---------------------------------------------
    id = UIMAP_ID_QUICK_ITEM_2;
    x = sx + UIMAP_QUICK_ITEM_2_SX;
    y = sy + UIMAP_QUICK_ITEM_2_SY;
    xl = UIMAP_QUICK_ITEM_2_XL;
    yl = UIMAP_QUICK_ITEM_2_YL;
    if(! IsItemNone(&sash_item[2]))
    {
        icon_index = GetItemIconIndex(&sash_item[2]);
        redraw_item_icon_image(x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon_index, bitmap);
    }
    game_range.add(x, y, xl, yl, event, id);

    //(8) quick item 3 ---------------------------------------------
    id = UIMAP_ID_QUICK_ITEM_3;
    x = sx + UIMAP_QUICK_ITEM_3_SX;
    y = sy + UIMAP_QUICK_ITEM_3_SY;
    xl = UIMAP_QUICK_ITEM_3_XL;
    yl = UIMAP_QUICK_ITEM_3_YL;
    if(! IsItemNone(&sash_item[3]))
    {
        icon_index = GetItemIconIndex(&sash_item[3]);
        redraw_item_icon_image(x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon_index, bitmap);
    }
    game_range.add(x, y, xl, yl, event, id);

    //(9) minimize button ------------------------------------------
    id = UIMAP_ID_RIGHT_MINIMIZE;
    frame = UIMAP_RIGHT_FRAME_MINIMIZE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(10) chat record button --------------------------------------
    id = UIMAP_ID_CHAT_RECORD;
    frame = UIMAP_RIGHT_FRAME_CHAT_RECORD;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(11) address book button --------------------------------------
    id = UIMAP_ID_ADDRESS_BOOK;
    frame = UIMAP_RIGHT_FRAME_ADDRESS_BOOK;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

}


void    refresh_map_ui_right(void)
{
    UIMAP_DATA  *data = &uimap_data;

    if(data->right_alpha_update == 1)
    {
        // Jack. [09:18,9/18/2002]
        /*
        data->right_alpha += 32;
        if(data->right_alpha >= 255)
        {
            data->right_alpha = 255;
            data->right_alpha_update = 0;
        }
        */
        data->right_alpha = 255;
        data->right_alpha_update = 0;
    }
    else if(data->right_alpha_update == -1)
    {
        // Jack. [09:18,9/18/2002]
        /*
        data->right_alpha -= 32;
        if(data->right_alpha <= 0)
        {
            data->right_alpha = 0;
            data->right_alpha_update = 0;
        }
        */
        data->right_alpha = 0;
        data->right_alpha_update = 0;
    }
}


void    minimize_map_ui_right(void)
{
    uimap_data.right_alpha_update = 0;
    uimap_data.right_alpha = 0;
}


void    maximize_map_ui_right(void)
{
    uimap_data.right_alpha_update = 0;
    uimap_data.right_alpha = 255;
}


/******************************************************************************************************************/
/* MAP UI MINIMAP                                                                                                 */
/******************************************************************************************************************/
void    minimize_redraw_map_ui_minimap(BMP *bitmap)
{
    UIIMAGE *data = ui_map_mini;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy;

    if(!data)
        return;
    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    id = UIMAP_ID_MINIMAP_MAXIMIZE;
    
    // Zhang Zhaohui 2003.5.8
    // frame = UIMAP_MINIMAP_FRAME_SMALLICON;
    frame = UIMAP_MINIMAP_FRAME_MAXIMIZE ;

    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


void    fade_redraw_map_ui_minimap(BMP *bitmap)
{
}


void    full_redraw_map_ui_minimap(BMP *bitmap)
{
    UIIMAGE *data = ui_map_mini;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy, xl, yl, i;

    if(!data)
        return;
    if(g_lPlayerIndex < 0)
        return;

    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    //(0) redraw minimap first ------------------------------------
    redraw_minimap(bitmap);

    //(1) background ----------------------------------------------
    id = UIMAP_ID_BKGND;
    frame = UIMAP_MINIMAP_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    //game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    x = sx + UIMAP_MINIMAP_BKGND_SX;
    y = sy + UIMAP_MINIMAP_BKGND_SY;
    xl = UIMAP_MINIMAP_BKGND_XL;
    yl = UIMAP_MINIMAP_BKGND_YL;
    // Jack. [7/22/2002]
    //game_range.add(x, y, xl, yl, event, id);

    //(2) minimize ------------------------------------------------
    id = UIMAP_ID_MINIMAP_MINIMIZE;
    frame = UIMAP_MINIMAP_FRAME_MINIMIZE;

// Zhaohui 2003.5.8
//    if(data->active_id == id)
//        frame += 2;
//    else if(data->hilight_id == id)

    if ( data->active_id == id )
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) ship speed ----------------------------------------------
    id = UIMAP_ID_SHIP_SPEED;
    for(i=0; i<uimap_data.ship_speed; i++)
    {
        frame = UIMAP_MINIMAP_FRAME_SHIP_SPEED_0 + i;
        cf = ui_map_shipspeed->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }

    //(4) wind dir ------------------------------------------------
    SLONG   weather_wind_dir;
    SLONG   ui_wind_dir;

    get_current_weather_wind(&weather_wind_dir, NULL);
    ui_wind_dir = weather_wind_dir_to_ui_wind_dir(weather_wind_dir);
    if(uimap_data.wind_dir < ui_wind_dir)
    {
        uimap_data.wind_dir += 5;
        if(uimap_data.wind_dir > ui_wind_dir)
            uimap_data.wind_dir = ui_wind_dir;
    }
    else if(uimap_data.wind_dir > ui_wind_dir)
    {
        uimap_data.wind_dir -= 5;
        if(uimap_data.wind_dir < ui_wind_dir)
            uimap_data.wind_dir = ui_wind_dir;
    }
    id = UIMAP_ID_WIND_DIRECTION;
    i = uimap_data.wind_dir / 5 + UIMAP_MINIMAP_FRAME_WIND_DIR_0;
    if(i>=0 && i < 72)
    {
        frame = i * 2;
        cf = ui_map_winddir->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);


        frame = i * 2 + 1;
        cf = ui_map_winddir->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
/*
    //(5) weather --------------------------------------------------
    id = UIMAP_ID_WEATHER;
    i = get_current_weather_type();
    if(i >= 0 && i < 5)
    {
        frame = UIMAP_MINIMAP_FRAME_WEATHER_0 + i;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);

        x = sx + UIMAP_MINIMAP_WEATHER_SX;
        y = sy + UIMAP_MINIMAP_WEATHER_SY;
        xl = UIMAP_MINIMAP_WEATHER_XL;
        yl = UIMAP_MINIMAP_WEATHER_YL;
        game_range.add(x, y, xl, yl, event, id);
    }
*/
    // (5) System Setting ---------------------------------------
    id = UIMAP_ID_SETTING;
    frame = UIMAP_MINIMAP_FRAME_SETTING;

    if ( data->active_id == id )
        frame += 2;
    else if ( data->hilight_id == id )
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

}


void    redraw_map_ui_minimap(BMP *bitmap)
{
    if(uimap_data.minimap_alpha == 255)
    {
        full_redraw_map_ui_minimap(bitmap);
    }
    else if(uimap_data.minimap_alpha == 0)
    {
        minimize_redraw_map_ui_minimap(bitmap);
    }
    else
    {
        fade_redraw_map_ui_minimap(bitmap);
    }
}


void    refresh_map_ui_minimap(void)
{
    UIMAP_DATA  *data = &uimap_data;

    if(data->minimap_alpha_update == 1)
    {
        // Jack. [09:18,9/18/2002]
        /*
        data->minimap_alpha += 32;
        if(data->minimap_alpha >= 255)
        {
            data->minimap_alpha = 255;
            data->minimap_alpha_update = 0;
        }
        */
        data->minimap_alpha = 255;
        data->minimap_alpha_update = 0;
    }
    else if(data->minimap_alpha_update == -1)
    {
        // Jack. [09:19,9/18/2002]
        /*
        data->minimap_alpha -= 32;
        if(data->minimap_alpha <= 0)
        {
            data->minimap_alpha = 0;
            data->minimap_alpha_update = 0;
        }
        */
        data->minimap_alpha = 0;
        data->minimap_alpha_update = 0;
    }

    //(2) check manface update -----------------------------------------
}


void    minimize_map_ui_minimap(void)
{
    uimap_data.minimap_alpha_update = 0;
    uimap_data.minimap_alpha = 0;
}


void    maximize_map_ui_minimap(void)
{
    uimap_data.minimap_alpha_update = 0;
    uimap_data.minimap_alpha = 255;
}



/******************************************************************************************************************/
/* MAP UI MANFACE                                                                                                 */
/******************************************************************************************************************/
void    redraw_map_ui_manface(BMP *bitmap)
{
    if(uimap_data.manface_alpha == 255)
    {
        full_redraw_map_ui_manface(bitmap);
    }
    else if(uimap_data.manface_alpha == 0)
    {
        minimize_redraw_map_ui_manface(bitmap);
    }
    else
    {
        fade_redraw_map_ui_manface(bitmap);
    }
}


void    fade_redraw_map_ui_manface(BMP *bitmap)
{
}


void    minimize_redraw_map_ui_manface(BMP *bitmap)
{
    UIIMAGE *data = ui_map_face;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy;

    if(!data)
        return;
    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;

    id = UIMAP_ID_MANFACE_MAXIMIZE;
    //frame = UIMAP_MANFACE_FRAME_SMALLICON;
    frame = UIMAP_FACE_FRAME_MINIMIZE;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    //y = sy + cf->frame_ry;
    y = sy + 0;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


void    full_redraw_map_ui_manface(BMP *bitmap)
{
    UIIMAGE *data = ui_map_face;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y, sx, sy;//, xl, yl;
    MANFACE_DATA    manface;
    SLONG career, sex, eyes, mouth, manchar, max_hp, hp;
    SLONG i, di = 0;
    SLONG str_len;
    CHAR *name = NULL;

    if(!data)
        return;
    if(g_lPlayerIndex < 0)
        return;

    event = UIMAP_EVENT;
    sx = 0;
    sy = 0;
    data->active_id = uimap_data.active_id;
    data->hilight_id = uimap_data.hilight_id;
    data->function_id = uimap_data.function_id;
    
    for ( i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++ )
    {
        
        LOCK_CHARACTER( g_lPlayerIndex );
        name = GetCharacterTeamMemberMainName( g_lPlayerIndex, i );
        UNLOCK_CHARACTER( g_lPlayerIndex );
        str_len = strlen( name );

        // 跳過自己
        if ( str_len > 0 && di == 0)
        {
            if ( strcmp( name, g_szPlayerMainName ) == 0 )
            {
                di = 1;
                continue;
            }
        }

        frame = UIMAP_FACE_FRAME_MANFACE_0 + ( i - di ) * 2;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle( x, y, cf->rle, bitmap );
        
        //////////////////////////////////////////////////////////////////

        if ( str_len > 0 )
        {

            x = sx + UIMAP_MANFACE_0_SX + UIMAP_MANFACE_DX * ( i - di );
            y = sy + UIMAP_MANFACE_0_SY;
            
            LOCK_CHARACTER( g_lPlayerIndex );
            career = GetCharacterTeamMemberCareer( g_lPlayerIndex, i );
            sex    = GetCharacterTeamMemberSex( g_lPlayerIndex, i );
            eyes   = GetCharacterTeamMemberEyes( g_lPlayerIndex, i );
            mouth  = GetCharacterTeamMemberMouth( g_lPlayerIndex, i );
            max_hp = GetCharacterTeamMemberMaxHp( g_lPlayerIndex, i );
            hp     = GetCharacterTeamMemberHp( g_lPlayerIndex, i );
            UNLOCK_CHARACTER( g_lPlayerIndex );

            manchar = get_character_main_face( career, sex);

            set_manface( &manface, manchar, eyes, mouth );

            //////////////////////////////////////////////////////////////////
            // TODO: 添加人物效果和 HP

            // redraw_manface(x, y, &manface, bitmap);
            redraw_scale_manface( x, y, UIMAP_MANFACE_W, UIMAP_MANFACE_H, &manface, bitmap );

            id = UIMAP_ID_MANFACE_0 + i * 10;
            game_range.add( x, y, UIMAP_MANFACE_W, UIMAP_MANFACE_H, event, id );
        }


        //////////////////////////////////////////////////////////////////

        frame = UIMAP_FACE_FRAME_MANFACE_0 + i * 2  + 1;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle( x, y, cf->rle, bitmap );
    }

    //(7) minimize -----------------------------------------------
    id = UIMAP_ID_MANFACE_MINIMIZE;
    frame = UIMAP_FACE_FRAME_MINIMIZE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


void    refresh_map_ui_manface(void)
{
    UIMAP_DATA  *data = &uimap_data;

    if(data->manface_alpha_update == 1)
    {
        // Jack. [09:19,9/18/2002]
        /*
        data->manface_alpha += 32;
        if(data->manface_alpha >= 255)
        {
            data->manface_alpha = 255;
            data->manface_alpha_update = 0;
        }
        */
        data->manface_alpha = 255;
        data->manface_alpha_update = 0;
    }
    else if(data->manface_alpha_update == -1)
    {
        // Jack. [09:19,9/18/2002]
        /*
        data->manface_alpha -= 32;
        if(data->manface_alpha <= 0)
        {
            data->manface_alpha = 0;
            data->manface_alpha_update = 0;
        }
        */
        data->manface_alpha = 0;
        data->manface_alpha_update = 0;
    }
}



void    minimize_map_ui_manface(void)
{
    uimap_data.manface_alpha_update = 0;
    uimap_data.manface_alpha = 0;
}


void    maximize_map_ui_manface(void)
{
    uimap_data.manface_alpha_update = 0;
    uimap_data.manface_alpha = 255;
}


/******************************************************************************************************************/
/* MOUSE POINT FUNCTIONS                                                                                          */
/******************************************************************************************************************/
void    redraw_map_ui_mouse_point_info(SLONG id, BMP *bitmap)
{
	static USTR	info[256];
	static USTR	name[128];
    static CHAR    *p = NULL;
    static SLONG level = 0;
    static SLONG last_id = 0;
    static SLONG len = 0;

    switch(id)
    {
    case UIMAP_ID_HP:
        if(g_lPlayerIndex >= 0)
        {
            SLONG	hp, hp_limit;

            hp = GetCharacterHp(g_lPlayerIndex);
            hp_limit = GetCharacterMaxHp(g_lPlayerIndex);
            
            sprintf((char *)name, TEXTMSG_MENU_HP, hp, hp_limit);
            sprintf((char *)info, "~C0%s~C0", name);
            redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        }
        break;
    case UIMAP_ID_MP:
        if(g_lPlayerIndex >= 0)
        {
            SLONG	mp, mp_limit;

            mp = GetCharacterMp(g_lPlayerIndex);
            mp_limit = GetCharacterMaxMp(g_lPlayerIndex);
            
            sprintf((char *)name, TEXTMSG_MENU_MP, mp, mp_limit);
            sprintf((char *)info, "~C0%s~C0", name);
            redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        }
        break;
    case UIMAP_ID_GOLD:
        break;
    case UIMAP_ID_LEFT_MINIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MINIMIZE, (USTR*)TEXTMSG_MENU_MINIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_PLAYER_FACE:
        if(g_lPlayerIndex >= 0)
        {
            SLONG   level;

            level = GetCharacterLevel(g_lPlayerIndex);
            sprintf((char *)name, "%s %d", TEXTMSG_NAME_LEVEL, level + 1);
            sprintf((char *)info, "~C0%s %d~C0", TEXTMSG_NAME_LEVEL, level + 1);
            redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        }
        break;
    case UIMAP_ID_FIGHT_STATE:
        break;
    case UIMAP_ID_STATE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_STATE, (USTR*)TEXTMSG_MENU_STATE_INFO, bitmap);
        break;
    case UIMAP_ID_ITEM:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_ITEM, (USTR*)TEXTMSG_MENU_ITEM_INFO, bitmap);
        break;
    case UIMAP_ID_MAGIC:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MAGIC, (USTR*)TEXTMSG_MENU_MAGIC_INFO, bitmap);
        break;
    case UIMAP_ID_TASK:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_TASK, (USTR*)TEXTMSG_MENU_TASK_INFO, bitmap);
        break;
    case UIMAP_ID_SHIP:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_SHIP, (USTR*)TEXTMSG_MENU_SHIP_INFO, bitmap);
        break;
    case UIMAP_ID_LEFT_QUICK_MAGIC:
        {
            SLONG   magic_no;

            LOCK_CHARACTER(g_lPlayerIndex);
            magic_no = GetCharacterLeftSkill(g_lPlayerIndex);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            sprintf((char *)name, "%s", GetSkillName(magic_no));
            sprintf((char *)info, "~C0%s~C0", GetSkillName(magic_no));
            redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        }
        break;
    case UIMAP_ID_RIGHT_QUICK_MAGIC:
        {
            SLONG   magic_no;

            LOCK_CHARACTER(g_lPlayerIndex);
            magic_no = GetCharacterRightSkill(g_lPlayerIndex);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            sprintf((char *)name, "%s", GetSkillName(magic_no));
            sprintf((char *)info, "~C0%s~C0", GetSkillName(magic_no));
            redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        }
        break;
    case UIMAP_ID_CHAT_INPUT:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_CHAT_INPUT, 
            (USTR*)TEXTMSG_MENU_CHAT_INPUT_INFO, bitmap);
        break;
    case UIMAP_ID_ADDRESS_BOOK:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_ADDRESS_BOOK, 
            (USTR*)TEXTMSG_MENU_ADDRESS_BOOK_INFO, bitmap);
        break;
    case UIMAP_ID_QUICK_ITEM_0:
        break;
    case UIMAP_ID_QUICK_ITEM_1:
        break;
    case UIMAP_ID_QUICK_ITEM_2:
        break;
    case UIMAP_ID_QUICK_ITEM_3:
        break;
    case UIMAP_ID_RIGHT_MINIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MINIMIZE, (USTR*)TEXTMSG_MENU_MINIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_CHAT_RECORD:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_CHAT_RECORD, 
            (USTR*)TEXTMSG_MENU_CHAT_RECORD_INFO, bitmap);
        break;
    case UIMAP_ID_MANFACE_0:
    case UIMAP_ID_MANFACE_1:
    case UIMAP_ID_MANFACE_2:
    case UIMAP_ID_MANFACE_3:
    case UIMAP_ID_MANFACE_4:
    case UIMAP_ID_MANFACE_5:
    case UIMAP_ID_MANFACE_6:
        if ( last_id != id )
        {
            LOCK_CHARACTER( g_lPlayerIndex );
            p = GetCharacterTeamMemberMainName( g_lPlayerIndex, ( id - UIMAP_ID_MANFACE_0 )/10 );
            level = GetCharacterTeamMemberLevel( g_lPlayerIndex, ( id - UIMAP_ID_MANFACE_0 )/10 ) + 1;
            sprintf( (CHAR*)name, "%s/%d", p, level );
            UNLOCK_CHARACTER( g_lPlayerIndex );

            len = strlen( p );
        }

        if ( len )
        {
            sprintf((char *)info, "~C0%s~C0", name );
            redraw_event_info_bar( UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap );
        }
        break;
/*    case UIMAP_ID_MANFACE_0:
        sprintf((char *)name, "TEAM PLAYER 0");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_MANFACE_1:
        sprintf((char *)name, "TEAM PLAYER 1");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_MANFACE_2:
        sprintf((char *)name, "TEAM PLAYER 2");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_MANFACE_3:
        sprintf((char *)name, "TEAM PLAYER 3");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_MANFACE_4:
        sprintf((char *)name, "TEAM PLAYER 4");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_MANFACE_5:
        sprintf((char *)name, "TEAM PLAYER 5");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_MANFACE_6:
        sprintf((char *)name, "TEAM PLAYER 6");
        sprintf((char *)info, "~C0%s~C0", name);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
*/
    case UIMAP_ID_MANFACE_MINIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MINIMIZE, (USTR*)TEXTMSG_MENU_MINIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_MINIMAP_MINIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MINIMIZE, (USTR*)TEXTMSG_MENU_MINIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_MINIMAP_MAXIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MAXIMIZE, (USTR*)TEXTMSG_MENU_MAXIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_LEFT_MAXIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MAXIMIZE, (USTR*)TEXTMSG_MENU_MAXIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_RIGHT_MAXIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MAXIMIZE, (USTR*)TEXTMSG_MENU_MAXIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_MANFACE_MAXIMIZE:
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)TEXTMSG_MENU_MAXIMIZE, (USTR*)TEXTMSG_MENU_MAXIMIZE_INFO, bitmap);
        break;
    case UIMAP_ID_SHIP_SPEED:
        sprintf((char *)name, "%s %d", TEXTMSG_NAME_SHIPSPEED, uimap_data.ship_speed);
        sprintf((char *)info, "~C0%s %d~C0", TEXTMSG_NAME_SHIPSPEED, uimap_data.ship_speed);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_WIND_DIRECTION:
        sprintf((char *)name, "%s %d", TEXTMSG_NAME_WINDDIR, uimap_data.wind_dir);
        sprintf((char *)info, "~C0%s %d~C0", TEXTMSG_NAME_WINDDIR, uimap_data.wind_dir);
        redraw_event_info_bar(UIMAP_EVENT, id, (USTR*)name, (USTR*)info, bitmap);
        break;
    case UIMAP_ID_SETTING:
        break;
    case UIMAP_ID_MINIMAP:
        break;
    default:
        if(id >= UIMAP_ID_QUICK_MAGIC_0 && id < UIMAP_ID_QUICK_MAGIC_0 + MAX_GAME_SKILL_BASES)
        {
            redraw_map_ui_quick_magic_mouse_point_info(id, bitmap);
        }
        break;
    }
    last_id = id;
}


SLONG   get_map_dark(void)
{
    return  uimap_data.map_dark;
}


void    set_map_dark(SLONG dark)
{
    if(dark >= 0 && dark < 256)
    {
        uimap_data.map_dark = dark;
    }
}


SLONG   is_maingame_enable_chat_ime(void)
{
//    return  uimap_data.enable_chat_ime;
    return FALSE;
}

void    set_maingame_enable_chat_ime(SLONG flag)
{
//    uimap_data.enable_chat_ime = flag ? true : false;
}


void    set_maingame_chat_ime_name(char *name)
{
//    strcpy((char *)uimap_data.chat_ime_name, (const char *)name);
}


USTR*   get_maingame_chat_ime_name(void)
{
//    return  (USTR*)uimap_data.chat_ime_name;
    return NULL;
}


SLONG   get_show_chat_records_flag(void)
{
    return  uimap_data.show_chat_records;
}


void    set_show_chat_records_flag(SLONG flag)
{
    uimap_data.show_chat_records = flag;
}


void    switch_show_chat_records_flag(void)
{
    if(TRUE == uimap_data.show_chat_records)
        uimap_data.show_chat_records = FALSE;
    else
        uimap_data.show_chat_records = TRUE;
}


SLONG   is_map_submenu_opened(SLONG submenu_index)
{
    if(uimap_data.opened_submenu == submenu_index)
        return  TRUE;
    return  FALSE;
}


void    direct_open_map_submenu(SLONG submenu_index)
{
    if(uimap_data.opened_submenu != submenu_index)
    {
        direct_close_map_submenu(uimap_data.opened_submenu);
        switch(submenu_index)
        {
        case SUBMENU_STATE:
            open_mapstate_menu(TRUE);
            break;
        case SUBMENU_ITEM:
            open_mapitem_menu(TRUE);
            break;
        case SUBMENU_SKILL:
            open_mapskill_menu(TRUE);
            break;
        case SUBMENU_TASK:
            open_maptask_menu(TRUE);
            break;
        case SUBMENU_SHIP:
            open_mapship_menu(TRUE);
            break;
        }
        uimap_data.opened_submenu = submenu_index;
    }
}


void    direct_close_map_submenu(SLONG submenu_index)
{
    if(uimap_data.opened_submenu == submenu_index)
    {
        switch(submenu_index)
        {
        case SUBMENU_STATE:
            open_mapstate_menu(FALSE);
            break;
        case SUBMENU_ITEM:
            open_mapitem_menu(FALSE);
            break;
        case SUBMENU_SKILL:
            open_mapskill_menu(FALSE);
            break;
        case SUBMENU_TASK:
            open_maptask_menu(FALSE);
            break;
        case SUBMENU_SHIP:
            open_mapship_menu(FALSE);
            break;
        }
        uimap_data.opened_submenu = SUBMENU_NONE;
    }
}


void    open_map_submenu(SLONG submenu_index)
{
    if(uimap_data.opened_submenu != submenu_index)
    {
        switch(submenu_index)
        {
        case SUBMENU_STATE:
            close_map_submenu(uimap_data.opened_submenu);
            open_mapstate_menu(TRUE);
            uimap_data.opened_submenu = submenu_index;
            break;
        case SUBMENU_ITEM:
            //向server發請求, 要求打開人物背包, 待收到回饋訊息後, 呼叫 open_mapitem_menu() 來打開物品介面.
            client_cmd_open_player_bag();
            break;
        case SUBMENU_SKILL:
            close_map_submenu(uimap_data.opened_submenu);
            open_mapskill_menu(TRUE);
            uimap_data.opened_submenu = submenu_index;
            break;
        case SUBMENU_TASK:
            close_map_submenu(uimap_data.opened_submenu);
            open_maptask_menu(TRUE);
            uimap_data.opened_submenu = submenu_index;
            break;
        case SUBMENU_SHIP:
            close_map_submenu(uimap_data.opened_submenu);
            open_mapship_menu(TRUE);
            uimap_data.opened_submenu = submenu_index;
            break;
        }
    }
}


void    close_map_submenu(SLONG submenu_index)
{
    if(uimap_data.opened_submenu == submenu_index)
    {
        switch(submenu_index)
        {
        case SUBMENU_STATE:
            open_mapstate_menu(FALSE);
            uimap_data.opened_submenu = SUBMENU_NONE;
            break;
        case SUBMENU_ITEM:
            //向server發請求, 要求關閉人物背包, 待收到回饋訊息後, 呼叫 close_mapitem_menu() 來關閉物品介面.
            client_cmd_close_player_bag();
            break;
        case SUBMENU_SKILL:
            open_mapskill_menu(FALSE);
            uimap_data.opened_submenu = SUBMENU_NONE;
            break;
        case SUBMENU_TASK:
            open_maptask_menu(FALSE);
            uimap_data.opened_submenu = SUBMENU_NONE;
            break;
        case SUBMENU_SHIP:
            open_mapship_menu(FALSE);
            uimap_data.opened_submenu = SUBMENU_NONE;
            break;
        }
    }
}


/******************************************************************************************************************/
/* NPC HP BAR FUNCTIONS                                                                                           */
/******************************************************************************************************************/
int init_ui_hpbar(void)
{
    UI_HPBAR    *data = &ui_hpbar;
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, limited_frames;
    CAKE_FRAME_ANI  *cfa;

    data->cfa = NULL;
    for(i=0; i<4; i++)
        data->cf[i] = NULL;

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\uihp.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(data->cfa);
    limited_frames = min(frames, 4);
    for(i=0; i<limited_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    return  0;
}


void    free_ui_hpbar(void)
{
    UI_HPBAR    *data = &ui_hpbar;
    SLONG   i;

    destroy_cake_frame_ani(&data->cfa);
    for(i=0; i<4; i++)
        data->cf[i] = NULL;
}


void    redraw_ui_hpbar_background(BMP *bitmap)
{
    UI_HPBAR    *data = &ui_hpbar;
    CAKE_FRAME  *cf;

    cf = data->cf[0];
    put_rle(cf->frame_rx, cf->frame_ry, cf->rle, bitmap);
}


void    redraw_npc_mouse_point_info(SLONG id, BMP *bitmap)
{
    enum 
    {   NPC_NAME_BAR_HEIGHT     =   20,
    NPC_NAME_GAP_X              =   8,
    NPC_HP_BAR_SX               =   440,
    NPC_HP_BAR_SY               =   42,
    NPC_HP_BAR_WIDTH            =   522 - 440,
    NPC_HP_BAR_HEIGHT           =   54 - 42,
    NPC_NAME_BAR_SX             =   420,
    NPC_NAME_BAR_SY             =   24,
    };
    
    SLONG   npc_index;
    SLONG   name_cx, name_cy;
    SLONG   npc_no, npc_kind, npc_x, npc_y, npc_z;
    USTR    npc_name[32];
    USTR    name[128];
    SLONG   name_bar_x, name_bar_y, len;
    SLONG   hp, hp2, hp_bar_len, level;
    SLONG	hp_bar_x, hp_bar_y;
    
    npc_index = id;
    if(npc_index >= 0 && npc_index < MAX_CHARACTER_PER_ZONE)
    {
        npc_no = npc_index;
        if( (npc_no >= 0) && (npc_no != g_lPlayerIndex) ) //not oneself
        {
            LOCK_CHARACTER(npc_no);
			GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
            name_cx = npc_x - map_data.map_sx;
            name_cy = npc_y - npc_z - map_data.map_sy - NPC_MASK_HEIGHT - 10;
			npc_kind = GetCharacterKind(npc_no);
            strcpy((char *)npc_name, (const char *)GetCharacterMainName(npc_no));
            hp = GetCharacterHp(npc_no);
            hp2 = GetCharacterMaxHp(npc_no);
            level = GetCharacterLevel(npc_no);
            UNLOCK_CHARACTER(npc_no);
            
            switch(npc_kind)
            {
                /*
            case NPC_KIND_NPC:
                {
                    len = strlen((const char *)npc_name);
                    name_bar_x = name_cx - len * 4 - NPC_NAME_GAP_X;
                    name_bar_y = name_cy - NPC_NAME_BAR_HEIGHT / 2;
                    dark_put_bar(name_bar_x, name_bar_y, len * 8 + NPC_NAME_GAP_X * 2, NPC_NAME_BAR_HEIGHT, bitmap, 16);
                    sprintf((char *)name, "~C4%s~C0", npc_name);
                    print16(name_bar_x + NPC_NAME_GAP_X, name_bar_y + (NPC_NAME_BAR_HEIGHT - 16) / 2, 
                        (USTR*)name, PEST_PUT, bitmap);
                    break;
                }
                */
                // Jack, temp set, show all npc's hp. [13:51,11/1/2002]
            case NPC_KIND_NPC:
            case NPC_KIND_PLAYER:
            case NPC_KIND_NORMAL_MONSTER:
            default:
                {
                    len = strlen((const char *)npc_name);
                    name_bar_x = NPC_NAME_BAR_SX;
                    name_bar_y = NPC_NAME_BAR_SY;
                    
                    //name
                    sprintf((char *)name, "~C4~F2LV:%d %s~C0~F0", level+1, npc_name);
                    print16(name_bar_x, name_bar_y, (USTR*)name, PEST_PUT, bitmap);

                    //hp
                    redraw_ui_hpbar_background(bitmap);

                    hp_bar_x = NPC_HP_BAR_SX;
                    hp_bar_y = NPC_HP_BAR_SY;
                    hp_bar_len = 0;
                    if(hp2) hp_bar_len = NPC_HP_BAR_WIDTH * hp / hp2;
                    if(hp_bar_len > NPC_HP_BAR_WIDTH) hp_bar_len = NPC_HP_BAR_WIDTH;
                    if(hp_bar_len < 0) hp_bar_len = 0;
                    if(hp && hp_bar_len == 0) hp_bar_len = 1;
                    put_bar(hp_bar_x, hp_bar_y, hp_bar_len, NPC_HP_BAR_HEIGHT - 1, SYSTEM_RED, bitmap);

                    //sprintf((char *)disp_rec,"~C4%s~C0 %d/%d~C0", TEXTMSG_NAME_HP, hp, hp2);
                    //print16(name_bar_x, name_bar_y + NPC_NAME_BAR_HEIGHT, (USTR*)disp_rec, PEST_PUT, bitmap);
                    break;
                }
            }
        }
    }
}



SLONG   exec_left_hit_uimap(SLONG event_id)
{
    switch(event_id)
    {
    case UIMAP_ID_ITEM:         //點擊道具按鈕
    case UIMAP_ID_TITLE_ITEM:   //點擊道具標題
		if(!is_map_submenu_opened(SUBMENU_ITEM))
			open_map_submenu(SUBMENU_ITEM);
        break;

    case UIMAP_ID_STATE:        //點擊狀態按鈕
    case UIMAP_ID_TITLE_STATE:  //點擊狀態標題
        if(!is_map_submenu_opened(SUBMENU_STATE))
            open_map_submenu(SUBMENU_STATE);
        break;

    case UIMAP_ID_MAGIC:        //點擊技能按鈕
    case UIMAP_ID_TITLE_MAGIC:  //點擊技能標題
        if(!is_map_submenu_opened(SUBMENU_SKILL))
            open_map_submenu(SUBMENU_SKILL);
        break;

    case UIMAP_ID_TASK:         //點擊任務按鈕
    case UIMAP_ID_TITLE_TASK:   //點擊任務標題
        if(!is_map_submenu_opened(SUBMENU_TASK))
            open_map_submenu(SUBMENU_TASK);
        break;

    case UIMAP_ID_SHIP:         //點擊船隻按鈕
    case UIMAP_ID_TITLE_SHIP:   //點擊船隻標題
        if(!is_map_submenu_opened(SUBMENU_SHIP))
            open_map_submenu(SUBMENU_SHIP);
        break;
        
    case UIMAP_ID_FIGHT_NEXT_STATE: //點擊下一個戰鬥狀態按鈕
        client_cmd_change_fight_state();
        break;
        
    case UIMAP_ID_FIGHT_PREV_STATE: //點擊上一個戰鬥狀態按鈕
        client_cmd_change_fight_state();
        break;
        
    case UIMAP_ID_MINIMAP_MINIMIZE: //點擊最小化右上角小地圖按鈕
        minimize_map_ui_minimap();
        break;
    case UIMAP_ID_SETTING:  // 點擊最小化右上角 系統設置 按鈕
        extern SLONG	exec_maingame_escape_key_up(void);
        exec_maingame_escape_key_up();
        break;
    case UIMAP_ID_MINIMAP:
        TM tm_info;
//        WM wm_info;
        memset( &tm_info, 0, sizeof( tm_info ) );
//        sm_set_tm_info( &tm_info );
        // TODO: 顯示探險地圖

        break;
    case UIMAP_ID_MINIMAP_MAXIMIZE: //點擊最大化右上角小地圖按鈕
        maximize_map_ui_minimap();
        break;
        
    case UIMAP_ID_LEFT_MINIMIZE:    //點擊左下角最小化按鈕
        minimize_map_ui_left();
        break;
    case UIMAP_ID_LEFT_MAXIMIZE:    //點擊左下角最大化按鈕
        maximize_map_ui_left();
        break;
        
    case UIMAP_ID_RIGHT_MINIMIZE:   //點擊右下角最小化按鈕
        minimize_map_ui_right();
        break;
    case UIMAP_ID_RIGHT_MAXIMIZE:   //點擊右下角最大化按鈕
        maximize_map_ui_right();
        break;
        
    case UIMAP_ID_MANFACE_MINIMIZE: //點擊左上角隊伍人員圖標最小化按鈕
        minimize_map_ui_manface();
        break;
        
    case UIMAP_ID_MANFACE_MAXIMIZE: //點擊左上角隊伍人員圖標最大化按鈕
        maximize_map_ui_manface();
        break;
        
    case UIMAP_ID_LEFT_QUICK_MAGIC:     //點擊左手快捷法術按鈕
        if( is_left_quick_magics_ui_visible() )
            hide_left_quick_magics_ui();
        else
            show_left_quick_magics_ui();
        break;

    case UIMAP_ID_RIGHT_QUICK_MAGIC:    //點擊右手快捷法術按鈕
        if( is_right_quick_magics_ui_visible() )
            hide_right_quick_magics_ui();
        else
            show_right_quick_magics_ui();
        break;
        
    case UIMAP_ID_QUICK_ITEM_0: //點擊快捷道具按鈕
    case UIMAP_ID_QUICK_ITEM_1:
    case UIMAP_ID_QUICK_ITEM_2:
    case UIMAP_ID_QUICK_ITEM_3:
        {
            SLONG   sash_index;
            
            sash_index = mouse_hand.point_no - UIMAP_ID_QUICK_ITEM_0;
            client_cmd_left_hit_sash_item(sash_index);
        }
        break;
        
//    case UIMAP_ID_CHAT_INPUT:   //點擊聊天輸入框
//        activate_map_chat_input(true);
//        break;
        
    case UIMAP_ID_CHAT_RECORD:  //點擊聊天紀錄按鈕
        switch_show_chat_records_flag();
        break;
        
    default:
        break;
    }
    return  0;
}


SLONG	exec_right_hit_uimap(SLONG event_id)
{
    switch(event_id)
    {
    case UIMAP_ID_QUICK_ITEM_0: //點擊快捷道具按鈕
    case UIMAP_ID_QUICK_ITEM_1:
    case UIMAP_ID_QUICK_ITEM_2:
    case UIMAP_ID_QUICK_ITEM_3:
        {
            SLONG   sash_index;
            
            sash_index = mouse_hand.point_no - UIMAP_ID_QUICK_ITEM_0;
            client_cmd_right_hit_sash_item(sash_index);
        }
        break;
	}
	return	0;
}

/******************************************************************************************************************/
/* MINIMAP FUNCTIONS                                                                                              */
/******************************************************************************************************************/
BMP*    load_fff(char *filename)
{
    PACK_FILE   *fp = NULL;
    BMP *tmp = NULL;
    SLONG   result;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
        return  NULL;
    result = naked_read_bitmap(fp, &tmp);
    pack_fclose(fp);
    if(TTN_OK == result)
        return  (BMP*)tmp;
    else
        return  NULL;
}


void    init_minimap(void)
{
    memset( &minimap_data, 0, sizeof(minimap_data));
}


SLONG   load_minimap_of_jpg(USTR *filename)
{
    BMP *bmp = NULL;
    SLONG   result, load_result;
    unsigned char   *pic = NULL, *p, r, g, b; //, a;
    int width, height, x, y;

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    start load jpg %s", filename);
#endif//DEBUG_MSG
    
    load_result = LoadJPG((const char *)filename, &pic, &width, &height );
    if(0 == load_result)
    {
#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    load jpg result %d, pic=%p, width=%d, height=%d", 
            load_result, pic, width, height);
#endif//DEBUG_MSG

        bmp = create_bitmap(width, height);
#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    create jpg bitmap %p", bmp);
#endif//DEBUG_MSG
        if(NULL != bmp)
        {
            p = pic;
            for(y = 0; y < bmp->h; y ++)
            {
                for(x = 0; x < bmp->w; x ++)
                {
                    r = *p++;
                    g = *p++;
                    b = *p++;
                    p++; //a = *p++;
                    bmp->line[y][x] = rgb2hi(r, g, b);
                }
            }
#ifdef  DEBUG_MSG
            log_encrypt_message(1, "    convert jpg pic to bitmap ok");
#endif//DEBUG_MSG
            if(pic) {free(pic); pic = NULL;}
#ifdef  DEBUG_MSG
            log_encrypt_message(1, "    free jpg pic ok");
#endif//DEBUG_MSG
            
            minimap_data.minimap_bitmap = bmp;
            minimap_data.minimap_xl = bmp->w;
            minimap_data.minimap_yl = bmp->h;
            minimap_data.is_loaded = 1;
            
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    set minimap_data ok");
#endif//DEBUG_MSG
            result = TTN_OK;
        }
        else
        {
            if(pic) {free(pic); pic = NULL;}
            minimap_data.is_loaded = 0;
            result = TTN_NOT_OK;
        }
    }
    else
    {
        minimap_data.is_loaded = 0;
        result = TTN_NOT_OK;
    }
    return  result;
}


SLONG   load_minimap_of_fff(USTR *filename)
{
    BMP *bmp = NULL;
    SLONG   result;

    if(NULL != (bmp  = load_fff((char *)filename)))
    {
        minimap_data.minimap_bitmap = bmp;
        minimap_data.minimap_xl = bmp->w;
        minimap_data.minimap_yl = bmp->h;
        minimap_data.is_loaded = 1;
        result = TTN_OK;
    }
    else
    {
        minimap_data.is_loaded = 0;
        result = TTN_NOT_OK;
    }
    return  result;
}


void    redraw_minimap(BMP *bitmap)
{
    enum { SX = 657,  SY = 25, BOUND_XL = 92, BOUND_YL = 92, EDGE_XL = 80, EDGE_YL = 50 };
    SLONG   bound_sx, bound_sy, stand_x, stand_y, stand_z;
    double  zoom_x, zoom_y, zoom;

    if(!minimap_data.is_loaded)
        return;

    if(g_lPlayerIndex < 0)
        return;

    //(1) Redraw minimap background -----------------------------------------------------
    LOCK_CHARACTER(g_lPlayerIndex);
	GetCharacterPosition(g_lPlayerIndex, &stand_x, &stand_y, &stand_z);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    zoom_x = (double)(minimap_data.minimap_xl - EDGE_XL * 2) / (double)map_head.map_xl;
    zoom_y = (double)(minimap_data.minimap_yl - EDGE_YL * 2) / (double)map_head.map_yl;
    zoom = min(zoom_x, zoom_y);
    bound_sx = (SLONG)(EDGE_XL + stand_x * zoom) - BOUND_XL/2;
    bound_sy = (SLONG)(EDGE_YL + stand_y * zoom) - BOUND_YL/2;
    if(bound_sx > minimap_data.minimap_xl - BOUND_XL) bound_sx = minimap_data.minimap_xl - BOUND_XL;
    if(bound_sy > minimap_data.minimap_yl - BOUND_YL) bound_sy = minimap_data.minimap_yl - BOUND_YL;
    if(bound_sx < 0) bound_sx = 0;
    if(bound_sy < 0) bound_sy = 0;
    bound_put_bitmap(SX, SY, bound_sx, bound_sy, BOUND_XL, BOUND_YL, minimap_data.minimap_bitmap, bitmap);
    game_range.add( SX, SY, BOUND_XL, BOUND_YL, UIMAP_EVENT, UIMAP_ID_MINIMAP );


	//(2a) Redraw Monster npc's position mark. -----------------------------------------------
    SLONG   npc_no, npc_flag, npc_x, npc_y, npc_z, npc_hp;

	//目前定義的怪物從500開始, 500以前為player npc.
    for(npc_no=500; npc_no<MAX_CHARACTER_PER_ZONE; npc_no++)
    {
		LOCK_CHARACTER(npc_no);
		npc_flag = get_npc_flag(npc_no);
		npc_hp = GetCharacterHp(npc_no);
		GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
		UNLOCK_CHARACTER(npc_no);
		
		if(npc_flag && npc_hp > 0)
		{
			npc_y -= npc_z;
			npc_x = (SLONG) (npc_x * zoom) + EDGE_XL - bound_sx;
			npc_y = (SLONG) (npc_y * zoom) + EDGE_YL - bound_sy;
			if( (npc_x > 2) && (npc_x < BOUND_XL - 2) && (npc_y > 2) && (npc_y < BOUND_YL - 2) )
			{
				put_pixel(SX + npc_x, SY + npc_y, SYSTEM_WHITE, bitmap);
				put_box(SX + npc_x - 1, SY + npc_y - 1, 3, 3, SYSTEM_BLACK, bitmap);
			}
		}
    }

	//(2b) Redraw Player's npc position mark ---------------------------------------------------
    for(npc_no=0; npc_no<500; npc_no++)
    {
        if(npc_no != g_lPlayerIndex)
        {
            LOCK_CHARACTER(npc_no);
            npc_flag = get_npc_flag(npc_no);
            npc_hp = GetCharacterHp(npc_no);
			GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
            UNLOCK_CHARACTER(npc_no);

            if(npc_flag && npc_hp > 0)
            {
                npc_y -= npc_z;
                npc_x = (SLONG) (npc_x * zoom) + EDGE_XL - bound_sx;
                npc_y = (SLONG) (npc_y * zoom) + EDGE_YL - bound_sy;
                if( (npc_x > 2) && (npc_x < BOUND_XL - 2) && (npc_y > 2) && (npc_y < BOUND_YL - 2) )
                {
                    put_bar(SX + npc_x, SY + npc_y, 2, 2, SYSTEM_RED, bitmap);
                    put_box(SX + npc_x - 1, SY + npc_y - 1, 4, 4, SYSTEM_WHITE, bitmap);
                }
            }
        }
    }

    //(3) Redraw player npc's position mask ----------------------------------------------------
    npc_x = (SLONG) (stand_x * zoom) + EDGE_XL - bound_sx;
    npc_y = (SLONG) (stand_y * zoom) + EDGE_YL - bound_sy;
    put_bar(SX + npc_x, SY + npc_y, 2, 2, SYSTEM_BLUE, bitmap);
    put_box(SX + npc_x - 1, SY + npc_y - 1, 4, 4, SYSTEM_WHITE, bitmap);
}


void    free_minimap(void)
{
    if(minimap_data.is_loaded)
    {
        destroy_bitmap(&minimap_data.minimap_bitmap);
        minimap_data.is_loaded = 0;
    }
}



void	debug_redraw_game_minimap(BMP *bitmap)
{
    enum { SX = 100,  SY = 100, BOUND_XL = 600, BOUND_YL = 400, EDGE_XL = 80, EDGE_YL = 50 };
    SLONG   bound_sx, bound_sy, stand_x, stand_y, stand_z, bound_xl, bound_yl;
    double  zoom_x, zoom_y, zoom;
	SLONG	sx, sy;
	SLONG	flag;

    flag = get_game_config_show_debug_minimap();
    if(!flag)
        return;

    if(!minimap_data.is_loaded)
        return;

    if(g_lPlayerIndex < 0)
        return;

    //(1) Redraw minimap background -----------------------------------------------------
    LOCK_CHARACTER(g_lPlayerIndex);
	GetCharacterPosition(g_lPlayerIndex, &stand_x, &stand_y, &stand_z);
    UNLOCK_CHARACTER(g_lPlayerIndex);

    zoom_x = (double)(minimap_data.minimap_xl - EDGE_XL * 2) / (double)map_head.map_xl;
    zoom_y = (double)(minimap_data.minimap_yl - EDGE_YL * 2) / (double)map_head.map_yl;
    zoom = min(zoom_x, zoom_y);
	bound_xl = min(minimap_data.minimap_xl - EDGE_XL * 2, BOUND_XL);
	bound_yl = min(minimap_data.minimap_yl - EDGE_YL * 2, BOUND_YL);
    bound_sx = (SLONG)(EDGE_XL + stand_x * zoom) - bound_xl/2;
    bound_sy = (SLONG)(EDGE_YL + stand_y * zoom) - bound_yl/2;
    if(bound_sx > minimap_data.minimap_xl - bound_xl) bound_sx = minimap_data.minimap_xl - bound_xl;
    if(bound_sy > minimap_data.minimap_yl - bound_yl) bound_sy = minimap_data.minimap_yl - bound_yl;
    if(bound_sx < 0) bound_sx = 0;
    if(bound_sy < 0) bound_sy = 0;
	sx = 400 - bound_xl / 2;
	sy = 300 - bound_yl / 2;
	put_menu_box(sx-2, sy-2, bound_xl+4, bound_yl+4, bitmap);
    bound_put_bitmap(sx, sy, bound_sx, bound_sy, bound_xl, bound_yl, minimap_data.minimap_bitmap, bitmap);


	//(2a) Redraw Monster npc's position mark. -----------------------------------------------
    SLONG   npc_no, npc_flag, npc_x, npc_y, npc_z, npc_hp;

	//目前定義的怪物從500開始, 500以前為player npc.
    for(npc_no=500; npc_no<MAX_CHARACTER_PER_ZONE; npc_no++)
    {
		LOCK_CHARACTER(npc_no);
		npc_flag = get_npc_flag(npc_no);
		npc_hp = GetCharacterHp(npc_no);
		GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
		UNLOCK_CHARACTER(npc_no);
		
		if(npc_flag && npc_hp > 0)
		{
			npc_y -= npc_z;
			npc_x = (SLONG) (npc_x * zoom) + EDGE_XL - bound_sx;
			npc_y = (SLONG) (npc_y * zoom) + EDGE_YL - bound_sy;
			if( (npc_x > 2) && (npc_x < bound_xl - 2) && (npc_y > 2) && (npc_y < bound_yl - 2) )
			{
				put_pixel(sx + npc_x, sy + npc_y, SYSTEM_WHITE, bitmap);
				put_box(sx + npc_x - 1, sy + npc_y - 1, 3, 3, SYSTEM_BLACK, bitmap);
			}
		}
    }

	//(2b) Redraw Player's npc position mark ---------------------------------------------------
    for(npc_no=0; npc_no<500; npc_no++)
    {
        if(npc_no != g_lPlayerIndex)
        {
            LOCK_CHARACTER(npc_no);
            npc_flag = get_npc_flag(npc_no);
            npc_hp = GetCharacterHp(npc_no);
			GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
            UNLOCK_CHARACTER(npc_no);

            if(npc_flag && npc_hp > 0)
            {
                npc_y -= npc_z;
                npc_x = (SLONG) (npc_x * zoom) + EDGE_XL - bound_sx;
                npc_y = (SLONG) (npc_y * zoom) + EDGE_YL - bound_sy;
                if( (npc_x > 2) && (npc_x < bound_xl - 2) && (npc_y > 2) && (npc_y < bound_yl - 2) )
                {
                    put_bar(sx + npc_x, sy + npc_y, 2, 2, SYSTEM_RED, bitmap);
                    put_box(sx + npc_x - 1, sy + npc_y - 1, 4, 4, SYSTEM_WHITE, bitmap);
                }
            }
        }
    }

    //(3) Redraw player npc's position mask ----------------------------------------------------
    npc_x = (SLONG) (stand_x * zoom) + EDGE_XL - bound_sx;
    npc_y = (SLONG) (stand_y * zoom) + EDGE_YL - bound_sy;
    put_bar(sx + npc_x, sy + npc_y, 2, 2, SYSTEM_BLUE, bitmap);
    put_box(sx + npc_x - 1, sy + npc_y - 1, 4, 4, SYSTEM_WHITE, bitmap);
}

