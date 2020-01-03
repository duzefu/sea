#if	0
//--------------------------------------------------------------------------------------------------------
/*
#define	ITEM_TYPE_UNKNOWN					0	//�������~���O(����)
#define ITEM_TYPE_CAP						1   //�U�l(���a���Y��)
#define ITEM_TYPE_HELM						2   //�Y��(���a���Y��)
#define ITEM_TYPE_VEIL						3   //����(���a���Y��)
#define ITEM_TYPE_HAT						4   //§�U(���a���Y��)
#define ITEM_TYPE_MASK						5   //����(���a���Y��)
#define ITEM_TYPE_STRAW						6   //��U(���a���Y��)
#define ITEM_TYPE_SHAKO						7   //�x�U(���a���Y��)
#define ITEM_TYPE_CLOTH						8   //��A(���a���Z��)
#define ITEM_TYPE_CANONICALS				9   //���v�A(���a���Z��)
#define ITEM_TYPE_REGIMENTAL				10  //�x�A(���a���Z��)
#define ITEM_TYPE_NIGHTCLOTH				11  //�]��A(���a���Z��)
#define ITEM_TYPE_MAGECLOTH					12  //�k�v�T(���a���Z��)
#define ITEM_TYPE_BIZCLOTH					13  //�Ӹ뤧�A(���a���Z��)
#define ITEM_TYPE_ROBE						14  //§�A(���a���Z��)
#define ITEM_TYPE_HEAVYPLATE				15  //���Z(���a���Z��)
#define ITEM_TYPE_CHAINARMOR				16  //��l��(���a���Z��)
#define ITEM_TYPE_LIGHTPLATE				17  //����(���a���Z��)
#define ITEM_TYPE_WEDDING					18  //�B��(���a���Z��)
#define ITEM_TYPE_SHOES						19  //�c��(���a���c��)
#define ITEM_TYPE_BOOT						20  //�u��(���a���c��)
#define ITEM_TYPE_BELT						21  //�y�a(���a���y�a)
#define	ITEM_TYPE_GLOVE						22	//��M(���a)
#define ITEM_TYPE_SWORD						23  //�C(���a�Z��)
#define ITEM_TYPE_CLERIC					24  //�ǱФh�M�ΪZ��(���a�Z��)
#define ITEM_TYPE_GUN						25  //��j(���a�Z��)
#define ITEM_TYPE_DAGGER					26  //�P��(���a�Z��)
#define ITEM_TYPE_THONG						27  //���@(���a�Z��)
#define ITEM_TYPE_CRYSTAL					28  //�����y(���a�Z��)
#define ITEM_TYPE_COIN						29  //����(���a�Z��)
#define ITEM_TYPE_RING						30  //�٫�(���a�˹�)
#define ITEM_TYPE_AMULET					31  //�@����(���a�˹�)
#define ITEM_TYPE_JEWEL						32  //�]�_(���a�˹�)
#define ITEM_TYPE_CLASSIC					33  //����M��(���a)
#define ITEM_TYPE_DRUG						34  //�ī~(�ī~)
#define	ITEM_TYPE_TREASURE					35	//���_��(�H��)(���a, ���v)
#define	ITEM_TYPE_STATUE					36	//���(���v)
#define	ITEM_TYPE_SAIL						37	//��|(���v)
#define	ITEM_TYPE_EMBOLON					38	//���(���v)
#define	ITEM_TYPE_CANNON					39	//��(���v)
#define	ITEM_TYPE_ARMOR						40	//��˥�(���v)
#define	ITEM_TYPE_SEAEXPENDABLE				41	//���v���ӫ~(���v)
#define	ITEM_TYPE_SAILOR					42	//���v����(���v)
#define	ITEM_TYPE_GOODS						43	//�ӫ~(���a, ���v)
*/
//����ʧ@����
typedef	struct POS_CHARACTER_ACTION 
{
	SLONG	DoingKind;			//�ư�����
	SLONG	DoingStep;			//�ưȶi��{��
	SHINT	DoingMagic;			//��e�ϥΪ��k�N�ޯ�s��
	UCHAR	ImageAction;		//���ɰʧ@����
	ULONG	ImageID;			//���ɤ��Х�
	//Jack, [1/12/2003]
	//remark for have move these data as union to position 
	//	SLONG	IdleTicks;			//�ݾ�: �ݾ����ɶ�
	//	SLONG	SequentialStep;		//�s��: �O�_�i��U�@�ӳs�򪺰ʧ@
	//	SLONG	BeatedBy;			//�Q��: �֧����� ?
	//	SLONG	BeatedWith;			//�Q��: �Q�ƻ�ޯ���� ?
	//	SLONG	PantTicks;			//�Q����: ���˦b�a�W�P���_�Ӥ������ݮ��ɶ�
	//	SLONG	BeatedX;			//�Q��,���`,�Q����: ������ x�y��
	//	SLONG	BeatedY;			//�Q��,���`,�Q����: ������ y�y��
	//	SLONG	MuseTicks;			//�߷Q: �C�j�h���ɶ��i��@���ƭȭp��
	//	SLONG	ClashSteps;			//�ļ�: �ļ����B��
	//	SLONG	PatrolTicks;		//����: ����IDLE����e�ɶ�
	//	SLONG	PatrolTotalTicks;	//����: ����IDLE���`�ɶ�
	//	SLONG	GadTicks;			//�H������: IDLE����e�ɶ�
	//	SLONG	GadTotalTicks;		//�H������: IDLE���`�ɶ�
} TPOS_CHARACTER_ACTION, *LPTPOS_CHARACTER_ACTION;

