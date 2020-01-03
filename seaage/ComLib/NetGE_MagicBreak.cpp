/*
**	NetGE_MagicBreak.cpp 
**	magic break functions.
**
**	Jack, 2003.1.26.
*/
#include "NetGE_MainFunc.h"
//=========================================================================
#define     MAX_MAGIC_BREAK_UNIT_STACK  (1024*5)    //���..���s�ƾ�...
//=========================================================================
//
TPOS_MAGIC_UNIT             g_GameMagicUnit[MAX_MAGIC_UNIT];
TPOS_MAGIC_BREAK            g_GameMagicBreak[MAX_MAGIC_BREAK];
//
TPOS_MAGIC_BREAK_PARAMETER  g_GameMagicParamentStack[MAX_MAGIC_BREAK_UNIT_STACK];
SLONG                       g_GameMagicParamentStackUseNum = 0;
//=========================================================================
void    DebugLogMagicBreakBase(void);
SLONG   LoadMagicBreakSystem(CHAR* szFileName) ;
void    InitMagicBreakBase(void);
//
SLONG   LoadGameMagicUnitBase(CHAR* szFileName);
SLONG   LoadGameMagicBreakBase(CHAR* szFileName);

SLONG   MagicBreakProc(SLONG break_no, SLONG skill_no, SLONG skill_level, 
                       SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_z, SLONG dest_npc);
SLONG   MagicUnitBreak(TPOS_MAGIC_BREAK_PARAMETER *p_para, SLONG BreakNo, 
                        SLONG npc_no, SLONG tag_npc, SLONG Skill,SLONG SkillLevel,
                        SLONG x, SLONG y, SLONG z, SLONG npc_x, SLONG npc_y, SLONG npc_z,
                        float angle);
