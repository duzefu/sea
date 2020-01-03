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
#define		WINSOCK_VER_ERROR            	-1    // WINSOCKET 版本錯誤
#define		INIT_SOCKET_ERROR           	-2    // 起始 SOCKET 錯誤
#define		CANT_CONNECTED		         	-3    // 無法連結伺服器
#define		CANT_ASYNC   		         	-4    // 無法非同步連結
// ---------------------------------------------------------------------------
// Common Event
// ---------------------------------------------------------------------------
#define	    WORLD_LOGIN   		            1002  // 世界伺服器註冊
#define	    ZONE_LOGIN    		            1003  // 區域伺服器登入
#define	    PLAYER_LOGIN 		            1004  // 玩家登入

#define		DOOR_SERVER_CLOSED	     		1005  // 大廳伺服器關閉 	
#define		WORLD_SERVER_CLOSED				1006  // 世界伺服器關閉	
#define		ZONE_SERVER_CLOSED				1007  // 區域伺服器關閉

#define     VERSION_ERROR                   1008  // 版本錯誤
#define		ERROR_DATA						1009  // 資料錯誤	
	
#define	    SAVE_USER_DETAIL         		1010  // 儲存玩家資料 - [DOOR]

#define		DOOR_SERVER_FULL				1011  // Door Server 人滿
#define		WORLD_SERVER_FULL				1012  // World Server 人滿
#define		ZONE_SERVER_FULL				1013  // Zone Server 人滿
#define		QQ_SERVER_FULL					1014  // QQ Server 人滿

