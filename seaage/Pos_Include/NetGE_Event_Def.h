//===============================================================================
// Netge_Event_Def.h
//===============================================================================
#ifndef NETGE_EVENT_DEF_H
#define NETGE_EVENT_DEF_H
//===============================================================================

// ---------------------------------------------------------------------------
#define		WM_POSGAMEEVENT		 			(WM_USER+1001)

// ---------------------------------------------------------------------------
// Init Winsocket Erroe Message
// ---------------------------------------------------------------------------
#define		WINSOCK_VER_ERROR            	-1    // WINSOCKET �������~
#define		INIT_SOCKET_ERROR           	-2    // �_�l SOCKET ���~
#define		CANT_CONNECTED		         	-3    // �L�k�s�����A��
#define		CANT_ASYNC   		         	-4    // �L�k�D�P�B�s��
// ---------------------------------------------------------------------------
// Common Event
// ---------------------------------------------------------------------------
#define	    WORLD_LOGIN   		            1002  // �@�ɦ��A�����U
#define	    ZONE_LOGIN    		            1003  // �ϰ���A���n�J
#define	    PLAYER_LOGIN 		            1004  // ���a�n�J

#define		DOOR_SERVER_CLOSED	     		1005  // �j�U���A������ 	
#define		WORLD_SERVER_CLOSED				1006  // �@�ɦ��A������	
#define		ZONE_SERVER_CLOSED				1007  // �ϰ���A������

#define     VERSION_ERROR                   1008  // �������~
#define		ERROR_DATA						1009  // ��ƿ��~	
	
#define	    SAVE_USER_DETAIL         		1010  // �x�s���a��� - [DOOR]

#define		DOOR_SERVER_FULL				1011  // Door Server �H��
#define		WORLD_SERVER_FULL				1012  // World Server �H��
#define		ZONE_SERVER_FULL				1013  // Zone Server �H��
#define		QQ_SERVER_FULL					1014  // QQ Server �H��

