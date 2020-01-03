/*
**	Weather.h
**  weather system.
**  
**  stephen, 2002.10.8.
*/
#ifndef _WEATHER_H_
#define _WEATHER_H_

// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
// --------- Weather System Define area
#define MAX_RAIN_POINT		4000					// 降雨數量
#define MAX_CLOUD			10						// 最多的雲量

#define WIND_RIGHT			0
#define WIND_RIGHT_DOWN		1
#define WIND_DOWN			2
#define WIND_LEFT_DOWN		3
#define WIND_LEFT			4
#define WIND_LEFT_UP		5
#define WIND_UP				6
#define WIND_UP_RIGHT		7

#define WIND_NONE			0   //無風
#define WIND_SMALL			1	//小風
#define WIND_MIDDLE			2	//中風
#define WIND_LARGE			3   //大風
#define WIND_DUMMY          4	//不做控制

// ===== 天氣控制命令
#define WEATHER_NORMAL		0x00000000          // 晴天
#define WEATHER_RAIN		0x00000001          // 下雨
#define WEATHER_SNOW		0x00000002			// 下雪
#define WEATHER_CLOUD		0x00000004  		// 霧或雲
#define WEATHER_THUNDER		0x00000008  		// 打雷
#define WEATHER_EARTHQUAKE	0x00000010			// 地震
#define WEATHER_DUMMY       0x80000000          // 不作控制


#define WEATHER_RAIN_STOP		0xFFFE			// 停止下雨
#define WEATHER_SNOW_STOP		0xFFFD			// 停止下雪
#define WEATHER_CLOUD_STOP		0xFFFB			// 停止霧或雲
#define WEATHER_THUNDER_STOP	0xFFF7			// 停止打雷
#define WEATHER_EARTHQUAKE_STOP	0xFFEF			// 停止地震

// ===== 撥放控制命令
#define WEATHER_CLEAR		0					// 清除
#define WEATHER_STARTUP		1					// 開始
#define WEATHER_STOP		2					// 結束

// ===== 數量大小控制命令
#define WEATHER_SMALL		0					// 小 // 在雲的情況	灰雲
#define WEATHER_MIDDLE		1					// 中 //			黑雲
#define WEATHER_LARGE		2					// 大 //			白雲


// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct WEATHER_PARAMETER_STRUCT
{
	SLONG wind_dir;								// 風向
	SLONG wind_range;							// 風向大小
	SLONG status;								// 天氣控制命令  

	SLONG rain_command;							// 下雨撥放命令
	SLONG rain_range;							// 下雨大小命令

	SLONG snow_command;							// 下雪撥放命令
	SLONG snow_range;							// 下雪大小命令

	SLONG thunder_command;						// 打雷撥放命令
	SLONG thunder_range;						// 打雷大小命令

	SLONG cloud_command;						// 雲撥放命令
	SLONG cloud_range;							// 雲的大小命令

	SLONG earthquake_command;					// 地震撥放命令
	SLONG earthquake_range;						// 地震大小命令

	SLONG x_offset;								// 風速的偏移量
	SLONG y_offset;
	SLONG rain_process_count;					// 下雨處理count
	SLONG snow_process_count;					// 下雪處理count
	SLONG thunder_process_count;				// 打雷處理count
	SLONG cloud_process_count;					// 雲處理count
	SLONG earthquake_process_count;				// 地震處理count

} WEATHER_PARAMETER ;


typedef struct WEATHER_RAIN_DATA_STRUCT
{
	SLONG active;								// 雨滴啟動flag  
												//			0 -> disable
												//			1 -> in sky 
												//			2 -> in ground
	SLONG x;									// 落地座標
	SLONG y;
	SLONG height;								// 雨滴高度

} WEATHER_RAIN_DATA ;


typedef struct WEATHER_SNOW_DATA_STRUCT
{
	SLONG active;								// 雪啟動flag  
												//			0 -> disable
												//			1 -> in sky 
												//			2 -> in ground
	SLONG x;									// 落地座標
	SLONG y;
	SLONG height;								// 雪高度
	SLONG size;									// 雪的大小

} WEATHER_SNOW_DATA ;


typedef struct WEATHER_CLOUD_DATA_STRUCT
{
	SLONG active;								// 雲啟動
												//			0 -> disable
												//			1 -> startup 
												//			2 -> show
												//          3 -> close
	SLONG x;									// 座標
	SLONG y;
	SLONG timer;
	SLONG type;									// 種類

} WEATHER_CLOUD_DATA;


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
// ----------- subtinue define area ------------------------------------------------
int     init_weather(void);
void    free_weather(void);
void    active_weather(int flag);
void    refresh_weather(void);
void    control_wind(SLONG wind_dir,SLONG wind_range);
void    control_weather(SLONG weather_type,SLONG weather_command,SLONG weather_range);
void    exec_weather(BMP *bitmap);
void    weather_adjust_map_move(void);
//
void    get_current_weather_wind(SLONG *wind_dir, SLONG *wind_range);
SLONG   get_current_weather_type(void);
SLONG   weather_wind_dir_to_ui_wind_dir(SLONG weather_wind_dir);
void	get_zone_weather_wind_for_boat(SLONG *dir, SLONG *force);
void	init_zone_weather(void);



#endif//_WEATHER_H_
