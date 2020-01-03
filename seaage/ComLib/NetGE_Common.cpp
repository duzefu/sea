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
	case CAREER_GENERAL:	// 提督
		User |= USER_CAREER_GENERAL;
		break;
	case CAREER_SWORDER:	// 劍士
		User |= USER_CAREER_SWORDER;
		break;
	case CAREER_THIEF:		// 小偷
		User |= USER_CAREER_THIEF;
		break;
	case CAREER_TRADER:	// 商人
		User |= USER_CAREER_TRADER;
		break;
	case CAREER_EXPLORER:	// 探險家
		User |= USER_CAREER_EXPLORER;
		break;
	case CAREER_CLERIC:	// 牧師
		User |= USER_CAREER_CLERIC;
		break;
	case CAREER_HOROSCOPER:// 占星術士
		User |= USER_CAREER_HOROSCOPER;
		break;
	}
	return	User;
}


//
//功能 : 計算按照一定順序由內向外環繞固定點的第n點的相對座標.
//       該順序如以下圖示:
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
//參數 : SLONG  n       ->  第n點(n = 0,1,2,3,...)
//       SLONG  *x      ->  存放返回的相對座標之 X.
//       SLONG  *y      ->  存放返回的相對座標之 Y.
//回傳 : 成功後返回 TTN_OK, 並將相對座標存放在 (*x, *y) 中.
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
//功能 : 計算按照一定順序繞固定點由內向外的第n個攻擊點的相對座標.
//       該順序如下所示:
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
//參數 : SLONG n        ->  第n個攻擊點點
//       SLONG *x       ->  存放返回的相對座標x
//       SLONG *y       ->  存放返回的相對座標y
//回傳 : 成功後返回 TTN_OK, 並將相對座標存放在 (*x, *y) 中.
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

	//計算 n 落於第幾圈中
	k = (SLONG) sqrt(n);
	k = k / 2 * 2 + 2;	//每行(列)的數值的個數(圈陣的大小)

	under = (k - 2) * (k - 2);	//最底下一行的起始值
	top = k * k - 1;			//最頂上一行的最終值
	r = k / 2 * 2 - 1;	//角頂點的(X/Y)數值

	//位於最底下一行
	if(n < under + k)	
	{
		*x = r + (under - n) * 2 ;
		*y = r;
		return	TTN_OK;
	}

	//位於最頂上一行
	if( n > top - k)
	{
		*x = (top - n) * 2 - r;
		*y = -r;
		return	TTN_OK;
	}

	//位於左右兩側
	rest = n - (under + k);
	*x = (rest % 2) ? -r : r;
	*y = (r - 2) - rest / 2 * 2;

	return	TTN_OK;
}



//功能: 獲得本機的IP地址資訊
//參數: lpszIP			-> [OUT] 存放IP資訊字串
//      dwStrLen		-> [IN]  IP資訊字串緩衝大小
//      lpcIPArray		-> [OUT] 存放IP地址整數, 按照書寫順序, 如192,168,0,106.
//		dwArrayCount	-> [OUT] IP地址整數位的個數
//回傳: 成功後返回 TTN_OK, 否則返回其他值.
//注意: 需要先初始化WinSock以後才能使用.
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

//功能 : 根據軸向差距計算方向索引號(屏幕座標系)
//參數 : SLONG  dx      ->  X軸(屏幕自左至右)差距
//       SLONG  dy      ->  Y軸(屏幕自左至右)差距
//       SLONG  parts   ->  圓周方向總數.
//回傳 : 方向索引值, 為 [0, parts-1].
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


//功能 : 根據屏幕角度計算方向索引號(屏幕座標系)
//參數 : SLONG  degree  ->  屏幕角度, [0, 36000]
//       SLONG  parts   ->  圓周方向總數.
//回傳 : 方向索引值, 為 [0, parts-1].
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

//功能 : 根據軸向差距計算角度(屏幕座標系)
//參數 : double dx       -> X軸(屏幕自左至右)差距
//       double dy       -> Y軸(屏幕自上至下)差距
//回傳 : 角度, 範圍為[0, 36000).
SLONG   ComputeScreenAxisDegree(double dx, double dy)
{
    SLONG   degree;

    degree = (SLONG)( atan2(dy, dx) * 36000 / ( 2 * PI ) );
    if(degree < 0)
        degree += 36000;
    return  degree;
}


