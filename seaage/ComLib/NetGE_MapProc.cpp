/*
**	NetGE_MapProc.cpp
**	map proc functions.
**
**	Jack, 2002.12.11.
*/
#include "NetGE_Mainfunc.h"


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
MAP_PROC        map_proc[MAX_MAP_PROC];
SLONG           map_proc_max;
MAP_PROC_HEAD   map_proc_head;


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
void    reset_map_proc_count(void)
{
    map_proc_max = 0;
}


void    set_map_proc_count(SLONG count)
{
    map_proc_max = count;
}


void    naked_read_map_proc(PACK_FILE *fp, SLONG read_procs)
{
    if( (read_procs < MAX_MAP_PROC) && (fp) )
    {
        pack_fread((USTR *)map_proc,1,sizeof(MAP_PROC)*read_procs,fp);
    }
}


void    clear_all_map_procs(void)
{
    SLONG i;
    for(i=0;i<map_proc_max;i++)
        map_proc[i].id=0;
    map_proc_max=0;
}


SLONG   load_map_proc(USTR *filename)
{
    PACK_FILE    *fp = NULL;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
    {
        //TODO:
        //add your own log error function here.
        //log_error(1, "file %s open error", filename);
        goto _error;
    }
    memset(&map_proc_head, 0, sizeof(MAP_PROC_HEAD));
    pack_fread(&map_proc_head, 1, sizeof(MAP_PROC_HEAD), fp);
    if(MAKEFOURCC('P','R','O','C') != map_proc_head.id)
    {
        //TODO:
        //add your own log error function here.
        //log_error(1, "map proc file format error");
        goto _error;
    }
    if(MAP_PROC_FILE_VERSION != map_proc_head.version)
    {
        //TODO:
        //add your own log error function here.
        //log_error(1, "map proc file version error");
        goto _error;
    }
    clear_all_map_procs();
    if(map_proc_head.total_procs > 0)
    {
        pack_fread(&map_proc[0], 1, sizeof(MAP_PROC) * map_proc_head.total_procs, fp);
        map_proc_max = map_proc_head.total_procs;
    }
    if(fp) { pack_fclose(fp); fp = NULL; }
    return  TTN_OK;

_error:
    if(fp) { pack_fclose(fp); fp = NULL; }
    return  TTN_NOT_OK;
}


BOOL    match_map_proc(SLONG x, SLONG y, SLONG *proc_id, SLONG *proc_type)
{
    SLONG   i;
    BOOL    matched_flag;

    matched_flag = FALSE;
    *proc_id = -1;
    *proc_type = DUMMY_PROC;

    for( i=0; i<map_proc_max; i++)
    {
        if(map_proc[i].id > 0)
        {
            if( TRUE == D3_is_point_in_poly_underside( (POLY *)&map_proc[i].poly, x, y) )
            {
                *proc_id = map_proc[i].id;
                *proc_type = map_proc[i].type;
                matched_flag = TRUE;
                break;
            }
        }
    }
    return matched_flag;
}



