/*
**	NetGE_MagicBreak.h 
**	magic break functions header. 
**
**	Jack, 2003.1.26.
*/
#pragma once
//-------------------------------------------------------------------------
#define     MAX_MAGIC_UNIT          256     //�̦h�঳���]�k�ե�..�椸������
#define     MAX_MAGIC_BREAK         256     //�̦h�঳���]�k���󪺬��}�覡
//
#define     MAX_MAGIC_DIR           32      //�k�N�ե󰵦h�঳����V  
                                            // 0 --- 31  ��  12�I�}�l���ɰw
//----
//  �k�N�ե󬵶}������
//----                
#define     MAGIC_BREAK_TYPE_TAG        0
#define     MAGIC_BREAK_TYPE_SELF       1
#define     MAGIC_BREAK_TYPE_EFF        2
//----
//  �w�q�]�k���󪺥ͦs�覡
//----
#define     MAGIC_SURVIAL_TIME            0x00000001  //���]�k����b�@�q�ɶ���|����
#define     MAGIC_SURVIAL_FRAME_ONE_TIME  0x00000002  //���]�k����b�ʵe�����̫�@�V�|����
#define     MAGIC_SURVIAL_PATH            0x00000004  //���]�k����b�����ۤv���B�ʶZ�������
#define     MAGIC_SURVIAL_ALPHA_DISAPPEAR 0x00000008  //���]�k����alpha�X�{..�����
#define     MAGIC_SURVIAL_ALPHA_APPEAR    0x00000010  //���]�k���� alpha����..�����
//----
//MAGIC PATHS(�k�N���|)
//      ��ai�w�q�F�]�k�ե󪺩��..�y��..
//----
#define     MAGIC_PATH_DUMP             0           //
#define     MAGIC_PATH_LINE             1		    //�u�ʸ��|..�N�O���]�k����O���Ӫ��u����...
#define     MAGIC_PATH_UP               2           //�y��..�q�U���W��
#define     MAGIC_PATH_CURVE            3		    //���u�����|, ����̷Ӯɶ����Ӧۤv�J�w�y��B��
#define     MAGIC_PATH_MISSILE          2		    //�ɼu�����|, ������ܥؼйB��
#define     MAGIC_PATH_STAY             5		    //���d��a, �`������
#define     MAGIC_PATH_LINK             6		    //�s���bNPC�W
#define     MAGIC_PATH_FALL             7		    //�q�Ť����U
#define     MAGIC_PATH_MOVE             8		    //�u�ʲ���, �J����׫����
#define     MAGIC_PATH_TRACE            9		    //���ܥؼ�, �J����צ۰�¶�L
#define     MAGIC_PATH_STAY_ONCE        10          //���d��a, ���񧹫����
#define     MAGIC_PATH_ROLL             11		    //�u��, �J�� NPC �u�}, �p�G���Ĥ�P���٦���
#define     MAGIC_PATH_SHAKE            12		    //�_�}�ç�����νd�򤺪��ĤH
#define     MAGIC_PATH_DIFFUSE          13		    //������νd�򤺪��ĤH
#define     MAGIC_PATH_SCREW            14		    //���۽u�覡�e�i
#define     MAGIC_PATH_EDDY             15		    //�������u, ��¶�I�k�̱���
#define	    MAGIC_PATH_PARABOLA			16		    //�ߪ��u
//----
//  �]�k�ե�㦳���ݩ�
//----
#define     MAGIC_UNIT_ATTRIB_DIR_CHANGE        0x00000001  //�b�����O���W��V(0��)���ɭ�..�ƾڬO�_�ݭn.������������
#define     MAGIC_UNIT_ATTRIB_COOR_RAND         0x00000002  //�H���y�Ъ�..�лx_
//----
//  �]�k���}�覡���ݩ�
//----
#define     MAGIC_BREAK_ATTRIB_TAG_BREAK        0x00000001  //�b�ؼЦ�m���}���ݩ�
//----
//�s���magic break�ɭԪ��̹��ĪG
//----
#define     MAGIC_BREAK_SCREEN_QUAKE            0x00000001  //�a�Ͼ_��
//----
//  �w�q�Ӫ��󪺤W�Ϥ覡
//----
#define     MAGIC_EFF_SHADOW                    0x00000001  //�Ӫ���W�ϬO�_�n�e�v�l
#define     MAGIC_EFF_INVERT_IMAGE              0x00000002  //�Ӫ���W�ϬO�_�ݭn�˼v���лx(�������v�l)
#define     MAGIC_EFF_BLEND                     0x00000010  //�Ӫ���W�ϬO�_�ݭn �ĦX��alpha�W�Ϥ覡 (�S�����ܥδ��q��put �ϥ�alpha �q�D�ӱ���)
#define     MAGIC_EFF_TRACK_DUST                0x00000100  //�Ӫ���b���ʹL�{���|�d�U�ǹЪ�����
//----
//  �]�k����ʵe������
//----
#define     MAGIC_FRAME_LOOP                    0x00000001  //�`������лx
#define     MAGIC_FRAME_ORDER                   0x00000002  //���`���Ǽ���лx
//
//-------------------------------------------------------------------------
//�ӵ��c�w�q���O�@�Ǫk�N�ե�..�欰�K�w�q���O�̤p���k�N�ե�
typedef struct POS_MAGIC_UNIT
{
    SLONG   AppearImgId;    //�X�{�ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
    SLONG   ProcImagId;     //�L�{�ʵe
    SLONG   DisAppearImgId; //�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
    SLONG   DirNum;			//��V�ƾ�
    SLONG   Path;           //�B�ʪ��y��
    SLONG   Survial;        //�ͦs���覡
    SLONG   FrameType;      //�ʵe�V��������
    SLONG   DrawEff;        //�W�Ϫ��ĪG
    SLONG   Stop;           //��������������
    double  Speed;          //���ʪ��t��
    double  VertSpeed;      //������V�W��..�t��
}TPOS_MAGIC_UNIT,*LPTOPS_MAGIC_UNIT;
//
//�w�q���O�p��ϥΨ���MAGIC_UNIT
typedef struct POS_MAGIC_BREAK_PARAMETER
{
    SLONG   UnitId;          //�ϥΪ� MAGIC_UNIT ��ID
    SLONG   Attrib;          //���MAGIC_BREAK��ӧ��ܤ�V,��MAGIC_UNIT�O�_�ݭn���ܤ�V
    SLONG   ox,oy,oz;        //�y�а��t    
    SLONG   Dir;             //��V���t...�b�ӲզX�ĪG��...��unit����V�O�_�ݭn���A���վ�(�̦h32��V  0--32)
    SLONG   SleepTime;       //�e�m���ݮɶ�
    SLONG   SurvialTime;     //�ͦs�ɶ�(-1��ܪ��O�Ӫk�N�ե�|�λ��s�b)
    SLONG   DirLockNum;      //�Ӫk�N�ե�O���O�A�঳�T�w���X�Ӥ�V(-1�N��঳�Ҧ�����V)
    union
    {
        SLONG   MoveStep;   //��ܸӪk�N�ե󪺳̦h���ʨB�ƥ�
        SLONG   MoveDist;   //�Ӫk�N�ե�ಾ�ʪ��Z��
    };
}TPOS_MAGIC_BREAK_PARAMETER,*LTPOS_MAGIC_BREAK_PARAMETER;
//�w�q���O�@��,�Ҧ���MAGIC_BREAK�@�Ϊ��Ѿ�
typedef struct POS_MAGIC_BREAK
{
    SLONG   UnitNum;        //��break�]�t����magic_action���ƥ�
    SLONG   Attrib;         //�ݩ�
    SLONG   ox, oy, oz;     //����]�k���}�ĪG���y�а��t
    SLONG   MaxDir;         //�Ӭ��}�覡��������̦h��V�ƥ�(-1�N��O���N��V)
    //
    SLONG   lBreakParamentBegin;    //�ƾڶ}�l....����m
}TPOS_MAGIC_BREAK,*LPTOPS_MAGIC_BREAK;
//
//-------------------------------------------------------------------------
SLONG	DummyBreakMagicFunction( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
//
SLONG   BreakMagic_FireBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireDragon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireWall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireArmor( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireBroken( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireAerolite( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FireWard( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_IceBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceBow( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceMirror( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceCoagulate( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceCircle( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceFall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_IceBlade( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_LightStrike( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBless( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBlade( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightBaptism( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_LightThundering( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_DustUnderStick( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustArrayStones( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustDiffuseWave( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustXirang( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustRollStone( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DustVirusGas( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_ArcChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_SeriesChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_SteelSever( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BallyragCircle( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_WindfallChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_ThrowDragon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_EvilBomb( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_CleanseLight( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BlestBarrier( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_Blessing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_Prayer( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_FastWind( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_HolyPhotosphere( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_VitalWind( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_RevengeAngel( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_JusticeAngel( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_AresDance( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BrokenBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_DemonHowl( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_WindBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BrokenArmor( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_ArhatBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_GasBarrier( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
SLONG   BreakMagic_BloodEddies( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

SLONG   BreakMagic_ShipCannon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
//�X�{�ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG   GetMagicUnitAppearImgId(SLONG lIndex);
//�L�{�ʵe
SLONG   GetMagicUnitProcImgId(SLONG lIndex);
//�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG   GetMagicUnitDisAppearImgId(SLONG lIndex);
//��V�ƾ�
SLONG   GetMagicUnitDirNum(SLONG lIndex);
//�B�ʪ��y��
SLONG   GetMagicUnitPath(SLONG lIndex);
//�ͦs���覡
SLONG   GetMagicUnitSurvial(SLONG lIndex);
//�W�Ϫ��ĪG
SLONG   GetMagicUnitDrawEff(SLONG lIndex);
//��������������
SLONG   GetMagicUnitStop(SLONG lIndex);
//���ʪ��t��
double  GetMagicUnitSpeed(SLONG lIndex);
//-------------------------------------------------------------------------
//  ��l�ƪk�N���}��...�ƾ�
//-------------------------------------------------------------------------
SLONG	InitMagicBreakSystem(void);
//-------------------------------------------------------------------------
//  ����k�N���}���@�Ǳ�����
//-------------------------------------------------------------------------
SLONG   BreakMagic_CommonBreak( SLONG skill_no, SLONG npc_no, SLONG type, SLONG dest_x, SLONG dest_y, SLONG dest_no);
SLONG   MagicBreakProc(SLONG break_no, SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_z, SLONG dest_npc);
