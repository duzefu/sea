/*
**  ClientMain.h
**  client main functions header.
**
**  Jack, 2002.5.6.
*/
#ifndef _CLIENTMAIN_H_
#define _CLIENTMAIN_H_


//DEFINES //////////////////////////////////////////////////////////////////////////////////////
//
#define WM_IME_STRING       (WM_USER+999)   //�Τ��J���~�r�r�����


typedef enum    APPSTATE_ENUMS
{   APPSTATE_SYSTEM_INIT                    =   0,      //�t�Ϊ�l��
APPSTATE_SHOW_SWAP_SCREEN					=	1,		//�̹�����(�S��)
//
APPSTATE_INIT_EULA                          =   5,      //�ǳƪ��v�ŧi
APPSTATE_SHOW_EULA                          =   6,      //���v�ŧi
//
APPSTATE_INIT_LOGIN                         =   10,     //�ǳƵn������
APPSTATE_SHOW_LOGIN                         =   20,     //�n������
//
APPSTATE_INIT_CREDITS                       =   30,     //�ǳƻs�@�s
APPSTATE_SHOW_CREDITS                       =   40,     //�s�@�s
//
APPSTATE_INIT_ACCOUNT_MANAGER               =   50,     //�ǳƱb���޲z
APPSTATE_SHOW_ACCOUNT_MANAGER               =   60,     //�b���޲z
//
APPSTATE_INIT_SELECT_WORLD_SERVER           =   70,     //�ǳƿ�ܥ@�ɦ��A��
APPSTATE_SHOW_SELECT_WORLD_SERVER           =   80,     //��ܥ@�ɦ��A��
//
APPSTATE_INIT_SELECT_CHARACTER              =   90,     //�ǳƿ�ܨ���
APPSTATE_SHOW_SELECT_CHARACTER              =   100,    //��ܨ���
//
APPSTATE_INIT_CREATE_CHARACTER              =   110,    //�ǳƳЫب���
APPSTATE_SHOW_CREATE_CHARACTER              =   120,    //�Ыب���
//
APPSTATE_INIT_CHG_CHAR_COLOR				=	121,	//�ǳƭק�H���C��
APPSTATE_SHOW_CHG_CHAR_COLOR				=	122,	//�]�m�H���v���C��
//
APPSTATE_INIT_SET_CHAR_FACE                 =   130,    //�ǳƳ]�m�H���v��
APPSTATE_SHOW_SET_CHAR_FACE                 =   140,    //�]�m�H���v��
//
APPSTATE_INIT_SET_CHAR_LOCATE               =   150,    //�ǳƳ]�m�H���X�ͦa
APPSTATE_SHOW_SET_CHAR_LOCATE               =   160,    //�]�m�H���X�ͦa
//
APPSTATE_INIT_LOADING_MAIN_GAME             =   170,    //�ǳƸ��J�D�C��
APPSTATE_SHOW_LOADING_MAIN_GAME             =   180,    //���J�D�C��
//
APPSTATE_INIT_MAIN_GAME                     =   200,    //�ǳƶi�J�D�C��
APPSTATE_SHOW_MAIN_GAME                     =   210,    //�D�C��
//
APPSTATE_INIT_CREATE_ACCOUNT                =   220,    //�ǳƳЫطs�b��
APPSTATE_SHOW_CREATE_ACCOUNT                =   230,    //��J�b���M�K�X
//
APPSTATE_INIT_SETUP_RECORD                  =   240,    //�ǳƫإ߸��
APPSTATE_SHOW_SETUP_RECORD                  =   250,    //�إ߸��
//
APPSTATE_INIT_SELECT_PAYMENT                =   260,    //�ǳƿ�ܥI�ڤ覡
APPSTATE_SHOW_SELECT_PAYMENT                =   270,    //��ܥI�ڤ覡
//
APPSTATE_INIT_MODIFY_RECORD                 =   290,    //�ǳƭק���
APPSTATE_SHOW_MODIFY_RECORD                 =   300,    //�ק���
//
APPSTATE_INIT_CHANGE_PASSWORD               =   310,    //�ǳƭק�K�X
APPSTATE_SHOW_CHANGE_PASSWORD               =   320,    //�ק�K�X
//
APPSTATE_INIT_SUPPLY_POINTS                 =   330,    //�ǳƥR���I��
APPSTATE_SHOW_SUPPLY_POINTS                 =   340,    //�R���I��
//
APPSTATE_INIT_CHANGEMAP_LOADING             =   350,    //�����a�ϫe�����ݵe��
APPSTATE_SHOW_CHANGEMAP_LOADING             =   360,    //�����a�ϫe������
//
APPSTATE_INIT_STARTING_SINGLE_GAME			=	99980,	//�ǳƶ}�l����C��(����)
APPSTATE_SHOW_STARTING_SINGLE_GAME			=	99981,	//�}�l����C��(����)
//
APPSTATE_ERROR_EXIT                         =   99990,  //�X�{���~�A�h�X
APPSTATE_SYSTEM_EXIT                        =   100000, //�t�Υ��`�h�X
//
APPSTATE_TEST_GRAFX                         =   100001,  //����
//
} APPSTATE_ENUMS;



