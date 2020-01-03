/*
**	NetGE_Doing.cpp 
**	character doing functions.
**
**	Jack, 2003.1.7
*/
#include "NetGE_MainFunc.h"


/************************************************************************************************************/
/* STRUCTS & DEFINS                                                                                         */
/************************************************************************************************************/
//------------
//����v����T
//------------
#define MAX_OBJECT_TYPES        33      //�̦h���������
#define MAX_OBJECT_IMAGES       4096    //�C�����󪺳̦h�ƥ�

#define	MAX_CHARACTER_FILES				512		// Max character files of the game.
#define MAX_CHARACTER_ACTIONS			28		//�C��NPC�H�����ʧ@�ƶq
#define MAX_CHARACTER_ACTIONS_BLOCK     3       //�̦h���ʧ@�ּƥ�
#define MAX_SEA_CHARACTER_FILES			512     //���WNPC��㦳���̦h���ɼƥ�
#define MAX_SEA_CHARACTER_ACTIONS		2       //���Wnpc��㦳���̦h���A

//
// NPC's file informations:
// Include file image id associated with every action of a npc.
//
typedef struct  tagCHARACTER_FILE_INFO
{
    SLONG   id[MAX_CHARACTER_ACTIONS_BLOCK][MAX_CHARACTER_ACTIONS];	// image file id    
} CHARACTER_FILE_INFO, *LPCHARACTER_FILE_INFO;


//
//�������vNPC���M���A�Mcak���ɪ��������Y
//
typedef struct  tagSEA_CHARACTER_FILE_INFO
{
    SLONG   id[MAX_SEA_CHARACTER_ACTIONS];	//image file id
    SLONG   walk_type;              //���vnpc���樫������( 0 sail_walk , 1 normal_walk )
    SLONG   track_id;               //�������y������
} SEA_CHARACTER_FILE_INFO, *LPSEA_CHARACTER_FILE_INFO;


//
// Object image frames information
//
typedef struct tagOBJECT_IMAGE_INFO
{
    SLONG   frames;     //���󪺴V��
} OBJECT_IMAGE_INFO, *LPOBJECT_IMAGE_INFO;


/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
static	SLONG   (*l_DoCharacterDoingSomething[MAX_CHARACTER_DOING_KINDS]) (SLONG lIndex);
static	void    (*l_ChangeCharacterDoingSomething[MAX_CHARACTER_DOING_KINDS]) (SLONG lIndex, SLONG lDoingKind, SLONG lDoingStep, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
static  SLONG   l_SkillDoingKindMapping[MAX_CHARACTER_DOING_KINDS];
//
static	UCHR    l_CharacterDoingPriority[MAX_CHARACTER_DOING_KINDS][MAX_CHARACTER_DOING_KINDS];

static	CHARACTER_FILE_INFO		l_CharacterFileInfo[MAX_CHARACTER_FILES];
static	SEA_CHARACTER_FILE_INFO l_SeaCharacterFileInfo[MAX_SEA_CHARACTER_FILES];
static	OBJECT_IMAGE_INFO		l_ObjectImageInfo[MAX_OBJECT_TYPES][MAX_OBJECT_IMAGES];

/************************************************************************************************************/
/* CHARACTER FRAME CONTROL FUNCTIONS                                                                        */
/************************************************************************************************************/
//
void    DirLoopCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames, dir_frame;
	SLONG	dir, frame;
    
    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
    dir_frame ++;
	if(dir_frame >= dir_frames * MAX_NPC_STEP_COUNT)
		dir_frame = 0;
	SetCharacterDirFrame(lIndex, dir_frame);

	dir = GetCharacterDir(lIndex);
	frame =  dir * dir_frames + dir_frame / MAX_NPC_STEP_COUNT;
	SetCharacterFrame(lIndex, frame);

	return;
}

//�ݭn��^����V��
SLONG   DirKeyLoopCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   key_frame_type;
	SLONG	dir_frame, dir, frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

    key_frame_type = NPC_KEY_FRAME_NONE;

	dir_frame = GetCharacterDirFrame(lIndex);
	dir_frame ++;
	if(dir_frame >= dir_frames * MAX_NPC_STEP_COUNT)
	{
		dir_frame = 0;
		key_frame_type = NPC_KEY_FRAME_HEAD;
	}
	else if(dir_frame == dir_frames * MAX_NPC_STEP_COUNT / 2)
	{
		key_frame_type = NPC_KEY_FRAME_HALF;
	}
	SetCharacterDirFrame(lIndex, dir_frame);

	dir = GetCharacterDir(lIndex);
	frame = dir * dir_frames + dir_frame / MAX_NPC_STEP_COUNT;
	SetCharacterFrame(lIndex, frame);

    return  key_frame_type;
}
//�P�_��̫�@�V����
SLONG   DirTailCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   frame_flag;
	SLONG	dir_frame, dir, frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

    frame_flag = NPC_KEY_FRAME_NONE;
	dir_frame = GetCharacterDirFrame(lIndex);
	if(dir_frame < dir_frames * MAX_NPC_STEP_COUNT - 1)
	{
		dir_frame ++;
		dir = GetCharacterDir(lIndex);
		frame = dir * dir_frames + dir_frame / MAX_NPC_STEP_COUNT;
		SetCharacterDirFrame(lIndex, dir_frame);
		SetCharacterFrame(lIndex, frame);
	}
	else
	{
		frame_flag = NPC_KEY_FRAME_TAIL;
	}

    return  frame_flag;
}
//��ʵe�����Ĥ@�V
void    DirHeadCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
	SLONG	dir, frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	SetCharacterDirFrame(lIndex, 0);
	dir = GetCharacterDir(lIndex);
    frame = dir * dir_frames;
	SetCharacterFrame(lIndex, frame);
}


