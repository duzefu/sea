/*
**	NetGE_Skill.cpp 
**	skill functions.
**
**	Jack, 2003.1.4
*/
#include "NetGE_MainFunc.h"


 

/************************************************************************************************************/
/* 全局變量                                                                                                 */
/************************************************************************************************************/
TPOS_SKILL_BS	GameSkillBase[MAX_GAME_SKILL_BASES][MAX_SKILL_LEVELS];  //[技能的編號][技能的等級]


/************************************************************************************************************/
/* SKILL FUNCTIONS                                                                                          */
/************************************************************************************************************/
SLONG	InitSkillSystem(void)
{
	SLONG	result;

	//
	//初始化遊戲物品基本表
	//
	InitGameSkillBase();
	result = LoadGameSkillBase("data\\magic.ini");
	if(0 != result)
		return	-1;
	DebugLogGameSkillBase();
	//
	//
	InitZoneMagicPart();
	//
	//初始化區域地圖上法術物件以及施法函數.
	InitMagicBreakSystem();
	//
	InitBreakMagicFunctions();
	// mark by lijun 2003-05-06
	/*
	SetBreakMagicFunction(MAGIC_NO_SHOOT,				BreakMagic_FireBall);
	SetBreakMagicFunction(MAGIC_NO_SEQUENTIAL_SHOOT,	BreakMagic_FireBroken);
	SetBreakMagicFunction(MAGIC_NO_DIFFUSE_SHOOT,		BreakMagic_FireAerolite);

	SetBreakMagicFunction(MAGIC_NO_DARK_STAR,			BreakMagic_LightStrike);
	SetBreakMagicFunction(MAGIC_NO_DARK_BALL,			BreakMagic_LightBall);
	SetBreakMagicFunction(MAGIC_NO_BEELINE_MAGIC,		BreakMagic_LightBlade);

	SetBreakMagicFunction(MAGIC_NO_LINK_BALL,			BreakMagic_ShipCannon);
    */
	return	0;
}


void	FreeSkillSystem(void)
{
	FreeGameSkillBase();
}


void	InitGameSkillBase(void)
{
    SLONG   i;
    //清空內存初始化數據
    for (i=0;i<MAX_GAME_SKILL_BASES;i++)
    {    
        memset(GameSkillBase[i],0,sizeof(TPOS_SKILL_BS)*MAX_SKILL_LEVELS);
    }

}

