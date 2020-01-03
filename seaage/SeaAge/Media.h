/*
**	Media.h 
**	Media file access functions.
**
**	Stephen, 2002.7.1.
**		Created.
**
**	Jack, 2003.1.21.
**		Added for SeaAge Editor.
**
*/
#ifndef _MEDIA_H_INCLUDE_
#define _MEDIA_H_INCLUDE_
#include "rays.h"
#include "vbmp.h"
#include "xsound.h"


// ---------- Define Ani command type
#define ANI_MAIN_COMMAND			1
#define ANI_DATABASE				2
#define ANI_EFFECT1					3
#define ANI_EFFECT2					4

// ---------- Define Media type
#define FILE_TYPE_UNKNOW			0
#define FILE_TYPE_WAV				1
#define FILE_TYPE_IMG				2

// --------- Define MDA command
#define MDA_COMMAND_ZOOM			0x0001				// 100 = zoom1, 200 = zoom2, 50 = zoom0.5,...
#define MDA_COMMAND_NEXT_FRAME		0x0002				//
#define MDA_COMMAND_FIRST			0x0004				//
#define MDA_COMMAND_LAST			0x0008				//
#define MDA_COMMAND_LOOP			0x0010				//
#define MDA_COMMAND_ALPHA			0x0020				// 0 ~ 255
#define MDA_COMMAND_HIGHTLIGHT		0x0040				// no other parameter
#define MDA_COMMAND_ASSIGN          0x0080				// no other parameter
#define MDA_COMMAND_PALETTE			0x0100				// use system_palette 上圖
#define MDA_COMMAND_PALETTE_OR		0x0200				// 當前 palette 與 system_palette OR 後上圖
#define MDA_COMMAND_PALETTE_AND		0x0400				// 當前 palette 與 system_palette AND 後上圖

#define MDA_MASK_NEXT_FRAME         0xFFFD



#define IMG_COPY					0xFF    // Copy + Length + Data... ( Total Length + 3 Byte )
#define IMG_SKIP					0xFE    // Skip + Length  ( Total 3 Byte )
#define IMG_LINE					0xFD    // One Line End


// ----------- define 海之樂章參數 ----------------
#define SEA_CHANGE_COLOR_TYPE		7		// 設定海樂換裝數量(Part) 

#define RGB_EFFECT_NONE         0x00
#define RGB_EFFECT_COPY         0x01
#define RGB_EFFECT_AND          0x02
#define RGB_EFFECT_OR           0x04
#define RGB_EFFECT_NOT          0x08
#define RGB_EFFECT_ANI_R        0x10
#define RGB_EFFECT_ANI_G        0x20
#define RGB_EFFECT_ANI_B        0x40

#define RGB_EFFECT_MASK_COPY    0xFE      // 1111 1110   0xFE
#define RGB_EFFECT_MASK_AND     0xFD      // 1111 1101   0xFD
#define RGB_EFFECT_MASK_OR      0xFB      // 1111 1011   0xFB
#define RGB_EFFECT_MASK_NOT     0xF7      // 1111 0111   0xF7
#define RGB_EFFECT_MASK_ANI_R   0xEF      // 1110 1111   0xEF
#define RGB_EFFECT_MASK_ANI_G   0xDF      // 1101 1111   0xDF
#define RGB_EFFECT_MASK_ANI_B   0xBF      // 1011 1111   0xBF


// ----------- typedef struct area --------------
typedef struct MDA_HEAD_STRUCT
{
	UCHR copyright[19];          // 'RAYS MEDIA FILE' 檔案說明, 檢查檔案類型用
	UCHR text_end_code;          // 0x1A 文字檔結束碼
	SLONG version;               // 版本 100
	SLONG total_database_frame;  // 資料庫裡總共有多少筆資料
	SLONG total_ani_frame;       // 動作庫裡總共有多少筆動作資料
	SLONG data_start_offset;     // 資料庫開始位置(從頭開始)
	SLONG ani_start_offset;      // 動作表開始位置(從頭開始)
} MDA_HEAD;


