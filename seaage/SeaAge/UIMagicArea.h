/*
**	UIMagicArea.h
**	magic area functions.
**
**	Jack, 2002/09/26.
*/
#ifndef _UIMAGICAREA_H_
#define _UIMAGICAREA_H_
 

// D E F I N E S //////////////////////////////////////////////////////////////////////////////////////////////////
/*
//------------
//�ؼнd������
//--------------------------------------
#define MAGIC_AREA_TYPE_CIRCLE              1   //��νd��
#define MAGIC_AREA_TYPE_RECTANGLE           2   //��νd��
#define MAGIC_AREA_TYPE_LINE                3   //�u�ʽd��
//
//---------------
//�ؼнd��лx
//--------------------------------------
#define MAGIC_AREA_FLAG_VISIBLE         0x00000001  //�d��i��


// S T R U C T U R E S ////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagMAGIC_AREA
{
    SLONG   flag;           //�лx
    SLONG   type;           //�ؼнd������
    SLONG   orig_x;         //�ؼнd���ǰ_�l�I�y�� X
    SLONG   orig_y;         //�ؼнd���ǰ_�l�I�y�� Y
    SLONG   dest_x;         //�ؼнd���ǥؼ��I�y�� X
    SLONG   dest_y;         //�ؼнd���ǥؼЮy�� Y
    SLONG   range;          //�ؼнd�򪺤j�p
    //
    SLONG   magic_no;       //���b�I�k���k�N�s��
    //
    CAKE_FRAME_ANI  *line_cfa;      //�u�ʰϰ����
    CAKE_FRAME_ANI  *circle_cfa;    //��ΰϰ����
    CAKE_FRAME_ANI  *rectangle_cfa; //�x�ΰϰ����
} MAGIC_AREA, *LPMAGIC_AREA;
*/
//�ؼмлx
//--------------------------------------
#define     MAX_MAGIC_AREA      MAX_CHARACTER_TEAM_MEMBERS
//
#define MAGIC_AREA_FLAG_VISIBLE         0x00000001  //�d��i��

// S T R U C T U R E S ////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagMAGIC_AREA
{
    SLONG   flag;           //�лx
    SLONG   x;              //�ؼнd���ǰ_�l�I�y�� X
    SLONG   y;              //�ؼнd���ǰ_�l�I�y�� Y
    //
    SLONG   magic_no;       //���b�I�k���k�N�s��
    SLONG   npc_no;         //���]�k�}��.�ϥΪ�
    //
    SLONG   new_imd_id;
    SLONG   new_frame;
    //
    SLONG   draw_img_id;     //�����b����w�������ɪ�ID
    SLONG   draw_frame;
} MAGIC_AREA, *LPMAGIC_AREA;

// G L O B A L S //////////////////////////////////////////////////////////////////////////////////////////////////
//extern  MAGIC_AREA  magic_area;
extern  MAGIC_AREA  g_magic_area[MAX_CHARACTER_TEAM_MEMBERS];

// F U N C T I O N S //////////////////////////////////////////////////////////////////////////////////////////////
SLONG   init_magic_area(void);
void    free_magic_area(void);
//
void	clear_magic_area(void);
/*
void    set_magic_area_visible(SLONG is_visible);
SLONG   is_magic_area_visible(void);
void    set_magic_area_orig_position(SLONG orig_x, SLONG orig_y);
void    set_magic_area_dest_position(SLONG dest_x, SLONG dest_y);
void    set_magic_area_range(SLONG range);
void    set_magic_area_type(SLONG type);
*/
void    set_magic_area_visible(SLONG index, SLONG is_visible);
SLONG   is_magic_area_visible(SLONG index);
void    set_magic_area_position(SLONG index, SLONG x, SLONG y);
void    set_magic_magic_no(SLONG index, SLONG magic_no);
void    set_magic_npc_no(SLONG index, SLONG npc_no);

void    redraw_magic_area(BMP *bitmap);

void    add_magic_area(SLONG x, SLONG y, SLONG dir, SLONG npc_no, SLONG magic_no, SLONG level);
void    delete_magic_area(SLONG npc_no,SLONG magic_no);

#endif//_UIMAGICAREA_H_