SLONG   LoadGameSkillBase(CHAR* szFileName) 
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, len, skill_no, skill_level;
	TPOS_SKILL_BS	*data = NULL;
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
			// Jack, TODO: Sugguest add this line ... [5/12/2003]
			//skip_compartment(line, &index, ' \09', 2);

			skill_no = get_buffer_number(line, &index);
			skill_level = get_buffer_number(line, &index) - 1;
			if ((skill_no >= 0 && skill_no < MAX_GAME_SKILL_BASES)  &&
			   (skill_level >= 0 && skill_level < MAX_SKILL_LEVELS))
			{
				data = &GameSkillBase[skill_no][skill_level];
				//
                strcpy(data->Name, (const char *)get_buffer_string(line, &index)); //名稱
                data->IconIndex = get_buffer_number(line, &index);			//圖標編號
                data->MpConsume = get_buffer_number(line, &index);          //使用該技能的mp消耗(當蓄力時間為0 ,)
                data->MpConsumeTick = get_buffer_number(line, &index);      //都少次心跳
                data->UseTag = get_buffer_number(line, &index);           //法術適用的目標(隊友0,敵人1)
                data->Attrib = get_buffer_number(line, &index);				//技能的屬性
                data->Kind = get_buffer_number(line, &index);				//技能類型(被動機能0,釋放類型1,光環2)
                data->Penetrate = get_buffer_number(line, &index);          //穿透(0,1)
                data->HitType = get_buffer_number(line, &index);            //法術命中結算範圍(當體0,多人1)
                //2.和npc動作相關的技能數據
                data->ActionCount = get_buffer_number(line, &index);        //npc動作的播放次數
                data->ActionId = get_buffer_number(line, &index);           //使用該技能需要使用的npc動作的編號
                //3.技能的效果數值  
                data->AttackType = get_buffer_number(line, &index);         //機能的傷害類型(物理 0,法術 1,特殊 2)
                data->AttackRatio = get_buffer_number(line, &index);        //攻擊改變的百分率

                data->AttachMaxHp = get_buffer_number(line, &index);        //改變生命上限
                data->AttachMaxMp = get_buffer_number(line, &index);        //改變法力上限
                data->AttachNowHp = get_buffer_number(line, &index);        //改變當前的生命上限
                data->AttachNowMp = get_buffer_number(line, &index);        //改變當前的法力上限
    
                data->AttackRatioChange = get_buffer_number(line, &index);  //改變攻擊力的百分係數(所有類型的攻擊力)
                data->PhysicAttackReduceRatio = get_buffer_number(line, &index);//物理傷害減少率
                data->PhysicDefence = get_buffer_number(line, &index);      //改變物理防禦的數值
                data->MagicDefence = get_buffer_number(line, &index);       //改變魔法防率
                data->ExplodeRatio = get_buffer_number(line, &index);       //改變魔法防率                
        
                data->TagAction = get_buffer_number(line, &index);          //目標需要改變到的動作
                data->TagActionRatio = get_buffer_number(line, &index);     //目標會改變到該動作的機率
                //4.法術的附加效果
                data->SelfStatus = get_buffer_number(line, &index);          //自己會改變的狀態
                data->SelfStatusRatio = get_buffer_number(line, &index);      //自己會改變到該狀態的機率
    
                data->TagStatus = get_buffer_number(line, &index);           //目標會改變的狀態
                data->TagStatusRatio = get_buffer_number(line, &index);       //目標會改變到該狀態的機率

                data->Dispel = get_buffer_number(line, &index);             //消除不良狀態能力
                data->Resurgent = get_buffer_number(line, &index);          //復活

                //5.法術和範圍相關的數值
                data->MagicDisChargeDistance = get_buffer_number(line, &index); //法術釋放距離....施法者需要距離走近目標多少後才能..釋放法術
                data->MagicBrokenDistance = get_buffer_number(line, &index);    //法術命中的判定距離...就是法術和npc的距離差多少算命中
                data->MagicHitDistance = get_buffer_number(line, &index);       //法術命中後數值結算距離
                data->MagicFlyDistance = get_buffer_number(line, &index);       //法術飛行的距離
                data->MagicEffRange = get_buffer_number(line, &index);          //面積法術的作用範圍(對魔法陣適用)
                //6.和法術施放相關的時間數值
                data->SpowerTick = get_buffer_number(line, &index);             //蓄力時間
                data->DamageTick = get_buffer_number(line, &index);             //延時期(多次傷害的間隔時間,)
                data->DeleyTick = get_buffer_number(line, &index);              //技能的持續時間
                data->PantTick = get_buffer_number(line, &index);               //施法完成後需要的喘息時間
                //7.和法術組件相關的數值
                data->HeightLeve = get_buffer_number(line, &index);             //法術組件的高度(地表法術0 ,中層1,高層2)
                //
                data->SelfBreakId = get_buffer_number(line, &index);;            //從自己身上炸出的法術效果的編號
                data->TagBreakId = get_buffer_number(line, &index);;             //在目標點炸開的法術效果的編號
                data->EffBreakId = get_buffer_number(line, &index);;             //命中後的法術效果的編號                
                //
                data->MagicId = get_buffer_number(line, &index);;               //魔法陣..使用的圖檔
			}
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return 0;

error:
    return -1;
}