//���⪬�A
typedef	struct POS_CHARACTER_STATE 
{
	ULONG	BitState;				//1/0���A(�O�_�b�԰����A, �]�]�O�_���}, �b���W�γ��a, �O�_���`...)

	SHINT	ReliveTicks;			//�A�ͪ��ɶ�
	//Jack, [1/12/2003]
	//remark for have move these data as union to position 
	//	SHINT	DeadTicks;				//���`�F�h���ɶ�
	SHINT	DeadState;				//���`�����A

	SHINT	RMagicState;			//�k��ޯબ�A
	SHINT	RMagicTotalTicks;		//�k��ޯ��`�ɶ�
	SHINT	RMagicCurrentTicks;		//�k��ޯ��e�ɶ�

	SHINT	HeadSleepState;			//�Y�w, �ίv(�Q��)
	SHINT	HeadSleepTicks;			//�Y�w, �ίv �ɶ�
	SHINT	HeadSleepLevel;			//�Y�w, �ίv ����

	SHINT	HeadPredictState;		//�w��:������, �ϰ���, �ϳ���(�D�ʥ�����)
	SHINT	HeadPredictLevel;		//�w��:������, �ϰ���, �ϳ��� ����

	SHINT	HeadDefenceState;		//���m�[�j(�Q�ʩΥD��)
	SHINT	HeadDefenceTicks;		//���m�[�j �ɶ�
	SHINT	HeadDefenceLevel;		//���m�[�j ����

	SHINT	HeadMagicState;			//�]�k�ϼu
	SHINT	HeadMagicTimes;			//�]�k�ϼu����	
	SHINT	HeadMagicLevel;			//�]�k�ϼu����

	SHINT	HeadBlindState;			//����(�Q��)	
	SHINT	HeadBlindTicks;			//���� �ɶ�	
	SHINT	HeadBlindLevel;			//���� ����	

	SHINT	BodyDodgeState;			//���{(�D�ʥ�����)

	SHINT	BodyVirusState;			//���r(�Q��)	
	SHINT	BodyVirusTicks;			//���r �ɶ�	
	SHINT	BodyVirusLevel;			//���r ����	

	SHINT	BodyHideState;			//�Q�l��(�Q��), ����1, ����2(�D��)	
	SHINT	BodyHideTicks;			//�Q�l��(�Q��), ����1, ����2 �ɶ�	
	SHINT	BodyHideLevel;			//�Q�l��(�Q��), ����1, ����2 ����

	SHINT	FootSpeedState;			//��w1, ��w2(�Q�ʩΪ̦b�d��)	
	SHINT	FootSpeedTicks;			//��w1, ��w2 �ɶ�	
	SHINT	FootSpeedLevel;			//��w1, ��w2 ����	

	SHINT	RotateState;			//����(�Q��)�
	SHINT	RotateTicks;			//���� �ɶ�	�
	SHINT	RotateLevel;			//���� ����	�

	SHINT	FireState;				//�ۤ�(�Q��)�
	SHINT	FireTicks;				//�ۤ� �ɶ�	�
	SHINT	FireLevel;				//�ۤ� ����	�

	SHINT	ExplodeState;			//�z��(�Q��)�
	SHINT	ExplodeTicks;			//�z�� �ɶ�	�
	SHINT	ExplodeLevel;			//�z�� ����	�

	SHINT	SailHurtState;			//�|�l�` (�Q��)	�
	SHINT	RudderHurtState;		//��l�` (�Q��)	�

	SHINT	PretendState;			//���� (�D��)	�
	SHINT	PretendOldFileIndex;	//���˫e���Ϲ�	�
	SHINT	PretendToFileIndex;		//���˫᪺�Ϲ�	�

	SHINT	HalfDownState;			//�b�I	�

	SHINT	OctopusState;			//���� (�Q��)	�
	SHINT	OctopusTicks;			//���� �ɶ�	�
	SHINT	OctopusLevel;			//���� ����	�

	ULONG	AI;						//�H���԰�AI

} TPOS_CHARACTER_STATE, *LPTPOS_CHARACTER_STATE;

