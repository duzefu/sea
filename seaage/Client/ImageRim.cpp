/*
**  ImageRim.cpp
**  image rim functions.
**
**  Jack, 2002.5.9.
**
*/
#include "mainfun.h"
#include "ErrorMsg.h"
#include "ImageRim.h"
#include "ClientMain.h"


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////

//�T����ت���ӹϯ��ީw�q
typedef enum    RIM_INDEX_ENUMS
{   RIM_INDEX_LU    =   0,  //left up corner
RIM_INDEX_RU        =   1,  //right up corner
RIM_INDEX_RD        =   2,  //right down corner
RIM_INDEX_LD        =   3,  //left down corner
RIM_INDEX_LT        =   4,  //left
RIM_INDEX_RT        =   5,  //right
RIM_INDEX_UP        =   6,  //up
RIM_INDEX_DN        =   7,  //down
RIM_INDEX_CT        =   8,  //center
} RIM_INDEX_ENUMS;


typedef enum    TALK_RIM_INDEX_ENUMS
{   TALK_RIM_INDEX_LU   =   0,  //���W��
TALK_RIM_INDEX_UP       =   1,  //�W
TALK_RIM_INDEX_RU       =   2,  //�k�W��
TALK_RIM_INDEX_LT       =   3,  //��
TALK_RIM_INDEX_CT       =   4,  //����
TALK_RIM_INDEX_RT       =   5,  //�k
TALK_RIM_INDEX_LD       =   6,  //���U
TALK_RIM_INDEX_DN       =   7,  //�U
TALK_RIM_INDEX_RD       =   8,  //�k�U
TALK_RIM_INDEX_PR       =   9,  //���V�k
TALK_RIM_INDEX_PL       =   10, //���V��
} TALK_RIM_INDEX_ENUMS;

// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
//�T����عϹ����
typedef struct  tagRIM_IMAGE
{
    CAKE_FRAME_ANI  *cfa;   //rim images
    CAKE_FRAME  *cf[9];     //rim block images pointer
    SLONG   ox[9];          //block image offset x
    SLONG   oy[9];          //block image offset y
    SLONG   xl[9];          //block image width
    SLONG   yl[9];          //block image height
} RIM_IMAGE, *LPRIM_IMAGE;


//�����عϹ����
typedef struct tagTALK_RIM_IMAGE 
{
    CAKE_FRAME_ANI  *cfa;   //talk rim images
    CAKE_FRAME  *cf[11];    //talk rim block images pointer
    SLONG   xl[11];         //block image width
    SLONG   yl[11];         //block image height
} TALK_RIM_IMAGE, *LPTALK_RIM_IMAGE;


//GLOBALS /////////////////////////////////////////////////////////////////////////////////
RIM_IMAGE       rim_image[MAX_RIM_IMAGES];
TALK_RIM_IMAGE  talk_rim_image[MAX_TALK_RIM_IMAGES];


//STATICS /////////////////////////////////////////////////////////////////////////////////
static  SLONG   rim_image_index = 0;
static  SLONG   talk_rim_image_index = 0;


/******************************************************************************************************************/
/* �T������ب��                                                                                                 */
/******************************************************************************************************************/
int     init_image_rim(void)
{
    SLONG   i, j;
    USTR    filename[_MAX_FNAME];
    SLONG   result, ret;
    CAKE_FRAME_ANI  *cfa = NULL;
    CAKE_FRAME  *cf = NULL;

    ret = 0;
    for(i=0; i<MAX_RIM_IMAGES; i++)
    {
        rim_image[i].cfa = NULL;
        for(j=0; j<9; j++)
        {
            rim_image[i].cf[j] = NULL;
            rim_image[i].ox[j] = 0;
            rim_image[i].oy[j] = 0;
            rim_image[i].xl[j] = 0;
            rim_image[i].yl[j] = 0;
        }
    }
    for(i=0; i<MAX_RIM_IMAGES; i++)
    {
        set_data_file(packed_menu_file);
        sprintf((char *)filename, "menu\\rimimg%d.cak", i);
        result = load_cake_frame_ani_from_file((USTR*)filename, &rim_image[i].cfa );
        if(result == TTN_OK)
        {
            for(j=0; j<9; j++)
            {
                cfa = get_specify_cake_frame_ani(rim_image[i].cfa, j);
                rim_image[i].cf[j] = cfa->cake_frame;
                rim_image[i].ox[j] = rim_image[i].cf[j]->frame_rx;
                rim_image[i].oy[j] = rim_image[i].cf[j]->frame_ry;
                rim_image[i].xl[j] = rim_image[i].cf[j]->rle->w;
                rim_image[i].yl[j] = rim_image[i].cf[j]->rle->h;
            }
        }
        else
        {
            errormsg_file_open((char *)filename);
            ret = -1;
            break;
        }
    }
    rim_image_index = 0;

    return  ret;
}


