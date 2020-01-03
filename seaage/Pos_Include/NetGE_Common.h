/*
**	NetGE_Common.h 
**	POS common header files.
**
**	Jack, 2002.12.4
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	SCREEN_WIDTH		800
#define	SCREEN_HEIGHT		600

#define	PI					3.1415927

//----------------------------------------------------------------------------
// 國家定義
//----------------------------------------------------------------------------
/*
#define     CHINA                           'A'	  // 中國
#define     ENGLAND                         'B'   // 英國
#define     SWEDEN                          'C'   // 瑞典
#define     FRANCE							'D'   // 法國
#define     GERMANY							'E'   // 德國
#define     SPAIN							'F'   // 西班牙
#define     PORTUGAL						'G'	  // 葡萄牙
#define     ITALY							'H'   // 義大利
#define     DENMRKE							'I'   // 丹麥
#define     FINLAND							'J'   // 芬蘭
#define     GREECE							'K'   // 希臘
#define     NORWAY							'L'   // 挪威
#define     IRELAND							'M'   // 愛爾蘭
#define     TUNIS							'N'   // 突尼斯
#define     ARAB							'O'   // 阿拉伯
#define     TURKEY							'P'   // 土耳其
#define     AFRICA							'Q'   // 非洲
#define     KOREA							'R'   // 韓國
#define     JAPAN							'S'   // 日本
#define     INDIA							'T'   // 印度
*/
//
#define     COUNTRY_CHINA                   'A'	  // 中國
#define     COUNTRY_ENGLAND                 'B'   // 英國
#define     COUNTRY_SWEDEN                  'C'   // 瑞典
#define     COUNTRY_FRANCE					'D'   // 法國
#define     COUNTRY_GERMANY					'E'   // 德國
#define     COUNTRY_SPAIN					'F'   // 西班牙
#define     COUNTRY_PORTUGAL				'G'	  // 葡萄牙
#define     COUNTRY_ITALY					'H'   // 義大利
#define     COUNTRY_DENMRKE					'I'   // 丹麥
#define     COUNTRY_FINLAND					'J'   // 芬蘭
#define     COUNTRY_GREECE					'K'   // 希臘
#define     COUNTRY_NORWAY					'L'   // 挪威
#define     COUNTRY_IRELAND					'M'   // 愛爾蘭
#define     COUNTRY_TUNIS					'N'   // 突尼斯
#define     COUNTRY_ARAB					'O'   // 阿拉伯
#define     COUNTRY_TURKEY					'P'   // 土耳其
#define     COUNTRY_AFRICA					'Q'   // 非洲
#define     COUNTRY_KOREA					'R'   // 韓國
#define     COUNTRY_JAPAN					'S'   // 日本
#define     COUNTRY_INDIA					'T'   // 印度

//----------------------------------------------------------------------------
// 遊戲角色職業定義
//----------------------------------------------------------------------------
/*
#define     GENERAL                         'A'   // 提督
#define     SWORDER                         'B'   // 劍士
#define     THIEF                           'C'   // 小偷
#define     TRADER                          'D'   // 商人
#define     EXPLORER                        'E'   // 探險家
#define     CLERIC                          'F'   // 牧師
#define     HOROSCOPER                      'G'   // 占星術士
*/
//
#define     CAREER_GENERAL                  'A'   // 提督
#define     CAREER_SWORDER                  'B'   // 劍士
#define     CAREER_THIEF                    'C'   // 小偷
#define     CAREER_TRADER                   'D'   // 商人
#define     CAREER_EXPLORER                 'E'   // 探險家
#define     CAREER_CLERIC                   'F'   // 牧師
#define     CAREER_HOROSCOPER               'G'   // 占星術士
// ---------------------------------------------------------------------------
// 人物性別定義
// ---------------------------------------------------------------------------
#define		MALE                            'A'   // 男
#define		FEMALE                          'B'   // 女
//
#define		SEX_MALE                        'A'   // 男
#define		SEX_FEMALE                      'B'   // 女

