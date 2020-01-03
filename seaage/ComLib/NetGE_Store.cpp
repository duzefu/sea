/*
**	NetGE_Store.cpp 
**	store functions.
**
**	Jack, 2003.2.19.
*/
#include "NetGE_MainFunc.h"

/************************************************************************************************************/
/* 全局變量                                                                                                 */
/************************************************************************************************************/
TPOS_STORE_BASE		GameStoreBase[MAX_GAME_STORE_BASES];
TPOS_ZONE_STORE		ZoneStore[MAX_ZONE_STORES];


/************************************************************************************************************/
/* 商店基本數值函數                                                                                         */
/************************************************************************************************************/
SLONG	InitStoreSystem(void)
{
	SLONG	result;

	InitGameStoreBase();
	result = LoadGameStoreBase();
	if(0 != result)
	{
		log_error(1, "load game store base error");
		return	-1;
	}
	//DebugLogGameStoreBase();

	InitZoneStore();

	return	0;
}

void	FreeStoreSystem(void)
{
	InitZoneStore();
	FreeGameStoreBase();
}

void	InitGameStoreBase(void)
{
	SLONG	i, j;

	for(i=0; i<MAX_GAME_STORE_BASES; i++)
	{
		for(j=0; j<MAX_STORE_ITEMS; j++)
		{
			GameStoreBase[i].ItemBaseID[j] = 0;
			GameStoreBase[i].InitCount[j] = 0;
			GameStoreBase[i].InitProduce[j] = 0;
			GameStoreBase[i].PriceQuotiety[j] = 100;
		}
	}
}

SLONG	LoadGameStoreBase(void)
{
	SLONG	i, result;

	for(i=0; i<MAX_GAME_STORE_BASES; i++)
	{
		result = LoadOneGameStoreBase(i);
		if(TTN_OK != result)
		{
			log_error(1, "load game store base %d error");
		}
	}
	return	0;
}

SLONG	LoadOneGameStoreBase(SLONG lStoreIndex)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    line[LINE_BUFFER_SIZE];
	USTR	filename[_MAX_PATH];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index, item_index;

	sprintf((char *)filename, "data\\store%03d.ini", lStoreIndex);
    file_size = load_file_to_buffer((USTR*)filename, &file_buf);
    if(file_size < 0)
        return  TTN_ERROR;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;

			//序號
			item_index = get_buffer_number(line, &index);
			if(item_index >= 0 && item_index < MAX_STORE_ITEMS)
			{
				GameStoreBase[lStoreIndex].ItemBaseID[item_index] = (UHINT)get_buffer_number(line, &index);
				GameStoreBase[lStoreIndex].InitCount[item_index] = (UHINT)get_buffer_number(line, &index);
				GameStoreBase[lStoreIndex].InitProduce[item_index] = get_buffer_number(line, &index);
				GameStoreBase[lStoreIndex].PriceQuotiety[item_index] = get_buffer_number(line, &index);
			}
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


void	DebugLogOneGameStoreBase(SLONG lIndex)
{
#ifdef	_DEBUG
	SLONG	i;
	log_error(1, ";log game store base %d", lIndex);
	for(i=0; i<MAX_STORE_ITEMS; i++)
	{
		log_error(1, "%-12d%-12u%-12d%-12d",
			GameStoreBase[lIndex].ItemBaseID[i],
			GameStoreBase[lIndex].InitCount[i],
			GameStoreBase[lIndex].InitProduce[i],
			GameStoreBase[lIndex].PriceQuotiety[i]
			);
	}
#endif//_DEBUG
}

void	DebugLogGameStoreBase(void)
{
#ifdef	_DEBUG
	SLONG	i;
	for(i=0; i<MAX_GAME_STORE_BASES; i++)
	{
		DebugLogOneGameStoreBase(i);
	}
#endif//_DEBUG
}

void	FreeGameStoreBase(void)
{
	// do nothing here.
}

