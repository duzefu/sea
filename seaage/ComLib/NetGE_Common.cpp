/*
**	NetGE_Common.cpp 
**	Pos common functions.
**
**	Jack, 2002.12.11
*/
#include "NetGE_Mainfunc.h"


#pragma	comment(lib, "ws2_32")


/************************************************************************************************************/
/* COMMON FUNCTIONS                                                                                         */
/************************************************************************************************************/
ULONG	MakeUserDescriptionByCareerSex(SLONG lCareer, SLONG lSex)
{
	ULONG	User;

	User = 0;
	switch(lSex)
	{
	case SEX_MALE:
		User |= USER_SEX_MALE;
		break;
	case SEX_FEMALE:
		User |= USER_SEX_FEMALE;
		break;
	}
	switch(lCareer)
	{
	case CAREER_GENERAL:	// ����
		User |= USER_CAREER_GENERAL;
		break;
	case CAREER_SWORDER:	// �C�h
		User |= USER_CAREER_SWORDER;
		break;
	case CAREER_THIEF:		// �p��
		User |= USER_CAREER_THIEF;
		break;
	case CAREER_TRADER:	// �ӤH
		User |= USER_CAREER_TRADER;
		break;
	case CAREER_EXPLORER:	// ���I�a
		User |= USER_CAREER_EXPLORER;
		break;
	case CAREER_CLERIC:	// ���v
		User |= USER_CAREER_CLERIC;
		break;
	case CAREER_HOROSCOPER:// �e�P�N�h
		User |= USER_CAREER_HOROSCOPER;
		break;
	}
	return	User;
}


//
//�\�� : �p����Ӥ@�w���ǥѤ��V�~��¶�T�w�I����n�I���۹�y��.
//       �Ӷ��Ǧp�H�U�ϥ�:
//                    |
//                    |
//             24 23 22 21 20
//             19  8  7  6 18
//----------   17  5  0  4 16   --------------------> (X)
//             15  3  2  1 14
//             13 12 11 10  9
//                    |
//                    |    
//                    V (Y)
//
//�Ѽ� : SLONG  n       ->  ��n�I(n = 0,1,2,3,...)
//       SLONG  *x      ->  �s���^���۹�y�Ф� X.
//       SLONG  *y      ->  �s���^���۹�y�Ф� Y.
//�^�� : ���\���^ TTN_OK, �ñN�۹�y�Цs��b (*x, *y) ��.
SLONG	WindingItemAxisPosition(SLONG n, SLONG *x, SLONG *y)
{
	SLONG	k, r, under, top, rest;

	//________________________________________________________________
	//(n)
	//                    |
	//                    |
	//             24 23 22 21 20
	//             19  8  7  6 18
	//----------   17  5  0  4 16   --------------------> (X)
	//             15  3  2  1 14
	//             13 12 11 10  9
	//                    |
	//                    |    
	//                    V (Y)
	//                    
	//________________________________________________________________
	//(x)
	//                    |
	//                    |
	//             -2 -1  0  1  2
	//             -2 -1  0  1  2
	//----------   -2 -1  0  1  2   --------------------> (X)
	//             -2 -1  0  1  2
	//             -2 -1  0  1  2
	//                    |
	//                    |    
	//                    V (Y)
	//
	//
	//________________________________________________________________
	//(y)
	//                    |
	//                    |
	//             -2 -2 -2 -2 -2
	//             -1 -1 -1 -1 -1
	//----------    0  0  0  0  0   --------------------> (X)
	//              1  1  1  1  1
	//              2  2  2  2  2
	//                    |
	//                    |    
	//                    V (Y)
	//

	if(n == 0)
	{
		*x = 0;
		*y = 0;
		return	TTN_OK;
	}

	k = (SLONG) sqrt(n);
	k = (k + 1) / 2 * 2 + 1;
	r = k / 2;
	under = (k - 2) * (k - 2);
	top = k * k;

	if(n < under + k)
	{
		*x = under + r - n;
		*y = r;
		return	TTN_OK;
	}

	if( n >= top - k)
	{
		*x = (top-1) - n - r;
		*y = -r;
		return	TTN_OK;
	}

	rest = n - (under + k);
	*x = (rest % 2) ? -r : r;
	*y = (r - 1) - rest / 2;

	return	TTN_OK;
}



