/*
**	UIMagicArea.cpp
**	magic area select functions.
**
**	Jack, 2002/09/26.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Npc.h"
#include "UIMagicArea.h"
#include "UIInfoBar.h"
#include "ClientMain.h"

 
/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
//只有隊友才可以看到...所以..遊戲中的..對多可見的魔法陣的數目..和最多..組隊的數目相同
MAGIC_AREA  g_magic_area[MAX_MAGIC_AREA];
/*
static  POINT   l_line_area_stand_offset[16] = 
{
    {114, 64}, {106, 59}, { 82, 84}, { 59,107},
    { 63,113}, {186,107}, {321, 84}, {413, 59},
    {447, 64}, {414,187}, {321,321}, {197,413},
    { 64,446}, { 60,414}, { 82,322}, {105,188}
};
*/
/******************************************************************************************************************/
/* UI MAGIC AREA FUNCTIONS                                                                                        */
/******************************************************************************************************************/
void    magic_area_id_manage(SLONG *new_id,SLONG *draw_id,SLONG *new_frame,SLONG *draw_frame)
{
    if ((*new_id) != INVALID_OBJECT_ID)
    {
        if ((*draw_id) == INVALID_OBJECT_ID)
        {
            add_reference_for_map_object_image(*new_id);
            //
            *draw_id = *new_id;
            *draw_frame = *new_frame;
        }
        else if ((*draw_id) != (*new_id))
        {
            dec_reference_for_map_object_image(*draw_id);
            add_reference_for_map_object_image(*new_id);
            //
            *draw_id = *new_id;
            *draw_frame = *new_frame;
        }
        else
        {
            *draw_frame = *new_frame;            
        }
    }
    else //從內存中釋放特殊效果圖檔
    {
        if ((*draw_id) != INVALID_OBJECT_ID)
        {
            dec_reference_for_map_object_image(*draw_id);
            //
            *draw_id = INVALID_OBJECT_ID;
            *draw_frame = 0;
        }
    }
}
//----
//
//----
void    loop_magic_area_frame(SLONG index)
{
    SLONG   id, frames, frame;

    id = g_magic_area[index].draw_img_id;
    if(id == INVALID_OBJECT_ID)
        return;
    //
    frames = GetObjectImageTotalFrames(id);
	frame = g_magic_area[index].draw_frame;

	frame++;
    if(frame >= frames)
		frame = 0;
    //
    g_magic_area[index].draw_frame = frame;
}

//---
//
//---
SLONG   init_magic_area(void)
{
    SLONG   i;
    //
    for (i=0; i<MAX_MAGIC_AREA ;i++)
    {
        memset(&g_magic_area[i], 0, sizeof(g_magic_area[i]));
        g_magic_area[i].new_imd_id = INVALID_OBJECT_ID;
        g_magic_area[i].draw_img_id = INVALID_OBJECT_ID;
    }
    //
    return  TTN_OK;
/*
    MAGIC_AREA *data = &magic_area;
    USTR    filename[_MAX_FNAME];
    SLONG   result;

    //初始化動畫指標
    data->line_cfa = NULL;
    data->circle_cfa = NULL;
    data->rectangle_cfa = NULL;

    //載入線性區域圖檔(劍)
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\magarea1.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->line_cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;
    //初始化數據.
    magic_area.flag = 0;

    return  TTN_OK;
*/    
}


void    free_magic_area(void)
{
    SLONG   i;
    MAGIC_AREA *data = NULL;
    //
    for (i=0; i<MAX_MAGIC_AREA; i++)
    {
        data = &(g_magic_area[i]);
        //
        data->new_imd_id = INVALID_OBJECT_ID;
        //圖檔管理
        magic_area_id_manage(&(data->new_imd_id), &(data->draw_img_id),
                             &(data->new_frame), &(data->draw_frame));
    }
/*
    MAGIC_AREA *data = &magic_area;

    destroy_cake_frame_ani(&data->line_cfa);
    destroy_cake_frame_ani(&data->circle_cfa);
    destroy_cake_frame_ani(&data->rectangle_cfa);
*/    
}