#define 	MAX_PLAYER_PER_WORLD	        1000  // 每個 World 的登入人數
#define	    MAX_PLAYER_PER_ZONE	            500   // 每個 Zone 的登入人數
#define	    MAX_NPC_PER_ZONE	            500   // 每個 Zone 的 NPC
#define     MAX_ZONE_PER_WORLD              100   // 每個 World 最多容納 Zone 的數量
#define	    MAX_PLAYER_PER_DOOR	            1000  // 每個 Door 的登入人數
#define     MAX_WORLD_PER_DOOR              50    // 每個 Door 的 World 連接數
#define     MAX_CHARACTER_TYPE              42    // 玩家可選擇角色的種類
#define     MAX_COUNTRYSEL_PER_WORLD        16    // 玩家可選擇國籍的數量 
#define		MAX_QQQUERY_PER_WORLD			1000  // 每個 World 可查找QQ資料的人數
// ---------------------------------------------------------------------------
// DoorServerEvent
// ---------------------------------------------------------------------------
#define		DOOR_LOGIN_OK					101   // 登入大廳成功
#define		DOOR_LOGIN_FAIL					102   // 登入大廳失敗
#define     REGISTER_ACCOUNT_CHECK          103   // 註冊帳號檢查名稱
#define     REGISTER_ACCOUNT_FINAL          104   // 註冊帳號確認
#define     REGISTER_ACCOUNT_IDUSED         105   // 註冊 ID 已被使用
#define     REGISTER_ACCOUNT_CHECK_OK       106   // 註冊帳號檢查名稱成功
#define     REGISTER_ACCOUNT_CHECK_FAIL     107   // 註冊帳號檢查名稱失敗
#define     REGISTER_ACCOUNT_FINAL_OK       108   // 註冊帳號確認成功
#define     REGISTER_ACCOUNT_FINAL_FAIL     109   // 註冊帳號確認失敗
#define     DOOR_LOGIN_ERRORID              110   // 登入大廳_無此 ID
#define     DOOR_LOGIN_ERRORPW              111   // 登入大廳_密碼錯誤
#define     DOOR_LOGIN_DENIED               112   // 登入大廳_拒絕登入
#define     DOOR_KICKED                     113   // 登入大廳_被伺服器踢除
#define     DOOR_LOGIN_REPEAT               114   // 登入大廳_重複登入
#define     CHANGE_PASSWORD                 115   // 更改密碼
#define     CHANGE_PASSWORD_OK              116   // 更改密碼成功
#define     CHANGE_PASSWORD_FAIL            117   // 更改密碼失敗
#define     CHANGE_PROFILE                  118   // 更改基本資料
#define     CHANGE_PROFILE_OK               119   // 更改基本資料成功
#define     CHANGE_PROFILE_FAIL             120   // 更改基本資料失敗
#define     CHANGE_PAY_TYPE                 121   // 更改付款方式
#define     CHANGE_PAY_TYPE_OK              122   // 更改付款方式成功 
#define     CHANGE_PAY_TYPE_FAIL            123   // 更改付款方式失敗
#define     ADD_PAY                         124   // 增加點數 
#define     ADD_PAY_OK                      125   // 增加點數成功
#define     ADD_PAY_FAIL                    126   // 增加點數失敗
#define     GET_WORLD_INFO_OK               127   // 取得世界伺服器資料OK
#define		REQUEST_WORLD_INFO				128	  // 要求世界伺服器資料	
// ---------------------------------------------------------------------------
// WorldServerEvent
// ---------------------------------------------------------------------------
#define		WORLD_LOGIN_OK					201   // 登入世界成功
#define		WORLD_LOGIN_FAIL				202   // 登入世界失敗
#define	    SEND_WORLD_INFO		            203   //*傳送世界服務器資料 
#define	    REFRESH_WORLD_INFO            	204   // 更新世界伺服器資料
#define	    NEW_WORLD_INFO            	    205   // 一個新的世界伺服器加入
#define	    ONE_WORLD_CLOSE            	    206   // 一個世界伺服器關閉
#define	    GET_WORLD_INFO		            207   // 取得世界伺服器資料
#define     CREATE_CHARACTER                208   // 創建角色         (方法 1 )
#define     CREATE_CHARACTER_CHECK          209   // 創建角色檢查名稱 (方法 2-1 )  
#define     CREATE_CHARACTER_FINAL          210   // 創建角色確認     (方法 2-2 )
#define     DELETE_CHARACTER                211   // 刪除角色
#define     CREATE_CHARACTER_OK             212   // 創建角色成功
#define     CREATE_CHARACTER_FAIL           213   // 創建角色失敗   
#define     CREATE_CHARACTER_CHECK_OK       214   // 創建角色檢查名稱成功
#define     CREATE_CHARACTER_CHECK_FAIL     215   // 創建角色檢查名稱失敗
#define     CREATE_CHARACTER_FINAL_OK       216   // 創建角色確認成功
#define     CREATE_CHARACTER_FINAL_FAIL     217   // 創建角色確認失敗
#define     DELETE_CHARACTER_OK             218   // 刪除角色成功
#define     DELETE_CHARACTER_FAIL           219   // 刪除角色失敗
#define     SEND_WORLD_TALK                 220   //*送出世界聊天
#define     CREATE_CHARACTER_NAMEUSED       221   // 創建角色名字重複
#define     WORLD_LOGIN_ERRORID             222   // 登入世界_無此 ID
#define     WORLD_LOGIN_ERRORPW             223   // 登入世界_密碼錯誤  
#define     WORLD_LOGIN_DENIED              224   // 登入世界_拒絕登入
#define     WORLD_KICKED                    225   // 登入世界_被伺服器踢除
#define     WORLD_LOGIN_REPEAT              226   // 登入世界_重複登入
#define     GET_CHARACTER_INFO              227   // 取得角色資料
#define     REQUEST_CHARACTER_DEFAULT       228   // 要求所選擇預設的主角資料
#define     GET_CHARACTER_DEFAULT           229   // 取得選擇預設主角資料
#define     ZONENAME_DUPLICATE              230   // 區域伺服器名稱已被使用
#define     PLAYER_REQUEST_LOGIN_ZONE       231   // 玩家要求進入區域伺服器的資料
#define		CHARACTER_SELECTED				232   // 玩家選擇的角色
#define		REQUEST_CHARACTER_INFO			233	  // 玩家要求角色清單
#define		REQUEST_ZONE_INFO				234	  // 要求 Zone Server 資料	
#define		ZONE_REQUEST_ITEM_ID			235	  // 區域伺服器要求物品唯一 ID	
#define		ZONE_GET_ITEM_ID				236	  // 世界伺服器送給區域伺服器物品唯一 ID	
#define		ZONE_REQUEST_JOIN_TEAM			237	  // 別的區域玩家要求加入隊伍	
#define		ZONE_REQUEST_AGREE_JOIN_TEAM	238	  // 同意別的區域玩家加入隊伍	
#define		ZONE_REQUEST_EXIT_TEAM			239	  // 別的區域玩家要求離開隊伍	
#define		ZONE_REQUEST_KICK_TEAM_MEMBER	240	  // 別的區域玩家要求剔除隊友
#define		ZONE_NOTIFY_SOMEONE_WANT_JOIN_TEAM	241	  // 通知某人加入隊伍	
#define		ZONE_NOTIFY_JOIN_TEAM_FULL		242   // 通知要加入的隊伍已滿
#define		ZONE_NOTIFY_ALREADY_IN_TEAM		243	  // 已經在別的隊伍	
#define		ZONE_NOTIFY_SOMEONE_JOIN_TEAM	244	  // 通知某人加入隊伍	
#define		ZONE_NOTIFY_SOMEONE_EXIT_TEAM	245	  // 通知某人離開隊伍	
#define		ZONE_NOTIFY_KICKED_FROM_TEAM	246   // 通知被踢離隊伍
#define		ZONE_NOTIFY_TEAM_MEMBER_INFO	247	  // 加入隊伍成功並通知隊友資訊
#define		ZONE_NOTIFY_TEAM_MEMBER_CHANGEZONE	248	  // 通知隊友換區域	