//���P¾�~�H�������O���H��4�ذ򥻭Ȫ��v�T
typedef struct tagCAREER_AFFECT_ATTACK
{
    SLONG   by_strength;    //���O�q�v�T
    SLONG   by_instinct;    //����ı�v�T
    SLONG   by_wit;         //�����O�v�T
    SLONG   by_luck;        //���B��v�T
} CAREER_AFFECT_ATTACK, *LPCAREER_AFFECT_ATTACK;


//���P¾�~���m�O���O�q,��ı,���O,�B��v�T
typedef struct tagCAREER_AFFECT_DEFENCE
{
    SLONG   by_strength;    //���O�q�v�T
    SLONG   by_instinct;    //����ı�v�T
    SLONG   by_wit;         //�����O�v�T
    SLONG   by_luck;        //���B��v�T
} CAREER_AFFECT_DEFENCE, *LPCAREER_AFFECT_DEFENCE;


//���P¾�~MAX_HP���O�q,��ı,���O,�B��v�T
typedef struct tagCAREER_AFFECT_MAX_HP
{
    SLONG   by_strength;    //���O�q�v�T
    SLONG   by_instinct;    //����ı�v�T
    SLONG   by_wit;         //�����O�v�T
    SLONG   by_luck;        //���B��v�T
} CAREER_AFFECT_MAX_HP, *LPCAREER_AFFECT_MAX_HP;


//���P¾�~MAX_MP���O�q,��ı,���O,�B��v�T
typedef struct tagCAREER_AFFECT_MAX_MP
{
    SLONG   by_strength;    //���O�q�v�T
    SLONG   by_instinct;    //����ı�v�T
    SLONG   by_wit;         //�����O�v�T
    SLONG   by_luck;        //���B��v�T
} CAREER_AFFECT_MAX_MP, *LPCAREER_AFFECT_MAX_MP;


//���⪺�����O, ���m�O, �ͩR�O�W��, ���O�W�����򥻭ȼv�T
typedef	struct	tagCAREER_ATTRIB_AFFECT
{
	SLONG	att;
	SLONG	dp;
	SLONG	max_hp;
	SLONG	max_mp;
} CAREER_ATTRIB_AFFECT, *LPCAREER_ATTRIB_AFFECT;


extern  void    InitCareerAffectAttack(void);
extern  SLONG   LoadCareerAffectAttack(void);
extern  void    FreeCareerAffectAttack(void);
extern  void    InitCareerAffectDefence(void);
extern  SLONG   LoadCareerAffectDefence(void);
extern  void    FreeCareerAffectDefence(void);
extern  void    InitCareerAffectMaxHp(void);
extern  SLONG   LoadCareerAffectMaxHp(void);
extern  void    FreeCareerAffectMaxHp(void);
extern  void    InitCareerAffectMaxMp(void);
extern  SLONG   LoadCareerAffectMaxMp(void);
extern  void    FreeCareerAffectMaxMp(void);
//
extern	void	InitCareerAttribAffect(void);
extern	SLONG	GetCareerAttribAffectAttack(void);
extern	SLONG	GetCareerAttribAffectDefence(void);
extern	SLONG	GetCareerAttribAffectMaxHp(void);
extern	SLONG	GetCareerAttribAffectMaxMp(void);
//
extern	SLONG	ComputeCareerAttribAffectByStr(SLONG char_index, SLONG strength);
extern	SLONG	ComputeCareerAttribAffectByIns(SLONG char_index, SLONG instinct);
extern	SLONG	ComputeCareerAttribAffectByWit(SLONG char_index, SLONG wit);
extern	SLONG	ComputeCareerAttribAffectByLucky(SLONG char_index, SLONG lucky);
//�\��: ��o�򥻭ȼv�T�������O
SLONG	GetCareerAttribAffectAttack(void)
{
	return	l_career_attrib_affect.att;
}


