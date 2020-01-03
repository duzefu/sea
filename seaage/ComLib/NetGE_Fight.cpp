/*
**	NetGE_Fight.cpp 
**	fight functions.
**
**	Jack, 2003.1.10
*/
#include "NetGE_MainFunc.h"


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	ATTRIB_ATTACK_QUOTIETY		0.01	//���ݩʼv�T�����O���Y��
#define	ATTRIB_DEFENCE_QUOTIETY		0.001	//���ݩʼv�T���m�O���Y��
#define	ATTRIB_MAXHP_QUOTIETY		0.001	//���ݩʼv�T�ͩR�O�W�����Y��
#define	ATTRIB_MAXMP_QUOTIETY		0.001	//���ݩʼv�T���O�W�����Y��


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
//���P¾�~�H���ɯżƾڵ��c
typedef struct tagCAREER_UPGRADE
{
    SLONG   next_exp;           //�U�@�Ÿg���
    SLONG   add_max_hp;         //�W�[��HP�W��
    SLONG   add_max_mp;         //�W�[��MP�W��
    SLONG   add_attrib_point;   //�W�[���ݩ��I
} CAREER_UPGRADE, *LPCAREER_UPGRADE;


typedef	struct tagCAREER_BASE_AFFECT_INFO
{
	double	str_attack;		//�O�q������O���v�T
	double	ins_attack;		//��ı������O���v�T
	double	wit_attack;		//���O������O���v�T
	double	lucky_attack;	//�B�������O���v�T
	//
	double	str_defence;	//�O�q�慨�m�O���v�T
	double	ins_defence;	//��ı�慨�m�O���v�T
	double	wit_defence;	//���O�慨�m�O���v�T
	double	lucky_defence;	//�B��慨�m�O���v�T
	//
	double	str_max_hp;		//�O�q��ͩR�O�W�����v�T
	double	ins_max_hp;		//��ı��ͩR�O�W�����v�T
	double	wit_max_hp;		//���O��ͩR�O�W�����v�T
	double	lucky_max_hp;	//�B���ͩR�O�W�����v�T
	//
	double	str_max_mp;		//�O�q�鷺�O�W�����v�T
	double	ins_max_mp;		//��ı�鷺�O�W�����v�T
	double	wit_max_mp;		//���O�鷺�O�W�����v�T
	double	lucky_max_mp;	//�B��鷺�O�W�����v�T
} CAREER_BASE_AFFECT_INFO, *LPCAREER_BASE_AFFECT_INFO;



// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
CAREER_UPGRADE				l_career_upgrade[MAX_GAME_CAREERS][MAX_CAREER_LEVELS];
CAREER_BASE_AFFECT_INFO		l_career_base_affect_info[MAX_GAME_CAREERS];


/************************************************************************************************************/
/* CAREER UPGRADE FUNCTIONS                                                                                 */
/************************************************************************************************************/
//�\��: ��l�ƤH���ɯżƭȪ�
void    InitCareerUpgrade(void)
{
    SLONG   char_index, level;
    SLONG   n;

    for(char_index = 0; char_index < MAX_GAME_CAREERS; char_index ++)
    {
        for(level = 0; level < MAX_CAREER_LEVELS; level ++)
        {
            n = level + 1;
            //may be we can use : next_exp = (n ^ 4) / 100 + (n ^ 3) * 10 + (n ^ 2) * 100 + n * 100;
            l_career_upgrade[char_index][level].next_exp = n * n * 10;
            l_career_upgrade[char_index][level].add_max_hp = 1;
            l_career_upgrade[char_index][level].add_max_mp = 1;
            l_career_upgrade[char_index][level].add_attrib_point = 1;
        }
    }
}


