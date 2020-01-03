/*
**	NetGE_Treasury.h 
**	treasury functions.
**
**	Hawke, 2003.5.28.
*/

#pragma once

#define		MAX_TREASURY_PER_WORLD		200

typedef struct POS_TREASURY
{
    ULONG	Index;
	char	Memo[256];
	SLONG	MapPartNo;				// 地圖碎片數量
	SLONG	MapRedPointX;			// 大地圖左上角的定位座標
	SLONG	MapRedPointY;			// 大地圖左上角的定位座標
	UHINT	RequestLevel;			// 要求等級
	ULONG	TimeLimit;				// 限制時間
    char	FindOutZoneName[32];	// 發現藏寶點的區域名稱
	ULONG	FindOutActiveNpcNo;		// 啟動寶藏事件的 NPC 編號
	char	ActiveZoneName[32];		// 藏寶地圖的地圖名稱
	SLONG	AppearPointX;			// 出現點
	SLONG	AppearPointY;			// 出現點
}TPOS_TREASURY;

extern	TPOS_TREASURY	Treasury[MAX_TREASURY_PER_WORLD];

// 計算經緯度相關函式
void	ChangeSailMapPositionToLongitudeAndLatitude(SLONG X, SLONG Y, SDOUBLE &Longitude, SDOUBLE &Latitude);
void	ChangeZonePositionToLongitudeAndLatitude(DWORD ZoneType, SLONG X, SLONG Y, SDOUBLE &Longitude, SDOUBLE &Latitude);

// 寶藏相關
extern	void	InitTreasury();
extern	void	FreeTreasury();
extern	void	SetTreasuryMapPartNo(ULONG Index, UHINT PartNo);
extern	UHINT	GetTreasuryMapPartNo(ULONG Index);
extern	void	SetTreasuryMapRedPoint(ULONG Index, SLONG X, SLONG Y);
extern	void	GetTreasuryMapRedPoint(ULONG Index, SLONG &X, SLONG &Y);
extern	void	SetTreasuryRequestLevel(ULONG Index, UHINT Level);
extern	UHINT	GetTreasuryRequestLevel(ULONG Index);
extern	void	SetTreasuryTimeLimit(ULONG Index, ULONG Time);
extern	ULONG	GetTreasuryTimeLimit(ULONG Index);
extern	void	SetTreasuryFindOutZoneName(ULONG Index, char *ZoneName);
extern	char*	GetTreasuryFindOutZoneName(ULONG Index);
extern	void	SetTreasuryFindOutActiveNpcNo(ULONG Index, ULONG NpcNo);
extern	ULONG	GetTreasuryFindOutActiveNpcNo(ULONG Index);
extern	void	SetTreasuryActiveZoneName(ULONG Index, char *ZoneName);
extern	char*	GetTreasuryActiveZoneName(ULONG Index);
extern	void	SetTreasuryActiveZoneAppearPoint(ULONG Index, SLONG X, SLONG Y);
extern	void	GetTreasuryActiveZoneAppearPoint(ULONG Index, SLONG &X, SLONG &Y);