//����ʵe��^�ʵe��e�V����m
SLONG   DirHalfCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   frame_flag, dir_frame;
	SLONG	dir, frame;

    frame_flag = NPC_KEY_FRAME_NONE;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
	if(dir_frame < dir_frames * MAX_NPC_STEP_COUNT - 1)
	{
		dir_frame ++;
		SetCharacterDirFrame(lIndex, dir_frame);

		dir = GetCharacterDir(lIndex);
		frame = dir * dir_frames + dir_frame / MAX_NPC_STEP_COUNT;
		SetCharacterFrame(lIndex, frame);

		if(dir_frame == dir_frames * MAX_NPC_STEP_COUNT / 2)
		{
			frame_flag = NPC_KEY_FRAME_HALF;
		}
	}
	else
	{
		frame_flag = NPC_KEY_FRAME_TAIL;
	}
    return  frame_flag;
}
//����ʵe��^�ʵe��e�V����m
//!!!���p�ʵe�u���@�V���ܷ|��bug ..!
SLONG   DirCharacterFrame(SLONG lIndex, SLONG no_play_frame)
{
    SLONG   id, frames, dir_frames;
    SLONG   frame_flag, dir_frame;
	SLONG	dir, frame;

    frame_flag = NPC_KEY_FRAME_NONE;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
	if(dir_frame < dir_frames * MAX_NPC_STEP_COUNT - 1)
	{
		dir_frame ++;
		SetCharacterDirFrame(lIndex, dir_frame);

		dir = GetCharacterDir(lIndex);
		frame = dir * dir_frames + dir_frame / MAX_NPC_STEP_COUNT;
		SetCharacterFrame(lIndex, frame);
	    if (dir_frame == 0)
	    {
		    frame_flag = NPC_KEY_FRAME_HEAD;
	    }		
        else if ((dir_frame == dir_frames - no_play_frame) && (0 != no_play_frame))  //���ۦ@4�V
        {
            frame_flag = NPC_KEY_FRAME_BACK;
        }			    
		else if(dir_frame == dir_frames * MAX_NPC_STEP_COUNT / 2)
		{
			frame_flag = NPC_KEY_FRAME_HALF;
		}
	}
	else if(dir_frame == (dir_frames * MAX_NPC_STEP_COUNT - 1))
	{
		frame_flag = NPC_KEY_FRAME_TAIL;
	}
    return  frame_flag;
}

//���`�ʪ��`������ʵe
void    DirFastLoopCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
	SLONG	dir, frame, dir_frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
    dir_frame ++;
    if(dir_frame  >= dir_frames)
        dir_frame = 0;
	SetCharacterDirFrame(lIndex, dir_frame);

	dir = GetCharacterDir(lIndex);
    frame = dir * dir_frames + dir_frame;
	SetCharacterFrame(lIndex, frame);
}
//���V������ʵe
void    DirSkipLoopCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
	SLONG	dir, frame, dir_frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
    dir_frame += 2;
    if(dir_frame  >= dir_frames)
        dir_frame = 0;
	SetCharacterDirFrame(lIndex, dir_frame);

	dir = GetCharacterDir(lIndex);
    frame = dir * dir_frames + dir_frame;
	SetCharacterFrame(lIndex, frame);
}
//���V����ʵe.�|��^�ʵe��e����m
SLONG   DirFastKeyLoopCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   key_frame_type;
	SLONG	dir, frame, dir_frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

    key_frame_type = NPC_KEY_FRAME_NONE;

	dir_frame = GetCharacterDirFrame(lIndex);
    dir_frame ++;
    if(dir_frame >= dir_frames)
    {
        dir_frame = 0;
        key_frame_type = NPC_KEY_FRAME_HEAD;
    }
	SetCharacterDirFrame(lIndex, dir_frame);

	dir = GetCharacterDir(lIndex);
    frame = dir * dir_frames + dir_frame;
	SetCharacterFrame(lIndex, frame);

    return  key_frame_type;
}
//���`����ʵe...��̫�@�V���ɭ�..�|��^�@�ӭ�
SLONG   DirFastTailCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   frame_flag;
	SLONG	dir, frame, dir_frame;

    frame_flag = NPC_KEY_FRAME_NONE;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
    if(dir_frame < dir_frames - 1)
    {
        dir_frame ++;

		dir = GetCharacterDir(lIndex);
        frame = dir * dir_frames + dir_frame;
		SetCharacterFrame(lIndex, frame);
    }
    else
    {
        frame_flag = NPC_KEY_FRAME_TAIL;
    }
	SetCharacterDirFrame(lIndex, dir_frame);

    return  frame_flag;
}

//���`����ʵe..�b������..�������ɭԷ|��^�@�ӭ�
SLONG   DirFastHalfCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   frame_flag;
	SLONG	dir, frame, dir_frame;

    frame_flag = NPC_KEY_FRAME_NONE;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(lIndex);
    if(dir_frame < dir_frames - 1)
    {
        dir_frame ++;
		SetCharacterDirFrame(lIndex, dir_frame);

		dir = GetCharacterDir(lIndex);
        frame = dir * dir_frames + dir_frame;
		SetCharacterFrame(lIndex, frame);

        if(dir_frame == dir_frames / 2)
        {
            frame_flag = NPC_KEY_FRAME_HALF;
        }
    }
    else
    {
        frame_flag = NPC_KEY_FRAME_TAIL;
    }

    return  frame_flag;
}