void    active_image_rim(int active)
{
}


void    free_image_rim(void)
{
    SLONG   i, j;

    for(i=0; i<MAX_RIM_IMAGES; i++)
    {
        if( rim_image[i].cfa )
            destroy_cake_frame_ani( &rim_image[i].cfa );
        rim_image[i].cfa = NULL;
        for(j=0; j<9; j++)
        {
            rim_image[i].cf[j] = NULL;
            rim_image[i].ox[j] = 0;
            rim_image[i].oy[j] = 0;
            rim_image[i].xl[j] = 0;
            rim_image[i].yl[j] = 0;
        }
    }
}


SLONG    set_rim_image(SLONG index)
{
	SLONG	last_index;

    if(index >= 0 && index < MAX_RIM_IMAGES)
    {
		last_index = rim_image_index;
        rim_image_index = index;
    }

	return	last_index;
}


void	get_image_rim_info(SLONG index, IMAGE_RIM_INFO *info)
{
    RIM_IMAGE   *ri;
    if(index >= 0 && index < MAX_RIM_IMAGES)
    {
		ri = &rim_image[index];
		if(info)
		{
			info->left_gap = ri->xl[RIM_INDEX_LT];
			info->right_gap = ri->xl[RIM_INDEX_RT];
			info->top_gap = ri->yl[RIM_INDEX_UP];
			info->bottom_gap = ri->yl[RIM_INDEX_DN];
		}
    }
}


