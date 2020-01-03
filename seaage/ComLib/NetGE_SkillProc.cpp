/*
    2003-05-29
    李駿 .. 關於戰鬥數值結算
*/
#include "NetGE_MainFunc.h"
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void    InitSkillProcUnit(void);
SLONG   LoadSkillProcessUnit(CHAR* szFileName);
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
TPOS_SKILL_PROCESS_UNIT     g_SkillProcessUnit[MAX_SKILL_PROCESS_UNIT];
//
TPOS_SKILL_VAL_PROCESS      g_ZoneSkillProcess[MAX_GAME_SKILL_PROCESS];
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
SLONG   GetZoneSkillProcessFlag(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].Flag;
}
void    SetZoneSkillProcessFlag(SLONG lIndex, SLONG lFlag)
{
    g_ZoneSkillProcess[lIndex].Flag = lFlag;
}

//
SLONG   GetZoneSkillProcessTail(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].Tail;
}
void    SetZoneSkillProcessTail(SLONG lIndex, SLONG lTail)
{
    g_ZoneSkillProcess[lIndex].Tail = lTail;
}
//
SLONG   GetZoneSkillProcessNext(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].Next;
}
void    SetZoneSkillProcessNext(SLONG lIndex, SLONG lNext)
{
    g_ZoneSkillProcess[lIndex].Next = lNext;
}
//
SLONG   GetZoneSkillProcessAttachMagic(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].AttachMagic;
}
void    SetZoneSkillProcessAttachMagic(SLONG lIndex, SLONG lAttachMagic)
{
    g_ZoneSkillProcess[lIndex].AttachMagic = lAttachMagic;
}
//
void    GetZoneSkillProcessPosition(SLONG lIndex, SLONG *x, SLONG *y, SLONG *z)
{
    *x = g_ZoneSkillProcess[lIndex].x;
    *y = g_ZoneSkillProcess[lIndex].y;
    *z = g_ZoneSkillProcess[lIndex].z;        
}
void    SetZoneSkillProcessPosition(SLONG lIndex, SLONG x, SLONG y, SLONG z)
{
    g_ZoneSkillProcess[lIndex].x = x;
    g_ZoneSkillProcess[lIndex].y = y;
    g_ZoneSkillProcess[lIndex].z = z;        
}
//
SLONG   GetZoneSkillProcessZoneType(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].UnitData.ZoneType;
}
void    SetZoneSkillProcessZoneType(SLONG lIndex, SLONG lZoneType)
{
    g_ZoneSkillProcess[lIndex].UnitData.ZoneType = lZoneType;
}
//
SLONG   GetZoneSkillProcessZoneData0(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].UnitData.ZoneData0;
}
void    SetZoneSkillProcessZoneData0(SLONG lIndex, SLONG lZoneData0)
{
    g_ZoneSkillProcess[lIndex].UnitData.ZoneData0 = lZoneData0;
}
//
SLONG   GetZoneSkillProcessZoneData1(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].UnitData.ZoneData1;
}
void    SetZoneSkillProcessZoneData1(SLONG lIndex, SLONG lZoneData1)
{
    g_ZoneSkillProcess[lIndex].UnitData.ZoneData1 = lZoneData1;
}
//
SLONG   GetZoneSkillProcessZoneData2(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].UnitData.ZoneData2;
}
void    SetZoneSkillProcessZoneData2(SLONG lIndex, SLONG lZoneData2)
{
    g_ZoneSkillProcess[lIndex].UnitData.ZoneData2 = lZoneData2;
}
//
SLONG   GetZoneSkillProcessZoneData3(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].UnitData.ZoneData3;
}
void    SetZoneSkillProcessZoneData3(SLONG lIndex, SLONG lZoneData3)
{
    g_ZoneSkillProcess[lIndex].UnitData.ZoneData3 = lZoneData3;
}
//
SLONG   GetZoneSkillProcessSurvialType(SLONG lIndex)
{
    return g_ZoneSkillProcess[lIndex].UnitData.SurvialType;
}
void    SetZoneSkillProcessSurvialType(SLONG lIndex, SLONG lSurvialType)
{
    g_ZoneSkillProcess[lIndex].UnitData.SurvialType = lSurvialType;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
SLONG	InitSkillProcessSystem(void)
{
//    InitSkillProc();
//    LoadSkillProcess("sValProc.ini");
    //
    return 0;
}
void    InitSkillProcUnit(void)
{
    memset(g_SkillProcessUnit, 0, sizeof(TPOS_SKILL_PROCESS_UNIT));
}
SLONG   LoadSkillProcessUnit(CHAR* szFileName)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, len, skill_no;
    //
	TPOS_SKILL_PROCESS_UNIT  *data = NULL;
    //
    file_size = load_file_to_buffer((USTR*)szFileName, &file_buf);
    if(file_size < 0)
        goto error;
    //
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
			//skip_compartment(line, &index, ' \09', 2);
			skill_no = get_buffer_number(line, &index);
			if (skill_no >= 0 && skill_no < MAX_SKILL_PROCESS_UNIT)
			{
				data = &g_SkillProcessUnit[skill_no];
				//
                data->ZoneType  =   get_buffer_number(line, &index);//技能結算的區域類型
                data->ZoneData0 =   get_buffer_number(line, &index);//技能結算的區域..數據
                data->ZoneData1 =   get_buffer_number(line, &index);
                data->ZoneData2 =   get_buffer_number(line, &index);
                data->ZoneData3 =   get_buffer_number(line, &index);
                data->SurvialType = get_buffer_number(line, &index);//生存類型
			}
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) 
        free(file_buf);
    //        
    return 0;
error:
    return -1;

}
//-------------------------------------------------------------------------
//  SKILL_VAL_PROCESS
//-------------------------------------------------------------------------
//----
//  
//----
void    InitZoneSkillProcess(void)
{
    //
    SLONG   i;
    //
    for(i = 0; i < HEAD_GAME_MAGIC_PART; i++)
    {
		SetZoneMagicPartNext(i, i);
		SetZoneMagicPartTail(i, i);
    }
    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART; i++)
    {
		SetZoneMagicPartFlag(i, 0);
		SetZoneMagicPartNext(i, -1);
    }

}
//----
//  
//----
void    ResetZoneSkillProcess(void)
{
    
}
//----
//
//----
void    ClearZoneSkillProcess(void)
{
}
//----
//
//----
void    IsZoneSkillProcessUnused(void)
{
}
//----
//
//----
SLONG	FindUnusedZoneSkillProcess(void)
{
    return 0;
}
//----
//
//----
SLONG	AddZoneSkillProcess(TPOS_SKILL_VAL_PROCESS *MP)
{
    return 0;
}
//----
//
//----
void	DeleteZoneSkillProcess(SLONG lIndex)
{
}
//----
//
//----
void	ReduceVoidZoneSkillProcess(void)
{
}
//----
//
//----
SLONG	CountZoneSkillProcess(void)
{
    return 0;
}
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

 