#define 	MAX_PLAYER_PER_WORLD	        1000  // �C�� World ���n�J�H��
#define	    MAX_PLAYER_PER_ZONE	            500   // �C�� Zone ���n�J�H��
#define	    MAX_NPC_PER_ZONE	            500   // �C�� Zone �� NPC
#define     MAX_ZONE_PER_WORLD              100   // �C�� World �̦h�e�� Zone ���ƶq
#define	    MAX_PLAYER_PER_DOOR	            1000  // �C�� Door ���n�J�H��
#define     MAX_WORLD_PER_DOOR              50    // �C�� Door �� World �s����
#define     MAX_CHARACTER_TYPE              42    // ���a�i��ܨ��⪺����
#define     MAX_COUNTRYSEL_PER_WORLD        16    // ���a�i��ܰ��y���ƶq 
#define		MAX_QQQUERY_PER_WORLD			1000  // �C�� World �i�d��QQ��ƪ��H��
// ---------------------------------------------------------------------------
// DoorServerEvent
// ---------------------------------------------------------------------------
#define		DOOR_LOGIN_OK					101   // �n�J�j�U���\
#define		DOOR_LOGIN_FAIL					102   // �n�J�j�U����
#define     REGISTER_ACCOUNT_CHECK          103   // ���U�b���ˬd�W��
#define     REGISTER_ACCOUNT_FINAL          104   // ���U�b���T�{
#define     REGISTER_ACCOUNT_IDUSED         105   // ���U ID �w�Q�ϥ�
#define     REGISTER_ACCOUNT_CHECK_OK       106   // ���U�b���ˬd�W�٦��\
#define     REGISTER_ACCOUNT_CHECK_FAIL     107   // ���U�b���ˬd�W�٥���
#define     REGISTER_ACCOUNT_FINAL_OK       108   // ���U�b���T�{���\
#define     REGISTER_ACCOUNT_FINAL_FAIL     109   // ���U�b���T�{����
#define     DOOR_LOGIN_ERRORID              110   // �n�J�j�U_�L�� ID
#define     DOOR_LOGIN_ERRORPW              111   // �n�J�j�U_�K�X���~
#define     DOOR_LOGIN_DENIED               112   // �n�J�j�U_�ڵ��n�J
#define     DOOR_KICKED                     113   // �n�J�j�U_�Q���A����
#define     DOOR_LOGIN_REPEAT               114   // �n�J�j�U_���Ƶn�J
#define     CHANGE_PASSWORD                 115   // ���K�X
#define     CHANGE_PASSWORD_OK              116   // ���K�X���\
#define     CHANGE_PASSWORD_FAIL            117   // ���K�X����
#define     CHANGE_PROFILE                  118   // ���򥻸��
#define     CHANGE_PROFILE_OK               119   // ���򥻸�Ʀ��\
#define     CHANGE_PROFILE_FAIL             120   // ���򥻸�ƥ���
#define     CHANGE_PAY_TYPE                 121   // ���I�ڤ覡
#define     CHANGE_PAY_TYPE_OK              122   // ���I�ڤ覡���\ 
#define     CHANGE_PAY_TYPE_FAIL            123   // ���I�ڤ覡����
#define     ADD_PAY                         124   // �W�[�I�� 
#define     ADD_PAY_OK                      125   // �W�[�I�Ʀ��\
#define     ADD_PAY_FAIL                    126   // �W�[�I�ƥ���
#define     GET_WORLD_INFO_OK               127   // ���o�@�ɦ��A�����OK
#define		REQUEST_WORLD_INFO				128	  // �n�D�@�ɦ��A�����	
// ---------------------------------------------------------------------------
// WorldServerEvent
// ---------------------------------------------------------------------------
#define		WORLD_LOGIN_OK					201   // �n�J�@�ɦ��\
#define		WORLD_LOGIN_FAIL				202   // �n�J�@�ɥ���
#define	    SEND_WORLD_INFO		            203   //*�ǰe�@�ɪA�Ⱦ���� 
#define	    REFRESH_WORLD_INFO            	204   // ��s�@�ɦ��A�����
#define	    NEW_WORLD_INFO            	    205   // �@�ӷs���@�ɦ��A���[�J
#define	    ONE_WORLD_CLOSE            	    206   // �@�ӥ@�ɦ��A������
#define	    GET_WORLD_INFO		            207   // ���o�@�ɦ��A�����
#define     CREATE_CHARACTER                208   // �Ыب���         (��k 1 )
#define     CREATE_CHARACTER_CHECK          209   // �Ыب����ˬd�W�� (��k 2-1 )  
#define     CREATE_CHARACTER_FINAL          210   // �Ыب���T�{     (��k 2-2 )
#define     DELETE_CHARACTER                211   // �R������
#define     CREATE_CHARACTER_OK             212   // �Ыب��⦨�\
#define     CREATE_CHARACTER_FAIL           213   // �Ыب��⥢��   
#define     CREATE_CHARACTER_CHECK_OK       214   // �Ыب����ˬd�W�٦��\
#define     CREATE_CHARACTER_CHECK_FAIL     215   // �Ыب����ˬd�W�٥���
#define     CREATE_CHARACTER_FINAL_OK       216   // �Ыب���T�{���\
#define     CREATE_CHARACTER_FINAL_FAIL     217   // �Ыب���T�{����
#define     DELETE_CHARACTER_OK             218   // �R�����⦨�\
#define     DELETE_CHARACTER_FAIL           219   // �R�����⥢��
#define     SEND_WORLD_TALK                 220   //*�e�X�@�ɲ��
#define     CREATE_CHARACTER_NAMEUSED       221   // �Ыب���W�r����
#define     WORLD_LOGIN_ERRORID             222   // �n�J�@��_�L�� ID
#define     WORLD_LOGIN_ERRORPW             223   // �n�J�@��_�K�X���~  
#define     WORLD_LOGIN_DENIED              224   // �n�J�@��_�ڵ��n�J
#define     WORLD_KICKED                    225   // �n�J�@��_�Q���A����
#define     WORLD_LOGIN_REPEAT              226   // �n�J�@��_���Ƶn�J
#define     GET_CHARACTER_INFO              227   // ���o������
#define     REQUEST_CHARACTER_DEFAULT       228   // �n�D�ҿ�ܹw�]���D�����
#define     GET_CHARACTER_DEFAULT           229   // ���o��ܹw�]�D�����
#define     ZONENAME_DUPLICATE              230   // �ϰ���A���W�٤w�Q�ϥ�
#define     PLAYER_REQUEST_LOGIN_ZONE       231   // ���a�n�D�i�J�ϰ���A�������
#define		CHARACTER_SELECTED				232   // ���a��ܪ�����
#define		REQUEST_CHARACTER_INFO			233	  // ���a�n�D����M��
#define		REQUEST_ZONE_INFO				234	  // �n�D Zone Server ���	
#define		ZONE_REQUEST_ITEM_ID			235	  // �ϰ���A���n�D���~�ߤ@ ID	
#define		ZONE_GET_ITEM_ID				236	  // �@�ɦ��A���e���ϰ���A�����~�ߤ@ ID	
#define		ZONE_REQUEST_JOIN_TEAM			237	  // �O���ϰ쪱�a�n�D�[�J����	
#define		ZONE_REQUEST_AGREE_JOIN_TEAM	238	  // �P�N�O���ϰ쪱�a�[�J����	
#define		ZONE_REQUEST_EXIT_TEAM			239	  // �O���ϰ쪱�a�n�D���}����	
#define		ZONE_REQUEST_KICK_TEAM_MEMBER	240	  // �O���ϰ쪱�a�n�D�簣����
#define		ZONE_NOTIFY_SOMEONE_WANT_JOIN_TEAM	241	  // �q���Y�H�[�J����	
#define		ZONE_NOTIFY_JOIN_TEAM_FULL		242   // �q���n�[�J������w��
#define		ZONE_NOTIFY_ALREADY_IN_TEAM		243	  // �w�g�b�O������	
#define		ZONE_NOTIFY_SOMEONE_JOIN_TEAM	244	  // �q���Y�H�[�J����	
#define		ZONE_NOTIFY_SOMEONE_EXIT_TEAM	245	  // �q���Y�H���}����	
#define		ZONE_NOTIFY_KICKED_FROM_TEAM	246   // �q���Q��������
#define		ZONE_NOTIFY_TEAM_MEMBER_INFO	247	  // �[�J����\�óq�����͸�T
#define		ZONE_NOTIFY_TEAM_MEMBER_CHANGEZONE	248	  // �q�����ʹ��ϰ�	

