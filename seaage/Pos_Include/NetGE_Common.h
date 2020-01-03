/*
**	NetGE_Common.h 
**	POS common header files.
**
**	Jack, 2002.12.4
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	SCREEN_WIDTH		800
#define	SCREEN_HEIGHT		600

#define	PI					3.1415927

//----------------------------------------------------------------------------
// ��a�w�q
//----------------------------------------------------------------------------
/*
#define     CHINA                           'A'	  // ����
#define     ENGLAND                         'B'   // �^��
#define     SWEDEN                          'C'   // ���
#define     FRANCE							'D'   // �k��
#define     GERMANY							'E'   // �w��
#define     SPAIN							'F'   // ��Z��
#define     PORTUGAL						'G'	  // �����
#define     ITALY							'H'   // �q�j�Q
#define     DENMRKE							'I'   // ����
#define     FINLAND							'J'   // ����
#define     GREECE							'K'   // ��þ
#define     NORWAY							'L'   // ����
#define     IRELAND							'M'   // �R����
#define     TUNIS							'N'   // �𥧴�
#define     ARAB							'O'   // ���ԧB
#define     TURKEY							'P'   // �g�ը�
#define     AFRICA							'Q'   // �D�w
#define     KOREA							'R'   // ����
#define     JAPAN							'S'   // �饻
#define     INDIA							'T'   // �L��
*/
//
#define     COUNTRY_CHINA                   'A'	  // ����
#define     COUNTRY_ENGLAND                 'B'   // �^��
#define     COUNTRY_SWEDEN                  'C'   // ���
#define     COUNTRY_FRANCE					'D'   // �k��
#define     COUNTRY_GERMANY					'E'   // �w��
#define     COUNTRY_SPAIN					'F'   // ��Z��
#define     COUNTRY_PORTUGAL				'G'	  // �����
#define     COUNTRY_ITALY					'H'   // �q�j�Q
#define     COUNTRY_DENMRKE					'I'   // ����
#define     COUNTRY_FINLAND					'J'   // ����
#define     COUNTRY_GREECE					'K'   // ��þ
#define     COUNTRY_NORWAY					'L'   // ����
#define     COUNTRY_IRELAND					'M'   // �R����
#define     COUNTRY_TUNIS					'N'   // �𥧴�
#define     COUNTRY_ARAB					'O'   // ���ԧB
#define     COUNTRY_TURKEY					'P'   // �g�ը�
#define     COUNTRY_AFRICA					'Q'   // �D�w
#define     COUNTRY_KOREA					'R'   // ����
#define     COUNTRY_JAPAN					'S'   // �饻
#define     COUNTRY_INDIA					'T'   // �L��

//----------------------------------------------------------------------------
// �C������¾�~�w�q
//----------------------------------------------------------------------------
/*
#define     GENERAL                         'A'   // ����
#define     SWORDER                         'B'   // �C�h
#define     THIEF                           'C'   // �p��
#define     TRADER                          'D'   // �ӤH
#define     EXPLORER                        'E'   // ���I�a
#define     CLERIC                          'F'   // ���v
#define     HOROSCOPER                      'G'   // �e�P�N�h
*/
//
#define     CAREER_GENERAL                  'A'   // ����
#define     CAREER_SWORDER                  'B'   // �C�h
#define     CAREER_THIEF                    'C'   // �p��
#define     CAREER_TRADER                   'D'   // �ӤH
#define     CAREER_EXPLORER                 'E'   // ���I�a
#define     CAREER_CLERIC                   'F'   // ���v
#define     CAREER_HOROSCOPER               'G'   // �e�P�N�h
// ---------------------------------------------------------------------------
// �H���ʧO�w�q
// ---------------------------------------------------------------------------
#define		MALE                            'A'   // �k
#define		FEMALE                          'B'   // �k
//
#define		SEX_MALE                        'A'   // �k
#define		SEX_FEMALE                      'B'   // �k

