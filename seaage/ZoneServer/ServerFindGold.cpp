/*
**	ServerFindGold.cpp 
**	server find gold functions.
**
**	Hawke, 2003.05.16
*/
#include "ZoneServer_Def.h"
// -----------------------------------------------------------------------------
SLONG	ServerDoSeparateMap(SLONG npc_no, TPOS_ITEM *Item)
{
	SLONG		treasury_index;
	SLONG		ret_value;
	UHINT		map_part, current_pieces;
	SLONG		bag_space_no;
	SLONG		bag_index;
	TPOS_PACKET	send_packet;	
	int			i;

	ret_value = FALSE;
	treasury_index = (SLONG)GetTreasureMapItemIndex(Item);
	current_pieces = GetTreasureMapItemCurrentPieces(Item);
	LOCK_TREASURY(0);
	map_part = GetTreasuryMapPartNo(treasury_index);
	UNLOCK_TREASURY(0);
	bag_space_no = ServerDoFindBagSpaceNo(npc_no);
	if(bag_space_no >= map_part)
	{
		TPOS_ITEM	SeparatedMap;		
		SLONG		t;		

		for(i = 0; i < map_part; i++)
		{
			t = Involution(2, i);
			if((t & current_pieces) == t)
			{	
				TPOS_EVENT_NOTIFYSETBAGITEM	EventNotifySetBagItem;

				memcpy(&SeparatedMap, Item, sizeof(TPOS_ITEM));
				SeparatedMap.IR.TreasureMap.CurrentPieces = (UHINT)t;				
				bag_index = ServerDoFindBagSpace(npc_no);
				LOCK_CHARACTER(0);
				SetCharacterBagItem(npc_no, bag_index, &SeparatedMap);
				UNLOCK_CHARACTER(0);
				send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);
				EventNotifySetBagItem.Item = SeparatedMap;
				EventNotifySetBagItem.BagIndex = (UCHAR)bag_index;
				memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
				server_send_packet_to_player(npc_no, &send_packet);
			}
		}		
		ret_value = TRUE;
	}else
	{
		send_packet.Header.dwType = NOTIFY_BAG_SPACE_NOT_ENOUGH;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
		server_send_packet_to_player(npc_no, &send_packet);
	}

	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	ServerDoComposeMap(TPOS_ITEM *SrcItem, TPOS_ITEM *TagItem, TPOS_ITEM *FinalItem)
{
	SLONG	ret_value;
	UHINT	src_index, tag_index;
	UHINT	src_pieces, tag_pieces;	

	ret_value = FALSE;	

	src_index = (UHINT)GetTreasureMapItemIndex(SrcItem);
	tag_index = (UHINT)GetTreasureMapItemIndex(TagItem);
	if(src_index == tag_index)
	{
		src_pieces = GetTreasureMapItemCurrentPieces(SrcItem);
		tag_pieces = GetTreasureMapItemCurrentPieces(TagItem);
		
		switch(src_pieces)
		{
		case 1:
		case 2:
		case 4:
		case 8:
		case 32:
		case 64:
		case 128:
		case 256:
		case 512:
		case 1024:
		case 2048:
		case 4096:
		case 8192:
		case 16384:
		case 32768:
			if((src_pieces & tag_pieces) != src_pieces)
			{
				if(tag_pieces != src_pieces)
				{
					memcpy(FinalItem, SrcItem, sizeof(TPOS_ITEM));
					SetTreasureMapItemCurrentPieces(FinalItem, src_pieces + tag_pieces);
					ret_value = TRUE;
				}				
			}			
			break;
		}				
	}

	return ret_value;	
}
// -----------------------------------------------------------------------------
SLONG	LoadTreasuryFile()
{
	FILE    *fp = NULL;
    SLONG   file_size;
    USTR*   file_buf = NULL;
	char	filename[256];	

	sprintf(filename,"Macro\\treasury.tmf");
    //載入treasury文件到file_buf中 ---------------------
    if(NULL == (fp = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    if(NULL == (file_buf = (USTR*)malloc(file_size)))
    {        
        goto _error;
    }
    fseek(fp, 0L, SEEK_SET);
    fread(file_buf, 1, file_size, fp);
    fclose(fp);

    //解壓讀取的數據到compressbuf中
    compresssize = file_size;
    uncompresssize = lzo_decompress(file_buf, compresssize, compressbuf);
    free(file_buf); file_buf = NULL;	
    //將解壓後的數據複製到Macro中
    if(uncompresssize != sizeof(TPOS_TREASURY) * MAX_TREASURY_PER_WORLD)
    {
        //log_error(1, "uncompressed file size error");
        goto _error;
    }	
    LOCK_TREASURY(0);
    memcpy(Treasury, compressbuf, sizeof(TPOS_TREASURY) * MAX_TREASURY_PER_WORLD);	
    UNLOCK_TREASURY(0);

    return  0;

_error:
    if(fp) { fclose(fp); fp = NULL; }
    if(file_buf) { free(file_buf); file_buf = NULL; }
    return  -1;
	
}
// -----------------------------------------------------------------------------