void    put_image_rim(SLONG sx, SLONG sy, SLONG xl, SLONG yl, void *vbitmap)
{
    BMP *bitmap = (BMP *)vbitmap;
    RIM_IMAGE   *ri = &rim_image[rim_image_index];
    CAKE_FRAME  *cf = NULL;
    SLONG   i, j, disp_x, disp_y;
    SLONG   x_segments, y_segments;

    x_segments = (xl + ri->xl[RIM_INDEX_UP] - 1) / ri->xl[RIM_INDEX_UP];
    y_segments = (yl + ri->yl[RIM_INDEX_LT] - 1) / ri->yl[RIM_INDEX_LT];

    xl = x_segments * ri->xl[RIM_INDEX_UP];
    yl = y_segments * ri->yl[RIM_INDEX_LT];

    //left up corner ----------------------------------------------------------
    {
        disp_x = sx - ri->xl[RIM_INDEX_LU];
        disp_y = sy - ri->yl[RIM_INDEX_LU];
        cf = ri->cf[RIM_INDEX_LU];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //right up corner ---------------------------------------------------------
    {
        disp_x = sx + xl;
        disp_y = sy - ri->yl[RIM_INDEX_RU];
        cf = ri->cf[RIM_INDEX_RU];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //left down corner --------------------------------------------------------
    {
        disp_x = sx - ri->xl[RIM_INDEX_LD];
        disp_y = sy + yl;
        cf = ri->cf[RIM_INDEX_LD];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //right down corner -------------------------------------------------------
    {
        disp_x = sx + xl;
        disp_y = sy + yl;
        cf = ri->cf[RIM_INDEX_RD];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //up line ------------------------------------------------------------------
    {
        disp_x = sx;
        disp_y = sy - ri->yl[RIM_INDEX_UP];
        cf = ri->cf[RIM_INDEX_UP];
        for(i=0; i<x_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, ri->xl[RIM_INDEX_UP], 8, SYSTEM_YELLOW, bitmap);
            disp_x += ri->xl[RIM_INDEX_UP];
        }
    }

    //down line ------------------------------------------------------------------
    {
        disp_x = sx;
        disp_y = sy + yl;
        cf = ri->cf[RIM_INDEX_DN];
        for(i=0; i<x_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, ri->xl[RIM_INDEX_DN], 8, SYSTEM_YELLOW, bitmap);
            disp_x += ri->xl[RIM_INDEX_DN];
        }
    }

    //left line -----------------------------------------------------------------
    {
        disp_x = sx - ri->xl[RIM_INDEX_LT];
        disp_y = sy;
        cf = ri->cf[RIM_INDEX_LT];
        for(i=0; i<y_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, 8, ri->yl[RIM_INDEX_LT], SYSTEM_YELLOW, bitmap);
            disp_y += ri->yl[RIM_INDEX_LT];
        }
    }

    //right line ----------------------------------------------------------------
    {
        disp_x = sx + xl;
        disp_y = sy;
        cf = ri->cf[RIM_INDEX_RT];
        for(i=0; i<y_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, 8, ri->yl[RIM_INDEX_RT], SYSTEM_YELLOW, bitmap);
            disp_y += ri->yl[RIM_INDEX_RT];
        }
    }

    //center -------------------------------------------------------------------
    disp_y = sy;
    cf = ri->cf[RIM_INDEX_CT];
    for(j=0; j<y_segments; j++)
    {
        disp_x = sx;
        for(i=0; i<x_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            disp_x += ri->xl[RIM_INDEX_CT];
        }
        disp_y += ri->yl[RIM_INDEX_CT];
    }
}



/******************************************************************************************************************/
/* ��ܮ���ب��                                                                                                 */
/******************************************************************************************************************/
int     init_talk_rim(void)
{
    SLONG   i, j;
    USTR    filename[_MAX_FNAME];
    SLONG   result, ret;
    CAKE_FRAME_ANI  *cfa = NULL;
    CAKE_FRAME  *cf = NULL;

    ret = 0;
    for(i=0; i<MAX_TALK_RIM_IMAGES; i++)
    {
        talk_rim_image[i].cfa = NULL;
        for(j=0; j<11; j++)
        {
            talk_rim_image[i].cf[j] = NULL;
        }
    }
    for(i=0; i<MAX_TALK_RIM_IMAGES; i++)
    {
        set_data_file(packed_menu_file);
        sprintf((char *)filename, "menu\\talkbox%d.cak", i);
        result = load_cake_frame_ani_from_file((USTR*)filename, &talk_rim_image[i].cfa );
        if(result == TTN_OK)
        {
            for(j=0; j<11; j++)
            {
                cfa = get_specify_cake_frame_ani(talk_rim_image[i].cfa, j);
                talk_rim_image[i].cf[j] = cfa->cake_frame;
                talk_rim_image[i].xl[j] = talk_rim_image[i].cf[j]->rle->w;
                talk_rim_image[i].yl[j] = talk_rim_image[i].cf[j]->rle->h;
            }
        }
        else
        {
            errormsg_file_open((char *)filename);
            ret = -1;
            break;
        }
    }
    talk_rim_image_index = 0;

    return  ret;
}


void    active_talk_rim(int active)
{
}


void    free_talk_rim(void)
{
    SLONG   i, j;

    for(i=0; i<MAX_TALK_RIM_IMAGES; i++)
    {
        destroy_cake_frame_ani( &talk_rim_image[i].cfa );
        for(j=0; j<11; j++)
        {
            talk_rim_image[i].cf[j] = NULL;
        }
    }
}