//
//�\�� : �p����Ӥ@�w����¶�T�w�I�Ѥ��V�~����n�ӧ����I���۹�y��.
//       �Ӷ��Ǧp�U�ҥ�:
//                        |                                       
//                        |                                       
//             35  34  33 | 32  31  30                            
//             29  15  14 | 13  12  28                            
//             27  11  02 | 03  10  26                            
//------------------------+---------------------------> (X)       
//             25  09  01 | 00  08  24                                 
//             23  07  06 | 05  04  22                                 
//             21  20  19 | 18  17  16                               
//                        |                                       
//                        |                                        
//                        V (Y)                                        
//
//�Ѽ� : SLONG n        ->  ��n�ӧ����I�I
//       SLONG *x       ->  �s���^���۹�y��x
//       SLONG *y       ->  �s���^���۹�y��y
//�^�� : ���\���^ TTN_OK, �ñN�۹�y�Цs��b (*x, *y) ��.
SLONG	WindingAttackAxisPosition(SLONG n, SLONG *x, SLONG *y)
{
	SLONG	k, r, under, top, rest;

	//________________________________________________________________
	// N = F(X, Y)                                                    
	//                                                                
	//                                                                
	//                        |                                       
	//                        |                                       
	//             35  34  33 | 32  31  30                            
	//             29  15  14 | 13  12  28                            
	//             27  11  02 | 03  10  26                            
	//------------------------+---------------------------> (X)       
	//             25  09  01 | 00  08  24                                 
	//             23  07  06 | 05  04  22                                 
	//             21  20  19 | 18  17  16                               
	//                        |                                       
	//                        |                                        
	//                        V (Y)                                        
	//________________________________________________________________
	//(x)
	//                                                                
	//                                                                
	//                        |                                       
	//                        |                                       
	//            -5  -3  -1  |  1  3  5                            
	//            -5  -3  -1  |  1  3  5                            
	//            -5  -3  -1  |  1  3  5                            
	//------------------------+---------------------------> (X)       
	//            -5  -3  -1  |  1  3  5                                 
	//            -5  -3  -1  |  1  3  5                                 
	//            -5  -3  -1  |  1  3  5                               
	//                        |                                        
	//                        |                                        
	//                        V (Y)                                        
	//________________________________________________________________
	//(y)
	//                                                                
	//                        |                                       
	//                        |                                       
	//            -5  -5  -5  | -5 -5 -5                            
	//            -3  -3  -3  | -3 -3 -3                            
	//            -1  -1  -1  | -1 -1 -1                            
	//------------------------+---------------------------> (X)       
	//             1   1   1  |  1  1  1                                 
	//             3   3   3  |  3  3  3                                 
	//             5   5   5  |  5  5  5                               
	//                        |                                        
	//                        |                                        
	//                        V (Y)                                        
	//

	if(n < 0)
	{
		*x = 0;
		*y = 0;
		return	TTN_OK;
	}

	//�p�� n ����ĴX�餤
	k = (SLONG) sqrt(n);
	k = k / 2 * 2 + 2;	//�C��(�C)���ƭȪ��Ӽ�(��}���j�p)

	under = (k - 2) * (k - 2);	//�̩��U�@�檺�_�l��
	top = k * k - 1;			//�̳��W�@�檺�̲׭�
	r = k / 2 * 2 - 1;	//�����I��(X/Y)�ƭ�

	//���̩��U�@��
	if(n < under + k)	
	{
		*x = r + (under - n) * 2 ;
		*y = r;
		return	TTN_OK;
	}

	//���̳��W�@��
	if( n > top - k)
	{
		*x = (top - n) * 2 - r;
		*y = -r;
		return	TTN_OK;
	}

	//��󥪥k�ⰼ
	rest = n - (under + k);
	*x = (rest % 2) ? -r : r;
	*y = (r - 2) - rest / 2 * 2;

	return	TTN_OK;
}



