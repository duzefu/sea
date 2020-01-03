/*
**	NetGE_Magic.cpp 
**	magic part functions.
**
**	Jack, 2003.1.24.
*/
#include "NetGE_MainFunc.h"

 

/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
TPOS_MAGIC_PART		ZoneMagicPart[MAX_GAME_MAGIC_PART];
TPOS_MAGIC_PART		BreakMagicPart[MAX_BREAK_MAGIC_PART];
SLONG				g_lMaxBreakMagicParts = 0;
TPOS_MAGIC_PIPE		g_MagicPipe;
//
FNBREAKMAGIC	l_BreakMagicFunction[MAX_GAME_SKILL_BASES];
/************************************************************************************************************/
/* MAGIC PART BASE FUNCTIONS                                                                                */
/*  �t�ιw���w�q�� MAGIC_PART �Ʋժ��ƭ�                                                                    */
/************************************************************************************************************/
void	SetZoneMagicPartFlag(SLONG lIndex, SLONG lFlag)
{
	ZoneMagicPart[lIndex].Flag = lFlag;
}

SLONG	GetZoneMagicPartFlag(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].Flag;
}

void	SetZoneMagicPartTail(SLONG lIndex, SLONG lTail)
{
	ZoneMagicPart[lIndex].Tail = lTail;
}

SLONG	GetZoneMagicPartTail(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].Tail;
}

void	SetZoneMagicPartNext(SLONG lIndex, SLONG lNext)
{
	ZoneMagicPart[lIndex].Next = lNext;
}

SLONG	GetZoneMagicPartNext(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].Next;
}

void	SetZoneMagicPartSkillIndex(SLONG lIndex, SLONG lSkillIndex)
{
	ZoneMagicPart[lIndex].SkillIndex = lSkillIndex;
}

SLONG	GetZoneMagicPartSkillIndex(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].SkillIndex;
}

void	SetZoneMagicPartSkillLevel(SLONG lIndex, SLONG SkillLevel)
{
	ZoneMagicPart[lIndex].SkillLevel = SkillLevel;
}

SLONG	GetZoneMagicPartSkillLevel(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].SkillLevel;
}

void	SetZoneMagicPartState(SLONG lIndex, SLONG lState)
{
	ZoneMagicPart[lIndex].State = lState;
}

SLONG	GetZoneMagicPartState(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].State;
}

void	SetZoneMagicPartSourceNo(SLONG lIndex, SLONG lNo)
{
	ZoneMagicPart[lIndex].SourceNo = lNo;
}

SLONG	GetZoneMagicPartSourceNo(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].SourceNo;
}

void	SetZoneMagicPartTargetNo(SLONG lIndex, SLONG lNo)
{
	ZoneMagicPart[lIndex].TargetNo = lNo;
}

SLONG	GetZoneMagicPartTargetNo(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].TargetNo;
}

void	SetZoneMagicPartLifeTick(SLONG lIndex, SLONG lTick)
{
	ZoneMagicPart[lIndex].LifeTick = lTick;
}

SLONG	GetZoneMagicPartLifeTick(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].LifeTick;
}

void	SetZoneMagicPartDelayTick(SLONG lIndex, SLONG lTick)
{
	ZoneMagicPart[lIndex].DelayTick = lTick;
}

SLONG	GetZoneMagicPartDelayTick(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].DelayTick;
}

void	SetZoneMagicPartSleepTick(SLONG lIndex, SLONG lTick)
{
	ZoneMagicPart[lIndex].SleepTick = lTick;
}

SLONG	GetZoneMagicPartSleepTick(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].SleepTick;
}

void	SetZoneMagicPartOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneMagicPart[lIndex].OrigX = lX;
	ZoneMagicPart[lIndex].OrigY = lY;
	ZoneMagicPart[lIndex].OrigZ = lZ;
}

void	GetZoneMagicPartOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	if(lX) *lX = ZoneMagicPart[lIndex].OrigX;
	if(lY) *lY = ZoneMagicPart[lIndex].OrigY;
	if(lZ) *lZ = ZoneMagicPart[lIndex].OrigZ;
}

void	SetZoneMagicPartCurrPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneMagicPart[lIndex].CurrX = lX;
	ZoneMagicPart[lIndex].CurrY = lY;
	ZoneMagicPart[lIndex].CurrZ = lZ;
}

void	GetZoneMagicPartCurrPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	if(lX) *lX = ZoneMagicPart[lIndex].CurrX;
	if(lY) *lY = ZoneMagicPart[lIndex].CurrY;
	if(lZ) *lZ = ZoneMagicPart[lIndex].CurrZ;
}

void	SetZoneMagicPartDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneMagicPart[lIndex].DestX = lX;
	ZoneMagicPart[lIndex].DestY = lY;
	ZoneMagicPart[lIndex].DestZ = lZ;
}

void	GetZoneMagicPartDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	if(lX) *lX = ZoneMagicPart[lIndex].DestX;
	if(lY) *lY = ZoneMagicPart[lIndex].DestY;
	if(lZ) *lZ = ZoneMagicPart[lIndex].DestZ;
}

void	SetZoneMagicPartStep(SLONG lIndex, SLONG lStep)
{
	ZoneMagicPart[lIndex].Step = lStep;
}

SLONG	GetZoneMagicPartStep(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].Step;
}

void	SetZoneMagicPartSpeed(SLONG lIndex, double fSpeed)
{
	ZoneMagicPart[lIndex].unit_data.Speed = fSpeed;
}

double	GetZoneMagicPartSpeed(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].unit_data.Speed;
}

void	SetZoneMagicPartVertSpeed(SLONG lIndex, double fVertSpeed)
{
	ZoneMagicPart[lIndex].unit_data.VertSpeed = fVertSpeed;
}
double	GetZoneMagicPartVertSpeed(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].unit_data.VertSpeed;
}



void	SetZoneMagicPartObjectIndex(SLONG lIndex, SLONG lObjectIndex)
{
	ZoneMagicPart[lIndex].ObjectIndex = lObjectIndex;
}

SLONG	GetZoneMagicPartObjectIndex(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].ObjectIndex;
}

void	SetZoneMagicPartImageID(SLONG lIndex, SLONG lID)
{
	ZoneMagicPart[lIndex].ImageID = lID;
}

SLONG	GetZoneMagicPartImageID(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].ImageID;
}

void	SetZoneMagicPartImageFrame(SLONG lIndex, SLONG lFrame)
{
	ZoneMagicPart[lIndex].ImageFrame = lFrame;
}

SLONG	GetZoneMagicPartImageFrame(SLONG lIndex)
{
	return	ZoneMagicPart[lIndex].ImageFrame;
}

void    SetZoneMagicPartImgDir(SLONG lIndex, SLONG lDir)
{
    ZoneMagicPart[lIndex].ImgDir = lDir;
}
SLONG   GetZoneMagicPartImgDir(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].ImgDir;
}
//�X�{�ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG	GetZoneMagicPartAppearImgId(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.AppearImgId;
}
void 	SetZoneMagicPartAppearImgId(SLONG lIndex, SLONG lAppearImgId)
{
    ZoneMagicPart[lIndex].unit_data.AppearImgId = lAppearImgId;
}


//�L�{�ʵe
SLONG	GetZoneMagicPartProcImagId(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.ProcImagId;
}
void 	SetZoneMagicPartProcImagId(SLONG lIndex, SLONG lProcImagId)
{
    ZoneMagicPart[lIndex].unit_data.ProcImagId = lProcImagId;
}
//�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG	GetZoneMagicPartDisAppearImgId(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.DisAppearImgId;
}
void 	SetZoneMagicPartDisAppearImgId(SLONG lIndex, SLONG lDisAppearImgId)
{
    ZoneMagicPart[lIndex].unit_data.DisAppearImgId = lDisAppearImgId;
}
//��V�ƾ�
SLONG	GetZoneMagicPartDirNum(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.DirNum;
}
void 	SetZoneMagicPartDirNum(SLONG lIndex, SLONG lDirNum)
{
    ZoneMagicPart[lIndex].unit_data.DirNum = lDirNum;
}
//�B�ʪ��y��
SLONG	GetZoneMagicPartPath(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.Path;
}
void 	SetZoneMagicPartPath(SLONG lIndex, SLONG lPath)
{
    ZoneMagicPart[lIndex].unit_data.Path = lPath;
}
//�ͦs���覡
SLONG	GetZoneMagicPartSurvial(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.Survial;
}
void 	SetZoneMagicPartSurvial(SLONG lIndex, SLONG lSurvial)
{
    ZoneMagicPart[lIndex].unit_data.Survial = lSurvial;
}
//�W�Ϫ��ĪG
SLONG	GetZoneMagicPartDrawEff(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.DrawEff;
}
void 	SetZoneMagicPartDrawEff(SLONG lIndex, SLONG lDrawEff)
{
    ZoneMagicPart[lIndex].unit_data.DrawEff = lDrawEff;
}
//��������������
SLONG	GetZoneMagicPartStop(SLONG lIndex)
{
    return	ZoneMagicPart[lIndex].unit_data.Stop;
}
void 	SetZoneMagicPartStop(SLONG lIndex, SLONG lStop)
{
    ZoneMagicPart[lIndex].unit_data.Stop = lStop;
}