// ---------------------------------------------------------------------------
// ZoneServerEvent
// ---------------------------------------------------------------------------
			/* 登出入相關 */
#define		ZONE_LOGIN_OK					301   // 登入區域成功
#define		ZONE_LOGIN_FAIL  				302   // 登入區域失敗
#define     SEND_ZONE_INFO                  303   // 傳送區域資料  
#define     REFRESH_ZONE_INFO               304   // 更新區域資料
#define     NEW_ZONE_INFO                   305   // 新的區域資料
#define     ONE_ZONE_CLOSE                  306   // 一個區域關閉
#define	    GET_ZONE_INFO                	307   // 取得區域資料
#define     GET_PLAYER_LIST                 308   // 登入玩家列表   
#define     ZONE_LOGIN_ERRORID              311   // 登入區域_無此 ID 
#define     ZONE_LOGIN_ERRORPW              312   // 登入區域_密碼錯誤
#define     ZONE_LOGIN_DENIED               313   // 登入區域_拒絕登入
#define     ZONE_KICKED                     314   // 登入區域_被伺服器剔除
#define     ZONE_LOGIN_REPEAT               315   // 登入區域_重複登入
#define     PLAYER_JOIN                     316   // 玩家加入
#define     PLAYER_EXIT                     317   // 玩家離開
#define     GAME_START                      318   // 地圖載完遊戲開始  
#define		REQUEST_EXIT_GAME				319   // 要求離開遊戲
#define		PREPARE_PLAYER_EXIT_GAME_OK		320	  // 玩家要求離開遊戲 Server 準備 OK	
#define     PLAYER_LOGOUT                   321   // 玩家離開
#define     SAVE_CHARACTER_INFO             322   // 儲存角色資料
#define		REQUEST_PLAYER_LIST				323	  // 玩家要求在線玩家資料				
#define     GET_REFRESH                     324   // 同步運算刷新  
			/* 各類開關 */
#define     SEND_ATTACK_SWITCH              340   // 送出攻擊開關 
#define     GET_ATTACK_SWITCH               341   // 取得攻擊開關 
#define     SEND_BAG_SWITCH                 342   // 送出裝備袋開關 
#define     GET_BAG_SWITCH                  343   // 取得裝備袋開關
			/* 技能相關 */
#define     CHANGE_MOUSE_SKILL              350   // 改變滑鼠技能 
#define     GET_CHANGE_MOUSE_SKILL          351   // 取得改變滑鼠技能  
#define     SET_MOUSE_SKILL                 352   // 玩家登入設定滑鼠技能
#define		REQUEST_SET_HAND_QUICK_SKILL	353	  // 玩家要求設置快捷技能(F1~F8)
#define		NOTIFY_SET_HAND_QUICK_SKILL		354   // 伺服器通知設置快捷技能(F1~F8)
#define		REQUEST_USE_HAND_QUICK_SKILL	355	  // 玩家要求使用快捷技能(F1~F8)
#define     GET_PLAYER_SKILL                356   // 玩家取得技能  
#define     GET_PLAYER_QUICK_SKILLITEM      357   // 玩家取得快捷技能和快捷物品  
			/* 天氣相關 */
#define     INIT_ZONE_WEATHER               360   // 起始區域天氣 
#define     REQUEST_CHANGE_WEATHER          361   // 玩家要求改變天氣
#define     SET_WEATHER_FAIL                362   // 玩家改變天氣失敗 
#define     GET_ZONE_NOW_WEATHER            363   // 取得區域起始天氣狀態
			/* 換區域 */