//�\��: ���J�S�w�H�����ɯżƭȪ�
SLONG   LoadOneCareerUpgrade(SLONG char_index)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    filename[_MAX_FNAME];
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   data_index;
    CAREER_UPGRADE    *data;

    sprintf((char *)filename, "data\\lvup%02d.ini", char_index);
    file_size = load_file_to_buffer(filename, &file_buf);
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
            data_index = get_buffer_number(line, &index);
            if(data_index >= 1 && data_index <= MAX_CAREER_LEVELS)
            {
                data = &l_career_upgrade[char_index][data_index-1];   //���űq1�}�l, ���O�b���s���q0�}�l�s�x.

                data->next_exp = get_buffer_number(line, &index);
                data->add_max_hp = get_buffer_number(line, &index);
                data->add_max_mp = get_buffer_number(line, &index);
                data->add_attrib_point = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


//�\��: ���J�Ҧ��H�����ɯżƭȪ�
SLONG   LoadCareerUpgrade(void)
{
    SLONG   i;

    for(i = 0; i < MAX_GAME_CAREERS; i++)
    {
        LoadOneCareerUpgrade(i);
    }
    return  TTN_OK;
}


//�\��: ����Ҧ��H�����ɯżƭȪ�
void    FreeCareerUpgrade(void)
{
    //nothing to do.
}


//�\��: DEBUG�Ҧ��H�����ɯżƭȪ�
void    DebugLogCareerUpgrade(void)
{
#ifdef  DEBUG
    SLONG   i;

    for(i = 0; i < MAX_GAME_CAREERS; i++)
    {
        DebugLogOneCareerUpgrade(i);
    }
#endif//DEBUG
}


//�\��: DEBUG�S�w�H�����ɯżƭȪ�
void    DebugLogOneCareerUpgrade(SLONG char_index)
{
#ifdef  DEBUG
    char    *lead_line[] = 
    {
        {";======================================================================="},
        {";LV    Experience      AddHP   AddMP   AddPoint                         "},
        {";======================================================================="},
        NULL
    };
    char    line[1024];
    SLONG   i;

    sprintf((char *)line, ";=========================");
    log_error(1, line);
    sprintf((char *)line, ";CHAR %d UPGRADE", char_index);
    log_error(1, line);
    for(i=0; lead_line[i]; i++)
    {
        log_error(1, lead_line[i]);
    }
    for(i=0; i<MAX_CAREER_LEVELS; i++)
    {
        sprintf((char *)line, "%-8d%-16d%-8d%-8d%-8d",
            i+1, 
            l_career_upgrade[char_index][i].next_exp,
            l_career_upgrade[char_index][i].add_max_hp,
            l_career_upgrade[char_index][i].add_max_mp,
            l_career_upgrade[char_index][i].add_attrib_point
            );
        log_error(1, line);
    }
#endif//DEBUG
}


//�\��: ��o����ɨ�U�ũһݭn���g���
SLONG   GetCareerUpgradeExp(SLONG char_index, SLONG level)
{
    return  l_career_upgrade[char_index][level].next_exp;
}

//�\��: ��o����ɯū�W�[��hp�W����
SLONG   GetCareerUpgradeAddMaxHp(SLONG char_index, SLONG level)
{
    return  l_career_upgrade[char_index][level].add_max_hp;
}

//�\��: ��o����ɯū�W�[��mp�W����
SLONG   GetCareerUpgradeAddMaxMp(SLONG char_index, SLONG level)
{
    return  l_career_upgrade[char_index][level].add_max_mp;
}

//�\��: ��o����ɯū�W�[���ݩ��I
SLONG   GetCareerUpgradeAddAttribPoint(SLONG char_index, SLONG level)
{
    return  l_career_upgrade[char_index][level].add_attrib_point;
}

//�\��: ������o�g��ȫ᪺�p��
SLONG   ComputeCharacterUpgradeResult(SLONG lIndex, SLONG level, SLONG exp, CHARACTER_UPGRADE_RESULT *lpResult)
{
	SLONG	char_index;
    SLONG	next_level;
	SLONG	next_exp;
    SLONG	add_max_hp, add_max_mp, add_attrib_point;
	SLONG	levelup_hp, levelup_mp, max_hp, max_mp;
	SLONG	attrib_point;

    //���Ť��X�k�Ϊ̤w�g�F��̰���
    if(level < 0 || level >= MAX_CAREER_LEVELS-1)
        return  false;

	//��o���a��¾�~����
	char_index = GetCharacterCareer(lIndex);
	char_index = CharCareer2IntCareer(char_index);

    next_level = level + 1;
    next_exp = l_career_upgrade[char_index][next_level].next_exp;
    if(exp < next_exp)
        return  false;

	//��o�ɯżv�T��
    add_max_hp = 0;
    add_max_mp = 0;
    add_attrib_point = 0;
    while(exp >= next_exp)
    {
        add_max_hp += l_career_upgrade[char_index][next_level].add_max_hp;
        add_max_mp += l_career_upgrade[char_index][next_level].add_max_mp;
        add_attrib_point += l_career_upgrade[char_index][next_level].add_attrib_point;

        next_level++;
        if(next_level < MAX_CAREER_LEVELS)
            next_exp = l_career_upgrade[char_index][next_level].next_exp;
        else
        {
            next_exp = MAX_CAREER_EXP;
            break;
        }
    }

	//�p��H�������ƭ�
	levelup_hp = GetCharacterLevelUpHp(lIndex);
	levelup_hp += add_max_hp;
	levelup_hp = CLAMP(levelup_hp, 0, MAX_CAREER_HP);
	SetCharacterLevelUpHp(lIndex, (UHINT)levelup_hp);
	max_hp = ComputeCharacterFinalMaxHp(lIndex);
	SetCharacterHp(lIndex, (UHINT)max_hp);

	levelup_mp = GetCharacterLevelUpMp(lIndex);
	levelup_mp += add_max_mp;
	SetCharacterLevelUpMp(lIndex, (UHINT)levelup_mp);
	levelup_mp = CLAMP(levelup_mp, 0, MAX_CAREER_MP);
	max_mp = ComputeCharacterFinalMaxMp(lIndex);
	SetCharacterMp(lIndex, (UHINT)max_mp);

	attrib_point = GetCharacterPropertyPoint(lIndex);
	attrib_point += add_attrib_point;
	attrib_point = CLAMP(attrib_point, 0, MAX_CAREER_PROPERTY_POINT);
	SetCharacterPropertyPoint(lIndex, (UHINT)attrib_point);

	SetCharacterNextExp(lIndex, (ULONG)next_exp);
	SetCharacterLevel(lIndex, (UHINT)next_level);

	//��^�p�⵲�G
	if(lpResult)
	{
		lpResult->max_hp = (UHINT)max_hp;
		lpResult->max_mp = (UHINT)max_mp;
		lpResult->property_point = (UHINT)attrib_point;
		lpResult->next_exp = (ULONG)next_exp;
		lpResult->level = (UHINT)next_level;
	}
    return  true;
}


/******************************************************************************************************************/
/* �̰��ݩ� �� �@�ǰ򥻭Ȫ��v�T                                                                                 */
/******************************************************************************************************************/
//�\��: ��l�ƨ���򥻭ȼv�TMP�ƾ�
void    InitCareerBaseAffectInfo(void)
{
    memset(l_career_base_affect_info, 0, sizeof(l_career_base_affect_info));
}


//�\��: ���J����򥻭ȼv�TMP�ƾ�
SLONG   LoadCareerBaseAffectInfo(void)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    filename[_MAX_FNAME];
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   data_index;
    CAREER_BASE_AFFECT_INFO  *data;

    sprintf((char *)filename, "data\\manbase.ini");
    file_size = load_file_to_buffer(filename, &file_buf);
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
            data_index = get_buffer_number(line, &index);
            if(data_index >= 0 && data_index < MAX_GAME_CAREERS)
            {
                data = &l_career_base_affect_info[data_index];

				// skip string for career name comment
				get_buffer_string(line, &index);

				data->str_attack = ATTRIB_ATTACK_QUOTIETY * get_buffer_number(line, &index);
				data->ins_attack = ATTRIB_ATTACK_QUOTIETY * get_buffer_number(line, &index);
				data->wit_attack = ATTRIB_ATTACK_QUOTIETY * get_buffer_number(line, &index);
				data->lucky_attack = ATTRIB_ATTACK_QUOTIETY * get_buffer_number(line, &index);
				//
				data->str_defence = ATTRIB_DEFENCE_QUOTIETY * get_buffer_number(line, &index);
				data->ins_defence = ATTRIB_DEFENCE_QUOTIETY * get_buffer_number(line, &index);
				data->wit_defence = ATTRIB_DEFENCE_QUOTIETY * get_buffer_number(line, &index);
				data->lucky_defence = ATTRIB_DEFENCE_QUOTIETY * get_buffer_number(line, &index);
				//
				data->str_max_hp = ATTRIB_MAXHP_QUOTIETY * get_buffer_number(line, &index);
				data->ins_max_hp = ATTRIB_MAXHP_QUOTIETY * get_buffer_number(line, &index);
				data->wit_max_hp = ATTRIB_MAXHP_QUOTIETY * get_buffer_number(line, &index);
				data->lucky_max_hp = ATTRIB_MAXHP_QUOTIETY * get_buffer_number(line, &index);
				//
				data->str_max_mp = ATTRIB_MAXMP_QUOTIETY * get_buffer_number(line, &index);
				data->ins_max_mp = ATTRIB_MAXMP_QUOTIETY * get_buffer_number(line, &index);
				data->wit_max_mp = ATTRIB_MAXMP_QUOTIETY * get_buffer_number(line, &index);
				data->lucky_max_mp = ATTRIB_MAXMP_QUOTIETY * get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


//�\��: ���񨤦�򥻭ȼv�TMP�ƾ�
void    FreeCareerBaseAffectInfo(void)
{
    //nothing to do.
}


void	DebugLogCareerBaseAffectInfo(void)
{
	//do nothing now...
}

//�\��: �� ���ݩ� �p�� �򥻧����O�v�T�ʤ���
UHINT	ComputeCareerBaseAttackRatio(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky)
{
	double	result;
	UHINT	base_att_ratio;

	result = l_career_base_affect_info[char_index].str_attack * str + 
		l_career_base_affect_info[char_index].ins_attack * ins +
		l_career_base_affect_info[char_index].wit_attack * wit +
		l_career_base_affect_info[char_index].lucky_attack * lucky;
	
	base_att_ratio = (UHINT)(result * 100 + 0.5);	// % value

	if(base_att_ratio > MAX_CAREER_BASE_ATTACK_RATIO)
		base_att_ratio = MAX_CAREER_BASE_ATTACK_RATIO;

	return (UHINT)base_att_ratio;
}

//�\��: �� ���ݩ� �p�� �򥻨��m�O
UHINT	ComputeCareerBaseDefence(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky)
{
	double	base_defence;
	SLONG	defence;

	base_defence = l_career_base_affect_info[char_index].str_defence * str +
		l_career_base_affect_info[char_index].ins_defence * ins +
		l_career_base_affect_info[char_index].wit_defence * wit +
		l_career_base_affect_info[char_index].lucky_defence * lucky;

	defence = (SLONG)base_defence;
	if(defence > MAX_CAREER_DEFENCE)
		defence = MAX_CAREER_DEFENCE;

	return	(UHINT)defence;
}

//�\��: �� ���ݩ� �p�� �򥻥ͩR�O�W��
UHINT	ComputeCareerBaseMaxHp(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky)
{
	double	base_max_hp;
	SLONG	max_hp;

	base_max_hp = l_career_base_affect_info[char_index].str_max_hp * str +
		l_career_base_affect_info[char_index].ins_max_hp * ins +
		l_career_base_affect_info[char_index].wit_max_hp * wit +
		l_career_base_affect_info[char_index].lucky_max_hp * lucky;
	max_hp = (SLONG)base_max_hp;
	if(max_hp > MAX_CAREER_HP)
		max_hp = MAX_CAREER_HP;

	return	(UHINT)max_hp;
}

//�\��: �� ���ݩ� �p�� �򥻤��O�W��
UHINT	ComputeCareerBaseMaxMp(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky)
{
	double	base_max_mp;
	SLONG	max_mp;

	base_max_mp = l_career_base_affect_info[char_index].str_max_mp * str +
		l_career_base_affect_info[char_index].ins_max_mp * ins +
		l_career_base_affect_info[char_index].wit_max_mp * wit +
		l_career_base_affect_info[char_index].lucky_max_mp * lucky;
	max_mp = (SLONG)base_max_mp;
	if(max_mp > MAX_CAREER_MP)
		max_mp = MAX_CAREER_MP;

	return	(UHINT)max_mp;
}


SLONG	CharCareer2IntCareer(SLONG career)
{
	switch(career)
	{
	case CAREER_GENERAL:	return 0;
	case CAREER_SWORDER:	return 1;
	case CAREER_THIEF:		return 2;
	case CAREER_TRADER:		return 3;
	case CAREER_EXPLORER:	return 4;
	case CAREER_CLERIC:		return 5;
	case CAREER_HOROSCOPER:	return 6;
	default:				return 0;
	}
}

/************************************************************************************************************/
/* �p��̰��ݩ�(�O�q,��ı,���O,�B��)���̲׭�                                                              */
/************************************************************************************************************/
UHINT	ComputeCharacterFinalStr(SLONG lIndex)
{
	UHINT	init_str;			//��l�Ʈɳ]�w���O�q��
	UHINT	level_up_str;		//�ɯŮɤ��t���O�q��
	ULONG	final_str;			//�̲פO�q

	init_str = GetCharacterInitStr(lIndex);
	level_up_str = GetCharacterLevelUpStr(lIndex);

	final_str = init_str + level_up_str;
	if(final_str > MAX_CAREER_STR)
		final_str = MAX_CAREER_STR;

	SetCharacterFinalStr(lIndex, (UHINT)final_str);

	return	(UHINT)final_str;
}

UHINT	ComputeCharacterFinalIns(SLONG lIndex)
{
	UHINT	init_ins;			//��l�Ʈɳ]�w����ı
	UHINT	level_up_ins;		//�ɯŮɤ��t����ı
	ULONG	final_ins;			//�̲ת�ı

	init_ins = GetCharacterInitIns(lIndex);
	level_up_ins = GetCharacterLevelUpIns(lIndex);

	final_ins = init_ins + level_up_ins;
	if(final_ins > MAX_CAREER_INS)
		final_ins = MAX_CAREER_INS;

	SetCharacterFinalIns(lIndex, (UHINT)final_ins);

	return	(UHINT)final_ins;
}


UHINT	ComputeCharacterFinalWit(SLONG lIndex)
{
	UHINT	init_wit;			//��l�Ʈɳ]�w����ı
	UHINT	level_up_wit;		//�ɯŮɤ��t����ı
	ULONG	final_wit;			//�̲ת�ı

	init_wit = GetCharacterInitWit(lIndex);
	level_up_wit = GetCharacterLevelUpWit(lIndex);

	final_wit = init_wit + level_up_wit;
	if(final_wit > MAX_CAREER_WIT)
		final_wit = MAX_CAREER_WIT;

	SetCharacterFinalWit(lIndex, (UHINT)final_wit);

	return	(UHINT)final_wit;
}


UHINT	ComputeCharacterFinalLucky(SLONG lIndex)
{
	UHINT	init_lucky;			//��l�Ʈɳ]�w���B��
	UHINT	level_up_lucky;		//�ɯŮɤ��t���B��
	ULONG	final_lucky;		//�̲׹B��

	init_lucky = GetCharacterInitLucky(lIndex);
	level_up_lucky = GetCharacterLevelUpLucky(lIndex);

	final_lucky = init_lucky + level_up_lucky;
	if(final_lucky > MAX_CAREER_LUCKY)
		final_lucky = MAX_CAREER_LUCKY;

	SetCharacterFinalLucky(lIndex, (UHINT)final_lucky);

	return	(UHINT)final_lucky;
}


/************************************************************************************************************/
/* �����O�p��                                                                                               */
/************************************************************************************************************/
UHINT	ComputeCharacterAttribAttackRatio(SLONG lIndex)
{
	UHINT	str, ins, wit, lucky;
	SLONG	career, career_index;
	SLONG	ratio;

	str = GetCharacterFinalStr(lIndex);
	ins = GetCharacterFinalIns(lIndex);
	wit = GetCharacterFinalWit(lIndex);
	lucky = GetCharacterFinalLucky(lIndex);
	career = GetCharacterCareer(lIndex);
	career_index = CharCareer2IntCareer(career);
	ratio = ComputeCareerBaseAttackRatio(career_index, str, ins, wit, lucky);

	SetCharacterAttribAttRatio(lIndex, (UHINT)ratio);

	return	(UHINT)ratio;
}

//�\��: �p��H����X�ޯ������O���v�T�ʤ���
UHINT	ComputeCharacterSkillAttackRatio(SLONG lIndex)
{
	// Jack, TODO [1/20/2003]
	// �����a���̰򥻧ޯ઺���� * �ӧޯ઺�ƭȪ��� AttackQuotiety.
	return	50;
}


//�\��: �p��H���˳ƪ��򥻧����O
UHINT	ComputeCharacterEquipBaseAttack(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	attack;

	attack = 0;
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		attack += GetItemAttackData(&item);
	}
	attack = CLAMP(attack, 0, MAX_CAREER_ATTACK);
	SetCharacterEquipBaseAtt(lIndex, (UHINT)attack);

	return	(UHINT)attack;
}


//�\��G�p��H���˳ƫ᪺�̲װ򥻧����O(��ڧ������ٻݭn�M�ޯ൥�i��B��)
UHINT	ComputeCharacterFinalAttack(SLONG lIndex)
{
	SLONG	equip_attack;
	SLONG	base_ratio;
	SLONG	final_attack;
	SLONG	skill_ratio;
	double	attack;

	equip_attack = GetCharacterEquipBaseAtt(lIndex);
	base_ratio = GetCharacterAttribAttRatio(lIndex);
	skill_ratio = GetCharacterSkillAttackRatio(lIndex);

	attack = equip_attack * (base_ratio * 0.01) * (1.0 + skill_ratio * 0.01);

	final_attack = (SLONG)attack;
	if(final_attack > MAX_CAREER_ATTACK)
		final_attack = MAX_CAREER_ATTACK;

	SetCharacterFinalAtt(lIndex, (UHINT)final_attack);

	return	(UHINT)final_attack;
}


//�\��G�p��H���ϥΧޯ�ɪ��̲ק����O�A���G�N�s��b�H������Ƶ��c���C
void	ComputeCharacterFinalAttackWithSkill(SLONG lIndex, SLONG lSkillNo)
{
	SLONG	final_attack;
	SLONG	skill_phy_ratio, skill_magic_ratio, skill_spec_ratio;
	SLONG	base_phy_attack, base_magic_attack, base_spec_attack;
	SLONG	final_phy_attack, final_magic_attack, final_spec_attack;
	SLONG	equip_added_magic_attack;
	SLONG	equip_added_spec_attack;

	final_attack = GetCharacterFinalAtt(lIndex);

    //
	skill_phy_ratio = 0;
	skill_magic_ratio = 0;
	skill_spec_ratio = 0;
    //
    switch (GetSkillAttackType(lSkillNo, 0))
    {
    case MAGIC_ATTACK_TYPE_PHYSICS://���z��������
	    skill_phy_ratio = GetSkillAttackRatio(lSkillNo, 0);
        break;
    case MAGIC_ATTACK_TYPE_MAGIC://�k�N��������
	    skill_phy_ratio = GetSkillAttackRatio(lSkillNo, 0);
        break;    
    case MAGIC_ATTACK_TYPE_SPECIAL://�S���������    
	    skill_phy_ratio = GetSkillAttackRatio(lSkillNo, 0);
        break;    
    }


	base_phy_attack = final_attack * skill_phy_ratio / 100;
	base_magic_attack = final_attack * skill_magic_ratio / 100;
	base_spec_attack = final_attack * skill_spec_ratio / 100;

	equip_added_magic_attack = GetCharacterEquipAddedMagicAtt(lIndex);
	equip_added_spec_attack = GetCharacterEquipAddedSpecAtt(lIndex);

	final_phy_attack = base_phy_attack;
	if(final_phy_attack > MAX_CAREER_ATTACK)
		final_phy_attack = MAX_CAREER_ATTACK;
	final_magic_attack = base_magic_attack + equip_added_magic_attack;
	if(final_magic_attack > MAX_CAREER_ATTACK)
		final_magic_attack = MAX_CAREER_ATTACK;
	final_spec_attack = base_spec_attack + equip_added_spec_attack;
	if(final_spec_attack > MAX_CAREER_ATTACK)
		final_spec_attack = MAX_CAREER_ATTACK;

	SetCharacterFinalPhysicAtt(lIndex, (UHINT)final_phy_attack);
	SetCharacterFinalMagicAtt(lIndex, (UHINT)final_magic_attack);
	SetCharacterFinalSpecAtt(lIndex, (UHINT)final_spec_attack);
}


/************************************************************************************************************/
/* ���m�O�p��                                                                                               */
/************************************************************************************************************/
//�\��G�p��H�����|���򥻭ȼv�T���򥻨��m�O
UHINT	ComputeCharacterBaseDefence(SLONG lIndex)
{
	SLONG	base_defence;
	SLONG	career, char_index;
	SLONG	str, ins, wit, lucky;

	str = GetCharacterFinalStr(lIndex);
	ins = GetCharacterFinalIns(lIndex);
	wit = GetCharacterFinalWit(lIndex);
	lucky = GetCharacterFinalLucky(lIndex);

	career = GetCharacterCareer(lIndex);
	char_index = CharCareer2IntCareer(career);
	base_defence = ComputeCareerBaseDefence(char_index, str, ins, wit, lucky);

	SetCharacterBaseDefence(lIndex, (UHINT)base_defence);

	return	(UHINT)base_defence;
}

//�\��G�p��H���˳ƪ����m�O�ƭ�
UHINT	ComputeCharacterEquipDefence(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_defence;

	equip_defence = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence += GetItemDefenceData(&item);
	}

	if(equip_defence > MAX_CAREER_DEFENCE)
		equip_defence = MAX_CAREER_DEFENCE;

	SetCharacterEquipDefence(lIndex, (UHINT)equip_defence);
	
	return	(UHINT)equip_defence;
}