//�\��: ��o������IP�a�}��T
//�Ѽ�: lpszIP			-> [OUT] �s��IP��T�r��
//      dwStrLen		-> [IN]  IP��T�r��w�Ĥj�p
//      lpcIPArray		-> [OUT] �s��IP�a�}���, ���ӮѼg����, �p192,168,0,106.
//		dwArrayCount	-> [OUT] IP�a�}��Ʀ쪺�Ӽ�
//�^��: ���\���^ TTN_OK, �_�h��^��L��.
//�`�N: �ݭn����l��WinSock�H��~��ϥ�.
int GetHostIp( LPSTR lpszIP, DWORD dwStrLen, CHAR **lpcIPArray, DWORD *dwArrayCount)
{
    struct hostent *site;
    char   strLocalName[256];
    static char cIp[8];
    LPSTR  lpszBuf; 

	if (!lpszIP || !lpcIPArray)
		return TTN_NOT_OK;

	*lpcIPArray = NULL;
	*dwArrayCount = 0;
	lpszIP[0] = '\0';

    if ( SOCKET_ERROR == gethostname( strLocalName, 256) )
        return TTN_NOT_OK;
	
    if ( NULL == ( site = gethostbyname(strLocalName) ) )
        return TTN_NOT_OK;
	
    if ( NULL == ( lpszBuf = inet_ntoa(*(struct in_addr *)*site->h_addr_list) ) )
        return TTN_NOT_OK;
    
	cIp[0] = ((struct in_addr *)*site->h_addr_list)->s_net;
	cIp[1] = ((struct in_addr *)*site->h_addr_list)->s_host;
	cIp[2] = ((struct in_addr *)*site->h_addr_list)->s_lh;
	cIp[3] = ((struct in_addr *)*site->h_addr_list)->s_impno;

	*lpcIPArray = cIp;
	*dwArrayCount = 4;
		
	lstrcpyn( lpszIP, lpszBuf, dwStrLen );
	
    return TTN_OK;
}



void	EncodeSeaNpcSyncPosition(SLONG &sync_x,SLONG &sync_y,SLONG &sync_z,
								 SLONG degree_dir, SLONG x, SLONG y,
								 SLONG speed_x, SLONG speed_y)
{
	// range of degree_dir: (0-359) 9bits
	// speed_x (+-500)    10bits
	// speed_y (+-500)	  10bits
	// sync_z: 3bit + 9bit(degree_dir) + 10bit(speedx) + 10bit(speedy)
	ULONG	ulong_speed_x, ulong_speed_y, ulong_degree_dir;	

	ulong_speed_x = (ULONG)(500 + speed_x);
	ulong_speed_y = (ULONG)(500 + speed_y);
	ulong_speed_x = (ulong_speed_x << 10) & 0x000ffc00;
	ulong_speed_y = ulong_speed_y & 0x000003ff;
	ulong_degree_dir = (ULONG)degree_dir;
	ulong_degree_dir = (ulong_degree_dir << 20) & 0x3ff00000;
	sync_z = ulong_degree_dir | ulong_speed_x | ulong_speed_y;
	sync_x = x;
	sync_y = y;
}


void DecodeSeaNpcSyncPosition(SLONG sync_x, SLONG sync_y, SLONG sync_z, 
							  SLONG &degree_dir, SLONG &x, SLONG &y,
							  SLONG &speed_x, SLONG &speed_y)
{
	ULONG	ulong_z;
	ULONG	ulong_speed_x, ulong_speed_y, ulong_degree_dir;

	ulong_z = (ULONG)sync_z;
	ulong_speed_y = ulong_z & 0x000003ff;
	ulong_speed_x = (ulong_z & 0x000ffc00) >> 10;
	ulong_degree_dir = (ulong_z & 0x3ff00000) >> 20;
	degree_dir = (SLONG)ulong_degree_dir;
	speed_x = (SLONG)ulong_speed_x - 500;
	speed_y = (SLONG)ulong_speed_y - 500;
	x = sync_x;
	y = sync_y;
}

//�\�� : �ھڶb�V�t�Z�p���V���޸�(�̹��y�Шt)
//�Ѽ� : SLONG  dx      ->  X�b(�̹��ۥ��ܥk)�t�Z
//       SLONG  dy      ->  Y�b(�̹��ۥ��ܥk)�t�Z
//       SLONG  parts   ->  ��P��V�`��.
//�^�� : ��V���ޭ�, �� [0, parts-1].
SLONG   ApproachScreenAxisDirEx(SLONG dx, SLONG dy, SLONG parts)
{
    SLONG   degree, dir, part_degree;

    if(parts <= 0)
        return  0;

    // Get degree between [0, 2 * PI] -> [0, 36000].
    degree = (SLONG)( atan2(dy, dx) * 36000 / ( 2 * PI ) );
    if(degree < 0)
        degree += 36000;

    part_degree = 36000 / parts;

    // Add part_degree/2 to match near degree to dir.
    dir = ( degree + part_degree / 2 ) / part_degree;

    // Over will be set to 0.
    if(dir > parts - 1) dir = 0;

    return  dir;
}


