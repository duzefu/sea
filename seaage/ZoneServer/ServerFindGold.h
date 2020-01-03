/*
**	ServerFindGold.h 
**	server find gold functions header.
**
**	Hawke, 2003.05.16
*/
#ifndef	_SERVERFINDGOLD_H_
#define	_SERVERFINDGOLD_H_

typedef	struct POS_FIND_GOLD
{
	char	Name[32];				// 寶藏名稱
	UHINT	MapPartNo;				// 地圖碎片數量
	SLONG	MapLeftUpX;				// 大地圖左上角的定位座標	
	SLONG	MapLeftUpY;				// 大地圖左上角的定位座標	
	char	FindOutZoneName[32];	// 發現藏寶點的區域名稱	
	char	Memo[256];				// 說明
	SLONG	RedPointX;				// 藏寶圖上面紅點的座標
	SLONG	RedPointY;				// 藏寶圖上面紅點的座標
	SLONG	ActiveNpcNo;			// 啟動藏寶區域的 NPC 或路牌編號	
	char	GoldMapname[32];		// 藏寶地圖的地圖名稱
	SLONG	AppearPointX;			// 出現點
	SLONG	AppearPointY;			// 出現點
	ULONG	TimeLimit;				// 限制時間
}TPOS_FIND_GOLD;

//void	ServerDoMakeFindGoldQuest();
SLONG	ServerDoSeparateMap(SLONG npc_no, TPOS_ITEM *Item);
SLONG	ServerDoComposeMap(TPOS_ITEM *SrcItem, TPOS_ITEM *TagItem, TPOS_ITEM *FinalItem);
SLONG	LoadTreasuryFile();

#endif