//�\��: �p��H����X�ޯ�慨�m�O���v�T
UHINT	ComputeCharacterSkillDefence(SLONG lIndex)
{
	// Jack, TODO [2/18/2003]
	return	50;
}



//�\��G�p��H�����̲ר��m�O
UHINT	ComputeCharacterFinalDefence(SLONG lIndex)
{
	SLONG	base_defence, equip_defence, skill_defence;
	SLONG	final_defence;

	base_defence = GetCharacterBaseDefence(lIndex);
	equip_defence = GetCharacterEquipDefence(lIndex);
	skill_defence = GetCharacterSkillDefence(lIndex);

	final_defence = base_defence + equip_defence + skill_defence;
	if(final_defence > MAX_CAREER_DEFENCE)
		final_defence = MAX_CAREER_DEFENCE;

	SetCharacterFinalDefence(lIndex, (UHINT)final_defence);

	return	(UHINT)final_defence;
}

/************************************************************************************************************/
/* ���z�v�p��                                                                                               */
/************************************************************************************************************/
//�\��G�p��H���˳ƪ����z�v
UHINT	ComputeCharacterEquipExplodeRate(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	explode_rate;

	explode_rate = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		explode_rate += GetItemExplodeRate(&item);
	}

	if(explode_rate > MAX_CAREER_EXPLODE_RATE)
		explode_rate = MAX_CAREER_EXPLODE_RATE;

	SetCharacterEquipExplodeRate(lIndex, (UHINT)explode_rate);
	
	return	(UHINT)explode_rate;
}


