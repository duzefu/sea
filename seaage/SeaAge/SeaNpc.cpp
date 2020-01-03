/*
**  seanpc
**  seanpc control model  
**  write by lijun 2002-11-22
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "ClientMain.h"
#include "Npc.h"
#include "MapTrack.h"
#include "SeaNpc.h"
//------------------------------------------------------------------------------------------------------------------------------------------------
//  V A R I A B L E
//------------------------------------------------------------------------------------------------------------------------------------------------
SEA_NPC_TRACK_FILE_INFO g_sea_npc_track_info[MAX_SEA_NPC_TRACK_FILE];
SLONG                   g_sea_npc_track_info_total=0;
//------------------------------------------------------------------------------------------------------------------------------------------------
//  F U N C T I O N
//------------------------------------------------------------------------------------------------------------------------------------------------
void    init_sea_npc_track_file_info(void)
{
    SLONG   i,j;
    for(i=0; i<MAX_SEA_NPC_TRACK_FILE; i++)
    {
        for(j=0; j<NPC_DIRS; j++)
        {
            g_sea_npc_track_info[i].idle[j] = -1;
            g_sea_npc_track_info[i].move[j] = -1;
        }
    }

}
void    debug_log_sea_npc_track_file_info(void)
{
#ifdef  DEBUG
    SLONG   i, j, id;
    USTR    temp[32];

    sprintf( ( char* )print_rec, ";Debug log sea npc track info record" );
    log_error( 1, print_rec );
    for(i = 0; i < MAX_SEA_NPC_TRACK_FILE; i ++ )
    {
        sprintf((char *)print_rec, "%-8d", i);
        for(j = 0; j < NPC_DIRS; j++ )
        {
            id = g_sea_npc_track_info[i].idle[j];
            sprintf((char *)temp, "%-8d", id);
            strcat((char *)print_rec, (const char *)temp);
            //
            id = g_sea_npc_track_info[i].move[j];
            sprintf((char *)temp, "%-8d", id);
            strcat((char *)print_rec, (const char *)temp);
        }
        log_error(1, print_rec);
    }
#endif//DEBUG
}
SLONG   load_sea_npc_track_file_info(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index, val;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, npc_index;
    SLONG   i, len;

    set_data_file(packed_data_file);
    file_size = load_file_to_buffer((USTR*)"data\\seanpctrack.ini", &file_buf);
    if(file_size < 0)
        goto error;
	g_sea_npc_track_info_total = 0;
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            npc_index = get_buffer_number(line, &index);
            if( npc_index >= 0 && npc_index < MAX_SEA_NPC_TRACK_FILE)
            {
                for(i = 0; i<NPC_DIRS*2; i++)
                {
                    val = get_buffer_number(line, &index);

                    if( i < NPC_DIRS )
                        g_sea_npc_track_info[npc_index].idle[i] = val;
                    else
                        g_sea_npc_track_info[npc_index].move[i%NPC_DIRS] = val;
                }
                g_sea_npc_track_info_total ++;
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}
//-----
//  增加船的軌跡
//  [in]track_id    在track_file_info 中的編號
//  [in]x           上圖的座標
//  [in]y           上圖的座標
//  [in]dir         方向
//  [in]state       狀態1 (待機) , 0 (移動)
//-----
void    add_sea_npc_track(SLONG track_id,SLONG x,SLONG y,SLONG dir,SLONG state)
{
    USTR    filename[256];
    //
    if( track_id< 0 || track_id >= MAX_SEA_NPC_TRACK_FILE )
        return;
    //
    if( dir <0 || dir >= NPC_DIRS )
        return;
    //
    if( state )
        sprintf((char *)filename,".\\object\\track\\18t%05d.cak",g_sea_npc_track_info[track_id].idle[dir] );
    else
        sprintf((char *)filename,".\\object\\track\\18t%05d.cak",g_sea_npc_track_info[track_id].move[dir] );
    //
    add_map_track( MTT_ONCE, x, y, 0, 1,filename);
}
//------------------------------------------------------------------------------------------------------------------------
//  .End
//------------------------------------------------------------------------------------------------------------------------