typedef struct IMG256_HEAD_STRUCT
{
	UCHR copyright[19];         // 'RAYS IMG256 FILE' 檔案說明, 檢查檔案類型用
	UCHR text_end_code;         // 0x1A 文字檔結束碼
	UHINT xlen;					// 影像的寬
	UHINT ylen;					// 影像的高
	UHINT orig_x;               // 原始座標位置
	UHINT orig_y;
	SHINT center_x;             // 重心點座標
	SHINT center_y;
	SLONG image_compress_size;	// Image 資料壓縮大小
	UCHR palette[768];			// 256色色盤
	SLONG img_start_offset;		// Image 資料開始位置
} IMG256_HEAD;



typedef struct POSITION_STRUCT
{
	SLONG x;
	SLONG y;
} POSITION;



typedef struct OFFSET_SIZE_STRUCT
{
	SLONG offset;
	SLONG size;
} OFFSET_SIZE;


typedef struct INDEX_OFFSET_SIZE_STRUCT
{
	UCHR name[32];
	SLONG offset;
	SLONG size;
} INDEX_OFFSET_SIZE;




typedef struct IMG256_IMAGE_STRUCT
{
	UCHR *image;
	IMG256_HEAD img256_head;
} IMG256_IMAGE;


typedef struct RGB_DATA_STRUCT
{
	UCHR effect;	// 紀錄特效
	UCHR r;			// 0~255
	UCHR g;			// 0~255
	UCHR b;			// 0~255
	UCHR scroll;	// 目前顏色遞增遞減的 flag, init 0.
} RGB_DATA;




#define ROOT_NODE		-1
#define END_NODE		-2
typedef struct MDA_NODE_STRUCT
{
	ULONG father_node;		// 父節點位置
	ULONG chind_node;		// 子節點位置
	ULONG equ_node;			// 同類型節點下一個位置
	UCHR *body_idx;			// 命令字串位置 point
	SLONG database_idx;		// 資料庫位置
} MDA_NODE;


#define MDA_EXEC_ERROR				0
#define MDA_EXEC_OK					1
#define MDA_EXEC_FIRST				2
#define MDA_EXEC_LAST				3

typedef struct MDA_GROUP_STRUCT
{
	ULONG	handle;					// MDA_GROUP handle
	UCHR	filename[256];			// mda filename 
	SLONG	total_database;			// total database frame
	SLONG	total_ani_command;		// total ani command 
	SLONG	database_start_offset;	// database start offset
	SLONG	command_start_offset;	// ani command start offset
	SLONG	total_node;				// 總共多少節點
	SLONG	total_ani_frame;		// 總共多少動作 frame 
	RGB_DATA sea_rgb_data[SEA_CHANGE_COLOR_TYPE];		// 海樂換裝用色盤 設定為 7 個部分
	MDA_NODE *command_node;			// 命令樹進入點
	IMG256_HEAD *img256_head;		// 目前解碼的 img256_head

	// --- Point area
	SLONG	*now_frame;				// Ani command 目前撥放的Frame 
	SLONG	*total_frame;			// 每個Ani command 共有幾個 Frame
	ULONG	*dire_frame_node;		// 直接指向資料庫節點的位置
	INDEX_OFFSET_SIZE *database_index;
	UCHR	*body;					// MDA body

	// Jack, Added [1/22/2003]
	SLONG	with_offset;			// 影像是否載入有偏移座標
	SLONG	offset_x;				// 影像偏移座標 x
	SLONG	offset_y;				// 影像偏移座標 y
	SLONG	references;				// 引用次數
} MDA_GROUP;


//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	MDA_GROUP *mda_group;
//

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
// ----------- Protype define --------------
// 啟動 Initialize
void	init_media_data(void);

// 開啟一個 Media 檔案
SLONG	mda_group_open(UCHR *filename,SLONG *handle);

// 關閉一個 Media 檔案, 並釋放內存
void	mda_group_close(SLONG *handle);

// 開啟一個 Media 檔案, 同時讀取座標(.MDR)
SLONG	mda_group_open_with_position(UCHR *filename, SLONG *handle);

// 執行一個 Media 的命令
SLONG	mda_group_exec(SLONG handle,UCHR *command,SLONG x,SLONG y,BMP *bitmap,SLONG mda_command,SLONG value,SLONG alpha_value,SLONG frame_value);

// 執行一個 Media 的命令, 包含座標校正
SLONG	mda_group_exec_with_position(SLONG handle,UCHR *command,SLONG x,SLONG y,BMP *bitmap,SLONG mda_command,SLONG value,SLONG alpha_value,SLONG frame_value);	

