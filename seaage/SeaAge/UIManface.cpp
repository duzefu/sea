/*
**	UIManface.cpp
**	UI of manchar face.
**
**	Jack, 2002/06/21.
**
**	Zhang Zhaohui, 2003.2.12
**			modified for qq manface
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "UIManFace.h"
#include "ClientMain.h"
#include "PosData.h"

typedef struct  tagMANFACE_IMAGE
{
    CAKE_FRAME_ANI  *cfa;           //ani image pointer
    SLONG           frames;         //total ani image frames
    CAKE_FRAME      *cf[1];         //image of each frame
} MANFACE_IMAGE, *LPMANFACE_IMAGE;

// ZZH, [2003.2.12 17:25]
// MANFACE_IMAGE   *manface_image = NULL;

MANFACE_IMAGE   *manface_image[MAX_MANFACE_IMAGE];
SLONG	manface_index = 0;


/******************************************************************************************************************/
/* MANFACE FUNCTIONS                                                                                              */
/******************************************************************************************************************/
int     init_manface(void)
{
    CAKE_FRAME_ANI  *cfa = NULL, *p = NULL;
	SLONG	j;
    SLONG   result, i, frames;
	char manface_filename[][40] = {	"menu\\manface.cak",
									"menu\\manface2.cak" };

	for ( j = 0; j < MAX_MANFACE_IMAGE; j++ )
		manface_image[j] = NULL;

    set_data_file(packed_menu_file);

    for ( j = 0; j < MAX_MANFACE_IMAGE; j++ )
	{
		result = load_cake_frame_ani_from_file((USTR*)manface_filename[j], &cfa);
		if(TTN_OK != result)
			return  -1;
		
		frames = count_cake_frames(cfa);
		manface_image[j] = (MANFACE_IMAGE*)malloc(sizeof(MANFACE_IMAGE) + (frames-1) * sizeof(CAKE_FRAME*));
		if(NULL == manface_image[j])
			return  -2;
		
		manface_image[j]->cfa = cfa;
		manface_image[j]->frames = frames;

		for(i=0; i<frames; i++)
		{
			p = get_specify_cake_frame_ani(cfa, i);
			manface_image[j]->cf[i] = p->cake_frame;
		}
	}
	manface_index = 0;
    return  0;
}


void    free_manface(void)
{
	SLONG j;
	for ( j = 0; j < MAX_MANFACE_IMAGE; j++ )
	{
		if ( !manface_image[j] )
			continue;

		if ( manface_image[j]->cfa )
			destroy_cake_frame_ani( &manface_image[j]->cfa );

		free( manface_image[j] );

		manface_image[j] = NULL;
	}
}


void    set_manface(MANFACE_DATA *mf, SLONG manchar_index, SLONG eye_index, SLONG mouth_index)
{
    mf->manchar_index = manchar_index;
    mf->eye_index = eye_index;
    mf->mouth_index = mouth_index;
}


void    redraw_manface(SLONG sx, SLONG sy, MANFACE_DATA *mf, BMP *bitmap)
{
    SLONG   mouth_frame, eye_frame;
    SLONG   x, y;
    CAKE_FRAME  *cf;

    if(! manface_image[manface_index])
        return;
    if(! mf)
        return;
    mouth_frame = mf->manchar_index * (MAX_MANFACE_MOUTH + MAX_MANFACE_EYES) 
        + mf->mouth_index * 2;
    eye_frame = mf->manchar_index * (MAX_MANFACE_MOUTH + MAX_MANFACE_EYES)
        + mf->eye_index * 2 + 1;
    if(mouth_frame >= 0 && mouth_frame < manface_image[manface_index]->frames)
    {
        cf = manface_image[manface_index]->cf[mouth_frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
    if(eye_frame >= 0 && eye_frame < manface_image[manface_index]->frames)
    {
        cf = manface_image[manface_index]->cf[eye_frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
}


void    get_character_manface(SLONG index, MANFACE_DATA *face)
{
    SLONG   career, sex, manchar_index;
    SLONG   eye_index, mouth_index;

    career = GetCharacterCareer(index);
    sex = GetCharacterSex(index);
    manchar_index = get_character_main_face(career, sex);
    eye_index = GetCharacterEyes(index);
    mouth_index = GetCharacterMouth(index);
    set_manface(face, manchar_index, eye_index, mouth_index);
}


SLONG	set_manface_index( SLONG index )
{
	SLONG last_index = manface_index;

	if ( index >= 0 && index < MAX_MANFACE_IMAGE )
		manface_index = index;

	return last_index;
}

void	redraw_scale_manface( SLONG sx, SLONG sy, SLONG w, SLONG h, MANFACE_DATA *mf, BMP *bitmap )
{
    SLONG   mouth_frame, eye_frame;
    SLONG   x, y;
    CAKE_FRAME  *cf;
	SLONG e_h, m_h, o_h = 0;
	SLONG m_y;
	
    if(! manface_image[manface_index])
        return;
    if(! mf)
        return;
    mouth_frame = mf->manchar_index * (MAX_MANFACE_MOUTH + MAX_MANFACE_EYES) 
        + mf->mouth_index * 2;
    eye_frame = mf->manchar_index * (MAX_MANFACE_MOUTH + MAX_MANFACE_EYES)
        + mf->eye_index * 2 + 1;

	if(mouth_frame >= 0 && mouth_frame < manface_image[manface_index]->frames)
    {        
		cf = manface_image[manface_index]->cf[mouth_frame];
		o_h = cf->rle->h;
		m_h = cf->rle->h;
		m_y = cf->frame_ry;
	}

    if(eye_frame >= 0 && eye_frame < manface_image[manface_index]->frames)
    {
        cf = manface_image[manface_index]->cf[eye_frame];
		e_h = cf->rle->h;
		o_h += cf->rle->h - ( e_h - m_y );
	}
	if ( o_h != 0 )
	{
		e_h = e_h * h / o_h;
		m_h = m_h * h / o_h;
		m_y = m_y * h / o_h;
	}

    if ( eye_frame >= 0 && eye_frame < manface_image[manface_index]->frames)
    {
        cf = manface_image[manface_index]->cf[eye_frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        scale_put_rle( x, y, w, e_h, cf->rle, bitmap );
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             if ( mouth_frame >= 0 && mouth_frame < manface_image[manface_index]->frames )
    {
        cf = manface_image[manface_index]->cf[mouth_frame];
        x = sx + cf->frame_rx;
        // y = sy + cf->frame_ry;
		y = sy + m_y;
        scale_put_rle( x, y, w, m_h, cf->rle, bitmap );
    }
	
}