//�s����ϥΪ��ʵe�������
SLONG   DirSequentialCharacterFrame(SLONG lIndex)
{
    SLONG   id, frames, dir_frames;
    SLONG   key_frame_type;
	SLONG	dir, frame, dir_frame;

    id = GetCharacterImageID(lIndex);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = frames / NPC_DIRS;

    key_frame_type = NPC_KEY_FRAME_NONE;

	dir_frame = GetCharacterDirFrame(lIndex);
    dir_frame ++;
    if(dir_frame == dir_frames - 4)   //���ۦ@4�V
    {
        key_frame_type = NPC_KEY_FRAME_BACK;
    }
    else if(dir_frame >= dir_frames-1) //�T�w���b�̫�V
    {
        dir_frame = dir_frames-1;
        key_frame_type = NPC_KEY_FRAME_TAIL;
    }
    else if(dir_frame == dir_frames / 2)
    {
        key_frame_type = NPC_KEY_FRAME_HALF;
    }
	SetCharacterDirFrame(lIndex, dir_frame);

	dir = GetCharacterDir(lIndex);
    frame = dir * dir_frames + dir_frame;
	SetCharacterFrame(lIndex, frame);

    return  key_frame_type;
}


SLONG	ClockwiseLoopCharacterDir(SLONG dir)
{
    switch(dir)
    {
    case NPC_UP:			return NPC_RIGHT_UP;
    case NPC_RIGHT_UP:		return NPC_RIGHT;
    case NPC_RIGHT:			return NPC_RIGHT_DOWN;
    case NPC_RIGHT_DOWN:	return NPC_DOWN;
    case NPC_DOWN:			return NPC_LEFT_DOWN;
    case NPC_LEFT_DOWN:     return NPC_LEFT;
    case NPC_LEFT:          return NPC_LEFT_UP;
    case NPC_LEFT_UP:       return NPC_UP;
    default:                return NPC_LEFT_DOWN;
    }
}


SLONG	AntiClockwiseLoopCharacterDir(SLONG dir)
{
    switch(dir)
    {
    case NPC_RIGHT_UP:		return NPC_UP;
    case NPC_RIGHT:			return NPC_RIGHT_UP;
    case NPC_RIGHT_DOWN:	return NPC_RIGHT;
    case NPC_DOWN:			return NPC_RIGHT_DOWN;
    case NPC_LEFT_DOWN:		return NPC_DOWN;
    case NPC_LEFT:			return NPC_LEFT_DOWN;
    case NPC_LEFT_UP:       return NPC_LEFT;
    case NPC_UP:			return NPC_LEFT_UP;
    default:                return NPC_RIGHT_DOWN;
    }
}


SLONG   ApproachCharacterDir(SLONG dx,SLONG dy)
{
    double k;

    //NPC have 8 dirs    &&    GEO_AXIS_Y = - SCR_AXIS_Y !!!
    //
    //In geometry coordinates, if we set x+ is 0 degree, so we have the following datas:
    //dir           degree-range        tan() range
    //----------    ---------------     ---------------------------------------
    //RIGHT         (-22.5, 22.5 )      (-0.4142,  0.4142)
    //RIGHT_UP      ( 22.5, 67.5 )      ( 0.4142,  2.4142)
    //UP            ( 67.5, 112.5)      ( 2.4142, +MAX   ) ## ( -MAX,  -2.4142)
    //LEFT_UP       (112.5, 157.5)      (-2.4142, -0.4142)
    //LEFT          (157.5, 202.5)      (-0.4142,  0.4142)
    //LEFT_DOWN     (202.5, 247.5)      ( 0.4142,  2.4142)
    //DOWN          (247.5, 292.5)      ( 2.4142, +MAX   ) ## ( -MAX,  -2.4142)
    //RIGHT_DOWN    (292.5, 337.5)      (-2.4142, -0.4142)
    //

    //We can simply change our screen coordinates to geometry coordinates by ...
    dy = -dy;

    //Now we do it as geometry coordinates.
    if(dx > 0)
    {
        k = (double)dy/(double)dx;  // math axis y = - screen axis y
        if( k<-2.4142) return NPC_DOWN;
        if( k>=-2.4142 && k<-0.4142) return NPC_RIGHT_DOWN;
        if( k>=-0.4142 && k<0.4142) return NPC_RIGHT;
        if( k>=0.4142  && k<2.4142) return NPC_RIGHT_UP;
        //if( k>=2.4142) return NPC_UP;
        return NPC_UP;
    }
    else if(dx < 0)
    {
        k = (double)dy/(double)dx;
        if( k<-2.4142) return NPC_UP;
        if( k>=-2.4142 && k<-0.4142) return NPC_LEFT_UP;
        if( k>=-0.4142 && k<0.4142) return NPC_LEFT;
        if( k>=0.4142  && k<2.4142) return NPC_LEFT_DOWN;
        //if( k>=2.4142) return NPC_DOWN;
        return NPC_DOWN;
    }
    else
    {
        if(dy > 0)  return NPC_UP;
        else        return NPC_DOWN;
    }
}