void	DebugLogGameSkillBase(void)
{
#ifdef	_DEBUG
	TPOS_SKILL_BS	*data = NULL;
	SLONG	i,j;

	log_error(1, ";debug log game skill base");
	
 

	log_error(1, ";Name[32], IconIndex, MpConsume, MpConsumeTick, UseTag, Attrib,  Penetrate, HitType, ActionCount, ActionId, AttackType, AttackRatio, AttachMaxHp, AttachMaxMp, AttachNowHp, AttachNowMp, AttackRatioChange, PhysicAttackReduceRatio, PhysicDefence, MagicDefence, ExplodeRatio, TagAction, TagActionRatio, SelfStatus, SelfStatusRatio, TagStatus, TagStatusRatio, Dispel, Resurgent, MagicDisChargeDistance, MagicBrokenDistance, MagicHitDistance, MagicFlyDistance, MagicEffRange, SpowerTick, DamageTick, DeleyTick, PantTick, HeightLeve, SelfBreakId, TagBreakId, EffBreakId, MagicId");
	for (i=0; i<MAX_GAME_SKILL_BASES; i++)
	{
	    for (j=0;j<MAX_SKILL_LEVELS;j++)
	    {
            data = &GameSkillBase[i][j];
		    sprintf((char *)print_rec, "%-12d,\
		                                %-12d,\
		                                %-12s,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d,\
		                                %-12d",
                                        i,
                                        j,
                                        data->Name,
                                        data->IconIndex,
                                        data->MpConsume,
                                        data->MpConsumeTick,
                                        data->UseTag,
                                        data->Attrib,
                                        data->Kind,                                        
                                        data->Penetrate,
                                        data->HitType,

                                        data->ActionCount,
                                        data->ActionId,

                                        data->AttackType,
                                        data->AttackRatio,

                                        data->AttachMaxHp,
                                        data->AttachMaxMp,
                                        data->AttachNowHp,
                                        data->AttachNowMp,

                                        data->AttackRatioChange,
                                        data->PhysicAttackReduceRatio,
                                        data->PhysicDefence,
                                        data->MagicDefence,
                                        data->ExplodeRatio,
        
                                        data->TagAction,
                                        data->TagActionRatio,

                                        data->SelfStatus,
                                        data->SelfStatusRatio,
    
                                        data->TagStatus,
                                        data->TagStatusRatio,

                                        data->Dispel,
                                        data->Resurgent,

                                        data->MagicDisChargeDistance,
                                        data->MagicBrokenDistance,
                                        data->MagicHitDistance,
                                        data->MagicFlyDistance,
                                        data->MagicEffRange,

                                        data->SpowerTick,
                                        data->DamageTick,
                                        data->DeleyTick,
                                        data->PantTick,

                                        data->HeightLeve,
                                        data->SelfBreakId,
                                        data->TagBreakId,
                                        data->EffBreakId,
                                        
                                        data->MagicId);
	    }
		log_error(1, print_rec);
	}
#endif//_DEBUG
}

void	FreeGameSkillBase(void)
{
	// Do nothing here.
}
//名稱    
CHAR*	GetSkillName(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo][0].Name;
}
//圖標編號
SLONG   GetSkillIconIndex(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo][0].IconIndex;
}
//使用該技能的mp消耗(當蓄力時間為0 ,)
SLONG   GetSkillMpConsume(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MpConsume;
}
//都少次心跳
SLONG   GetSkillMpConsumeTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MpConsumeTick;
}
    
//法術適用的目標(隊友0,敵人1)
SLONG   GetSkillUseTag(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].UseTag;
}
//技能的屬性
SLONG   GetSkillAttrib(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib;
}
//技能類型(被動機能0,釋放類型1,光環2)
SLONG   GetSkillKind(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Kind;
}
//穿透(0,1)
SLONG   GetSkillPenetrate(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Penetrate;
}
//法術命中結算範圍(當體0,多人1)
SLONG   GetSkillHitType(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].HitType;
}
//2.和npc動作相關的技能數據
//npc動作的播放次數
SLONG   GetSkillActionCount(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].ActionCount;
}
//使用該技能需要使用的npc動作的編號
SLONG   GetSkillActionId(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].ActionId;
}
//3.技能的效果數值  
//機能的傷害類型(物理 0,法術 1,特殊 2)
SLONG   GetSkillAttackType(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttackType;
}
//攻擊改變的百分率
SLONG   GetSkillAttackRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttackRatio;
}

