#if	0
//--------------------------------------------------------------------------------------------------------
/*
#define	ITEM_TYPE_UNKNOWN					0	//未知物品類別(未知)
#define ITEM_TYPE_CAP						1   //帽子(陸地之頭盔)
#define ITEM_TYPE_HELM						2   //頭盔(陸地之頭盔)
#define ITEM_TYPE_VEIL						3   //面紗(陸地之頭盔)
#define ITEM_TYPE_HAT						4   //禮帽(陸地之頭盔)
#define ITEM_TYPE_MASK						5   //面具(陸地之頭盔)
#define ITEM_TYPE_STRAW						6   //草帽(陸地之頭盔)
#define ITEM_TYPE_SHAKO						7   //軍帽(陸地之頭盔)
#define ITEM_TYPE_CLOTH						8   //衣服(陸地之鎧甲)
#define ITEM_TYPE_CANONICALS				9   //牧師服(陸地之鎧甲)
#define ITEM_TYPE_REGIMENTAL				10  //軍服(陸地之鎧甲)
#define ITEM_TYPE_NIGHTCLOTH				11  //夜行服(陸地之鎧甲)
#define ITEM_TYPE_MAGECLOTH					12  //法師袍(陸地之鎧甲)
#define ITEM_TYPE_BIZCLOTH					13  //商賈之服(陸地之鎧甲)
#define ITEM_TYPE_ROBE						14  //禮服(陸地之鎧甲)
#define ITEM_TYPE_HEAVYPLATE				15  //重鎧(陸地之鎧甲)
#define ITEM_TYPE_CHAINARMOR				16  //鏈子甲(陸地之鎧甲)
#define ITEM_TYPE_LIGHTPLATE				17  //輕甲(陸地之鎧甲)
#define ITEM_TYPE_WEDDING					18  //婚紗(陸地之鎧甲)
#define ITEM_TYPE_SHOES						19  //鞋類(陸地之鞋類)
#define ITEM_TYPE_BOOT						20  //靴類(陸地之鞋類)
#define ITEM_TYPE_BELT						21  //腰帶(陸地之腰帶)
#define	ITEM_TYPE_GLOVE						22	//手套(陸地)
#define ITEM_TYPE_SWORD						23  //劍(陸地武器)
#define ITEM_TYPE_CLERIC					24  //傳教士專用武器(陸地武器)
#define ITEM_TYPE_GUN						25  //手槍(陸地武器)
#define ITEM_TYPE_DAGGER					26  //匕首(陸地武器)
#define ITEM_TYPE_THONG						27  //皮鞭(陸地武器)
#define ITEM_TYPE_CRYSTAL					28  //水晶球(陸地武器)
#define ITEM_TYPE_COIN						29  //金幣(陸地武器)
#define ITEM_TYPE_RING						30  //戒指(陸地裝飾)
#define ITEM_TYPE_AMULET					31  //護身符(陸地裝飾)
#define ITEM_TYPE_JEWEL						32  //珠寶(陸地裝飾)
#define ITEM_TYPE_CLASSIC					33  //角色專用(陸地)
#define ITEM_TYPE_DRUG						34  //藥品(藥品)
#define	ITEM_TYPE_TREASURE					35	//藏寶圖(碎片)(陸地, 海洋)
#define	ITEM_TYPE_STATUE					36	//船首像(海洋)
#define	ITEM_TYPE_SAIL						37	//船帆(海洋)
#define	ITEM_TYPE_EMBOLON					38	//船撞角(海洋)
#define	ITEM_TYPE_CANNON					39	//砲(海洋)
#define	ITEM_TYPE_ARMOR						40	//船裝甲(海洋)
#define	ITEM_TYPE_SEAEXPENDABLE				41	//海洋消耗品(海洋)
#define	ITEM_TYPE_SAILOR					42	//海洋水手(海洋)
#define	ITEM_TYPE_GOODS						43	//商品(陸地, 海洋)
*/
//角色動作相關
typedef	struct POS_CHARACTER_ACTION 
{
	SLONG	DoingKind;			//事務類型
	SLONG	DoingStep;			//事務進行程度
	SHINT	DoingMagic;			//當前使用的法術技能編號
	UCHAR	ImageAction;		//圖檔動作索引
	ULONG	ImageID;			//圖檔文件標示
	//Jack, [1/12/2003]
	//remark for have move these data as union to position 
	//	SLONG	IdleTicks;			//待機: 待機的時間
	//	SLONG	SequentialStep;		//連擊: 是否進行下一個連續的動作
	//	SLONG	BeatedBy;			//被擊: 誰攻擊我 ?
	//	SLONG	BeatedWith;			//被擊: 被甚麼技能攻擊 ?
	//	SLONG	PantTicks;			//被擊倒: 擊倒在地上與爬起來之間的喘息時間
	//	SLONG	BeatedX;			//被擊,死亡,被擊倒: 攻擊源 x座標
	//	SLONG	BeatedY;			//被擊,死亡,被擊倒: 攻擊源 y座標
	//	SLONG	MuseTicks;			//冥想: 每隔多長時間進行一次數值計算
	//	SLONG	ClashSteps;			//衝撞: 衝撞的步數
	//	SLONG	PatrolTicks;		//巡邏: 巡邏IDLE的當前時間
	//	SLONG	PatrolTotalTicks;	//巡邏: 巡邏IDLE的總時間
	//	SLONG	GadTicks;			//隨機移動: IDLE的當前時間
	//	SLONG	GadTotalTicks;		//隨機移動: IDLE的總時間
} TPOS_CHARACTER_ACTION, *LPTPOS_CHARACTER_ACTION;