SLONG	set_talk_rim(SLONG index)
{
	SLONG	last_index;

	last_index = -1;
    if(index >= 0 && index < MAX_TALK_RIM_IMAGES)
    {
		last_index = talk_rim_image_index;
        talk_rim_image_index = index;
    }
	return	last_index;
}


//�\�� : �b���w�ؼнw�Ĥ��e�@�ӹ�ܮ�
//�Ѽ� : SLONG  sx      -> ��ܮؤ����ϰ쪺���W���y�� X
//       SLONG  sy      -> ��ܮؤ����ϰ쪺���W���y�� Y
//       SLONG  xl      -> ��ܮؤ����ϰ쪺�e��
//       SLONG  yl      -> ��ܮؤ����ϰ쪺����
void    put_talk_rim(SLONG sx, SLONG sy, SLONG xl, SLONG yl, void *vbitmap)
{
    BMP *bitmap = (BMP *)vbitmap;
    TALK_RIM_IMAGE   *ri = &talk_rim_image[talk_rim_image_index];
    CAKE_FRAME  *cf = NULL;
    SLONG   i, j, disp_x, disp_y;
    SLONG   x_segments, y_segments;
    SLONG   ptr_index, ptr_left;

    //�p�⤤���ϰ�ݭn�h�֭Ӥp������_��, �è̦���xl,yl���վ�.
    x_segments = xl / ri->xl[TALK_RIM_INDEX_CT];
    y_segments = yl / ri->yl[TALK_RIM_INDEX_CT];
    xl = x_segments * ri->xl[TALK_RIM_INDEX_CT];
    yl = y_segments * ri->yl[TALK_RIM_INDEX_CT];

    //center -------------------------------------------------------------------
    disp_y = sy;
    cf = ri->cf[TALK_RIM_INDEX_CT];
    for(j=0; j<y_segments; j++)
    {
        disp_x = sx;
        for(i=0; i<x_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            disp_x += ri->xl[TALK_RIM_INDEX_CT];
        }
        disp_y += ri->yl[TALK_RIM_INDEX_CT];
    }

    //left up corner ----------------------------------------------------------
    {
        disp_x = sx - ri->xl[TALK_RIM_INDEX_LU];
        disp_y = sy - ri->yl[TALK_RIM_INDEX_LU];
        cf = ri->cf[TALK_RIM_INDEX_LU];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //right up corner ---------------------------------------------------------
    {
        disp_x = sx + xl;
        disp_y = sy - ri->yl[TALK_RIM_INDEX_RU];
        cf = ri->cf[TALK_RIM_INDEX_RU];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //left down corner --------------------------------------------------------
    {
        disp_x = sx - ri->xl[TALK_RIM_INDEX_LD];
        disp_y = sy + yl;
        cf = ri->cf[TALK_RIM_INDEX_LD];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //right down corner -------------------------------------------------------
    {
        disp_x = sx + xl;
        disp_y = sy + yl;
        cf = ri->cf[TALK_RIM_INDEX_RD];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
    }

    //up line ------------------------------------------------------------------
    {
        disp_x = sx;
        disp_y = sy - ri->yl[TALK_RIM_INDEX_UP];
        cf = ri->cf[TALK_RIM_INDEX_UP];
        for(i=0; i<x_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, ri->xl[RIM_INDEX_UP], 8, SYSTEM_YELLOW, bitmap);
            disp_x += ri->xl[TALK_RIM_INDEX_UP];
        }
    }

    //left line ------------------------------------------------------------------
    {
        disp_x = sx - ri->xl[TALK_RIM_INDEX_LT];
        disp_y = sy;
        cf = ri->cf[TALK_RIM_INDEX_LT];
        for(i=0; i<y_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, 8, ri->yl[RIM_INDEX_LT], SYSTEM_YELLOW, bitmap);
            disp_y += ri->yl[TALK_RIM_INDEX_LT];
        }
    }

    //right line ----------------------------------------------------------------
    {
        disp_x = sx + xl;
        disp_y = sy;
        cf = ri->cf[TALK_RIM_INDEX_RT];
        for(i=0; i<y_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            //put_box(disp_x, disp_y, 8, ri->yl[RIM_INDEX_RT], SYSTEM_YELLOW, bitmap);
            disp_y += ri->yl[TALK_RIM_INDEX_RT];
        }
    }

    //down line ------------------------------------------------------------------
    {
        //��ܶ}�f���V����2��e��.
        //�p���ܫ��V���}�f��V�M�v�����Ǹ�
        ptr_index = x_segments / 2;
        if(x_segments % 2) //x_segments���_��
        {
            ptr_left = true;
        }
        else
        {
            ptr_left = false;
        }
        disp_y = sy + yl;

        //��ܫ��V�}�f���e������
        disp_x = sx;
        cf = ri->cf[TALK_RIM_INDEX_DN];
        for(i=0; i<ptr_index; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            disp_x += ri->xl[TALK_RIM_INDEX_DN];
        }

        //��ܫ��V
        if(ptr_left)
            cf = ri->cf[TALK_RIM_INDEX_PL];
        else
            cf = ri->cf[TALK_RIM_INDEX_PR];
        put_rle(disp_x, disp_y, cf->rle, bitmap);
        disp_x += 2 * ri->xl[TALK_RIM_INDEX_DN];    //�e�׬�2��e��

        //��ܫ��V�}�f���᭱����
        cf = ri->cf[TALK_RIM_INDEX_DN];
        for(i=ptr_index+2; i<x_segments; i++)
        {
            put_rle(disp_x, disp_y, cf->rle, bitmap);
            disp_x += ri->xl[TALK_RIM_INDEX_DN];
        }
    }
}



/************************************************************************************************************/
/* NPC IMAGE SHADOW FUNCTIONS                                                                               */
/************************************************************************************************************/
typedef	struct tagNPC_SHADOW_IMAGE 
{
    CAKE_FRAME_ANI  *cfa;   //npc shadow images
    CAKE_FRAME  *cf[4];		//shadow image of each frame
} NPC_SHADOW_IMAGE, *LPNPC_SHADOW_IMAGE;


NPC_SHADOW_IMAGE	l_npc_shadow_image;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int		init_npc_shadow_image(void)
{
	char	filename[_MAX_FNAME];
	SLONG	result, total_frames;
	SLONG	i, valid_frames;
	CAKE_FRAME_ANI	*cfa;

	set_data_file(packed_menu_file);
	sprintf((char *)filename, "menu\\shadow.cak");
	result = load_cake_frame_ani_from_file((USTR*)filename, &l_npc_shadow_image.cfa );
	if(TTN_OK != result)
		return	-1;

	total_frames = count_cake_frames(l_npc_shadow_image.cfa);
	for(i=0; i<4; i++)
	{
		valid_frames = min(i, total_frames-1);
		cfa = get_specify_cake_frame_ani(l_npc_shadow_image.cfa, valid_frames);
		l_npc_shadow_image.cf[i] = cfa->cake_frame;
	}

	return	0;
}


void	free_npc_shadow_image(void)
{
	SLONG	i;

	if(l_npc_shadow_image.cfa)
		destroy_cake_frame_ani(&l_npc_shadow_image.cfa);
	l_npc_shadow_image.cfa = NULL;
	for(i=0; i<4; i++)
	{
		l_npc_shadow_image.cf[i] = NULL;
	}
}


void	put_npc_shadow_image(SLONG cx, SLONG cy, SLONG shadow_size, SLONG flags, void *vbitmap)
{
	BMP *bitmap = (BMP*)vbitmap;
	RLE	*rle = NULL;
	SLONG	sx, sy;

	if(shadow_size < 0 || shadow_size > 3)
		return;

	rle = l_npc_shadow_image.cf[shadow_size]->rle;
	if(! rle)
		return;

	sx = cx - rle->w/2;
	sy = cy - rle->h/2;
	put_rle(sx, sy, rle, bitmap);

}

