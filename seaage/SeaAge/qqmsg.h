/*
 *    QQmsg.h
 *    
 *    show message in uiqq
 *
 *    Zhang Zhaohui, 2002/11/01.
 *    
 */

#pragma once

#include "ErrorMsg.h"


/***************************************
 *
 *
 *  Text for different version
 *
 *
 **************************************/

#ifdef  BIG5_VERSION

#define QQTXT_HIDE_LOGIN            "����"
#define QQTXT_HIDE_LOGIN_INFO       "~C0����~C0"
#define QQTXT_ONLINE_LOGIN          "�b�u"
#define QQTXT_ONLINE_LOGIN_INFO     "~C0�b�u~C0"
#define QQTXT_SYSSET                "�ѼƳ]�m"
#define QQTXT_SYSSET_INFO           "~C0�ѼƳ]�m~C0"
#define QQTXT_MESSAGE               "�t�ά���"
#define QQTXT_MESSAGE_INFO          "~C0�t�ά���~C0"
#define QQTXT_SEARCH                "�j��"
#define QQTXT_SEARCH_INFO           "~C0�j��~C0"
#define QQTXT_CALLGM                "�I�s�޲z��"
#define QQTXT_CALLGM_INFO           "~C0�I�s�޲z��~C0"
#define QQTXT_TIME_STR              "%d�~%d��%d�� %d:%d"
#define QQTXT_STRANGER_NAME         "���ͤH"
#define QQTXT_RECEIVE_ITEM          "  "

#define QQMB_TITLE_WARNING          "�`�N"
#define QQMB_TITLE_ERROR            "���~"
#define QQMB_TEXT_SEARCH1           "�п�ܤ@�Ӫ��a"
#define QQMB_TEXT_SEARCH2           "�п�J�ܤ֤@�ӷj������"
#define QQMB_TEXT_INPUT_EMPTY       "����o�e�Ů���"
#define QQMB_TEXT_CANOT_ADD_SELF    "�A����N�ۤv�[���n��"
#define QQMB_TEXT_ALREADY_ADDED     "�A�w�g�K�[�F�o�Ӧn��"
#define QQMB_TEXT_DEL_FRIEND        "�T�w�n�N��%s���R���\�H"

#define QQERR_SUCCESS               "���\������n�ͪ��ާ@"
#define QQERR_QF_ALREADY_ADDED      "�A�w�g�K�[�F�o�Ӧn��"
#define QQERR_QF_MAX_COUNT          "�A���n�ͤw�g��F�̤j�ơA����A�~��K�[�F"
#define QQERR_NO_ENOUGH_MEM         "�S���������O����ӧ�����n�ͪ��ާ@"
#define QQERR_SEND_ITEM_FAILED      "�ǰe���~����"

#endif  /* BIG5_VERSION */

#ifdef GB_VERSION

#define QQTXT_HIDE_LOGIN            "����"
#define QQTXT_HIDE_LOGIN_INFO       "~C0����~C0"
#define QQTXT_ONLINE_LOGIN          "����"
#define QQTXT_ONLINE_LOGIN_INFO     "~C0����~C0"
#define QQTXT_SYSSET                "��������"
#define QQTXT_SYSSET_INFO           "~C0��������~C0"
#define QQTXT_MESSAGE               "ϵͳ��¼"
#define QQTXT_MESSAGE_INFO          "~C0ϵͳ��¼~C0"
#define QQTXT_SEARCH                "����"
#define QQTXT_SEARCH_INFO           "~C0����~C0"
#define QQTXT_CALLGM                "���й���Ա"
#define QQTXT_CALLGM_INFO           "~C0���й���Ա~C0"
#define QQTXT_TIME_STR              "%d��%d��%d�� %d:%d"
#define QQTXT_STRANGER_NAME         "İ����"
#define QQTXT_RECEIVE_ITEM          "  "

#define QQMB_TITLE_WARNING          "ע��"
#define QQMB_TITLE_ERROR            "����"
#define QQMB_TEXT_SEARCH1           "��ѡ��һ�����"
#define QQMB_TEXT_SEARCH2           "����������һ����������"
#define QQMB_TEXT_INPUT_EMPTY       "���ܷ��Ϳ���Ϣ"
#define QQMB_TEXT_CANOT_ADD_SELF    "���ܽ��Լ���Ϊ����"
#define QQMB_TEXT_ALREADY_ADDED     "���Ѿ������˼�Ϊ����"
#define QQMB_TEXT_DEL_FRIEND        "ȷ��Ҫ����%s��ɾ��ô��"

#define QQERR_SUCCESS               "�ɹ���ɶԺ��ѵĲ���"
#define QQERR_QF_ALREADY_ADDED      "���Ѿ�������������"
#define QQERR_QF_MAX_COUNT          "��ĺ����Ѿ�����������������ټ��������"
#define QQERR_NO_ENOUGH_MEM         "û���㹻���ڴ�����ɶԺ��ѵĲ���"
#define QQERR_SEND_ITEM_FAILED      "������Ʒʧ��"
#endif  /* GB_VERSION */


