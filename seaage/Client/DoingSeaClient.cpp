/*
    2002-11-25
    海洋NPC在聯機的時候的處理
 */
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "ClientMain.h"
#include "SeaNpc.h"
#include "DoingSeaClient.h"
#include "Weather.h"
//-----
//  在聯機的時候,對海上npc待機的處理
//-----
SLONG   client_do_sea_npc_idle( SLONG npc_no )
{
    SLONG       new_action, new_id;
    SLONG       is_fight, file_index, id;

    LOCK_CHARACTER(npc_no);//先鎖定NPC
	file_index = GetCharacterFileIndex(npc_no);
	id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);  //取得NPC的上圖狀態
    new_action = GetOnSeaIdleAction(is_fight);
    new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
    if(id != new_id)
    {
        SetCharacterIdleTicks(npc_no, 150 + system_rand()%100);
		SetCharacterImageID(npc_no, new_id);
        DirHeadSeaCharacterFrame(npc_no, -1);
    }
    else
    {
        DirFastLoopSeaCharacterFrame(npc_no);
    }
	UNLOCK_CHARACTER(npc_no);//解鎖
    //
    return ACTION_RETURN_PROC;	
}
//-----
//
//-----
SLONG   client_do_sea_npc_sail_to(SLONG npc_no)
{
    enum 
    {   DOING_STEP_MOVE_TO  =   0,
       DOING_STEP_ARRIVE   =   1,
       DOING_STEP_STOP     =   2,
    };
    SLONG   degree_dir;
    SLONG   map_no, doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action;
    SLONG   dir, id,new_dir;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   track_id;
    SLONG   is_fight, foot_state, is_defence;
    //和船航行相關的數據
    SLONG   old_dir;
    FLOAT   Ax;				    //船的x軸上的加速度
    FLOAT   Ay;				    //船的y軸上的加速度
    FLOAT   Speedx;			    //船在x軸上的速度(就是船在x軸上,單位時間的位移)
    FLOAT   Speedy;			    //船在y軸上的速度(就是船在x軸上,單位時間的位移)
    FLOAT   BoatWinUseRate;		//船對風的使用率(和船的速度有關係) (節數)
    FLOAT   BoatWeight;			//船的重量(和船的阻力有關係)       ()
    SLONG   Rotate;				//船的旋轉角度(船的轉角)           ()
    FLOAT   BoatBaseSpeed;		//船的基本速度                     ()
    FLOAT   SpeedAddLeftx;	    //用餘保存速度計算後的餘數 x
    FLOAT   SpeedAddLefty;	    //用餘保存速度計算後的餘數 y
    FLOAT   BoatDir[3];		    //船的方向
    FLOAT   BoatForce[3];       //船受到的推力
    FLOAT   resist[3];          //船受到的阻力
    SLONG   lspeedx,lspeedy;
    SLONG   wind_dir;
    SLONG   wind_force;
    float   base_speed_x,base_speed_y;
    float   t_speed_x,t_speed_y;
    float   cosq;
    float   tag[3];
    float   temp[3];
    FLOAT   speed_ver[3];
    FLOAT   mod;
    SLONG   result;

    //先取得npc的數據
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    map_no = 0;
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_defence = IsCharacterOnDefenceState(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);
    //
    new_action = GetOnSeaMoveAction(is_fight);
    new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
    //
    if(id != new_id)	//改變npc的圖檔案
    {
		SetCharacterImageID(npc_no, new_id);
        DirHeadSeaCharacterFrame(npc_no, -1);
    }
    Speedx          =   (FLOAT)(GetCharacterShipSpeedX(npc_no)*1.0 / BOAT_SPEED_ACCURACY);
    Speedy          =   (FLOAT)(GetCharacterShipSpeedY(npc_no)*1.0 / BOAT_SPEED_ACCURACY);
    BoatWinUseRate  =   (FLOAT)GetCharacterShipSailSize(npc_no);	//船對風的使用率(和船的速度有關係) (節數)
    BoatWeight      =   (FLOAT)GetCharacterShipWeight(npc_no);	//船的重量(和船的阻力有關係)
    Rotate          =   GetCharacterShipTurn(npc_no);		//船的旋轉角度(船的轉角)
    BoatBaseSpeed   =   (FLOAT)move_speed;		//船的基本速度
    degree_dir = GetCharacterShipDegreeDir(npc_no);
    ShipDegreeDirToVector(degree_dir,BoatDir);
    old_dir = GetCharacterShipOldDegreeDir(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
    track_id = GetSeaCharacterFileTrackID( file_index );
    //
	get_zone_weather_wind_for_boat( &wind_dir, &wind_force);
    //
    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO://移動到目標地點的過程
        //加速過程
        //正常根據風力的行駛
        //--AI處理,,處理船的轉向..是否PARK等標誌
        tag[0] = (FLOAT)( dest_x - x );
        tag[1] = (FLOAT)( dest_y - y );
        tag[2] = 0.0f;
        VectorNormal( tag );
        cosq = VectorDotProduct( tag,BoatDir );
        if( cosq < cos(Rotate * PI * 2 / MAX_BOAT_DIR) )
        {
            VectorCrossProduct( tag,BoatDir,temp );
			if( temp[2] < 0 )
				degree_dir += Rotate;
			else
				degree_dir -= Rotate;
			if( degree_dir >= MAX_BOAT_DIR )
			{
				degree_dir = degree_dir % MAX_BOAT_DIR;
			}
			if( degree_dir < 0 )
			{
				degree_dir = (degree_dir + MAX_BOAT_DIR * 100) % MAX_BOAT_DIR;
			}
            ShipDegreeDirToVector(degree_dir,BoatDir);
        }
        else
        {
            BoatDir[0] = tag[0];
            BoatDir[1] = tag[1];
            BoatDir[2] = tag[2];
        }
        //如果速度的方向和船的方向的點極
        speed_ver[0] = Speedx;
        speed_ver[1] = Speedy;
        speed_ver[2] = 0.0f;
        if( VectorDotProduct(speed_ver, BoatDir ) > 0 )
        {
            mod =(FLOAT)(  sqrt(Speedx*Speedx+Speedy*Speedy) );
            Speedx = BoatDir[0] * mod;
            Speedy = BoatDir[1] * mod;
        }
        //
        //..船的正常移動過程
        // 1 根據風力計算船的加速度
        ShipWindDirToForceVector( degree_dir,wind_dir,BoatForce );
        BoatForce[0] = BoatForce[0] * BoatWinUseRate * wind_force / 100;
        BoatForce[1] = BoatForce[1] * BoatWinUseRate * wind_force / 100;

        // 2 根據速度,重量計算船的阻力
        ComputeSeaCharacterSailResistance(BoatWeight,Speedx,Speedy,BoatDir,resist);

        // 3 取得船現在真正的加速度
        Ax = BoatForce[0]+resist[0];
        Ay = BoatForce[1]+resist[1];

        // 4 更具原來的速度,加速度,基本速度計算船的真正速度,上次移動剩下的浮點速度
        Speedx += Ax;
        Speedy += Ay;
		Speedx = FloatToPrecision10Float(Speedx);
		Speedy = FloatToPrecision10Float(Speedy);
        //
        //
        // 計算船的基本速度
        base_speed_x = (BoatDir[0] * BoatBaseSpeed);
        base_speed_y = (BoatDir[1] * BoatBaseSpeed);
        t_speed_x = (Speedx+base_speed_x );
        t_speed_y = (Speedy+base_speed_y );
        //
        lspeedx = (SLONG)(t_speed_x);
        lspeedy = (SLONG)(t_speed_y);

        // 5 移動船到新的位置
        x += lspeedx;
        y += lspeedy;
        // 6 保留剩下的浮點餘數
        SpeedAddLeftx = t_speed_x-lspeedx;
        SpeedAddLefty = t_speed_y-lspeedy;
        //剩餘的速度需要保存起來
        Speedx += SpeedAddLeftx;
        Speedy += SpeedAddLefty;
        //減速停止的過程
        //
        new_dir = ApproachSeaCharacterDir( BoatDir );

        //將需要保留的新速據保留起來
        LOCK_CHARACTER(npc_no);
        //播放動畫
        if( old_dir == dir )
            DirFastLoopSeaCharacterFrame(npc_no);
        old_dir = dir;
        //改變npc的方向
        if( dir != new_dir)
        {
			SetCharacterDir(npc_no, new_dir);
            DirHeadSeaCharacterFrame(npc_no, new_dir);
        }
        UNLOCK_CHARACTER(npc_no);

        //判斷船的目標點是否阻檔
        LOCK_MAPMASK(map_no);
        result = IsPixelMaskStop(x, y);
        UNLOCK_MAPMASK(map_no);
        if( TRUE == result )
        {
            //碰倒阻檔速度變為0
            Speedx = (-1* Speedx);
            Speedy = (-1* Speedy);
            //
            SpeedAddLeftx = 0.0f;
            SpeedAddLefty = 0.0f;
            //
            //碰到的是阻擋
            LOCK_CHARACTER(npc_no);
            // 2. 保留當前的速度
            SetCharacterShipSpeedX(npc_no,(SLONG)(Speedx*BOAT_SPEED_ACCURACY));
            SetCharacterShipSpeedY(npc_no,(SLONG)(Speedy*BOAT_SPEED_ACCURACY));
            //  4.設置新的船的方向
            SetCharacterShipDegreeDir(npc_no,degree_dir);
            SetCharacterShipOldDegreeDir(npc_no,old_dir);
            UNLOCK_CHARACTER(npc_no);

            //判斷目的地是否到達
            //如果船的方向是指向目標的...那就表示到達了.!!!
            if( ( tag[0] == BoatDir[0] ) &&
                ( tag[1] == BoatDir[1] )   )
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_STOP);
                UNLOCK_CHARACTER(npc_no);
            }
        }
        else
        {
            // 1. 保留當前的座標
            //
            LOCK_CHARACTER(npc_no);
			SetCharacterPosition(npc_no, x, y, z);
            SetCharacterShipSpeedX(npc_no,(SLONG)(Speedx*BOAT_SPEED_ACCURACY));
            SetCharacterShipSpeedY(npc_no,(SLONG)(Speedy*BOAT_SPEED_ACCURACY));
            SetCharacterShipDegreeDir(npc_no,degree_dir);
            SetCharacterShipOldDegreeDir(npc_no,old_dir);
            UNLOCK_CHARACTER(npc_no);

            //判斷是否到達目標地點
            //如果船的方向是指向目標的...那就表示到達了.!!!
            if( ( tag[0] == BoatDir[0] ) &&
                ( tag[1] == BoatDir[1] )   )
            {
                if(( abs( x - dest_x) <= abs(lspeedx)+1 ) &&
                   ( abs( y - dest_y) <= abs(lspeedy)+1 )   )
                {
                    LOCK_CHARACTER(npc_no);
					SetCharacterDoingStep(npc_no, DOING_STEP_ARRIVE);
                    UNLOCK_CHARACTER(npc_no);
                }
            }
        }
        add_sea_npc_track(track_id,x,y,new_dir,0);
        break;

    case DOING_STEP_ARRIVE:
        LOCK_CHARACTER(npc_no);
		SetCharacterPosition(npc_no, x, y, z);
        DirFastLoopSeaCharacterFrame(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        break;
    case DOING_STEP_STOP:
        LOCK_CHARACTER(npc_no);
        DirFastLoopSeaCharacterFrame(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        break;
    }
    return ACTION_RETURN_PROC;    
}
//-----
//
//-----
SLONG   client_do_sea_npc_walk_to(SLONG npc_no)
{
    //
    static  FLOAT   s_rotate=(FLOAT)(PI/16);
    //
    enum 
    {   DOING_STEP_MOVE_TO  =   0,
    };
    //
    SLONG   map_no, doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action;
    SLONG   dir, id,new_dir;
    SLONG   track_id;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   ret;
    SLONG   is_fight, foot_state, is_defence;
    //
    SLONG   degree_dir;
    FLOAT   BoatDir[3];
    FLOAT   tag[3],temp[3];
    FLOAT   cosq;
    //
    SLONG   Rotate;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    map_no = 0;
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_defence = IsCharacterOnDefenceState(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);
    degree_dir = GetCharacterShipDegreeDir(npc_no);
    Rotate = GetCharacterShipTurn(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
    ShipDegreeDirToVector( degree_dir,BoatDir );
    //
    track_id = GetSeaCharacterFileTrackID( file_index );
    //

    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
                {
                    //NPCde 轉身的過程
                    tag[0] = (FLOAT)( dest_x - x );
                    tag[1] = (FLOAT)( dest_y - y );
                    tag[2] = 0.0f;
                    VectorNormal( tag );
                    cosq = VectorDotProduct( tag, BoatDir);
                    if( cosq < cos(s_rotate) )
                    {
                        VectorCrossProduct( tag,BoatDir,temp );
                        if( temp[2] < 0 )
                            degree_dir = ( degree_dir + Rotate ) % MAX_BOAT_DIR;
                        else
					        degree_dir = (degree_dir + MAX_BOAT_DIR * 100) % MAX_BOAT_DIR;
                        //
                        ShipDegreeDirToVector( degree_dir,BoatDir );
                    }
                    else
                    {
                        tag[0] = BoatDir[0];
                        tag[1] = BoatDir[1];
                        tag[2] = BoatDir[2];
                    }
                    //轉身的過程
                    new_dir = ApproachSeaCharacterDir( BoatDir );
                    new_action = GetOnSeaMoveAction(is_fight);
                    new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
                    //
                    LOCK_CHARACTER(npc_no);
					SetCharacterDir(npc_no, new_dir);
					SetCharacterImageID(npc_no, new_id);
                    if( new_dir != dir )
                        DirHeadSeaCharacterFrame(npc_no,new_dir);
                    if( ( BoatDir[0] == tag[0] ) && 
                        ( BoatDir[1] == tag[1] )   )
                    {
						SetCharacterPosition(npc_no, x, y, z);
                        DirFastLoopSeaCharacterFrame(npc_no);
                    }
                    SetCharacterShipDegreeDir(npc_no,degree_dir);	//船的方向
                    UNLOCK_CHARACTER(npc_no);
                }
				break;
            case STEP_ARRIVE:
                LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
                break;
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                LOCK_CHARACTER(npc_no);
				SetCharacterDestPosition(npc_no, x, y, 0);
                DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
                break;
            }
            break;
        }
    }
    add_sea_npc_track(track_id,x,y,dir,0);
    //
    return ACTION_RETURN_PROC;
}
//------------------------------------------------------------------------------------------------------------
//      .End
//------------------------------------------------------------------------------------------------------------