/************************************************************************************************************/
/* CHARACTER DOING ACTION FUNCTIONS                                                                         */
/************************************************************************************************************/
/*
SLONG   GetIdleAction(SLONG is_fight)
{
    SLONG   action;

    switch(is_fight)
    {
    case FALSE:
        action = AC_WAIT_0;
        break;
    case TRUE:
        action = AC_FIGHT_WAIT;
        break;
    default:
        action = AC_WAIT_0;
        break;
    }
    return  action;
}


SLONG   GetSpecialIdleAction(SLONG is_fight)
{
    SLONG   action;

    switch(is_fight)
    {
    case FALSE:
        action = AC_WAIT_1;
        break;
    case TRUE:
        action = AC_FIGHT_WAIT;
        break;
    default:
        action = AC_WAIT_0;
        break;
    }
    return  action;
}


SLONG   GetRunAction(SLONG is_fight)
{
    SLONG   action;

    switch(is_fight)
    {
    case FALSE:
        action = AC_RUN;
        break;
    case TRUE:
        action = AC_FIGHT_RUN;
        break;
    default:
        action = AC_RUN;
        break;
    }
    return  action;
}


SLONG   GetSequentialAttackAction(SLONG attack_step)
{
    SLONG   action;

    switch(attack_step)
    {
    case 1: action = AC_SPECIAL_0; break;   //��1��
    case 2: action = AC_SPECIAL_1; break;   //��2��
    case 3: action = AC_SPECIAL_2; break;   //��3��
    case 4: action = AC_SPECIAL_3; break;   //��4��
    case 5: action = AC_SPECIAL_4; break;   //��5��
    default:action = AC_SPECIAL_0; break;
    }
    return  action;
}

SLONG	GetMagicAction(void)
{
	return	AC_MAGIC;
}
*/
SLONG   GetSequentialAttackAction(SLONG attack_step)
{
    SLONG   action;

    switch(attack_step)
    {
    case 0: 
        action = AC_SPECIAL_0; 
        break;   //��1��
    case 1: 
        action = AC_SPECIAL_1; 
        break;   //��2��
    case 2: 
        action = AC_SPECIAL_2; 
        break;   //��3��
    case 3: 
        action = AC_SPECIAL_3; 
        break;   //��4��
    case 4: 
        action = AC_SPECIAL_4; 
        break;   //��5��
    default:
        action = AC_SPECIAL_0; 
        break;
    }
    return  action;
}


