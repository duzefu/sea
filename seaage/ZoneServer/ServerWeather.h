/*
**	ServerWeather.h 
**	server weather functions header.
**
**	Jack, 2002.12.5
*/
#ifndef	_SERVERWEATHER_H_
#define	_SERVERWEATHER_H_


extern	void	server_get_zone_weather_wind(DWORD *size, DWORD *dir);
extern	void	server_get_zone_weather_wind_for_boat(SLONG *dir, SLONG *force);




#endif//_SERVERWEATHER_H_


