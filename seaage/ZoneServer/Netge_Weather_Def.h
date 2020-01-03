#ifndef NETGE_WEATHER_DEF_H
#define NETGE_WEATHER_DEF_H
//------------------------------------------------------------------------------
// ���V����R�O���c
#define WIND_RIGHT		       0		// �V�k�j
#define WIND_RIGHT_DOWN	       1		// �V�k�U�j
#define WIND_DOWN			   2		// �V�U�j
#define WIND_LEFT_DOWN		   3		// �V���U�j
#define WIND_LEFT			   4		// �V���j
#define WIND_LEFT_UP		   5		// �V���W�j
#define WIND_UP			       6		// �V�W�j
#define WIND_UP_RIGHT		   7		// �V�k�W�j

#define WIND_NONE			   0		// �S����
#define WIND_SMALL		       1		// �p��
#define WIND_MIDDLE		       2		// ����
#define WIND_LARGE		       3		// �j��
#define WIND_DUMMY             4        // ������

// �Ѯ𱱨�R�O
#define WEATHER_NORMAL		   0x00000000		// ����
#define WEATHER_RAIN		   0x00000001		// �U�B
#define WEATHER_SNOW		   0x00000002		// �U��
#define WEATHER_CLOUD		   0x00000004		// ���ζ�
#define WEATHER_THUNDER	       0x00000008		// ���p
#define WEATHER_EARTHQUAKE	   0x00000010		// �a�_
#define WEATHER_DUMMY          0x80000000       // ������

// ���񱱨�R�O
#define WEATHER_CLEAR		   0		// �M��
#define WEATHER_STARTUP	       1		// �}�l
#define WEATHER_STOP		   2		// ����

// �ƶq�j�p����R�O
#define WEATHER_SMALL		   0		// �p // �b�������p	�Ƕ�
#define WEATHER_MIDDLE	       1		// �� //			�¶�
#define WEATHER_LARGE		   2		// �j //			�ն�

#pragma pack(push)
#pragma pack(1)
//------------------------------------------------------------------------------
// �Ѯ�
//------------------------------------------------------------------------------
typedef struct
{
 DWORD      dType;      // ���w�n�U���ؤѮ𪺺��� 
 DWORD      dActive;    // �}�l,�M��,����
 DWORD      dSize;      // �j�p 
 DWORD      dWindSize;  // ���V�j�p 
 DWORD      dWindDir;   // ���V��V
}TPOS_WEATHER;
//------------------------------------------------------------------------------
// ��e�ϰ�Ѯ𵲺c
//------------------------------------------------------------------------------
typedef struct
{
 DWORD      dWeatherType;      // �Ѯ𫬺A  
 DWORD      dRainActive;       // �O�_�U�B
 DWORD      dRainSize;         // �B���j�p
 DWORD      dSnowActive;       // �O�_�U��
 DWORD      dSnowSize;         // �����j�p
 DWORD      dCloudActive;      // �O�_����
 DWORD      dCloudSize;        // �����j�p
 DWORD      dThunderActive;    // �O�_���p  
 DWORD      dThunderSize;      // �p���j�p
 DWORD      dEarthQuakeActive; // �O�_�a�_
 DWORD      dEarthQuakeSize;   // �a�_�j�p 
 DWORD      dWindSize;         // �����j�p  
 DWORD      dWindDir;          // ���V��V
}TPOS_ZONEWEATHER;
//------------------------------------------------------------------------------
#pragma pack(pop)

#endif