/************************************************************************************************************/
/* ZONE MAGIC PART FUNCTIONS                                                                                */
/************************************************************************************************************/
//----
//  ��l�� �]�k�ե�
//----
void	InitZoneMagicPart(void)
{
    SLONG   i;

    for(i = 0; i < HEAD_GAME_MAGIC_PART; i++)
    {
		SetZoneMagicPartNext(i, i);
		SetZoneMagicPartTail(i, i);
    }
    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART; i++)
    {
		SetZoneMagicPartFlag(i, 0);
		SetZoneMagicPartNext(i, -1);
    }
}
//----
//  �q�m�]�k�ե�
//----
void	ResetZoneMagicPart(void)
{
    SLONG   i;

    for(i = 0; i < HEAD_GAME_MAGIC_PART; i++)
    {
		SetZoneMagicPartNext(i, i);
		SetZoneMagicPartTail(i, i);
    }
    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART; i++)
    {
		SetZoneMagicPartFlag(i, 0);
		SetZoneMagicPartNext(i, -1);
    }
}
//----
//  �M���]�k�ե󤤪�..�������
//----
void	ClearZoneMagicPartObjectIndex(void)
{
    SLONG   i;

    for(i = HEAD_GAME_MAGIC_PART; i<MAX_GAME_MAGIC_PART;  i++)
    {
        SetZoneMagicPartObjectIndex(i, -1);
    }
}
//----
//  �P�_����magic_part �O�_�w�g�Q�ϥΤF.
//----
SLONG	IsZoneMagicPartUnused(SLONG lIndex)
{
	SLONG	flag;

	flag = GetZoneMagicPartFlag(lIndex);
	return	flag == 0 ? true : false;
}
//----
//  ���o�@�ӪŪ�..magic_part ..������
//----
SLONG	FindUnusedZoneMagicPart(void)
{
    SLONG   i, find_index;

    find_index = -1;
    for(i = HEAD_GAME_MAGIC_PART; i < MAX_GAME_MAGIC_PART; i++)
    {
		if(IsZoneMagicPartUnused(i))
        {
            find_index = i;
            break;
        }
    }
    return find_index;
}
//----
//  �W�[�@�� magic_part �ƾ�
//----
SLONG	AddZoneMagicPart(TPOS_MAGIC_PART *MP)
{
    SLONG   index, tail, map_no = 0;

    index = FindUnusedZoneMagicPart();
    if(index >= 0)
    {
		//
        // Update magic_part's data
		//
		SetZoneMagicPartFlag(index, 1);
        CopyMagicPartData( &ZoneMagicPart[index], MP);

		//
        // Insert this node to circulated-link.
		//
		SetZoneMagicPartNext(index, map_no);
        tail = GetZoneMagicPartTail(map_no);
		SetZoneMagicPartNext(tail, index);
		SetZoneMagicPartTail(map_no, index);
    }
    return index;
}
//----
//  �R���@�� magic_part �ƾ�
//----
void	DeleteZoneMagicPart(SLONG lIndex)
{
    SLONG   p, s, next, map_no = 0;

    s = map_no;
    p = GetZoneMagicPartNext(map_no);
    while(p != map_no)
    {
        if(p == lIndex)
        {
			//
            // Delete this node from circulated-link.
			//
			next = GetZoneMagicPartNext(p);
			SetZoneMagicPartNext(s, next);
            if(next == map_no)
			{
				SetZoneMagicPartTail(map_no, s);
			}

			//
            // Update this node's data.
			//
			SetZoneMagicPartFlag(p, 0);
            break;
        }
        else
        {
            s = p;
            p = GetZoneMagicPartNext(p);
        }
    }
}
//---
//  �N�S���Ϊ�magic_part �h��
//---
void	ReduceVoidZoneMagicPart(void)
{
    SLONG   p, s, next, map_no = 0;

    s = map_no;
    p = GetZoneMagicPartNext(map_no);
    while(p != map_no)
    {
		if(IsZoneMagicPartUnused(p))
        {
			//
            // Delete this node from circulated-link.
			//
			next = GetZoneMagicPartNext(p);
			SetZoneMagicPartNext(s, next);
            if(next == map_no)
			{
				SetZoneMagicPartTail(map_no, s);
			}

			//
            // Get the new p for the next loop.
			//
            p = GetZoneMagicPartNext(s);
        }
        else
        {
            s = p;
            p = GetZoneMagicPartNext(p);
        }
    }
    return;
}
//---
//  �p��Ӱϰ줤��magic_part ���ƥ�
//---
SLONG	CountZoneMagicPart(void)
{
    SLONG   total, p, map_no = 0;

    total = 0;
    p = GetZoneMagicPartNext(map_no);
    while(p != map_no)
    {
        total ++;
        p = GetZoneMagicPartNext(p);
    }
    return total;
}
//---
//  ����magic_part���ƾ�
//---
void	CopyMagicPartData(TPOS_MAGIC_PART *pDest, TPOS_MAGIC_PART *pSrc)
{
    SLONG   back_flag, back_next;

    back_flag = pDest->Flag;
    back_next = pDest->Next;
    memcpy(pDest, pSrc, sizeof(*pSrc));
    pDest->Flag = back_flag;
    pDest->Next = back_next;
}

