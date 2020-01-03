/*
**	NetGE_Character.cpp 
**	Character functions header.
**
**	Jack, 2002.12.9
**
**	Modified by Zhang Zhaohui 2002.12.20
**
**	Modified by Hawke 2003.03.28
**
**	Jack, 2003.5.14.
**		--- Add CareerLevel related functions.
**
*/
#include "NetGE_Mainfunc.h"
 
 

/***********************************************************************/
/* GLOBALS                                                             */
/***********************************************************************/
TPOS_CHARACTER	ZoneCharacter[MAX_CHARACTER_PER_ZONE];



/************************************************************************/
/* FUNCTIONS                                                            */
/************************************************************************/
void	InitAllZoneCharacters(void)
{
	SLONG	i;

	memset(ZoneCharacter, 0, sizeof(ZoneCharacter));
	for(i=0; i<MAX_CHARACTER_PER_ZONE; i++)
	{
		ClearCharacterSkills(i);
	}
}


void	ClearOneCharacter(SLONG lIndex)
{
	memset(&ZoneCharacter[lIndex], 0, sizeof(ZoneCharacter[lIndex]));
	ClearCharacterSkills(lIndex);
}

void	ClearCharacterSkills(SLONG lIndex)
{
	SLONG	i;

	for(i=0; i<MAX_CHARACTER_SKILLS; i++)
	{
		SetCharacterSkillNo(lIndex, i, -1);
		SetCharacterSkillLevel(lIndex, i, 0);
	}
}

SLONG	IsCharacterAvailable(SLONG lIndex)
{
	if(ZoneCharacter[lIndex].Name.MainName[0])
		return	TRUE;
	return	FALSE;
}
/************************************************************************/
/* Set/Get character Name ( ID, MainName, NickName, QQID ).             */
/************************************************************************/
void	SetCharacterType(SLONG lIndex, UHINT uType)
{
	ZoneCharacter[lIndex].Header.Type = uType;
}

UHINT	GetCharacterType(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Header.Type;
}

void	SetCharacterAccount(SLONG lIndex, CHAR *szAccout)
{
	strcpy( ZoneCharacter[lIndex].Name.ID, szAccout );
}

CHAR*	GetCharacterAccount(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Name.ID;
}

void	SetCharacterMainName(SLONG lIndex, CHAR *szMainName)
{
	strcpy( ZoneCharacter[lIndex].Name.MainName, szMainName );		
}

CHAR*	GetCharacterMainName(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Name.MainName;
}

void	SetCharacterNickName(SLONG lIndex, CHAR *szNickName)
{
	strcpy( ZoneCharacter[lIndex].Name.NickName, szNickName );
}

CHAR*	GetCharacterNickName(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Name.NickName;
}

void	SetCharacterQQID(SLONG lIndex, ULONG uID)
{
	ZoneCharacter[lIndex].Name.QQID = uID;
}

ULONG	GetCharacterQQID(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Name.QQID;
}

void	SetCharacterIndex(SLONG lCharIndex, SLONG lIndex)
{
	ZoneCharacter[lCharIndex].Name.Index = lIndex;
}

SLONG	GetCharacterIndex(SLONG lCharIndex)
{
	return	ZoneCharacter[lCharIndex].Name.Index;
}

/************************************************************************/
/*  Set/Get Character Style                                             */
/************************************************************************/

void	SetCharacterPicture(SLONG lIndex, SLONG lPicture)
{
	ZoneCharacter[lIndex].Style.Picture = (char)lPicture;
}

SLONG	GetCharacterPicture(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.Picture;
}

void	SetCharacterColor(SLONG lIndex, SLONG lColor)
{
	ZoneCharacter[lIndex].Style.Color = (char)lColor;
}

SLONG	GetCharacterColor(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.Color;
}

void	SetCharacterEyes(SLONG lIndex, SLONG lEyes)
{
	ZoneCharacter[lIndex].Style.Eyes = (char)lEyes;
}

SLONG	GetCharacterEyes(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.Eyes;
}

void	SetCharacterMouth(SLONG lIndex, SLONG lMouth)
{
	ZoneCharacter[lIndex].Style.Mouth = (char)lMouth;
}

SLONG	GetCharacterMouth(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.Mouth;
}

void	SetCharacterMainNameColor(SLONG lIndex, SLONG lColor)
{
	ZoneCharacter[lIndex].Style.MainNameColor = (char)lColor;
}

SLONG	GetCharacterMainNameColor(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.MainNameColor;
}

void	SetCharacterNickNameColor(SLONG lIndex, SLONG lColor)
{
	ZoneCharacter[lIndex].Style.NickNameColor = (char)lColor;
}

SLONG	GetCharacterNickNameColor(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.NickNameColor;
}

void	SetCharacterMessageColor(SLONG lIndex, SLONG lColor)
{
	ZoneCharacter[lIndex].Style.MessageColor = (char)lColor;
}

SLONG	GetCharacterMessageColor(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.MessageColor;
}

void	SetCharacterTalkBackColor(SLONG lIndex, SLONG lColor)
{
	ZoneCharacter[lIndex].Style.TalkBackColor = (char)lColor;
}

SLONG	GetCharacterTalkBackColor(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.TalkBackColor;
}

void	SetCharacterLogo(SLONG lIndex, ULONG lLogo)
{
	ZoneCharacter[lIndex].Style.Logo = lLogo;
}

ULONG	GetCharacterLogo(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.Logo;
}

void	SetCharacterFileIndex(SLONG lIndex, SLONG lFileIndex)
{
	ZoneCharacter[lIndex].Style.FileIndex = lFileIndex;
}

SLONG	GetCharacterFileIndex(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Style.FileIndex;
}

void	SetCharacterLandFileIndex(SLONG lIndex, SLONG lFileIndex)
{
	ZoneCharacter[lIndex].Style.LandFileIndex = lFileIndex;
}

SLONG	GetCharacterLandFileIndex(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Style.LandFileIndex;
}

void	SetCharacterSeaFileIndex(SLONG lIndex, SLONG lFileIndex)
{
	ZoneCharacter[lIndex].Style.SeaFileIndex = lFileIndex;
}

SLONG	GetCharacterSeaFileIndex(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Style.SeaFileIndex;
}

void	SetCharacterPartRGB(SLONG lIndex, SLONG lPart, ULONG uRGB)
{
	ZoneCharacter[lIndex].Style.PartRGB[lPart] = uRGB;
}

ULONG	GetCharacterPartRGB(SLONG lIndex, SLONG lPart)
{
	return	ZoneCharacter[lIndex].Style.PartRGB[lPart];
}

void	SetCharacterNameColorTicks(SLONG lIndex, ULONG uTicks)
{
	ZoneCharacter[lIndex].Style.NameColorTicks = uTicks;
}

ULONG	GetCharacterNameColorTicks(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Style.NameColorTicks;
}


/************************************************************************/
/* Set/Get Character Position                                           */
/************************************************************************/

void	SetCharacterZoneName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneCharacter[lIndex].Position.ZoneName, szName );
}

CHAR *	GetCharacterZoneName(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.ZoneName;
}

void	SetCharacterPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneCharacter[lIndex].Position.X = lX;
	ZoneCharacter[lIndex].Position.Y = lY;
	ZoneCharacter[lIndex].Position.Z = lZ;
}

void	GetCharacterPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	*lX = ZoneCharacter[lIndex].Position.X;
	*lY = ZoneCharacter[lIndex].Position.Y;
	*lZ = ZoneCharacter[lIndex].Position.Z;
}

void	SetCharacterDir(SLONG lIndex, SLONG lDir)
{
	ZoneCharacter[lIndex].Position.Dir = (UCHAR)lDir;
}

SLONG	GetCharacterDir(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.Dir;
}

void	SetCharacterDirFrame(SLONG lIndex, SLONG lFrame)
{
	ZoneCharacter[lIndex].Position.DirFrame = lFrame;
}

SLONG	GetCharacterDirFrame(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.DirFrame;
}

void	SetCharacterFrame(SLONG lIndex, SLONG lFrame)
{
	ZoneCharacter[lIndex].Position.Frame = lFrame;
}

SLONG	GetCharacterFrame(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.Frame;
}

void	SetCharacterDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneCharacter[lIndex].Position.DestX = lX;
	ZoneCharacter[lIndex].Position.DestY = lY;
	ZoneCharacter[lIndex].Position.DestZ = lZ;
}

void	GetCharacterDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	*lX = ZoneCharacter[lIndex].Position.DestX;
	*lY = ZoneCharacter[lIndex].Position.DestY;
	*lZ = ZoneCharacter[lIndex].Position.DestZ;
}

void	SetCharacterDestID(SLONG lIndex, SLONG uID)
{
	ZoneCharacter[lIndex].Position.DestID = uID;
}

SLONG	GetCharacterDestID(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.DestID;
}

void	SetCharacterOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneCharacter[lIndex].Position.OrigX = lX;
	ZoneCharacter[lIndex].Position.OrigY = lY;
	ZoneCharacter[lIndex].Position.OrigZ = lZ;
}

void	GetCharacterOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	*lX = ZoneCharacter[lIndex].Position.OrigX;
	*lY = ZoneCharacter[lIndex].Position.OrigY;
	*lZ = ZoneCharacter[lIndex].Position.OrigZ;
}

void	SetCharacterOrigID(SLONG lIndex, ULONG uID)
{
	ZoneCharacter[lIndex].Position.OrigID = uID;
}

ULONG	GetCharacterOrigID(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.OrigID;
}

void	SetCharacterStopRadius(SLONG lIndex, SLONG lRadius)
{
	ZoneCharacter[lIndex].Position.StopRadius = lRadius;
}

SLONG	GetCharacterStopRadius(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.StopRadius;
}

void	SetCharacterDialogWithCount(SLONG lIndex, SLONG lCount)
{
	ZoneCharacter[lIndex].Position.DialogWithCount = lCount;
}

SLONG	GetCharacterDialogWithCount(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.DialogWithCount;
}

void	SetCharacterDialogDestIndex(SLONG lIndex, SLONG lDestIndex)
{
	ZoneCharacter[lIndex].Position.DialogDestIndex = lDestIndex;
}

SLONG	GetCharacterDialogDestIndex(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.DialogDestIndex;
}

/************************************************************************/
/* Set/Get Character Speed                                              */
/************************************************************************/