// ---------------------------------------------------------------------------
// ZoneServerEvent
// ---------------------------------------------------------------------------
			/* �n�X�J���� */
#define		ZONE_LOGIN_OK					301   // �n�J�ϰ즨�\
#define		ZONE_LOGIN_FAIL  				302   // �n�J�ϰ쥢��
#define     SEND_ZONE_INFO                  303   // �ǰe�ϰ���  
#define     REFRESH_ZONE_INFO               304   // ��s�ϰ���
#define     NEW_ZONE_INFO                   305   // �s���ϰ���
#define     ONE_ZONE_CLOSE                  306   // �@�Ӱϰ�����
#define	    GET_ZONE_INFO                	307   // ���o�ϰ���
#define     GET_PLAYER_LIST                 308   // �n�J���a�C��   
#define     ZONE_LOGIN_ERRORID              311   // �n�J�ϰ�_�L�� ID 
#define     ZONE_LOGIN_ERRORPW              312   // �n�J�ϰ�_�K�X���~
#define     ZONE_LOGIN_DENIED               313   // �n�J�ϰ�_�ڵ��n�J
#define     ZONE_KICKED                     314   // �n�J�ϰ�_�Q���A���簣
#define     ZONE_LOGIN_REPEAT               315   // �n�J�ϰ�_���Ƶn�J
#define     PLAYER_JOIN                     316   // ���a�[�J
#define     PLAYER_EXIT                     317   // ���a���}
#define     GAME_START                      318   // �a�ϸ����C���}�l  
#define		REQUEST_EXIT_GAME				319   // �n�D���}�C��
#define		PREPARE_PLAYER_EXIT_GAME_OK		320	  // ���a�n�D���}�C�� Server �ǳ� OK	
#define     PLAYER_LOGOUT                   321   // ���a���}
#define     SAVE_CHARACTER_INFO             322   // �x�s������
#define		REQUEST_PLAYER_LIST				323	  // ���a�n�D�b�u���a���				
#define     GET_REFRESH                     324   // �P�B�B���s  
			/* �U���}�� */
#define     SEND_ATTACK_SWITCH              340   // �e�X�����}�� 
#define     GET_ATTACK_SWITCH               341   // ���o�����}�� 
#define     SEND_BAG_SWITCH                 342   // �e�X�˳ƳU�}�� 
#define     GET_BAG_SWITCH                  343   // ���o�˳ƳU�}��
			/* �ޯ���� */
