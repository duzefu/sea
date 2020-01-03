/*
**	NetGE_Misc.cpp 
**	misc functions.
**
**	Jack, 2003.1.7
*/
#include "NetGE_MainFunc.h"


//
FLOAT   g_boat_dir_vector[MAX_BOAT_DIR][2]; //對所有的船的方向..的單位失量的定義
FLOAT   g_wind_dir_vector[MAX_WIND_DIR][2]; //對所有的風的方向..的單位失量的定義
//
FLOAT   g_boat_wind_force[MAX_BOAT_DIR][MAX_WIND_DIR][2];//根據預先定義的船的方向,和風的方向計算出船的受力
//
FLOAT   g_32dir_vector[32][3];      //保存於先計算好的...32方向的失量
FLOAT   g_32dir_rotation[32][3];      //保存於先計算好的...32方向的旋轉的
//------------------------------------------------------------------------------------------------------
void    InitShipMath(void);
//------------------------------------------------------------------------------------------------------
//  初始化船的數學公式
//------------------------------------------------------------------------------------------------------
void    ShipDegreeDirToVector(SLONG degree_dir, FLOAT dir[3])
{
    dir[0] = g_boat_dir_vector[degree_dir][0];
    dir[1] = g_boat_dir_vector[degree_dir][1];
    dir[2] = 0.0f;
}


void    WindDirToVector(SLONG wind_dir,FLOAT dir[3])
{
    dir[0] = g_wind_dir_vector[wind_dir][0];
    dir[1] = g_wind_dir_vector[wind_dir][1];
    dir[2] = 0.0f;
}


void    ShipWindDirToForceVector(SLONG boat_dir,SLONG wind_dir,FLOAT dir[3] )
{
    dir[0] = g_boat_wind_force[boat_dir][wind_dir][0];
    dir[1] = g_boat_wind_force[boat_dir][wind_dir][1];
    dir[2] = 0.0f;
}


void    ComputeSeaCharacterSailResistance(float boat_weight,float speedx,float speedy,float boat_dir[3],float resist[3])
{
    float	weight[3];

    //船受到的阻力和船的速度成正比
    //根据x,  y軸上的速度計算船的真正速度
    //
    weight[0] = boat_dir[0] * boat_weight;
    weight[1] = boat_dir[1] * boat_weight;
    weight[2] = 0.0f;
    //
    resist[0] = (float)(-1.0 * (BOAT_SPEED_RESISTANCE_RATE * speedx + weight[0]) );
    resist[1] = (float)(-1.0 * (BOAT_SPEED_RESISTANCE_RATE * speedy + weight[1]) );
    resist[2] = 0.0f;    
    
}