/************************************************************************************************************/
/* DUMMY BREAK MAGIC FUNCTION                                                                               */
/************************************************************************************************************/
SLONG	DummyBreakMagicFunction( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    SetBreakMagicPartsCount(0);
	return	0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FIRE SERIES MAGICS (���t�k�N)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mark by lijun 2003-05-06
/*
//----
//  ������y...
//----
SLONG   BreakMagic_FireBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    { 
        PARTS_NUM       =   1,
        PARTS_RADIUS    =   48,
        OUTER_RADIUS    =   200,
        SHIFTS          =   32,
        EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	5, 203, 204, 205, 
		6, 206, 207, 208, 
		7, 209, 210, 211, 
		8, 212, 213, 214, 
		1, 191, 192, 193, 
		2, 194, 195, 196, 
		3, 197, 198, 199,
		4, 200, 201, 202
	};
    static  explode_id[EXPLODES] = { 9 };
    SLONG   part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;

    part_index = 0;
    {
        //�]�m�I�k��
        SetBreakMagicPartSourceNo(part_index, npc_no);
        //�]�m�����ؼ�
        SetBreakMagicPartTargetNo(part_index, -1);
        //�]�m���]�k�ե�N���ޯ�s��
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        //�]�m���]�k�ե󪺩�ʭy��
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        //�]�m���]�k�ե�..�|���쪺��������
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        //�]�m���]�k�ե�..�ҳB���ͦs�g��
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //�]�m�]�k�ե󪺥ͦs�g��..�ɶ�
        SetBreakMagicPartLifeTick(part_index, 36);
        //�]�m�]�k�ե����᪺����ɶ�
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
        //�]�m�]�k�ե󪺲��ʥؼ�
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
        //�]�m�]�k�ե�.. �}�l..�y��
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		//�]�m�]�k�ե�..��e..�y��
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		//�]�m�]�k�ե�Z���}�l��m��..�B��
        SetBreakMagicPartStep(part_index, 0);
        //�]�m�]�k�ե󪺲��ʳt��
        SetBreakMagicPartSpeed(part_index, 16);
        //
        //�]�m�]�k�ե󪺲��ʪ�..���ɪ�id ..
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        //�]�m�]�k�ե�..���}������id .
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        //
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        //�]�m�]�k�ե󪺤W�Ϥ覡
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        //�I�]�k����Q�ϥ�.....�лx
        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_FireDragon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   16,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 19 };
    SLONG   explode_id[EXPLODES] = { 19 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt( dx * dx + dy * dy );
    if(dr == 0)
        return -1;

    kx = dx / dr;
    ky = dy / dr;

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_MOVE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 12);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_FireWall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   32,
    SHIFTS          =   4,
    STAY_DIST       =   12,
    };
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    double  upright_kx, upright_ky;
    SLONG   i, part_index;
    //SLONG   shift_id[SHIFTS] = { 26, 27, 28, 29 };
    SLONG   shift_id[SHIFTS] = { 401, 402, 403, 404 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt( dx * dx + dy * dy );
    if(dr == 0)
        return -1;

    kx = dx / dr;
    ky = dy / dr;
    upright_kx = ky;
    upright_ky = -kx;

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_STAY);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 192);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i/2);
        //
        part_dest_x = (SLONG) ( dest_x + STAY_DIST * upright_kx * (i / 2) * (1 - i%2 * 2) );
        part_dest_y = (SLONG) ( dest_y + STAY_DIST * upright_ky * (i / 2) * (1 - i%2 * 2) );
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        shift_dir = system_rand() % SHIFTS;
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, shift_id[shift_dir]);
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return  0;
}


SLONG   BreakMagic_FireArmor( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 25 };
    static  explode_id[EXPLODES] = { 25 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	// about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_FireBroken( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	14, 227, 228, 229, 
		15, 230, 231, 232,
		16, 233, 234, 235,
		17, 236, 237, 238,
		10, 215, 216, 217,
		11, 218, 219, 220,
		12, 221, 222, 223,
		13, 224, 225, 226
	};
    static  explode_id[EXPLODES] = { 18 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_FireAerolite( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   6,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        {-28, 26}, {30, 18}, { -7, -9 },
        {-28, 26}, {30, 18}, { -7, -9 }
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 21 };
    SLONG   explode_id[EXPLODES] = { 22 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i * 5);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = part_dest_x;
        part_orig_y = part_dest_y;
        part_orig_z = SCREEN_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_FireWard( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    STAR_GONS       =   5,
    CUT_BREAKS      =   4,
    PARTS_NUM       =   STAR_GONS * (1 + CUT_BREAKS * 2 + 1),
    SHIFTS          =   4,
    EXPLODES        =   4,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        //five star inner point
        {   67,   48 },        {  -25,   78 },        {  -82,    0 },        {  -25,  -78 },        {   67,  -48 },
        //five star ordered break point
        //order 0
        {   87,   38 },        {   64,   70 },        {  -10,   94 },        {  -47,   82 },        {  -92,   19 },
        {  -92,  -19 },        {  -47,  -82 },        {  -10,  -94 },        {   64,  -70 },        {   87,  -38 },
        //order 1
        {  107,   29 },        {   61,   92 },        {    5,  110 },        {  -68,   86 },        { -103,   39 },
        { -103,  -39 },        {  -68,  -86 },        {    5, -110 },        {   61,  -92 },        {  107,  -29 },
        //order 2
        {  127,   19 },        {   57,  113 },        {   20,  126 },        {  -90,   90 },        { -113,   58 },
        { -113,  -58 },        {  -90,  -90 },        {   20, -126 },        {   57, -113 },        {  127,  -19 },
        //order 3
        {  146,   10 },        {   54,  135 },        {   36,  142 },        { -112,   94 },        { -124,   77 },
        { -124,  -77 },        { -112,  -94 },        {   36, -142 },        {   54, -135 },        {  146,  -10 },
        //long dist gon points
        {  167,    0 },        {   51,  158 },        { -135,   98 },        { -135,  -98 },        {   51, -158 }
    };
    static  SLONG   sleep_tick[1 + CUT_BREAKS * 2 + 1] = { 1,2,2,3,3,4,4,5,5,6 };

    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 29, 29, 29, 29 };
    SLONG   explode_id[EXPLODES] = { 29, 29, 29, 29 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    shift_dir = system_rand() % SHIFTS;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_STAY);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 192);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, sleep_tick[i / STAR_GONS]);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y / 2;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        //shift_dir = system_rand() % SHIFTS;
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, shift_id[shift_dir]);
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ICE SERIES MAGICS (�B�t�k�N)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG   BreakMagic_IceBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	37, 251, 252, 253, 
		38, 254, 255, 256,
		39, 257, 258, 259,
		40, 260, 261, 262,
		33, 239, 240, 241,
		34, 242, 243, 244,
		35, 245, 246, 247,
		36, 248, 249, 250
	};
    static  explode_id[EXPLODES] = { 41 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 20);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_IceBow( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	46, 275, 276, 277, 
		47, 278, 279, 280,
		48, 281, 282, 283,
		49, 284, 285, 286,
		42, 263, 264, 265,
		43, 266, 267, 268,
		44, 269, 270, 271,
		45, 272, 273, 274
	};
    static  explode_id[EXPLODES] = { 50 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 20);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_IceMirror( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 51 };
    static  explode_id[EXPLODES] = { 51 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_IceCoagulate( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 23 };  
    static  explode_id[EXPLODES] = { 23 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_IceCircle( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   128,
    SHIFTS          =   1,
    STAY_DIST       =   12,
    PARTS_RADIUS    =   48,
    };
    SLONG   x, y, z;
    double  sita, speed_ratio;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 24 };
    SLONG   shift_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;
        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_MOVE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 12);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        sita = (double)( i * 2 * PI / PARTS_NUM );
        part_dest_x = (SLONG) ( x + 5 * PARTS_RADIUS * cos(sita) );
        part_dest_y = (SLONG) ( y + 5 * PARTS_RADIUS/2 * sin(sita) );
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * cos(sita) );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS/2 * sin(sita) );
        part_orig_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);

        //Speed is based on the length from (dest_x,dest_y) to (part_orig_x, part_orig_y).
        speed_ratio = sqrt( cos(sita) * cos(sita) + ( sin(sita) / 2 ) * ( sin(sita) / 2 ) );
        SetBreakMagicPartSpeed(part_index, 16 * speed_ratio);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, shift_id[shift_dir]);
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_IceFall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   9,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        {-28, 26}, {30, 18}, { -7, -9 },
        { -8,  6}, {10, 28}, {-25, -2 },
        { 16,-10}, { 4, 12}, {-16, 12 },
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 53 };
    SLONG   explode_id[EXPLODES] = { 54 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i * 5);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = part_dest_x;
        part_orig_y = part_dest_y;
        part_orig_z = SCREEN_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 24);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_IceBlade( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   5,
    SHIFTS          =   32,
    EXPLODES        =   1,
    STAY_DIST       =   12,
    PARTS_RADIUS    =   48,
    };
    SLONG   x, y, z;
    double  sita;
    SLONG   degree, base_degree;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = 
	{	303, 304, 305, 306,
		307, 308, 309, 310,
		311, 312, 313, 314,
		315, 316, 317, 318,
		287, 288, 289, 290,
		291, 292, 293, 294,
		295, 296, 297, 298,
		299, 300, 301, 302
	};
    SLONG   explode_id[EXPLODES] = { 319 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    //We doubled (dest_y-y) for base_degree here for later we must adjust for ellipse xa/xb = 2:1.
    base_degree = (SLONG)( atan2( 2 * (dest_y - y), dest_x - x) / PI * 180 );
    if(base_degree < 0)
        base_degree += 360;

    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 20);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        degree = base_degree + i * 360 / PARTS_NUM ;
        if(degree > 360)
            degree -= 360;
        sita = degree * PI / 180;

        part_dest_x = (SLONG) ( x + 5 * PARTS_RADIUS * cos(sita) );
        part_dest_y = (SLONG) ( y + 5 * PARTS_RADIUS/2 * sin(sita) );
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * cos(sita) );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS/2 * sin(sita) );
        part_orig_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
        //
		shift_dir = ApproachScreenAxisDegreeDirEx(degree*100, SHIFTS);

        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIGHT SERIES MAGICS (�p�q�t�k�N)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG   BreakMagic_LightStrike( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   16,
    INNER_RADIUS    =   54,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    SHIFT_DIR_JOLT  =   3,
    };
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   dir_degree, degree;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = 
    {   
        71, 72, 73, 74, 75, 76, 77, 78,
        79, 80, 81, 82, 83, 84, 85, 86,
        55, 56, 57, 58, 59, 60, 61, 62, 
        63, 64, 65, 66, 67, 68, 69, 70,
    };
    SLONG   shift_dir, base_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt( dx * dx + dy * dy );
    if(dr == 0)
        return -1;

    kx = dx / dr;
    ky = dy / dr;

    degree = (SLONG)( atan2(dest_y - y, dest_x - x) / PI * 180 );
    if(degree < 0)
        degree += 360;
    dir_degree = 360 / SHIFTS;
    base_dir = (degree + dir_degree / 2) / dir_degree ;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_MOVE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 20);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + INNER_RADIUS * kx );
        part_orig_y = (SLONG) ( y + INNER_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 20);
        //
        shift_dir = ( base_dir + ( 1 - system_rand()%2 * 2 ) * ( system_rand() % SHIFT_DIR_JOLT ) + SHIFTS ) % SHIFTS;
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_LightBless( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 32 };  
    static  explode_id[EXPLODES] = { 32 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height.
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}



SLONG   BreakMagic_LightBlade( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 94 }; // { 93 };
    static  explode_id[EXPLODES] = { 88 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    //SLONG   dest_npc;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
    SLONG   map_no;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
	map_no = 0;
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0) dr = 1.0;
    kx = dx / dr;
    ky = dy / dr;

    //For server, we have find_near_target_npc() and store it in magic_pipe before.
    //For client, we receive the dest_npc and store it in magic_pipe before.
    //dest_npc = GetMagicPipeDestNo();

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, dest_no);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_TRACE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 80);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 6);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_LightBall( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 87 };
    static  explode_id[EXPLODES] = { 92 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = 0;
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_LightBaptism( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   64,
    SHIFTS          =   32,
    STAY_DIST       =   12,
    PARTS_RADIUS    =   48,
    };
    SLONG   x, y, z;
    double  sita, speed_ratio;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] =
    {   
        71, 72, 73, 74, 75, 76, 77, 78,
        79, 80, 81, 82, 83, 84, 85, 86,
        55, 56, 57, 58, 59, 60, 61, 62, 
        63, 64, 65, 66, 67, 68, 69, 70,
    };
    SLONG   shift_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_MOVE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 12);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        sita = (double)( i * 2 * PI / PARTS_NUM );
        part_dest_x = (SLONG) ( x + 5 * PARTS_RADIUS * cos(sita) );
        part_dest_y = (SLONG) ( y + 5 * PARTS_RADIUS / 2 * sin(sita) );
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * cos(sita) );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS / 2 * sin(sita) );
        part_orig_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);

        //speed is based on the length from (dest_x,dest_y) to (part_orig_x, part_orig_y).
        speed_ratio = sqrt( cos(sita) * cos(sita) + ( sin(sita) / 2 ) * ( sin(sita) / 2 ) );
        SetBreakMagicPartSpeed(part_index, 16 * speed_ratio);
        //
        //shift_dir = (i / (PARTS_NUM / SHIFTS) ) % SHIFTS;
        shift_dir = (i / (PARTS_NUM / SHIFTS)  +  SHIFTS / 4) % SHIFTS; //rotate the part image 90 degree.
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, shift_id[shift_dir]);
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_LightThundering( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    //PARTS_NUM       =   6,
    PARTS_NUM       =   1,
    SHIFTS          =   4,
    EXPLODES        =   1,
    };
    static  POINT   point[PARTS_NUM] = 
    {
		{0, 0},
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 95, 96, 97, 98 };
    SLONG   explode_id[EXPLODES] = { 99 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 100);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i * 3);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = part_dest_x;
        part_orig_y = part_dest_y;
        part_orig_z = SCREEN_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 70);
        //
        shift_dir = system_rand() % SHIFTS;
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DUST SERIES MAGICS (�g�t�k�N)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG   BreakMagic_DustUnderStick( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   8,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   1,
    EXPLODES        =   1,
    PARTS_GAP       =   32,
    };
    SLONG   x, y, z;
    double  degree;
    double  sita, ratio, gap;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 100 };
    SLONG   explode_id[EXPLODES] = { 100 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    degree = (SLONG)( atan2( (dest_y - y), dest_x - x) / PI * 180 );
    if(degree < 0)
        degree += 360;
    sita = degree * 2 * PI / 360;

    ratio = sqrt( cos(sita) * cos(sita) + ( sin(sita) / 2 ) * ( sin(sita) / 2 ) );
    gap = PARTS_GAP * ratio;

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;
        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_STAY_ONCE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 12);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, i);
        //
        part_dest_x = (SLONG) ( x + (PARTS_RADIUS + gap * i) * cos(sita) );
        part_dest_y = (SLONG) ( y + (PARTS_RADIUS + gap * i) * sin(sita) );
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_DustArrayStones( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_PER_LINE  =   8,
    PARTS_LINES     =   16,
    PARTS_NUM       =   PARTS_PER_LINE * PARTS_LINES,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   1,
    EXPLODES        =   1,
    PARTS_GAP       =   32,
    };
    SLONG   x, y, z;
    double  sita, ratio, gap;
    SLONG   i, j, part_index;
    SLONG   shift_id[SHIFTS] = { 100 };
    SLONG   explode_id[EXPLODES] = { 100 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_LINES; i++ )
    {
        sita = (double)( i * 2 * PI / PARTS_LINES );
        ratio = sqrt( cos(sita) * cos(sita) + ( sin(sita) / 2 ) * ( sin(sita) / 2 ) );
        gap = PARTS_GAP * ratio;

        for(j = 0; j < PARTS_PER_LINE; j++)
        {
            part_index = i * PARTS_PER_LINE + j;

            SetBreakMagicPartSourceNo(part_index, npc_no);
            SetBreakMagicPartTargetNo(part_index, -1);
            SetBreakMagicPartSkillIndex(part_index, magic_no);
            SetBreakMagicPartPath(part_index, MAGIC_PATH_STAY_ONCE);
            SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
            SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
            //
            SetBreakMagicPartLifeTick(part_index, 12);
            SetBreakMagicPartDelayTick(part_index, 0);
            SetBreakMagicPartSleepTick(part_index, j);
            //
            part_dest_x = (SLONG) ( x + (PARTS_RADIUS + gap * j) * cos(sita) );
            part_dest_y = (SLONG) ( y + (PARTS_RADIUS + gap * j) * sin(sita) );
            part_dest_z = LO_MAGIC_HEIGHT;
			SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
			SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
			SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
            //
            SetBreakMagicPartStep(part_index, 0);
            SetBreakMagicPartSpeed(part_index, 0);
            
            //
            SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
            SetBreakMagicPartExplodeImageID(part_index, shift_id[shift_dir]);
            SetBreakMagicPartObjectIndex(part_index, -1);
            SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
            SetBreakMagicPartImageFrame(part_index, 0);
            SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
            
            SetBreakMagicPartFlag(part_index, 1);
        }
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_DustDiffuseWave( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   12,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        {-23   ,  25      },
        {8     ,  30      },
        {-5    ,  -3      },
        {-40   ,  7       },
        {27    ,  6       },
        {-26   ,  -15     },
        {34    ,  27      },
        {23    ,  -27     },
        {3     ,  -37     },
        {-18   ,  -33     },
        {49    ,  -1      },
        {-45   ,  -24     }
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 130 };
    SLONG   explode_id[EXPLODES] = { 130 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_STAY_ONCE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, (i / 3) * 10);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_DustXirang( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 31 };  
    static  explode_id[EXPLODES] = { 31 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_DustRollStone( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   16,
    EXPLODES        =   8,
    };
    static  shift_id[SHIFTS] = 
	{	112, 397,
		113, 398,
		114, 399,
		115, 400,
		108, 393,
		109, 394,
		110, 395,
		111, 396,
	};
    static  explode_id[EXPLODES] = { 116 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_ROLL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 48);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 10);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_DustVirusGas( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 117};
    static  explode_id[EXPLODES] = { 118 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = 0;
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_ArcChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	131, 332, 333, 334,
		132, 335, 336, 337,
		133, 338, 339, 340,
		134, 341, 342, 343,
		135, 320, 321, 322, 
		136, 323, 324, 325,
		137, 326, 327, 328,
		138, 329, 330, 331,
	};
    static  explode_id[EXPLODES] = { 88 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		//
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_SeriesChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	131, 332, 333, 334,
		132, 335, 336, 337,
		133, 338, 339, 340,
		134, 341, 342, 343,
		135, 320, 321, 322, 
		136, 323, 324, 325,
		137, 326, 327, 328,
		138, 329, 330, 331,
	};
    static  explode_id[EXPLODES] = { 88 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_SteelSever( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 30 };
    static  explode_id[EXPLODES] = { 30 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG   BreakMagic_BallyragCircle( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 139 };
    static  explode_id[EXPLODES] = { 139 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_SHAKE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_WindfallChop( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   1,
    SHIFTS          =   16,
    EXPLODES        =   16,
    STAY_DIST       =   12,
    PARTS_RADIUS    =   24,
    };
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  sita, dr;
    SLONG   degree, base_degree;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = 
	{	140, 380, 
		141, 381,
		142, 382,
		143, 383,
		144, 376,
		145, 377,
		146, 378,
		147, 379
	};
    SLONG   explode_id[EXPLODES] = 
	{	140, 380, 
		141, 381,
		142, 382,
		143, 383,
		144, 376,
		145, 377,
		146, 378,
		147, 379
	};
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;

    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = shift_dir;

    //We doubled (dest_y-y) for base_degree here for later we must adjust for ellipse xa/xb = 2:1.
    base_degree = (SLONG)( atan2( 2 * (dest_y - y), dest_x - x) / PI * 180 );
    if(base_degree < 0)
        base_degree += 360;

    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_MOVE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 10);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        degree = base_degree + i * 360 / PARTS_NUM ;
        if(degree > 360)
            degree -= 360;
        sita = degree * PI / 180;
        part_dest_x = (SLONG) ( x + 5 * PARTS_RADIUS * cos(sita) );
        part_dest_y = (SLONG) ( y + 5 * PARTS_RADIUS/2 * sin(sita) );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * cos(sita) );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS/2 * sin(sita) );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_ThrowDragon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	152, 356, 357, 358,
		153, 359, 360, 361,
		154, 362, 363, 364,
		155, 365, 366, 367,
		148, 344, 345, 346,
		149, 347, 348, 349,
		150, 350, 351, 352,
		151, 353, 354, 355,
	};
    static  explode_id[EXPLODES] = { 157 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 20);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_EvilBomb( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   8,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 166, 166, 166, 166, 166, 166, 166, 166 };
    static  explode_id[EXPLODES] = { 156 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;


    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 32);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 8);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}



SLONG   BreakMagic_CleanseLight( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 158 };
    static  explode_id[EXPLODES] = { 158 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_BlestBarrier( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 122 };
    static  explode_id[EXPLODES] = { 122 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_Blessing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 159 };
    static  explode_id[EXPLODES] = { 159 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_Prayer( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 160 };
    static  explode_id[EXPLODES] = { 160 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_FastWind( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 161 };
    static  explode_id[EXPLODES] = { 161 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;


    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_HolyPhotosphere( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   8,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 162, 162, 162, 162, 162, 162, 162, 162 };
    static  explode_id[EXPLODES] = { 163 };
    SLONG   part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    kx = dx / dr;
    ky = dy / dr;

    part_index = 0;
    {
        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINE);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 36);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}



SLONG   BreakMagic_VitalWind( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 164 };
    static  explode_id[EXPLODES] = { 164 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_RevengeAngel( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 165 };
    static  explode_id[EXPLODES] = { 165 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_DIFFUSE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_JusticeAngel( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        {0, 0}
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 167 };
    SLONG   explode_id[EXPLODES] = { 168 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = part_dest_x;
        part_orig_y = part_dest_y;
        part_orig_z = SCREEN_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 40);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG   BreakMagic_AresDance( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 128 };
    static  explode_id[EXPLODES] = { 128 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 0);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_BrokenBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        {0, 0}
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 9 };
    SLONG   explode_id[EXPLODES] = { 9 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;
    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 40);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_DemonHowl( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   1,
    SHIFTS          =   4,
    EXPLODES        =   4,
    };
    static  POINT   point[PARTS_NUM] = 
    {
        {0, 0}
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 169, 170, 171, 172 };
    SLONG   explode_id[EXPLODES] = { 169, 170, 171, 172 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = ApproachScreenAxisDirEx( dest_x - x, dest_y - y, SHIFTS );
    explode_dir = shift_dir;

    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = dest_x + point[i].x;
        part_dest_y = dest_y + point[i].y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 40);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_WindBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   24,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   16,
    EXPLODES        =   16,
    };
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, kx, ky;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = 
	{	173, 372, 
		174, 373,
		175, 374,
		176, 375,
		177, 368,
		178, 369,
		179, 370,
		180, 371
	};
    SLONG   explode_id[EXPLODES] = 
	{	173, 372, 
		174, 373,
		175, 374,
		176, 375,
		177, 368,
		178, 369,
		179, 370,
		180, 371
	};
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt( dx * dx + dy * dy );
    if(dr == 0)
        return -1;

    kx = dx / dr;
    ky = dy / dr;

    shift_dir = ApproachScreenAxisDirEx( dx, dy, SHIFTS) ;
    explode_dir = shift_dir;

    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;
        
        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_SCREW);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 60);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
        //
        SetBreakMagicPartStep(part_index, i);
        SetBreakMagicPartSpeed(part_index, 4);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_BrokenArmor( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 121 };
    static  explode_id[EXPLODES] = { 121 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_LINK);
        SetBreakMagicPartStop(part_index, 0);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = 80;	//about npc's image height
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_ArhatBoxing( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum
    {
    PARTS_NUM       =   1,
    SHIFTS          =   8,
    EXPLODES        =   8,
    };
    SLONG   x, y, z;
    SLONG   i, part_index;
    SLONG   shift_id[SHIFTS] = { 181, 182, 183, 184, 185, 186, 187, 188 };
    SLONG   explode_id[EXPLODES] = { 181, 182, 183, 184, 185, 186, 187, 188 };
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = ApproachScreenAxisDirEx( dest_x - x, dest_y - y, SHIFTS );
    explode_dir = shift_dir;

    for(i = 0; i < PARTS_NUM; i++ )
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_FALL);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 300);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = dest_x;
        part_dest_y = dest_y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 40);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_GasBarrier( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 189 };
    static  explode_id[EXPLODES] = { 189 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_DIFFUSE);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 99999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 12);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}


SLONG   BreakMagic_BloodEddies( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    {
    PARTS_NUM       =   1,
    SHIFTS          =   1,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = { 190 };
    static  explode_id[EXPLODES] = { 190 };
    SLONG   i, part_index;
    SLONG   x, y, z;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    shift_dir = 0;
    explode_dir = 0;

    for(i=0; i<PARTS_NUM; i++)
    {
        part_index = i;

        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_EDDY);
        SetBreakMagicPartStop(part_index, MASK_LO_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 256);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        part_dest_x = x;
        part_dest_y = y;
        part_dest_z = LO_MAGIC_HEIGHT;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartOrigPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
		SetBreakMagicPartCurrPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 2 * PI / 64);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);

        SetBreakMagicPartFlag(part_index, 1);
    }
    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}



SLONG   BreakMagic_ShipCannon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no )
{
    enum 
    { 
    PARTS_NUM       =   1,
    PARTS_RADIUS    =   48,
    OUTER_RADIUS    =   200,
    SHIFTS          =   32,
    EXPLODES        =   1,
    };
    static  shift_id[SHIFTS] = 
	{	5, 203, 204, 205, 
		6, 206, 207, 208, 
		7, 209, 210, 211, 
		8, 212, 213, 214, 
		1, 191, 192, 193, 
		2, 194, 195, 196, 
		3, 197, 198, 199,
		4, 200, 201, 202
	};
    static  explode_id[EXPLODES] = { 9 };
    SLONG   part_index;
    SLONG   x, y, z;
    SLONG   dx, dy;
    double  dr, init_zspeed, t;
    SLONG   shift_dir, explode_dir;
	SLONG	part_dest_x, part_dest_y, part_dest_z;
	SLONG	part_orig_x, part_orig_y, part_orig_z;

    SetBreakMagicPartsCount(0);

    LOCK_CHARACTER(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);

    dx = dest_x - x;
    dy = dest_y - y;
    dr = sqrt(dx * dx + dy * dy);
    if(dr == 0)
        return -1;
    shift_dir = ApproachScreenAxisDirEx(dx, dy, SHIFTS);
    explode_dir = 0;

    part_index = 0;
    {
        SetBreakMagicPartSourceNo(part_index, npc_no);
        SetBreakMagicPartTargetNo(part_index, -1);
        SetBreakMagicPartSkillIndex(part_index, magic_no);
        SetBreakMagicPartPath(part_index, MAGIC_PATH_PARABOLA);
        SetBreakMagicPartStop(part_index, MASK_MID_MAGIC);
        SetBreakMagicPartState(part_index, MAGIC_STATE_SLEEP);
        //
        SetBreakMagicPartLifeTick(part_index, 999);
        SetBreakMagicPartDelayTick(part_index, 0);
        SetBreakMagicPartSleepTick(part_index, 0);
        //
        //part_dest_x = (SLONG) ( x + OUTER_RADIUS * kx );
        //part_dest_y = (SLONG) ( y + OUTER_RADIUS * ky );
        part_dest_x = dest_x;
        part_dest_y = dest_y;
        part_dest_z = 0;
		SetBreakMagicPartDestPosition(part_index, part_dest_x, part_dest_y, part_dest_z);
        //
        //part_orig_x = (SLONG) ( x + PARTS_RADIUS * kx );
        //part_orig_y = (SLONG) ( y + PARTS_RADIUS * ky );
        //part_orig_z = MID_MAGIC_HEIGHT;
        part_orig_x = x;
        part_orig_y = y;
        part_orig_z = MID_MAGIC_HEIGHT;
		SetBreakMagicPartOrigPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		SetBreakMagicPartCurrPosition(part_index, part_orig_x, part_orig_y, part_orig_z);
		//
        SetBreakMagicPartStep(part_index, 0);
        SetBreakMagicPartSpeed(part_index, 16);
		t = dr / 16.0;	//t = distance / speed
		init_zspeed = (- part_orig_z - GRAVITY_ACCELERATION * t * t / 2) / t;	//v0 = (-z0 - g*t*t/2)/t;
		SetBreakMagicPartVertSpeed(part_index, init_zspeed);
        //
        SetBreakMagicPartShiftImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, shift_id[shift_dir] ));
        SetBreakMagicPartExplodeImageID(part_index, MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, explode_id[explode_dir] ));
        SetBreakMagicPartObjectIndex(part_index, -1);
        SetBreakMagicPartImageID(part_index, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(part_index, 0);
        SetBreakMagicPartImageEffect(part_index, OBJECT_NORMAL_IMAGE);
        
        SetBreakMagicPartFlag(part_index, 1);
    }

    SetBreakMagicPartsCount(PARTS_NUM);

    return PARTS_NUM;
}
*/
//-------------------------------------------------------------------------
//  ��l�ƪk�N���}��...�ƾ�
//-------------------------------------------------------------------------
SLONG	InitMagicBreakSystem(void)
{
    LoadGameMagicUnitBase("data\\magunit.ini");
    LoadGameMagicBreakBase("data\\magbrk.ini");
    //
    return 0;
}
//-------------------------------------------------------------------------
//  ����k�N���}���@�Ǳ�����
//      ��MAGIC_BREAK �@�Ǭ����ƾڪ�Ū��
//-------------------------------------------------------------------------
SLONG   LoadGameMagicUnitBase(CHAR* szFileName) 
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   num;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, len, skill_no;
	TPOS_MAGIC_UNIT *data = NULL;
    //
    file_size = load_file_to_buffer((USTR*)szFileName, &file_buf);
    if(file_size < 0)
        goto error;
	//total_item_bases = 0;
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            //
			skill_no = get_buffer_number(line, &index);
			if (skill_no >= 0 && skill_no < MAX_GAME_SKILL_BASES)
			{
				data = &g_GameMagicUnit[skill_no];
				//
                num = data->AppearImgId = get_buffer_number(line, &index);    //�X�{�ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
                if (num < 0)
                    data->AppearImgId = INVALID_OBJECT_ID;
                else                
                    data->AppearImgId = MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, num);
                //                    
                num = data->ProcImagId = get_buffer_number(line, &index);     //�L�{�ʵe
                if (num < 0)
                    data->ProcImagId = INVALID_OBJECT_ID;
                else                
                    data->ProcImagId = MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, num);
                //
                num = data->DisAppearImgId = get_buffer_number(line, &index); //�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
                if (num < 0)
                    data->DisAppearImgId = INVALID_OBJECT_ID;
                else                
                    data->DisAppearImgId = MAKE_OBJECT_ID( OBJECT_TYPE_MAGIC, num); 
                //
                data->DirNum = get_buffer_number(line, &index);			//��V�ƾ�
                data->Path = get_buffer_number(line, &index);           //�B�ʪ��y��
                data->Survial = get_buffer_number(line, &index);        //�ͦs���覡
                data->DrawEff = get_buffer_number(line, &index);        //�W�Ϫ��ĪG
                data->Stop = get_buffer_number(line, &index);           //��������������
                data->Speed = (1.0*get_buffer_number(line, &index))/100;//��������������
			}
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return 0;

