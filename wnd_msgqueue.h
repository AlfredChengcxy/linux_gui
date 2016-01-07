/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  app_frmotdrmessage.h
* ժ    Ҫ��  GUIMESSAGE����ϵͳ����ģ�飬�˲��ֶ���GUI����Ϣ���ͼ�������ز�
*             ��������ʵ����Ϣ�ĵ���ģ�͡�
*
* ��ǰ�汾��  v1.0.0
* ��    �ߣ�  gyh
* ������ڣ�  2015-1-9
*
* ȡ���汾��
* ԭ �� �ߣ�
* ������ڣ�
*******************************************************************************/

#ifndef _APP_FRMOTDRMESSAGE_H
#define _APP_FRMOTDRMESSAGE_H

#include "guiglobal.h"

/**************************************************
* ����appotdr����Ϣ�������ܰ�����Ϣ���������
**************************************************/
#define OTDRMESSAGE_ITEM_LIMIT       100			//������Ϣ�������ɰ�������Ϣ��

typedef struct _otdr_msg_queue
{
	int queuesize;
	int head, tail;
	int *q;
	
    GUIMUTEX Mutex;         //������������ͬ����־����Ϣ���м�ע����Ϣ�ķ���
}OTDRMSGQUEUE, *POTDRMSGQUEUE;

OTDRMSGQUEUE *CreateOTDRMsgQueue(int iQueueLimit);

//����0Ϊ�ǿգ����ط�0Ϊ��
int IsEmptyOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue);

//���ط�0Ϊ��
int IsFULLOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue);
int ClearOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue);
void WriteOTDRMsgQueue(int key, OTDRMSGQUEUE *pObjQueue);
void ReadOTDRMsgQueue(int *key, OTDRMSGQUEUE *pObjQueue);

void InitWifiQueue(int iQueueLimit);
void SetWifiMsgQueue(OTDRMSGQUEUE *q);
OTDRMSGQUEUE * GetWifiMsgQueue(void);
void ReadWifiMsgQueue(int *key);
void WriteWifiMsgQueue(int key);

#endif