//改變生命上限
SLONG   GetSkillAttachMaxHp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachMaxHp;
}
//改變法力上限
SLONG   GetSkillAttachMaxMp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachMaxMp;
}
//改變當前的生命上限
SLONG   GetSkillAttachNowHp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachNowHp;
}
//改變當前的法力上限
SLONG   GetSkillAttachNowMp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachNowMp;
}
//改變攻擊力的百分係數(所有類型的攻擊力)
SLONG   GetSkillAttackRatioChange(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttackRatioChange;
}
//物理傷害減少率
SLONG   GetSkillPhysicAttackReduceRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].PhysicAttackReduceRatio;
}
//改變物理防禦的數值
SLONG   GetSkillPhysicDefence(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].PhysicDefence;
}
//改變魔法防率
SLONG   GetSkillMagicDefence(SLONG lSkillNo, SLONG lLevel)    
{
    return	GameSkillBase[lSkillNo][lLevel].PhysicDefence;
}
//改變的膛爆的機率
SLONG   GetSkillExplodeRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].ExplodeRatio;
}
//目標需要改變到的動作
SLONG   GetSkillTagAction(SLONG lSkillNo, SLONG lLevel)        
{
    return	GameSkillBase[lSkillNo][lLevel].TagAction;
}
//目標會改變到該動作的機率
SLONG   GetSkillTagActionRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagActionRatio;
}
//4.法術的附加效果
//自己會改變的狀態
SLONG   GetSkillSelfStatus(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SelfStatus;
}
    
//自己會改變到該狀態的機率
SLONG   GetSkillSelfStateRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SelfStatusRatio;
}
    