#define     GET_CHANGE_MAP                  370   // 取得更換地圖
#define     START_CHANGE_MAP                371   // 開始換地圖
			/* 相關 */   
#define     GET_NPC_RELIVE					380   // 取得怪物重生
			/* 升級相關 */
#define     NPC_LEVEL_UP                    391   // NPC升級
#define     UPDATE_NPC_BASE_DATA            392   // 改變NPC的基本數值
#define     SET_NPC_UPGRADE_BASE_DATA       393   // 設置NPC的升級技術點數
			/* Doing Kind 相關 */
#define     CHANGE_NPC_DOING                400   // 改變NPC正在進行的事務類型
#define     UPDATE_NPC_DOING                401   // 修正NPC進行的事務類型的具體值
			/* 戰鬥相關 */
#define		NOTIFY_CREATE_MAGIC_AREA		410	  // 通知生成魔法(陣)區域			
#define		NOTIFY_NPC_AI_BLOCK				411	  // 伺服器通知 NPC AI Block
#define		NOTIFY_BREAK_MAGIC				412	  // 通知產生法術組件	
			/* 設置一些屬性 */
#define     SET_NPC_EXP                     420   // 設置NPC的經驗值
#define     SET_NPC_HP                      421   // 設置NPC的HP
#define		SET_NPC_MP						422	  // 設置NPC的MP 
#define		SET_MAINNAME_COLOR				423	  // 改變名字顏色	
#define		SET_GOODEVIL					424   // 改變玩家善惡值(包含PK)
#define		SET_NPC_MOVESPEED				425	  // 改變移動速度	
#define		SET_MONEY						426   // 改變金錢
#define		SET_NPC_SKILL					427	  // 設置技能	
#define		SET_NPC_POSITION				428	  // 設置座標	
			/* 操作相關 */
#define     HIT_RECV                        440   // 點擊消息接收
#define     HIT_MAP                         441   // 點擊地圖
#define     HIT_NPC                         442   // 點擊 NPC
#define     HIT_ITEM                        443   // 點擊物品
#define     END_HIT_MAP                     444   // 點擊地圖結束
#define		REQUEST_CHANGE_DIR				445	  // 玩家原地更換方向 
			/* 商店相關 */
#define		NOTIFY_STORE_DATA				460	  // 商店資料
#define		REQUEST_BUY_ITEM				461	  // 玩家要求買物品
#define		REFRESH_STORE_DATA				462	  // 更新商店物品
#define		REQUEST_SELL_ITEM				463	  // 玩家要求買物品
			/* 組隊相關 */
#define		REQUEST_JOIN_TEAM				470	  // 要求加入隊伍
#define		REQUEST_AGREE_JOIN_TEAM			471	  // 同意某人加入隊伍	
#define		REQUEST_EXIT_TEAM				472	  // 要求離開隊伍	
#define		REQUEST_KICK_TEAM_MEMBER		473   // 要求踢開某隊友	
#define		NOTIFY_SOMEONE_WANT_JOIN_TEAM	474	  // 通知隊長某人想加入
#define		NOTIFY_JOIN_TEAM_FULL			475   // 通知要加入的隊伍已滿
#define		NOTIFY_ALREADY_IN_TEAM			476	  // 已經在別的隊伍	
#define		NOTIFY_SOMEONE_JOIN_TEAM		477	  // 通知某人加入隊伍	
#define		NOTIFY_SOMEONE_EXIT_TEAM		478	  // 通知某人離開隊伍	
#define		NOTIFY_KICKED_FROM_TEAM			479   // 通知被踢離隊伍
#define		NOTIFY_TEAM_MEMBER_INFO			480	  // 加入隊伍成功並通知隊友資訊
#define		NOTIFY_TEAM_MEMBER_CHANGEZONE	481	  // 通知隊友換區域	
#define		NOTIFY_MAKE_TEAM				482	  // 通知隊伍成立
#define		NOTIFY_KILL_TEAM				483	  // 通知隊伍解散
#define		NOTIFY_CHANGE_LEADER			484	  // 通知隊長換人 
#define		NOTIFY_RELOAD_TEAM_INFO			485	  // 重取隊伍資訊	
			/* 銀行相關 */