//�\�� : �ھګ̹����׭p���V���޸�(�̹��y�Шt)
//�Ѽ� : SLONG  degree  ->  �̹�����, [0, 36000]
//       SLONG  parts   ->  ��P��V�`��.
//�^�� : ��V���ޭ�, �� [0, parts-1].
SLONG	ApproachScreenAxisDegreeDirEx(SLONG degree, SLONG parts)
{
    SLONG   dir, part_degree;

    if(parts <= 0)
        return  0;

    part_degree = 36000 / parts;

    // Add part_degree/2 to match near degree to dir.
    dir = ( degree + part_degree / 2 ) / part_degree;

    // Over will be set to 0.
    if(dir > parts - 1) dir = 0;

    return  dir;
}

//�\�� : �ھڶb�V�t�Z�p�⨤��(�̹��y�Шt)
//�Ѽ� : double dx       -> X�b(�̹��ۥ��ܥk)�t�Z
//       double dy       -> Y�b(�̹��ۤW�ܤU)�t�Z
//�^�� : ����, �d��[0, 36000).
SLONG   ComputeScreenAxisDegree(double dx, double dy)
{
    SLONG   degree;

    degree = (SLONG)( atan2(dy, dx) * 36000 / ( 2 * PI ) );
    if(degree < 0)
        degree += 36000;
    return  degree;
}


//
//�\�� : �p�����������ϥΪ��t��(�Ҽ{����[�t��)
//�Ѽ� : SLONG dist         -> ��Z���ؼ��I���Z��.
//       SLONG v            -> ���e���t��.
//       SLONG vmax         -> ����̤j���t��.
//       SLONG acc          -> ����[�t��.
//       SLONG keep_steps   -> ����ɥH�Y�t�ׯ��(����U���t�ק���)���B��.
//�^�� : ����t��.
SLONG   ComputeShipSailVelocity(SLONG dist, SLONG v, SLONG vmax, SLONG acc, SLONG keep_steps)
{
    /*
    **  ���]���e�t�׬�v, �̤j�t�׬�vmax, �Z���ؼ��I���Z����dist, �[�t�׬�a, ���F�ؼ��I�ɪ��t�׬�vmin.
    **  �ϨҪ�ܱq�t��0�}�l�B�ʨ쵲���t��0, �åB�Z���������ɪ��L�{�p�U:
    **
    **      S......(�[�t��).....|.......(�ót��)......|....(��t��).........D
    **
    **���ڭ̥��Ҽ{��C�B�ʤ@�B�N�[�t(��t)�@��.
    **
    **  �]��q��e�t�ת��A�}�l��t�����檺�Z����dist0, ����dist0���{�ɴ�t�Z��.
    **  �p���t�{�ɶZ��dist0:
    **      ��q��e�t��v�}�l��t, ��ؼ��I�t�׬�0, �ݭn���ɶ���t0, 
    **          t0 = (vmin - v) / (- a);
    **      �Z��dist0,
    **          dist0 = v * t0 + (-a) * t0 * t0 / 2;
    **
    **�����]��H��e�t�רC�B�� k �B��}�l�[�t(��t)�@��, ���������dist0�p�U:
    **          kdist0 = k * dist0 = k * v * v / a / 2;
    **
    */
    enum {VMIN = 4};
    double  t0, dist0;
    SLONG   kdist0;

    t0 = (double)(VMIN - v) / (double)(-acc);
    dist0 = v * t0 + (-acc) * t0 * t0 / 2;
    kdist0 = (SLONG)(keep_steps * dist0 + 0.5);
    if(dist < kdist0)
    {//��e�Z���p���t�{�ɶZ��(��t��0�ɪ��Z��)��, �}�l��t.
        return  max(v - acc, VMIN);
    }
    else if(dist < kdist0 + v * keep_steps)
    {//�O���ثe�t��, ������Fkeep_steps�B���F�U�@�Ӵ�t�{���I.
        return  v;
    }
    else
    {//�_�h, �@���[�t.
        return  min(v+acc, vmax);
    }
}