//----------------------------------------------------------------------------
// 使用人定義(如物品使用人, 技能使用人等)
//----------------------------------------------------------------------------
#define		USER_SEX_MALE						0x00000001  //男性專用
#define		USER_SEX_FEMALE						0x00000002  //女性專用
//
#define		USER_CAREER_GENERAL					0x00000010  //提督專用
#define		USER_CAREER_SWORDER           		0x00000020  //劍士專用
#define		USER_CAREER_THIEF             		0x00000040  //小偷專用
#define		USER_CAREER_TRADER            		0x00000080  //商人專用
#define		USER_CAREER_EXPLORER          		0x00000100  //探險家專用
#define		USER_CAREER_CLERIC            		0x00000200  //牧師專用
#define		USER_CAREER_HOROSCOPER        		0x00000400  //占星術士(魔法師)
//
//----------------------------------------------------------------------------
// 左右手定義
//----------------------------------------------------------------------------
#define		LEFT_HAND							0			//左手
#define		RIGHT_HAND							1			//右手

//----------------------------------------------------------------------------
// 獲得列表時使用
//----------------------------------------------------------------------------
#define		BEGIN			        			0
#define		NEXT			        			1
#define     END									99999

//----------------------------------------------------------------------------
// 顏色索引值定義
//----------------------------------------------------------------------------
#define		COLOR_RED							1
#define		COLOR_GREEN							2
#define		COLOR_BLUE							3
#define		COLOR_GRAY							4
#define		COLOR_YELLOW						5	//GOLD
#define		COLOR_BLACK							6

//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	union	tagARGB_DATA
{
	ULONG		u4;
	struct  
	{
		UCHR	a;
		UCHR	r;
		UCHR	g;
		UCHR	b;
	};
} ARGB_DATA, *LPARGB_DATA;


// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	ULONG	MakeUserDescriptionByCareerSex(SLONG lCareer, SLONG lSex);
//
extern	SLONG	WindingItemAxisPosition(SLONG n, SLONG *x, SLONG *y);
extern	SLONG	WindingAttackAxisPosition(SLONG n, SLONG *x, SLONG *y);
extern	int		GetHostIp(LPSTR lpszIP, DWORD dwStrLen, CHAR **lpcIPArray, DWORD *dwArrayCount);
extern	void	EncodeSeaNpcSyncPosition(SLONG &sync_x,SLONG &sync_y,SLONG &sync_z,
										 SLONG degree_dir, SLONG x, SLONG y,
										 SLONG speed_x, SLONG speed_y);
extern	void	DecodeSeaNpcSyncPosition(SLONG sync_x, SLONG sync_y, SLONG sync_z, 
										 SLONG &degree_dir, SLONG &x, SLONG &y,
										 SLONG &speed_x, SLONG &speed_y);
extern	SLONG   ApproachScreenAxisDirEx(SLONG dx, SLONG dy, SLONG parts);
extern	SLONG	ApproachScreenAxisDegreeDirEx(SLONG degree, SLONG parts);
extern	SLONG   ComputeScreenAxisDegree(double dx, double dy);
extern	SLONG   ComputeShipSailVelocity(SLONG dist, SLONG v, SLONG vmax, SLONG acc, SLONG keep_steps);
extern	SLONG   ComputeShipWerveVelocity(SLONG v, SLONG vmax, SLONG acc);
extern	double  ComputeShipWerveRadius(SLONG v, SLONG veer);
extern	SLONG   ComputeShipSwerveAngle(SLONG x, SLONG y, SLONG dir_degree, SLONG veer, SLONG dest_x, SLONG dest_y);
extern	SLONG   IsShipCanSailTo(SLONG x, SLONG y, SLONG dir_degree, SLONG v, SLONG veer, SLONG dest_x, SLONG dest_y);
extern	float	FloatToPrecision10Float(float value);
extern	ULONG	GameIndexColorToTrueColor(SLONG index);