#define     CHANGE_MOUSE_SKILL              350   // ���ܷƹ��ޯ� 
#define     GET_CHANGE_MOUSE_SKILL          351   // ���o���ܷƹ��ޯ�  
#define     SET_MOUSE_SKILL                 352   // ���a�n�J�]�w�ƹ��ޯ�
#define		REQUEST_SET_HAND_QUICK_SKILL	353	  // ���a�n�D�]�m�ֱ��ޯ�(F1~F8)
#define		NOTIFY_SET_HAND_QUICK_SKILL		354   // ���A���q���]�m�ֱ��ޯ�(F1~F8)
#define		REQUEST_USE_HAND_QUICK_SKILL	355	  // ���a�n�D�ϥΧֱ��ޯ�(F1~F8)
#define     GET_PLAYER_SKILL                356   // ���a���o�ޯ�  
#define     GET_PLAYER_QUICK_SKILLITEM      357   // ���a���o�ֱ��ޯ�M�ֱ����~  
			/* �Ѯ���� */
#define     INIT_ZONE_WEATHER               360   // �_�l�ϰ�Ѯ� 
#define     REQUEST_CHANGE_WEATHER          361   // ���a�n�D���ܤѮ�
#define     SET_WEATHER_FAIL                362   // ���a���ܤѮ𥢱� 
#define     GET_ZONE_NOW_WEATHER            363   // ���o�ϰ�_�l�Ѯ𪬺A
			/* ���ϰ� */
#define     GET_CHANGE_MAP                  370   // ���o�󴫦a��
#define     START_CHANGE_MAP                371   // �}�l���a��
			/* ���� */   
#define     GET_NPC_RELIVE					380   // ���o�Ǫ�����
			/* �ɯŬ��� */
#define     NPC_LEVEL_UP                    391   // NPC�ɯ�
#define     UPDATE_NPC_BASE_DATA            392   // ����NPC���򥻼ƭ�
#define     SET_NPC_UPGRADE_BASE_DATA       393   // �]�mNPC���ɯŧ޳N�I��
			/* Doing Kind ���� */
#define     CHANGE_NPC_DOING                400   // ����NPC���b�i�檺�ư�����
#define     UPDATE_NPC_DOING                401   // �ץ�NPC�i�檺�ư������������
			/* �԰����� */
#define		NOTIFY_CREATE_MAGIC_AREA		410	  // �q���ͦ��]�k(�})�ϰ�			
#define		NOTIFY_NPC_AI_BLOCK				411	  // ���A���q�� NPC AI Block
#define		NOTIFY_BREAK_MAGIC				412	  // �q�����ͪk�N�ե�	
			/* �]�m�@���ݩ� */
#define     SET_NPC_EXP                     420   // �]�mNPC���g���
#define     SET_NPC_HP                      421   // �]�mNPC��HP
#define		SET_NPC_MP						422	  // �]�mNPC��MP 
#define		SET_MAINNAME_COLOR				423	  // ���ܦW�r�C��	
#define		SET_GOODEVIL					424   // ���ܪ��a���c��(�]�tPK)
#define		SET_NPC_MOVESPEED				425	  // ���ܲ��ʳt��	
#define		SET_MONEY						426   // ���ܪ���
#define		SET_NPC_SKILL					427	  // �]�m�ޯ�	
#define		SET_NPC_POSITION				428	  // �]�m�y��	
			/* �ާ@���� */
#define     HIT_RECV                        440   // �I����������
#define     HIT_MAP                         441   // �I���a��
#define     HIT_NPC                         442   // �I�� NPC
#define     HIT_ITEM                        443   // �I�����~
#define     END_HIT_MAP                     444   // �I���a�ϵ���
#define		REQUEST_CHANGE_DIR				445	  // ���a��a�󴫤�V 
			/* �ө����� */
#define		NOTIFY_STORE_DATA				460	  // �ө����
#define		REQUEST_BUY_ITEM				461	  // ���a�n�D�R���~
#define		REFRESH_STORE_DATA				462	  // ��s�ө����~
#define		REQUEST_SELL_ITEM				463	  // ���a�n�D�R���~
			/* �ն����� */