//�\�� : �p���b��V���ɭ����ӨϥΪ��t��(�Ҽ{�[�t��).
SLONG   ComputeShipWerveVelocity(SLONG v, SLONG vmax, SLONG acc)
{
    return  min(v+acc, vmax);
}


//�\�� : �p�������s�b�|.
double  ComputeShipWerveRadius(SLONG v, SLONG veer)
{
    /*
    �p��������s���̤p�b�|:
    �]��V���C�B�樫�Z���� s, ���B�M�U�B�������ਤ�� t, �h���s�b�|��:
    R = s / 2 / sin(t/2) = s * csc(t/2) / 2.
    */
    double  r;
    r = v / ( 2 * sin(veer * PI / 18000 / 2) );
    return  r;
}


//�\�� : �p����e�ݭn��ʪ�����.
SLONG   ComputeShipSwerveAngle(SLONG x, SLONG y, SLONG dir_degree, SLONG veer, SLONG dest_x, SLONG dest_y)
{
    SLONG   dx, dy, dir_dx, dir_dy, delta;
    SLONG   dest_degree, delta_degree, swerve_degree;
    double  sita;

    dx = dest_x - x;
    dy = dest_y - y;
    dest_degree = ComputeScreenAxisDegree(dx, dy);
    
    sita = dir_degree * PI / 18000;
    dir_dx = (SLONG)(100 * cos(sita));
    dir_dy = (SLONG)(100 * sin(sita));
    delta_degree = D2_nipangle_line_line(0, 0, dir_dx, dir_dy, 0, 0, dx, dy);
    if(delta_degree < veer)
    {
        swerve_degree = dest_degree - dir_degree;
    }
    else
    {
        delta = dir_dx * dy - dir_dy * dx;
        if(delta > 0)
            swerve_degree = veer;
        else
            swerve_degree = -veer;
    }
    return  swerve_degree;
}


//�\�� : �P�_��O�_�i�H��F�ؼ��I.
SLONG   IsShipCanSailTo(SLONG x, SLONG y, SLONG dir_degree, SLONG v, SLONG veer, SLONG dest_x, SLONG dest_y)
{
    //���i��F�ϰ�: 
    //�H���e��V�����߶b, ��ⰼ�P�Ӷb�ۤ�, �b�|����̤p���s�b�|����.
    /*
    ��樫������V�B�z:
    �]��V���C�B�樫�Z���� s, ���B�M�U�B�������ਤ�� t, �h���s�b�|��:
    R = s / 2 / sin(t/2) = s * csc(t/2) / 2.
    */
    double  r, sita, a1, a2;
    double  x1, y1, x2, y2;
    double  dx, dy, dist1, dist2;

    //�p��������s���̤p�b�|�C
    sita = veer * PI / 18000 / 2;
    r = v / ( 2 * sin(sita) );

    //�p��P��e��V�۫������A�ⰼ���A�����F���A��ΰϰ쪺��߮y�СC
    a1 = (dir_degree + 9000) * PI / 18000;
    a2 = (dir_degree - 9000) * PI / 18000;
    x1 = x + r * cos(a1);
    y1 = y + r * sin(a1);
    x2 = x + r * cos(a2);
    y2 = y + r * sin(a2);

    //�P�_�ؼ��I�O�_��󤣯��F�ϰ�C
    dx = dest_x - x1;
    dy = dest_y - y1;
    dist1 = sqrt(dx * dx + dy * dy);
    if(dist1 < r)
        return  FALSE;
    dx = dest_x - x2;
    dy = dest_y - y2;
    dist2 = sqrt(dx * dx + dy * dy);
    if(dist2 < r)
        return  FALSE;

    return  TRUE;
}

//PS: �u��� float �b�����d�򤺪���.
float	FloatToPrecision10Float(float value)
{
	return	(float)((long)(value * 10) / 10.0);
}



ULONG	GameIndexColorToTrueColor(SLONG index)
{
	switch(index)
	{
	case COLOR_RED:		return	U4_SYSTEM_RED;
	case COLOR_GREEN:	return	U4_SYSTEM_GREEN;
	case COLOR_BLUE:	return	U4_SYSTEM_BLUE;
	case COLOR_GRAY:	return	U4_SYSTEM_DARK3;
	case COLOR_YELLOW:	return	U4_SYSTEM_YELLOW;
	case COLOR_BLACK:	return	U4_SYSTEM_BLACK;
	default:			return	U4_SYSTEM_BLUE;
	}
}