//�\��: �p��H����X�ޯ�｣�z�v�v�T�ʤ���
UHINT	ComputeCharacterSkillExplodeRate(SLONG lIndex)
{
	// Jack, TODO [2/18/2003]
	return	50;
}

//�\��G�p��H�����̲׽��z�v
UHINT	ComputeCharacterFinalExplodeRate(SLONG lIndex)
{
	UHINT	equip_explode_rate;
	UHINT	skill_explode_rate;
	SLONG	final_explode_rate;

	equip_explode_rate = GetCharacterEquipExplodeRate(lIndex);
	skill_explode_rate = GetCharacterSkillExplodeRate(lIndex);
	final_explode_rate = equip_explode_rate + skill_explode_rate;
	final_explode_rate = CLAMP(final_explode_rate, 0, MAX_CAREER_EXPLODE_RATE);
	SetCharacterFinalExplodeRate(lIndex, (UHINT)final_explode_rate);

	return	(UHINT)final_explode_rate;
}

/************************************************************************************************************/
/* �p���ܤO(�ʤ���)                                                                                       */
/************************************************************************************************************/
//�\��G�p��H���˳ƪ���ܤO(�ʤ���)
UHINT	ComputeCharacterEquipResistRatio(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_resist;

	equip_resist = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_resist += GetItemResistRatio(&item);
	}

	if(equip_resist > MAX_CAREER_RESIST)
		equip_resist = MAX_CAREER_RESIST;

	SetCharacterEquipResistRatio(lIndex, (UHINT)equip_resist);
	
	return	(UHINT)equip_resist;
}


//�\��: �p��H�����̲ש�ܤO
UHINT	ComputeCharacterFinalResist(SLONG lIndex)
{
	UHINT	equip_resist, final_resist;

	equip_resist = GetCharacterEquipResistRatio(lIndex);
	final_resist = equip_resist;
	SetCharacterFinalResist(lIndex, final_resist);

	return	final_resist;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ͩR�O�W��
//
// �զ�:
//   (1) AttribHp: ��(�ݩ�)�ͩR�O�W��
//       ����: �ѤH���O�q/��ı/���O/�B��|�����ݩʹB��o��.
//
//	 (2) LevelUpHp: �ɯŲ֭p��o���ͩR�O�W��
//
//   (3) EquipHp: �H���Ҧ��˳ƪ��[���ͩR�O�W��
//      
//   (4) SkillHp: �H���Ҧ��ޯ���[���ͩR�O�W��
//
//	 (5) MaxHp: �̲ת��ͩR�O�W��
//       �⦡: MaxHp = AttribHp + LevelUpHp + EquipHp + SkillHp.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//�\��: �p���(�ݩ�)�ͩR�O�W��
UHINT	ComputeCharacterAttribMaxHp(SLONG lIndex)
{
	SLONG	career;
	SLONG	str, ins, wit, lucky;
	UHINT	attrib_hp;

	career = GetCharacterCareer(lIndex);
	career = CharCareer2IntCareer(career);
	str = GetCharacterFinalStr(lIndex);
	ins = GetCharacterFinalIns(lIndex);
	wit = GetCharacterFinalWit(lIndex);
	lucky = GetCharacterFinalLucky(lIndex);
	attrib_hp = ComputeCareerBaseMaxHp(career, str, ins, wit, lucky);
	SetCharacterAttribHp(lIndex, attrib_hp);

	return	attrib_hp;
}

//�\��: �p��H���˳Ƽv�T�ͩR�O�W��
UHINT	ComputeCharacterEquipMaxHp(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_hp;

	equip_hp = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_hp += GetItemAddedMaxHp(&item);
	}

	if(equip_hp > MAX_CAREER_HP)
		equip_hp = MAX_CAREER_HP;

	SetCharacterEquipHp(lIndex, (UHINT)equip_hp);
	
	return	(UHINT)equip_hp;
}