//---
//  計算船受到的推力
//  [in]    wind[3] 向量包含船的方向和受到的風力
//  [in]    boat_dir[3] 向量船的運行方向
//  [in]    wind_use_rate   對風的利用率
//  [out]   boat_force[3]   船受到的推力和方向
//  [out]   sail_dir[3]     船的航行的方向
//---
void    ComputeSeaCharacterSailForce(float wind[3],float boat_dir[3],float wind_use_rate,float boat_force[3],float sail_dir[3]) 
{
    float   ab[3],ae[3];
    float   cb[3],ce[3];
    float   use1[3],use2[3];
    float   sail_force[3],sail_force_dir[3];
    float   sf[3],sf1[3],sf2[3];
    float   bf[3],bf1[3],bf2[3];
    float   alf;

    //可用的帆的位置必須是符合以下條件:
    //a 為船的方向
    //b 為帆的方向
    //c 為風的方向
    //則 b 必須符合條件  a.b < 0  &&  b.c < 0

    //先計算出 和 a 的點積為負數的矢量的範圍
    VectorZCross(boat_dir, ab, ae);

    //再計算出 和 c 的點積為負數的矢量的範圍
    VectorZCross(wind, cb, ce);

    //判斷 a c 的點積
    if( VectorDotProduct(ab, wind) <= 0 )
    {
        use1[0] = ab[0];
        use1[1] = ab[1];
        use1[2] = ab[2];
    }
    else
    {
        use1[0] = ae[0];
        use1[1] = ae[1];
        use1[2] = ae[2];
    }

    //        
    if( VectorDotProduct(cb,boat_dir) <= 0 )
    {
        use2[0] = cb[0];
        use2[1] = cb[1];
        use2[2] = cb[2];
    }
    else
    {
        use2[0] = ce[0];
        use2[1] = ce[1];
        use2[2] = ce[2];
    }
    //
    VectorNormal(use1);
    VectorNormal(use2);
    //
    VectorAdd( use1,use2,sail_force_dir );
    //
    //if( m_BoatRoateFlag && use_rotate)
    //{
        //如果船正在旋轉
        //sail_force_dir[0]  = use2[0];
        //sail_force_dir[1]  = use2[1];
        //sail_force_dir[2]  = use2[2];
    //}
    //
    VectorNormal(sail_force_dir);
	//
	//中間過程保存需要的船帆的方向
    sail_dir[0] = sail_force_dir[0];
    sail_dir[1] = sail_force_dir[1];
    sail_dir[2] = sail_force_dir[2];        
    //
    sail_force_dir[0] = -1.0f * sail_force_dir[0];
    sail_force_dir[1] = -1.0f * sail_force_dir[1];
    sail_force_dir[2] = -1.0f * sail_force_dir[2];
	//
    //和 sail_force_dir 點積為0的量
    VectorZCross(sail_force_dir, sf1, sf2);
    //
    if( VectorDotProduct(sf1,wind) >= 0 )
    {
        sf[0] = sf1[0];
        sf[1] = sf1[1];
        sf[2] = sf1[2];                
    }        
    else
    {
        sf[0] = sf2[0];
        sf[1] = sf2[1];
        sf[2] = sf2[2];  
    }        
    //
    VectorNormal(sf);

    //根据 sf, sail_force_dir,  wind 計算帆受風的影響力
    alf = VectorDotProduct(wind,sail_force_dir);

    //對風的使用率
    alf = alf * wind_use_rate / 100;
    sail_force[0] = sail_force_dir[0] * alf;
    sail_force[1] = sail_force_dir[1] * alf;
    sail_force[2] = sail_force_dir[2] * alf;

    //用船的方向計算出點積為0的量
    VectorZCross(boat_dir,bf1,bf2);
    if( VectorDotProduct(bf1,sail_force) >= 0 )
    {
        bf[0] = bf1[0];
        bf[1] = bf1[1];
        bf[2] = bf1[2];                
    }
    else
    {
        bf[0] = bf2[0];
        bf[1] = bf2[1];
        bf[2] = bf2[2];                
    }

    //
    //根据 sail_force, bf, boat_dir 計算船的受風的推力
    alf  = VectorDotProduct(sail_force,boat_dir);    
    boat_force[0] = boat_dir[0] * alf;
    boat_force[1] = boat_dir[1] * alf;
    boat_force[2] = boat_dir[2] * alf;
}


void    InitShipMath(void)
{
    SLONG   i,j;
    FLOAT   wind[3],BoatDir[3],BoatForce[3],SailDir[3];

    //對所有的船的方向..的單位失量的定義
    for( i=0;i<MAX_BOAT_DIR;i++ )
    {
        g_boat_dir_vector[i][0] = (FLOAT)cos(PI*2*i/MAX_BOAT_DIR);
        g_boat_dir_vector[i][1] = (FLOAT)sin(PI*2*i/MAX_BOAT_DIR);
    }
    //對所有的風的方向..的單位失量的定義
    for( i=0;i<MAX_WIND_DIR;i++ )
    {
        g_wind_dir_vector[i][0] = (FLOAT)cos(PI*2*i/MAX_WIND_DIR);
        g_wind_dir_vector[i][1] = (FLOAT)sin(PI*2*i/MAX_WIND_DIR);
    }
    //根據預先定義的船的方向,和風的方向計算出船的受力
    for( i=0;i<MAX_BOAT_DIR;i++ )
	{
        for( j=0;j<MAX_WIND_DIR;j++ )
        {
            wind[0] = g_wind_dir_vector[j][0];
            wind[1] = g_wind_dir_vector[j][1];
            wind[2] = 0.0f;
            //
            BoatDir[0] = g_boat_dir_vector[i][0];
            BoatDir[1] = g_boat_dir_vector[i][1];
            BoatDir[2] = 0.0f;
            //
            // 1 根據風力計算船的加速度
            ComputeSeaCharacterSailForce(wind,BoatDir,100,BoatForce,SailDir);
            //
            g_boat_wind_force[i][j][0] = BoatForce[0];
            g_boat_wind_force[i][j][1] = BoatForce[1];
        }
	}
}

