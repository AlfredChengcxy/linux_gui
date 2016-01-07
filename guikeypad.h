/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guikeypad.h
* ժ    Ҫ��  GUIKEYPADģ����Ҫ����豸����㶨�弰ʵ�֣��Ա�GUI�ܹ������ڲ�ͬ
*             Ӳ��ƽ̨��Ӧ�ò����Ӳ�����졣guikeypad.h������GUI�ļ���ӳ������
*             ��������ز���������ʵ��GUI��ͼ������豸����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_KEYPAD_H
#define _GUI_KEYPAD_H


/**************************************
* Ϊ����GUIKEYPAD����Ҫ���õ�����ͷ�ļ�
**************************************/
#include "guibase.h"


/*************
* �����������
*************/
#define GUIKEYPAD_TYP_STD       1   //��׼��������(PC����)
#define GUIKEYPAD_TYP_CUST      2   //�Զ����������


/******************
* ����GUI�м��̽ṹ
******************/
typedef struct _keypad
{
    int iDevFd;                 //�����豸�ļ�������
    int iDevType;               //�����豸���ͣ�1��ʾ��׼��2��ʾ�Զ���

    THREADFUNC fnKeypadThread;  //�ص����������ڴ��������߳�
    GUIMUTEX Mutex;             //�����������ڿ��Ƽ����̶߳Լ����豸�ķ���
} GUIKEYPAD;


/**********************************
* ����GUI�������������صĲ�������
**********************************/
//����ָ������Ϣ�������̶���
GUIKEYPAD* CreateKeypad(char *strDevName, int iDevType, 
                        THREADFUNC fnKeypadThread);
//ɾ�����̶���
int DestroyKeypad(GUIKEYPAD **ppKeypadObj);

//�õ���ǰ�ļ��̶���
GUIKEYPAD* GetCurrKeypad(void);
//���õ�ǰ�ļ��̶���
int SetCurrKeypad(GUIKEYPAD *pKeypadObj);


/***********************
* ����GUI��Ĭ�ϼ����߳�
***********************/
//Ĭ�ϼ����߳���ں���
void* DefaultKeypadThread(void *pThreadArg);

//��׼���ͼ���(PC����)�Ĵ�������������ɼ����̵߳Ĵ���
int StandardKeypadProcess(GUIKEYPAD *pKeypadObj);
//�Զ������ͼ��̵Ĵ�������������ɼ����̵߳Ĵ���
int CustomKeypadProcess(GUIKEYPAD *pKeypadObj);


#endif  //_GUI_KEYPAD_H