//角色狀態
typedef	struct POS_CHARACTER_STATE 
{
	ULONG	BitState;				//1/0狀態(是否在戰鬥狀態, 包包是否打開, 在海上或陸地, 是否死亡...)

	SHINT	ReliveTicks;			//再生的時間
	//Jack, [1/12/2003]
	//remark for have move these data as union to position 
	//	SHINT	DeadTicks;				//死亡了多長時間
	SHINT	DeadState;				//死亡的狀態

	SHINT	RMagicState;			//右鍵技能狀態
	SHINT	RMagicTotalTicks;		//右鍵技能總時間
	SHINT	RMagicCurrentTicks;		//右鍵技能當前時間

	SHINT	HeadSleepState;			//頭暈, 睡眠(被動)
	SHINT	HeadSleepTicks;			//頭暈, 睡眠 時間
	SHINT	HeadSleepLevel;			//頭暈, 睡眠 等級

	SHINT	HeadPredictState;		//預知:反隱形, 反偽裝, 反陷阱(主動光環技)
	SHINT	HeadPredictLevel;		//預知:反隱形, 反偽裝, 反陷阱 等級

	SHINT	HeadDefenceState;		//防禦加強(被動或主動)
	SHINT	HeadDefenceTicks;		//防禦加強 時間
	SHINT	HeadDefenceLevel;		//防禦加強 等級

	SHINT	HeadMagicState;			//魔法反彈
	SHINT	HeadMagicTimes;			//魔法反彈次數	
	SHINT	HeadMagicLevel;			//魔法反彈等級

	SHINT	HeadBlindState;			//失明(被動)	
	SHINT	HeadBlindTicks;			//失明 時間	
	SHINT	HeadBlindLevel;			//失明 等級	

	SHINT	BodyDodgeState;			//躲閃(主動光環技)

	SHINT	BodyVirusState;			//中毒(被動)	
	SHINT	BodyVirusTicks;			//中毒 時間	
	SHINT	BodyVirusLevel;			//中毒 等級	

	SHINT	BodyHideState;			//被吸血(被動), 隱形1, 隱形2(主動)	
	SHINT	BodyHideTicks;			//被吸血(被動), 隱形1, 隱形2 時間	
	SHINT	BodyHideLevel;			//被吸血(被動), 隱形1, 隱形2 等級

	SHINT	FootSpeedState;			//遲緩1, 遲緩2(被動或者在範圍內)	
	SHINT	FootSpeedTicks;			//遲緩1, 遲緩2 時間	
	SHINT	FootSpeedLevel;			//遲緩1, 遲緩2 等級	

	SHINT	RotateState;			//旋轉(被動)船隻
	SHINT	RotateTicks;			//旋轉 時間	船隻
	SHINT	RotateLevel;			//旋轉 等級	船隻

	SHINT	FireState;				//著火(被動)船隻
	SHINT	FireTicks;				//著火 時間	船隻
	SHINT	FireLevel;				//著火 等級	船隻

	SHINT	ExplodeState;			//爆炸(被動)船隻
	SHINT	ExplodeTicks;			//爆炸 時間	船隻
	SHINT	ExplodeLevel;			//爆炸 等級	船隻

	SHINT	SailHurtState;			//帆損害 (被動)	船隻
	SHINT	RudderHurtState;		//舵損害 (被動)	船隻

	SHINT	PretendState;			//偽裝 (主動)	船隻
	SHINT	PretendOldFileIndex;	//偽裝前的圖像	船隻
	SHINT	PretendToFileIndex;		//偽裝後的圖像	船隻

	SHINT	HalfDownState;			//半沉	船隻

	SHINT	OctopusState;			//章魚 (被動)	船隻
	SHINT	OctopusTicks;			//章魚 時間	船隻
	SHINT	OctopusLevel;			//章魚 等級	船隻

	ULONG	AI;						//人物戰鬥AI

} TPOS_CHARACTER_STATE, *LPTPOS_CHARACTER_STATE;

