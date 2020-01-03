/*
**  ImageRim.h
**  image rim functions header.
**
**  Jack, 2002.5.9.
**
*/
#ifndef _IMAGERIM_H_
#define _IMAGERIM_H_


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_RIM_IMAGES          2   //1種訊息邊框
#define MAX_TALK_RIM_IMAGES     3   //3種對話邊框


//
// STRUCTURE ////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct tagIMAGE_RIM_INFO 
{
	SLONG	left_gap;
	SLONG	right_gap;
	SLONG	top_gap;
	SLONG	bottom_gap;
} IMAGE_RIM_INFO, *LPIMAGE_RIM_INFO;


//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
//訊息邊框
int     init_image_rim(void);
void    active_image_rim(int active);
void    free_image_rim(void);
//
SLONG	set_rim_image(SLONG index);
void	get_image_rim_info(SLONG index, IMAGE_RIM_INFO *info);
void    put_image_rim(SLONG sx, SLONG sy, SLONG xl, SLONG yl, void *vbitmap);
//
//對話邊框
int     init_talk_rim(void);
void    active_talk_rim(int active);
void    free_talk_rim(void);
//
SLONG	set_talk_rim(SLONG index);
void    put_talk_rim(SLONG sx, SLONG sy, SLONG xl, SLONG yl, void *vbitmap);
//
int		init_npc_shadow_image(void);
void	free_npc_shadow_image(void);
void	put_npc_shadow_image(SLONG cx, SLONG cy, SLONG shadow_size, SLONG flags, void *vbitmap);


#endif//_IMAGERIM_H_