void	clear_magic_area(void)
{
    SLONG   i;
    //
    for (i=0; i<MAX_MAGIC_AREA; i++)
    {
        g_magic_area[i].flag = 0;
        g_magic_area[i].new_imd_id = INVALID_OBJECT_ID;
        //圖檔管理
        magic_area_id_manage(&(g_magic_area[i].new_imd_id), &(g_magic_area[i].draw_img_id),
                             &(g_magic_area[i].new_frame), &(g_magic_area[i].draw_frame));
    }
/*    
	magic_area.flag = 0;
*/	
}

void    set_magic_area_visible(SLONG index, SLONG is_visible)
{
    if (index<0 || index>=MAX_MAGIC_AREA)
        return;
    //
    if(is_visible) 
        g_magic_area[index].flag |= MAGIC_AREA_FLAG_VISIBLE;
    else        
        g_magic_area[index].flag &= ~MAGIC_AREA_FLAG_VISIBLE;
}
SLONG   is_magic_area_visible(SLONG index)
{
    if(g_magic_area[index].flag & MAGIC_AREA_FLAG_VISIBLE)
        return  TRUE;
    return  FALSE;
}
void    set_magic_area_position(SLONG index, SLONG x, SLONG y)
{
    //
    g_magic_area[index].x = x;
    g_magic_area[index].y = y;
}
void    set_magic_magic_no(SLONG index, SLONG magic_no)
{
    g_magic_area[index].magic_no = magic_no;
}
void    set_magic_npc_no(SLONG index, SLONG npc_no)
{
    g_magic_area[index].npc_no = npc_no;
}
//-------------------------------------------------------------------------
//  UTILITY FUNCTION
//-------------------------------------------------------------------------