//----------------------------------------------------------------------------
// �ϥΤH�w�q(�p���~�ϥΤH, �ޯ�ϥΤH��)
//----------------------------------------------------------------------------
#define		USER_SEX_MALE						0x00000001  //�k�ʱM��
#define		USER_SEX_FEMALE						0x00000002  //�k�ʱM��
//
#define		USER_CAREER_GENERAL					0x00000010  //�����M��
#define		USER_CAREER_SWORDER           		0x00000020  //�C�h�M��
#define		USER_CAREER_THIEF             		0x00000040  //�p���M��
#define		USER_CAREER_TRADER            		0x00000080  //�ӤH�M��
#define		USER_CAREER_EXPLORER          		0x00000100  //���I�a�M��
#define		USER_CAREER_CLERIC            		0x00000200  //���v�M��
#define		USER_CAREER_HOROSCOPER        		0x00000400  //�e�P�N�h(�]�k�v)
//
//----------------------------------------------------------------------------
// ���k��w�q
//----------------------------------------------------------------------------
#define		LEFT_HAND							0			//����
#define		RIGHT_HAND							1			//�k��

//----------------------------------------------------------------------------
// ��o�C��ɨϥ�
//----------------------------------------------------------------------------
#define		BEGIN			        			0
#define		NEXT			        			1
#define     END									99999

//----------------------------------------------------------------------------
// �C����ޭȩw�q
//----------------------------------------------------------------------------
#define		COLOR_RED							1
#define		COLOR_GREEN							2
#define		COLOR_BLUE							3
#define		COLOR_GRAY							4
#define		COLOR_YELLOW						5	//GOLD
#define		COLOR_BLACK							6

//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	union	tagARGB_DATA
{
	ULONG		u4;
	struct  
	{
		UCHR	a;
		UCHR	r;
		UCHR	g;
		UCHR	b;
	};
} ARGB_DATA, *LPARGB_DATA;


// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	ULONG	MakeUserDescriptionByCareerSex(SLONG lCareer, SLONG lSex);
//
extern	SLONG	WindingItemAxisPosition(SLONG n, SLONG *x, SLONG *y);
extern	SLONG	WindingAttackAxisPosition(SLONG n, SLONG *x, SLONG *y);
extern	int		GetHostIp(LPSTR lpszIP, DWORD dwStrLen, CHAR **lpcIPArray, DWORD *dwArrayCount);
extern	void	EncodeSeaNpcSyncPosition(SLONG &sync_x,SLONG &sync_y,SLONG &sync_z,
										 SLONG degree_dir, SLONG x, SLONG y,
										 SLONG speed_x, SLONG speed_y);
extern	void	DecodeSeaNpcSyncPosition(SLONG sync_x, SLONG sync_y, SLONG sync_z, 
										 SLONG &degree_dir, SLONG &x, SLONG &y,
										 SLONG &speed_x, SLONG &speed_y);
extern	SLONG   ApproachScreenAxisDirEx(SLONG dx, SLONG dy, SLONG parts);
extern	SLONG	ApproachScreenAxisDegreeDirEx(SLONG degree, SLONG parts);
extern	SLONG   ComputeScreenAxisDegree(double dx, double dy);
extern	SLONG   ComputeShipSailVelocity(SLONG dist, SLONG v, SLONG vmax, SLONG acc, SLONG keep_steps);
extern	SLONG   ComputeShipWerveVelocity(SLONG v, SLONG vmax, SLONG acc);
extern	double  ComputeShipWerveRadius(SLONG v, SLONG veer);
extern	SLONG   ComputeShipSwerveAngle(SLONG x, SLONG y, SLONG dir_degree, SLONG veer, SLONG dest_x, SLONG dest_y);
extern	SLONG   IsShipCanSailTo(SLONG x, SLONG y, SLONG dir_degree, SLONG v, SLONG veer, SLONG dest_x, SLONG dest_y);
extern	float	FloatToPrecision10Float(float value);
extern	ULONG	GameIndexColorToTrueColor(SLONG index);


