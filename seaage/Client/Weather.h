/*
**	Weather.h
**  weather system.
**  
**  stephen, 2002.10.8.
*/
#ifndef _WEATHER_H_
#define _WEATHER_H_

// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
// --------- Weather System Define area
#define MAX_RAIN_POINT		4000					// ���B�ƶq
#define MAX_CLOUD			10						// �̦h�����q

#define WIND_RIGHT			0
#define WIND_RIGHT_DOWN		1
#define WIND_DOWN			2
#define WIND_LEFT_DOWN		3
#define WIND_LEFT			4
#define WIND_LEFT_UP		5
#define WIND_UP				6
#define WIND_UP_RIGHT		7

#define WIND_NONE			0   //�L��
#define WIND_SMALL			1	//�p��
#define WIND_MIDDLE			2	//����
#define WIND_LARGE			3   //�j��
#define WIND_DUMMY          4	//��������

// ===== �Ѯ𱱨�R�O
#define WEATHER_NORMAL		0x00000000          // ����
#define WEATHER_RAIN		0x00000001          // �U�B
#define WEATHER_SNOW		0x00000002			// �U��
#define WEATHER_CLOUD		0x00000004  		// ���ζ�
#define WEATHER_THUNDER		0x00000008  		// ���p
#define WEATHER_EARTHQUAKE	0x00000010			// �a�_
#define WEATHER_DUMMY       0x80000000          // ���@����


#define WEATHER_RAIN_STOP		0xFFFE			// ����U�B
#define WEATHER_SNOW_STOP		0xFFFD			// ����U��
#define WEATHER_CLOUD_STOP		0xFFFB			// �������ζ�
#define WEATHER_THUNDER_STOP	0xFFF7			// ����p
#define WEATHER_EARTHQUAKE_STOP	0xFFEF			// ����a�_

// ===== ���񱱨�R�O
#define WEATHER_CLEAR		0					// �M��
#define WEATHER_STARTUP		1					// �}�l
#define WEATHER_STOP		2					// ����

// ===== �ƶq�j�p����R�O
#define WEATHER_SMALL		0					// �p // �b�������p	�Ƕ�
#define WEATHER_MIDDLE		1					// �� //			�¶�
#define WEATHER_LARGE		2					// �j //			�ն�


// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct WEATHER_PARAMETER_STRUCT
{
	SLONG wind_dir;								// ���V
	SLONG wind_range;							// ���V�j�p
	SLONG status;								// �Ѯ𱱨�R�O  

	SLONG rain_command;							// �U�B����R�O
	SLONG rain_range;							// �U�B�j�p�R�O

	SLONG snow_command;							// �U������R�O
	SLONG snow_range;							// �U���j�p�R�O

	SLONG thunder_command;						// ���p����R�O
	SLONG thunder_range;						// ���p�j�p�R�O

	SLONG cloud_command;						// ������R�O
	SLONG cloud_range;							// �����j�p�R�O

	SLONG earthquake_command;					// �a�_����R�O
	SLONG earthquake_range;						// �a�_�j�p�R�O

	SLONG x_offset;								// ���t�������q
	SLONG y_offset;
	SLONG rain_process_count;					// �U�B�B�zcount
	SLONG snow_process_count;					// �U���B�zcount
	SLONG thunder_process_count;				// ���p�B�zcount
	SLONG cloud_process_count;					// ���B�zcount
	SLONG earthquake_process_count;				// �a�_�B�zcount

} WEATHER_PARAMETER ;


typedef struct WEATHER_RAIN_DATA_STRUCT
{
	SLONG active;								// �B�w�Ұ�flag  
												//			0 -> disable
												//			1 -> in sky 
												//			2 -> in ground
	SLONG x;									// ���a�y��
	SLONG y;
	SLONG height;								// �B�w����

} WEATHER_RAIN_DATA ;


typedef struct WEATHER_SNOW_DATA_STRUCT
{
	SLONG active;								// ���Ұ�flag  
												//			0 -> disable
												//			1 -> in sky 
												//			2 -> in ground
	SLONG x;									// ���a�y��
	SLONG y;
	SLONG height;								// ������
	SLONG size;									// �����j�p

} WEATHER_SNOW_DATA ;


typedef struct WEATHER_CLOUD_DATA_STRUCT
{
	SLONG active;								// ���Ұ�
												//			0 -> disable
												//			1 -> startup 
												//			2 -> show
												//          3 -> close
	SLONG x;									// �y��
	SLONG y;
	SLONG timer;
	SLONG type;									// ����

} WEATHER_CLOUD_DATA;


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
// ----------- subtinue define area ------------------------------------------------
int     init_weather(void);
void    free_weather(void);
void    active_weather(int flag);
void    refresh_weather(void);
void    control_wind(SLONG wind_dir,SLONG wind_range);
void    control_weather(SLONG weather_type,SLONG weather_command,SLONG weather_range);
void    exec_weather(BMP *bitmap);
void    weather_adjust_map_move(void);
//
void    get_current_weather_wind(SLONG *wind_dir, SLONG *wind_range);
SLONG   get_current_weather_type(void);
SLONG   weather_wind_dir_to_ui_wind_dir(SLONG weather_wind_dir);
void	get_zone_weather_wind_for_boat(SLONG *dir, SLONG *force);
void	init_zone_weather(void);



#endif//_WEATHER_H_