typedef	enum	APPEVENT_ENUMS
{	APPEVENT_NOTHING						=	0,		//�S������ƥ�
APPEVENT_START_CHANGE_ZONE					=	1,		//�}�l����ZONE
APPEVENT_START_LOGIN_ZONE					=	2,		//�}�l�n�JZONE
APPEVENT_START_PLAY_MAINGAME				=	3,		//�}�l�C��
} APPEVENT_ENUMS;


//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////// 
extern  HINSTANCE   g_hInstance;                // App instance
extern  DWORD   g_dwAppState;               //���ε{������e���檬�A
extern  DWORD   g_dwOldAppState;            //���ε{�����H�e���檬�A
extern  DWORD   g_dwNextAppState;           //���ε{�����U�@�Ӱ��檬�A
extern	DWORD	g_dwAppEvent;				//���ε{�����ƥ�
extern  DWORD   g_dwConnectedServerType;    //���ε{���ثe�s�������A������
extern  LONG    g_lPlayerIndex;             //���a�� NPC ���޸�
extern  LONG    g_lPlayerMap;               //���a��e�Ҧb���a��, ��ڤW�ثe�u�Ψӧ@ map_base[]������, 
                                            //�åB�T�w�� 0.
extern  TCHAR   g_szPlayerZone[64];         //���a��e�Ҧb��ZONE�W��
extern	DWORD	g_dwZoneType;				//���a��e�Ҧb��ZONE����
extern  TCHAR   g_szPlayerMap[64];          //���a��e�Ҧb���a�ϦW��
extern  TCHAR   g_szPlayerMainName[64];     //���a���W��
extern  DWORD   g_dwHeartBeat;              //�߸����ƭp��
extern	LONG	g_lIsSingleGame;			//�O�_������C��
extern	LONG	g_IsExitingGame;			//�����C���O�_���b�h�X(���a��ESC�H��).
//
extern  DATA_FILE   *packed_data_file;   //(1) �ƭȳ���	data.pos	<data>
extern  DATA_FILE   *packed_menu_file;   //(2) ��泡��	menu.pos	<menu>
extern  DATA_FILE   *packed_sound_file;  //(3) ���ĳ���	sound.pos	<sound>
extern  DATA_FILE   *packed_music_file;  //(4) ���ֳ���	music.pos	<music>
extern  DATA_FILE   *packed_tile_file;   //(5) �ϯ�����	tile.pos	<tile>
extern  DATA_FILE   *packed_house_file;  //(6) �Ыγ���	house.pos	<house>
extern  DATA_FILE   *packed_map_file;    //(7) �a�ϳ���	map.pos	    <map>
extern  DATA_FILE   *packed_object_file; //(8) ���󳡤�	object.pos	<object>
extern	DATA_FILE	*packed_macro_file;	 //(9) �@������ macro.pos   <macro>
extern  DATA_FILE   *packed_other_file;  //(10) ��L		sea.pos
extern	DATA_FILE	*packed_npc_file;	//(11) LAND NPC npc.pos
extern	DATA_FILE	*packed_seanpc_file;	//(11) SEA NPC seanpc.pos

//FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////
extern  void    change_app_state(void);
extern  void    set_next_app_state(DWORD dwNextState);




#endif//_CLIENTMAIN_H_