void	SetCharacterMoveSpeed(SLONG lIndex, SLONG lSpeed)
{
	ZoneCharacter[lIndex].Speed.Mspeed = lSpeed;
}

SLONG	GetCharacterMoveSpeed(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Speed.Mspeed;
}

void	SetCharacterShipSpeedX(SLONG lIndex, SLONG lSpeedX)
{
	ZoneCharacter[lIndex].Speed.FSpeedX = lSpeedX;
}

SLONG	GetCharacterShipSpeedX(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Speed.FSpeedX;
}

void	SetCharacterShipSpeedY(SLONG lIndex, SLONG lSpeedY)
{
	ZoneCharacter[lIndex].Speed.FSpeedY = lSpeedY;
}

SLONG	GetCharacterShipSpeedY(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Speed.FSpeedY;
}

void	SetCharacterShipSailSize(SLONG lIndex, SLONG lSize)
{
	ZoneCharacter[lIndex].Speed.SailSize = (UHINT)lSize;
}

SLONG	GetCharacterShipSailSize(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Speed.SailSize;
}

void	SetCharacterShipTurn(SLONG lIndex, SLONG lTurn)
{
	ZoneCharacter[lIndex].Speed.Turn = (UHINT)lTurn;
}

SLONG	GetCharacterShipTurn(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Speed.Turn;
}

void	SetCharacterShipWeight(SLONG lIndex, SLONG lWeight)
{
	ZoneCharacter[lIndex].Speed.Weight = (UHINT)lWeight;
}

SLONG	GetCharacterShipWeight(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Speed.Weight;
}

void	SetCharacterShipDegreeDir(SLONG lIndex, SLONG lDegreeDir)
{
	ZoneCharacter[lIndex].Speed.DegreeDir = lDegreeDir;
}

SLONG	GetCharacterShipDegreeDir(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Speed.DegreeDir;
}

void	SetCharacterShipOldDegreeDir(SLONG lIndex, SLONG lDegreeDir)
{
	ZoneCharacter[lIndex].Speed.OldDegreeDir = lDegreeDir;
}

SLONG	GetCharacterShipOldDegreeDir(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Speed.OldDegreeDir;
}

/************************************************************************/
/* Check/Set Character State 1 ( Fight? Sail? Open Bag? Dead? )         */
/* 設置npc狀態的函數                                                    */
/************************************************************************/
//判斷npc是否在戰鬥狀態
SLONG	IsCharacterOnFightState(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_ON_FIGHT ? true : false);
}
//
void	SetCharacterOnFightState(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_ON_FIGHT;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_ON_FIGHT;
}
//判斷npc是否在格檔狀態
SLONG	IsCharacterOnBlockState(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_ON_BLOCK ? true : false);
}
//
void	SetCharacterOnBlockState(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_ON_BLOCK;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_ON_BLOCK;
}

//判斷npc是否在包裹打開的狀態
SLONG	IsCharacterBagOpened(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_BAG_OPENED ? true : false);
}

void	SetCharacterBagOpened(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_BAG_OPENED;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_BAG_OPENED;
}
//判斷npc是否在海上
SLONG	IsCharacterOnTheSea(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_ON_SEA ? true : false);
}

void	SetCharacterOnTheSea(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_ON_SEA;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_ON_SEA;
}
//判斷npc是否在死亡的狀態
SLONG	IsCharacterOnDeadState(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_IS_DEAD ? true : false);
}

void	SetCharacterOnDeadState(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_IS_DEAD;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_IS_DEAD;
}
//判斷npc是否的防禦加強的狀態
SLONG	IsCharacterOnDefenceState(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_ON_DEFENCE ? true : false);
}

void	SetCharacterOnDefenceState(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_ON_DEFENCE;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_ON_DEFENCE;
}

//判斷npc是否躲避
SLONG	IsCharacterDodge(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_DODGE ? true : false);
}


void	SetCharacterDodge(SLONG lIndex, SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_DODGE;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_DODGE;
}

//格檔(提高npc的格檔機率)
SLONG   IsCharacterOnBlock(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_ON_BLOCK ? true : false);
}
void    SetCharacterOnBlock(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_ON_BLOCK;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_ON_BLOCK;
}

//魔法反彈(有一定類型的法術)
SLONG   IsCharacterMagicRebound(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_MAGIC_REBOUND ? true : false);
}
void    SetCharacterMagicRebound(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_MAGIC_REBOUND;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_MAGIC_REBOUND;
}

//隱形(自己人可見,敵人不可見)
SLONG   IsCharacterShowSubtil(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_SHOW_SUBTIL ? true : false);
}
void    SetCharacterShowSubtil(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_SHOW_SUBTIL;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_SHOW_SUBTIL;
}

//遲緩1(只有在移動的時候..速度變慢,動畫播放速度變慢)
SLONG   IsCharacterSpeedDelay1(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_SPEED_DELAY1 ? true : false);
}
void    SetCharacterSpeedDelay1(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_SPEED_DELAY1;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_SPEED_DELAY1;
}

//遲緩2遲緩2(動畫速度播放加快,移動速度變慢)
SLONG   IsCharacterSpeedDelay2(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_SPEED_DELAY2 ? true : false);
}
void    SetCharacterSpeedDelay2(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_SPEED_DELAY2;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_SPEED_DELAY2;
}

//無敵(人物上圖需要閃爍)
SLONG   IsCharacterWithoutEqual(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_WITHOUT_EQUAL ? true : false);
}
void    SetCharacterWithoutEqual(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_WITHOUT_EQUAL;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_WITHOUT_EQUAL;
}
//黑人狀態
SLONG   IsCharacterBlackNpc(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_BLACK_NPC ? true : false);
}
void    SetCharacterBlackNpc(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_BLACK_NPC;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_BLACK_NPC;
}


//NPC摔倒狀態
SLONG   IsCharacterNpcFaint(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_NPC_FAINT ? true : false);
}
void    SetCharacterNpcFaint(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_NPC_FAINT;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_NPC_FAINT;
}

//NPC爬起來
SLONG   IsCharacterNpcStandUp(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_NPC_STAND_UP ? true : false);
}
void    SetCharacterNpcStandUp(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_NPC_STAND_UP;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_NPC_STAND_UP;
}


//頭昏
SLONG   IsCharacterHeadSleep(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_HEAD_SLEEP ? true : false);
}
void    SetCharacterHeadSleep(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_HEAD_SLEEP;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_HEAD_SLEEP;
}

//睡眠
SLONG   IsCharacterOnSleep(SLONG lIndex)
{
	return ( ZoneCharacter[lIndex].State.BitState & CHARACTER_ON_SLEEP ? true : false);
}
void    SetCharacterOnSleep(SLONG lIndex,SLONG lFlag)
{
	if ( lFlag )
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_ON_SLEEP;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_ON_SLEEP;
}

//判斷npc在停留的狀態
SLONG	IsCharacterOnPauseState(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].State.BitState & CHARACTER_IS_PAUSE ? true : false;
}

void	SetCharacterOnPauseState(SLONG lIndex, SLONG lFlag)
{
	if(lFlag)
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_IS_PAUSE;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_IS_PAUSE;
}
//判斷怪物是否攜帶特定物品
SLONG	IsCharacterOnSpecialItem(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].State.BitState & CHARACTER_SPECIAL_ITEM ? true : false;
}

void	SetCharacterOnSpecialItem(SLONG lIndex, SLONG lFlag)
{
	if(lFlag)
		ZoneCharacter[lIndex].State.BitState |= CHARACTER_SPECIAL_ITEM;
	else
		ZoneCharacter[lIndex].State.BitState &= ~CHARACTER_SPECIAL_ITEM;
}




/************************************************************************/
/* Set/Get Character Property 2                                         */
/*  對一些和狀態相關的數據的npc數據的設定                               */
/************************************************************************/
void	SetCharacterBitState(SLONG lIndex, ULONG uState)
{
	ZoneCharacter[lIndex].State.BitState = uState;
}

ULONG	GetCharacterBitState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BitState;
}

void	SetCharacterReliveTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.ReliveTicks = lTicks;
}

SHINT	GetCharacterReliveTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.ReliveTicks;
}

void	SetCharacterDeadTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.DeadTicks = lTicks;
}

SLONG	GetCharacterDeadTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.DeadTicks;
}

void	SetCharacterDeadAlpha(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.DeadTicks = lTicks;
}

SLONG	GetCharacterDeadAlpha(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.DeadAlpha;
}

void	SetCharacterAttackPantTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.AttackPantTicks = lTicks;
}

SLONG	GetCharacterAttackPantTicks(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.AttackPantTicks;
}

void	SetCharacterAttackPantTotalTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.AttackPantTotalTicks = lTicks;
}

SLONG	GetCharacterAttackPantTotalTicks(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Position.AttackPantTotalTicks;
}

void	SetCharacterDeadState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.DeadState = lState;
}

SHINT	GetCharacterDeadState(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].State.DeadState;
}

void	SetCharacterRightHandMagicState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.RMagicState = lState;
}

SHINT	GetCharacterRightHandMagicState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RMagicState;
}

void	SetCharacterRightHandMagicTotalTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.RMagicTotalTicks = lTicks;
}

SHINT	GetCharacterRightHandMagicTotalTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RMagicTotalTicks;
}

void	SetCharacterRightHandMagicCurrentTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.RMagicCurrentTicks = lTicks;
}

SHINT	GetCharacterRightHandMagicCurrentTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RMagicCurrentTicks;
}

void	SetCharacterHeadSleepState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.HeadSleepState = lState;
}

SHINT	GetCharacterHeadSleepState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadSleepState;
}

void	SetCharacterHeadSleepTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.HeadSleepTicks = lTicks;
}

SHINT	GetCharacterHeadSleepTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadSleepTicks;
}

void	SetCharacterHeadSleepLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.HeadSleepLevel = lLevel;
}

SHINT	GetCharacterHeadSleepLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadSleepLevel;
}

void	SetCharacterHeadDefenceState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.HeadDefenceState = lState;
}

SHINT	GetCharacterHeadDefenceState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadDefenceState;
}

void	SetCharacterHeadDefenceTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.HeadDefenceTicks = lTicks;
}

SHINT	GetCharacterHeadDefenceTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadDefenceTicks;
}

void	SetCharacterHeadDefenceLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.HeadDefenceLevel = lLevel;
}

SHINT	GetCharacterHeadDefenceLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadDefenceLevel;
}

void	SetCharacterHeadMagicState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.HeadMagicState = lState;
}