/************************************************************************************************************/
/* CHARACTER DOING SOMETHING FUNCTIONS                                                                      */
/************************************************************************************************************/
static	SLONG   DummyCharacterDoingNothing(SLONG lIndex)
{
	// Do nothing here.
    return ACTION_RETURN_PROC;
}
static  void    DummyChangeCharacterDoingSomething(SLONG lIndex,SLONG lDoingKind, SLONG lDoingStep, SLONG d1, SLONG d2, SLONG d3, SLONG d4,SLONG d5)
{

}
void	InitCharacterDoingSomethingFunction(void)
{
	SLONG	i;
	SLONG   skill_no;

	for(i=0; i<MAX_CHARACTER_DOING_KINDS; i++)
	{
		l_DoCharacterDoingSomething[i] = DummyCharacterDoingNothing;
        l_ChangeCharacterDoingSomething[i] = DummyChangeCharacterDoingSomething;
        l_SkillDoingKindMapping[i] = DOING_KIND_SKILL_ACTION;
	}
    //
    skill_no = MAGIC_NO_JOIN_TEAM;            //�ն�
    skill_no = MAGIC_NO_LEAVE_TEAM;           //����
    skill_no = MAGIC_NO_TRADE;                //���
    skill_no = MAGIC_NO_FOLLOW;               //���H
    skill_no = MAGIC_NO_IDENTIFY;             //ų�w
    //
    //land magic no defines -----------------------------------------------------
    skill_no = MAGIC_NO_WALK;                 //�樫
    skill_no = MAGIC_NO_MUSE;                 //�߷Q
    skill_no = MAGIC_NO_ESCRIME;              //�C�N
    //
    skill_no = MAGIC_NO_SEQUENTIAL_ESCRIME;   //�s��
    l_SkillDoingKindMapping[skill_no] = DOING_KIND_SEQUENTIAL_ATTACK_NPC;
    //
    skill_no = MAGIC_NO_STRONG;               //�j��
    skill_no = MAGIC_NO_DEFENCE;              //���
    //
    skill_no = MAGIC_NO_CLASH;                //�ļ�
    l_SkillDoingKindMapping[skill_no] = DOING_KIND_CLASH;
    //
    skill_no = MAGIC_NO_PENETRABLE_ESCRIME;   //�C��
    skill_no = MAGIC_NO_KNOCK_TO_DIZZY;       //�V�w
    skill_no = MAGIC_NO_FATAL_ESCRIME;        //�����C
    //
    skill_no = MAGIC_NO_SHOOT;                //�g��
    skill_no = MAGIC_NO_SEQUENTIAL_SHOOT;     //�s�g
    skill_no = MAGIC_NO_EYES_SHOOT;           //������
    skill_no = MAGIC_NO_DODGE;                //���{
    skill_no = MAGIC_NO_PENETRABLE_SHOOT;     //��z�u
    skill_no = MAGIC_NO_DOUBLE_SHOOT;         //�����u��
    skill_no = MAGIC_NO_FEET_SHOOT;           //���}
    skill_no = MAGIC_NO_DIFFUSE_SHOOT;        //���g
    //
    skill_no = MAGIC_NO_BOOK_READ;            //Ū��
    skill_no = MAGIC_NO_CURE;                 //�v��
    skill_no = MAGIC_NO_DEFEND_MIRROR;        //���m��
    skill_no = MAGIC_NO_RELIVE;               //�_��
    skill_no = MAGIC_NO_BAPTISM;              //�~§
    skill_no = MAGIC_NO_MAGIC_MIRROR;         //�]�k��
    skill_no = MAGIC_NO_ENRICH_BLOOD;         //�j�ɦ�
    skill_no = MAGIC_NO_INFINITE_KINDNESS;    //�����E��
    //
    skill_no = MAGIC_NO_DARK_STAR;            //�t�P
    skill_no = MAGIC_NO_SLEEP;                //�ίv��
    skill_no = MAGIC_NO_TORTOISE;             //�Q�t��
    skill_no = MAGIC_NO_RESIST;               //���
    skill_no = MAGIC_NO_DARK_BALL;            //�t�y
    skill_no = MAGIC_NO_BEELINE_MAGIC;        //���u�]�k
    skill_no = MAGIC_NO_AZRAEL;               //����
    skill_no = MAGIC_NO_DEVIL;                //�c�]
    //
    skill_no = MAGIC_NO_THONG;                //���@
    skill_no = MAGIC_NO_CIRRUS_TRAP;          //�ý�����
    skill_no = MAGIC_NO_BEAST_TRAP;           //���~��
    skill_no = MAGIC_NO_ERUPTIVE_THONG;       //���@�W�O
    skill_no = MAGIC_NO_RAVEL_TRAP;           //�Ѱ�����
    skill_no = MAGIC_NO_PREDICT;              //�w�P
    skill_no = MAGIC_NO_STONE_TRAP;           //���۳���
    skill_no = MAGIC_NO_PRETEND;              //����
    skill_no = MAGIC_NO_LANDMINE;             //�a�p
    //
    skill_no = MAGIC_NO_DAGGER;               //�P��
    skill_no = MAGIC_NO_BEHIND_DAGGER;        //�I��
    skill_no = MAGIC_NO_STEAL;                //����
    skill_no = MAGIC_NO_UNLOCK;               //�}��
    skill_no = MAGIC_NO_HIDE;                 //����
    skill_no = MAGIC_NO_POISON;               //�U�r
    skill_no = MAGIC_NO_GOLD;                 //����
    skill_no = MAGIC_NO_NEGOTIATE;            //�ͧP
    skill_no = MAGIC_NO_ATTRACT_MONSTER;      //�l�ީǪ�
    skill_no = MAGIC_NO_BOX_TRAP;             //�_�c����
    skill_no = MAGIC_NO_CONTROL_MONSTER;      //�Ǫ�����
    //
    skill_no = MAGIC_NO_CHOP;                 //���
    skill_no = MAGIC_NO_TOXOPHILY;            //�g�b
    skill_no = MAGIC_NO_RELIVE_2;             //�_���G
    skill_no = MAGIC_NO_SUCK_BLOOD;           //�l��
    skill_no = MAGIC_NO_SUCK_MAGIC;           //�l�]
    skill_no = MAGIC_NO_DESTROY_ARMOR;        //����}�a
    skill_no = MAGIC_NO_RELIVE_3;             //�_���T
    skill_no = MAGIC_NO_HIDE_2;               //�����G
    skill_no = MAGIC_NO_FIRE_BALL;            //���y
    skill_no = MAGIC_NO_EXPLODE;              //���z�@
    skill_no = MAGIC_NO_EXPLODE_2;            //���z�G
    skill_no = MAGIC_NO_BREAK_EQUIP;          //���˳�
    skill_no = MAGIC_NO_RECALL;               //�l��
    skill_no = MAGIC_NO_CHANGE_FORM;          //�ܨ�
    skill_no = MAGIC_NO_INSURANCE;            //�O�I
    skill_no = MAGIC_NO_INSURANCE_2;          //�O�I�G
    skill_no = MAGIC_NO_INSURANCE_3;          //�O�I�T
    skill_no = MAGIC_NO_INSURANCE_4;          //�O�I�|
    skill_no = MAGIC_NO_INSURANCE_5;          //�O�I��
    //
    //sea magic no defines -----------------------------------------------------
    skill_no = MAGIC_NO_SEAWALK;              //���W������
    skill_no = MAGIC_NO_SEA_PRETEND;          //���W����
    skill_no = MAGIC_NO_ARMOUR_PIERCING_BALL; //��Ҽu
    skill_no = MAGIC_NO_LINK_BALL;            //��u
    skill_no = MAGIC_NO_BURNT_BALL;           //�U�N�u
    skill_no = MAGIC_NO_EMANATORY_BALL;       //���u
    skill_no = MAGIC_NO_REPAIR_BOAT;          //�ײz
}

void	SetCharacterDoingSomethingFunction(SLONG lDoingKind, FNDOING pFunc)
{
	if(lDoingKind >= 0 && lDoingKind < MAX_CHARACTER_DOING_KINDS)
	{
		l_DoCharacterDoingSomething[lDoingKind] = pFunc;
	}
}