void	DebugLogShipMath(void)
{
#ifdef	_DEBUG
	SLONG	i, j;

	log_error(1, ";g_boat_dir_vector");
	for(i=0; i<MAX_BOAT_DIR; i++)
	{
		log_error(1, "[%d]::[0]%f, [1]%f", i, g_boat_dir_vector[i][0], g_boat_dir_vector[i][1]);
	}
	log_error(1, "");

	log_error(1, ";g_wind_dir_vector");
	for(i=0; i<MAX_WIND_DIR; i++)
	{
		log_error(1, "[%d]::[0]%f, [1]%f", i, g_boat_dir_vector[i][0], g_boat_dir_vector[i][1]);
	}
	log_error(1, "");


	log_error(1, ";g_boat_wind_force");
	for(i=0; i<MAX_BOAT_DIR; i++)
	{
		for(j=0; j<MAX_WIND_DIR; j++)
		{
			log_error(1, "[%d][%d]::[0]%f, [1]%f", i, j, g_boat_wind_force[i][j][0], g_boat_wind_force[i][j][1]);
		}
	}
	log_error(1, "");
#endif//_DEBUG
}



//矢量相減
void    VectorSub(float in1[3] , float in2[3] , float out[3] )
{
	out[0] = in1[0] - in2[0] ;
	out[1] = in1[1] - in2[1] ;
	out[2] = in1[2] - in2[2] ;
}

//矢量相加
void    VectorAdd(float in1[3] , float in2[3] , float out[3] )
{
	out[0] = in1[0] + in2[0] ;
	out[1] = in1[1] + in2[1] ;
	out[2] = in1[2] + in2[2] ;
}

//計算矢量點積
float   VectorDotProduct(float in1[3] , float in2[3] )
{
	return ( in1[0] * in2[0] + in1[1] * in2[1] + in1[2] * in2[2] );
}

//計算矢量叉積
void    VectorCrossProduct(float in1[3],float in2[3],float out[3])
{
	out[0] = in1[1] * in2[2] - in1[2] * in2[1] ;
	out[1] = in1[2] * in2[0] - in1[0] * in2[2] ;
	out[2] = in1[0] * in2[1] - in1[1] * in2[0] ;
}

//計算矢量的模
float   VectorAbsolute( float in1[3]  )
{
	return( float ( sqrt( in1[0] * in1[0] + in1[1] * in1[1] + in1[2] * in1[2] ) ) );
}

//矢量歸一化
float   VectorNormal( float normal[3] )
{
    double	length;
    //
    length = sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);
    if( 0.0 == length )
    {
		normal[0] = 0.0f;
		normal[1] = 0.0f;
		normal[2] = 0.0f;
    }
    else
    {
		normal[0] = (float)(normal[0]/length);
		normal[1] = (float)(normal[1]/length);
		normal[2] = (float)(normal[2]/length);
    }
	return (float )length;
}

//建立單位矩陣
void    CreateUnitMatrix( float out[4][4] )
{
	out[0][0] = 1, out[0][1] = 0, out[0][2] = 0, out[0][3] = 0;
	out[1][0] = 0, out[1][1] = 1, out[1][2] = 0, out[1][3] = 0;
	out[2][0] = 0, out[2][1] = 0, out[2][2] = 1, out[2][3] = 0;
	out[3][0] = 0, out[3][1] = 0, out[3][2] = 0, out[3][3] = 1;
}