#define		NOTIFY_BANK_MONEY_ITEM			490	  // 通知玩家銀行裡面的物品和錢	
#define		NOTIFY_MONEY_NOT_ENOUGH			491   // 銀行的錢不夠玩家取出	
#define		NOTIFY_NO_ITEM_ROOM				492   // 銀行的空間不夠玩家存物品
#define		REQUEST_SAVE_MONEY				493   // 玩家要求存錢
#define		REQUEST_LOAD_MONEY				494   // 玩家要求取錢
#define		REQUEST_HIT_BANK_ITEM			495	  // 玩家點擊銀行物品	
#define		NOTIFY_SET_BANK_ITEM			496	  // 通知玩家銀行的物品	
#define		SET_BANK_MONEY					497	  // 設置銀行金錢 	
			/* 物品相關 */
#define		REQUEST_HIT_BAG_ITEM			500	  // 玩家點擊包包物品
#define		REQUEST_HIT_HEAD_ITEM			501	  // 玩家點擊頭部裝備	
#define		REQUEST_HIT_NECK_ITEM			502   // 玩家點擊頸部裝備
#define		REQUEST_HIT_BODY_ITEM			503   // 玩家點擊身體裝備
#define		REQUEST_HIT_WAIST_ITEM			504   // 玩家點擊腰部裝備
#define		REQUEST_HIT_GLOVE_ITEM			505   // 玩家點擊手套裝備
#define		REQUEST_HIT_WEAPON_ITEM			506   // 玩家點擊武器裝備
#define		REQUEST_HIT_WRIST_ITEM			507   // 玩家點擊手腕裝備
#define		REQUEST_HIT_FEET_ITEM			508   // 玩家點擊腳部裝備
#define		REQUEST_HIT_OTHERA_ITEM			509   // 玩家點擊其他裝備
#define		REQUEST_HIT_OTHERB_ITEM			510
#define		REQUEST_HIT_OTHERC_ITEM			511
#define		REQUEST_HIT_SASH_ITEM			512	  // 玩家點擊腰帶物品
#define		REQUEST_HIT_TRANS_ITEM			513   // 玩家點擊傳送物品
#define		REQUEST_HIT_TREASURE_ITEM		514	  // 玩家點擊藏寶地圖
#define		REQUEST_DROP_ITEM				515   // 玩家丟棄物品
#define		REQUEST_HIT_MAP_ITEM			516   // 玩家點擊地上物品
#define		NOTIFY_ADD_MAP_ITEM				517	  // 伺服器通知玩家地上增加物品
#define		NOTIFY_DELETE_MAP_ITEM			518   // 伺服器通知玩家地上刪除物品
#define		NOTIFY_SET_ONMOUSE_ITEM			519	  // 伺服器通知玩家設定手上物品
#define		NOTIFY_SET_BAG_ITEM				520   // 伺服器通知玩家設定包包物品
#define		NOTIFY_SET_HEAD_ITEM			521   // 伺服器通知玩家設定頭部裝備
#define		NOTIFY_SET_NECK_ITEM			522   // 伺服器通知玩家設定頸部裝備
#define		NOTIFY_SET_BODY_ITEM			523   // 伺服器通知玩家設定身體裝備
#define		NOTIFY_SET_WAIST_ITEM			524   // 伺服器通知玩家設定腰部裝備
#define		NOTIFY_SET_GLOVE_ITEM			525   // 伺服器通知玩家設定手套裝備
#define		NOTIFY_SET_WEAPON_ITEM			526   // 伺服器通知玩家設定武器裝備
#define		NOTIFY_SET_WRIST_ITEM			527   // 伺服器通知玩家設定手腕裝備
#define		NOTIFY_SET_FEET_ITEM			528   // 伺服器通知玩家設定腳部裝備
#define		NOTIFY_SET_OTHERA_ITEM			529   // 伺服器通知玩家設定其他物品
#define		NOTIFY_SET_OTHERB_ITEM			530   // 伺服器通知玩家設定其他物品
#define		NOTIFY_SET_OTHERC_ITEM			531   // 伺服器通知玩家設定其他物品
#define		NOTIFY_SET_SASH_ITEM			532   // 伺服器通知玩家設定腰部物品
#define		NOTIFY_SET_TRANS_ITEM			533   // 伺服器通知玩家設定傳送物品
#define		NOTIFY_SET_TREASURE_ITEM		534   // 伺服器通知玩家設定藏寶圖物品
#define		NOTIFY_AFTER_CHANGE_EQUIP		535	  // 改變裝備後的數值
#define		NOTIFY_ZONE_ITEM_LIST			536	  // 取得區域物品列表			
			/* 劇本相關 */