SLONG   ExecCharacterDoingSomething(SLONG lIndex, SLONG lDoingKind)
{
	if(lDoingKind >= 0 && lDoingKind < MAX_CHARACTER_DOING_KINDS)
	{
		return l_DoCharacterDoingSomething[lDoingKind](lIndex);
	}
	//
	return ACTION_RETURN_FAIL;
}
void    SetChangeCharacterDoingSomethingFun(SLONG lIndex, FNCHANGEDOING pFunc)
{
	if(lIndex >= 0 && lIndex < MAX_CHARACTER_DOING_KINDS)
	{
		l_ChangeCharacterDoingSomething[lIndex] = pFunc;
	}
}
void    ExecChangeCharacterDoingSomethingFun(SLONG lIndex,SLONG lDoingKind, SLONG lDoingStep, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
	if(lDoingKind >= 0 && lDoingKind < MAX_CHARACTER_DOING_KINDS)
	{
		l_ChangeCharacterDoingSomething[lDoingKind](lIndex,lDoingKind,lDoingStep,d1,d2,d3,d4,d5);
	}

}
SLONG   GetSkillNeedDoingKind(SLONG lIndex)
{
    return l_SkillDoingKindMapping[lIndex];
}
/************************************************************************************************************/
/* CHARACTER DOING PRIORITY FUNCTIONS                                                                       */
/************************************************************************************************************/
void    InitCharacterDoingPriority(void)
{
    SLONG   i, j;

    for(i=0; i<MAX_CHARACTER_DOING_KINDS; i++)
    {
        for(j=0; j<MAX_CHARACTER_DOING_KINDS; j++)
        {
            l_CharacterDoingPriority[i][j] = 1;
        }
    }
}