//---
//  �W�[�@�Ӭ��}��magic_part�ե�
//---
void	AppendBreakMagicParts(void)
{
    SLONG   i, part_index;

    LOCK_MAGIC(0);
    for(i=0; i<g_lMaxBreakMagicParts; i++)
    {
        part_index = AddZoneMagicPart(&BreakMagicPart[i]);
    }
    UNLOCK_MAGIC(0);
}
//---
//  �`������magic_part�ե�
//---
void	LoopZoneMagicPartFrame(SLONG p)
{
	SLONG	image_id, total_frames;
	SLONG	frame;

	image_id = GetZoneMagicPartImageID(p);
	total_frames = GetObjectImageTotalFrames(image_id);
	frame = GetZoneMagicPartImageFrame(p);
	frame ++;
	if(frame >= total_frames)
		frame = 0;
	SetZoneMagicPartImageFrame(p, frame);
}
//---
//  �����̫�@�V����
//---
SLONG	OverZoneMagicPartFrame(SLONG p)
{
	SLONG	image_id, total_frames, frame;

	image_id = GetZoneMagicPartImageID(p);
	total_frames = GetObjectImageTotalFrames(image_id);
	frame = GetZoneMagicPartImageFrame(p);
	frame ++;
	if(frame < total_frames)
	{
		SetZoneMagicPartImageFrame(p, frame);
		return	FALSE;
	}
	return	TRUE;
}
//---
//  �����̫�@�V����..��^�V���H��
//---
SLONG	KeyPlayZoneMagicPartFrame(SLONG p)
{
	SLONG	image_id, total_frames;
	SLONG	frame;
	SLONG	result;

	image_id = GetZoneMagicPartImageID(p);
	total_frames = GetObjectImageTotalFrames(image_id);
	frame = GetZoneMagicPartImageFrame(p);
	frame ++;
	if(frame < total_frames)
	{
		SetZoneMagicPartImageFrame(p, frame);
	}

	if(frame == 0)
		result = MAGIC_KEY_FRAME_HEAD;
	else if(frame == total_frames / 2)
		result = MAGIC_KEY_FRAME_HALF;
	else if(frame == total_frames - 1)
		result = MAGIC_KEY_FRAME_TAIL;
	else if(frame == total_frames)
		result = MAGIC_KEY_FRAME_OVER;
	else
		result = MAGIC_KEY_FRAME_NONE;

	return	result;
}