//不同職業人物攻擊力受人物4種基本值的影響
typedef struct tagCAREER_AFFECT_ATTACK
{
    SLONG   by_strength;    //受力量影響
    SLONG   by_instinct;    //受直覺影響
    SLONG   by_wit;         //受智力影響
    SLONG   by_luck;        //受運氣影響
} CAREER_AFFECT_ATTACK, *LPCAREER_AFFECT_ATTACK;


//不同職業防禦力受力量,直覺,智力,運氣影響
typedef struct tagCAREER_AFFECT_DEFENCE
{
    SLONG   by_strength;    //受力量影響
    SLONG   by_instinct;    //受直覺影響
    SLONG   by_wit;         //受智力影響
    SLONG   by_luck;        //受運氣影響
} CAREER_AFFECT_DEFENCE, *LPCAREER_AFFECT_DEFENCE;


//不同職業MAX_HP受力量,直覺,智力,運氣影響
typedef struct tagCAREER_AFFECT_MAX_HP
{
    SLONG   by_strength;    //受力量影響
    SLONG   by_instinct;    //受直覺影響
    SLONG   by_wit;         //受智力影響
    SLONG   by_luck;        //受運氣影響
} CAREER_AFFECT_MAX_HP, *LPCAREER_AFFECT_MAX_HP;


//不同職業MAX_MP受力量,直覺,智力,運氣影響
typedef struct tagCAREER_AFFECT_MAX_MP
{
    SLONG   by_strength;    //受力量影響
    SLONG   by_instinct;    //受直覺影響
    SLONG   by_wit;         //受智力影響
    SLONG   by_luck;        //受運氣影響
} CAREER_AFFECT_MAX_MP, *LPCAREER_AFFECT_MAX_MP;


//角色的攻擊力, 防禦力, 生命力上限, 內力上限受基本值影響
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
//功能: 獲得基本值影響的攻擊力
SLONG	GetCareerAttribAffectAttack(void)
{
	return	l_career_attrib_affect.att;
}


//功能: 獲得基本值影響的防禦力
SLONG	GetCareerAttribAffectDefence(void)
{
	return	l_career_attrib_affect.dp;
}


//功能: 獲得基本值影響的生命力上限
SLONG	GetCareerAffectMaxHp(void)
{
	return	l_career_attrib_affect.max_hp;
}


//功能: 獲得基本值影響的內力上限
SLONG	GetCareerAffectMaxMp(void)
{
	return	l_career_attrib_affect.max_mp;
}


//功能: 計算力量的改變對角色屬性的影響
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


//功能: 計算直覺的改變對角色屬性的影響
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


//功能: 計算智力的改變對角色屬性的影響
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


//功能: 計算運氣的改變對角色屬性的影響
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




