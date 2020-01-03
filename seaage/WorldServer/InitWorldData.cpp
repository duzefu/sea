//-------------------------------------------------------------------------------
// Psalm of Sea Init Data
// By Haweke Hsieh
// 2002-10-05
//-------------------------------------------------------------------------------
#include "WorldServer_Def.h"

//-------------------------------------------------------------------------------
void InitCharacterDefault()
{
	memset(CharacterDefault, 0x0, sizeof(TPOS_CHARACTER_DEFAULT) * MAX_CHARACTER_TYPE);
	// 男提督A
	CharacterDefault[0].Index = 0;
	CharacterDefault[0].FileIndex = 1;
	CharacterDefault[0].Sex = 'A';
	CharacterDefault[0].Career = 'A';
	CharacterDefault[0].Color = 'A';
	CharacterDefault[0].Eyes = '0';
	CharacterDefault[0].Mouth = '0';
	CharacterDefault[0].Str = 6;
	CharacterDefault[0].Ins = 10;
	CharacterDefault[0].Wis = 5;
	CharacterDefault[0].Lucky = 2;
	CharacterDefault[0].Hp = 55;
	CharacterDefault[0].Mp = 20;
	CharacterDefault[0].Mspeed = 12;
	CharacterDefault[0].Attack = 11;
	CharacterDefault[0].Defence = 6;
	CharacterDefault[0].Sight = 500;
	CharacterDefault[0].Skill[0] = MAGIC_NO_JOIN_TEAM;
	CharacterDefault[0].Skill[1] = MAGIC_NO_LEAVE_TEAM;
	CharacterDefault[0].Skill[2] = MAGIC_NO_TRADE;
	CharacterDefault[0].Skill[3] = MAGIC_NO_FOLLOW;
	CharacterDefault[0].Skill[4] = MAGIC_NO_IDENTIFY;
	CharacterDefault[0].Skill[5] = MAGIC_NO_WALK;
	CharacterDefault[0].Skill[6] = MAGIC_NO_SHOOT;
	CharacterDefault[0].Skill[7] = MAGIC_NO_SEQUENTIAL_SHOOT;
	CharacterDefault[0].Skill[8] = MAGIC_NO_DIFFUSE_SHOOT;
	CharacterDefault[0].Skill[9] = MAGIC_NO_SEAWALK;	
	CharacterDefault[0].Skill[10] = MAGIC_NO_LINK_BALL;
	// 女提督A
	CharacterDefault[1].Index = 2;
	CharacterDefault[1].FileIndex = 4;
	CharacterDefault[1].Sex = 'B';
	CharacterDefault[1].Career = 'A';
	CharacterDefault[1].Color = 'A';
	CharacterDefault[1].Eyes = '0';
	CharacterDefault[1].Mouth = '0';
	CharacterDefault[1].Str = 6;
	CharacterDefault[1].Ins = 10;
	CharacterDefault[1].Wis = 5;
	CharacterDefault[1].Lucky = 2;
	CharacterDefault[1].Hp = 55;
	CharacterDefault[1].Mp = 20;
	CharacterDefault[1].Mspeed = 12;
	CharacterDefault[1].Attack = 11;
	CharacterDefault[1].Defence = 6;
	CharacterDefault[1].Sight = 500;
	CharacterDefault[1].Skill[0] = MAGIC_NO_JOIN_TEAM;
	CharacterDefault[1].Skill[1] = MAGIC_NO_LEAVE_TEAM;
	CharacterDefault[1].Skill[2] = MAGIC_NO_TRADE;
	CharacterDefault[1].Skill[3] = MAGIC_NO_FOLLOW;
	CharacterDefault[1].Skill[4] = MAGIC_NO_IDENTIFY;
	CharacterDefault[1].Skill[5] = MAGIC_NO_WALK;
	CharacterDefault[1].Skill[6] = MAGIC_NO_SHOOT;
	CharacterDefault[1].Skill[7] = MAGIC_NO_SEQUENTIAL_SHOOT;
	CharacterDefault[1].Skill[8] = MAGIC_NO_DIFFUSE_SHOOT;
	CharacterDefault[1].Skill[9] = MAGIC_NO_SEAWALK;
	CharacterDefault[1].Skill[10] = MAGIC_NO_LINK_BALL;
	// 男劍客A
	CharacterDefault[2].Index = 2;
	CharacterDefault[2].FileIndex = 7;
	CharacterDefault[2].Sex = 'A';
	CharacterDefault[2].Career = 'B';
	CharacterDefault[2].Color = 'A';
	CharacterDefault[2].Eyes = '0';
	CharacterDefault[2].Mouth = '0';
	CharacterDefault[2].Str = 10;
	CharacterDefault[2].Ins = 2;
	CharacterDefault[2].Wis = 1;
	CharacterDefault[2].Lucky = 1;
	CharacterDefault[2].Hp = 40;
	CharacterDefault[2].Mp = 10;
	CharacterDefault[2].Mspeed = 12;
	CharacterDefault[2].Attack = 11;
	CharacterDefault[2].Defence = 6;
	CharacterDefault[2].Sight = 500;
	CharacterDefault[2].Skill[0] = MAGIC_NO_JOIN_TEAM;
	CharacterDefault[2].Skill[1] = MAGIC_NO_LEAVE_TEAM;
	CharacterDefault[2].Skill[2] = MAGIC_NO_TRADE;
	CharacterDefault[2].Skill[3] = MAGIC_NO_FOLLOW;
	CharacterDefault[2].Skill[4] = MAGIC_NO_IDENTIFY;
	CharacterDefault[2].Skill[5] = MAGIC_NO_WALK;
	CharacterDefault[2].Skill[6] = MAGIC_NO_ESCRIME;
	CharacterDefault[2].Skill[7] = MAGIC_NO_SEQUENTIAL_ESCRIME;
	CharacterDefault[2].Skill[8] = MAGIC_NO_CLASH;
	CharacterDefault[2].Skill[9] = MAGIC_NO_SEAWALK;	
	CharacterDefault[2].Skill[10] = MAGIC_NO_LINK_BALL;
	// 女劍客A
	CharacterDefault[3].Index = 3;
	CharacterDefault[3].FileIndex = 10;
	CharacterDefault[3].Sex = 'B';
	CharacterDefault[3].Career = 'B';
	CharacterDefault[3].Color = 'A';
	CharacterDefault[3].Eyes = '0';
	CharacterDefault[3].Mouth = '0';
	CharacterDefault[3].Str = 10;
	CharacterDefault[3].Ins = 2;
	CharacterDefault[3].Wis = 1;
	CharacterDefault[3].Lucky = 1;
	CharacterDefault[3].Hp = 40;
	CharacterDefault[3].Mp = 10;
	CharacterDefault[3].Mspeed = 12;
	CharacterDefault[3].Attack = 11;
	CharacterDefault[3].Defence = 6;
	CharacterDefault[3].Sight = 500;
	CharacterDefault[3].Skill[0] = MAGIC_NO_JOIN_TEAM;
	CharacterDefault[3].Skill[1] = MAGIC_NO_LEAVE_TEAM;
	CharacterDefault[3].Skill[2] = MAGIC_NO_TRADE;
	CharacterDefault[3].Skill[3] = MAGIC_NO_FOLLOW;
	CharacterDefault[3].Skill[4] = MAGIC_NO_IDENTIFY;
	CharacterDefault[3].Skill[5] = MAGIC_NO_WALK;
	CharacterDefault[3].Skill[6] = MAGIC_NO_ESCRIME;
	CharacterDefault[3].Skill[7] = MAGIC_NO_SEQUENTIAL_ESCRIME;
	CharacterDefault[3].Skill[8] = MAGIC_NO_CLASH;
	CharacterDefault[3].Skill[9] = MAGIC_NO_SEAWALK;
	CharacterDefault[3].Skill[10] = MAGIC_NO_LINK_BALL;
	// 男牧師A
	CharacterDefault[10].Index = 10;
	CharacterDefault[10].FileIndex = 31;
	CharacterDefault[10].Sex = 'A';
	CharacterDefault[10].Career = 'F';
	CharacterDefault[10].Color = 'A';
	CharacterDefault[10].Eyes = '0';
	CharacterDefault[10].Mouth = '0';
	CharacterDefault[10].Str = 4;
	CharacterDefault[10].Ins = 3;
	CharacterDefault[10].Wis = 10;
	CharacterDefault[10].Lucky = 8;
	CharacterDefault[10].Hp = 40;
	CharacterDefault[10].Mp = 45;
	CharacterDefault[10].Mspeed = 12;
	CharacterDefault[10].Attack = 11;
	CharacterDefault[10].Defence = 6;
	CharacterDefault[10].Sight = 500;
	CharacterDefault[10].Skill[0] = MAGIC_NO_JOIN_TEAM;
	CharacterDefault[10].Skill[1] = MAGIC_NO_LEAVE_TEAM;
	CharacterDefault[10].Skill[2] = MAGIC_NO_TRADE;
	CharacterDefault[10].Skill[3] = MAGIC_NO_FOLLOW;
	CharacterDefault[10].Skill[4] = MAGIC_NO_IDENTIFY;
	CharacterDefault[10].Skill[5] = MAGIC_NO_WALK;
	CharacterDefault[10].Skill[6] = MAGIC_NO_DARK_STAR;
	CharacterDefault[10].Skill[7] = MAGIC_NO_DARK_BALL;
	CharacterDefault[10].Skill[8] = MAGIC_NO_BEELINE_MAGIC;
	CharacterDefault[10].Skill[9] = MAGIC_NO_SEAWALK;	
	CharacterDefault[10].Skill[10] = MAGIC_NO_LINK_BALL;
	// 女劍客A
	CharacterDefault[11].Index = 11;
	CharacterDefault[11].FileIndex = 34;
	CharacterDefault[11].Sex = 'B';
	CharacterDefault[11].Career = 'F';
	CharacterDefault[11].Color = 'A';
	CharacterDefault[11].Eyes = '0';
	CharacterDefault[11].Mouth = '0';
	CharacterDefault[11].Str = 4;
	CharacterDefault[11].Ins = 3;
	CharacterDefault[11].Wis = 10;
	CharacterDefault[11].Lucky = 8;
	CharacterDefault[11].Hp = 40;
	CharacterDefault[11].Mp = 15;
	CharacterDefault[11].Mspeed = 12;
	CharacterDefault[11].Attack = 11;
	CharacterDefault[11].Defence = 6;
	CharacterDefault[11].Sight = 500;
	CharacterDefault[11].Skill[0] = MAGIC_NO_JOIN_TEAM;
	CharacterDefault[11].Skill[1] = MAGIC_NO_LEAVE_TEAM;
	CharacterDefault[11].Skill[2] = MAGIC_NO_TRADE;
	CharacterDefault[11].Skill[3] = MAGIC_NO_FOLLOW;
	CharacterDefault[11].Skill[4] = MAGIC_NO_IDENTIFY;
	CharacterDefault[11].Skill[5] = MAGIC_NO_WALK;
	CharacterDefault[11].Skill[6] = MAGIC_NO_DARK_STAR;
	CharacterDefault[11].Skill[7] = MAGIC_NO_DARK_BALL;
	CharacterDefault[11].Skill[8] = MAGIC_NO_BEELINE_MAGIC;
	CharacterDefault[11].Skill[9] = MAGIC_NO_SEAWALK;
	CharacterDefault[11].Skill[10] = MAGIC_NO_LINK_BALL;
}
//-------------------------------------------------------------------------------
void InitCountryDefaultCity()
{
	int	i, j;
	DWORD zonetype;


	memset(CountryCity, 0x0, sizeof(TPOS_COUNTRYCITY) * 16);
	j = 0;
	for(i = 0;i < MAX_ZONE_PER_MACRO;i++)
	{
		//LoadZoneMacroFile(Macro[0].Zone[i].cName);
		zonetype = ReturnZoneType(Macro[0].Zone[i].dType);
		if(zonetype == CITY_BIRTH || zonetype == FIELD_BIRTH || zonetype == SAIL_BIRTH)
		{
			if(j == 16)break;
			CountryCity[j].cCountry = Macro[0].Zone[i].cCountry;
			strcpy(CountryCity[j].cCityName, Macro[0].Zone[i].cName);
			strcpy(CountryCity[j].cCityMap, Macro[0].Zone[i].cMapName);
			CountryCity[j].lDefaultX = Macro[0].Zone[i].lBirthPointX;
			CountryCity[j].lDefaultY = Macro[0].Zone[i].lBirthPointY;
			CountryCity[j].lDefaultZ = Macro[0].Zone[i].lBirthPointZ;
			j++;
		}
	}	
}
// -----------------------------------------------------------------------------
int	ReturnZoneType(DWORD zonetype)
{
	int city,field,sail,newbie,pk,findgold,birth,normal;
	
	city	 = (zonetype & 0x0000000f);
	field    = (zonetype & 0x000000f0) >> 4;
	sail     = (zonetype & 0x00000f00) >> 8;
	newbie   = (zonetype & 0x0000f000) >> 12;
	pk		 = (zonetype & 0x000f0000) >> 16;
	findgold = (zonetype & 0x00f00000) >> 20;	
	birth	 = (zonetype & 0x0f000000) >> 24;	
	normal	 = (zonetype & 0xf0000000) >> 28;

	if(city == 1)
	{
		if(normal == 1)return CITY_NORMAL;
		if(newbie == 1)return CITY_NEWBIE;
		if(pk == 1)return CITY_PK;
		if(findgold == 1)return CITY_FINDGOLD;
		if(birth == 1)return CITY_BIRTH;	
	}
	if(field == 1)
	{
		if(normal == 1)return FIELD_NORMAL;
		if(newbie == 1)return FIELD_NEWBIE;
		if(pk == 1)return FIELD_PK;
		if(findgold == 1)return FIELD_FINDGOLD;
		if(birth == 1)return FIELD_BIRTH;	
	}
	if(sail == 1)
	{
		if(normal == 1)return SAIL_NORMAL;
		if(newbie == 1)return SAIL_NEWBIE;
		if(pk == 1)return SAIL_PK;
		if(findgold == 1)return SAIL_FINDGOLD;
		if(birth == 1)return SAIL_BIRTH;	
	}
	return CITY_NORMAL;
}
//-------------------------------------------------------------------------------
SLONG	LoadZoneMacroFile(char *Name)
{
	FILE    *fp = NULL;
    SLONG   file_size;
    USTR*   file_buf = NULL;
	char	filename[256];

	sprintf(filename,"%s.zmf",Name);
    //載入macro文件到file_buf中 ---------------------
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
    if(uncompresssize != sizeof(TPOS_MACRO_ZONE))
    {
        //log_error(1, "uncompressed file size error");
        goto _error;
    }
    LOCK_MACRO(0);
    memcpy(&ZoneMacro[0], compressbuf, sizeof(TPOS_MACRO_ZONE));
    UNLOCK_MACRO(0);

    return  0;

_error:
    if(fp) { fclose(fp); fp = NULL; }
    if(file_buf) { free(file_buf); file_buf = NULL; }
    return  -1;
	
}
//-------------------------------------------------------------------------------