// 取得 Media 檔案 總 Frame 
SLONG	get_media_total_frame(SLONG handle);
//
void	set_media_rgb_data(SLONG handle,SLONG select_part,UCHR r,UCHR g,UCHR b);	// 設置 海樂換裝 色盤資料
void	get_media_rgb_data(SLONG handle,SLONG select_part,UCHR *r,UCHR *g,UCHR *b); // 取得 海樂換裝 色盤資料
void	get_media_rgb_data_with_scroll(SLONG handle,SLONG select_part,UCHR *r,UCHR *g,UCHR *b, UCHR *scroll);
SLONG	get_mda_index(ULONG mda_handle);					// 取得 Media 的真正索引
void	set_media_offset_position(SLONG handle, SLONG offset_x, SLONG offset_y);
SLONG	found_exist_mda_group(USTR *filename);
void	set_media_rgb_effect(SLONG handle,SLONG select_part,UCHR effect);


// ----------------------------------------

SLONG	add_mda_group(void);
ULONG	find_next_mda_handle(void);
void	mda_group_reset(SLONG handle);
void	mda_group_reset_single(SLONG handle,SLONG ani_idx);
SLONG	get_mda_index(ULONG mda_handle);
void	free_mda_group(void);
SLONG	get_file_size(UCHR *filename);
SLONG	get_total_ani_command(UCHR *body,SLONG mda_group_index);
void	make_mda_command_tree(UCHR *data_buffer,SLONG mda_group_index,SLONG total_ani_node);
SLONG	check_media_type(UCHR *data_buffer);
SLONG	check_is_mda_file(UCHR *filename);
SLONG	check_is_wav_type(UCHR *data_buffer);
SLONG	check_is_img256_type(UCHR *data_buffer);
SLONG	find_database(SLONG mda_group_index,UCHR *database_text);
void	take_space(UCHR *data);
void	get_part_str(UCHR *in,UCHR *out,SLONG *idx,UCHR key,SLONG max);
SLONG	check_file_exist(UCHR *filename);
SLONG	read_mda_image(UCHR *mda_filename,SLONG frame_no,IMG256_IMAGE *img256_image);
void	display_rgb_img256_buffer(SLONG x,SLONG y,RGB_DATA *rgb_data,UCHR *data_buffer,BMP *bitmap);
void	display_rgb_img256_buffer_with_highlight(SLONG x,SLONG y,RGB_DATA *rgb_data,UCHR *data_buffer,BMP *bitmap);
void	display_rgb_img256_buffer_with_alpha(SLONG x,SLONG y,RGB_DATA *rgb_data,UCHR *data_buffer,BMP *bitmap, SLONG alpha_value);

SLONG	auto_play_buffer_voice(UCHR *buffer,SLONG size,SLONG loop,SLONG vol);
void	auto_stop_voice(UCHR *filename);
void	auto_stop_all_voice(void);
void	oper_hightlight_color(UHINT *color,UHINT *bk_color);
void	rgb_hightlight_color(UCHR fr,UCHR fg,UCHR fb,UHINT *bk_color);
void	display_hightlight_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap);
void	display_hightlight_zoom_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG zoom_percent);
void	display_zoom_img256_buffer_alpha(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG zoom_percent,SLONG alpha_base);
void	display_zoom_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG zoom_percent);
void	display_img256_buffer_alpha(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap,SLONG alpha_base);
void	display_img256_buffer(SLONG x,SLONG y,UCHR *data_buffer,BMP *bitmap);
ULONG	add_mda_child_node(ULONG father_node,SLONG *node_idx,UCHR *body_index,SLONG mda_group_index);
ULONG	get_maincommand_no(UCHR *command,SLONG father_node,SLONG mda_group_index,ULONG *maincommand_node);
SLONG	get_database_no(SLONG now_frame,ULONG maincommand_node,SLONG mda_group_index,UCHR *database_text);
void	update_media_rgb_data(SLONG handle,SLONG select_part,SLONG r_off,SLONG g_off,SLONG b_off);
void	exec_user_command(UCHR *src_command,UCHR *data_buffer);
UCHR	oper_and_color(UCHR for_color,UCHR bak_color);
UCHR	oper_and_value(UCHR final_color, UCHR init_color);


#endif		//_MEDIA_H_INCLUDE_