//---
//  �ǳ��]�k�ե��z���ݭn���H��
//  ....�p�G�঳...��k�N�ե󪺹��ɧ��ܨ�..�������ʵe(���}�ʵe)
//---
void	PrepareZoneMagicPartForExplode(SLONG p)
{
	SLONG	image_id;
    //�ե󪺬��}�L�{..����ե󪺮����ʵe
    image_id = GetZoneMagicPartDisAppearImgId(p);
    SetZoneMagicPartState(p, MAGIC_STATE_EXPLODE);
    SetZoneMagicPartImageID(p, image_id);
    SetZoneMagicPartImageFrame(p, 0); 
    // mark by lijun 2003-05-06
    /*
	SLONG	image_id;

	SetZoneMagicPartState(p, MAGIC_STATE_EXPLODE);
	image_id = GetZoneMagicPartExplodeImageID(p);
	SetZoneMagicPartImageID(p, image_id);
	SetZoneMagicPartImageFrame(p, 0);
    */	
}
//---
//  �ǳ��]�k�ե󲾰ʪ��H��
//---
void	PrepareZoneMagicPartForShift(SLONG p)
{
	SLONG	image_id;
    //
	SetZoneMagicPartState(p, MAGIC_STATE_SHIFT);
	//�p�G���X�{���ʵe�ݭn������X�{�ʵe...
	image_id = GetZoneMagicPartAppearImgId(p);
	if (image_id == INVALID_OBJECT_ID)
	{
	    image_id = GetZoneMagicPartProcImagId(p);
	}
	//
	SetZoneMagicPartImageID(p, image_id);
	SetZoneMagicPartImageFrame(p, 0);
	//
    // mark by lijun 2003-05-06
    /*
	SLONG	image_id;
    //
	SetZoneMagicPartState(p, MAGIC_STATE_SHIFT);
	image_id = GetZoneMagicPartShiftImageID(p);
	SetZoneMagicPartImageID(p, image_id);
	SetZoneMagicPartImageFrame(p, 0);
    */	
}
/************************************************************************************************************/
/* MAGIC PIPE FUNCTIONS                                                                                     */
/************************************************************************************************************/
void	SetMagicPipeDestNo(SLONG lDestNo)
{
	g_MagicPipe.lDestNo = lDestNo;
}

SLONG	GetMagicPipeDestNo(void)
{
	return	g_MagicPipe.lDestNo;
}


/************************************************************************************************************/
/* BREAK MAGIC PART FUNCTIONS                                                                               */
/************************************************************************************************************/
void	SetBreakMagicPartsCount(SLONG lCounts)
{
	g_lMaxBreakMagicParts = lCounts;
}

SLONG	GetBreakMagicPartsCount(void)
{
	return	g_lMaxBreakMagicParts;
}

void	SetBreakMagicPartFlag(SLONG lIndex, SLONG lFlag)
{
	BreakMagicPart[lIndex].Flag = lFlag;
}

SLONG	GetBreakMagicPartFlag(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].Flag;
}

void	SetBreakMagicPartSkillIndex(SLONG lIndex, SLONG lSkillIndex)
{
	BreakMagicPart[lIndex].SkillIndex = lSkillIndex;
}

SLONG	GetBreakMagicPartSkillIndex(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].SkillIndex;
}

void	SetBreakMagicPartSkillLevel(SLONG lIndex, SLONG SkillLevel)
{
	BreakMagicPart[lIndex].SkillLevel = SkillLevel;
}

SLONG	GetBreakMagicPartSkillLevel(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].SkillLevel;
}



void	SetBreakMagicPartState(SLONG lIndex, SLONG lState)
{
	BreakMagicPart[lIndex].State = lState;
}

SLONG	GetBreakMagicPartState(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].State;
}

void	SetBreakMagicPartSourceNo(SLONG lIndex, SLONG lNo)
{
	BreakMagicPart[lIndex].SourceNo = lNo;
}

SLONG	GetBreakMagicPartSourceNo(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].SourceNo;
}

void	SetBreakMagicPartTargetNo(SLONG lIndex, SLONG lNo)
{
	BreakMagicPart[lIndex].TargetNo = lNo;
}

SLONG	GetBreakMagicPartTargetNo(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].TargetNo;
}

void	SetBreakMagicPartLifeTick(SLONG lIndex, SLONG lTick)
{
	BreakMagicPart[lIndex].LifeTick = lTick;
}

SLONG	GetBreakMagicPartLifeTick(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].LifeTick;
}

void	SetBreakMagicPartDelayTick(SLONG lIndex, SLONG lTick)
{
	BreakMagicPart[lIndex].DelayTick = lTick;
}