//�\��: ��o�򥻭ȼv�T�����m�O
SLONG	GetCareerAttribAffectDefence(void)
{
	return	l_career_attrib_affect.dp;
}


//�\��: ��o�򥻭ȼv�T���ͩR�O�W��
SLONG	GetCareerAffectMaxHp(void)
{
	return	l_career_attrib_affect.max_hp;
}


//�\��: ��o�򥻭ȼv�T�����O�W��
SLONG	GetCareerAffectMaxMp(void)
{
	return	l_career_attrib_affect.max_mp;
}


//�\��: �p��O�q�����ܹ﨤���ݩʪ��v�T
SLONG	ComputeCareerAttribAffectByStr(SLONG char_index, SLONG strength)
{
	if(char_index < 0 || char_index >= MAX_GAME_CAREERS)
		return	TTN_NOT_OK;

	memset(&l_career_attrib_affect, 0, sizeof(l_career_attrib_affect));
	l_career_attrib_affect.att = l_career_affect_attack[char_index].by_strength * strength;
	l_career_attrib_affect.dp = l_career_affect_defence[char_index].by_strength * strength;
	l_career_attrib_affect.max_hp = l_career_affect_hp[char_index].by_strength * strength;
	l_career_attrib_affect.max_mp = l_career_affect_mp[char_index].by_strength * strength;

	return	TTN_OK;
}


//�\��: �p�⪽ı�����ܹ﨤���ݩʪ��v�T
SLONG	ComputeCareerAttribAffectByIns(SLONG char_index, SLONG instinct)
{
	if(char_index < 0 || char_index >= MAX_GAME_CAREERS)
		return	TTN_NOT_OK;

	memset(&l_career_attrib_affect, 0, sizeof(l_career_attrib_affect));
	l_career_attrib_affect.att = l_career_affect_attack[char_index].by_instinct * instinct;
	l_career_attrib_affect.dp = l_career_affect_defence[char_index].by_instinct * instinct;
	l_career_attrib_affect.max_hp = l_career_affect_hp[char_index].by_instinct * instinct;
	l_career_attrib_affect.max_mp = l_career_affect_mp[char_index].by_instinct * instinct;

	return	TTN_OK;
}


//�\��: �p�ⴼ�O�����ܹ﨤���ݩʪ��v�T
SLONG	ComputeCareerAttribAffectByWit(SLONG char_index, SLONG wit)
{
	if(char_index < 0 || char_index >= MAX_GAME_CAREERS)
		return	TTN_NOT_OK;

	memset(&l_career_attrib_affect, 0, sizeof(l_career_attrib_affect));
	l_career_attrib_affect.att = l_career_affect_attack[char_index].by_wit * wit;
	l_career_attrib_affect.dp = l_career_affect_defence[char_index].by_wit * wit;
	l_career_attrib_affect.max_hp = l_career_affect_hp[char_index].by_wit * wit;
	l_career_attrib_affect.max_mp = l_career_affect_mp[char_index].by_wit * wit;

	return	TTN_OK;
}


//�\��: �p��B�𪺧��ܹ﨤���ݩʪ��v�T
SLONG	ComputeCareerAttribAffectByLucky(SLONG char_index, SLONG luck)
{
	if(char_index < 0 || char_index >= MAX_GAME_CAREERS)
		return	TTN_NOT_OK;

	memset(&l_career_attrib_affect, 0, sizeof(l_career_attrib_affect));
	l_career_attrib_affect.att = l_career_affect_attack[char_index].by_luck * luck;
	l_career_attrib_affect.dp = l_career_affect_defence[char_index].by_luck * luck;
	l_career_attrib_affect.max_hp = l_career_affect_hp[char_index].by_luck * luck;
	l_career_attrib_affect.max_mp = l_career_affect_mp[char_index].by_luck * luck;

	return	TTN_OK;
}




//�\��: ��l�ƨ���򥻭ȼv�T�����ƾ�
void    InitCareerAffectAttack(void)
{
    memset(l_career_affect_attack, 0, sizeof(CAREER_AFFECT_ATTACK) * MAX_GAME_CAREERS);
}


