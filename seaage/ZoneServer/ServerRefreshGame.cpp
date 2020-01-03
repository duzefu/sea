//-------------------------------------------------------------------------------
// Psalm of Sea Refresh Game Operation
// By Hawke Hsieh
// 2002-10-10
//-------------------------------------------------------------------------------

#include "ZoneServer_Def.h"
//---------------------------------------------------------------------------
// Refresh Game Operation
//---------------------------------------------------------------------------
void RefreshMainGame(void)
{
	DWORD	hb;
    refresh++;	
    CheckConnectPoint();
    server_refresh_character();
	server_refresh_magic();
	server_refresh_item();
    CheckWheather();	
	//任務十分鍾再生
	switch(ZoneType)
	{
	case CITY_NORMAL:
	case CITY_PK:
	case CITY_NEWBIE:
	case CITY_BIRTH:
	case CITY_FINDGOLD:
		hb = get_heartbeat_times();
		if(hb % 12000 == 0)
		{
			ServerDoMakeNPCQuestList();
		}
		break;
	}	
}
//---------------------------------------------------------------------------
// Check Character Go To Zone Connect Point
//---------------------------------------------------------------------------
void CheckConnectPoint(void)
{
    long						proc_id,proc_type;
    static TPOS_PACKET			send_packet; 
	static TPOS_COMPACKET		send_compacket; 
	TPOS_EVENT_GETCHANGEMAP		EventGetChangeMap;
	TPOS_EVENT_QQPLAYERLOGOUT	EventQQPlayerLogout;		
    int						cnIndex; 
    TPOS_DB_CHARACTER		DbCharacter;
    long					doing_kind, x, y, z;
    BOOL					match_result;
    char					mainname[32];
	int						k;
	int						npc_no;
	UHINT					hp;
	DWORD					dest_zonetype;
	DWORD					qq_id;	
    
    proc_id=0;
    proc_type=0;
    cnIndex=0;
    for(npc_no = 0;npc_no < MAX_PLAYER_PER_ZONE;npc_no++)
    {		
        LOCK_CHARACTER(npc_no);
		hp = GetCharacterHp(npc_no);
        doing_kind = GetCharacterDoingKind(npc_no);
		GetCharacterPosition(npc_no, &x, &y, &z);        
        UNLOCK_CHARACTER(npc_no);

        match_result = match_map_proc(x, y, &proc_id, &proc_type);
		// 判斷該玩家是否死亡 , 如果是就不處理換地圖
		if(doing_kind != DOING_KIND_DEAD && hp != 0)
		{			
			if(TRUE == match_result)
			{
				switch(proc_type)
				{
				case AUTO_PROC:
					if(doing_kind != DOING_KIND_CHANGEMAP)
					{
						LOCK_CHARACTER(npc_no);
						SetCharacterDoingKind(npc_no, DOING_KIND_CHANGEMAP);
						strcpy(mainname, GetCharacterMainName(npc_no));
						qq_id = GetCharacterQQID(npc_no);
						UNLOCK_CHARACTER(npc_no);
						
						LOCK_CONNECTION(cnIndex);
						cnIndex = FindConnectionByName((char *)mainname);
						UNLOCK_CONNECTION(cnIndex);           
						if(cnIndex >= 0)
						{   
							// QQ 離線
							send_packet.Header.dwType = QQ_PLAYER_LOGOUT;
							send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQPLAYERLOGOUT);		
							EventQQPlayerLogout.QQID = qq_id;
							memcpy(send_packet.data.cBuf, &EventQQPlayerLogout, sizeof(TPOS_EVENT_QQPLAYERLOGOUT));
							CompressPacket(&send_packet, &send_compacket);
							QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);

							// 傳給玩家改變地圖的資訊
							send_packet.Header.dwType = GET_CHANGE_MAP;
							send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_EVENT_GETCHANGEMAP);
							
							strcpy(EventGetChangeMap.cZoneName,
								ZoneMapDefault[MapLink[0].Point[proc_id].ZoneData].cZoneName);		 
							strcpy(EventGetChangeMap.cMapName,
								ZoneMapDefault[MapLink[0].Point[proc_id].ZoneData].cMapName);							
							
							LOCK_ZONEINFO(0);
							k = FindZoneInfoByName(EventGetChangeMap.cZoneName);					
							strcpy(EventGetChangeMap.cAddr, ZoneInfo[k].cAddr);
							EventGetChangeMap.dwPort = ZoneInfo[k].dwPort;
							EventGetChangeMap.dwType = ZoneInfo[k].dwType;
							dest_zonetype = ZoneInfo[k].dwType;
							UNLOCK_ZONEINFO(0);

							EventGetChangeMap.lX = MapLink[0].Point[proc_id].lDestX;
							EventGetChangeMap.lY = MapLink[0].Point[proc_id].lDestY;
							EventGetChangeMap.lZ = 0;
							switch(dest_zonetype)
							{
							case SAIL_NORMAL:
							case SAIL_NEWBIE:
							case SAIL_PK:
							case SAIL_FINDGOLD:
							case SAIL_BIRTH:
								// 算出座標
								// 1. 找出進出線
								SLONG	x1, x2, y1, y2, z1, z2, sx, sy, sz;
								double	t;
								
								D3_get_poly_underside_touch_line(&map_proc[proc_id].poly, &x1, &y1, &z1, &x2, &y2, &z2);
								// 2. 找出當作座標與進出線垂直交叉點
								D3_droop_point_line(x, y, 0, x1, y1, 0, x2, y2, 0, &sx, &sy, &sz);
								// 3. 找出垂直交叉點在進出線上的 t 值
								t = compute_enter_t(&map_proc[proc_id].poly, sx, sy, sz);
								// 4. 用目的地的預設座標找出與進出線平行的線段
								compute_enter_line_points(&x1, &y1, &z1, &x2, &y2, &z2, 
									MapLink[0].Point[proc_id].lDestX,
									MapLink[0].Point[proc_id].lDestY,
									0);	
								// 5. 用 t 值算出在該線段上的座標 ( 就是結果 )
								compute_enter_t_point(x1, y1, 0, x2, y2, 0, t, &sx, &sy, &sz);							
								
								EventGetChangeMap.lX = sx;
								EventGetChangeMap.lY = sy;
								EventGetChangeMap.lZ = sz;								
								break;
							}
							EventGetChangeMap.cDir = MapLink[0].Point[proc_id].cDir[0];						
							memcpy(send_packet.data.cBuf, &EventGetChangeMap, sizeof(TPOS_EVENT_GETCHANGEMAP));						
							
							CompressPacket(&send_packet, &send_compacket);
							
							LOCK_CONNECTION(cnIndex);				
							QueuePacket(&Pos_Cn[cnIndex] ,&send_compacket, CONNECTED_SERVER_ZONE);
							UNLOCK_CONNECTION(cnIndex);
							
							LOCK_CHARACTER(npc_no);
							ServerDoClearOnMouseItemForPlayerExit(npc_no);
							memset(&DbCharacter, 0x0, sizeof(TPOS_DB_CHARACTER));
							ConvertZoneCharacterDataToDBCharacter(npc_no, &DbCharacter);
							// 如果有在隊伍內, 存下隊長的名字
							if(strcmp(GetCharacterTeamMemberMainName(npc_no, 0), "") != 0)
							{
								strcpy(DbCharacter.LeaderName, GetCharacterTeamMemberMainName(npc_no, 0)); 
							}
							UNLOCK_CHARACTER(npc_no);

							// 儲存物品
							SaveCharacterItemDataByMainNameAndIndex(npc_no);
							SaveCharacterBankData(npc_no);
							// 設定要儲存玩家的資訊
							strcpy(DbCharacter.MainName, mainname);
							strcpy(DbCharacter.ZoneName,
								ZoneMapDefault[MapLink[0].Point[proc_id].ZoneData].cZoneName);
							DbCharacter.X = MapLink[0].Point[proc_id].lDestX;
							DbCharacter.Y = MapLink[0].Point[proc_id].lDestY;
							DbCharacter.Z = MapLink[0].Point[proc_id].lDestZ;
							DbCharacter.Dir = MapLink[0].Point[proc_id].cDir[0];                        						
							
							switch(dest_zonetype)
							{
							case CITY_NORMAL:
							case CITY_NEWBIE:
							case CITY_PK:
							case CITY_FINDGOLD:
							case CITY_BIRTH:
							case FIELD_NORMAL:
							case FIELD_NEWBIE:
							case FIELD_PK:
							case FIELD_FINDGOLD:
							case FIELD_BIRTH:
								LOCK_CHARACTER(npc_no);
								SetCharacterOnTheSea(npc_no, FALSE);
								DbCharacter.BitState = GetCharacterBitState(npc_no);							
								UNLOCK_CHARACTER(npc_no);
								break;
							case SAIL_NORMAL:
							case SAIL_NEWBIE:
							case SAIL_PK:
							case SAIL_FINDGOLD:
							case SAIL_BIRTH:
								LOCK_CHARACTER(npc_no);
								SetCharacterOnTheSea(npc_no, TRUE);
								DbCharacter.BitState = GetCharacterBitState(npc_no);													
								UNLOCK_CHARACTER(npc_no);
							}
							SaveCharacterInfo(cnIndex, &DbCharacter);												
							// 將資料清空
							LOCK_CHARACTER(npc_no);
							ClearOneCharacter(npc_no);
							UNLOCK_CHARACTER(npc_no);
						}
						else
						{
							// Jack, TODO [20:12,10/20/2002]
						}
					}
					break; 
				}
			}
		}
    }
}