//目標會改變的狀態
SLONG   GetSkillTagStatus(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagStatus;
}
//目標會改變到該狀態的機率
SLONG   GetSkillTagStatusRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagStatusRatio;
}
//消除不良狀態能力
SLONG   GetSkillDispel(SLONG lSkillNo, SLONG lLevel)    
{
    return	GameSkillBase[lSkillNo][lLevel].Dispel;
}
//復活
SLONG   GetSkillResurgent(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Resurgent;
}
//5.法術和範圍相關的數值
//法術釋放距離....施法者需要距離走近目標多少後才能..釋放法術
SLONG   GetSkillMagicDisChargeDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicDisChargeDistance;
}
//法術命中的判定距離...就是法術和npc的距離差多少算命中
SLONG   GetSkillMagicBrokenDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicBrokenDistance;
}
//法術命中後數值結算距離
SLONG   GetSkillMagicHitDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicHitDistance;
}
//法術飛行的距離
SLONG   GetSkillMagicFlyDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicFlyDistance;
}
//面積法術的作用範圍(對魔法陣適用)
SLONG   GetSkillMagicEffRange(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicEffRange;
}
//6.和法術施放相關的時間數值
SLONG   GetSkillSpowerTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SpowerTick;
}
//延時期(多次傷害的間隔時間,)
SLONG   GetSkillDamageTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].DamageTick;
}
//技能的持續時間
SLONG   GetSkillDeleyTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].DeleyTick;
}
//施法完成後需要的喘息時間
SLONG   GetSkillPantTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].PantTick;
}
//7.和法術組件相關的數值
//法術組件的高度(地表法術0 ,中層1,高層2)
SLONG   GetSkillHeightLeve(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].HeightLeve;
}
//法術效果編號.
SLONG   GetSkillSelfBreakId(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SelfBreakId;
}
SLONG   GetSkillTagBreakId(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagBreakId;
}
SLONG   GetSkillEffBreakId(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].EffBreakId;
}
//8.魔法陣相關的數據
SLONG   GetSkillMagicId(SLONG lSkillNo, SLONG lLevel)
{
    //
    return	GameSkillBase[lSkillNo][lLevel].MagicId;
}
//取得技能屬性的判定函數
//該技能可否裝備在左手
SLONG   IsLeftHandSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_LEFT_HAND ? true : false;
}
//該技能可否裝備在右手
SLONG   IsRightHandSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_RIGHT_HAND ? true : false;
}
//該技能是否施陸戰技能
SLONG   IsLandSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_FOR_LAND ? true : false;
}
//該技能是否是海洋技能
SLONG   IsSeaSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_FOR_SEA ? true : false;
}
//該技能 在地圖技能列表上會顯示本技能
//..............該函數可以用來判定是否是...戰鬥技能
SLONG   IsListVisibleSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_LIST_VISIBLE ? true : false;
}
//判斷是否是通用 技能.. 在海洋..和陸地都可以使用
SLONG   IsCommonSkill(SLONG lSkillNo, SLONG lLevel)
{
	if( IsLandSkill(lSkillNo, lLevel) && IsSeaSkill(lSkillNo, lLevel))
		return	true;
	return	false;
}
//顯示在地圖快捷圖標列的最底下
SLONG   IsUnderListSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_UNDER_LIST ? true : false;
}
//和平模式下使用的技能
SLONG   IsPeaceSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_PEACE ? true : false;
}
//戰鬥模式下使用的技能
SLONG   IsFightSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_FIGHT ? true : false;
}
//判斷該技能是否需要蓄力量
SLONG   IsSkillNeedSpower(SLONG lSkillNo, SLONG lLevel)
{
    if (GameSkillBase[lSkillNo][lLevel].SpowerTick <= 0)
        return false;
    return true;         
}
//判斷使用的魔法陣的類型
SLONG   IsSkillNeedSelfMagicArea(SLONG lSkillNo, SLONG lLevel)
{
    if (GameSkillBase[lSkillNo][lLevel].Attrib | MAGIC_ATTRIB_MAGIC_AREA_SELF)
        return true;
    return false;
}
//判斷該借技能是否需要目標npc
//....如果沒有目標npc該技能...不可以使用
SLONG   IsSkillNeedTagNpc(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_NEED_NPC ? true : false;
}
//判斷該技能是否可以對著空地使用
SLONG   IsSkillUsePosition(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_POSITION ? true : false;
}
//判斷該技能的目標是否是普通npc
SLONG   IsSkillUseTagNormalNpc(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_NORMAL_NPC ? true : false;    
}
//判斷該技能的目標是朋友..隊友
SLONG   IsSkillUseTagFriend(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_FRIEND_NPC ? true : false;    
}
//判斷該技能的目標是敵人
SLONG   IsSkillUseTagEnemy(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_ENEMY_NPC ? true : false;    
}
//判斷該技能的目標是自己
SLONG   IsSkillUseTagSelf(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_SELF ? true : false;    
}
//判斷該技能的使用目標是死人
SLONG   IsSkillUseTagDeadNpc(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_DEAD_NPC ? true : false;    
}
//判斷在鼠標的左鍵按下的時候莫個技能可否使用
SLONG   IsSkillMouseDownCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc)
{
    //
    if (lSkillNo<=0 || lSkillNo>=MAX_GAME_SKILL_BASES)
        return false;//不在範圍內的技能..不可使用
    //如果是普通技能..就一定可以使用..(不是戰鬥技能)
    if (IsListVisibleSkill(lSkillNo, lLevel))
    {
        return true;
    }
    //判斷該技能是否需要目標npc
    if (lTagNpc<0)
    {
        //沒有目標npc
        if (IsSkillNeedTagNpc(lSkillNo, 0)) //一定需要目標npc
            return false;
        if (IsSkillUsePosition(lSkillNo, 0))//不可以對空白地點使用
            return false;
        //
        return true;            
    }
    else
    {
        //判斷目標是否是合格的目標
        //1. 判斷是否是死人
        if (IsSkillUseTagDeadNpc(lSkillNo, 0))
        {
            if (!IsCharacterDead(lTagNpc))
            {
                return false;
            }        
        }
        //2.判斷是否是只能對自己使用的
        if (IsSkillUseTagSelf(lSkillNo, lLevel))
        {
            if (lPlayerIndex != lTagNpc)
            {
                return false;
            }
        }
        
        if (IsCharacterTeamMember(lPlayerIndex, lTagNpc))
        {
            //3.判斷是否是只能對敵人使用的
            if (IsSkillUseTagEnemy(lSkillNo, lLevel))
            {            
                return false;
            }                
        }
        else
        {
            //3.判斷是否是智能對隊友使用的
            if (IsSkillUseTagFriend(lSkillNo, lLevel))
            {
                return false;
            }        
        }
        return true;
    }
    return false;
}
//判斷在鼠標的放開的時候莫個技能可否使用...主要都是..需要蓄力的技能
SLONG   IsSkillMouseUpCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc)
{
    //1.只需要判定蓄力的時間是否夠用
    return true;
}
//檔鼠標的左鍵按下的時候判定..需要莫個技能需要改變到的doingkind 
SLONG   GetSkillMosueDownDoingKind(SLONG lSkillNo, SLONG lLevel)
{
    //判斷該技能是需要...蓄力
    if (IsSkillNeedSpower(lSkillNo, lLevel))
        return DOING_KIND_SPOWER;
    //否者默認使用...SKILL_ACTION  的doingkind
    return DOING_KIND_SKILL_ACTION;
}

