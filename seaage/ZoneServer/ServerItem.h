/*
**	ServerItem.h
**	server item functions.
**
**	Hawke, 2003/02/20.
*/
#ifndef _SERVERITEM_H_
#define _SERVERITEM_H_

void	server_refresh_item();
void	ServerDoGatherZoneItem(TPOS_CN	*cn);
SLONG	ServerDoFindBagSpaceNo(SLONG npc_no);
SLONG	ServerDoFindBagSpace(SLONG	npc_no);
SLONG	ServerDoCheckIsTreasureMapItem(TPOS_ITEM *Item);
void	ServerDoUseDrugItem(SLONG npc_no, TPOS_ITEM *Item, UHINT BagIndex);
void	ServerDoUseTreasureMapItem(SLONG npc_no, TPOS_ITEM *Item, UHINT BagIndex);

#endif
