/*
 * UIRebuildCabin.h
 *
 * write by lairiwen
 * 2002.11.29
 */


#ifndef __UIREBUILDCABIN_H__
#define __UIREBUILDCABIN_H__

/*
 * Ҫ�ӷ�����ȡ��������:
 *     1.��������.
 *     2.ÿ�����յ�����,�������е���Ʒ.
 *     3.����������ڸۿڸ��첻ͬ���յļ۸񼰲�ͬ�����ڴ˸ۿڲ�����ܵĵ��Ľ�Ǯ.
 *     4.��ҳ��н�Ǯ.
 *
 * ���ظ�������������.
 *     1:��Ҵ�������.
 *     2:��Ҹ��촬�յ�����.
 */


#define MAX_SHIP_NUM 20
#define MAX_CABIN_NUM 40

// ÿ�ִ��Ĵ�������.
extern int g_CabinNum[MAX_SHIP_NUM];

// ÿ�ִ��������յ�λ�ü���������.
extern int g_CabinPos[MAX_SHIP_NUM][MAX_CABIN_NUM][3];

#endif /*__UIREBUILDCABIN_H__*/