SHINT	GetCharacterHeadMagicState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadMagicState;
}

void	SetCharacterHeadMagicTimes(SLONG lIndex, SHINT lTimes)
{
	ZoneCharacter[lIndex].State.HeadMagicTimes = lTimes;
}

SHINT	GetCharacterHeadMagicTimes(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadMagicTimes;
}

void	SetCharacterHeadMagicLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.HeadMagicLevel = lLevel;
}

SHINT	GetCharacterHeadMagicLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadMagicLevel;
}

void	SetCharacterHeadBlindState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.HeadBlindState = lState;
}

SHINT	GetCharacterHeadBlindState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadBlindState;
}

void	SetCharacterHeadBlindTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.HeadBlindTicks = lTicks;
}

SHINT	GetCharacterHeadBlindTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadBlindTicks;
}

void	SetCharacterHeadBlindLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.HeadBlindLevel = lLevel;
}

SHINT	GetCharacterHeadBlindLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HeadBlindLevel;
}

void	SetCharacterBodyDodgeState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.BodyDodgeState = lState;
}

SHINT	GetCharacterBodyDodgeState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyDodgeState;
}

void	SetCharacterBodyVirusState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.BodyVirusState = lState;
}

SHINT	GetCharacterBodyVirusState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyVirusState;
}

void	SetCharacterBodyVirusTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.BodyVirusTicks = lTicks;
}

SHINT	GetCharacterBodyVirusTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyVirusTicks;
}

void	SetCharacterBodyVirusLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.BodyVirusLevel = lLevel;
}

SHINT	GetCharacterBodyVirusLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyVirusLevel;
}

void	SetCharacterBodyHideState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.BodyHideState = lState;
}

SHINT	GetCharacterBodyHideState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyHideState;
}

void	SetCharacterBodyHideTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.BodyHideTicks = lTicks;
}

SHINT	GetCharacterBodyHideTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyHideTicks;
}

void	SetCharacterBodyHideLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.BodyHideLevel = lLevel;
}

SHINT	GetCharacterBodyHideLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.BodyHideLevel;
}

void	SetCharacterFootSpeedState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.FootSpeedState = lState;
}

SHINT	GetCharacterFootSpeedState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.FootSpeedState;
}

void	SetCharacterFootSpeedTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.FootSpeedTicks = lTicks;
}

SHINT	GetCharacterFootSpeedTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.FootSpeedTicks;
}

void	SetCharacterFootSpeedLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.FootSpeedLevel = lLevel;
}

SHINT	GetCharacterFootSpeedLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.FootSpeedLevel;
}

/************************************************************************/
/* Set/Get Character Property 3                                         */
/************************************************************************/

void	SetCharacterShipRotateState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.RotateState = lState;
}

SHINT	GetCharacterShipRotateState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RotateState;
}

void	SetCharacterShipRotateTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.RotateTicks = lTicks;
}

SHINT	GetCharacterShipRotateTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RotateTicks;
}

void	SetCharacterShipRotateLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.RotateLevel = lLevel;
}

SHINT	GetCharacterShipRotateLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RotateLevel;
}

void	SetCharacterShipFireState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.FireState = lState;
}

SHINT	GetCharacterShipFireState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.FireState;
}

void	SetCharacterShipFireTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.FireTicks = lTicks;
}

SHINT	GetCharacterShipFireTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.FireTicks;
}

void	SetCharacterShipFireLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.FireLevel = lLevel;
}

SHINT	GetCharacterShipFireLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.FireLevel;
}

void	SetCharacterShipExplodeState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.ExplodeState = lState;
}

SHINT	GetCharacterShipExplodeState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.ExplodeState;
}

void	SetCharacterShipExplodeTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.ExplodeTicks = lTicks;
}

SHINT	GetCharacterShipExplodeTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.ExplodeTicks;
}

void	SetCharacterShipExplodeLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.ExplodeLevel = lLevel;
}

SHINT	GetCharacterShipExplodeLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.ExplodeLevel;
}

void	SetCharacterShipSailHurtState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.SailHurtState = lState;
}

SHINT	GetCharacterShipSailHurtState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.SailHurtState;
}

void	SetCharacterShipRudderHurtState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.RudderHurtState = lState;
}

SHINT	GetCharacterShipRudderHurtState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.RudderHurtState;
}

/************************************************************************/
/* Set/Get Character Property 4                                         */
/************************************************************************/

void	SetCharacterShipPretendState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.PretendState = lState;
}

SHINT	GetCharacterShipPretendState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.PretendState;
}

void	SetCharacterShipPretendOldFileIndex(SLONG lIndex, SHINT lFileIndex)
{
	ZoneCharacter[lIndex].State.PretendOldFileIndex = lFileIndex;
}

SHINT	GetCharacterShipPretendOldFileIndex(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.PretendOldFileIndex;
}

void	SetCharacterShipPretendToFileIndex(SLONG lIndex, SHINT lFileIndex)
{
	ZoneCharacter[lIndex].State.PretendToFileIndex = lFileIndex;
}

SHINT	GetCharacterShipPretendToFileIndex(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.PretendToFileIndex;
}

void	SetCharacterShipHalfDownState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.HalfDownState = lState;
}

SHINT	GetCharacterShipHalfDownState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.HalfDownState;
}

void	SetCharacterShipOctopusState(SLONG lIndex, SHINT lState)
{
	ZoneCharacter[lIndex].State.OctopusState = lState;
}

SHINT	GetCharacterShipOctopusState(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.OctopusState;
}

void	SetCharacterShipOctopusTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].State.OctopusTicks = lTicks;
}

SHINT	GetCharacterShipOctopusTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.OctopusTicks;
}

void	SetCharacterShipOctopusLevel(SLONG lIndex, SHINT lLevel)
{
	ZoneCharacter[lIndex].State.OctopusLevel = lLevel;
}

SHINT	GetCharacterShipOctopusLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].State.OctopusLevel;
}

void	SetCharacterAI(SLONG lIndex, ULONG uAI)
{
	ZoneCharacter[lIndex].AI.AI  = uAI;
}

ULONG	GetCharacterAI(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].AI.AI;
}
void	SetCharacterAIBlock(SLONG lIndex, ULONG uAIBlock)
{
	ZoneCharacter[lIndex].AI.AIBlock  = uAIBlock;
}

ULONG	GetCharacterAIBlock(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].AI.AIBlock;
}

void	SetCharacterTotalOnlineTicks(SLONG lIndex, ULONG uTicks)
{
	ZoneCharacter[lIndex].State.TotalOnlineTicks = uTicks;
}

ULONG	GetCharacterTotalOnlineTicks(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].State.TotalOnlineTicks;
}
/************************************************************************/
/* 一些和控制相關的..根據狀態屬性..判定npc能作莫些事情的函數            */
/************************************************************************/
//判斷npc單強可否移動
SLONG   IsCharacterCanMove(SLONG lIndex)
{
    return  false;
}
//判斷npc當前可否pk
SLONG   IsCharacterCanPk(SLONG lIndex)
{
    return  false;
}
//判斷npc當前可否陸戰
SLONG   IsCharacterCanLandFight(SLONG lIndex)
{
    return  false;
}
//判斷npc當前可否海戰
SLONG   IsCharacterCanSeaFight(SLONG lIndex)
{
    return  false;
}
//判斷npc當前是否需要處於無敵的狀態
SLONG   IsCharacterCanBeHurt(SLONG lIndex)
{
    return  false;
}
//判斷npc可否增加到地圖上
SLONG   IsCharacterCanAddToMap(SLONG lIndex)
{
    return  false;
}
//判斷npc是否需要上圖
SLONG   IsCharacterCanShow(SLONG lIndex)
{
    return  false;
}
//
/************************************************************************/
/* Set/Get Character Strength                                           */
/************************************************************************/

void	SetCharacterFinalStr(SLONG lIndex, UHINT uStr)
{
	ZoneCharacter[lIndex].Property.Str.FinalStr = uStr;
}

UHINT	GetCharacterFinalStr(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Str.FinalStr;
}

void	SetCharacterInitStr(SLONG lIndex, UHINT uStr)
{
	ZoneCharacter[lIndex].Property.Str.InitStr = uStr;
}

UHINT	GetCharacterInitStr(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Str.InitStr;
}

void	SetCharacterLevelUpStr(SLONG lIndex, UHINT uStr)
{
	ZoneCharacter[lIndex].Property.Str.LevUpStr = uStr;
}

UHINT	GetCharacterLevelUpStr(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Str.LevUpStr;
}

void	SetCharacterPointStr(SLONG lIndex, UHINT uStr)
{
	ZoneCharacter[lIndex].Property.Str.PointStr = uStr;
}

UHINT	GetCharacterPointStr(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Str.PointStr;
}

/************************************************************************/
/* Set/Get Character Ins                                                */
/************************************************************************/

void	SetCharacterFinalIns(SLONG lIndex, UHINT uIns)
{
	ZoneCharacter[lIndex].Property.Ins.FinalIns = uIns;
}

UHINT	GetCharacterFinalIns(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Ins.FinalIns;
}

void	SetCharacterInitIns(SLONG lIndex, UHINT uIns)
{
	ZoneCharacter[lIndex].Property.Ins.InitIns = uIns;
}

UHINT	GetCharacterInitIns(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Ins.InitIns;
}

void	SetCharacterLevelUpIns(SLONG lIndex, UHINT uIns)
{
	ZoneCharacter[lIndex].Property.Ins.LevUpIns = uIns;
}

UHINT	GetCharacterLevelUpIns(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Ins.LevUpIns;
}

void	SetCharacterPointIns(SLONG lIndex, UHINT uIns)
{
	ZoneCharacter[lIndex].Property.Ins.PointIns = uIns;
}

UHINT	GetCharacterPointIns(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Ins.PointIns;
}

/************************************************************************/
/* Set/Get Character Wit                                                */
/************************************************************************/

void	SetCharacterFinalWit(SLONG lIndex, UHINT uWit)
{
	ZoneCharacter[lIndex].Property.Wit.FinalWit = uWit;
}

UHINT	GetCharacterFinalWit(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Wit.FinalWit;
}

void	SetCharacterInitWit(SLONG lIndex, UHINT uWit)
{
	ZoneCharacter[lIndex].Property.Wit.InitWit = uWit;
}

UHINT	GetCharacterInitWit(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Wit.InitWit;
}