//�\��: ���J����򥻭ȼv�T�����ƾ�
SLONG   LoadCareerAffectAttack(void)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    filename[_MAX_FNAME];
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   data_index;
    CAREER_AFFECT_ATTACK  *data;

    sprintf((char *)filename, "data\\attack.ini");
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
                data = &l_career_affect_attack[data_index];

                data->by_strength = get_buffer_number(line, &index);
                data->by_instinct = get_buffer_number(line, &index);
                data->by_wit = get_buffer_number(line, &index);
                data->by_luck = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


//�\��: ���񨤦�򥻭ȼv�T�����ƾ�
void    FreeCareerAffectAttack(void)
{
    //nothing to do.
}


//�\��: ��l�ƨ���򥻭ȼv�T���m�O�ƾ�
void    InitCareerAffectDefence(void)
{
    memset(l_career_affect_defence, 0, sizeof(CAREER_AFFECT_DEFENCE) * MAX_GAME_CAREERS);
}


//�\��: ���J����򥻭ȼv�T���m�O�ƾ�
SLONG   LoadCareerAffectDefence(void)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    filename[_MAX_FNAME];
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   data_index;
    CAREER_AFFECT_DEFENCE  *data;

    sprintf((char *)filename, "data\\defence.ini");
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
                data = &l_career_affect_defence[data_index];

                data->by_strength = get_buffer_number(line, &index);
                data->by_instinct = get_buffer_number(line, &index);
                data->by_wit = get_buffer_number(line, &index);
                data->by_luck = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


//�\��: ���񨤦�򥻭ȼv�T���m�O�ƾ�
void    FreeCareerAffectDefence(void)
{
    //nothing to do.
}


//�\��: ��l�ƨ���򥻭ȼv�THP�ƾ�
void    InitCareerAffectMaxHp(void)
{
    memset(l_career_affect_hp, 0, sizeof(CAREER_AFFECT_MAX_HP) * MAX_GAME_CAREERS);
}


//�\��: ���J����򥻭ȼv�THP�ƾ�
SLONG   LoadCareerAffectMaxHp(void)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    filename[_MAX_FNAME];
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   data_index;
    CAREER_AFFECT_MAX_HP  *data;

    sprintf((char *)filename, "data\\hp.ini");
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
                data = &l_career_affect_hp[data_index];

                data->by_strength = get_buffer_number(line, &index);
                data->by_instinct = get_buffer_number(line, &index);
                data->by_wit = get_buffer_number(line, &index);
                data->by_luck = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


//�\��: ���񨤦�򥻭ȼv�THP�ƾ�
void    FreeCareerAffectMaxHp(void)
{
    //nothing to do.
}


//�\��: ��l�ƨ���򥻭ȼv�TMP�ƾ�
void    InitCareerAffectMaxMp(void)
{
    memset(l_career_affect_mp, 0, sizeof(CAREER_AFFECT_MAX_MP) * MAX_GAME_CAREERS);
}


//�\��: ���J����򥻭ȼv�TMP�ƾ�
SLONG   LoadCareerAffectMaxMp(void)
{
    enum {LINE_BUFFER_SIZE = 2048};
    USTR    filename[_MAX_FNAME];
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL;
    SLONG   file_size, buffer_index, len, pass, result;
    SLONG   index;
    SLONG   data_index;
    CAREER_AFFECT_MAX_MP  *data;

    sprintf((char *)filename, "data\\mp.ini");
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
                data = &l_career_affect_mp[data_index];

                data->by_strength = get_buffer_number(line, &index);
                data->by_instinct = get_buffer_number(line, &index);
                data->by_wit = get_buffer_number(line, &index);
                data->by_luck = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    
    return TTN_OK;
}


//�\��: ���񨤦�򥻭ȼv�TMP�ƾ�
void    FreeCareerAffectMaxMp(void)
{
    //nothing to do.
}

extern  CAREER_AFFECT_ATTACK      l_career_affect_attack[MAX_GAME_CAREERS];
extern  CAREER_AFFECT_DEFENCE     l_career_affect_defence[MAX_GAME_CAREERS];
extern  CAREER_AFFECT_MAX_HP      l_career_affect_hp[MAX_GAME_CAREERS];
extern  CAREER_AFFECT_MAX_MP      l_career_affect_mp[MAX_GAME_CAREERS];
extern	CAREER_ATTRIB_AFFECT	  l_career_attrib_affect;