//mark by lijun 2003-04-21
/*
CHAR*	GetSkillName(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].Name;
}

SLONG   GetSkillAttrib(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].Attrib;
}


SLONG   GetSkillIconIndex(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].IconIndex;
}


SLONG   GetSkillPrepareTicks(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].PrepareTicks;
}


SLONG   GetSkillSpowerTicks(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].SpowerTicks;
}


SLONG   GetSkillDelayTicks(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].DelayTicks;
}


SLONG	GetSkillPersistTicks(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].PersistTicks;
}


SLONG	GetSkillPantTicks(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].PantTicks;
}


SLONG	GetSkillDoTimes(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].DoTimes;
}


SLONG	GetSkillNeedMp(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].NeedMp;
}


SLONG	GetSkillAbnormity(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].Abnormity;
}

SLONG	GetSkillRelation(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].Relation;
}


SLONG	GetSkillExplodeRange(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].ExplodeRange;
}


SLONG   GetSkillExplodeDistance(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].ExplodeDistance;
}


SLONG   GetSkillTargetDistance(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].TargetDistance;
}


SLONG	GetSkillSpecialID(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].SpecialID;
}


SLONG	GetSkillHitType(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].HitType;
}


SLONG	GetSkillPhysicAttackRatio(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].PhysicAttackRatio;
}


SLONG	GetSkillMagicAttackRatio(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].MagicAttackRatio;
}


SLONG	GetSkillSpecialAttackRatio(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].SpecialAttackRatio;
}


SLONG	GetSkillAttachDefenceData(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].AttachDefenceData;
}


SLONG	GetSkillAttachDefenceTicks(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].AttachDefenceTicks;
}


SLONG	GetSkillDodgeRate(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].DodgeRate;
}


SLONG	GetSkillExplodeRate(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].ExplodeRate;
}


SLONG	GetSkillChangeRate(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].ChangeRate;
}

SLONG	GetSkillLevelQuotiety(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].LevelQuotiety;
}

SLONG	GetSkillAttackQuotiety(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].AttackQuotiety;
}

SLONG	GetSkillAttachMaxHp(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].AttachMaxHp;
}

SLONG	GetSkillAttachMaxMp(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].AttachMaxMp;
}

SLONG   IsLeftHandSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_LEFT_HAND ? true : false;
}

SLONG   IsRightHandSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_RIGHT_HAND ? true : false;
}


SLONG   IsLandSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_FOR_LAND ? true : false;
}


SLONG   IsSeaSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_FOR_SEA ? true : false;
}


SLONG   IsListVisibleSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_LIST_VISIBLE ? true : false;
}


SLONG   IsCommonSkill(SLONG lSkillNo)
{
	if( IsLandSkill(lSkillNo) && IsSeaSkill(lSkillNo))
		return	true;
	return	false;
}


SLONG   IsUnderListSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_UNDER_LIST ? true : false;
}


SLONG   IsPeaceSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_PEACE ? true : false;
}


SLONG   IsFightSkill(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_FIGHT ? true : false;
}


SLONG   IsSkillNeedPrepare(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_NEED_PREPARE ? true : false;
}


SLONG   IsSkillNeedSpower(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_NEED_SPOWER ? true : false;
}

SLONG	IsPassiveSkill(SLONG lSkillNo)
{
	return	GameSkillBase[lSkillNo].Attrib & MAGIC_ATTRIB_PASSIVE ? true : false;
}
*/