void	SetCharacterLevelUpWit(SLONG lIndex, UHINT uWit)
{
	ZoneCharacter[lIndex].Property.Wit.LevUpWit = uWit;
}

UHINT	GetCharacterLevelUpWit(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Wit.LevUpWit;
}

void	SetCharacterPointWit(SLONG lIndex, UHINT uWit)
{
	ZoneCharacter[lIndex].Property.Wit.PointWit = uWit;
}

UHINT	GetCharacterPointWit(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Wit.PointWit;
}

/************************************************************************/
/* Set/Get Character Lucky                                              */
/************************************************************************/

void	SetCharacterFinalLucky(SLONG lIndex, UHINT uLucky)
{
	ZoneCharacter[lIndex].Property.Lucky.FinalLucky = uLucky;
}

UHINT	GetCharacterFinalLucky(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Lucky.FinalLucky;
}

void	SetCharacterInitLucky(SLONG lIndex, UHINT uLucky)
{
	ZoneCharacter[lIndex].Property.Lucky.InitLucky = uLucky;
}

UHINT	GetCharacterInitLucky(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Lucky.InitLucky;
}

void	SetCharacterLevelUpLucky(SLONG lIndex, UHINT uLucky)
{
	ZoneCharacter[lIndex].Property.Lucky.LevUpLucky = uLucky;
}

UHINT	GetCharacterLevelUpLucky(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Lucky.LevUpLucky;
}

void	SetCharacterPointLucky(SLONG lIndex, UHINT uLucky)
{
	ZoneCharacter[lIndex].Property.Lucky.PointLucky = uLucky;
}

UHINT	GetCharacterPointLucky(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Lucky.PointLucky;
}

/************************************************************************/
/* Set/Get Character Attack                                             */
/************************************************************************/
void	SetCharacterFinalAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.FinalAtt = uAtt;
}

UHINT	GetCharacterFinalAtt(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Property.Attack.FinalAtt;
}

void	SetCharacterFinalPhysicAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.FinalPhysicAtt = uAtt;
}

UHINT	GetCharacterFinalPhysicAtt(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Property.Attack.FinalPhysicAtt;
}

void	SetCharacterFinalMagicAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.FinalMagicAtt = uAtt;
}

UHINT	GetCharacterFinalMagicAtt(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Property.Attack.FinalMagicAtt;
}

void	SetCharacterFinalSpecAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.FinalSpecAtt = uAtt;
}

UHINT	GetCharacterFinalSpecAtt(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Property.Attack.FinalSpecAtt;
}

void	SetCharacterEquipBaseAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.EquipBaseAtt = uAtt;
}

UHINT	GetCharacterEquipBaseAtt(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.EquipBaseAtt;
}

void	SetCharacterEquipAddedMagicAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.EquipAddedMagicAtt = uAtt;
}

UHINT	GetCharacterEquipAddedMagicAtt(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.EquipAddedMagicAtt;
}

void	SetCharacterEquipAddedSpecAtt(SLONG lIndex, UHINT uAtt)
{
	ZoneCharacter[lIndex].Property.Attack.EquipAddedSpecAtt = uAtt;
}

SLONG	GetCharacterEquipAddedSpecAtt(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.EquipAddedSpecAtt;
}

void	SetCharacterAttribAttRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Attack.AttribAttRatio = uRatio;
}

UHINT	GetCharacterAttribAttRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.AttribAttRatio;
}

void	SetCharacterSkillAttackRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Attack.SkillAttackRatio = uRatio;
}

UHINT	GetCharacterSkillAttackRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.SkillAttackRatio;
}

void	SetCharacterAttackRange(SLONG lIndex, UHINT uRange)
{
	ZoneCharacter[lIndex].Property.Attack.AttackRange = uRange;
}

UHINT	GetCharacterAttackRange(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.AttackRange;
}

void	SetCharacterAttackRate(SLONG lIndex, UHINT uRate)
{
	ZoneCharacter[lIndex].Property.Attack.AttackRate = uRate;
}

UHINT	GetCharacterAttackRate(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.AttackRate;
}

void	SetCharacterSightRange(SLONG lIndex, UHINT uRange)
{
	ZoneCharacter[lIndex].Property.Attack.SightRange = uRange;
}

UHINT	GetCharacterSightRange(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.SightRange;
}

void	SetCharacterFinalExplodeRate(SLONG lIndex, UHINT uRate)
{
	ZoneCharacter[lIndex].Property.Attack.FinalExplodeRate = uRate;
}

UHINT	GetCharacterFinalExplodeRate(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.FinalExplodeRate;
}

void	SetCharacterEquipExplodeRate(SLONG lIndex, UHINT uRate)
{
	ZoneCharacter[lIndex].Property.Attack.EquipExplodeRate = uRate;
}

UHINT	GetCharacterEquipExplodeRate(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.EquipExplodeRate;
}

void	SetCharacterSkillExplodeRate(SLONG lIndex, UHINT uRate)
{
	ZoneCharacter[lIndex].Property.Attack.SkillExplodeRate = uRate;
}

UHINT	GetCharacterSkillExplodeRate(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.SkillExplodeRate;
}

/************************************************************************/
/* Set/Get Character Defance                                            */
/************************************************************************/
void	SetCharacterFinalDefence(SLONG lIndex, UHINT uDefence)
{
	ZoneCharacter[lIndex].Property.Defence.FinalDefence = uDefence;
}

UHINT	GetCharacterFinalDefence(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Property.Defence.FinalDefence;
}

void	SetCharacterBaseDefence(SLONG lIndex, UHINT uDefence)
{
	ZoneCharacter[lIndex].Property.Defence.BaseDefence = uDefence;
}

UHINT	GetCharacterBaseDefence(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.BaseDefence;
}

void	SetCharacterEquipDefence(SLONG lIndex, UHINT uDefence)
{
	ZoneCharacter[lIndex].Property.Defence.EquipDefence = uDefence;
}

UHINT	GetCharacterEquipDefence(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.EquipDefence;
}

void	SetCharacterSkillDefence(SLONG lIndex, UHINT uDefence)
{
	ZoneCharacter[lIndex].Property.Defence.SkillDefence = uDefence;
}

UHINT	GetCharacterSkillDefence(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.SkillDefence;
}

void	SetCharacterSkillDefenceTicks(SLONG lIndex, UHINT uTicks)
{
	ZoneCharacter[lIndex].Property.Defence.SkillDefenceTicks = uTicks;
}

UHINT	GetCharacterSkillDefenceTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.SkillDefenceTicks;
}

void	SetCharacterEquipResistRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Defence.EquipResistRatio = uRatio;
}

UHINT	GetCharacterEquipResistRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.EquipResistRatio;
}

void	SetCharacterFinalResist(SLONG lIndex, UHINT uResist)
{
	ZoneCharacter[lIndex].Property.Defence.FinalResist = uResist;
}

UHINT	GetCharacterFinalResist(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Property.Defence.FinalResist;
}

void	SetCharacterDodgeRate(SLONG lIndex, UHINT uRate)
{
	ZoneCharacter[lIndex].Property.Defence.DodgeRate = uRate;
}

UHINT	GetCharacterDodgeRate(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.DodgeRate;
}

void	SetCharacterParryRate(SLONG lIndex, UHINT uRate)
{
	ZoneCharacter[lIndex].Property.Defence.ParryRate = uRate;
}

UHINT	GetCharacterParryRate(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Defence.ParryRate;
}

/************************************************************************/
/* Set/Get Character Property Point(s)                                  */
/************************************************************************/

void	SetCharacterPropertyPoint(SLONG lIndex, UHINT uPoint)
{
	ZoneCharacter[lIndex].Property.PropertyPoint = uPoint;
}

UHINT	GetCharacterPropertyPoint(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.PropertyPoint;
}

void	AffectCharacterPropertyPoint(SLONG lIndex)
{
	ZoneCharacter[lIndex].Property.Str.LevUpStr += ZoneCharacter[lIndex].Property.Str.PointStr;


}

/************************************************************************/
/* Set/Get Character Exp and Level                                      */
/************************************************************************/

void	SetCharacterExp(SLONG lIndex, ULONG uExp)
{
	ZoneCharacter[lIndex].ExpLev.Exp = uExp;
}

ULONG	GetCharacterExp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].ExpLev.Exp;
}

void	SetCharacterNextExp(SLONG lIndex, ULONG uExp)
{
	ZoneCharacter[lIndex].ExpLev.NextExp = uExp;
}


ULONG	GetCharacterNextExp(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].ExpLev.NextExp;
}

void	SetCharacterLevel(SLONG lIndex, UHINT uLevel)
{
	ZoneCharacter[lIndex].ExpLev.Level = uLevel;
}

UHINT	GetCharacterLevel(SLONG lIndex)
{
	return ZoneCharacter[lIndex].ExpLev.Level;
}

/************************************************************************/
/* Set/Get Character HP and MP                                          */
/************************************************************************/

void	SetCharacterHp(SLONG lIndex, UHINT uHp)
{
	ZoneCharacter[lIndex].HpMp.Hp = uHp;
}

UHINT	GetCharacterHp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.Hp;
}

void	SetCharacterMaxHp(SLONG lIndex, UHINT uMaxHp)
{
	ZoneCharacter[lIndex].HpMp.MaxHp = uMaxHp;
}

UHINT	GetCharacterMaxHp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.MaxHp;
}

void	SetCharacterAttribHp(SLONG lIndex, UHINT uHp)
{
	ZoneCharacter[lIndex].HpMp.AttribHp = uHp;
}

UHINT	GetCharacterAttribHp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.AttribHp;
}

void	SetCharacterLevelUpHp(SLONG lIndex, UHINT uHp)
{
	ZoneCharacter[lIndex].HpMp.LevelUpHp = uHp;
}

UHINT	GetCharacterLevelUpHp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.LevelUpHp;
}

void	SetCharacterEquipHp(SLONG lIndex, UHINT uHp)
{
	ZoneCharacter[lIndex].HpMp.EquipHp = uHp;
}

UHINT	GetCharacterEquipHp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.EquipHp;
}

void	SetCharacterSkillHp(SLONG lIndex, UHINT uHp)
{
	ZoneCharacter[lIndex].HpMp.SkillHp = uHp;
}

UHINT	GetCharacterSkillHp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.SkillHp;
}

void	SetCharacterHpRes(SLONG lIndex, UHINT uRes)
{
	ZoneCharacter[lIndex].HpMp.HpRes = uRes;
}