//
//���a���~�S���ݩʩw�q(SPECIAL 3)
//
#define	LAND_ITEM_SPECIAL3_NONE							0	//�L�����ݩ�
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_STR				1	//�O�q + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_STR				2	//�O�q + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_STR				3	//�O�q + 5
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_INS				4	//��ı + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_INS				5	//��ı + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_INS				6	//��ı + 5
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_WIT				7	//���O + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_WIT				8	//���O + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_WIT				9	//���O + 5
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_LUCKY				10	//�B�� + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_LUCKY				11	//�B�� + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_LUCKY				12	//�B�� + 5

SLONG	GetItemAddedStr(TPOS_ITEM *IT)
{
	SLONG	added_str;
	SLONG	type;
	SLONG	hp;
	UHINT	special3;

	//
	// Only land equipment item has add str property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Added str is controled by special3 flags.
	//
	added_str = 0;
	special3 = GetLandItemSpecial3(IT);
	if(special3 & LAND_ITEM_SPECIAL3_ADD_SMALL_STR)
	{
		added_str += 1;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_MIDDLE_STR)
	{
		added_str += 3;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_LARGE_STR)
	{
		added_str += 5;
	}

	return	added_str;
}


SLONG	GetItemAddedIns(TPOS_ITEM *IT)
{
	SLONG	added_ins;
	SLONG	type;
	SLONG	hp;
	UHINT	special3;

	//
	// Only land equipment item has add str property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Added str is controled by special3 flags.
	//
	added_ins = 0;
	special3 = GetLandItemSpecial3(IT);
	if(special3 & LAND_ITEM_SPECIAL3_ADD_SMALL_INS)
	{
		added_ins += 1;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_MIDDLE_INS)
	{
		added_ins += 3;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_LARGE_INS)
	{
		added_ins += 5;
	}

	return	added_ins;
}


SLONG	GetItemAddedWit(TPOS_ITEM *IT)
{
	SLONG	added_wit;
	SLONG	type;
	SLONG	hp;
	UHINT	special3;

	//
	// Only land equipment item has add str property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Added str is controled by special3 flags.
	//
	added_wit = 0;
	special3 = GetLandItemSpecial3(IT);
	if(special3 & LAND_ITEM_SPECIAL3_ADD_SMALL_WIT)
	{
		added_wit += 1;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_MIDDLE_WIT)
	{
		added_wit += 3;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_LARGE_WIT)
	{
		added_wit += 5;
	}

	return	added_wit;
}


SLONG	GetItemAddedLucky(TPOS_ITEM *IT)
{
	SLONG	added_lucky;
	SLONG	type;
	SLONG	hp;
	UHINT	special3;

	//
	// Only land equipment item has add str property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Added str is controled by special3 flags.
	//
	added_lucky = 0;
	special3 = GetLandItemSpecial3(IT);
	if(special3 & LAND_ITEM_SPECIAL3_ADD_SMALL_LUCKY)
	{
		added_lucky += 1;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_MIDDLE_LUCKY)
	{
		added_lucky += 3;
	}
	if(special3 & LAND_ITEM_SPECIAL3_ADD_LARGE_LUCKY)
	{
		added_lucky += 5;
	}

	return	added_lucky;
}



//�\��: �p��H���˳ƪ��[���O�q
SLONG	ComputeCharacterEquipStr(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_str;

	equip_str = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_str += GetItemAddedStr(&item);
	}

	if(equip_str > MAX_CAREER_STR)
		equip_str = MAX_CAREER_STR;

	SetCharacterEquipStr(lIndex, (UHINT)equip_str);
	
	return	equip_str;
}

//�\��: �p��H���˳ƪ��[����ı
SLONG	ComputeCharacterEquipIns(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_ins;

	equip_ins = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_ins += GetItemAddedIns(&item);
	}

	if(equip_ins > MAX_CAREER_INS)
		equip_ins = MAX_CAREER_INS;

	SetCharacterEquipIns(lIndex, (UHINT)equip_ins);
	
	return	equip_ins;
}

//�\��: �p��H���˳ƪ��[�����O
SLONG	ComputeCharacterEquipWit(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_wit;

	equip_wit = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_wit += GetItemAddedWit(&item);
	}

	if(equip_wit > MAX_CAREER_WIT)
		equip_wit = MAX_CAREER_WIT;

	SetCharacterEquipWit(lIndex, (UHINT)equip_wit);
	
	return	equip_wit;
}

