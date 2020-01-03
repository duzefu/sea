/*
**	NetGE_Skill.cpp 
**	skill functions.
**
**	Jack, 2003.1.4
*/
#include "NetGE_MainFunc.h"


 

/************************************************************************************************************/
/* �����ܶq                                                                                                 */
/************************************************************************************************************/
TPOS_SKILL_BS	GameSkillBase[MAX_GAME_SKILL_BASES][MAX_SKILL_LEVELS];  //[�ޯ઺�s��][�ޯ઺����]


/************************************************************************************************************/
/* SKILL FUNCTIONS                                                                                          */
/************************************************************************************************************/
SLONG	InitSkillSystem(void)
{
	SLONG	result;

	//
	//��l�ƹC�����~�򥻪�
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
	//��l�ưϰ�a�ϤW�k�N����H�άI�k���.
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
    //�M�Ť��s��l�Ƽƾ�
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
                strcpy(data->Name, (const char *)get_buffer_string(line, &index)); //�W��
                data->IconIndex = get_buffer_number(line, &index);			//�ϼнs��
                data->MpConsume = get_buffer_number(line, &index);          //�ϥθӧޯ઺mp����(��W�O�ɶ���0 ,)
                data->MpConsumeTick = get_buffer_number(line, &index);      //���֦��߸�
                data->UseTag = get_buffer_number(line, &index);           //�k�N�A�Ϊ��ؼ�(����0,�ĤH1)
                data->Attrib = get_buffer_number(line, &index);				//�ޯ઺�ݩ�
                data->Kind = get_buffer_number(line, &index);				//�ޯ�����(�Q�ʾ���0,��������1,����2)
                data->Penetrate = get_buffer_number(line, &index);          //��z(0,1)
                data->HitType = get_buffer_number(line, &index);            //�k�N�R������d��(����0,�h�H1)
                //2.�Mnpc�ʧ@�������ޯ�ƾ�
                data->ActionCount = get_buffer_number(line, &index);        //npc�ʧ@�����񦸼�
                data->ActionId = get_buffer_number(line, &index);           //�ϥθӧޯ�ݭn�ϥΪ�npc�ʧ@���s��
                //3.�ޯ઺�ĪG�ƭ�  
                data->AttackType = get_buffer_number(line, &index);         //���઺�ˮ`����(���z 0,�k�N 1,�S�� 2)
                data->AttackRatio = get_buffer_number(line, &index);        //�������ܪ��ʤ��v

                data->AttachMaxHp = get_buffer_number(line, &index);        //���ܥͩR�W��
                data->AttachMaxMp = get_buffer_number(line, &index);        //���ܪk�O�W��
                data->AttachNowHp = get_buffer_number(line, &index);        //���ܷ�e���ͩR�W��
                data->AttachNowMp = get_buffer_number(line, &index);        //���ܷ�e���k�O�W��
    
                data->AttackRatioChange = get_buffer_number(line, &index);  //���ܧ����O���ʤ��Y��(�Ҧ������������O)
                data->PhysicAttackReduceRatio = get_buffer_number(line, &index);//���z�ˮ`��ֲv
                data->PhysicDefence = get_buffer_number(line, &index);      //���ܪ��z���m���ƭ�
                data->MagicDefence = get_buffer_number(line, &index);       //�����]�k���v
                data->ExplodeRatio = get_buffer_number(line, &index);       //�����]�k���v                
        
                data->TagAction = get_buffer_number(line, &index);          //�ؼлݭn���ܨ쪺�ʧ@
                data->TagActionRatio = get_buffer_number(line, &index);     //�ؼз|���ܨ�Ӱʧ@�����v
                //4.�k�N�����[�ĪG
                data->SelfStatus = get_buffer_number(line, &index);          //�ۤv�|���ܪ����A
                data->SelfStatusRatio = get_buffer_number(line, &index);      //�ۤv�|���ܨ�Ӫ��A�����v
    
                data->TagStatus = get_buffer_number(line, &index);           //�ؼз|���ܪ����A
                data->TagStatusRatio = get_buffer_number(line, &index);       //�ؼз|���ܨ�Ӫ��A�����v

                data->Dispel = get_buffer_number(line, &index);             //�������}���A��O
                data->Resurgent = get_buffer_number(line, &index);          //�_��

                //5.�k�N�M�d��������ƭ�
                data->MagicDisChargeDistance = get_buffer_number(line, &index); //�k�N����Z��....�I�k�̻ݭn�Z������ؼЦh�֫�~��..����k�N
                data->MagicBrokenDistance = get_buffer_number(line, &index);    //�k�N�R�����P�w�Z��...�N�O�k�N�Mnpc���Z���t�h�ֺ�R��
                data->MagicHitDistance = get_buffer_number(line, &index);       //�k�N�R����ƭȵ���Z��
                data->MagicFlyDistance = get_buffer_number(line, &index);       //�k�N���檺�Z��
                data->MagicEffRange = get_buffer_number(line, &index);          //���n�k�N���@�νd��(���]�k�}�A��)
                //6.�M�k�N�I��������ɶ��ƭ�
                data->SpowerTick = get_buffer_number(line, &index);             //�W�O�ɶ�
                data->DamageTick = get_buffer_number(line, &index);             //���ɴ�(�h���ˮ`�����j�ɶ�,)
                data->DeleyTick = get_buffer_number(line, &index);              //�ޯ઺����ɶ�
                data->PantTick = get_buffer_number(line, &index);               //�I�k������ݭn���ݮ��ɶ�
                //7.�M�k�N�ե�������ƭ�
                data->HeightLeve = get_buffer_number(line, &index);             //�k�N�ե󪺰���(�a��k�N0 ,���h1,���h2)
                //
                data->SelfBreakId = get_buffer_number(line, &index);;            //�q�ۤv���W���X���k�N�ĪG���s��
                data->TagBreakId = get_buffer_number(line, &index);;             //�b�ؼ��I���}���k�N�ĪG���s��
                data->EffBreakId = get_buffer_number(line, &index);;             //�R���᪺�k�N�ĪG���s��                
                //
                data->MagicId = get_buffer_number(line, &index);;               //�]�k�}..�ϥΪ�����
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
//�W��    
CHAR*	GetSkillName(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo][0].Name;
}
//�ϼнs��
SLONG   GetSkillIconIndex(SLONG lSkillNo)
{
    return	GameSkillBase[lSkillNo][0].IconIndex;
}
//�ϥθӧޯ઺mp����(��W�O�ɶ���0 ,)
SLONG   GetSkillMpConsume(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MpConsume;
}
//���֦��߸�
SLONG   GetSkillMpConsumeTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MpConsumeTick;
}
    
