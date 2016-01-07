/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guitouch.h
* ժ    Ҫ��  GUITOUCHģ����Ҫ����豸����㶨�弰ʵ�֣��Ա�GUI�ܹ������ڲ�ͬӲ
*             ��ƽ̨��Ӧ�ò����Ӳ�����졣guitouch.h������GUI�Ĵ�����ӳ�����ͼ�
*             ������ز���������ʵ��GUI�Ĵ����������豸����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_TOUCH_H
#define _GUI_TOUCH_H


/*************************************
* Ϊ����GUITOUCH����Ҫ���õ�����ͷ�ļ�
*************************************/
#include "guibase.h"


/********************
* ����GUI�д���������
********************/
#define GUITOUCH_TYP_STD        1   //��׼���ʹ�����(PC���)
#define GUITOUCH_TYP_CUST       2   //�Զ������ʹ�����


/********************
* ����GUI�д������ṹ
********************/
typedef struct _touch
{
    int iDevFd;                 //�������豸�ļ�������
    int iDevType;               //�������豸���ͣ�1��ʾ��׼��2��ʾ�Զ���

    unsigned int uiHorRes;      //������ˮƽ�ֱ��ʣ�0~0xFFFF
    unsigned int uiVerRes;      //��������ֱ�ֱ��ʣ�0~0xFFFF
    unsigned int uiCursX;       //��������굱ǰ������ֵ��0~0xFFFF
    unsigned int uiCursY;       //��������굱ǰ������ֵ��0~0xFFFF

    THREADFUNC fnTouchThread;   //�ص����������ڴ����������߳�
    GUIMUTEX Mutex;             //�����������ڿ��ƴ������̶߳Դ������豸�ķ���
} GUITOUCH;


/************************************
* ����GUI���봥����������صĲ�������
************************************/
//����ָ������Ϣ��������������
GUITOUCH* CreateTouch(char *strDevName, int iDevType, 
                      unsigned int uiHorRes, unsigned int uiVerRes,
                      THREADFUNC fnTouchThread);
//ɾ������������
int DestroyTouch(GUITOUCH **ppTouchObj);

//�õ���ǰ�Ĵ���������
GUITOUCH* GetCurrTouch(void);
//���õ�ǰ�Ĵ���������
int SetCurrTouch(GUITOUCH *pTouchObj);

//���ô������Ĺ��λ��
int SetTouchCursor(unsigned int uiCursX, unsigned int uiCursY,
                   GUITOUCH *pTouchObj);


/***********************
����GUI��Ĭ�ϴ������߳�
***********************/
//Ĭ�ϴ������߳���ں���
void* DefaultTouchThread(void *pThreadArg);

//��׼���ʹ�����(PC���)�Ĵ�������������ɴ������̵߳Ĵ���
int StandardTouchProcess(GUITOUCH *pTouchObj);
//�Զ������ʹ������Ĵ�������������ɴ������̵߳Ĵ���
int CustomTouchProcess(GUITOUCH *pTouchObj);


#endif  //_GUI_TOUCH_H