/************************************************************************************************************/
/* 區域商店函數                                                                                             */
/************************************************************************************************************/
void	InitZoneStore(void)
{
	SLONG	i;
	for(i=0; i<MAX_ZONE_STORES; i++)
	{
		ZoneStore[i].Flag = 0;
	}
}

void	RefreshOneZoneStore(SLONG lIndex)
{
	// Jack, TODO [2/24/2003]
}

void	RefreshZoneStore(void)
{
	SLONG	i;

	for(i=0; i<MAX_ZONE_STORES; i++)
	{
		RefreshOneZoneStore(i);
	}
}


void	SetupZoneStore(SLONG lIndex, SLONG lBaseIndex)
{
	TPOS_STORE_ITEM	store_item;
	TPOS_ITEM	item;
	SLONG	i;

	memset(&ZoneStore[lIndex], 0, sizeof(ZoneStore[lIndex]));
	ZoneStore[lIndex].StorePriceQuotiety = 100;
	for(i=0; i<MAX_STORE_ITEMS; i++)
	{
		memset(&item, 0, sizeof(item));
		item.BaseID = GameStoreBase[lBaseIndex].ItemBaseID[i];
		store_item.Flags = STORE_ITEM_TYPE_PRODUCT;
		store_item.Count = GameStoreBase[lBaseIndex].InitCount[i];

		store_item.Price = ComputeItemBuyCost(&item);
		store_item.Produce = 0;
		store_item.AddUpProduce = 0;
		store_item.Item = item;

		ZoneStore[lIndex].StoreItem[i] = store_item;

	}

	ZoneStore[lIndex].Flag = 1;
}


void	SetZoneStoreFlag(SLONG lIndex, SLONG lFlag)
{
	ZoneStore[lIndex].Flag = lFlag;
}

SLONG	GetZoneStoreFlag(SLONG lIndex)
{
	return	ZoneStore[lIndex].Flag;
}

void	SetZoneStoreName(SLONG lIndex, char *szStoreName)
{
	if(szStoreName) strcpy(ZoneStore[lIndex].StoreName, szStoreName);
}

char*	GetZoneStoreName(SLONG lIndex)
{
	return	(char *)ZoneStore[lIndex].StoreName;
}

void	SetZoneStorePriceQuotiety(SLONG lIndex, SLONG lQuotiety)
{
	ZoneStore[lIndex].StorePriceQuotiety = lQuotiety;
}

SLONG	GetZoneStorePriceQuotiety(SLONG lIndex)
{
	return	ZoneStore[lIndex].StorePriceQuotiety;
}

SLONG	SetZoneStoreItem(SLONG lIndex, SLONG lItemIndex, TPOS_STORE_ITEM *lpStoreItem)
{
	SLONG	result;

	result = FALSE;
	if(lpStoreItem)
	{
		ZoneStore[lIndex].StoreItem[lItemIndex] = *lpStoreItem;
		result = TRUE;
	}
	return	result;
}

SLONG	GetZoneStoreItem(SLONG lIndex, SLONG lItemIndex, TPOS_STORE_ITEM *lpStoreItem)
{
	if(lpStoreItem) *lpStoreItem = ZoneStore[lIndex].StoreItem[lItemIndex];
	return	TRUE;
}


SLONG	FindZoneStoreCustomerIndex(SLONG lIndex, char *szMainName)
{
	SLONG	i, index;

	index = -1;
	for(i=0; i<MAX_STORE_CUSTOMERS; i++)
	{
		if(0 == strcmpi((const char*)ZoneStore[lIndex].CustomerName[i], (const char *)szMainName))
		{
			index = i;
			break;
		}
	}
	return	index;
}

void	SetZoneStoreCustomerName(SLONG lIndex, SLONG lCustomerIndex, char *szMainName)
{
	if(szMainName)
	{
		strcpy((char *)ZoneStore[lIndex].CustomerName[lCustomerIndex], (const char *)szMainName);
	}
}

char*	GetZoneStoreCustomerName(SLONG lIndex, SLONG lCustomerIndex)
{
	return	(char *)ZoneStore[lIndex].CustomerName[lCustomerIndex];
}

