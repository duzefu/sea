/*
    2002-11-25
    ���vNPC�b�p�����ɭԪ��B�z
 */
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "ClientMain.h"
#include "SeaNpc.h"
#include "DoingSeaClient.h"
#include "Weather.h"
//-----
//  �b�p�����ɭ�,����Wnpc�ݾ����B�z
//-----
SLONG   client_do_sea_npc_idle( SLONG npc_no )
{
    SLONG       new_action, new_id;
    SLONG       is_fight, file_index, id;

    LOCK_CHARACTER(npc_no);//����wNPC
	file_index = GetCharacterFileIndex(npc_no);
	id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);  //���oNPC���W�Ϫ��A
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
	UNLOCK_CHARACTER(npc_no);//����
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
    //�M����������ƾ�
    SLONG   old_dir;
    FLOAT   Ax;				    //�x�b�W���[�t��
    FLOAT   Ay;				    //�y�b�W���[�t��
    FLOAT   Speedx;			    //��bx�b�W���t��(�N�O��bx�b�W,���ɶ����첾)
    FLOAT   Speedy;			    //��by�b�W���t��(�N�O��bx�b�W,���ɶ����첾)
    FLOAT   BoatWinUseRate;		//��ﭷ���ϥβv(�M��t�צ����Y) (�`��)
    FLOAT   BoatWeight;			//����q(�M����O�����Y)       ()
    SLONG   Rotate;				//����ਤ��(��ਤ)           ()
    FLOAT   BoatBaseSpeed;		//��򥻳t��                     ()
    FLOAT   SpeedAddLeftx;	    //�ξl�O�s�t�׭p��᪺�l�� x
    FLOAT   SpeedAddLefty;	    //�ξl�O�s�t�׭p��᪺�l�� y
    FLOAT   BoatDir[3];		    //���V
    FLOAT   BoatForce[3];       //����쪺���O
    FLOAT   resist[3];          //����쪺���O
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

    //�����onpc���ƾ�
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
    if(id != new_id)	//����npc�����ɮ�
    {
		SetCharacterImageID(npc_no, new_id);
        DirHeadSeaCharacterFrame(npc_no, -1);
    }
    Speedx          =   (FLOAT)(GetCharacterShipSpeedX(npc_no)*1.0 / BOAT_SPEED_ACCURACY);
    Speedy          =   (FLOAT)(GetCharacterShipSpeedY(npc_no)*1.0 / BOAT_SPEED_ACCURACY);
    BoatWinUseRate  =   (FLOAT)GetCharacterShipSailSize(npc_no);	//��ﭷ���ϥβv(�M��t�צ����Y) (�`��)
    BoatWeight      =   (FLOAT)GetCharacterShipWeight(npc_no);	//����q(�M����O�����Y)
    Rotate          =   GetCharacterShipTurn(npc_no);		//����ਤ��(��ਤ)
    BoatBaseSpeed   =   (FLOAT)move_speed;		//��򥻳t��
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
    case DOING_STEP_MOVE_TO://���ʨ�ؼЦa�I���L�{
        //�[�t�L�{
        //���`�ھڭ��O����p
        //--AI�B�z,,�B�z���V..�O�_PARK���лx
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
        //�p�G�t�ת���V�M���V���I��
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
        //..����`���ʹL�{
        // 1 �ھڭ��O�p���[�t��
        ShipWindDirToForceVector( degree_dir,wind_dir,BoatForce );
        BoatForce[0] = BoatForce[0] * BoatWinUseRate * wind_force / 100;
        BoatForce[1] = BoatForce[1] * BoatWinUseRate * wind_force / 100;

        // 2 �ھڳt��,���q�p�����O
        ComputeSeaCharacterSailResistance(BoatWeight,Speedx,Speedy,BoatDir,resist);

        // 3 ���o��{�b�u�����[�t��
        Ax = BoatForce[0]+resist[0];
        Ay = BoatForce[1]+resist[1];

        // 4 ����Ӫ��t��,�[�t��,�򥻳t�׭p���u���t��,�W�����ʳѤU���B�I�t��
        Speedx += Ax;
        Speedy += Ay;
		Speedx = FloatToPrecision10Float(Speedx);
		Speedy = FloatToPrecision10Float(Speedy);
        //
        //
        // �p���򥻳t��
        base_speed_x = (BoatDir[0] * BoatBaseSpeed);
        base_speed_y = (BoatDir[1] * BoatBaseSpeed);
        t_speed_x = (Speedx+base_speed_x );
        t_speed_y = (Speedy+base_speed_y );
        //
        lspeedx = (SLONG)(t_speed_x);
        lspeedy = (SLONG)(t_speed_y);

        // 5 ���ʲ��s����m
        x += lspeedx;
        y += lspeedy;
        // 6 �O�d�ѤU���B�I�l��
        SpeedAddLeftx = t_speed_x-lspeedx;
        SpeedAddLefty = t_speed_y-lspeedy;
        //�Ѿl���t�׻ݭn�O�s�_��
        Speedx += SpeedAddLeftx;
        Speedy += SpeedAddLefty;
        //��t����L�{
        //
        new_dir = ApproachSeaCharacterDir( BoatDir );

        //�N�ݭn�O�d���s�t�ګO�d�_��
        LOCK_CHARACTER(npc_no);
        //����ʵe
        if( old_dir == dir )
            DirFastLoopSeaCharacterFrame(npc_no);
        old_dir = dir;
        //����npc����V
        if( dir != new_dir)
        {
			SetCharacterDir(npc_no, new_dir);
            DirHeadSeaCharacterFrame(npc_no, new_dir);
        }
        UNLOCK_CHARACTER(npc_no);

        //�P�_��ؼ��I�O�_����
        LOCK_MAPMASK(map_no);
        result = IsPixelMaskStop(x, y);
        UNLOCK_MAPMASK(map_no);
        if( TRUE == result )
        {
            //�I�˪��ɳt���ܬ�0
            Speedx = (-1* Speedx);
            Speedy = (-1* Speedy);
            //
            SpeedAddLeftx = 0.0f;
            SpeedAddLefty = 0.0f;
            //
            //�I�쪺�O����
            LOCK_CHARACTER(npc_no);
            // 2. �O�d��e���t��
            SetCharacterShipSpeedX(npc_no,(SLONG)(Speedx*BOAT_SPEED_ACCURACY));
            SetCharacterShipSpeedY(npc_no,(SLONG)(Speedy*BOAT_SPEED_ACCURACY));
            //  4.�]�m�s�����V
            SetCharacterShipDegreeDir(npc_no,degree_dir);
            SetCharacterShipOldDegreeDir(npc_no,old_dir);
            UNLOCK_CHARACTER(npc_no);

            //�P�_�ت��a�O�_��F
            //�p�G���V�O���V�ؼЪ�...���N��ܨ�F�F.!!!
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
            // 1. �O�d��e���y��
            //
            LOCK_CHARACTER(npc_no);
			SetCharacterPosition(npc_no, x, y, z);
            SetCharacterShipSpeedX(npc_no,(SLONG)(Speedx*BOAT_SPEED_ACCURACY));
            SetCharacterShipSpeedY(npc_no,(SLONG)(Speedy*BOAT_SPEED_ACCURACY));
            SetCharacterShipDegreeDir(npc_no,degree_dir);
            SetCharacterShipOldDegreeDir(npc_no,old_dir);
            UNLOCK_CHARACTER(npc_no);

            //�P�_�O�_��F�ؼЦa�I
            //�p�G���V�O���V�ؼЪ�...���N��ܨ�F�F.!!!
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
                    //NPCde �ਭ���L�{
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
                    //�ਭ���L�{
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
                    SetCharacterShipDegreeDir(npc_no,degree_dir);	//���V
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