UHINT	GetCharacterHpRes(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.HpRes;
}

void	SetCharacterMp(SLONG lIndex, UHINT uMp)
{
	ZoneCharacter[lIndex].HpMp.Mp = uMp;
}

UHINT	GetCharacterMp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.Mp;
}

void	SetCharacterMaxMp(SLONG lIndex, UHINT uMaxMp)
{
	ZoneCharacter[lIndex].HpMp.MaxMp = uMaxMp;
}

UHINT	GetCharacterMaxMp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.MaxMp;
}

void	SetCharacterAttribMp(SLONG lIndex, UHINT uMp)
{
	ZoneCharacter[lIndex].HpMp.AttribMp = uMp;
}

UHINT	GetCharacterAttribMp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.AttribMp;
}

void	SetCharacterLevelUpMp(SLONG lIndex, UHINT uMp)
{
	ZoneCharacter[lIndex].HpMp.LevelUpMp = uMp;
}

UHINT	GetCharacterLevelUpMp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.LevelUpMp;
}

void	SetCharacterEquipMp(SLONG lIndex, UHINT uMp)
{
	ZoneCharacter[lIndex].HpMp.EquipMp = uMp;
}

UHINT	GetCharacterEquipMp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.EquipMp;
}

void	SetCharacterSkillMp(SLONG lIndex, UHINT uMp)
{
	ZoneCharacter[lIndex].HpMp.SkillMp = uMp;
}

UHINT	GetCharacterSkillMp(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.SkillMp;
}

void	SetCharacterMpRes(SLONG lIndex, UHINT uRes)
{
	ZoneCharacter[lIndex].HpMp.MpRes = uRes;
}

UHINT	GetCharacterMpRes(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.MpRes;
}

/************************************************************************/
/* Set/Get Character Skill                                              */
/************************************************************************/

void	SetCharacterSkillNo(SLONG lCharIndex, SLONG lSkillIndex, SLONG lSkillNo)
{
	ZoneCharacter[lCharIndex].SkillExp.Skill[lSkillIndex] = (SHINT)lSkillNo;
}

SLONG	GetCharacterSkillNo(SLONG lCharIndex, SLONG lSkillIndex)
{
	return ZoneCharacter[lCharIndex].SkillExp.Skill[lSkillIndex];
}

void	SetCharacterSkillLevel(SLONG lCharIndex, SLONG lSkillIndex, UHINT uLevel)
{
	ZoneCharacter[lCharIndex].SkillExp.Level[lSkillIndex] = uLevel;
}

UHINT	GetCharacterSkillLevel(SLONG lCharIndex, SLONG lSkillIndex)
{
	return ZoneCharacter[lCharIndex].SkillExp.Level[lSkillIndex];
}
//----
//  npc 根據skill_no 和 npc_no  取得對應的skill 的等級..如果..不會..返回 0等級
//----
SLONG   GetCharacterSpecialSkillLevel(SLONG lCharIndex, SLONG lSkillNo)
{
    SLONG   i;
    //
    for (i=0; i<MAX_CHARACTER_SKILLS; i++)
    {
        //
        if (ZoneCharacter[lCharIndex].SkillExp.Skill[i] == lSkillNo )
        {
            return true;
        }
    }    
    return false;
}

/************************************************************************/
/* Set/Get Character Equipment                                          */
/************************************************************************/

void	SetCharacterEquipHead(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquHead = *lpItem;
}

void	GetCharacterEquipHead(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquHead;
}

void	SetCharacterEquipNeck(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquNeck = *lpItem;
}

void	GetCharacterEquipNeck(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquNeck;
}

void	SetCharacterEquipBody(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquBody = *lpItem;
}

void	GetCharacterEquipBody(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquBody;
}

void	SetCharacterEquipWaist(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquWaist = *lpItem;
}

void	GetCharacterEquipWaist(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquWaist;
}

void	SetCharacterEquipGlove(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquGlove = *lpItem;
}

void	GetCharacterEquipGlove(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquGlove;
}

void	SetCharacterEquipWeapon(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquWeapon = *lpItem;
}

void	GetCharacterEquipWeapon(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquWeapon;
}

void	SetCharacterEquipWrist(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquWrist = *lpItem;
}

void	GetCharacterEquipWrist(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquWrist;
}

void	SetCharacterEquipFeet(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquFeet = *lpItem;
}

void	GetCharacterEquipFeet(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquFeet;
}

void	SetCharacterEquipOtherA(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquOtherA = *lpItem;
}

void	GetCharacterEquipOtherA(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquOtherA;
}

void	SetCharacterEquipOtherB(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquOtherB = *lpItem;
}

void	GetCharacterEquipOtherB(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquOtherB;
}

void	SetCharacterEquipOtherC(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lIndex].Equipment.EquOtherC = *lpItem;
}

void	GetCharacterEquipOtherC(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lIndex].Equipment.EquOtherC;
}

/************************************************************************/
/*  Set/Get Character Item and Gold                                     */
/************************************************************************/

void	SetCharacterBagItem(SLONG lCharIndex, SLONG lBagIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lCharIndex].BodyItemMoney.BagItem[lBagIndex] = *lpItem;
}

void	GetCharacterBagItem(SLONG lCharIndex, SLONG lBagIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lCharIndex].BodyItemMoney.BagItem[lBagIndex];
}

void	SetCharacterSashItem(SLONG lCharIndex, SLONG lSashIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lCharIndex].BodyItemMoney.SashItem[lSashIndex] = *lpItem;
}

void	GetCharacterSashItem(SLONG lCharIndex, SLONG lSashIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lCharIndex].BodyItemMoney.SashItem[lSashIndex];
}

void	SetCharacterTransItem(SLONG lCharIndex, SLONG lTransIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lCharIndex].BodyItemMoney.TransItem[lTransIndex] = *lpItem;
}

void	GetCharacterTransItem(SLONG lCharIndex, SLONG lTransIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lCharIndex].BodyItemMoney.TransItem[lTransIndex];
}

void	SetCharacterOnMouseItem(SLONG lCharIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lCharIndex].BodyItemMoney.OnMouseItem = *lpItem;
}

void	GetCharacterOnMouseItem(SLONG lCharIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lCharIndex].BodyItemMoney.OnMouseItem;
}

void	SetCharacterTreasureItem(SLONG lCharIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lCharIndex].BodyItemMoney.TreasureItem = *lpItem;
}

void	GetCharacterTreasureItem(SLONG lCharIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lCharIndex].BodyItemMoney.TreasureItem;
}

void	SetCharacterBodyMoney(SLONG lIndex, ULONG uMoney)
{
	ZoneCharacter[lIndex].BodyItemMoney.Money = uMoney;
}

ULONG	GetCharacterBodyMoney(SLONG lIndex)
{
	return ZoneCharacter[lIndex].BodyItemMoney.Money;
}

/************************************************************************/
/* Set/Get Character Bank Item and Gold                                 */
/************************************************************************/

void	SetCharacterBankItem(SLONG lCharIndex, SLONG lItemIndex, TPOS_ITEM *lpItem)
{
	ZoneCharacter[lCharIndex].BankItemMoney.Item[lItemIndex] = *lpItem;
}

void	GetCharacterBankItem(SLONG lCharIndex, SLONG lItemIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneCharacter[lCharIndex].BankItemMoney.Item[lItemIndex];
}

void	SetCharacterBankMoney(SLONG lIndex, ULONG uMoney)
{
	ZoneCharacter[lIndex].BankItemMoney.Money = uMoney;
}

ULONG	GetCharacterBankMoney(SLONG lIndex)
{
	return ZoneCharacter[lIndex].BankItemMoney.Money;
}

/************************************************************************/
/* Set/Get Character Team Associated Datas                              */
/************************************************************************/
void	SetCharacterTeamMemberFlag(SLONG lCharIndex, SLONG lMemberIndex, ULONG uFlag)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Flags = uFlag;
}

ULONG	GetCharacterTeamMemberFlag(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Flags;
}

void	SetCharacterTeamMemberMainName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szMainName)
{
	strcpy(ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].MainName, szMainName);
}

CHAR*	GetCharacterTeamMemberMainName(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	(CHAR*)ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].MainName;
}

void	SetCharacterTeamMemberHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uHp)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Hp = uHp;
}

UHINT	GetCharacterTeamMemberHp(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Hp;
}

void	SetCharacterTeamMemberMaxHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uMaxHp)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].MaxHp = uMaxHp;
}

UHINT	GetCharacterTeamMemberMaxHp(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].MaxHp;
}

void	SetCharacterTeamMemberLevel(SLONG lCharIndex, SLONG lMemberIndex, UHINT uLevel)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Level = uLevel;
}

UHINT	GetCharacterTeamMemberLevel(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Level;
}

void	SetCharacterTeamMemberEyes(SLONG lCharIndex, SLONG lMemberIndex, SLONG lEyes)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Eyes = (CHAR)lEyes;
}

SLONG	GetCharacterTeamMemberEyes(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Eyes;
}

void	SetCharacterTeamMemberMouth(SLONG lCharIndex, SLONG lMemberIndex, SLONG lMouth)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Mouth = (CHAR)lMouth;
}

SLONG	GetCharacterTeamMemberMouth(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Mouth;
}

void	SetCharacterTeamMaxMembers(SLONG lCharIndex, SLONG lMaxMembers)
{
	ZoneCharacter[lCharIndex].Team.MaxMembers = lMaxMembers;
}

SLONG	GetCharacterTeamMaxMembers(SLONG lCharIndex)
{
	return	ZoneCharacter[lCharIndex].Team.MaxMembers;
}

void	SetCharacterTeamMemberCareer(SLONG lCharIndex, SLONG lMemberIndex, SLONG lCareer)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Career = (CHAR)lCareer;
}

SLONG	GetCharacterTeamMemberCareer(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Career;
}

void	SetCharacterTeamMemberSex(SLONG lCharIndex, SLONG lMemberIndex, SLONG lSex)
{
	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Sex = (CHAR)lSex;
}

SLONG	GetCharacterTeamMemberSex(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].Sex;
}

void	SetCharacterTeamMemberZoneName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szZoneName)
{
	strcpy((char *)ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].ZoneName, (const char *)szZoneName);
}

CHAR*	GetCharacterTeamMemberZoneName(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	(CHAR*)ZoneCharacter[lCharIndex].Team.Member[lMemberIndex].ZoneName;
}