//�\��: �p��H���ޯ�v�T���ͩR�O�W��
UHINT	ComputeCharacterSkillMaxHp(SLONG lIndex)
{
	SLONG	i, skill_no, skill_level;
	SLONG	max_hp, total_max_hp;
	
	total_max_hp = 0;
	for(i=0; i<MAX_CHARACTER_SKILLS; i++)
	{
		skill_no = GetCharacterSkillNo(lIndex, i);
		if(skill_no >= 0)
		{
			skill_level = GetCharacterSkillLevel(lIndex, i);
			max_hp = GetSkillAttachMaxHp(skill_no, 0);
			
			// Jack, Need to be modified... [2/17/2003]
			// Compute max_hp with skill_no and skill_level. 
			// Here is the simply implementation.
			//
			max_hp = max_hp + max_hp * skill_level / MAX_SKILL_LEVELS;
			total_max_hp += max_hp;
		}
	}
	total_max_hp = CLAMP(total_max_hp, 0, MAX_CAREER_HP);
	SetCharacterSkillHp(lIndex, (UHINT)total_max_hp);

	return	(UHINT)total_max_hp;
}


//�\��: �p��H�����̲ץͩR�O�W��
UHINT	ComputeCharacterFinalMaxHp(SLONG lIndex)
{
	UHINT	attrib_max_hp, levelup_max_hp;
	UHINT	equip_max_hp, skill_max_hp;
	ULONG	final_max_hp;

	attrib_max_hp = GetCharacterAttribHp(lIndex);
	levelup_max_hp = GetCharacterLevelUpHp(lIndex);
	equip_max_hp = GetCharacterEquipHp(lIndex);
	skill_max_hp = GetCharacterSkillHp(lIndex);
	final_max_hp = attrib_max_hp + levelup_max_hp + equip_max_hp + skill_max_hp;
	final_max_hp = CLAMP(final_max_hp, 0, MAX_CAREER_HP);
	SetCharacterMaxHp(lIndex, (UHINT)final_max_hp);

	return	(UHINT)final_max_hp;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���O�W��
//
// �զ�:
//   (1) AttribMp: ��(�ݩ�)���O�W��
//       ����: �ѤH���O�q/��ı/���O/�B��|�����ݩʹB��o��.
//
//	 (2) LevelUpMp: �ɯŲ֭p��o�����O�W��
//
//   (3) EquipMp: �H���Ҧ��˳ƪ��[�����O�W��
//      
//   (4) SkillMp: �H���Ҧ��ޯ���[�����O�W��
//
//	 (5) MaxMp: �̲ת����O�W��
//       �⦡: MaxMp = AttribMp + LevelUpMp + EquipMp + SkillMp.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//�\��: �p���(�ݩ�)���O�W��
UHINT	ComputeCharacterAttribMaxMp(SLONG lIndex)
{
	SLONG	career;
	SLONG	str, ins, wit, lucky;
	UHINT	attrib_mp;

	career = GetCharacterCareer(lIndex);
	career = CharCareer2IntCareer(career);
	str = GetCharacterFinalStr(lIndex);
	ins = GetCharacterFinalIns(lIndex);
	wit = GetCharacterFinalWit(lIndex);
	lucky = GetCharacterFinalLucky(lIndex);
	attrib_mp = ComputeCareerBaseMaxMp(career, str, ins, wit, lucky);
	SetCharacterAttribMp(lIndex, attrib_mp);

	return	attrib_mp;
}

//�\��: �p��H���˳Ƽv�T���O�W��
UHINT	ComputeCharacterEquipMaxMp(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_mp;

	equip_mp = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_mp += GetItemAddedMaxMp(&item);
	}

	if(equip_mp > MAX_CAREER_MP)
		equip_mp = MAX_CAREER_MP;

	SetCharacterEquipMp(lIndex, (UHINT)equip_mp);
	
	return	(UHINT)equip_mp;
}

//�\��: �p��H���ޯ�v�T�����O�W��
UHINT	ComputeCharacterSkillMaxMp(SLONG lIndex)
{
	SLONG	i, skill_no, skill_level;
	SLONG	max_mp, total_max_mp;
	
	total_max_mp = 0;
	for(i=0; i<MAX_CHARACTER_SKILLS; i++)
	{
		skill_no = GetCharacterSkillNo(lIndex, i);
		if(skill_no >= 0)
		{
			skill_level = GetCharacterSkillLevel(lIndex, i);
			max_mp = GetSkillAttachMaxHp(skill_no, 0);
			
			// Jack, Need to be modified... [2/17/2003]
			// Compute max_hp with skill_no and skill_level. 
			// Here is the simply implementation.
			//
			max_mp = max_mp + max_mp * skill_level / MAX_SKILL_LEVELS;
			total_max_mp += max_mp;
		}
	}
	total_max_mp = CLAMP(total_max_mp, 0, MAX_CAREER_HP);
	SetCharacterSkillMp(lIndex, (UHINT)total_max_mp);
	return	(UHINT)total_max_mp;
}