//功能: 初始化角色基本值影響攻擊數據
void    InitCareerAffectAttack(void)
{
    memset(l_career_affect_attack, 0, sizeof(CAREER_AFFECT_ATTACK) * MAX_GAME_CAREERS);
}


//功能: 載入角色基本值影響攻擊數據
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


//功能: 釋放角色基本值影響攻擊數據
void    FreeCareerAffectAttack(void)
{
    //nothing to do.
}


//功能: 初始化角色基本值影響防禦力數據
void    InitCareerAffectDefence(void)
{
    memset(l_career_affect_defence, 0, sizeof(CAREER_AFFECT_DEFENCE) * MAX_GAME_CAREERS);
}


//功能: 載入角色基本值影響防禦力數據
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


//功能: 釋放角色基本值影響防禦力數據
void    FreeCareerAffectDefence(void)
{
    //nothing to do.
}


//功能: 初始化角色基本值影響HP數據
void    InitCareerAffectMaxHp(void)
{
    memset(l_career_affect_hp, 0, sizeof(CAREER_AFFECT_MAX_HP) * MAX_GAME_CAREERS);
}


//功能: 載入角色基本值影響HP數據
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


//功能: 釋放角色基本值影響HP數據
void    FreeCareerAffectMaxHp(void)
{
    //nothing to do.
}


//功能: 初始化角色基本值影響MP數據
void    InitCareerAffectMaxMp(void)
{
    memset(l_career_affect_mp, 0, sizeof(CAREER_AFFECT_MAX_MP) * MAX_GAME_CAREERS);
}


//功能: 載入角色基本值影響MP數據
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


//功能: 釋放角色基本值影響MP數據
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
//陸地物品特殊屬性定義(SPECIAL 3)
//
#define	LAND_ITEM_SPECIAL3_NONE							0	//無任何屬性
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_STR				1	//力量 + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_STR				2	//力量 + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_STR				3	//力量 + 5
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_INS				4	//直覺 + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_INS				5	//直覺 + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_INS				6	//直覺 + 5
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_WIT				7	//智力 + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_WIT				8	//智力 + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_WIT				9	//智力 + 5
#define	LAND_ITEM_SPECIAL3_ADD_SMALL_LUCKY				10	//運氣 + 1
#define	LAND_ITEM_SPECIAL3_ADD_MIDDLE_LUCKY				11	//運氣 + 3
#define	LAND_ITEM_SPECIAL3_ADD_LARGE_LUCKY				12	//運氣 + 5

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



//功能: 計算人物裝備附加的力量
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

//功能: 計算人物裝備附加的直覺
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

//功能: 計算人物裝備附加的智力
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

//功能: 計算人物裝備附加的運氣
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

	UHINT	SkillPhyRatio;		//被動技能對物理攻擊力的影響百分比
	UHINT	SkillMagicRatio;	//被動技能對法術攻擊力的影響百分比
	UHINT	SkillSpecRatio;		//被動技能對特殊攻擊力的影響百分比
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

//功能：計算人物裝備的防禦力百分比
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


//功能：計算人物的最終防禦百分比
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

	//UHINT	WeaponBaseAtt;			//武器裝備的基本攻擊力
	//UHINT	EquipAddedAtt;			//所有裝備增加的傷害力
	//UHINT	EquipEnhanceAttRatio;	//所有裝備的加強傷害(%)
	//

extern	UHINT	ComputeCharacterWeaponBaseAtt(SLONG lIndex);
extern	UHINT	ComputeCharacterEquipAddedAtt(SLONG lIndex);
extern	SLONG	ComputeCharacterEquipEnhanceAttRatio(SLONG lIndex);
//功能: 計算人物武器的基本攻擊力
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

//功能: 計算人物裝備的增加攻擊力
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


//功能: 計算人物所有裝備的加強傷害
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


//功能: 角色獲得經驗值後的計算
SLONG   ComputeCareerUpgradeResult(SLONG char_index, SLONG level, SLONG exp, CAREER_UPGRADE_RESULT *added)
{
    SLONG   next_level, next_exp;
    SLONG   add_max_hp, add_max_mp, add_attrib_point;

    //等級不合法或者已經達到最高級
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
