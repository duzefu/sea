/*
**	UIIconMessage.h 
**	icon control message functions header.
**
**	Jack, 2003.3.18.
**
**  ZhangZhaohui, 2003.3.26
**  ------�C�����u�X��������r, ���Τ᪺�椬�ʧ@
** 
*/
#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//readme:
//����:
// �C����, ����Y�Ǻ���������, �|�u�X�@�ӫe���a��ICON����r������,
// �Ӯ�������ܹ������C������; �Y�Ǳ��p�U, �i�H�q�L�ƹ��I����ICON��
// �@��Ӯ������^�X����, ��p�P�N�Ϊ̤��P�N��.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//

// 
// CONST ///////////////////////////////////////////////////////////////////////////////////////////////////
//
enum ICONMSG_BASE
{
	IM_HINT		= 0,
	IM_YESNO	= 1,
	IM_MAX		= 8,
	IM_MSGLEN	= 80,
	IM_FRAMES	= 4,
	IM_EVENT	= 25000,
	IM_IMG_YES	= 0,			// "�O"���s�b���ɤ�����m
	IM_IMG_NO	= 1,			// "�_"���s�b���ɤ�����m
	IM_IMG_INFO = 2,			// "�H��"���s�b���ɤ�����m
	IM_MAX_PARA = 4,			// �̦h�|�ӰѼ�
};

enum ICONMSG_ACTION
{
	IMA_YES		= 1,
	IMA_NO		= 2,
};

enum ICONMSG_STATE
{
	IMS_FLASH		= 0,
	IMS_NORMAL		= 1,
	IMS_DISAPPEAR	= 2,
};

enum ICONMSG_LEFT
{
	IMT_FLASH		= 1500,		// 1.5 ��
	IMT_NORMAL		= 10000,	// 10 ��
};
//
// STRUCTS //////////////////////////////////////////////////////////////////////////////////////////////////
//
/*
//������ICON�ϼмv�����
typedef	struct tagICONMSG_IMAGE
{
	CAKE_FRAME_ANI	*cfa;	// images
} ICONMSG_IMAGE, *LPICONMSG_IMAGE;
*/

//
//�����Ѽ�
typedef	struct tagICONMSG_PARA 
{
	ULONG	flags;				// �����лx
//	ULONG	life;				// �����ͦs�ɶ�
	SLONG	num[IM_MAX_PARA];				// ������ưѼ� 1 ~ 3
	CHAR	str[IM_MAX_PARA][IM_MSGLEN];	// �����r��Ѽ� 1 ~ 3
} ICONMSG_PARA;
//
// �������e
typedef struct tagICONMSG
{
	union
	{
		SLONG		alpha;				// �z����
		DWORD		flash;				// ����{�{
	};
	DWORD		state;				// ��������e���A
	DWORD		start_time;			// ��e���A���}�l�ɶ�
	CHAR		msg[IM_MSGLEN];		// ������r
} ICONMSG;
//
//�������
typedef	struct tagICONMSG_NODE	ICONMSG_NODE; 
struct tagICONMSG_NODE
{
	INT				index;			// ����������
	DWORD			event;			// �Τ�]�w���ƥ�
	DWORD			type;			// �������лx
	ICONMSG			content;		// ���������e
	ICONMSG_PARA	para;			// �������Ѽ�
};

//
//�����w�q��r
typedef	struct  tagMSG_DEFINE
{
	DWORD   para_type;			// 0-�L�Ѽ�,0X1-�r�Ŧ�,0X2-�㫬
	CHAR	text[IM_MSGLEN];
} MSG_DEFINE;


//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//

INT		init_iconmsg( VOID );
VOID	active_iconmsg( INT active );
VOID	free_iconmsg( VOID );

INT		add_iconmsg( DWORD id, DWORD type, ICONMSG_PARA* para, DWORD event );

VOID	refresh_iconmsg( VOID );
LONG	handle_iconmsg( UINT msg, WPARAM wparam, LPARAM lparam );
VOID	redraw_iconmsg( BMP *bitmap );