SLONG   find_free_magic_area(void)
{
    SLONG   i;
    //
    for (i=0; i<MAX_MAGIC_AREA ;i++)
    {
        if (!(g_magic_area[i].flag & MAGIC_AREA_FLAG_VISIBLE))
            return i;            
    }
    //
    return -1;
}
void    add_magic_area(SLONG x, SLONG y, SLONG dir, SLONG npc_no, SLONG magic_no, SLONG level)
{   
    SLONG   pos;
    SLONG   magic_id;
    //
    pos = find_free_magic_area();
    //
    if (pos >= 0)
    {
        magic_id = GetSkillMagicId(magic_no, level);
        //
        g_magic_area[pos].flag |= MAGIC_AREA_FLAG_VISIBLE;
        //
        g_magic_area[pos].x = x;              //目標範圍基準起始點座標 X
        g_magic_area[pos].y = y;              //目標範圍基準起始點座標 Y
        g_magic_area[pos].magic_no = magic_no;//正在施法的法術編號
        g_magic_area[pos].npc_no = npc_no;    //該魔法陣的.使用者
        //
        //
        if (magic_id < 0)
            g_magic_area[pos].new_imd_id = INVALID_OBJECT_ID;
        else                
            g_magic_area[pos].new_imd_id = MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, magic_id + dir); 
        g_magic_area[pos].new_frame = 0;
        //
    }
}
void    delete_magic_area(SLONG npc_no,SLONG magic_no)
{
    SLONG   i;
    MAGIC_AREA *data = NULL;    
    //
    for (i=0; i<MAX_MAGIC_AREA ;i++)
    {
        if ((g_magic_area[i].magic_no == magic_no) &&
           (g_magic_area[i].npc_no == npc_no))
        {
            data = &(g_magic_area[i]);
            //
            data->x         = 0;    //目標範圍基準起始點座標 X
            data->y         = 0;    //目標範圍基準起始點座標 Y
            data->magic_no  = 0;    //正在施法的法術編號
            data->npc_no    = 0;    //該魔法陣的.使用者
            //
            data->new_imd_id = INVALID_OBJECT_ID;
            magic_area_id_manage(&(g_magic_area[i].new_imd_id), &(g_magic_area[i].draw_img_id),
                                 &(g_magic_area[i].new_frame), &(g_magic_area[i].draw_frame));
            //
            data->flag &= ~MAGIC_AREA_FLAG_VISIBLE;
        }           
    }
    return ;
}
void    reflash_magic_area(void)
{
    SLONG   i;
    //
    for (i=0; i<MAX_MAGIC_AREA ;i++)
    {
        magic_area_id_manage(&(g_magic_area[i].new_imd_id), &(g_magic_area[i].draw_img_id),
            &(g_magic_area[i].new_frame), &(g_magic_area[i].draw_frame));
        if(g_magic_area[i].flag & MAGIC_AREA_FLAG_VISIBLE)
            loop_magic_area_frame(i);
    }
}
void    redraw_magic_area(BMP *bitmap)
{
    SLONG   i;
    SLONG   ox, oy;
    SLONG   img_id, img_frame;
    SLONG   sx, sy, px, py, pz;
    CAKE_FRAME_ANI  *ext_cfa = NULL;
    CAKE_FRAME  *ext_cf = NULL;
    POLY *ext_pl = NULL;    
    RLE     *ext_rle= NULL;
    //
    reflash_magic_area();
    //
    for (i=0; i<MAX_MAGIC_AREA ;i++)
    {
        if(g_magic_area[i].flag & MAGIC_AREA_FLAG_VISIBLE)
        {
            img_id = g_magic_area[i].draw_img_id;
            img_frame = g_magic_area[i].draw_frame;
            //
            if (img_id != INVALID_OBJECT_ID)
            {
                ext_cfa = get_map_object_image(img_id, img_frame);
                ext_rle = NULL;
                if (ext_cfa)
                    ext_cf = ext_cfa->cake_frame;
                if (ext_cf)
                { 
                    ext_rle = ext_cf->rle; ext_pl = ext_cf->poly; 
                }
                if (ext_rle)
                {
                    px = g_magic_area[i].x;
                    py = g_magic_area[i].y;
                    pz = 0;
                    //
                    ox = -ext_cf->poly_rx;
                    oy = -ext_cf->poly_ry;
                    sx = px - map_data.map_sx + ox;
                    sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT * 2 / 4 + oy;
                    put_rle(sx, sy, ext_rle, bitmap);
                }
            }
        }
    
    }
    
/*
    if(!is_magic_area_visible())
        return;

    switch(magic_area.type)
    {
    case MAGIC_AREA_TYPE_CIRCLE:
        break;
    case MAGIC_AREA_TYPE_RECTANGLE:
        break;
    case MAGIC_AREA_TYPE_LINE:
        {
            SLONG   dir, dx, dy;
            SLONG   x, y;
            CAKE_FRAME_ANI  *cfa;
            CAKE_FRAME  *cf;
            
            dx = magic_area.dest_x - magic_area.orig_x;
            dy = magic_area.dest_y - magic_area.orig_y;
            dir = ApproachScreenAxisDirEx(dx, dy, 16);
            cfa = get_specify_cake_frame_ani(magic_area.line_cfa, dir);
            if(cfa)
            {
                cf = cfa->cake_frame;
                if(cf)
                {
                    x = cf->frame_rx - l_line_area_stand_offset[dir].x + magic_area.orig_x - map_data.map_sx;
                    y = cf->frame_ry - l_line_area_stand_offset[dir].y + magic_area.orig_y - map_data.map_sy;
                    alpha_put_rle(x, y, cf->rle, bitmap, 144);
                }
            }
        }
        break;
    }
*/    
}
/*
SLONG   is_magic_area_visible(void)
{
    if(magic_area.flag & MAGIC_AREA_FLAG_VISIBLE)
        return  TRUE;
    return  FALSE;
}
*/
/*
void    set_magic_area_orig_position(SLONG orig_x, SLONG orig_y)
{
    magic_area.orig_x = orig_x;
    magic_area.orig_y = orig_y;
}


void    set_magic_area_dest_position(SLONG dest_x, SLONG dest_y)
{
    magic_area.dest_x = dest_x;
    magic_area.dest_y = dest_y;
}
*/
/*
void    set_magic_area_range(SLONG range)
{
    magic_area.range = range;
}


void    set_magic_area_type(SLONG type)
{
    magic_area.type = type;
}
*/
/*
void    set_magic_area_visible(SLONG is_visible)
{
    if(is_visible) 
        magic_area.flag |= MAGIC_AREA_FLAG_VISIBLE;
    else
        magic_area.flag &= ~MAGIC_AREA_FLAG_VISIBLE;
}
*/

//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

