/*
**	NetGE_QQ.h 
**	QQ functions header.
**
**	Jack, 2002.12.9
*/
#pragma once

//
// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)
// =============================================
// QQ Get MyData Struct
// =============================================
typedef struct POS_QQ_MYDATA
{
	ULONG			ID;						// QQ 唯一	ID 號
	ULONG			Config;					// 相關設定	
	CHAR			CharacterName[32];		// 角色名稱
	CHAR			GuildName[32];			// 工會名稱
	CHAR			State;					// 狀態
}TPOS_QQ_MYDATA;
// =============================================
// Friend List Struct
// =============================================
typedef struct POS_QQ_FRIEND
{
	DWORD			Index;					// 傳輸的索引
	ULONG			RequestID;				// 要求列表的 QQID
	ULONG			ID;						// 唯一的ID
	CHAR			MainName[32];			// 好友名稱
	UCHAR			Relation;				// 好壞 0-好, 1-壞 
	CHAR			Career;					// 職業
	CHAR			State;					// 狀態
}TPOS_QQ_FRIEND;	

// =============================================
// Friend List Get Drom DataBase Struct
// =============================================
typedef struct POS_QQ_FRIEND_DB
{
	ULONG			ID;						// 唯一的ID	
	UCHAR			Relation;				// 好壞 0-好, 1-壞 	
}TPOS_QQ_FRIEND_DB;	

// =============================================
// QQ Query Detail Struct
// =============================================
typedef struct POS_QQ_QD
{
	DWORD			Index;					// Server端查詢的BookMark
	ULONG			RequestID;				// 要求查詢的玩家QQID
	ULONG			TargetID;				// 要查詢的QQID
	CHAR			MainName[32];			// 要查詢的角色名稱
	CHAR			NickName[32];			// 要查詢的角色暱稱
	CHAR			Country;				// 要查詢的國家名稱
	CHAR			Guild[32];				// 要查詢的工會名稱
	UINT			Level;					// 要查詢的等級
	CHAR			State;					// 要查詢的狀態		
}TPOS_QQ_QD;

// =============================================
// QQ Query Detail Return Data Struct
// =============================================
typedef struct POS_QQ_QD_RETURN
{
	ULONG			RequestID;				// 要求查詢的玩家QQID
	ULONG			ID;						// 唯一的ID
	CHAR			MainName[32];			// 角色名稱
	CHAR			NickName[32];			// 角色暱稱
	CHAR			Country;				// 國家名稱
	CHAR			GuildName[32];			// 工會名稱
	ULONG			Money;					// 金錢
	UINT			Level;					// 等級
	ULONG			PK;						// PK 數量
	CHAR			Spouse[32];				// 配偶名稱
	LONG			Prestige;				// 聲望				
	CHAR			Career;					// 職業
}TPOS_QQ_QD_RETURN;

// =============================================
// QQ Query Add List
// =============================================
typedef struct POS_QQ_ADDLIST
{	
	ULONG			ID;						// 唯一ID
	CHAR			MainName[32];			// 角色名字
	CHAR			GuildName[32];			// 商會名稱	
	CHAR			Career;					// 職業
	UINT			Level;					// 等級	
}TPOS_QQ_ADDLIST;

// =============================================
// QQ Query Add List Return
// =============================================
typedef struct POS_QQ_ADDLIST_RETURN
{
	DWORD			Index;					// Server端查詢的BookMark
	ULONG			RequestID;				// 要求的QQID
	TPOS_QQ_ADDLIST	AddList[11];
}TPOS_QQ_ADDLIST_RETURN;

// =============================================
// QQ Send Msg To One 
// =============================================
typedef struct POS_QQ_SEND_2ONE_MSG
{	
	ULONG			SendID;					// 發送角色ID
	ULONG			RecvID;					// 接收角色ID
	CHAR			Msg[200];	
}TPOS_QQ_SEND_2ONE_MSG;

// =============================================
// QQ Send Msg To One Some
// =============================================
typedef struct POS_QQ_SEND_2SOME_MSG
{
	ULONG			SendID;					// 發送角色ID
	ULONG			RecvID[50];				// 接收角色 ID
	CHAR			Msg[200];	
}TPOS_QQ_SEND_2SOME_MSG;

// =============================================
// QQ Struct
// =============================================
typedef struct POS_QQ
{
	ULONG			ID;						// QQ 唯一	ID 號
	ULONG			Config;					// 相關設定
	CHAR			WorldServerName[32];	// 世界伺服器名稱	
	CHAR			AccountName[32];		// 帳號名稱	
	CHAR			CharacterName[32];		// 角色名稱	
	CHAR			GuildName[32];			// 工會名稱
	CHAR			LeaderName[32];			// 隊長角色名稱
	CHAR			NickName[32];			// 暱稱
	CHAR			Country;				// 國家 
	CHAR			State;					// 狀態
	CHAR			Career;					// 職業
	DWORD			Level;					// 等級
	TPOS_QQ_FRIEND_DB	Friend[256];		// 好友名單 
	TPOS_QQ_FRIEND_DB	GuildFriend[128];	// 工會好友名單
}TPOS_QQ;	

// =============================================
// QQ Server Save Online Player List Struct
// =============================================
typedef struct POS_QQ_ONLINE_PLAYER_LIST
{
	ULONG			Index;
	ULONG			ID;
	CHAR			MainName[32];
	CHAR			ZoneName[32];
	CHAR			GuildName[32];
	UCHAR			Relation;
	CHAR			State;
	DWORD			Level;
	TPOS_QQ_FRIEND_DB	Friend[256];
	TPOS_QQ_FRIEND_DB	GuildFriend[128];		// 工會好友名單
}TPOS_QQ_ONLINE_PLAYER_LIST;

// =============================================
// QQ Server Query Temp Struct
// =============================================
typedef struct POS_QQ_QD_TEMP
{
	LONG			Index;					// 查詢到第幾筆
	TPOS_QQ_QD		Qd;
	LONG			AddListNullIndex;
	TPOS_QQ_ADDLIST AddList[11];
}TPOS_QQ_QD_TEMP;

// =============================================
// QQ Server Struct
// =============================================
typedef struct POS_QQ_SERVER_INFO
{
	DWORD			Index;					// 索引
	CHAR			QQServerName[32];		// QQServer 名稱
	CHAR			QQServerIP[16];			// QQServer IP
	DWORD			QQServerPort;			// QQServer Port
	DWORD			QQServerState;			// QQServer State 
}TPOS_QQ_SERVER_INFO;

// =============================================
// QQ Status Struct
// =============================================
typedef struct POS_QQ_STATE
{
	ULONG			ID;
	CHAR			Status;
}TPOS_QQ_STATE;

// =============================================
// QQ PlayerCount Struct
// =============================================
typedef struct POS_QQ_PLAYER_COUNT
{
	ULONG			RequestID;
	ULONG			PlayerCount;
}TPOS_QQ_PLAYER_COUNT;

#pragma	pack(pop)


//
// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

//
// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//