//�k�N�A�Ϊ��ؼ�(����0,�ĤH1)
SLONG   GetSkillUseTag(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].UseTag;
}
//�ޯ઺�ݩ�
SLONG   GetSkillAttrib(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib;
}
//�ޯ�����(�Q�ʾ���0,��������1,����2)
SLONG   GetSkillKind(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Kind;
}
//��z(0,1)
SLONG   GetSkillPenetrate(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Penetrate;
}
//�k�N�R������d��(����0,�h�H1)
SLONG   GetSkillHitType(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].HitType;
}
//2.�Mnpc�ʧ@�������ޯ�ƾ�
//npc�ʧ@�����񦸼�
SLONG   GetSkillActionCount(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].ActionCount;
}
//�ϥθӧޯ�ݭn�ϥΪ�npc�ʧ@���s��
SLONG   GetSkillActionId(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].ActionId;
}
//3.�ޯ઺�ĪG�ƭ�  
//���઺�ˮ`����(���z 0,�k�N 1,�S�� 2)
SLONG   GetSkillAttackType(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttackType;
}
//�������ܪ��ʤ��v
SLONG   GetSkillAttackRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttackRatio;
}

//���ܥͩR�W��
SLONG   GetSkillAttachMaxHp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachMaxHp;
}
//���ܪk�O�W��
SLONG   GetSkillAttachMaxMp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachMaxMp;
}
//���ܷ�e���ͩR�W��
SLONG   GetSkillAttachNowHp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachNowHp;
}
//���ܷ�e���k�O�W��
SLONG   GetSkillAttachNowMp(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttachNowMp;
}
//���ܧ����O���ʤ��Y��(�Ҧ������������O)
SLONG   GetSkillAttackRatioChange(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].AttackRatioChange;
}
//���z�ˮ`��ֲv
SLONG   GetSkillPhysicAttackReduceRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].PhysicAttackReduceRatio;
}
//���ܪ��z���m���ƭ�
SLONG   GetSkillPhysicDefence(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].PhysicDefence;
}
//�����]�k���v
SLONG   GetSkillMagicDefence(SLONG lSkillNo, SLONG lLevel)    
{
    return	GameSkillBase[lSkillNo][lLevel].PhysicDefence;
}
//���ܪ����z�����v
SLONG   GetSkillExplodeRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].ExplodeRatio;
}
//�ؼлݭn���ܨ쪺�ʧ@
SLONG   GetSkillTagAction(SLONG lSkillNo, SLONG lLevel)        
{
    return	GameSkillBase[lSkillNo][lLevel].TagAction;
}
//�ؼз|���ܨ�Ӱʧ@�����v
SLONG   GetSkillTagActionRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagActionRatio;
}
//4.�k�N�����[�ĪG
//�ۤv�|���ܪ����A
SLONG   GetSkillSelfStatus(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SelfStatus;
}
    