error:
    return -1;
}
//-------------------------------------------------------------------------
//  Ū���k�N�ե󬵶}��...�]�w
//-------------------------------------------------------------------------
SLONG   LoadGameMagicBreakBase(CHAR* szFileName) 
{
    enum {LINE_BUFFER_SIZE = 1024};
    //
    USTR    *file_buf;
    SLONG   type;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, len, skill_no, sub_count;
	TPOS_MAGIC_BREAK *data = NULL;
	TPOS_MAGIC_BREAK_PARAMETER *parament = NULL;
    //
    file_size = load_file_to_buffer((USTR*)szFileName, &file_buf);
    if(file_size < 0)
        goto error;
	//total_item_bases = 0;
    pass = 0;
    buffer_index = 0;
    sub_count = 0;
    //
    g_GameMagicParamentStackUseNum = 0;
    //
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            //
            type = get_buffer_number(line, &index);
            //
            switch (type)
            {
            case 0: //���μƾ�
                //
                if (NULL != data)
                {
                    data->lBreakParamentBegin = g_GameMagicParamentStackUseNum;
                    data->UnitNum = sub_count;
                    g_GameMagicParamentStackUseNum += sub_count;
                    sub_count = 0;
                }
                //
			    skill_no = get_buffer_number(line, &index);
			    if (skill_no >= 0 && skill_no < MAX_GAME_SKILL_BASES)
			    {
				    data = &g_GameMagicBreak[skill_no];
				    //
                    data->UnitNum = 0;        //��break�]�t����magic_action���ƥ�
                    data->Attrib = get_buffer_number(line, &index); //�ݩ�
                    data->ox = get_buffer_number(line, &index);             //����]�k���}�ĪG���y�а��t
                    data->oy = get_buffer_number(line, &index);
                    data->oz = get_buffer_number(line, &index);
                    data->MaxDir = get_buffer_number(line, &index);         //�Ӭ��}�覡��������̦h��V�ƥ�(-1�N��O���N��V)
			    }
			    //
			    sub_count = 0;
                break;
            default:
                if (sub_count < 100)
                {
                    parament = &g_GameMagicParamentStack[g_GameMagicParamentStackUseNum + sub_count];
                    //
                    parament->UnitId = get_buffer_number(line, &index);         //�ϥΪ� MAGIC_UNIT ��ID
                    parament->Attrib = get_buffer_number(line, &index);         //���MAGIC_BREAK��ӧ��ܤ�V,��MAGIC_UNIT�O�_�ݭn���ܤ�V
                    parament->ox = get_buffer_number(line, &index);
                    parament->oy = get_buffer_number(line, &index);
                    parament->oz = get_buffer_number(line, &index);             //�y�а��t
                    parament->Dir = get_buffer_number(line, &index);            //��V���t...�b�ӲզX�ĪG��...��unit����V�O�_�ݭn���A���վ�(�̦h32��V  0--32)
                    parament->SleepTime = get_buffer_number(line, &index);      //�e�m���ݮɶ�
                    parament->SurvialTime = get_buffer_number(line, &index);    //�ͦs�ɶ�(-1��ܪ��O�Ӫk�N�ե�|�λ��s�b)
                    parament->DirLockNum = get_buffer_number(line, &index);     //��V�ƥ�
                    parament->MoveStep = get_buffer_number(line, &index);       //��ܸӪk�N�ե󪺳̦h���ʨB�ƥ�
                    //
                    sub_count ++;
                }                
                break;
            }
            //
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    //�O�ҳ̫�@��..�椸��..�ƾڦ�Ū�X��..
    if (NULL != data)
    {
        data->lBreakParamentBegin = g_GameMagicParamentStackUseNum;
        data->UnitNum = sub_count;
        g_GameMagicParamentStackUseNum += sub_count;
        sub_count = 0;
    }    
    
    if(file_buf) free(file_buf);
    return 0;

error:
    return -1;
}
//-------------------------------------------------------------------------
//  �]�mMAGIC_UNIT �ƾ�
//-------------------------------------------------------------------------
//�X�{�ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG   GetMagicUnitAppearImgId(SLONG lIndex)
{
    return g_GameMagicUnit[lIndex].AppearImgId;
}
//�L�{�ʵe
SLONG   GetMagicUnitProcImgId(SLONG lIndex)
{
    return g_GameMagicUnit[lIndex].ProcImagId;
}
//�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG   GetMagicUnitDisAppearImgId(SLONG lIndex)    
{
    return g_GameMagicUnit[lIndex].DisAppearImgId;
}
//��V�ƾ�
SLONG   GetMagicUnitDirNum(SLONG lIndex) 
{
    return g_GameMagicUnit[lIndex].DirNum;
}
//�B�ʪ��y��
SLONG   GetMagicUnitPath(SLONG lIndex)     
{
    return g_GameMagicUnit[lIndex].Path;
}
//�ͦs���覡
SLONG   GetMagicUnitSurvial(SLONG lIndex)     
{
    return g_GameMagicUnit[lIndex].Survial;
}
//�W�Ϫ��ĪG
SLONG   GetMagicUnitDrawEff(SLONG lIndex)
{
    return g_GameMagicUnit[lIndex].DrawEff;
}
//��������������
SLONG   GetMagicUnitStop(SLONG lIndex)
{
    return g_GameMagicUnit[lIndex].Stop;
}
//���ʪ��t��
double  GetMagicUnitSpeed(SLONG lIndex)
{
    return g_GameMagicUnit[lIndex].Speed;
}
//-------------------------------------------------------------------------
//  �k�N�ե󪺬��}���
//-------------------------------------------------------------------------
//----
//�q�Ϊ��]�k���}������
//----
SLONG   BreakMagic_CommonBreak( SLONG skill_no, SLONG npc_no, SLONG type, SLONG dest_x, SLONG dest_y, SLONG dest_no)
{
    SLONG   break_no;
    SLONG   skill_level;
    SLONG   dx, dy, dz;
    SLONG   break_count = 0;
    //
    SetBreakMagicPartsCount(0);
    //
    dx = dest_x;
    dy = dest_y;
    dz = 0;
    if (dest_no >=0)
    {
        //�p�G���ؼ�npc�ؼЮy�аϥؼ�npc����m
        //
        LOCK_CHARACTER(dest_no);
        GetCharacterPosition(npc_no, &dx, &dy, &dz);
        UNLOCK_CHARACTER(dest_no);
    }
    //
    LOCK_CHARACTER(npc_no);
    skill_level = GetCharacterSpecialSkillLevel(npc_no, skill_no);
    UNLOCK_CHARACTER(npc_no);
    //
    switch (type)
    {
    case MAGIC_BREAK_TYPE_SELF:
        break_no = GetSkillSelfBreakId(skill_no, skill_level);    
        break;
    case MAGIC_BREAK_TYPE_EFF:
        break_no = GetSkillEffBreakId(skill_no, skill_level);    
        break;
    case MAGIC_BREAK_TYPE_TAG:        
    default:
        break_no = GetSkillTagBreakId(skill_no, skill_level);
        break;
    }
    //
    break_count = 0;
    if (break_no >=0 && break_no < MAX_MAGIC_BREAK)
    {
        break_count = MagicBreakProc(break_no, skill_no, skill_level, npc_no, 
                                     dest_x, dest_y, 0, dest_no);
    }
    //
    SetBreakMagicPartsCount(break_count);
    //
    return break_count;
}