//�\��: �p��H���˳ƪ��[���B��
SLONG	ComputeCharacterEquipLucky(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_lucky;

	equip_lucky = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_lucky += GetItemAddedLucky(&item);
	}

	if(equip_lucky > MAX_CAREER_LUCKY)
		equip_lucky = MAX_CAREER_LUCKY;

	SetCharacterEquipLucky(lIndex, (UHINT)equip_lucky);
	
	return	equip_lucky;
}

extern	SLONG	ComputeCharacterEquipStr(SLONG lIndex);
extern	SLONG	ComputeCharacterEquipIns(SLONG lIndex);
extern	SLONG	ComputeCharacterEquipWit(SLONG lIndex);
extern	SLONG	ComputeCharacterEquipLucky(SLONG lIndex);
//
void	SetCharacterEquipStr(SLONG lIndex, UHINT uStr)
{
	ZoneCharacter[lIndex].Property.Str.EquipStr = uStr;
}

UHINT	GetCharacterEquipStr(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Str.EquipStr;
}

void	SetCharacterStatusStrRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Str.StatusStrRatio = uRatio;
}

UHINT	GetCharacterStatusStrRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Str.StatusStrRatio;
}

void	SetCharacterEquipIns(SLONG lIndex, UHINT uIns)
{
	ZoneCharacter[lIndex].Property.Ins.EquipIns = uIns;
}

UHINT	GetCharacterEquipIns(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Ins.EquipIns;
}

void	SetCharacterStatusInsRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Ins.StatusInsRatio = uRatio;
}

UHINT	GetCharacterStatusInsRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Ins.StatusInsRatio;
}

void	SetCharacterEquipWit(SLONG lIndex, UHINT uWit)
{
	ZoneCharacter[lIndex].Property.Wit.EquipWit = uWit;
}

UHINT	GetCharacterEquipWit(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Wit.EquipWit;
}

void	SetCharacterStatusWitRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Wit.StatusWitRatio = uRatio;
}

UHINT	GetCharacterStatusWitRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Wit.StatusWitRatio;
}

void	SetCharacterEquipLucky(SLONG lIndex, UHINT uLucky)
{
	ZoneCharacter[lIndex].Property.Lucky.EquipLucky = uLucky;
}

UHINT	GetCharacterEquipLucky(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Lucky.EquipLucky;
}

void	SetCharacterStatusLuckyRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Lucky.StatusLuckyRatio = uRatio;
}

UHINT	GetCharacterStatusLuckyRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Lucky.StatusLuckyRatio;
}

	UHINT	SkillPhyRatio;		//�Q�ʧޯ�磌�z�����O���v�T�ʤ���
	UHINT	SkillMagicRatio;	//�Q�ʧޯ��k�N�����O���v�T�ʤ���
	UHINT	SkillSpecRatio;		//�Q�ʧޯ��S������O���v�T�ʤ���
	//
void	SetCharacterSkillMagicRatio(SLONG lIndex, UHINT	uRatio)
{
	ZoneCharacter[lIndex].Property.Attack.SkillMagicRatio = uRatio;
}

UHINT	GetCharacterSkillMagicRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.SkillMagicRatio;
}

void	SetCharacterSkillSpecRatio(SLONG lIndex, UHINT uRatio)
{
	ZoneCharacter[lIndex].Property.Attack.SkillMagicRatio = uRatio;
}

UHINT	GetCharacterSkillSpecRatio(SLONG lIndex)
{
	return ZoneCharacter[lIndex].Property.Attack.SkillSpecRatio;
}

//�\��G�p��H���˳ƪ����m�O�ʤ���
SLONG	ComputeCharacterEquipDefenceRatio(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	equip_defence_ratio;

	equip_defence_ratio = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		equip_defence_ratio += GetItemDefenceRatio(&item);
	}

	if(equip_defence_ratio > MAX_CAREER_DEFENCE_RATIO)
		equip_defence_ratio = MAX_CAREER_DEFENCE_RATIO;

	SetCharacterEquipDefenceRatio(lIndex, (UHINT)equip_defence_ratio);
	
	return	equip_defence_ratio;
}


//�\��G�p��H�����̲ר��m�ʤ���
SLONG	ComputeCharacterFinalDefenceRatio(SLONG lIndex)
{
	SLONG	equip_ratio;
	SLONG	final_ratio;

	equip_ratio = GetCharacterEquipDefenceRatio(lIndex);
	final_ratio = equip_ratio;

	SetCharacterFinalDefenceRatio(lIndex, (UHINT)final_ratio);

	return	final_ratio;
}