/************************************************************************/
/* Set/Get Character Enemy Associated Datas                             */
/************************************************************************/
void	SetCharacterEnemyMaxMembers(SLONG lCharIndex, SLONG lMaxMembers)
{
	ZoneCharacter[lCharIndex].Enemy.MaxMembers = lMaxMembers;
}

SLONG	GetCharacterEnemyMaxMembers(SLONG lCharIndex)
{
	return	ZoneCharacter[lCharIndex].Enemy.MaxMembers;
}

void	SetCharacterEnemyMemberHitHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uHp)
{
	ZoneCharacter[lCharIndex].Enemy.Member[lMemberIndex].HitHp = uHp;
}

UHINT	GetCharacterEnemyMemberHitHp(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Enemy.Member[lMemberIndex].HitHp;
}

void	SetCharacterEnemyMemberMainName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szMainName)
{
	strcpy(ZoneCharacter[lCharIndex].Enemy.Member[lMemberIndex].MainName, szMainName);
}

CHAR*	GetCharacterEnemyMemberMainName(SLONG lCharIndex, SLONG lMemberIndex)
{
	return	ZoneCharacter[lCharIndex].Enemy.Member[lMemberIndex].MainName;
}

/************************************************************************/
/* Set/Get Character Society                                            */
/************************************************************************/

void	SetCharacterSex(SLONG lIndex, SLONG lSex)
{
	ZoneCharacter[lIndex].Society.Sex = (CHAR)lSex;
}

SLONG	GetCharacterSex(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.Sex;
}

void	SetCharacterCountry(SLONG lIndex, SLONG lCountry)
{
	ZoneCharacter[lIndex].Society.Country = (CHAR)lCountry;
}

SLONG	GetCharacterCountry(SLONG lIndex)
{
	return (SLONG)ZoneCharacter[lIndex].Society.Country;
}

void	SetCharacterGuildName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneCharacter[lIndex].Society.Guild, szName );
}

CHAR*	GetCharacterGuildName(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.Guild;
}

void	SetCharacterSpouseName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneCharacter[lIndex].Society.Spouse, szName );
}

CHAR*	GetCharacterSpouseName(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.Spouse;
}

void	SetCharacterCareer(SLONG lIndex, SLONG lCareer)
{
	ZoneCharacter[lIndex].Society.Career = (CHAR)lCareer;
}

SLONG	GetCharacterCareer(SLONG lIndex)
{
	return (SLONG)ZoneCharacter[lIndex].Society.Career;
}

void	SetCharacterOffice(SLONG lIndex, ULONG uOffice)
{
	ZoneCharacter[lIndex].Society.Office = uOffice;
}

void	SetCharacterCareerLevel(SLONG lIndex, SLONG lLevel)
{
	ZoneCharacter[lIndex].Society.CareerLevel = (UCHR)lLevel;
}

SLONG	GetCharacterCareerLevel(SLONG lIndex)
{
	return	(SLONG)ZoneCharacter[lIndex].Society.CareerLevel;
}

ULONG	GetCharacterOffice(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.Office;
}

void	SetCharacterNobilityName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneCharacter[lIndex].Society.Nobility, szName );
}

CHAR*	GetCharacterNobilityName(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.Nobility;
}

void	SetCharacterGoodEvil(SLONG lIndex, SLONG lData)
{
	ZoneCharacter[lIndex].Society.GoodEvil = lData;
}

SLONG	GetCharacterGoodEvil(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.GoodEvil;
}

void	SetCharacterPrestige(SLONG lIndex, SLONG lPres)
{
	ZoneCharacter[lIndex].Society.Prestige = lPres;
}

SLONG	GetCharacterPrestige(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.Prestige;
}

void	SetCharacterPkCount(SLONG lIndex, ULONG uCount)
{
	ZoneCharacter[lIndex].Society.PkCount = uCount;
}

ULONG	GetCharacterPkCount(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.PkCount;
}

void	SetCharacterPkedCount(SLONG lIndex, ULONG uCount)
{
	ZoneCharacter[lIndex].Society.PkedCount = uCount;
}

ULONG	GetCharacterPkedCount(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Society.PkedCount;
}

void	SetCharacterKind(SLONG lIndex, SLONG lKind)
{
	ZoneCharacter[lIndex].Society.Kind = (CHAR)lKind;
}

SLONG	GetCharacterKind(SLONG lIndex)
{
	return	(SLONG)ZoneCharacter[lIndex].Society.Kind;
}

/************************************************************************/
/* Set/Get Character Land Skill QuickKey                                */
/************************************************************************/

void	SetCharacterLandLeftSkill(SLONG lIndex, SHINT lSkill)
{
	ZoneCharacter[lIndex].QuickButton.LandLeftSkill = lSkill;
}

SHINT	GetCharacterLandLeftSkill(SLONG lIndex)
{
	return ZoneCharacter[lIndex].QuickButton.LandLeftSkill;
}

void	SetCharacterLandRightSkill(SLONG lIndex, SHINT lSkill)
{
	ZoneCharacter[lIndex].QuickButton.LandRightSkill = lSkill;
}

SHINT	GetCharacterLandRightSkill(SLONG lIndex)
{
	return ZoneCharacter[lIndex].QuickButton.LandRightSkill;
}

void	SetCharacterLandFnSkillNo(SLONG lIndex, SLONG lFnIndex, SHINT lSkill)
{
	ZoneCharacter[lIndex].QuickButton.LandFnSkillNo[lFnIndex] = lSkill;
}

SHINT	GetCharacterLandFnSkillNo(SLONG lIndex, SLONG lFnIndex)
{
	return ZoneCharacter[lIndex].QuickButton.LandFnSkillNo[lFnIndex];
}

void	SetCharacterLandFnSkillHand(SLONG lIndex, SLONG lFnIndex, SLONG lHand)
{
	ZoneCharacter[lIndex].QuickButton.LandFnSkillHand[lFnIndex] = (CHAR)lHand;
}

SLONG	GetCharacterLandFnSkillHand(SLONG lIndex, SLONG lFnIndex)
{
	return ZoneCharacter[lIndex].QuickButton.LandFnSkillHand[lFnIndex];
}

/************************************************************************/
/* Set/Get Character Sea Skill QuickKey                                 */
/************************************************************************/

void	SetCharacterSeaLeftSkill(SLONG lIndex, SHINT lSkill)
{
	ZoneCharacter[lIndex].QuickButton.SeaLeftSkill = lSkill;
}

SHINT	GetCharacterSeaLeftSkill(SLONG lIndex)
{
	return ZoneCharacter[lIndex].QuickButton.SeaLeftSkill;
}

void	SetCharacterSeaRightSkill(SLONG lIndex, SHINT lSkill)
{
	ZoneCharacter[lIndex].QuickButton.SeaRightSkill = lSkill;
}

SHINT	GetCharacterSeaRightSkill(SLONG lIndex)
{
	return ZoneCharacter[lIndex].QuickButton.SeaRightSkill;
}

void	SetCharacterSeaFnSkillNo(SLONG lIndex, SLONG lFnIndex, SHINT lSkill)
{
	ZoneCharacter[lIndex].QuickButton.SeaFnSkillNo[lFnIndex] = lSkill;
}

SHINT	GetCharacterSeaFnSkillNo(SLONG lIndex, SLONG lFnIndex)
{
	return ZoneCharacter[lIndex].QuickButton.SeaFnSkillNo[lFnIndex];
}

void	SetCharacterSeaFnSkillHand(SLONG lIndex, SLONG lFnIndex, SLONG lHand)
{
	ZoneCharacter[lIndex].QuickButton.SeaFnSkillHand[lFnIndex] = (CHAR)lHand;
}

SLONG	GetCharacterSeaFnSkillHand(SLONG lIndex, SLONG lFnIndex)
{
	return ZoneCharacter[lIndex].QuickButton.SeaFnSkillHand[lFnIndex];
}

/************************************************************************/
/* Set/Get Character Action                                            */
/************************************************************************/

void	SetCharacterDoingKind(SLONG lIndex, SLONG lKind)
{
	ZoneCharacter[lIndex].Action.DoingKind = lKind;
}

SLONG	GetCharacterDoingKind(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Action.DoingKind;
}

void	SetCharacterDoingStep(SLONG lIndex, SLONG lStep)
{
	ZoneCharacter[lIndex].Action.DoingStep = lStep;
}

SLONG	GetCharacterDoingStep(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Action.DoingStep;
}


void	SetCharacterDoingKindStep(SLONG lIndex, SLONG lDoingKind, SLONG lDoingStep)
{
	ZoneCharacter[lIndex].Action.DoingKind = lDoingKind;
	ZoneCharacter[lIndex].Action.DoingStep = lDoingStep;
}

void	SetCharacterDoingMagic(SLONG lIndex, SHINT lMagic)
{
	ZoneCharacter[lIndex].Action.DoingMagic = lMagic;
}

SHINT	GetCharacterDoingMagic(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Action.DoingMagic;
}

void	SetCharacterMagicTimes(SLONG lIndex, SHINT lTimes)
{
	ZoneCharacter[lIndex].Action.MagicTimes = lTimes;
}

SHINT	GetCharacterMagicTimes(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Action.MagicTimes;
}

void	SetCharacterFightTicks(SLONG lIndex, SHINT lTicks)
{
	ZoneCharacter[lIndex].Action.FightTicks = lTicks;
}

SHINT	GetCharacterFightTicks(SLONG lIndex)
{
	return	ZoneCharacter[lIndex].Action.FightTicks;
}

void	SetCharacterImageAction(SLONG lIndex, SLONG lAction)
{
	ZoneCharacter[lIndex].Action.ImageAction = (UCHAR)lAction;
}

SLONG	GetCharacterImageAction(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Action.ImageAction;
}

void	SetCharacterImageID(SLONG lIndex, ULONG uID)
{
	ZoneCharacter[lIndex].Action.ImageID = uID;
}

ULONG	GetCharacterImageID(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Action.ImageID;
}

void	SetCharacterIdleTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.IdleTicks = lTicks;
}

SLONG	GetCharacterIdleTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.IdleTicks;
}

void	SetCharacterSequentialStep(SLONG lIndex, SLONG lStep)
{
	ZoneCharacter[lIndex].Position.SequentialStep = lStep;
}

SLONG	GetCharacterSequentialStep(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.SequentialStep;
}

void	SetCharacterBeatedBy(SLONG lIndex, SLONG lBy)
{
	ZoneCharacter[lIndex].Position.BeatedBy = lBy;
}