SLONG   LoadCharacterDoingPriority(CHAR *szFileName)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   cur_doing;
    SLONG   j;

    file_size = load_file_to_buffer((USTR*)szFileName, &file_buf);
    if(file_size < 0)
        return  TTN_ERROR;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;

            //get current doing kind index
            cur_doing = get_buffer_number(line, &index);
            if( cur_doing >= 0 && cur_doing < MAX_CHARACTER_DOING_KINDS )
            {
                for(j = 0; j<MAX_CHARACTER_DOING_KINDS; j++)
                {
                    l_CharacterDoingPriority[cur_doing][j] = (UCHR)get_buffer_number(line, &index);
                }
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


void    FreeCharacterDoingPriority(void)
{
    //nothing to do.
}


SLONG   IsHighPriorityDoingKind(SLONG cur_doing, SLONG new_doing)
{
    if(cur_doing < 0 || cur_doing >= MAX_CHARACTER_DOING_KINDS)
        return  1;
    if(new_doing < 0 || new_doing >= MAX_CHARACTER_DOING_KINDS)
        return  0;
    return  l_CharacterDoingPriority[cur_doing][new_doing];
}


void    DebugLogCharacterDoingPriority(void)
{
#ifdef  DEBUG
    SLONG   i, j;
    USTR    line[1024];
    USTR    temp[128];

    sprintf((char *)print_rec, ";Debug log npc doing pri");
    log_error(1,print_rec);
    sprintf((char *)print_rec, ";--------------------------------------------------------------------------------------");
    log_error(1,print_rec);
    for(i=0; i<MAX_CHARACTER_DOING_KINDS; i++)
    {
        memset(line, 0, 1024);
        sprintf((char *)temp, "%-4d", i);
        strcat((char *)line, (const char *)temp);
        for(j=0; j<MAX_CHARACTER_DOING_KINDS; j++)
        {
            sprintf((char *)temp, "%-4d", l_CharacterDoingPriority[i][j]);
            strcat((char *)line, (const char *)temp);
        }
        log_error(1, line);
    }
    sprintf((char *)print_rec, ";--------------------------------------------------------------------------------------");
    log_error(1,print_rec);
#endif//DEBUG
}


/************************************************************************************************************/
/* CHARACTER FILE INFORMATION FUNCTIONS                                                                     */
/************************************************************************************************************/
void    InitCharacterFileInfo(void)
{
    SLONG   i,j, k;

    for(i=0; i<MAX_CHARACTER_FILES; i++)
    {
        for(j=0; j<MAX_CHARACTER_ACTIONS; j++)
        {
            for (k=0; k<MAX_CHARACTER_ACTIONS_BLOCK; k++)
                l_CharacterFileInfo[i].id[k][j] = INVALID_OBJECT_ID;
        }
    }
}


SLONG   LoadCharacterFileInfo(CHAR *szFileName)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index, val;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, npc_index, action_block;
    SLONG   i, len;

    file_size = load_file_to_buffer((USTR*)szFileName, &file_buf);
    if(file_size < 0)
        goto error;

    //npc_file_info_total = 0;
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            npc_index = get_buffer_number(line, &index);
            action_block = get_buffer_number(line, &index);
            if ((npc_index >= 0 && npc_index < MAX_CHARACTER_FILES ) &&
                (action_block >= 0 && action_block < MAX_CHARACTER_ACTIONS_BLOCK))
            {
                for(i = 0; i<MAX_CHARACTER_ACTIONS; i++)
                {
                    val = get_buffer_number(line, &index);
                    l_CharacterFileInfo[npc_index].id[action_block][i] = (val >= 0) ? MAKE_OBJECT_ID( OBJECT_TYPE_NPC, val ) : INVALID_OBJECT_ID;
                }
                //npc_file_info_total ++;
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}


void    FreeCharacterFileInfo(void)
{
    //nothing to do.
}


void    DebugLogCharacterFileInfo(void)
{
#ifdef  DEBUG
    SLONG   i, j, k, id;
    USTR    temp[32];

    sprintf( ( char* )print_rec, ";Debug log npc info record" );
    log_error( 1, print_rec );
    for(i = 0; i < MAX_CHARACTER_FILES; i ++ )
    {
        for (k=0; k<MAX_CHARACTER_ACTIONS_BLOCK; k++)
        {
            sprintf((char *)print_rec, "%-8d %d-8k", i, k);
            for(j = 0; j < MAX_CHARACTER_ACTIONS; j++ )
            {
                id = l_CharacterFileInfo[i].id[k][j];
                sprintf((char *)temp, "%-8d", (id == INVALID_OBJECT_ID) ? -1 : MAKE_OBJECT_INDEX(id));
                strcat((char *)print_rec, (const char *)temp);
            }
            log_error(1, print_rec);
        }        
    }
#endif//DEBUG
}


SLONG   GetCharacterFileActionImageID( SLONG file_index, SLONG action_block, SLONG action)
{
    if(file_index>=0 && file_index<MAX_CHARACTER_FILES && 
       action >= 0 && action < MAX_CHARACTER_ACTIONS   &&
       action_block >=0 && action_block < MAX_CHARACTER_ACTIONS_BLOCK)
    {
        return  l_CharacterFileInfo[file_index].id[action_block][action];
    }
    return INVALID_OBJECT_ID;
}


/************************************************************************************************************/
/* OBJECT IMAGE FUNCTIONS                                                                                   */
/************************************************************************************************************/
void    InitObjectImageInfo(void)
{
    SLONG   i, j;

    for(i=0; i<MAX_OBJECT_TYPES; i++)
    {
        for(j=0; j<MAX_OBJECT_IMAGES; j++)
        {
            l_ObjectImageInfo[i][j].frames = 1;
        }
    }
}

SLONG   LoadObjectImageInfo(char *szFileName)
{
    PACK_FILE    *fp=NULL;
    SLONG   i,j;
    SLONG   frames;

    //���}����v����T���
    if(NULL == (fp = pack_fopen((const char *)szFileName,"rb")) )
    {
        sprintf((char *)print_rec,"file %s open error", szFileName);
        log_error(1, print_rec);
        return TTN_ERROR;
    }

    //���J����v����T
    for(i=0; i<MAX_OBJECT_TYPES; i++)
    {
        for(j=0; j<MAX_OBJECT_IMAGES; j++)
        {
            pack_fread(&frames, 1, sizeof(SLONG), fp);
            l_ObjectImageInfo[i][j].frames = frames;
        }
    }

    //Ū�����\, �������
    if(fp) pack_fclose(fp);
    return TTN_OK;
}

void    FreeObjectImageInfo(void)
{
    // Do nothing because of no memory allocate.
}

SLONG   GetObjectImageTotalFrames(SLONG id)
{
    SLONG type, index;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
    if(type >= 0 && type < MAX_OBJECT_TYPES && index >= 0 && index < MAX_OBJECT_IMAGES)
        return l_ObjectImageInfo[type][index].frames;
    return  1;
}

void	SetObjectImageTotalFrames(SLONG id, SLONG frames)
{
    SLONG type, index;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
    if(type >= 0 && type < MAX_OBJECT_TYPES && index >= 0 && index < MAX_OBJECT_IMAGES)
	{
		l_ObjectImageInfo[type][index].frames = frames;
	}
}

/************************************************************************************************************/
/* SEA CHARACTER FILE INFORMATIONS                                                                          */
/************************************************************************************************************/
void    InitSeaCharacterFileInfo(void)
{
    SLONG   i,j;
    for(i=0; i<MAX_SEA_CHARACTER_FILES; i++)
    {
        for(j=0; j<MAX_SEA_CHARACTER_ACTIONS; j++)
        {
            l_SeaCharacterFileInfo[i].id[j] = INVALID_OBJECT_ID;
        }
        l_SeaCharacterFileInfo[i].track_id = 0;
        l_SeaCharacterFileInfo[i].walk_type = 0;
    }
}

SLONG   LoadSeaCharacterFileInfo(CHAR *szFileName)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index, val;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, npc_index;
    SLONG   i, len;

    file_size = load_file_to_buffer((USTR*)szFileName, &file_buf);
    if(file_size < 0)
        goto error;
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            npc_index = get_buffer_number(line, &index);
            if( npc_index >= 0 && npc_index < MAX_SEA_CHARACTER_FILES)
            {
                for(i = 0; i<MAX_SEA_CHARACTER_ACTIONS; i++)
                {
                    val = get_buffer_number(line, &index);
                    l_SeaCharacterFileInfo[npc_index].id[i] = (val >= 0) ? MAKE_OBJECT_ID( OBJECT_TYPE_SEANPC, val ) : INVALID_OBJECT_ID;
                }
                //
                val = get_buffer_number(line, &index);
                l_SeaCharacterFileInfo[npc_index].walk_type = val;
                //
                val = get_buffer_number(line, &index);
                l_SeaCharacterFileInfo[npc_index].track_id = val;
                //
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}

void    DebugLogSeaCharacterFileInfo(void)
{
#ifdef  DEBUG
    SLONG   i, j, id;
    USTR    temp[32];

    sprintf( ( char* )print_rec, ";Debug log sea npc info record" );
    log_error( 1, print_rec );
    for(i = 0; i < MAX_SEA_CHARACTER_FILES; i ++ )
    {
        sprintf((char *)print_rec, "%-8d", i);
        for(j = 0; j < MAX_SEA_CHARACTER_ACTIONS; j++ )
        {
            id = l_SeaCharacterFileInfo[i].id[j];
            sprintf((char *)temp, "%-8d", (id == INVALID_OBJECT_ID) ? -1 : MAKE_OBJECT_INDEX(id));
            strcat((char *)print_rec, (const char *)temp);
        }
        log_error(1, print_rec);
    }
#endif//DEBUG
}


SLONG   GetSeaCharacterFileSailType(SLONG file_index)
{
    if(file_index>=0 && file_index<MAX_SEA_CHARACTER_FILES )
    {
        return  l_SeaCharacterFileInfo[file_index].walk_type;
    }
    return -1;
}

SLONG   GetSeaCharacterFileTrackID(SLONG file_index )
{
    if(file_index>=0 && file_index<MAX_SEA_CHARACTER_FILES )
    {
        return  l_SeaCharacterFileInfo[file_index].track_id;
    }
    return -1;
}

SLONG   GetSeaCharacterFileActionImageID(SLONG file_index, SLONG action)
{
    if(file_index>=0 && file_index<MAX_SEA_CHARACTER_FILES 
		&& action >= 0 && action < MAX_SEA_CHARACTER_ACTIONS)
    {
        return  l_SeaCharacterFileInfo[file_index].id[action];
    }
    return INVALID_OBJECT_ID;
}


SLONG   GetOnSeaIdleAction(SLONG fight_flag)
{
    return( AC_SEA_IDLE  );
}

SLONG   GetOnSeaMoveAction(SLONG fight_flag)
{
    return (AC_SEA_WALK);
}


void    DirHeadSeaCharacterFrame(SLONG npc_no, SLONG old_dir)
{
    static  SLONG   frame_temp_frame[NPC_DIRS][NPC_DIRS]=
    {   
      //NPC_UP  ,NPC_DOWN   ,NPC_LEFT   ,NPC_RIGHT  ,NPC_RIGHT_UP   ,NPC_LEFT_DOWN  ,NPC_LEFT_UP    ,NPC_RIGHT_DOWN
        {12     ,8          ,10         ,14         ,13             ,8              ,11             ,0  },//NPC_UP         
        {14     ,4          ,6          ,2          ,0              ,5              ,8              ,3  },//NPC_DOWN       
        {10     ,6          ,8          ,12         ,12             ,7              ,9              ,4  },//NPC_LEFT       
        {14     ,2          ,4          ,0          ,15             ,4              ,14             ,1  },//NPC_RIGHT      
        {14     ,2          ,12         ,15         ,14             ,2              ,12             ,1  },//NPC_RIGHT_UP   
        {10     ,5          ,7          ,2          ,2              ,6              ,8              ,4  },//NPC_LEFT_DOWN  
        {11     ,6          ,9          ,4          ,12             ,8              ,10             ,14 },//NPC_LEFT_UP    
        {14     ,3          ,4          ,1          ,0              ,4              ,8              ,2  },//NPC_RIGHT_DOWN 
    };              
    SLONG   id, frames, dir_frames, dir, frame;

    id = GetCharacterImageID(npc_no);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = (frames-NPC_DIRS*2) / NPC_DIRS;
	SetCharacterDirFrame(npc_no, 0);

	dir = GetCharacterDir(npc_no);
    if( old_dir < 0 )
	{
		frame = dir * dir_frames;
        SetCharacterFrame(npc_no, frame);
	}
    else
    {
        frame = frames - NPC_DIRS * 2 +  frame_temp_frame[old_dir][dir];
		// Jack, add here. [1/29/2003]
        frame = frames - NPC_DIRS * 2 +  frame_temp_frame[old_dir][dir];
		if(frame > frames - 1)
			frame = frames - 1;
		if(frame < 0)
			frame = 0;

        SetCharacterFrame(npc_no, frame);
    }
}


void    DirFastLoopSeaCharacterFrame(SLONG npc_no)
{
    SLONG   id, frames, dir_frames;
	SLONG	dir_frame, dir, frame;

    id = GetCharacterImageID(npc_no);
    frames = GetObjectImageTotalFrames(id);
    dir_frames = (frames-NPC_DIRS*2) / NPC_DIRS;

	dir_frame = GetCharacterDirFrame(npc_no);
    dir_frame ++;
    if(dir_frame  >= dir_frames)
        dir_frame = 0;
	SetCharacterDirFrame(npc_no, dir_frame);

	dir = GetCharacterDir(npc_no);
    frame = dir * dir_frames + dir_frame;
	SetCharacterFrame(npc_no, frame);
}


SLONG   ApproachSeaCharacterDir(FLOAT dir[3])
{
    static  float   sin22 = (float)sin( PI * 22/180);
    static  float   sin66 = (float)sin( PI * 66/180);
    static  float   sin90 = 1.0f;
    static  float   sin_22 = (float)sin( -PI * 22/180);
    static  float   sin_66 = (float)sin( -PI * 66/180);
    static  float   sin_90 = -1.0f;
    //
    if( dir[0] >= 0  )
    {
        if( dir [1] > sin66)
            return SEANPC_DOWN;
        else if( dir [1] > sin22)
            return SEANPC_RIGHT_DOWN;
        else if( dir [1] > sin_22)
            return SEANPC_RIGHT;
        else if( dir [1] > sin_66)
            return SEANPC_RIGHT_UP;
        else 
            return SEANPC_UP;
    }
    else
    {
        if( dir [1] > sin66)
            return SEANPC_DOWN;
        else if( dir [1] > sin22)
            return SEANPC_LEFT_DOWN;
        else if( dir [1] > sin_22)
            return SEANPC_LEFT;
        else if( dir [1] > sin_66)
            return SEANPC_LEFT_UP;
        else 
            return SEANPC_UP;
    }
    return SEANPC_DOWN;
}
//---
//  �ھڤH�������A..���o..�H�����ʧ@����
//---
SLONG   StatuseToActionBlocks(SLONG fight_flag, SLONG block_flag)
{
    if (fight_flag)
    {    
        if (block_flag)
            return CHARACTER_ACTION_BLOCK_WARD;
        else
            return CHARACTER_ACTION_BLOCK_FIGHT;
    }        
    return CHARACTER_ACTION_BLOCK_NORMAL;        
}   
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------
  