#define		NOTIFY_NPC_ON_PAUSE				550	  // NPC在對話狀態	
#define		NOTIFY_NPC_NO_PAUSE				551	  // NPC離開對話狀態	
#define		NOTIFY_NPC_TALK					552   // 
#define		NOTIFY_NPC_CHOICE				553
#define		NOTIFY_END_DIALOG				554
#define		REQUEST_NPC_PROC				555
			/* 任務相關 */
#define		NOTIFY_NPC_QUEST_LIST			560	  // 伺服器通知 NPC 任務列表
#define		NOTIFY_PLAYER_QUEST_LIST		561	  // 伺服器通知玩家身上任務列表
#define		REQUEST_DO_ONE_QUEST			562	  // 玩家要求接受一個任務
#define		NOTIFY_COMPELETE_QUEST			563	  // 伺服器通知玩家完成某個任務
#define		REQUEST_PLAYER_QUEST_LIST		564	  // 玩家要求已接的任務清單	
			/* 寶藏相關 */
#define		NOTIFY_MAP_INFO					570	  // 通知地圖的資訊
#define		REQUEST_SEPARATE_MAP			571	  // 要求拆開地圖
#define		NOTIFY_BAG_SPACE_NOT_ENOUGH		572	  // 通知包包空間不夠存放拆開後的地圖
			/* 聊天相關 */
#define     TALK_PUBLIC                     580   // 聊天-公開   (區域伺服器內玩家)
#define     TALK_WISPER                     581   // 聊天-悄悄話
#define     TALK_GRUOUP                     582   // 聊天-組隊
#define     TALK_GUILD                      583   // 聊天-工會
#define     TALK_COUNTRY                    584   // 聊天-國家
#define     TALK_PA                         585   // 聊天-廣播 (OICQ 系統一次多發送)
#define     GET_PUBLIC_TALK                 586   // 取得公開交談
#define     GET_WORLD_TALK                  587   // 取得世界交談
#define     SYSTEM_MESSAGE                  588   // 系統公告 

			/* QQ 相關 */