SLONG	GetCharacterBeatedBy(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.BeatedBy;
}

void	SetCharacterBeatedWith(SLONG lIndex, SLONG lWith)
{
	ZoneCharacter[lIndex].Position.BeatedWith = lWith;
}

SLONG	GetCharacterBeatedWith(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.BeatedWith;
}

void	SetCharacterPantTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.PantTicks = lTicks;
}

SLONG	GetCharacterPantTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.PantTicks;
}

void	SetCharacterBeatedX(SLONG lIndex, SLONG lX)
{
	ZoneCharacter[lIndex].Position.BeatedX = lX;
}

SLONG	GetCharacterBeatedX(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.BeatedX;
}

void	SetCharacterBeatedY(SLONG lIndex, SLONG lY)
{
	ZoneCharacter[lIndex].Position.BeatedY = lY;
}

SLONG	GetCharacterBeatedY(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.BeatedY;
}

void	SetCharacterBeatedXY(SLONG lIndex, SLONG lX, SLONG lY)
{
	ZoneCharacter[lIndex].Position.BeatedX = lX;
	ZoneCharacter[lIndex].Position.BeatedY = lY;
}

void	GetCharacterBeatedXY(SLONG lIndex, SLONG *lX, SLONG *lY)
{
	if(lX) *lX = ZoneCharacter[lIndex].Position.BeatedX;
	if(lY) *lY = ZoneCharacter[lIndex].Position.BeatedY;
}

void	SetCharacterMuseTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.MuseTicks = lTicks;
}

SLONG	GetCharacterMuseTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.MuseTicks;
}

void	SetCharacterClashSteps(SLONG lIndex, SLONG lSteps)
{
	ZoneCharacter[lIndex].Position.ClashSteps = lSteps;
}

SLONG	GetCharacterClashSteps(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.ClashSteps;
}

void	SetCharacterPatrolTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.PatrolTicks = lTicks;
}

SLONG	GetCharacterPatrolTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.PatrolTicks;
}

void	SetCharacterPatrolTotalTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.PatrolTotalTicks = lTicks;
}

SLONG	GetCharacterPatrolTotalTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.PatrolTotalTicks;
}

void	SetCharacterGadTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.GadTicks = lTicks;
}

SLONG	GetCharacterGadTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.GadTicks;
}

void	SetCharacterGadTotalTicks(SLONG lIndex, SLONG lTicks)
{
	ZoneCharacter[lIndex].Position.GadTotalTicks = lTicks;
}

SLONG	GetCharacterGadTotalTicks(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Position.GadTotalTicks;
}

/************************************************************************************************************/
/* LEVEL 1 FUNCTIONS                                                                                        */
/************************************************************************************************************/
void	SetCharacterLeftSkill(SLONG lIndex, SHINT lSkill)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
	{
		SetCharacterSeaLeftSkill(lIndex, lSkill);
	}
	else
	{
		SetCharacterLandLeftSkill(lIndex, lSkill);
	}
}


SHINT	GetCharacterLeftSkill(SLONG lIndex)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
		return	GetCharacterSeaLeftSkill(lIndex);
	else
		return	GetCharacterLandLeftSkill(lIndex);
}


void	SetCharacterRightSkill(SLONG lIndex, SHINT lSkill)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
	{
		SetCharacterSeaRightSkill(lIndex, lSkill);
	}
	else
	{
		SetCharacterLandRightSkill(lIndex, lSkill);
	}
}


SHINT	GetCharacterRightSkill(SLONG lIndex)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
		return	GetCharacterSeaRightSkill(lIndex);
	else
		return	GetCharacterLandRightSkill(lIndex);
}



void	SetCharacterFnSkill(SLONG lIndex, SLONG lFnIndex, SLONG lSkill, SLONG lHand)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
	{
		SetCharacterSeaFnSkillNo(lIndex, lFnIndex, (SHINT)lSkill);
		SetCharacterSeaFnSkillHand(lIndex, lFnIndex, lHand);
	}
	else
	{
		SetCharacterLandFnSkillNo(lIndex, lFnIndex, (SHINT)lSkill);
		SetCharacterLandFnSkillHand(lIndex, lFnIndex, lHand);
	}
}

void	GetCharacterFnSkill(SLONG lIndex, SLONG lFnIndex, SLONG *lSkill, SLONG *lHand)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
	{
		if(lSkill) *lSkill = GetCharacterSeaFnSkillNo(lIndex, lFnIndex);
		if(lHand) *lHand = GetCharacterSeaFnSkillHand(lIndex, lFnIndex);
	}
	else
	{
		if(lSkill) *lSkill = GetCharacterLandFnSkillNo(lIndex, lFnIndex);
		if(lHand) *lHand = GetCharacterLandFnSkillHand(lIndex, lFnIndex);
	}
}


SLONG	FindCharacterBagItemRoom(SLONG lIndex)
{
	TPOS_ITEM	it;
    SLONG   i, find_index;

	find_index = -1;
    for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
    {
		GetCharacterBagItem(lIndex, i, &it);
		if( IsItemNone(&it) )
        {
			find_index = i;
            break;
        }
    }
    return  find_index;
}


SLONG	FindCharacterSashItemRoom(SLONG lIndex)
{
	TPOS_ITEM	it;
    SLONG   i, find_index;

	find_index = -1;
    for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
    {
		GetCharacterSashItem(lIndex, i, &it);
		if( IsItemNone(&it) )
        {
			find_index = i;
            break;
        }
    }
    return  find_index;
}


SLONG	FindCharacterTransItemRoom(SLONG lIndex)
{
	TPOS_ITEM	it;
    SLONG   i, find_index;

	find_index = -1;
    for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
    {
		GetCharacterTransItem(lIndex, i, &it);
		if( IsItemNone(&it) )
        {
			find_index = i;
            break;
        }
    }
    return  find_index;
}


SLONG	FindCharacterByMainName(CHAR *szMainName)
{
    SLONG   i, find_index;

    if(!szMainName) 
		return -1;
    find_index = -1;
    for(i=0; i <MAX_CHARACTER_PER_ZONE; i++)
    {
		if(0 == strcmpi((const char *)ZoneCharacter[i].Name.MainName, (const char *)szMainName))
		{
			find_index = i;
			break;
		}
    }
    return  find_index;
}


SLONG   FindCharacterLandFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand)
{
    SLONG   i, find_index;
	SLONG	skill_no, hand;

	find_index = -1;
    for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
    {
		skill_no = GetCharacterLandFnSkillNo(lIndex, i);
		hand = GetCharacterLandFnSkillHand(lIndex, i);
		if(skill_no == lSkillNo && hand == lHand)
		{
			find_index = i;
			break;
		}
    }
    return  find_index;
}


SLONG   FindCharacterSeaFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand)
{
    SLONG   i, find_index;
	SLONG	skill_no, hand;

	find_index = -1;
    for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
    {
		skill_no = GetCharacterSeaFnSkillNo(lIndex, i);
		hand = GetCharacterSeaFnSkillHand(lIndex, i);
		if(skill_no == lSkillNo && hand == lHand)
		{
			find_index = i;
			break;
		}
    }
    return  find_index;
}


SLONG	FindCharacterFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand)
{
	SLONG	on_the_sea;

	on_the_sea = IsCharacterOnTheSea(lIndex);
	if(on_the_sea)
	{
		return	FindCharacterSeaFnSkillIndex(lIndex, lSkillNo, lHand);
	}
	else
	{
		return	FindCharacterLandFnSkillIndex(lIndex, lSkillNo, lHand);
	}
}


SLONG	FindCharacterSkillIndex(SLONG lIndex, SLONG lSkillNo)
{
    SLONG   find_index, skill_no;
    SLONG   i;

    find_index = -1;
    for(i=0; i<MAX_CHARACTER_SKILLS; i++)
    {
		skill_no = GetCharacterSkillNo(lIndex, i);
        if(skill_no == lSkillNo)
        {
            find_index = i;
            break;
        }
    }
    return  find_index;
}


void    InitCharacterRightSkillState(SLONG lIndex)
{
    SLONG   magic_no;
	SLONG	total;
    
    magic_no = GetCharacterRightSkill(lIndex);

    if( IsSkillNeedSpower(magic_no, 0) )
    {
		total = GetSkillSpowerTick(magic_no, 0);
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_WAIT_SPOWER);
		SetCharacterRightHandMagicTotalTicks(lIndex, (SHINT)total);
		SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
    }
    else
    {
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_OK);
		SetCharacterRightHandMagicTotalTicks(lIndex, 0);
		SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
    }    
    /*
    if( IsSkillNeedPrepare(magic_no) )
    {
		total = GetSkillPrepareTicks(magic_no);
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_PREPARE);
		SetCharacterRightHandMagicTotalTicks(lIndex, (SHINT)total);
		SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
    }
    else if( IsSkillNeedSpower(magic_no) )
    {
		total = GetSkillSpowerTicks(magic_no);
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_WAIT_SPOWER);
		SetCharacterRightHandMagicTotalTicks(lIndex, (SHINT)total);
		SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
    }
    else
    {
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_OK);
		SetCharacterRightHandMagicTotalTicks(lIndex, 0);
		SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
    }
    */    
}