//----
//  ���󬵶}�@�Ǫk�N�ĪG��������
//  
//  break_no    :   ���}�������s��
//  npc_no      :   ���檺npc�s��
//  dest_x      :   �ؼЮy��
//  dest_y
//  dest_npc    :   �ؼ�npc(�M�ؼЮy�Ь۹�,,�p�G�S�ؼ�npc�N�ϥΥؼ�npc���y��,,�p�G�S���жǤJ-1)
//  
//  ��^        ;   ���}������ƥ�
//----
SLONG   MagicBreakProc(SLONG break_no, SLONG skill_no, SLONG skill_level, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_z, SLONG dest_npc)
{
    SLONG   i;
    SLONG   break_count=0;
    SLONG   count = 0;    
    SLONG   para_begin;
    SLONG   sx, sy, sz;
    SLONG   npc_x, npc_y, npc_z;
    SLONG   break_x = 0, break_y = 0, break_z = 0;
    SLONG   break_dir = 0;
    SLONG   in_of_pos[3];
    float   break_angle;
    //
    //
    LOCK_CHARACTER(npc_no);
    GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
    UNLOCK_CHARACTER(npc_no);
    //�p����I..�M�ؼЪ�.����
    in_of_pos[0] = dest_x - npc_x;
    in_of_pos[1] = dest_y - npc_y;
    in_of_pos[2] = dest_z - npc_z;
    //
    break_dir = Vertex2Dir32(in_of_pos);
    break_angle = (float)(PI * 2 * break_dir / 32);
    //
    break_count = g_GameMagicBreak[break_no].UnitNum;
    //�O�b�ؼ�..���}���лx
    if (g_GameMagicBreak[break_no].Attrib & MAGIC_BREAK_ATTRIB_TAG_BREAK)
    {
        sx = dest_x;
        sy = dest_y;
        sz = dest_z;
    }
    else
    {
        sx = npc_x;
        sy = npc_y;
        sz = npc_z;
    }
    break_x = sx + (SLONG)(g_GameMagicBreak[break_no].ox * g_32dir_rotation[break_dir][0] - 
                              g_GameMagicBreak[break_no].oy * g_32dir_rotation[break_dir][1]);
    break_y = sy + (SLONG)(g_GameMagicBreak[break_no].ox * g_32dir_rotation[break_dir][1] + 
                              g_GameMagicBreak[break_no].oy * g_32dir_rotation[break_dir][0]);    
    break_z = sz + g_GameMagicBreak[break_no].oz;
    //
    count = 0;
    for (i=0; i<break_count; i++)
    {
        para_begin = g_GameMagicBreak[break_no].lBreakParamentBegin;
        if (MagicUnitBreak( &g_GameMagicParamentStack[para_begin+i], count,
                        npc_no, dest_npc, skill_no, skill_level, 
                        break_x, break_y, break_z, npc_x, npc_y, npc_z,break_angle))
            count ++;
    }
    //
    return count;
}