//
//功能 : 計算船隻直航時應當使用的速度(考慮船隻的加速度)
//參數 : SLONG dist         -> 船隻距離目標點的距離.
//       SLONG v            -> 船隻當前航行速度.
//       SLONG vmax         -> 船隻的最大航行速度.
//       SLONG acc          -> 船隻的加速度.
//       SLONG keep_steps   -> 船隻航行時以某速度航行(直到下次速度改變)的步數.
//回傳 : 船隻的速度.
SLONG   ComputeShipSailVelocity(SLONG dist, SLONG v, SLONG vmax, SLONG acc, SLONG keep_steps)
{
    /*
    **  假設船隻當前速度為v, 最大速度為vmax, 距離目標點的距離為dist, 加速度為a, 船隻到達目標點時的速度為vmin.
    **  圖例表示從速度0開始運動到結束速度0, 並且距離足夠長時的過程如下:
    **
    **      S......(加速區).....|.......(勻速區)......|....(減速區).........D
    **
    **※我們先考慮船隻每運動一步就加速(減速)一次.
    **
    **  設船隻從當前速度狀態開始減速能夠航行的距離為dist0, 那麼dist0為臨界減速距離.
    **  計算減速臨界距離dist0:
    **      船隻從當前速度v開始減速, 到目標點速度為0, 需要的時間為t0, 
    **          t0 = (vmin - v) / (- a);
    **      距離dist0,
    **          dist0 = v * t0 + (-a) * t0 * t0 / 2;
    **
    **※假設船隻以當前速度每運動 k 步後開始加速(減速)一次, 那麼對應的dist0如下:
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
    {//當前距離小於減速臨界距離(減速到0時的距離)時, 開始減速.
        return  max(v - acc, VMIN);
    }
    else if(dist < kdist0 + v * keep_steps)
    {//保持目前速度, 直到航行了keep_steps步後到達下一個減速臨界點.
        return  v;
    }
    else
    {//否則, 一直加速.
        return  min(v+acc, vmax);
    }
}


//功能 : 計算船隻在轉向的時候應該使用的速度(考慮加速度).
SLONG   ComputeShipWerveVelocity(SLONG v, SLONG vmax, SLONG acc)
{
    return  min(v+acc, vmax);
}


//功能 : 計算船隻的轉彎半徑.
double  ComputeShipWerveRadius(SLONG v, SLONG veer)
{
    /*
    計算船隻能夠轉彎的最小半徑:
    設轉向中每步行走距離為 s, 本步和下步之間的轉角為 t, 則轉彎半徑為:
    R = s / 2 / sin(t/2) = s * csc(t/2) / 2.
    */
    double  r;
    r = v / ( 2 * sin(veer * PI / 18000 / 2) );
    return  r;
}


//功能 : 計算船隻當前需要轉動的角度.
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


//功能 : 判斷船隻是否可以到達目標點.
SLONG   IsShipCanSailTo(SLONG x, SLONG y, SLONG dir_degree, SLONG v, SLONG veer, SLONG dest_x, SLONG dest_y)
{
    //不可到達區域: 
    //以船隻當前方向為中心軸, 船隻兩側與該軸相切, 半徑為船隻最小轉彎半徑的圓.
    /*
    船隻行走中的轉向處理:
    設轉向中每步行走距離為 s, 本步和下步之間的轉角為 t, 則轉彎半徑為:
    R = s / 2 / sin(t/2) = s * csc(t/2) / 2.
    */
    double  r, sita, a1, a2;
    double  x1, y1, x2, y2;
    double  dx, dy, dist1, dist2;

    //計算船隻能夠轉彎的最小半徑。
    sita = veer * PI / 18000 / 2;
    r = v / ( 2 * sin(sita) );

    //計算與當前方向相垂直的，兩側的，不能到達的，圓形區域的圓心座標。
    a1 = (dir_degree + 9000) * PI / 18000;
    a2 = (dir_degree - 9000) * PI / 18000;
    x1 = x + r * cos(a1);
    y1 = y + r * sin(a1);
    x2 = x + r * cos(a2);
    y2 = y + r * sin(a2);

    //判斷目標點是否位於不能到達區域。
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

//PS: 只支持 float 在有限範圍內的值.
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