#define		QQ_PLAYER_LOGIN					600	  // 登入QQ	
#define		QQ_LOGIN_OK						601	  // 登入OK	
#define		QQ_LOGIN_FAIL					602	  // 登入失敗	
#define		QQ_LOGIN_ERRPW					603   // 密碼錯誤
#define		QQ_LOGIN_ERRID					604   // ID錯誤
#define		QQ_LOGIN_DENIED					605   // 被拒絕登入
#define		QQ_LOGIN_REPEAT					606   // 重複登入
#define		QQ_PLAYER_LOGOUT				607	  // 登出	
#define		QQ_REQUEST_MYDATA				608   // 要求自己的資料
#define		QQ_GET_MYDATA					609   // 取的自己的資料
#define		QQ_REQUEST_FRIEND_LIST			610   // 要求好友列表
#define		QQ_GET_FRIEND_LIST				611   // 取得列表
#define		QQ_REQUEST_GUILD_FRIEND_LIST	612   // 要求工會好友列表
#define		QQ_GET_GUILD_FRIEND_LIST		613   // 取得工會好友列表
#define		QQ_SET_MYSTATE					614   // 設定我的狀態
#define		QQ_GET_MYSTATE					615   // 取得我的狀態
#define		QQ_GET_OTHERSTATE				616   // 取得其他人變化的狀態
#define		QQ_SET_MYCONFIG					617   // 改變我的設定   
#define		QQ_GET_MYCONFIG					618   // 取得我的設定
#define		QQ_REQUEST_QUERY_SOMEONE		619   // 要求查詢玩家資料
#define		QQ_GET_QUERY_SOMEONE			620   // 取得查詢的玩家資料
#define		QQ_REQUEST_QUERY_ADD_LIST		621   // 要求查詢想加入的玩家列表
#define		QQ_GET_QUERY_ADD_LIST			622   // 取得查詢想加入的玩家列表
#define		QQ_REQUEST_ADD_SOMEONE			623   // 要求加入某玩家   
#define		QQ_GET_ADD_SOMEONE				624   // 取得加入的某玩家
#define		QQ_FRIEND_LOGIN					625   // 好友登入 
#define		QQ_FRIEND_LOGOUT				626   // 好友登出
#define		QQ_REQUEST_TEAM_LIST			627   // 取得隊友列表
#define		QQ_GET_TEAM_LIST				628   // 取得隊友列表
#define		QQ_TEAM_JOIN					629   // 隊友加入
#define		QQ_TEAM_EXIT					630   // 隊友離開
#define		QQ_REQUEST_DEL_FRIEND			631	  // 要求刪除好友
#define		QQ_GET_DEL_FRIEND				632	  // 取得刪除好友	
#define		QQ_SEND_2ONE_MSG				633   // 送給一個好友消息
#define		QQ_SEND_2SOME_MSG				634	  // 送給很多好友消息	
#define		QQ_GET_MSG						635   // 取得訊息
#define		QQ_REQUEST_PLAYER_COUNT			636   // 要求伺服器的玩家人數
#define		QQ_GET_PLAYER_COUNT				637   // 取得伺服器的玩家人數
#define		QQ_GET_ADD_GUILD_FRIEND			638	  // 取得加入的工會好友	
#define		QQ_REQUEST_QUERY_ONLINE_ADDLIST 639	  // 要求線上玩家
#define		QQ_REQUEST_DEL_GUILD_FRIEND		640	  // 要求刪除工會好友	
#define		QQ_GET_DEL_GUILD_FRIEND			641	  // 取得刪除工會好友
#define		QQ_GET_QUERY_ADD_LIST_END		642	  // 取得查詢QQ玩家列表結束
#define		QQ_REQUEST_TRANSFER_ITEM		643	  // 要求 QQ 傳送物品
#define		QQ_GET_TRANSFER_ITEM			644	  // 取得 QQ 傳輸物品
#define		QQ_TRANSFER_ITEM_OK				645	  // QQ 傳輸物品 OK	
#define		QQ_TRANSFER_ITEM_FAIL			646	  // QQ 傳輸物品 FAIL	
#define		QQ_REQUEST_TRANSFER_ITEM_FROM_WORLD	647	  // 要求 QQ 傳送物品 (World 發送)
#define		QQ_TRANSFER_ITEM_OK_FROM_WORLD		648	  // QQ 傳輸物品 OK (World 發送)	
#define		QQ_TRANSFER_ITEM_FAIL_FROM_WORLD	649	  // QQ 傳輸物品 FAIL (World 發送)
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
#define     SYNC_POSITION                   801   // 同步位置
#define     SEA_SYNC_POSITION               802   // 海上同步位置
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
#define     OPEN_BAG                        1     // 打開裝備袋
#define     CLOSE_BAG                       0     // 關閉裝備袋
#define     SWITCH_BAG                      2     // 切換裝備袋

// ---------------------------------------------------------------------------
// TOP SECRET MSG
// ---------------------------------------------------------------------------
#define		GOD_REQUEST_FULLHPMP			950	  // 加滿 HP & MP	
#define		GOD_REQUEST_JUMPTO				951	  // 改變座標
#define		GOD_REQUEST_ITEM				952   // 要求物品
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
#define     LEFT                            0     // 滑鼠左鍵
#define     RIGHT                           1     // 滑鼠右鍵
// ---------------------------------------------------------------------------
// 改變屬性 
// ---------------------------------------------------------------------------
#define     UPDATE_NPC_BASE_STRENGTH        0     //改變NPC的基本力量
#define     UPDATE_NPC_BASE_INSTINCT        1     //改變NPC的基本直覺
#define     UPDATE_NPC_BASE_WIT             2     //改變NPC的基本智力
#define     UPDATE_NPC_BASE_LUCK            3     //改變NPC的基本運氣
// ---------------------------------------------------------------------------
// 路徑搜索下一步后的返回值
// ---------------------------------------------------------------------------
#define     STEP_ARRIVE                     0     //到達
#define     STEP_ON_THE_WAY                 1     //在途中
#define     STEP_OBSTRUCT                   2     //被阻隔
#define     STEP_OUTSTRETCH                 3     //超出範圍
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
#define     CONNECTED_SERVER_NONE           0x00000000      // 未連接任何伺服器
#define     CONNECTED_SERVER_DOOR           0x00000001      // 連接Door伺服器
#define     CONNECTED_SERVER_WORLD          0x00000002      // 連接World伺服器
#define     CONNECTED_SERVER_ZONE           0x00000004      // 連接Zone伺服器
#define     CONNECTED_SERVER_ZONESYNC       0x00000008      // 連接Zone同步
// ---------------------------------------------------------------------------
#endif