//�ۤv�|���ܨ�Ӫ��A�����v
SLONG   GetSkillSelfStateRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SelfStatusRatio;
}
    
//�ؼз|���ܪ����A
SLONG   GetSkillTagStatus(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagStatus;
}
//�ؼз|���ܨ�Ӫ��A�����v
SLONG   GetSkillTagStatusRatio(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].TagStatusRatio;
}
//�������}���A��O
SLONG   GetSkillDispel(SLONG lSkillNo, SLONG lLevel)    
{
    return	GameSkillBase[lSkillNo][lLevel].Dispel;
}
//�_��
SLONG   GetSkillResurgent(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Resurgent;
}
//5.�k�N�M�d��������ƭ�
//�k�N����Z��....�I�k�̻ݭn�Z������ؼЦh�֫�~��..����k�N
SLONG   GetSkillMagicDisChargeDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicDisChargeDistance;
}
//�k�N�R�����P�w�Z��...�N�O�k�N�Mnpc���Z���t�h�ֺ�R��
SLONG   GetSkillMagicBrokenDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicBrokenDistance;
}
//�k�N�R����ƭȵ���Z��
SLONG   GetSkillMagicHitDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicHitDistance;
}
//�k�N���檺�Z��
SLONG   GetSkillMagicFlyDistance(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicFlyDistance;
}
//���n�k�N���@�νd��(���]�k�}�A��)
SLONG   GetSkillMagicEffRange(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].MagicEffRange;
}
//6.�M�k�N�I��������ɶ��ƭ�
SLONG   GetSkillSpowerTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].SpowerTick;
}
//���ɴ�(�h���ˮ`�����j�ɶ�,)
SLONG   GetSkillDamageTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].DamageTick;
}
//�ޯ઺����ɶ�
SLONG   GetSkillDeleyTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].DeleyTick;
}
//�I�k������ݭn���ݮ��ɶ�
SLONG   GetSkillPantTick(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].PantTick;
}
//7.�M�k�N�ե�������ƭ�
//�k�N�ե󪺰���(�a��k�N0 ,���h1,���h2)
SLONG   GetSkillHeightLeve(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].HeightLeve;
}
//�k�N�ĪG�s��.
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
//8.�]�k�}�������ƾ�
SLONG   GetSkillMagicId(SLONG lSkillNo, SLONG lLevel)
{
    //
    return	GameSkillBase[lSkillNo][lLevel].MagicId;
}
//���o�ޯ��ݩʪ��P�w���
//�ӧޯ�i�_�˳Ʀb����
SLONG   IsLeftHandSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_LEFT_HAND ? true : false;
}
//�ӧޯ�i�_�˳Ʀb�k��
SLONG   IsRightHandSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_RIGHT_HAND ? true : false;
}
//�ӧޯ�O�_�I���ԧޯ�
SLONG   IsLandSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_FOR_LAND ? true : false;
}
//�ӧޯ�O�_�O���v�ޯ�
SLONG   IsSeaSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_FOR_SEA ? true : false;
}
//�ӧޯ� �b�a�ϧޯ�C��W�|��ܥ��ޯ�
//..............�Ө�ƥi�H�ΨӧP�w�O�_�O...�԰��ޯ�
SLONG   IsListVisibleSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_LIST_VISIBLE ? true : false;
}
//�P�_�O�_�O�q�� �ޯ�.. �b���v..�M���a���i�H�ϥ�
SLONG   IsCommonSkill(SLONG lSkillNo, SLONG lLevel)
{
	if( IsLandSkill(lSkillNo, lLevel) && IsSeaSkill(lSkillNo, lLevel))
		return	true;
	return	false;
}
//��ܦb�a�ϧֱ��ϼЦC���̩��U
SLONG   IsUnderListSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_UNDER_LIST ? true : false;
}
//�M���Ҧ��U�ϥΪ��ޯ�
SLONG   IsPeaceSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_PEACE ? true : false;
}
//�԰��Ҧ��U�ϥΪ��ޯ�
SLONG   IsFightSkill(SLONG lSkillNo, SLONG lLevel)
{
    return	GameSkillBase[lSkillNo][lLevel].Attrib & MAGIC_ATTRIB_FIGHT ? true : false;
}
//�P�_�ӧޯ�O�_�ݭn�W�O�q
SLONG   IsSkillNeedSpower(SLONG lSkillNo, SLONG lLevel)
{
    if (GameSkillBase[lSkillNo][lLevel].SpowerTick <= 0)
        return false;
    return true;         
}
//�P�_�ϥΪ��]�k�}������
SLONG   IsSkillNeedSelfMagicArea(SLONG lSkillNo, SLONG lLevel)
{
    if (GameSkillBase[lSkillNo][lLevel].Attrib | MAGIC_ATTRIB_MAGIC_AREA_SELF)
        return true;
    return false;
}
//�P�_�ӭɧޯ�O�_�ݭn�ؼ�npc
//....�p�G�S���ؼ�npc�ӧޯ�...���i�H�ϥ�
SLONG   IsSkillNeedTagNpc(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_NEED_NPC ? true : false;
}
//�P�_�ӧޯ�O�_�i�H��۪Ŧa�ϥ�
SLONG   IsSkillUsePosition(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_POSITION ? true : false;
}
//�P�_�ӧޯ઺�ؼЬO�_�O���qnpc
SLONG   IsSkillUseTagNormalNpc(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_NORMAL_NPC ? true : false;    
}
//�P�_�ӧޯ઺�ؼЬO�B��..����
SLONG   IsSkillUseTagFriend(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_FRIEND_NPC ? true : false;    
}
//�P�_�ӧޯ઺�ؼЬO�ĤH
SLONG   IsSkillUseTagEnemy(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_ENEMY_NPC ? true : false;    
}
//�P�_�ӧޯ઺�ؼЬO�ۤv
SLONG   IsSkillUseTagSelf(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_SELF ? true : false;    
}
//�P�_�ӧޯ઺�ϥΥؼЬO���H
SLONG   IsSkillUseTagDeadNpc(SLONG lSkillNo, SLONG lLevel)
{
    return GameSkillBase[lSkillNo][lLevel].UseTag & MAGIC_TAG_DEAD_NPC ? true : false;    
}
//�P�_�b���Ъ�������U���ɭԲ��ӧޯ�i�_�ϥ�
SLONG   IsSkillMouseDownCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc)
{
    //
    if (lSkillNo<=0 || lSkillNo>=MAX_GAME_SKILL_BASES)
        return false;//���b�d�򤺪��ޯ�..���i�ϥ�
    //�p�G�O���q�ޯ�..�N�@�w�i�H�ϥ�..(���O�԰��ޯ�)
    if (IsListVisibleSkill(lSkillNo, lLevel))
    {
        return true;
    }
    //�P�_�ӧޯ�O�_�ݭn�ؼ�npc
    if (lTagNpc<0)
    {
        //�S���ؼ�npc
        if (IsSkillNeedTagNpc(lSkillNo, 0)) //�@�w�ݭn�ؼ�npc
            return false;
        if (IsSkillUsePosition(lSkillNo, 0))//���i�H��ťզa�I�ϥ�
            return false;
        //
        return true;            
    }
    else
    {
        //�P�_�ؼЬO�_�O�X�檺�ؼ�
        //1. �P�_�O�_�O���H
        if (IsSkillUseTagDeadNpc(lSkillNo, 0))
        {
            if (!IsCharacterDead(lTagNpc))
            {
                return false;
            }        
        }
        //2.�P�_�O�_�O�u���ۤv�ϥΪ�
        if (IsSkillUseTagSelf(lSkillNo, lLevel))
        {
            if (lPlayerIndex != lTagNpc)
            {
                return false;
            }
        }
        
        if (IsCharacterTeamMember(lPlayerIndex, lTagNpc))
        {
            //3.�P�_�O�_�O�u���ĤH�ϥΪ�
            if (IsSkillUseTagEnemy(lSkillNo, lLevel))
            {            
                return false;
            }                
        }
        else
        {
            //3.�P�_�O�_�O����ﶤ�ͨϥΪ�
            if (IsSkillUseTagFriend(lSkillNo, lLevel))
            {
                return false;
            }        
        }
        return true;
    }
    return false;
}
//�P�_�b���Ъ���}���ɭԲ��ӧޯ�i�_�ϥ�...�D�n���O..�ݭn�W�O���ޯ�
SLONG   IsSkillMouseUpCanUse(SLONG lPlayerIndex, SLONG lSkillNo, SLONG lLevel, SLONG lTagNpc)
{
    //1.�u�ݭn�P�w�W�O���ɶ��O�_����
    return true;
}
//�ɹ��Ъ�������U���ɭԧP�w..�ݭn���ӧޯ�ݭn���ܨ쪺doingkind 
SLONG   GetSkillMosueDownDoingKind(SLONG lSkillNo, SLONG lLevel)
{
    //�P�_�ӧޯ�O�ݭn...�W�O
    if (IsSkillNeedSpower(lSkillNo, lLevel))
        return DOING_KIND_SPOWER;
    //�_���q�{�ϥ�...SKILL_ACTION  ��doingkind
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