//建立零矩陣
void    CreateZeroMatrix( float out[4][4] )
{
    out[0][0] = 0, out[0][1] = 0, out[0][2] = 0, out[0][3] = 0;
    out[1][0] = 0, out[1][1] = 0, out[1][2] = 0, out[1][3] = 0;
    out[2][0] = 0, out[2][1] = 0, out[2][2] = 0, out[2][3] = 0;
    out[3][0] = 0, out[3][1] = 0, out[3][2] = 0, out[3][3] = 0;
}


//求一個向量的...和Z軸一起構成...的面的叉積
void    VectorZCross(float in[3],float out1[3],float out2[3] )
{
    float temp[3];

    temp[0] = 0.0f;
    temp[1] = 0.0f;
    temp[2] = 1.0f;
    VectorCrossProduct(in, temp, out1);
    //
    temp[2] = -1.0f;
    VectorCrossProduct(in, temp, out2);
}


//定點繞Z軸旋轉
void	Vertex3DRoateZ(FLOAT in[3],FLOAT out[3],FLOAT radians)
{
	out[0]=(FLOAT)(in[0]*cos(radians))-(FLOAT)(in[1]*sin(radians));
	out[1]=(FLOAT)(in[0]*sin(radians))+(FLOAT)(in[1]*cos(radians));
	out[2]=in[2];
}

