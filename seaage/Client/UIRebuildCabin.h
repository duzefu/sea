/*
 * UIRebuildCabin.h
 *
 * write by lairiwen
 * 2002.11.29
 */


#ifndef __UIREBUILDCABIN_H__
#define __UIREBUILDCABIN_H__

/*
 * 要从服务器取的数据有:
 *     1.船的类型.
 *     2.每个船舱的类型,及船舱中的物品.
 *     3.玩家现在所在港口改造不同船舱的价格及不同船舱在此港口拆除所能的到的金钱.
 *     4.玩家持有金钱.
 *
 * 返回给服务器的数据.
 *     1:玩家船的类型.
 *     2:玩家改造船舱的类型.
 */


#define MAX_SHIP_NUM 20
#define MAX_CABIN_NUM 40

// 每种船的船舱数量.
extern int g_CabinNum[MAX_SHIP_NUM];

// 每种船各个船舱的位置及船舱类型.
extern int g_CabinPos[MAX_SHIP_NUM][MAX_CABIN_NUM][3];

#endif /*__UIREBUILDCABIN_H__*/