//---------------------------------------------------------------------------
// Check Wheather
//---------------------------------------------------------------------------
void CheckWheather(void)
{
 
}
//-------------------------------------------------------------------------------
// 儲存玩家資料
//-------------------------------------------------------------------------------
int SaveCharacterInfo(DWORD cnIndex,TPOS_DB_CHARACTER *dbcharacter)
{
    static TPOS_PACKET		send_packet;
	static TPOS_COMPACKET	send_compacket;
    char			str[256];
    	
    //if(UpdateRecordOfCharacterDB(dbcharacter)==TRUE)
	UpdateRecordOfCharacterDB(dbcharacter);
    {
        send_packet.Header.dwType=START_CHANGE_MAP;
        send_packet.Header.dwSize=sizeof(TPOS_PACKETHEADER);

		CompressPacket(&send_packet, &send_compacket);
        
        LOCK_CONNECTION(cnIndex);
        if(QueuePacket(&Pos_Cn[cnIndex], &send_compacket, CONNECTED_SERVER_ZONE))
        {
            sprintf(str,"SEND %s START_CHANGE_MAP",Pos_Cn[cnIndex].User.cId);
            SaveMsgToLog("SYSTEM", str);
        }
        UNLOCK_CONNECTION(cnIndex);

        return (1);
    } 
    return DLL_ERROR;  
}
//-------------------------------------------------------------------------------
// 檢查名字顏色的時間
//-------------------------------------------------------------------------------
void	CheckNameColorTicks(ULONG npc_no)
{
	ULONG						namecolorticks;
	SLONG						namecolor;	
	SLONG						goodevil;
	TPOS_PACKET					send_packet;
	TPOS_EVENT_SETMAINNAMECOLOR	EventSetMainNameColor;
	TPOS_EVENT_SETGOODEVIL		EventSetGoodEvil;
	SLONG						goodevilchanged;
	SLONG						namecolorchanged;	
	
	goodevilchanged = FALSE;
	namecolorchanged = FALSE;
	
	LOCK_CHARACTER(0);	
	namecolor = GetCharacterMainNameColor(npc_no);
	namecolorticks = GetCharacterNameColorTicks(npc_no);
	goodevil = GetCharacterGoodEvil(npc_no);
	
	switch(namecolor)
	{
	case COLOR_RED:
		if(namecolorticks == 576000)
		//if(namecolorticks == 200) For Test
		{
			goodevil++;
			if(goodevil >= 0)
			{
				namecolor = COLOR_BLUE;
				goodevil = 0;
				SetCharacterGoodEvil(npc_no, 0);
				SetCharacterMainNameColor(npc_no, COLOR_BLUE);
				SetCharacterNameColorTicks(npc_no, 0);
				goodevilchanged = TRUE;
				namecolorchanged = TRUE;
			}
		}else
		{
			namecolorticks++;
			SetCharacterNameColorTicks(npc_no, namecolorticks);
		}
		break;
	case COLOR_GRAY:
		//if(namecolorticks == 100) For Test
		if(namecolorticks == 18000)
		{
			if(goodevil > 0)
			{
				namecolor = COLOR_YELLOW;
				SetCharacterMainNameColor(npc_no, COLOR_YELLOW);
			}
			if(goodevil == 0)
			{
				namecolor = COLOR_BLUE;
				SetCharacterMainNameColor(npc_no, COLOR_BLUE);
			}			
			SetCharacterNameColorTicks(npc_no, 0);			
			namecolorchanged = TRUE;
		}else
		{
			namecolorticks++;
			SetCharacterNameColorTicks(npc_no, namecolorticks);
		}
		break;
	}
	UNLOCK_CHARACTER(0);
	
	if(goodevilchanged == TRUE)
	{
		send_packet.Header.dwType = SET_GOODEVIL;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETGOODEVIL);
		EventSetGoodEvil.GoodEvil = goodevil;		
		memcpy(send_packet.data.cBuf, &EventSetGoodEvil, sizeof(TPOS_EVENT_SETGOODEVIL));
		server_send_packet_to_player(npc_no, &send_packet);
	}
	if(namecolorchanged == TRUE)
	{
		send_packet.Header.dwType = SET_MAINNAME_COLOR;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMAINNAMECOLOR);
		EventSetMainNameColor.MainNameColor = (char)namecolor;
		EventSetMainNameColor.Npc_No = npc_no;
		memcpy(send_packet.data.cBuf, &EventSetMainNameColor, sizeof(TPOS_EVENT_SETMAINNAMECOLOR));
		server_send_packet_to_all(&send_packet);
	}	
}