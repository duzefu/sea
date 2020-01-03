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
	ULONG			ID;						// QQ �ߤ@	ID ��
	ULONG			Config;					// �����]�w	
	CHAR			CharacterName[32];		// ����W��
	CHAR			GuildName[32];			// �u�|�W��
	CHAR			State;					// ���A
}TPOS_QQ_MYDATA;
// =============================================
// Friend List Struct
// =============================================
typedef struct POS_QQ_FRIEND
{
	DWORD			Index;					// �ǿ骺����
	ULONG			RequestID;				// �n�D�C�� QQID
	ULONG			ID;						// �ߤ@��ID
	CHAR			MainName[32];			// �n�ͦW��
	UCHAR			Relation;				// �n�a 0-�n, 1-�a 
	CHAR			Career;					// ¾�~
	CHAR			State;					// ���A
}TPOS_QQ_FRIEND;	

// =============================================
// Friend List Get Drom DataBase Struct
// =============================================
typedef struct POS_QQ_FRIEND_DB
{
	ULONG			ID;						// �ߤ@��ID	
	UCHAR			Relation;				// �n�a 0-�n, 1-�a 	
}TPOS_QQ_FRIEND_DB;	

// =============================================
// QQ Query Detail Struct
// =============================================
typedef struct POS_QQ_QD
{
	DWORD			Index;					// Server�ݬd�ߪ�BookMark
	ULONG			RequestID;				// �n�D�d�ߪ����aQQID
	ULONG			TargetID;				// �n�d�ߪ�QQID
	CHAR			MainName[32];			// �n�d�ߪ�����W��
	CHAR			NickName[32];			// �n�d�ߪ�����ʺ�
	CHAR			Country;				// �n�d�ߪ���a�W��
	CHAR			Guild[32];				// �n�d�ߪ��u�|�W��
	UINT			Level;					// �n�d�ߪ�����
	CHAR			State;					// �n�d�ߪ����A		
}TPOS_QQ_QD;

// =============================================
// QQ Query Detail Return Data Struct
// =============================================
typedef struct POS_QQ_QD_RETURN
{
	ULONG			RequestID;				// �n�D�d�ߪ����aQQID
	ULONG			ID;						// �ߤ@��ID
	CHAR			MainName[32];			// ����W��
	CHAR			NickName[32];			// ����ʺ�
	CHAR			Country;				// ��a�W��
	CHAR			GuildName[32];			// �u�|�W��
	ULONG			Money;					// ����
	UINT			Level;					// ����
	ULONG			PK;						// PK �ƶq
	CHAR			Spouse[32];				// �t���W��
	LONG			Prestige;				// �n��				
	CHAR			Career;					// ¾�~
}TPOS_QQ_QD_RETURN;

// =============================================
// QQ Query Add List
// =============================================
typedef struct POS_QQ_ADDLIST
{	
	ULONG			ID;						// �ߤ@ID
	CHAR			MainName[32];			// ����W�r
	CHAR			GuildName[32];			// �ӷ|�W��	
	CHAR			Career;					// ¾�~
	UINT			Level;					// ����	
}TPOS_QQ_ADDLIST;

// =============================================
// QQ Query Add List Return
// =============================================
typedef struct POS_QQ_ADDLIST_RETURN
{
	DWORD			Index;					// Server�ݬd�ߪ�BookMark
	ULONG			RequestID;				// �n�D��QQID
	TPOS_QQ_ADDLIST	AddList[11];
}TPOS_QQ_ADDLIST_RETURN;

// =============================================
// QQ Send Msg To One 
// =============================================
typedef struct POS_QQ_SEND_2ONE_MSG
{	
	ULONG			SendID;					// �o�e����ID
	ULONG			RecvID;					// ��������ID
	CHAR			Msg[200];	
}TPOS_QQ_SEND_2ONE_MSG;

// =============================================
// QQ Send Msg To One Some
// =============================================
typedef struct POS_QQ_SEND_2SOME_MSG
{
	ULONG			SendID;					// �o�e����ID
	ULONG			RecvID[50];				// �������� ID
	CHAR			Msg[200];	
}TPOS_QQ_SEND_2SOME_MSG;

// =============================================
// QQ Struct
// =============================================
typedef struct POS_QQ
{
	ULONG			ID;						// QQ �ߤ@	ID ��
	ULONG			Config;					// �����]�w
	CHAR			WorldServerName[32];	// �@�ɦ��A���W��	
	CHAR			AccountName[32];		// �b���W��	
	CHAR			CharacterName[32];		// ����W��	
	CHAR			GuildName[32];			// �u�|�W��
	CHAR			LeaderName[32];			// ��������W��
	CHAR			NickName[32];			// �ʺ�
	CHAR			Country;				// ��a 
	CHAR			State;					// ���A
	CHAR			Career;					// ¾�~
	DWORD			Level;					// ����
	TPOS_QQ_FRIEND_DB	Friend[256];		// �n�ͦW�� 
	TPOS_QQ_FRIEND_DB	GuildFriend[128];	// �u�|�n�ͦW��
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
	TPOS_QQ_FRIEND_DB	GuildFriend[128];		// �u�|�n�ͦW��
}TPOS_QQ_ONLINE_PLAYER_LIST;

// =============================================
// QQ Server Query Temp Struct
// =============================================
typedef struct POS_QQ_QD_TEMP
{
	LONG			Index;					// �d�ߨ�ĴX��
	TPOS_QQ_QD		Qd;
	LONG			AddListNullIndex;
	TPOS_QQ_ADDLIST AddList[11];
}TPOS_QQ_QD_TEMP;

// =============================================
// QQ Server Struct
// =============================================
typedef struct POS_QQ_SERVER_INFO
{
	DWORD			Index;					// ����
	CHAR			QQServerName[32];		// QQServer �W��
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