SLONG	GetBreakMagicPartDelayTick(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].DelayTick;
}

void	SetBreakMagicPartSleepTick(SLONG lIndex, SLONG lTick)
{
	BreakMagicPart[lIndex].SleepTick = lTick;
}

SLONG	GetBreakMagicPartSleepTick(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].SleepTick;
}

void	SetBreakMagicPartOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	BreakMagicPart[lIndex].OrigX = lX;
	BreakMagicPart[lIndex].OrigY = lY;
	BreakMagicPart[lIndex].OrigZ = lZ;
}

void	GetBreakMagicPartOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	if(lX) *lX = BreakMagicPart[lIndex].OrigX;
	if(lY) *lY = BreakMagicPart[lIndex].OrigY;
	if(lZ) *lZ = BreakMagicPart[lIndex].OrigZ;
}

void	SetBreakMagicPartCurrPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	BreakMagicPart[lIndex].CurrX = lX;
	BreakMagicPart[lIndex].CurrY = lY;
	BreakMagicPart[lIndex].CurrZ = lZ;
}

void	GetBreakMagicPartCurrPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	if(lX) *lX = BreakMagicPart[lIndex].CurrX;
	if(lY) *lY = BreakMagicPart[lIndex].CurrY;
	if(lZ) *lZ = BreakMagicPart[lIndex].CurrZ;
}

void	SetBreakMagicPartDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	BreakMagicPart[lIndex].DestX = lX;
	BreakMagicPart[lIndex].DestY = lY;
	BreakMagicPart[lIndex].DestZ = lZ;
}

void	GetBreakMagicPartDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	if(lX) *lX = BreakMagicPart[lIndex].DestX;
	if(lY) *lY = BreakMagicPart[lIndex].DestY;
	if(lZ) *lZ = BreakMagicPart[lIndex].DestZ;
}

void	SetBreakMagicPartStep(SLONG lIndex, SLONG lStep)
{
	BreakMagicPart[lIndex].Step = lStep;
}

SLONG	GetBreakMagicPartStep(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].Step;
}

void	SetBreakMagicPartSpeed(SLONG lIndex, double fSpeed)
{
	BreakMagicPart[lIndex].unit_data.Speed = fSpeed;
}
double	GetBreakMagicPartSpeed(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].unit_data.Speed;
}

void	SetBreakMagicPartVertSpeed(SLONG lIndex, double fVertSpeed)
{
	BreakMagicPart[lIndex].unit_data.VertSpeed = fVertSpeed;
}
double	GetBreakMagicPartVertSpeed(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].unit_data.VertSpeed;
}


void	SetBreakMagicPartObjectIndex(SLONG lIndex, SLONG lObjectIndex)
{
	BreakMagicPart[lIndex].ObjectIndex = lObjectIndex;
}

SLONG	GetBreakMagicPartObjectIndex(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].ObjectIndex;
}

void	SetBreakMagicPartImageID(SLONG lIndex, SLONG lID)
{
	BreakMagicPart[lIndex].ImageID = lID;
}

SLONG	GetBreakMagicPartImageID(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].ImageID;
}

void	SetBreakMagicPartImageFrame(SLONG lIndex, SLONG lFrame)
{
	BreakMagicPart[lIndex].ImageFrame = lFrame;
}

SLONG	GetBreakMagicPartImageFrame(SLONG lIndex)
{
	return	BreakMagicPart[lIndex].ImageFrame;
}

void    SetBreakMagicPartImgDir(SLONG lIndex, SLONG lDir)
{
    BreakMagicPart[lIndex].ImgDir = lDir;
}
SLONG   GetBreakMagicPartImgDir(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].ImgDir;
}