void    RefreshCharacterRightHandMagicState(SLONG lIndex)
{
    SLONG   magic_no;
	SLONG	state;
	SLONG	curr_ticks, total_ticks;

	state = GetCharacterRightHandMagicState(lIndex);
	curr_ticks = GetCharacterRightHandMagicCurrentTicks(lIndex);
	total_ticks = GetCharacterRightHandMagicTotalTicks(lIndex);
    switch(state)
    {
    case MAGIC_STATE_OK:
        break;
    case MAGIC_STATE_PREPARE:
        if(++curr_ticks >= total_ticks)
        {
            magic_no = GetCharacterRightSkill(lIndex);
            if( IsSkillNeedSpower(magic_no, 0) )
            {
				total_ticks = GetSkillSpowerTick(magic_no, 0);
                SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_WAIT_SPOWER);
                SetCharacterRightHandMagicTotalTicks(lIndex, (SHINT)total_ticks);
				SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
            }
            else
            {
                SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_OK);
                SetCharacterRightHandMagicTotalTicks(lIndex, 0);
				SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
            }
        }
		else
		{
			SetCharacterRightHandMagicCurrentTicks(lIndex, (SHINT)curr_ticks);
		}
        break;
    case MAGIC_STATE_WAIT_SPOWER:
        break;
    case MAGIC_STATE_SPOWER:
        if(++curr_ticks >= total_ticks)
        {
            SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_WAIT_BREAK);
            SetCharacterRightHandMagicTotalTicks(lIndex, -1);		//當作alpha的增加或者減少標誌
            SetCharacterRightHandMagicCurrentTicks(lIndex, 255);    //目前的alpha值
        }
		else
		{
			SetCharacterRightHandMagicCurrentTicks(lIndex, (SHINT)curr_ticks);
		}
        break;
    case MAGIC_STATE_WAIT_BREAK:	//當作alpha處理
        if(total_ticks == 1)
        {
            curr_ticks += 32;
            if(curr_ticks > 255)
            {
				SetCharacterRightHandMagicCurrentTicks(lIndex, 255);	//alpha
				SetCharacterRightHandMagicTotalTicks(lIndex, -1);	//dec alpha flag
            }
			else
			{
				SetCharacterRightHandMagicCurrentTicks(lIndex, (SHINT)curr_ticks);	//alpha
			}
        }
        else
        {
            curr_ticks -= 32;
            if(curr_ticks < 128)
            {
				SetCharacterRightHandMagicCurrentTicks(lIndex, 128);	//alpha
				SetCharacterRightHandMagicTotalTicks(lIndex, 1);	//inc alpha flag
            }
			else
			{
				SetCharacterRightHandMagicCurrentTicks(lIndex, (SHINT)curr_ticks);	//alpha
			}
        }
        break;
    }
}


void    SetCharacterRightHandMagicStartSpower(SLONG lIndex)
{
	SLONG	state;

	state = GetCharacterRightHandMagicState(lIndex);
    if(state == MAGIC_STATE_WAIT_SPOWER)
	{
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_SPOWER);
	}
}


SLONG   IsCharacterRightHandMagicCanBreak(SLONG lIndex)
{
	SLONG	state;

	state = GetCharacterRightHandMagicState(lIndex);
    if(state == MAGIC_STATE_WAIT_BREAK || state == MAGIC_STATE_OK)
        return  TRUE;
    return  FALSE;
}


SLONG	SetupCharacterHandQuickSkill(SLONG lIndex, SLONG lQuickIndex, SLONG lHand, SLONG lSkillNo)
{
	SLONG	i;
	SLONG	old_skill_no, old_skill_hand;

	GetCharacterFnSkill(lIndex, lQuickIndex, &old_skill_no, &old_skill_hand);
	if(old_skill_no == lSkillNo && old_skill_hand == lHand)
	{
		//If it WAS, clean it.
		SetCharacterFnSkill(lIndex, lQuickIndex, -1, 0);
	}
	else
	{
		//If it wasnt, clear old associated quick magic set, and set it new.
		for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
		{
			GetCharacterFnSkill(lIndex, i, &old_skill_no, &old_skill_hand);
			if(old_skill_no == lSkillNo)
			{
				SetCharacterFnSkill(lIndex, i, -1, 0);
			}
		}

		//Set it new.
		SetCharacterFnSkill(lIndex, lQuickIndex, lSkillNo, lHand);
	}
	return	TTN_OK;
}
//----
//  一些人物行為的判定函數
//----
//判定人物是否死亡
SLONG   IsCharacterDead(SLONG lIndex)
{
	return ZoneCharacter[lIndex].HpMp.Hp <= 0 ? true : false;
}
//判斷莫兩個人之間是否是隊友
SLONG   IsCharacterTeamMember(SLONG lNpcSc, SLONG lNpcTag)
{
    SLONG   i;
    SLONG   maxmember;
    //
    if (lNpcSc == lNpcTag)
        return false;
    //
    maxmember = ZoneCharacter[lNpcSc].Team.MaxMembers;
    //
    for (i=0; i<maxmember; i++)
    {
        if (strcmp((char *)ZoneCharacter[lNpcTag].Name.MainName,
                   (char *)ZoneCharacter[lNpcSc].Team.Member[i].MainName) == 0)
            return true;
    }
    //
    return false;
}   

//----
//  怪物..用來檢測..莫個npc可否攻擊
//----
SLONG   IsCharacterCanAttackMonsterCheck(SLONG lIndex)
{
    if (!IsCharacterAvailable(lIndex))
        return false;
    if (ZoneCharacter[lIndex].Action.DoingKind == DOING_KIND_CHANGEMAP)
        return false;
    //
    return true;        
}
//------------------------------------------------------------------------
//  在表格建立好後..最好是..使用
//         SLONG   IsHighPriorityDoingKind(SLONG cur_doing, SLONG new_doing)
//------------------------------------------------------------------------
//----
//  npc自己..可以自己中斷自己的動作
//----
SLONG   IsCharacterSelfDoingKindBreak(SLONG lIndex)
{   
    //行走  待機   蓄力 的時候可以被中斷
    switch (ZoneCharacter[lIndex].Action.DoingKind)
    {
    case DOING_KIND_MOVE_TO://移動
    case DOING_KIND_IDLE:   //待機
    case DOING_KIND_SPOWER: //蓄力量
        return true;
        break;
    default:
        return false;
        break;        
    }
	return false;
}
//----
//  npc可以被..強行中斷的動作
//----
SLONG   IsCharacterOtherDoingBreak(SLONG lIndex)
{
    //死亡
    //到地
    //爬起來
    //升級
    switch (ZoneCharacter[lIndex].Action.DoingKind)
    {
    case DOING_KIND_DEAD:           //人物死亡
    case DOING_KIND_DOWN_AND_OUT:   //人物被擊倒    
    case DOING_KIND_UPGRADE:        //升級.
    case DOING_KIND_CHANGEMAP:      //切換地圖
        return false;
        break;
    }
    //
    return true;
}
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

// Jack,  [5/8/2003]
//-------------------------------------------------------------------------
// quest related functions
//-------------------------------------------------------------------------
void	SetQuestType(TPOS_QUEST_INFO *lpQI, SLONG lType)
{
	lpQI->QuestType = (UCHR)lType;
}

SLONG	GetQuestType(TPOS_QUEST_INFO *lpQI)
{
	return	lpQI->QuestType;
}

void	SetQuestPublishZone(TPOS_QUEST_INFO *lpQI, CHAR* szZoneName)
{
	strcpy(lpQI->PublishZone, szZoneName);
}

CHAR*	GetQuestPublishZone(TPOS_QUEST_INFO *lpQI)
{
	return	(CHAR*)lpQI->PublishZone;
}

void	SetQuestPublishNpc(TPOS_QUEST_INFO *lpQI, CHAR* szNpcName)
{
	strcpy(lpQI->PublishNpc, szNpcName);
}

CHAR*	GetQuestPublishNpc(TPOS_QUEST_INFO *lpQI)
{
	return	(CHAR*)lpQI->PublishNpc;
}

void	SetQuestTargetZone(TPOS_QUEST_INFO *lpQI, CHAR *szZoneName)
{
	strcpy(lpQI->TargetZone, szZoneName);
}

CHAR*	GetQuestTargetZone(TPOS_QUEST_INFO *lpQI)
{
	return	(CHAR*)lpQI->TargetZone;
}

void	SetQuestTargetNpc(TPOS_QUEST_INFO *lpQI, CHAR *szNpcName)
{
	strcpy(lpQI->TargetNpc, szNpcName);
}

CHAR*	GetQuestTargetNpc(TPOS_QUEST_INFO *lpQI)
{
	return	(CHAR*)lpQI->TargetNpc;
}

void	SetQuestAcceptTime(TPOS_QUEST_INFO *lpQI, ULONG uTime)
{
	lpQI->AcceptTime = uTime;
}

ULONG	GetQuestAcceptTime(TPOS_QUEST_INFO *lpQI)
{
	return	lpQI->AcceptTime;
}

void	SetQuestDeadline(TPOS_QUEST_INFO *lpQI, ULONG uDeadline)
{
	lpQI->Deadline = uDeadline;
}

ULONG	GetQuestDeadline(TPOS_QUEST_INFO *lpQI)
{
	return	lpQI->Deadline;
}

void	SetQuestPay(TPOS_QUEST_INFO *lpQI, SLONG lPayType, ULONG uPayData)
{
	lpQI->PayType = (UCHR)lPayType;
	lpQI->PayData = uPayData;
}

void	GetQuestPay(TPOS_QUEST_INFO *lpQI, SLONG *lPayType, ULONG *uPayData)
{
	*lPayType = lpQI->PayType;
	*uPayData = lpQI->PayData;
}

void	SetQuestPunish(TPOS_QUEST_INFO *lpQI, SLONG lPunishType, ULONG uPunishData)
{
	lpQI->PunishType = (UCHR)lPunishType;
	lpQI->PunishData = uPunishData;
}

void	GetQuestPunish(TPOS_QUEST_INFO *lpQI, SLONG *lPunishType, ULONG *uPunishData)
{
	*lPunishType = lpQI->PunishType;
	*uPunishData = lpQI->PunishData;
}

void	SetQuestMemo(TPOS_QUEST_INFO *lpQI, CHAR *szMemo)
{
	strcpy(lpQI->Memo, szMemo);
}

CHAR*	GetQuestMemo(TPOS_QUEST_INFO *lpQI)
{
	return	(CHAR*)lpQI->Memo;
}
//
void	SetCharacterQuestInfo(SLONG lCharIndex, SLONG lQuestIndex, TPOS_QUEST_INFO *lpInfo)
{
	ZoneCharacter[lCharIndex].Quest.QuestInfo[lQuestIndex] = *lpInfo;
}

void	GetCharacterQuestInfo(SLONG lCharIndex, SLONG lQuestIndex, TPOS_QUEST_INFO *lpInfo)
{
	if(lpInfo) memcpy(lpInfo, &ZoneCharacter[lCharIndex].Quest.QuestInfo[lQuestIndex], sizeof(TPOS_QUEST_INFO));
}

SLONG	FindCharacterEmptyQuestIndex(SLONG lCharIndex)
{
	SLONG	i, find_index, quest_type;

	find_index = -1;
	for(i=0; i<MAX_CHARACTER_QUESTS; i++)
	{
		quest_type = ZoneCharacter[lCharIndex].Quest.QuestInfo[i].QuestType;
		if(quest_type == QUEST_TYPE_NONE)
		{
			find_index = i;
			break;
		}
	}
	return	find_index;
}