#define		REQUEST_JOIN_TEAM				470	  // �n�D�[�J����
#define		REQUEST_AGREE_JOIN_TEAM			471	  // �P�N�Y�H�[�J����	
#define		REQUEST_EXIT_TEAM				472	  // �n�D���}����	
#define		REQUEST_KICK_TEAM_MEMBER		473   // �n�D��}�Y����	
#define		NOTIFY_SOMEONE_WANT_JOIN_TEAM	474	  // �q�������Y�H�Q�[�J
#define		NOTIFY_JOIN_TEAM_FULL			475   // �q���n�[�J������w��
#define		NOTIFY_ALREADY_IN_TEAM			476	  // �w�g�b�O������	
#define		NOTIFY_SOMEONE_JOIN_TEAM		477	  // �q���Y�H�[�J����	
#define		NOTIFY_SOMEONE_EXIT_TEAM		478	  // �q���Y�H���}����	
#define		NOTIFY_KICKED_FROM_TEAM			479   // �q���Q��������
#define		NOTIFY_TEAM_MEMBER_INFO			480	  // �[�J����\�óq�����͸�T
#define		NOTIFY_TEAM_MEMBER_CHANGEZONE	481	  // �q�����ʹ��ϰ�	
#define		NOTIFY_MAKE_TEAM				482	  // �q�������
#define		NOTIFY_KILL_TEAM				483	  // �q������Ѵ�
#define		NOTIFY_CHANGE_LEADER			484	  // �q���������H 
#define		NOTIFY_RELOAD_TEAM_INFO			485	  // ���������T	
			/* �Ȧ���� */
#define		NOTIFY_BANK_MONEY_ITEM			490	  // �q�����a�Ȧ�̭������~�M��	
#define		NOTIFY_MONEY_NOT_ENOUGH			491   // �Ȧ檺���������a���X	
#define		NOTIFY_NO_ITEM_ROOM				492   // �Ȧ檺�Ŷ��������a�s���~
#define		REQUEST_SAVE_MONEY				493   // ���a�n�D�s��
#define		REQUEST_LOAD_MONEY				494   // ���a�n�D����
#define		REQUEST_HIT_BANK_ITEM			495	  // ���a�I���Ȧ檫�~	
#define		NOTIFY_SET_BANK_ITEM			496	  // �q�����a�Ȧ檺���~	
#define		SET_BANK_MONEY					497	  // �]�m�Ȧ���� 	
			/* ���~���� */
#define		REQUEST_HIT_BAG_ITEM			500	  // ���a�I���]�]���~
#define		REQUEST_HIT_HEAD_ITEM			501	  // ���a�I���Y���˳�	
#define		REQUEST_HIT_NECK_ITEM			502   // ���a�I���V���˳�
#define		REQUEST_HIT_BODY_ITEM			503   // ���a�I������˳�
#define		REQUEST_HIT_WAIST_ITEM			504   // ���a�I���y���˳�
#define		REQUEST_HIT_GLOVE_ITEM			505   // ���a�I����M�˳�
#define		REQUEST_HIT_WEAPON_ITEM			506   // ���a�I���Z���˳�
#define		REQUEST_HIT_WRIST_ITEM			507   // ���a�I����ø˳�
#define		REQUEST_HIT_FEET_ITEM			508   // ���a�I���}���˳�
#define		REQUEST_HIT_OTHERA_ITEM			509   // ���a�I����L�˳�
#define		REQUEST_HIT_OTHERB_ITEM			510
#define		REQUEST_HIT_OTHERC_ITEM			511
#define		REQUEST_HIT_SASH_ITEM			512	  // ���a�I���y�a���~
#define		REQUEST_HIT_TRANS_ITEM			513   // ���a�I���ǰe���~
#define		REQUEST_HIT_TREASURE_ITEM		514	  // ���a�I�����_�a��
#define		REQUEST_DROP_ITEM				515   // ���a��󪫫~
#define		REQUEST_HIT_MAP_ITEM			516   // ���a�I���a�W���~
#define		NOTIFY_ADD_MAP_ITEM				517	  // ���A���q�����a�a�W�W�[���~
#define		NOTIFY_DELETE_MAP_ITEM			518   // ���A���q�����a�a�W�R�����~
#define		NOTIFY_SET_ONMOUSE_ITEM			519	  // ���A���q�����a�]�w��W���~
#define		NOTIFY_SET_BAG_ITEM				520   // ���A���q�����a�]�w�]�]���~
#define		NOTIFY_SET_HEAD_ITEM			521   // ���A���q�����a�]�w�Y���˳�
#define		NOTIFY_SET_NECK_ITEM			522   // ���A���q�����a�]�w�V���˳�
#define		NOTIFY_SET_BODY_ITEM			523   // ���A���q�����a�]�w����˳�
#define		NOTIFY_SET_WAIST_ITEM			524   // ���A���q�����a�]�w�y���˳�
#define		NOTIFY_SET_GLOVE_ITEM			525   // ���A���q�����a�]�w��M�˳�
#define		NOTIFY_SET_WEAPON_ITEM			526   // ���A���q�����a�]�w�Z���˳�
#define		NOTIFY_SET_WRIST_ITEM			527   // ���A���q�����a�]�w��ø˳�
#define		NOTIFY_SET_FEET_ITEM			528   // ���A���q�����a�]�w�}���˳�
#define		NOTIFY_SET_OTHERA_ITEM			529   // ���A���q�����a�]�w��L���~
#define		NOTIFY_SET_OTHERB_ITEM			530   // ���A���q�����a�]�w��L���~
#define		NOTIFY_SET_OTHERC_ITEM			531   // ���A���q�����a�]�w��L���~
#define		NOTIFY_SET_SASH_ITEM			532   // ���A���q�����a�]�w�y�����~
#define		NOTIFY_SET_TRANS_ITEM			533   // ���A���q�����a�]�w�ǰe���~
#define		NOTIFY_SET_TREASURE_ITEM		534   // ���A���q�����a�]�w���_�Ϫ��~
#define		NOTIFY_AFTER_CHANGE_EQUIP		535	  // ���ܸ˳ƫ᪺�ƭ�
#define		NOTIFY_ZONE_ITEM_LIST			536	  // ���o�ϰ쪫�~�C��			
			/* �@������ */