SLONG	GetItemDefenceRatio(TPOS_ITEM *IT)
{
	SLONG	type, hp;
	SLONG	data_type, data_value;
	SLONG	defence_ratio;

	//
	// Only land equipment item has add str property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Defence ratio are associated with type1-data1 and type2-data2.
	//
	defence_ratio = 0;
	data_type = GetLandItemDataType1(IT);
	if(data_type == LAND_ITEM_DATATYPE_ENHANCE_DEF)
	{
		data_value = GetLandItemDataValue1(IT);
		defence_ratio += data_value;
	}
	
	data_type = GetLandItemDataType2(IT);
	if(data_type == LAND_ITEM_DATATYPE_ENHANCE_DEF)
	{
		data_value = GetLandItemDataValue2(IT);
		defence_ratio += data_value;
	}

	return	defence_ratio;
}

	//UHINT	WeaponBaseAtt;			//�Z���˳ƪ��򥻧����O
	//UHINT	EquipAddedAtt;			//�Ҧ��˳ƼW�[���ˮ`�O
	//UHINT	EquipEnhanceAttRatio;	//�Ҧ��˳ƪ��[�j�ˮ`(%)
	//

extern	UHINT	ComputeCharacterWeaponBaseAtt(SLONG lIndex);
extern	UHINT	ComputeCharacterEquipAddedAtt(SLONG lIndex);
extern	SLONG	ComputeCharacterEquipEnhanceAttRatio(SLONG lIndex);
//�\��: �p��H���Z�����򥻧����O
UHINT	ComputeCharacterWeaponBaseAtt(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	attack;

	attack = 0;
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		attack = GetItemBaseAttack(&item);
	}
	if(attack > MAX_CAREER_ATTACK)
		attack = MAX_CAREER_ATTACK;

	SetCharacterWeaponBaseAtt(lIndex, (UHINT)attack);

	return	(UHINT)attack;
}

//�\��: �p��H���˳ƪ��W�[�����O
UHINT	ComputeCharacterEquipAddedAtt(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	added_attack;

	added_attack = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		added_attack += GetItemAddedAttack(&item);
	}

	if(added_attack > MAX_CAREER_ATTACK)
		added_attack = MAX_CAREER_ATTACK;

	SetCharacterEquipAddedAtt(lIndex, (UHINT)added_attack);
	
	return	(UHINT)added_attack;
}


//�\��: �p��H���Ҧ��˳ƪ��[�j�ˮ`
SLONG	ComputeCharacterEquipEnhanceAttRatio(SLONG lIndex)
{
	TPOS_ITEM	item;
	SLONG	enhance_ratio;

	enhance_ratio = 0;
	GetCharacterEquipHead(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}

	GetCharacterEquipNeck(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipBody(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipWaist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipGlove(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipWeapon(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipWrist(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipFeet(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipOtherA(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipOtherB(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}
	
	GetCharacterEquipOtherC(lIndex, &item);
	if(! IsItemNone(&item))
	{
		enhance_ratio += GetItemEnhanceAttackRatio(&item);
	}

	if(enhance_ratio > MAX_CAREER_ENHANCE_ATTACK_RATIO)
		enhance_ratio = MAX_CAREER_ENHANCE_ATTACK_RATIO;

	SetCharacterEquipEnhanceAttRatio(lIndex, (UHINT)enhance_ratio);
	
	return	enhance_ratio;
}


//�\��: ������o�g��ȫ᪺�p��
SLONG   ComputeCareerUpgradeResult(SLONG char_index, SLONG level, SLONG exp, CAREER_UPGRADE_RESULT *added)
{
    SLONG   next_level, next_exp;
    SLONG   add_max_hp, add_max_mp, add_attrib_point;

    //���Ť��X�k�Ϊ̤w�g�F��̰���
    if(level < 0 || level >= MAX_CAREER_LEVELS-1)
        return  false;

    next_level = level + 1;
    next_exp = l_career_upgrade[char_index][next_level].next_exp;
    if(exp < next_exp)
        return  false;

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

    added->add_max_hp = add_max_hp;
    added->add_max_mp = add_max_mp;
    added->add_attrib_point = add_attrib_point;
    added->next_exp = next_exp;
    added->level = next_level;
    return  true;
}



//--------------------------------------------------------------------------------------------------------
#endif