//�\��: �p��H�����̲פ��O�W��
UHINT	ComputeCharacterFinalMaxMp(SLONG lIndex)
{
	UHINT	attrib_max_mp, levelup_max_mp;
	UHINT	equip_max_mp, skill_max_mp;
	ULONG	final_max_mp;

	attrib_max_mp = GetCharacterAttribMp(lIndex);
	levelup_max_mp = GetCharacterLevelUpMp(lIndex);
	equip_max_mp = GetCharacterEquipMp(lIndex);
	skill_max_mp = GetCharacterSkillMp(lIndex);
	final_max_mp = attrib_max_mp + levelup_max_mp + equip_max_mp + skill_max_mp;
	final_max_mp = CLAMP(final_max_mp, 0, MAX_CAREER_MP);
	SetCharacterMaxMp(lIndex, (UHINT)final_max_mp);

	return	(UHINT)final_max_mp;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���a�հt�ݩ��I
//
// ����: 
//	(1) ���a�հt�ݩ��I��, �N�վ�᪺�ݩ��I�����[�b LevelUp$$$ �W, �P��, �ٷ|�O�s�b Point$$$ �W, �H
//      �ƪ��a�վ�^��.
//  (2) ��վ㧹��, ���a�����վ㤶����, �t�βM�� Point$$$ ���ȥH�����վ�, �o��, �i�H������a�U����
//      �}������, �N����A�^�դW���վ㪺��.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//�\��: �p��H�����ݩ�(��,��,�ͩR,���O)���|�����ݩʪ��v�T���G.
//
// base attributes : str, ins, wit, lucky
//    affect datas : attack, defence, max_hp(hp), max_mp(mp)
//
void	UpdateCharacterDataWithBaseAttrib(SLONG lIndex)
{
	SLONG	career;
	UHINT	attack_ratio, base_defence, base_max_hp, base_max_mp;
	UHINT	final_str, final_ins, final_wit, final_lucky;
	UHINT	final_att, final_defence, final_max_hp, final_max_mp, hp, mp;

	final_str = GetCharacterFinalStr(lIndex);
	final_ins = GetCharacterFinalIns(lIndex);
	final_wit = GetCharacterFinalWit(lIndex);
	final_lucky = GetCharacterFinalLucky(lIndex);
	career = GetCharacterCareer(lIndex);
	career = CharCareer2IntCareer(career);
	
	attack_ratio = ComputeCareerBaseAttackRatio(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterAttribAttRatio(lIndex, attack_ratio);
	final_att = ComputeCharacterFinalAttack(lIndex);
	
	base_defence = ComputeCareerBaseDefence(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterBaseDefence(lIndex, base_defence);
	final_defence = ComputeCharacterFinalDefence(lIndex);
	
	base_max_hp = ComputeCareerBaseMaxHp(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterAttribHp(lIndex, base_max_hp);
	final_max_hp = ComputeCharacterFinalMaxHp(lIndex);
	hp = GetCharacterHp(lIndex);
	hp = CLAMP(hp, 0, final_max_hp);
	SetCharacterHp(lIndex, hp);
	
	base_max_mp = ComputeCareerBaseMaxMp(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterAttribMp(lIndex, base_max_mp);
	final_max_mp = ComputeCharacterFinalMaxMp(lIndex);
	mp = GetCharacterMp(lIndex);
	mp = CLAMP(mp, 0, final_max_mp);
	SetCharacterMp(lIndex, mp);
}


//
//�\��: �ݩ��I -> �O�q ���p��.
//
SLONG	ComputeCharacterPropertyPointToPointStr(SLONG lIndex, SLONG lData, POINTSTR_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, point_str, levelup_str;
	UHINT	convert_data;
	SLONG	result;
	UHINT	final_str;

	result = FALSE;
	property_point = GetCharacterPropertyPoint(lIndex);
	convert_data = (UHINT)( MIN(lData, property_point) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point -= convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_str, final_str, levelup_str. 
		//
		point_str = GetCharacterPointStr(lIndex);
		point_str += convert_data;
		SetCharacterPointStr(lIndex, point_str);
		levelup_str = GetCharacterLevelUpStr(lIndex);
		levelup_str += convert_data;
		SetCharacterLevelUpStr(lIndex, levelup_str);
		final_str = ComputeCharacterFinalStr(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->str = final_str;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: �O�q�I -> �ݩ��I ���p��
//
SLONG	ComputeCharacterPointStrToPropertyPoint(SLONG lIndex, SLONG lData, POINTSTR_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, point_str, levelup_str;
	UHINT	convert_data;
	SLONG	result;
	UHINT	final_str;

	result = FALSE;
	point_str = GetCharacterPointStr(lIndex);
	convert_data = (UHINT)( MIN(lData, point_str) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point = GetCharacterPropertyPoint(lIndex);
		property_point += convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_str & final_str. 
		//
		point_str = GetCharacterPointStr(lIndex);
		point_str -= convert_data;
		SetCharacterPointStr(lIndex, point_str);
		levelup_str = GetCharacterLevelUpStr(lIndex);
		levelup_str -= convert_data;
		SetCharacterLevelUpStr(lIndex, levelup_str);
		final_str = ComputeCharacterFinalStr(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->str = final_str;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: �ݩ��I -> ��ı ���p��
//
SLONG	ComputeCharacterPropertyPointToPointIns(SLONG lIndex, SLONG lData, POINTINS_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, convert_data;
	UHINT	point_ins, final_ins, levelup_ins;
	SLONG	result;

	result = FALSE;
	property_point = GetCharacterPropertyPoint(lIndex);
	convert_data = (UHINT)( MIN(lData, property_point) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point -= convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_ins & final_ins. 
		//
		point_ins = GetCharacterPointIns(lIndex);
		point_ins += convert_data;
		SetCharacterPointIns(lIndex, point_ins);
		levelup_ins = GetCharacterLevelUpIns(lIndex);
		levelup_ins += convert_data;
		SetCharacterLevelUpIns(lIndex, levelup_ins);
		final_ins = ComputeCharacterFinalIns(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->ins = final_ins;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: ��ı�I -> �ݩ��I ���p��
//
SLONG	ComputeCharacterPointInsToPropertyPoint(SLONG lIndex, SLONG lData, POINTINS_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, convert_data;
	UHINT	point_ins, final_ins, levelup_ins;
	SLONG	result;

	result = FALSE;
	point_ins = GetCharacterPointIns(lIndex);
	convert_data = (UHINT)( MIN(lData, point_ins) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point = GetCharacterPropertyPoint(lIndex);
		property_point += convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_ins & final_ins. 
		//
		point_ins -= convert_data;
		SetCharacterPointIns(lIndex, point_ins);
		levelup_ins = GetCharacterLevelUpIns(lIndex);
		levelup_ins -= convert_data;
		SetCharacterLevelUpIns(lIndex, levelup_ins);
		final_ins = ComputeCharacterFinalIns(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->ins = final_ins;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: �ݩ��I -> ���O ���p��
//
SLONG	ComputeCharacterPropertyPointToPointWit(SLONG lIndex, SLONG lData, POINTWIT_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, convert_data;
	UHINT	point_wit, final_wit, levelup_wit;
	SLONG	result;

	result = FALSE;
	property_point = GetCharacterPropertyPoint(lIndex);
	convert_data = (UHINT)( MIN(lData, property_point) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point -= convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_wit & final_wit. 
		//
		point_wit = GetCharacterPointWit(lIndex);
		point_wit += convert_data;
		SetCharacterPointWit(lIndex, point_wit);
		levelup_wit = GetCharacterLevelUpWit(lIndex);
		levelup_wit += convert_data;
		SetCharacterLevelUpWit(lIndex, levelup_wit);
		final_wit = ComputeCharacterFinalWit(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->wit = final_wit;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: ���O�I -> �ݩ��I ���p��
//
SLONG	ComputeCharacterPointWitToPropertyPoint(SLONG lIndex, SLONG lData, POINTWIT_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, convert_data;
	UHINT	point_wit, final_wit, levelup_wit;
	SLONG	result;

	result = FALSE;
	point_wit = GetCharacterPointWit(lIndex);
	convert_data = (UHINT)( MIN(lData, point_wit) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point = GetCharacterPropertyPoint(lIndex);
		property_point += convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_wit & final_wit. 
		//
		point_wit -= convert_data;
		SetCharacterPointWit(lIndex, point_wit);
		levelup_wit = GetCharacterLevelUpWit(lIndex);
		levelup_wit -= convert_data;
		SetCharacterLevelUpWit(lIndex, levelup_wit);
		final_wit = ComputeCharacterFinalWit(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->wit = final_wit;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: �ݩ��I -> �B���I ���p��
//
SLONG	ComputeCharacterPropertyPointToPointLucky(SLONG lIndex, SLONG lData, POINTLUCKY_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, convert_data;
	UHINT	point_lucky, final_lucky, levelup_lucky;
	SLONG	result;

	result = FALSE;
	property_point = GetCharacterPropertyPoint(lIndex);
	convert_data = (UHINT)( MIN(lData, property_point) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point -= convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_lucky & final_lucky. 
		//
		point_lucky = GetCharacterPointLucky(lIndex);
		point_lucky += convert_data;
		SetCharacterPointLucky(lIndex, point_lucky);
		levelup_lucky = GetCharacterLevelUpLucky(lIndex);
		levelup_lucky += convert_data;
		SetCharacterLevelUpLucky(lIndex, levelup_lucky);
		final_lucky = ComputeCharacterFinalLucky(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->lucky = final_lucky;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: �B���I -> �ݩ��I ���p��
//
SLONG	ComputeCharacterPointLuckyToPropertyPoint(SLONG lIndex, SLONG lData, POINTLUCKY_UPDATE_RESULT *lpResult)
{
	UHINT	property_point, convert_data;
	UHINT	point_lucky, final_lucky, levelup_lucky;
	SLONG	result;

	result = FALSE;
	point_lucky = GetCharacterPointLucky(lIndex);
	convert_data = (UHINT)( MIN(lData, point_lucky) );
	if(convert_data > 0)
	{
		//
		// Step 1: Update character's property point.
		//
		property_point = GetCharacterPropertyPoint(lIndex);
		property_point += convert_data;
		SetCharacterPropertyPoint(lIndex, property_point);

		//
		// Step 2: Compute character's point_lucky & final_lucky. 
		//
		point_lucky -= convert_data;
		SetCharacterPointLucky(lIndex, point_lucky);
		levelup_lucky = GetCharacterLevelUpLucky(lIndex);
		levelup_lucky -= convert_data;
		SetCharacterLevelUpLucky(lIndex, levelup_lucky);
		final_lucky = ComputeCharacterFinalLucky(lIndex);

		//
		// Step 3: Compute character's base-attrib-associated data.
		//         Include: attack, defence, max_hp, max_mp, hp, mp.
		//
		UpdateCharacterDataWithBaseAttrib(lIndex);

		//
		// Step 4: Update data which will be notify to client.
		//
		lpResult->property_point = property_point;
		lpResult->lucky = final_lucky;
		lpResult->att = GetCharacterFinalAtt(lIndex);
		lpResult->defence = GetCharacterFinalDefence(lIndex);
		lpResult->max_hp = GetCharacterMaxHp(lIndex);
		lpResult->max_mp = GetCharacterMaxMp(lIndex);
		lpResult->hp = GetCharacterHp(lIndex);
		lpResult->mp = GetCharacterMp(lIndex);

		result = TRUE;
	}
	return	result;
}


//
//�\��: ���a�վ��ݩ��I����
//
void	EndAdjustCharacterPropertyPoint(SLONG lIndex)
{
	SetCharacterPointStr(lIndex, 0);
	SetCharacterPointIns(lIndex, 0);
	SetCharacterPointWit(lIndex, 0);
	SetCharacterPointLucky(lIndex, 0);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ܪ��a���Z���˳�
//
// ���v�T���ƭ�:
//	(1) �����O
//			EquipBaseAtt, EquipAddedMagicAtt, EquipAddedSpecAtt
//			FinalAtt
//	(2) ���z�v
//			EquipExplodeRate 
//			FinalExplodeRate
//	(3) ���m�O
//			EquipDefence
//			FinalDefence
//	(4) �˳Ʃ�ܦʤ���
//			EquipResistRatio
//			FinalResist
//	(5) �ͩR�O�W��/�ͩR�O
//			EquipHp
//			MaxHp/Hp
//	(6) ���O�W��/���O
//			EquipMp
//			MaxMp/Mp
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG	UpdateCharacterDataWithChangeEquip(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	ULONG	equip_base_att, equip_added_magic_att, equip_added_spec_att, final_att;
	ULONG	equip_explode_rate, final_explode_rate;
	ULONG	equip_defence, final_defence;
	ULONG	equip_resist_ratio, final_resist;
	ULONG	equip_hp, max_hp, hp;
	ULONG	equip_mp, max_mp, mp;
	TPOS_ITEM	item;

	//
	// Compute equip affected data.
	//
	equip_base_att = equip_added_magic_att = equip_added_spec_att = final_att = 0;
	equip_explode_rate = final_explode_rate = 0;
	equip_defence = final_defence = 0;
	equip_resist_ratio = final_resist = 0;
	equip_hp = max_hp = hp = 0;
	equip_mp = max_mp = mp = 0;

	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);

		// Only weapon item has base_att attribute.
		equip_base_att += GetItemAttackData(&item);
	}

	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_added_magic_att += GetItemAddedMagicAttack(&item);
		equip_added_spec_att += GetItemAddedSpecialAttack(&item);
		equip_explode_rate += GetItemExplodeRate(&item);
		equip_defence += GetItemDefenceData(&item);
		equip_resist_ratio += GetItemResistRatio(&item);
		equip_hp += GetItemAddedMaxHp(&item);
		equip_mp += GetItemAddedMaxMp(&item);
	}

	//
	// Limited equip affected data.
	//
	equip_base_att = CLAMP(equip_base_att, 0, MAX_CAREER_ATTACK);
	equip_added_magic_att = CLAMP(equip_added_magic_att, 0, MAX_CAREER_ATTACK);
	equip_added_spec_att = CLAMP(equip_added_spec_att, 0, MAX_CAREER_ATTACK);
	equip_explode_rate = CLAMP(equip_explode_rate, 0, MAX_CAREER_EXPLODE_RATE);
	equip_defence = CLAMP(equip_defence, 0, MAX_CAREER_DEFENCE);
	equip_resist_ratio = CLAMP(equip_resist_ratio, 0, MAX_CAREER_RESIST);
	equip_hp = CLAMP(equip_hp, 0, MAX_CAREER_HP);
	equip_mp = CLAMP(equip_mp, 0, MAX_CAREER_MP);

	//
	// Compute character final data.
	//
	SetCharacterEquipBaseAtt(lIndex, (UHINT)equip_base_att);
	SetCharacterEquipAddedMagicAtt(lIndex, (UHINT)equip_added_magic_att);
	SetCharacterEquipAddedSpecAtt(lIndex, (UHINT)equip_added_spec_att);
	final_att = ComputeCharacterFinalAttack(lIndex);

	SetCharacterEquipExplodeRate(lIndex, (UHINT)equip_explode_rate);
	final_explode_rate = ComputeCharacterFinalExplodeRate(lIndex);

	SetCharacterEquipDefence(lIndex, (UHINT)equip_defence);
	final_defence = ComputeCharacterFinalDefence(lIndex);

	SetCharacterEquipResistRatio(lIndex, (UHINT)equip_resist_ratio);
	final_resist = ComputeCharacterFinalResist(lIndex);

	SetCharacterEquipHp(lIndex, (UHINT)equip_hp);
	max_hp = ComputeCharacterFinalMaxHp(lIndex);
	hp = GetCharacterHp(lIndex);
	hp = CLAMP(hp, 0, max_hp);
	SetCharacterHp(lIndex, (UHINT)hp);

	SetCharacterEquipMp(lIndex, (UHINT)equip_mp);
	max_mp = ComputeCharacterFinalMaxMp(lIndex);
	mp = GetCharacterMp(lIndex);
	mp = CLAMP(mp, 0, max_mp);
	SetCharacterMp(lIndex, (UHINT)mp);


	//
	// Update result data.
	//
	if(lpResult)
	{
		lpResult->att = (UHINT)final_att;
		lpResult->defence = (UHINT)final_defence;
		lpResult->hp = (UHINT)hp;
		lpResult->max_hp = (UHINT)max_hp;
		lpResult->max_mp = (UHINT)max_mp;
		lpResult->mp = (UHINT)mp;
		lpResult->resist = (UHINT)final_resist;
	}

	//
	// Always return true when we change character's equip(any).
	//
	return	TRUE;
}


SLONG	ComputeCharacterDataAfterChangeEquipHead(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}

SLONG	ComputeCharacterDataAfterChangeEquipNeck(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}

SLONG	ComputeCharacterDataAfterChangeEquipBody(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipWaist(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipGlove(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipWeapon(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipWrist(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipFeet(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipOtherA(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipOtherB(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


SLONG	ComputeCharacterDataAfterChangeEquipOtherC(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult)
{
	return	UpdateCharacterDataWithChangeEquip(lIndex, lpResult);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�\��: ��l�ƫ�p�⪱�a�������
//����: �I�s�e�ݭn�]�m�n�����a��ƥ]�t
//	(1) InitStr, LevelUpStr
//	(2) InitIns, LevelUpIns
//	(3) InitWit, LevelUpWit
//	(4) InitLucky, LevelUpLucky
//	(5) All equip items.
//	(6) All skills.
//
//�����B��B�J:
//	(1) Base attributes:
//		InitStr, LevelUpStr => FinalStr
//		InitIns, LevelUpIns => FinalIns
//		InitWit, LevelUpWit => FinalWit
//		InitLucky, LevelUpLucky => FinalLucky
//
//	(2) Base attributes associated data:
//		Attrib AttribFinalStr, FinalIns, FinalWit, FinalLucky
//		 => AttribAttack, AttribDefence, AttribMaxHp, AttribMaxMp.
//
//	(3) Skills associated data:
//		Skills => SkillAddedAttack, SkillAddedDefence, SkillAdded...
//
//	(4) Items associated data:
//		Items => ItemAddedAttack, ItemAddedDefence, ItemAddedMaxHp, ItemAddedMaxMp(,SightRange....)
//
//	(5) Final data:
//		(2.3.4) => FinalAttack, FinalDefence, MaxHp, MaxMp.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	ComputeCharacterDataAfterInit(SLONG lIndex)
{
	SLONG	career;
	UHINT	final_str, final_ins, final_wit, final_lucky;
	UHINT	attack_ratio, base_defence, base_max_hp, base_max_mp;

	career = GetCharacterCareer(lIndex);
	career = CharCareer2IntCareer(career);

	//
	// Base attributes:
	//
	final_str = ComputeCharacterFinalStr(lIndex);
	final_ins = ComputeCharacterFinalIns(lIndex);
	final_wit = ComputeCharacterFinalWit(lIndex);
	final_lucky = ComputeCharacterFinalLucky(lIndex);

	//
	// Base attributes associated data:
	//
	attack_ratio = ComputeCareerBaseAttackRatio(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterAttribAttRatio(lIndex, attack_ratio);
	base_defence = ComputeCareerBaseDefence(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterBaseDefence(lIndex, base_defence);
	base_max_hp = ComputeCareerBaseMaxHp(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterAttribHp(lIndex, base_max_hp);
	base_max_mp = ComputeCareerBaseMaxMp(career, final_str, final_ins, final_wit, final_lucky);
	SetCharacterAttribMp(lIndex, base_max_mp);

	//
	// Skill associated data:
	//
	ComputeCharacterSkillAttackRatio(lIndex);
	ComputeCharacterSkillExplodeRate(lIndex);
	ComputeCharacterSkillDefence(lIndex);
	ComputeCharacterSkillMaxHp(lIndex);
	ComputeCharacterSkillMaxMp(lIndex);

	//
	// Item associated data & final data
	//
	UpdateCharacterDataWithChangeEquip(lIndex, NULL);
    //
    //
	return;
}
//----
//  �@�Ǩϥξ԰��ޯ઺�ǳƨ��
//----
void    FightPrepareSpower(SLONG lIndex, SLONG Skill, SLONG lLevel)
{
    SLONG   total_tick;
    //�ϱonpc�k��ޯબ�A..���b�W�O��
    SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_SPOWER);
    //�M��npc�k��ޯ�p�Ƭ�0
    SetCharacterRightHandMagicCurrentTicks(lIndex, 0);
    //�]�m.npc�k��ޯ�p��..���̤j��
    total_tick = GetSkillSpowerTick(Skill, lLevel);    
    SetCharacterRightHandMagicTotalTicks(lIndex, (SHINT)total_tick);
    //
}
//----
//  
//----
void    FightAbortSpower(SLONG lIndex,SLONG Skill,SLONG lLevel)
{
    SLONG   skill_no, skill_level;
    //�ϱonpc�k�䪺���A..���`���A
    //�P�_�ӧޯ�O�_�ݭn�W�O�q
    skill_no = GetCharacterLandRightSkill(lIndex);    
    skill_level = GetCharacterSpecialSkillLevel(lIndex, skill_no);
    if (IsSkillNeedSpower(skill_no, skill_level))
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_WAIT_SPOWER);    
    else    
        SetCharacterRightHandMagicState(lIndex, MAGIC_STATE_OK);
    //�M��npc�k��ޯ�p�Ƭ�0
    SetCharacterRightHandMagicCurrentTicks(lIndex, 0);    
    //�]�m.npc�k��ޯ�p��..1
    SetCharacterRightHandMagicTotalTicks(lIndex, 1);    
}
//----
//  
//----
SLONG   search_near_target_npc(SLONG npc_no)
{
    SLONG   center_x, center_y, center_z, view;
    SLONG   find_npc;

    LOCK_CHARACTER(npc_no);    
    GetCharacterPosition(npc_no, &center_x, &center_y, &center_z);    
	view = GetCharacterSightRange(npc_no);
    UNLOCK_CHARACTER(npc_no);

	find_npc = find_near_target_npc(npc_no, center_x, center_y, view, 0);

    return  find_npc;
}
//----
//  
//----
SLONG   find_near_target_npc(SLONG src_npc, SLONG center_x, SLONG center_y, SLONG radius, SLONG find_flags)
{
    SLONG   find_npc, doing_kind;
    SLONG   npc_no, npc_x, npc_y, npc_z, npc_hp;
    double	dist, min_dist;
    
    find_npc = -1;
    min_dist = radius * radius;
    //If src_npc is a player npc -------------------------------    
	LOCK_CHARACTER(0);
    for(npc_no=0; npc_no<500; npc_no++)
    {
        //
		if(npc_no == src_npc)
			continue;

		if(!IsCharacterAvailable(npc_no))
			continue;

		doing_kind = GetCharacterDoingKind(npc_no);
		if(doing_kind == DOING_KIND_CHANGEMAP)
			continue;

		npc_hp = GetCharacterHp(npc_no);
		if(npc_hp <= 0)
			continue;

		GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
        //		
        dist = (npc_x - center_x) * (npc_x - center_x) + (npc_y - center_y) * (npc_y - center_y);
        if(dist < min_dist)
        {
            min_dist = dist;
            find_npc = npc_no;
        }
    } 
	UNLOCK_CHARACTER(0);
    //
    return  find_npc;
}
//---
//  �ھ�npc�{�����ޯ�..���@�ӥX��
//      npc_no      �ݭn�ϥΧޯ઺NPC
//      dest_no     �ݭn�������ؼ�NPC
//---
SLONG   get_can_use_skill_to_attack(SLONG npc_no, SLONG dest_no)
{
    SLONG   i;
    SLONG   skill_no, skill_level;
    //
    for (i=0; i<MAX_CHARACTER_SKILLS; i++)
    {
        //
        skill_no = ZoneCharacter[npc_no].SkillExp.Skill[i];
        skill_level = ZoneCharacter[npc_no].SkillExp.Level[i];
        if (skill_no>=0 && skill_no<=MAX_GAME_SKILL_BASES)
        {
            //�ݭn�O�԰��ޯ�
            if (IsFightSkill(skill_no, skill_level))
            {
                //
                return skill_no;
            }
        }
    }    
    return 0;
}
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------