//----
//  �@���]�k�椸���}���L�{
//  TPOS_MAGIC_BREAK_PARAMETER  :   �ѼƧi�D.unit ���}���@�ǳ]�w
//  BreakNo                     :   �ϥΪ�g_GameMagicBreak���s��
//  npc_no                      :   �ޯ઺�����
//  tag_npc                     :   �ޯ઺�ؼ�npc
//  skill                       :   �ϥΪ��ޯ�
//  skill_level                 :   �ϥΪ��ޯ઺����
//  x,y,z                       :   �y��..��ӪkĬ�ե󪺮y��
//  dir                         :   ��V�̦h����V���O32
//----
SLONG   MagicUnitBreak(TPOS_MAGIC_BREAK_PARAMETER *p_para, SLONG BreakNo, 
                        SLONG npc_no, SLONG tag_npc, SLONG Skill,SLONG SkillLevel,
                        SLONG x, SLONG y, SLONG z, SLONG npc_x, SLONG npc_y, SLONG npc_z,
                        float angle)
{
    float   sin_rotate, cos_rotate;
    float   sin_vector, cos_vector;    
    float   rotate_angle;
    SLONG   orig_x, orig_y, orig_z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   dx, dy, dz;
    SLONG   tox, toy, toz;
    SLONG   ox, oy, oz;
    SLONG   dir_change = 0;
    SLONG   fact_dir;
    SLONG   img_dir, img_max_dir;
    SLONG   stop_mask;
    SLONG   rand_angle;
    SLONG   ret = 0;
    //
    //1.������vMAGIC_UNIT �����ƾڨ�MAGIC_PART��
    SetBreakMagicPartMagicUnit(BreakNo, &g_GameMagicUnit[p_para->UnitId]);
    //2.�p��Ӫk�N�椸����ڤ�V
    dir_change = 0;
    if (p_para->Attrib & MAGIC_UNIT_ATTRIB_DIR_CHANGE)
    {
        dir_change = 1;
    }
    //
    rotate_angle = (float)(PI * 2 * p_para->Dir / 32);
    if (dir_change)
    {
        rotate_angle += angle;
    }
    //3.�]�m�W�[��magic_part���W�Ϯy��
    tox = p_para->ox ;
    toy = p_para->oy ;
    toz = p_para->oz ;    
    //�����y���H���лx
    if (p_para->Attrib & MAGIC_UNIT_ATTRIB_COOR_RAND)
    {
        //
        rand_angle = rand() % 360;
        //
        tox = (SLONG)(p_para->oy * cos (rand_angle * PI * 2 / 360 ));
        toy = (SLONG)(p_para->oy * sin (rand_angle * PI * 2 / 360 ));
        toz = p_para->oz;
    }    
    //
    ox = tox;
    oy = toy;
    oz = toz;        
    //
    if (dir_change)
    {
        if (p_para->DirLockNum > 0)
        {
            //
            fact_dir = (SLONG)(rotate_angle / (PI *2 ) * p_para->DirLockNum+0.5);
            //
            rotate_angle = (float)((PI *2 ) * fact_dir / p_para->DirLockNum);
        }
        sin_rotate = (float)(sin(PI * 2 - rotate_angle));
        cos_rotate = (float)(cos(PI * 2 - rotate_angle));
        //�p����઺sin cos 
        //
        ox = (SLONG)(tox * cos_rotate - 
                    toy * sin_rotate);
        oy = (SLONG)(tox * sin_rotate + 
                    toy * cos_rotate);
        oz = (SLONG)toz;
    }
    //
    //
    orig_x = x + ox;
    orig_y = y + oy;
    orig_z = z + oz;
    //�P�w�k�N�ե󪺬��}�I��ؼ��I�O�_������
    stop_mask = g_GameMagicUnit[p_para->UnitId].Stop;
    if (IsPixelLineThrough(npc_x, npc_y, orig_x, orig_y, stop_mask) )
    {
        //    
        SetBreakMagicPartOrigPosition(BreakNo, orig_x, orig_y, orig_z);
        SetBreakMagicPartCurrPosition(BreakNo, orig_x, orig_y, orig_z);
        //�]�m�]�k�ե󪺲��ʥؼ�
        //....�ݭn�ھڸӪk�N�ե�path ..�]�m�����ʪ��ؼЦ�m
        switch (GetMagicUnitPath(p_para->UnitId))
        {
        case MAGIC_PATH_LINE://�u�ʸ��|..�N�O���]�k����O���Ӫ��u����...
            //
            sin_vector = (float)(sin(PI /2 - rotate_angle));
            cos_vector = (float)(cos(PI /2 - rotate_angle));
            //        
            dx = (SLONG)(p_para->MoveDist * cos_vector);
            dy = (SLONG)(p_para->MoveDist * sin_vector);
            dz = 0;
            //
            dest_x = orig_x + dx;
            dest_y = orig_y + dy;
            dest_z = orig_z + dz;
            //
            break;
        case MAGIC_PATH_UP:
            //
            dest_x = orig_x;
            dest_y = orig_y;
            dest_z = orig_z + p_para->MoveDist;
            break;            
        default:
            dest_x = orig_x;
            dest_y = orig_y;
            dest_z = orig_z;
            break;
        }
        //�]�m���󬵶}����V
        img_max_dir = g_GameMagicUnit[p_para->UnitId].DirNum;
        img_dir = (SLONG)(img_max_dir * rotate_angle / (PI * 2) + 0.5);
        if (img_dir>=img_max_dir)
        {
            // bug here  ... if exec this 
            img_dir = img_max_dir -1;
        }
        //
        SetBreakMagicPartImgDir(BreakNo, img_dir);
        //
        SetBreakMagicPartDestPosition(BreakNo, dest_x, dest_y, dest_z);
        //�]�m�I�k��
        SetBreakMagicPartSourceNo(BreakNo, npc_no);
        //�]�m�����ؼ�
        SetBreakMagicPartTargetNo(BreakNo, tag_npc);
        //�]�m�]�k����W...�ޯ�
        SetBreakMagicPartSkillIndex(BreakNo, Skill);
        SetBreakMagicPartSkillLevel(BreakNo, SkillLevel);
        //�M�ե��ݩʬ������ƾڶ�...���󥻥ͨ��欰����������
        SetBreakMagicPartState(BreakNo, MAGIC_STATE_SLEEP);
        //�]�m���󪺥�v�ɶ�
        SetBreakMagicPartSleepTick(BreakNo, p_para->SleepTime);
        //�]�m���󪺥ͦs�ɶ�
        SetBreakMagicPartLifeTick(BreakNo, p_para->SurvialTime);
        //DelayTick  ...?
        //�]�m�]�k�ե�Z���}�l��m��..�B��
        SetBreakMagicPartStep(BreakNo, 0);    
        //�q�{�]�m�W�Ϫ����ɬ���...�b�]�k���󪺥ͩR�g�����h...�ʺA�]�w..MAGIC_PART������
        SetBreakMagicPartObjectIndex(BreakNo, -1);
        SetBreakMagicPartImageID(BreakNo, INVALID_OBJECT_ID);
        SetBreakMagicPartImageFrame(BreakNo, 0);
        //�����ݭn���..�k�N�ե�..�q�{sleep...
        SetBreakMagicPartFlag(BreakNo, 1);
        //
        ret = 1;
    }    
    return ret;
}

//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------




