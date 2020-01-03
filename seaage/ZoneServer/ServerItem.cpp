/*
**	ServerItem.cpp
**	server item functions
**
**	Hawke, 2003/02/20.
*/
#include "ZoneServer_Def.h"
// -----------------------------------------------------------------------------
void	server_refresh_item()
{
	SLONG		p;
	TPOS_ITEM	item;    
	SLONG		life;
	
	LOCK_ITEM(0);
    p = GetZoneItemNext(0);
    while(p != 0)
	{			
		GetZoneItem(p, &item);				
		if(! IsItemNone(&item))
		{			
			life = GetZoneItemLife(p);			
			life--;
			if(life == (ZONE_ITEM_LIFE_TICKS - ZONE_ITEM_OWNER_TICKS))
			{
				SetZoneItemLife(p, life);
				SetZoneItemOwner(p, "");
			}		
			if(life <= 0)
			{
				// Hawke  [2/20/2003]
				// TODO Delete Item
			}
		}				
		p = GetZoneItemNext(p);		
    }	
	UNLOCK_ITEM(0);
    return;
}
// -----------------------------------------------------------------------------
void	ServerDoGatherZoneItem(TPOS_CN	*cn)
{
	SLONG							p, index;
	SLONG							map_no = 0;	
	TPOS_EVENT_NOTIFYZONEITEMLIST	EventNotifyZoneItemList;	

	index = 0;
	memset(&EventNotifyZoneItemList, 0x0, sizeof(TPOS_EVENT_NOTIFYZONEITEMLIST));
	LOCK_ITEM(0);
    p = ZoneItemGS[map_no].Next;	
	while(p != map_no)
    {
		EventNotifyZoneItemList.X[index] = ZoneItemGS[p].X;
		EventNotifyZoneItemList.Y[index] = ZoneItemGS[p].Y;
		EventNotifyZoneItemList.Item[index] = ZoneItemGS[p].Item;

		index++;
		if(index == 500)
		{
			TPOS_PACKET	send_packet;	

			send_packet.Header.dwType = NOTIFY_ZONE_ITEM_LIST;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYZONEITEMLIST);
			memcpy(send_packet.data.cBuf, &EventNotifyZoneItemList, sizeof(TPOS_EVENT_NOTIFYZONEITEMLIST));

			server_send_packet_to_one(cn, &send_packet);
			memset(&EventNotifyZoneItemList, 0x0, sizeof(TPOS_EVENT_NOTIFYZONEITEMLIST));

			index = 0;
		}

		p = ZoneItemGS[p].Next;
	}	
	if(index >= 0 && index < 500)
	{
		TPOS_PACKET	send_packet;	
		
		send_packet.Header.dwType = NOTIFY_ZONE_ITEM_LIST;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYZONEITEMLIST);
		memcpy(send_packet.data.cBuf, &EventNotifyZoneItemList, sizeof(TPOS_EVENT_NOTIFYZONEITEMLIST));
		
		server_send_packet_to_one(cn, &send_packet);		
	}
	UNLOCK_ITEM(0);
}
// -----------------------------------------------------------------------------
SLONG	ServerDoFindBagSpaceNo(SLONG npc_no)
{
	SLONG		ret_value, t;
	TPOS_ITEM	DestItem;

	ret_value = 0;
	
	for(t = 0;t < MAX_CHARACTER_BAG_ITEMS;t++)
	{
		LOCK_CHARACTER(0);
		GetCharacterBagItem(npc_no, t, &DestItem);
		UNLOCK_CHARACTER(0);
		if(IsItemNone(&DestItem))
		{
			ret_value++;			
		}
	}
	
	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	ServerDoFindBagSpace(SLONG	npc_no)
{
	SLONG		ret_value, t;
	TPOS_ITEM	DestItem;

	ret_value = -1;
	
	for(t = 0;t < MAX_CHARACTER_BAG_ITEMS;t++)
	{
		LOCK_CHARACTER(0);
		GetCharacterBagItem(npc_no, t, &DestItem);
		UNLOCK_CHARACTER(0);
		if(IsItemNone(&DestItem))
		{
			ret_value = t;
			break;
		}
	}
	
	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	ServerDoCheckIsTreasureMapItem(TPOS_ITEM *Item)
{
	SLONG	ret_value, item_type;

	ret_value = FALSE;

	item_type = GetItemType(Item);
	if(item_type == ITEM_TYPE_TREASURE_MAP)
	{
		ret_value = TRUE;
	}

	return	ret_value;
}
// -----------------------------------------------------------------------------
void	ServerDoUseDrugItem(SLONG npc_no, TPOS_ITEM *Item, UHINT BagIndex)
{
	UINT		hp, maxhp, mp, maxmp;		
	int			addkind = 0;	// 0:無,1:HP,2:MP,3:HP+MP
	TPOS_EVENT_SETNPCHP	EventSetNpcHp;
	TPOS_EVENT_SETNPCMP	EventSetNpcMp;
	TPOS_PACKET			send_packet;
	char				mainname[32];	
	SLONG				cn_index;
	
	LOCK_CHARACTER(0);
	strcpy(mainname, GetCharacterMainName(npc_no));
	hp = GetCharacterHp(npc_no);
	maxhp = GetCharacterMaxHp(npc_no);
	mp = GetCharacterMp(npc_no);
	maxmp = GetCharacterMaxMp(npc_no);
	UNLOCK_CHARACTER(0);	
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);	

	UHINT	id;
	id =Item->BaseID;
	if(hp > 0)
	{		
		switch(id)
		{
		case 3100:	//傷藥
			hp += maxhp/3;
			addkind = 1;
			break;
		case 3101:	//生命之水
			hp = maxhp;
			addkind = 1;
			break;
		case 3102:	//提神劑
			mp += maxmp/3;
			addkind = 2;
			break;
		case 3103:	//魔力之水
			mp = maxmp;
			addkind = 2;
			break;
		case 3104:	//神秘之水
			hp = maxhp;
			mp = maxmp;
			addkind = 3;
			break;
		}
		if(addkind > 0 && addkind < 4)
		{
			TPOS_EVENT_NOTIFYSETBAGITEM	EventNotifySetBagItem;

			SetItemNone(Item);
			LOCK_CHARACTER(0);
			SetCharacterHp(npc_no, hp);
			SetCharacterMp(npc_no, mp);
			SetCharacterBagItem(npc_no, BagIndex, Item);
			UNLOCK_CHARACTER(0);
				
			// 送出包包物品的信息
			send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);
			EventNotifySetBagItem.BagIndex = (UCHAR)BagIndex;		
			memcpy(&EventNotifySetBagItem.Item, Item, sizeof(TPOS_ITEM));
			memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
			if(cn_index != -1)server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
				
			if(addkind == 1 || addkind ==3)
			{			
				// 送出 HP 
				send_packet.Header.dwType = SET_NPC_HP;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCHP);
				EventSetNpcHp.iHp = hp;
				EventSetNpcHp.Index = npc_no;
				memcpy(send_packet.data.cBuf, &EventSetNpcHp, sizeof(TPOS_EVENT_SETNPCHP));
				server_send_packet_to_all(&send_packet);			
			}
			if(addkind == 2 || addkind ==3)
			{
				// 送出 MP
				send_packet.Header.dwType = SET_NPC_MP;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCMP);
				EventSetNpcMp.iMp = mp;
				EventSetNpcMp.Index = npc_no;
				memcpy(send_packet.data.cBuf, &EventSetNpcMp, sizeof(TPOS_EVENT_SETNPCMP));
				server_send_packet_to_all(&send_packet);							
			}			
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoUseTreasureMapItem(SLONG npc_no, TPOS_ITEM *Item, UHINT BagIndex)
{
	TPOS_EVENT_NOTIFYMAPINFO	EventNotifyMapInfo;
	TPOS_PACKET					send_packet;
	UHINT						current_pieces, all_pieces;
	char						mainname[32];
	SLONG						cn_index;
	SLONG						treasury_index;
	SLONG						x, y;
	SLONG						whole_pieces;
	
	memset(&EventNotifyMapInfo, 0x0, sizeof(TPOS_EVENT_NOTIFYMAPINFO));

	LOCK_CHARACTER(0);
	strcpy(mainname, GetCharacterMainName(npc_no));
	UNLOCK_CHARACTER(0);	

	EventNotifyMapInfo.BagIndex = BagIndex;	
	
	all_pieces = GetTreasureMapItemWholePieces(Item);
	current_pieces = GetTreasureMapItemCurrentPieces(Item);
	treasury_index = (SLONG)GetTreasureMapItemIndex(Item);	

	LOCK_TREASURY(0);
	GetTreasuryMapRedPoint(treasury_index, x, y);			
	strcpy(EventNotifyMapInfo.Memo, Treasury[treasury_index].Memo);
	UNLOCK_TREASURY(0);	
	
	EventNotifyMapInfo.RedPointX = x;
	EventNotifyMapInfo.RedPointY = y;
	EventNotifyMapInfo.MapLeftUpX = x - 136;
	if(EventNotifyMapInfo.MapLeftUpX < 0)EventNotifyMapInfo.MapLeftUpX = 0;
	EventNotifyMapInfo.MapLeftUpY = y - 173;
	if(EventNotifyMapInfo.MapLeftUpY < 0)EventNotifyMapInfo.MapLeftUpY = 0;		
	whole_pieces = Involution(2, all_pieces);
	if((whole_pieces - 1) != current_pieces)
	{	
		EventNotifyMapInfo.RedPointX = 0;
		EventNotifyMapInfo.RedPointX = 0;
	}	

	send_packet.Header.dwType = NOTIFY_MAP_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYMAPINFO);

	memcpy(send_packet.data.cBuf, &EventNotifyMapInfo, sizeof(TPOS_EVENT_NOTIFYMAPINFO));

	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	if(cn_index != -1)server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
}
// -----------------------------------------------------------------------------