/*
**	ServerWeather.cpp 
**	server weather functions.
**
**	Jack, 2002.12.5
*/
#include "ZoneServer_Def.h"
#include "ServerWeather.h"



/************************************************************************************************************/
/* ZONE WEATHER MAIN FUNCTIONS                                                                              */
/************************************************************************************************************/
__inline	void	server_get_zone_weather_wind(DWORD *size, DWORD *dir)
{
	if(size) *size = ZoneWeather->dWindSize;
	if(dir) *dir = ZoneWeather->dWindDir;
}



void	server_get_zone_weather_wind_for_boat(SLONG *dir, SLONG *force)
{
	DWORD	wind_dir, wind_size;

	server_get_zone_weather_wind(&wind_size, &wind_dir);
	*dir = wind_dir;
	switch(wind_size)
	{
	case WIND_SMALL:	//小風
		*force = 5;
		break;
	case WIND_MIDDLE:	//中風
		*force = 10;
		break;
	case WIND_LARGE:	//大風
		*force = 20;
		break;
	case WIND_NONE:		//無風
	default:
		*force = 0;
		break;
	}
}