//---
//  MAGIC_UNIT ����
//---
//�X�{�ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG	GetBreakMagicPartAppearImgId(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.AppearImgId;
}
void 	SetBreakMagicPartAppearImgId(SLONG lIndex, SLONG lAppearImgId)
{
    BreakMagicPart[lIndex].unit_data.AppearImgId = lAppearImgId;
}
//�L�{�ʵe
SLONG	GetBreakMagicPartProcImagId(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.ProcImagId;
}
void 	SetBreakMagicPartProcImagId(SLONG lIndex, SLONG lProcImagId)
{
    BreakMagicPart[lIndex].unit_data.ProcImagId = lProcImagId;
}
//�����ʵe (�S���Ӱʵe �� -1) ����.�b����ʵe���ɭ�..���|���ӹL�{
SLONG	GetBreakMagicPartDisAppearImgId(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.DisAppearImgId;
}
void 	SetBreakMagicPartDisAppearImgId(SLONG lIndex, SLONG lDisAppearImgId)
{
    BreakMagicPart[lIndex].unit_data.DisAppearImgId = lDisAppearImgId;
}
//��V�ƾ�
SLONG	GetBreakMagicPartDirNum(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.DirNum;
}
void 	SetBreakMagicPartDirNum(SLONG lIndex, SLONG lDirNum)
{
    BreakMagicPart[lIndex].unit_data.DirNum = lDirNum;
}
//�B�ʪ��y��
SLONG	GetBreakMagicPartPath(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.Path;
}
void 	SetBreakMagicPartPath(SLONG lIndex, SLONG lPath)
{
    BreakMagicPart[lIndex].unit_data.Path = lPath;
}
//�ͦs���覡
SLONG	GetBreakMagicPartSurvial(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.Survial;
}
void 	SetBreakMagicPartSurvial(SLONG lIndex, SLONG lSurvial)
{
    BreakMagicPart[lIndex].unit_data.Survial = lSurvial;
}
//�W�Ϫ��ĪG
SLONG	GetBreakMagicPartDrawEff(SLONG lIndex)
{
    return	BreakMagicPart[lIndex].unit_data.DrawEff;
}
void 	SetBreakMagicPartDrawEff(SLONG lIndex, SLONG lDrawEff)
{
    BreakMagicPart[lIndex].unit_data.DrawEff = lDrawEff;
}
//��������������
SLONG	GetBreakMagicPartStop(SLONG lIndex)    
{
    return	BreakMagicPart[lIndex].unit_data.Stop;
}
void 	SetBreakMagicPartStop(SLONG lIndex, SLONG lStop)
{
    BreakMagicPart[lIndex].unit_data.Stop = lStop;
}
//����MAGIC_PART����TPOS_MAGIC_UNIT�l��
void    SetBreakMagicPartMagicUnit(SLONG lIndex, TPOS_MAGIC_UNIT *p_unit)
{
    memcpy(&BreakMagicPart[lIndex].unit_data,p_unit,sizeof(BreakMagicPart[lIndex].unit_data));
}
//----
//  ���]�k�ե󪺤�V..���ܨ�..�~����ɪ���V
//----
SLONG   MagicDirToImgDir(SLONG lMagicDir, SLONG MaxDir)
{
    SLONG   dir8[8] = {4,3,2,1,0,7,6,4};
    SLONG   dir16[16] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9};
    SLONG   dir32[32] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,
                         0,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17}; 
    switch(MaxDir)
    {
    case 8:
        return dir8[lMagicDir];
        break;
    case 16:
        return dir16[lMagicDir];
        break;
    case 32:
        return dir32[lMagicDir];
        break;
    }
    return lMagicDir;
}
/*************************************************************************/
/* BREAK MAGIC FUNCTIONS                                                 */
/*************************************************************************/
void	InitBreakMagicFunctions(void)
{
	SLONG	i;

	memset(l_BreakMagicFunction, 0, sizeof(l_BreakMagicFunction));
	for(i=0; i<MAX_GAME_SKILL_BASES; i++)
	{
	    // mark by lijun 2003-05-06
		//l_BreakMagicFunction[i] = DummyBreakMagicFunction;
		l_BreakMagicFunction[i] = BreakMagic_CommonBreak;
	}
}


void	SetBreakMagicFunction(SLONG lSkillNo, FNBREAKMAGIC pFunc)
{
	if(lSkillNo < 0 || lSkillNo >= MAX_GAME_SKILL_BASES)
		return;

	if(pFunc)
	{
		l_BreakMagicFunction[lSkillNo] = pFunc;
	}
}


void	ExecBreakMagic(SLONG lSkillNo, SLONG lSrcNo, SLONG lType, SLONG lDestX, SLONG lDestY, SLONG lDestNo)
{
	if(lSkillNo >= 0 && lSkillNo < MAX_GAME_SKILL_BASES) 
	{
		l_BreakMagicFunction[lSkillNo](lSkillNo, lSrcNo, lType, lDestX, lDestY, lDestNo);
	}
}

