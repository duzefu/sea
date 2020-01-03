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
	char	Name[32];				// �_�æW��
	UHINT	MapPartNo;				// �a�ϸH���ƶq
	SLONG	MapLeftUpX;				// �j�a�ϥ��W�����w��y��	
	SLONG	MapLeftUpY;				// �j�a�ϥ��W�����w��y��	
	char	FindOutZoneName[32];	// �o�{���_�I���ϰ�W��	
	char	Memo[256];				// ����
	SLONG	RedPointX;				// ���_�ϤW�����I���y��
	SLONG	RedPointY;				// ���_�ϤW�����I���y��
	SLONG	ActiveNpcNo;			// �Ұ����_�ϰ쪺 NPC �θ��P�s��	
	char	GoldMapname[32];		// ���_�a�Ϫ��a�ϦW��
	SLONG	AppearPointX;			// �X�{�I
	SLONG	AppearPointY;			// �X�{�I
	ULONG	TimeLimit;				// ����ɶ�
}TPOS_FIND_GOLD;

//void	ServerDoMakeFindGoldQuest();
SLONG	ServerDoSeparateMap(SLONG npc_no, TPOS_ITEM *Item);
SLONG	ServerDoComposeMap(TPOS_ITEM *SrcItem, TPOS_ITEM *TagItem, TPOS_ITEM *FinalItem);
SLONG	LoadTreasuryFile();

#endif