#define		NOTIFY_NPC_ON_PAUSE				550	  // NPC�b��ܪ��A	
#define		NOTIFY_NPC_NO_PAUSE				551	  // NPC���}��ܪ��A	
#define		NOTIFY_NPC_TALK					552   // 
#define		NOTIFY_NPC_CHOICE				553
#define		NOTIFY_END_DIALOG				554
#define		REQUEST_NPC_PROC				555
			/* ���Ȭ��� */
#define		NOTIFY_NPC_QUEST_LIST			560	  // ���A���q�� NPC ���ȦC��
#define		NOTIFY_PLAYER_QUEST_LIST		561	  // ���A���q�����a���W���ȦC��
#define		REQUEST_DO_ONE_QUEST			562	  // ���a�n�D�����@�ӥ���
#define		NOTIFY_COMPELETE_QUEST			563	  // ���A���q�����a�����Y�ӥ���
#define		REQUEST_PLAYER_QUEST_LIST		564	  // ���a�n�D�w�������ȲM��	
			/* �_�ì��� */
#define		NOTIFY_MAP_INFO					570	  // �q���a�Ϫ���T
#define		REQUEST_SEPARATE_MAP			571	  // �n�D��}�a��
#define		NOTIFY_BAG_SPACE_NOT_ENOUGH		572	  // �q���]�]�Ŷ������s���}�᪺�a��
			/* ��Ѭ��� */
#define     TALK_PUBLIC                     580   // ���-���}   (�ϰ���A�������a)
#define     TALK_WISPER                     581   // ���-������
#define     TALK_GRUOUP                     582   // ���-�ն�
#define     TALK_GUILD                      583   // ���-�u�|
#define     TALK_COUNTRY                    584   // ���-��a
#define     TALK_PA                         585   // ���-�s�� (OICQ �t�Τ@���h�o�e)
#define     GET_PUBLIC_TALK                 586   // ���o���}���
#define     GET_WORLD_TALK                  587   // ���o�@�ɥ��
#define     SYSTEM_MESSAGE                  588   // �t�Τ��i 

			/* QQ ���� */