//根據傳入的向量的方向..計算得出實際上需要的方向
//方向順序是從12點開始的順時針方向
SLONG   Vertex2Dir8(SLONG  in_of_pos[3])
{
    float   dir[3];
    const   SLONG   dir_num = 8;
    static  float   sin_val[8] = 
    {
        (float)sin( PI /8*1),
        (float)sin( PI /8*3),
        (float)sin( PI /8*5),
        (float)sin( PI /8*7),
        (float)sin( PI /8*1*-1),
        (float)sin( PI /8*3*-1),
        (float)sin( PI /8*5*-1),
        (float)sin( PI /8*7*-1),        
    };
    //
    dir[0] = (float)in_of_pos[0];
    dir[1] = (float)in_of_pos[1];
    dir[2] = (float)in_of_pos[2];        
    dir[1] = -1 * dir[1];    
    VectorNormal(dir);
    //
    if( dir[0] >= 0  )
    {
        //      |*******
        //      |*******
        //      |*******
        //------------------
        //      |+++++++
        //      |+++++++
        //      |+++++++
        //帶 * + 的區域
        if (dir[1]>sin_val[1])
        {
            return 0;
        }
        else if (dir[1]>sin_val[0])
        {
            return 1;
        }
        else if (dir[1]>sin_val[dir_num/2])
        {
            return 2;        
        }
        else if(dir[1]>sin_val[dir_num/2+1])
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }
    else
    {
        //*******|
        //*******|
        //*******|
        //-------------------
        //+++++++|
        //+++++++|
        //+++++++|
        //帶 * + 的區域
        if (dir[1]>sin_val[2])
        {
            return 0;
        }
        else if (dir[1]>sin_val[3])
        {
            return 7;
        }
        else if (dir[1]>sin_val[dir_num-1])
        {
            return 6;        
        }
        else if(dir[1]>sin_val[dir_num-2])
        {
            return 5;
        }
        else
        {
            return 4;
        }        
    }
    return 0;
}
//根據傳入的向量的方向..計算得出實際上需要的方向
//方向順序是從12點開始的順時針方向
SLONG   Vertex2Dir16(SLONG  in_of_pos[3])
{
    float   dir[3];
    const   SLONG   dir_num = 16;
    static  float   sin_val[16] = 
    {
        (float)sin( PI /16*1),
        (float)sin( PI /16*3),
        (float)sin( PI /16*5),
        (float)sin( PI /16*7),
        (float)sin( PI /16*9),
        (float)sin( PI /16*11),
        (float)sin( PI /16*13),
        (float)sin( PI /16*15),
        //
        (float)sin( PI /16*1*-1),
        (float)sin( PI /16*3*-1),
        (float)sin( PI /16*5*-1),
        (float)sin( PI /16*7*-1),
        (float)sin( PI /16*9*-1),
        (float)sin( PI /16*11*-1),
        (float)sin( PI /16*13*-1),
        (float)sin( PI /16*15*-1),        
    };
    //
    dir[0] = (float)in_of_pos[0];
    dir[1] = (float)in_of_pos[1];
    dir[2] = (float)in_of_pos[2];        
    dir[1] = -1 * dir[1];    
    VectorNormal(dir);
    //    
    if( dir[0] >= 0  )
    {
        //      |*******
        //      |*******
        //      |*******
        //------------------
        //      |+++++++
        //      |+++++++
        //      |+++++++
        //帶 * + 的區域
        if(dir[1]>sin_val[3])
            return 0;
        else if (dir[1]>sin_val[2])
            return 1;        
        else if (dir[1]>sin_val[1])
            return 2;        
        else if (dir[1]>sin_val[0])
            return 3;        
        else if (dir[1]>sin_val[dir_num/2])
            return 4;        
        else if(dir[1]>sin_val[dir_num/2+1])
            return 5;        
        else if(dir[1]>sin_val[dir_num/2+2])
            return 6;        
        else if(dir[1]>sin_val[dir_num/2+3])
            return 7;
        else
            return 8;
    }
    else
    {
        //*******|
        //*******|
        //*******|
        //-------------------
        //+++++++|
        //+++++++|
        //+++++++|
        //帶 * + 的區域
        if(dir[1]>sin_val[4])
            return 0;
        else if (dir[1]>sin_val[5])
            return 15;        
        else if (dir[1]>sin_val[6])
            return 14;        
        else if (dir[1]>sin_val[7])
            return 13;        
        else if (dir[1]>sin_val[dir_num-1])
            return 12;        
        else if(dir[1]>sin_val[dir_num-2])
            return 11;        
        else if(dir[1]>sin_val[dir_num-3])
            return 10;        
        else if(dir[1]>sin_val[dir_num-4])        
            return 9;        
        else
            return 8;                
    }
    //
    return 0;
}
//根據傳入的向量的方向..計算得出實際上需要的方向
//方向順序是從12點開始的順時針方向
SLONG   Vertex2Dir32(SLONG  in_of_pos[3])
{
    float   dir[3];
    const   SLONG   dir_num = 32;
    static  float   sin_val[32] = 
    {
        (float)sin( PI /32*1),
        (float)sin( PI /32*3),
        (float)sin( PI /32*5),
        (float)sin( PI /32*7),
        (float)sin( PI /32*9),
        (float)sin( PI /32*11),
        (float)sin( PI /32*13),
        (float)sin( PI /32*15),
        (float)sin( PI /32*17),
        (float)sin( PI /32*19),
        (float)sin( PI /32*21),
        (float)sin( PI /32*23),
        (float)sin( PI /32*25),
        (float)sin( PI /32*27),
        (float)sin( PI /32*29),
        (float)sin( PI /32*31),
        //
        (float)sin( PI /32*1*-1),
        (float)sin( PI /32*3*-1),
        (float)sin( PI /32*5*-1),
        (float)sin( PI /32*7*-1),
        (float)sin( PI /32*9*-1),
        (float)sin( PI /32*11*-1),
        (float)sin( PI /32*13*-1),
        (float)sin( PI /32*15*-1),
        (float)sin( PI /32*17*-1),
        (float)sin( PI /32*19*-1),
        (float)sin( PI /32*21*-1),
        (float)sin( PI /32*23*-1),
        (float)sin( PI /32*25*-1),
        (float)sin( PI /32*27*-1),
        (float)sin( PI /32*29*-1),
        (float)sin( PI /32*31*-1),        
    };
    //
    dir[0] = (float)in_of_pos[0];
    dir[1] = (float)in_of_pos[1];
    dir[2] = (float)in_of_pos[2];
    VectorNormal(dir);
    //
    if( dir[0] >= 0  )
    {
        //      |*******
        //      |*******
        //      |*******
        //------------------
        //      |+++++++
        //      |+++++++
        //      |+++++++
        //帶 * + 的區域
        if(dir[1]>sin_val[7])
            return 0;
        else if(dir[1]>sin_val[6])
            return 1;
        else if(dir[1]>sin_val[5])
            return 2;
        else if(dir[1]>sin_val[4])
            return 3;
        else if(dir[1]>sin_val[3])
            return 4;
        else if (dir[1]>sin_val[2])    
            return 5;
        else if (dir[1]>sin_val[1])
            return 6;
        else if (dir[1]>sin_val[0])
            return 7;
        else if (dir[1]>sin_val[dir_num/2])
            return 8;
        else if(dir[1]>sin_val[dir_num/2+1])
            return 9;
        else if(dir[1]>sin_val[dir_num/2+2])
            return 10;
        else if(dir[1]>sin_val[dir_num/2+3])
            return 11;
        else if(dir[1]>sin_val[dir_num/2+4])
            return 12;
        else if(dir[1]>sin_val[dir_num/2+5])
            return 13;
        else if(dir[1]>sin_val[dir_num/2+6])
            return 14;
        else if(dir[1]>sin_val[dir_num/2+7])
            return 15;
        else
            return 16;
    }
    else
    {
        //*******|
        //*******|
        //*******|
        //-------------------
        //+++++++|
        //+++++++|
        //+++++++|
        //帶 * + 的區域
        if(dir[1]>sin_val[8])
            return 0;
        else if (dir[1]>sin_val[9])    
            return 31;
        else if (dir[1]>sin_val[10])    
            return 30;
        else if (dir[1]>sin_val[11])    
            return 29;
        else if (dir[1]>sin_val[12])                            
            return 28;
        else if (dir[1]>sin_val[13])
            return 27;
        else if (dir[1]>sin_val[14])
            return 26;
        else if (dir[1]>sin_val[15])
            return 25;
        else if (dir[1]>sin_val[dir_num-1])
            return 24;
        else if(dir[1]>sin_val[dir_num-2])
            return 23;
        else if(dir[1]>sin_val[dir_num-3])
            return 22;
        else if(dir[1]>sin_val[dir_num-4])
            return 21;
        else if(dir[1]>sin_val[dir_num-5])
            return 20;
        else if(dir[1]>sin_val[dir_num-6])
            return 19;
        else if(dir[1]>sin_val[dir_num-7])
            return 18;
        else if(dir[1]>sin_val[dir_num-8])        
            return 17;
        else
            return 16;
    }
    //
    return 0;

}
//----
//  不同方向標準之間的轉換
//----
SLONG   DirChange(SLONG lScDir, SLONG lScDirMax, SLONG lTagDirMax)
{
    //
    return lTagDirMax * lScDir / lScDirMax;
}
//---
//  初開始化
//---
void    IniMiscMath(void)
{
    SLONG   i;
    //32方向的旋轉
    for (i=0; i<32; i++)    
    {
        g_32dir_rotation[i][0] = (float)cos(PI / 16 * i * -1);
        g_32dir_rotation[i][1] = (float)sin(PI / 16 * i * -1);
        g_32dir_rotation[i][2] = 0.0f;
    }
    //32方向的失量
    for (i=0; i<32; i++)
    {
        g_32dir_vector[i][0] = (float)cos(PI / 2 - PI / 16 * i);
        g_32dir_vector[i][1] = (float)sin(PI / 2 - PI / 16 * i);
        g_32dir_vector[i][2] = 0.0f;
    }
    //船只計算數據
    InitShipMath();
    //
    
}
//---
//  次方運算
//---
SLONG	Involution(SLONG x, SLONG y)
{
	int		i;	
	SLONG	ret_value;

	ret_value = x;

	if(y == 0)return 1;
	if(y == 1)return ret_value;
	
	for(i = 1; i < y; i++)
	{		
		ret_value = ret_value * x;
	}

	return ret_value;
}
