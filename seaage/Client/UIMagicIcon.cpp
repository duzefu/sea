/*
**	UISkillIcon.cpp
**	UI of skill icon functions.
**
**	Jack, 2002/09/11.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "UIMagicIcon.h"
#include "ClientMain.h"


/******************************************************************************************************************/
typedef struct  tagMAGIC_ICON_IMAGE //技能圖標
{
    CAKE_FRAME_ANI  *cfa;                   //所有技能ICON圖像的指標
    CAKE_FRAME      *cf[MAX_MAGIC_ICONS];   //每個技能ICON的圖像指標
    //
    CAKE_FRAME_ANI  *clockwise_cfa;         //順時針方向的MASK
    SLONG           clockwise_frames;       //順時針方向的MASK幀數
    CAKE_FRAME_ANI  *anti_clockwise_cfa;    //反時針方向的MASK
    SLONG           anti_clockwise_frames;  //反時針方向的MASK幀數
} MAGIC_ICON_IMAGE, *LPMAGIC_ICON_IMAGE;


MAGIC_ICON_IMAGE    magic_icon_image;


/******************************************************************************************************************/
/* SKILL ICON FUNCTIONS                                                                                           */
/******************************************************************************************************************/
SLONG   init_magic_icon_image(void)
{
    MAGIC_ICON_IMAGE *data = &magic_icon_image;
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;

    //初始化動畫指標
    data->cfa = NULL;
    for(i=0; i<MAX_MAGIC_ICONS; i++)
    {
        data->cf[i] = NULL;
    }
    data->clockwise_cfa = NULL;
    data->anti_clockwise_cfa = NULL;

    //載入法術圖標
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\skillico.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;

    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_MAGIC_ICONS);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    //載入順時針方向mask
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\icon360a.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->clockwise_cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;
    data->clockwise_frames = count_cake_frames(data->clockwise_cfa);

    //載入反時針方向mask
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\icon360b.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->anti_clockwise_cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;
    data->anti_clockwise_frames = count_cake_frames(data->anti_clockwise_cfa);

    return  TTN_OK;
}


void    free_magic_icon_image(void)
{
    MAGIC_ICON_IMAGE *data = &magic_icon_image;
    SLONG   i;

    destroy_cake_frame_ani(&data->cfa);
    for(i=0; i<MAX_MAGIC_ICONS; i++)
    {
        data->cf[i] = NULL;
    }
    destroy_cake_frame_ani(&data->clockwise_cfa);
    data->clockwise_frames = 0;
    destroy_cake_frame_ani(&data->anti_clockwise_cfa);
    data->anti_clockwise_frames = 0;
}


void    redraw_magic_icon_image(SLONG cx, SLONG cy, SLONG index, BMP *bitmap, SLONG redraw_flags)
{
    MAGIC_ICON_IMAGE *data = &magic_icon_image;
    CAKE_FRAME  *cf;
    RLE *rle;

    if(index < 0 || index >= MAX_MAGIC_ICONS)
        return;
    cf = data->cf[index];
    if(! cf)
        return;
    rle = cf->rle;
    if(! rle)
        return;

    switch(redraw_flags)
    {
    case MAGIC_ICON_NORMAL:
        put_rle(cx - rle->w/2, cy - rle->h/2, rle, bitmap);
        break;
    case MAGIC_ICON_INVALID:
        gray_put_rle(cx - rle->w/2, cy - rle->h/2, rle, bitmap);
        break;
    default:
        break;
    }
}


void    redraw_alpha_magic_icon_image(SLONG cx, SLONG cy, SLONG index, BMP *bitmap, SLONG alpha)
{
    MAGIC_ICON_IMAGE *data = &magic_icon_image;
    CAKE_FRAME  *cf;
    RLE *rle;

    cf = data->cf[index];
    if(! cf) return;
    rle = cf->rle;
    if(! rle) return;
    alpha_put_rle(cx - rle->w/2, cy - rle->h/2, rle, bitmap, alpha);
}


void    redraw_magic_icon_clockwise_mask(SLONG cx, SLONG cy, SLONG opened_percent, BMP *bitmap)
{
    MAGIC_ICON_IMAGE *data = &magic_icon_image;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;
    RLE *rle;
    SLONG   frame;

    frame = (opened_percent * (data->clockwise_frames - 1) + 50 ) / 100;
    cfa = get_specify_cake_frame_ani(data->clockwise_cfa, frame);
    if(!cfa) return;
    cf = cfa->cake_frame;
    if(!cf) return;
    rle = cf->rle;
    if(!rle) return;
    put_rle(cx - MAGIC_ICON_WIDTH/2 + cf->frame_rx, cy - MAGIC_ICON_HEIGHT/2 + cf->frame_ry, rle, bitmap);
}


void    redraw_magic_icon_anti_clockwise_mask(SLONG cx, SLONG cy, SLONG opened_percent, BMP *bitmap)
{
    MAGIC_ICON_IMAGE *data = &magic_icon_image;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;
    RLE *rle;
    SLONG   frame;

    frame = (opened_percent * (data->anti_clockwise_frames - 1) + 50 ) / 100;
    cfa = get_specify_cake_frame_ani(data->anti_clockwise_cfa, frame);
    if(!cfa) return;
    cf = cfa->cake_frame;
    if(!cf) return;
    rle = cf->rle;
    if(!rle) return;
    put_rle(cx - MAGIC_ICON_WIDTH/2 + cf->frame_rx, cy - MAGIC_ICON_HEIGHT/2 + cf->frame_ry, rle, bitmap);
}



void    redraw_magic_icon_image_with_state(SLONG cx, SLONG cy, SLONG index, SLONG state, SLONG ticks, SLONG total_ticks, BMP *bitmap)
{
    SLONG   opened_percent;

    switch(state)
    {
    case MAGIC_STATE_OK:            //法術OK,可以使用.
        redraw_magic_icon_image(cx, cy, index, bitmap, MAGIC_ICON_NORMAL);
        break;
    case MAGIC_STATE_PREPARE:       //法術前置時間進行中
        redraw_magic_icon_image(cx, cy, index, bitmap, MAGIC_ICON_NORMAL);
        opened_percent = ticks * 100 / total_ticks;
        redraw_magic_icon_anti_clockwise_mask(cx, cy, opened_percent, bitmap);
        break;
    case MAGIC_STATE_WAIT_SPOWER:   //等待蓄力中
        redraw_magic_icon_image(cx, cy, index, bitmap, MAGIC_ICON_NORMAL);
        opened_percent = 0;
        //redraw_magic_icon_clockwise_mask(cx, cy, opened_percent, bitmap);
        break;
    case MAGIC_STATE_SPOWER:        //法術正在蓄力中
        redraw_magic_icon_image(cx, cy, index, bitmap, MAGIC_ICON_NORMAL);
        opened_percent = ticks * 100 / total_ticks;
        redraw_magic_icon_clockwise_mask(cx, cy, opened_percent, bitmap);
        break;
    case MAGIC_STATE_WAIT_BREAK:    //法術等待釋放
        redraw_alpha_magic_icon_image(cx, cy, index, bitmap, ticks);
        break;
    }
}