#define		QQ_PLAYER_LOGIN					600	  // �n�JQQ	
#define		QQ_LOGIN_OK						601	  // �n�JOK	
#define		QQ_LOGIN_FAIL					602	  // �n�J����	
#define		QQ_LOGIN_ERRPW					603   // �K�X���~
#define		QQ_LOGIN_ERRID					604   // ID���~
#define		QQ_LOGIN_DENIED					605   // �Q�ڵ��n�J
#define		QQ_LOGIN_REPEAT					606   // ���Ƶn�J
#define		QQ_PLAYER_LOGOUT				607	  // �n�X	
#define		QQ_REQUEST_MYDATA				608   // �n�D�ۤv�����
#define		QQ_GET_MYDATA					609   // �����ۤv�����
#define		QQ_REQUEST_FRIEND_LIST			610   // �n�D�n�ͦC��
#define		QQ_GET_FRIEND_LIST				611   // ���o�C��
#define		QQ_REQUEST_GUILD_FRIEND_LIST	612   // �n�D�u�|�n�ͦC��
#define		QQ_GET_GUILD_FRIEND_LIST		613   // ���o�u�|�n�ͦC��
#define		QQ_SET_MYSTATE					614   // �]�w�ڪ����A
#define		QQ_GET_MYSTATE					615   // ���o�ڪ����A
#define		QQ_GET_OTHERSTATE				616   // ���o��L�H�ܤƪ����A
#define		QQ_SET_MYCONFIG					617   // ���ܧڪ��]�w   
#define		QQ_GET_MYCONFIG					618   // ���o�ڪ��]�w
#define		QQ_REQUEST_QUERY_SOMEONE		619   // �n�D�d�ߪ��a���
#define		QQ_GET_QUERY_SOMEONE			620   // ���o�d�ߪ����a���
#define		QQ_REQUEST_QUERY_ADD_LIST		621   // �n�D�d�߷Q�[�J�����a�C��
#define		QQ_GET_QUERY_ADD_LIST			622   // ���o�d�߷Q�[�J�����a�C��
#define		QQ_REQUEST_ADD_SOMEONE			623   // �n�D�[�J�Y���a   
#define		QQ_GET_ADD_SOMEONE				624   // ���o�[�J���Y���a
#define		QQ_FRIEND_LOGIN					625   // �n�͵n�J 
#define		QQ_FRIEND_LOGOUT				626   // �n�͵n�X
#define		QQ_REQUEST_TEAM_LIST			627   // ���o���ͦC��
#define		QQ_GET_TEAM_LIST				628   // ���o���ͦC��
#define		QQ_TEAM_JOIN					629   // ���ͥ[�J
#define		QQ_TEAM_EXIT					630   // �������}
#define		QQ_REQUEST_DEL_FRIEND			631	  // �n�D�R���n��
#define		QQ_GET_DEL_FRIEND				632	  // ���o�R���n��	
#define		QQ_SEND_2ONE_MSG				633   // �e���@�Ӧn�ͮ���
#define		QQ_SEND_2SOME_MSG				634	  // �e���ܦh�n�ͮ���	
#define		QQ_GET_MSG						635   // ���o�T��
#define		QQ_REQUEST_PLAYER_COUNT			636   // �n�D���A�������a�H��
#define		QQ_GET_PLAYER_COUNT				637   // ���o���A�������a�H��
#define		QQ_GET_ADD_GUILD_FRIEND			638	  // ���o�[�J���u�|�n��	
#define		QQ_REQUEST_QUERY_ONLINE_ADDLIST 639	  // �n�D�u�W���a
#define		QQ_REQUEST_DEL_GUILD_FRIEND		640	  // �n�D�R���u�|�n��	
#define		QQ_GET_DEL_GUILD_FRIEND			641	  // ���o�R���u�|�n��
#define		QQ_GET_QUERY_ADD_LIST_END		642	  // ���o�d��QQ���a�C����
#define		QQ_REQUEST_TRANSFER_ITEM		643	  // �n�D QQ �ǰe���~
#define		QQ_GET_TRANSFER_ITEM			644	  // ���o QQ �ǿ骫�~
#define		QQ_TRANSFER_ITEM_OK				645	  // QQ �ǿ骫�~ OK	
#define		QQ_TRANSFER_ITEM_FAIL			646	  // QQ �ǿ骫�~ FAIL	
#define		QQ_REQUEST_TRANSFER_ITEM_FROM_WORLD	647	  // �n�D QQ �ǰe���~ (World �o�e)
#define		QQ_TRANSFER_ITEM_OK_FROM_WORLD		648	  // QQ �ǿ骫�~ OK (World �o�e)	
#define		QQ_TRANSFER_ITEM_FAIL_FROM_WORLD	649	  // QQ �ǿ骫�~ FAIL (World �o�e)
// ---------------------------------------------------------------------------
// Zone Map Type
// ---------------------------------------------------------------------------
#define		CITY_NORMAL						10
#define		CITY_NEWBIE						11
#define		CITY_PK							12
#define		CITY_FINDGOLD					13
#define		CITY_BIRTH						14
#define		FIELD_NORMAL					20
#define		FIELD_NEWBIE					21
#define		FIELD_PK						22
#define		FIELD_FINDGOLD					23
#define		FIELD_BIRTH						24
#define		SAIL_NORMAL						30
#define		SAIL_NEWBIE						31
#define		SAIL_PK							32
#define		SAIL_FINDGOLD					33
#define		SAIL_BIRTH						34
// ---------------------------------------------------------------------------
// Game Event
// ---------------------------------------------------------------------------
#define     GAME_EVENT                      800   // Not Use Now
#define     SYNC_POSITION                   801   // �P�B��m
#define     SEA_SYNC_POSITION               802   // ���W�P�B��m
#define     NORMAL                          810   // Not Use Now
#define     ATTACK                          811   // Not Use Now
#define     MOVE                            812   // Not Use Now   
// ---------------------------------------------------------------------------
// Attack Switch
// ---------------------------------------------------------------------------
#define     ATTACK_DISABLED                 0     // Attack Switch Off (Attack Disabled)
#define     ATTACK_ENABLED                  1     // Attack Switch On  (Attack Enabled)
// ---------------------------------------------------------------------------
// Bag Switch
// ---------------------------------------------------------------------------
#define     OPEN_BAG                        1     // ���}�˳ƳU
#define     CLOSE_BAG                       0     // �����˳ƳU
#define     SWITCH_BAG                      2     // �����˳ƳU

