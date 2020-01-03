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
	SLONG	MapPartNo;				// �a�ϸH���ƶq
	SLONG	MapRedPointX;			// �j�a�ϥ��W�����w��y��
	SLONG	MapRedPointY;			// �j�a�ϥ��W�����w��y��
	UHINT	RequestLevel;			// �n�D����
	ULONG	TimeLimit;				// ����ɶ�
    char	FindOutZoneName[32];	// �o�{���_�I���ϰ�W��
	ULONG	FindOutActiveNpcNo;		// �Ұ��_�èƥ� NPC �s��
	char	ActiveZoneName[32];		// ���_�a�Ϫ��a�ϦW��
	SLONG	AppearPointX;			// �X�{�I
	SLONG	AppearPointY;			// �X�{�I
}TPOS_TREASURY;

extern	TPOS_TREASURY	Treasury[MAX_TREASURY_PER_WORLD];

// �p��g�n�׬����禡
void	ChangeSailMapPositionToLongitudeAndLatitude(SLONG X, SLONG Y, SDOUBLE &Longitude, SDOUBLE &Latitude);
void	ChangeZonePositionToLongitudeAndLatitude(DWORD ZoneType, SLONG X, SLONG Y, SDOUBLE &Longitude, SDOUBLE &Latitude);

// �_�ì���
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



