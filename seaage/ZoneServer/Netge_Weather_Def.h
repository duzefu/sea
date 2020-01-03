#ifndef NETGE_WEATHER_DEF_H
#define NETGE_WEATHER_DEF_H
//------------------------------------------------------------------------------
// 風向控制命令結構
#define WIND_RIGHT		       0		// 向右吹
#define WIND_RIGHT_DOWN	       1		// 向右下吹
#define WIND_DOWN			   2		// 向下吹
#define WIND_LEFT_DOWN		   3		// 向左下吹
#define WIND_LEFT			   4		// 向左吹
#define WIND_LEFT_UP		   5		// 向左上吹
#define WIND_UP			       6		// 向上吹
#define WIND_UP_RIGHT		   7		// 向右上吹

#define WIND_NONE			   0		// 沒有風
#define WIND_SMALL		       1		// 小風
#define WIND_MIDDLE		       2		// 中風
#define WIND_LARGE		       3		// 大風
#define WIND_DUMMY             4        // 不改變

// 天氣控制命令
#define WEATHER_NORMAL		   0x00000000		// 晴天
#define WEATHER_RAIN		   0x00000001		// 下雨
#define WEATHER_SNOW		   0x00000002		// 下雪
#define WEATHER_CLOUD		   0x00000004		// 霧或雲
#define WEATHER_THUNDER	       0x00000008		// 打雷
#define WEATHER_EARTHQUAKE	   0x00000010		// 地震
#define WEATHER_DUMMY          0x80000000       // 不改變

// 撥放控制命令
#define WEATHER_CLEAR		   0		// 清除
#define WEATHER_STARTUP	       1		// 開始
#define WEATHER_STOP		   2		// 結束

// 數量大小控制命令
#define WEATHER_SMALL		   0		// 小 // 在雲的情況	灰雲
#define WEATHER_MIDDLE	       1		// 中 //			黑雲
#define WEATHER_LARGE		   2		// 大 //			白雲

#pragma pack(push)
#pragma pack(1)
//------------------------------------------------------------------------------
// 天氣
//------------------------------------------------------------------------------
typedef struct
{
 DWORD      dType;      // 指定要下哪種天氣的種類 
 DWORD      dActive;    // 開始,清除,結束
 DWORD      dSize;      // 大小 
 DWORD      dWindSize;  // 風向大小 
 DWORD      dWindDir;   // 風向方向
}TPOS_WEATHER;
//------------------------------------------------------------------------------
// 當前區域天氣結構
//------------------------------------------------------------------------------
typedef struct
{
 DWORD      dWeatherType;      // 天氣型態  
 DWORD      dRainActive;       // 是否下雨
 DWORD      dRainSize;         // 雨的大小
 DWORD      dSnowActive;       // 是否下雪
 DWORD      dSnowSize;         // 雪的大小
 DWORD      dCloudActive;      // 是否有雲
 DWORD      dCloudSize;        // 雲的大小
 DWORD      dThunderActive;    // 是否打雷  
 DWORD      dThunderSize;      // 雷的大小
 DWORD      dEarthQuakeActive; // 是否地震
 DWORD      dEarthQuakeSize;   // 地震大小 
 DWORD      dWindSize;         // 風的大小  
 DWORD      dWindDir;          // 風向方向
}TPOS_ZONEWEATHER;
//------------------------------------------------------------------------------
#pragma pack(pop)

#endif