// ---------------------------------------------------------------------------
// TOP SECRET MSG
// ---------------------------------------------------------------------------
#define		GOD_REQUEST_FULLHPMP			950	  // �[�� HP & MP	
#define		GOD_REQUEST_JUMPTO				951	  // ���ܮy��
#define		GOD_REQUEST_ITEM				952   // �n�D���~
#define		GOD_REQUEST_MONEY				953		
#define		GOD_REQUEST_EXP					954
#define		GOD_REQUEST_MOVEFAST			955
#define		GOD_REQUEST_SUPERMAN			956
#define		GOD_REQUEST_DEAD				957
#define		GOD_REQUEST_CHANGEZONE			958
#define		GOD_REQUEST_PROPERTYPOINT		959
#define		GOD_REQUEST_GET_MAP				960
#define		GOD_NOTIFY_PROPERTYPOINT		970
// ---------------------------------------------------------------------------
// Mouse Side Hit Define
// ---------------------------------------------------------------------------
#define     LEFT                            0     // �ƹ�����
#define     RIGHT                           1     // �ƹ��k��
// ---------------------------------------------------------------------------
// �����ݩ� 
// ---------------------------------------------------------------------------
#define     UPDATE_NPC_BASE_STRENGTH        0     //����NPC���򥻤O�q
#define     UPDATE_NPC_BASE_INSTINCT        1     //����NPC���򥻪�ı
#define     UPDATE_NPC_BASE_WIT             2     //����NPC���򥻴��O
#define     UPDATE_NPC_BASE_LUCK            3     //����NPC���򥻹B��
// ---------------------------------------------------------------------------
// ���|�j���U�@�B�Z����^��
// ---------------------------------------------------------------------------
#define     STEP_ARRIVE                     0     //��F
#define     STEP_ON_THE_WAY                 1     //�b�~��
#define     STEP_OBSTRUCT                   2     //�Q���j
#define     STEP_OUTSTRETCH                 3     //�W�X�d��
// ---------------------------------------------------------------------------
// ZoneInfo and WorldInfo and PlayerInfo Use
// ---------------------------------------------------------------------------
#define		BEGIN			        		0     
#define		NEXT			        		1
#define     END                             99999 
// ---------------------------------------------------------------------------
// DLL Status Reply
// ---------------------------------------------------------------------------
#define		DLL_ERROR				        0				// return error from DLL
#define		DLL_OK					        1				// return ok from DLL
// ---------------------------------------------------------------------------
// Current Connected Server Type
// ---------------------------------------------------------------------------
#define     CONNECTED_SERVER_NONE           0x00000000      // ���s��������A��
#define     CONNECTED_SERVER_DOOR           0x00000001      // �s��Door���A��
#define     CONNECTED_SERVER_WORLD          0x00000002      // �s��World���A��
#define     CONNECTED_SERVER_ZONE           0x00000004      // �s��Zone���A��
#define     CONNECTED_SERVER_ZONESYNC       0x00000008      // �s��Zone�P�B
// ---------------------------------------------------------------------------
#endif