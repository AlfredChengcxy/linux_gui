/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  app_frmotdrmessage.c
* ժ    Ҫ��  GUIMESSAGE����ϵͳ����ģ�飬guimessage.cʵ����GUI����Ϣ���͵����
*             ����������ʵ����Ϣ�ĵ���ģ�͡�
*
* ��ǰ�汾��  v1.0.0
* ��    �ߣ�  gyh
* ������ڣ�  2015-1-9
*
* ȡ���汾��  
* ԭ �� �ߣ� 
* ������ڣ�  
*******************************************************************************/

#include "wnd_msgqueue.h"


/************************
* appotdr�еĵ�ǰ�¼�����
*************************/
static OTDRMSGQUEUE *pWifiMsg = NULL;

/***
  * ���ܣ�
        ����ָ������Ϣֱ�Ӵ�����Ϣ����
  * ������
        1.int iQueueLimit:      ��Ҫ��������Ϣ�������Ϣ���е���󳤶�
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
OTDRMSGQUEUE *CreateOTDRMsgQueue(int iQueueLimit)
{
	int iErr = 0;
	OTDRMSGQUEUE *pOtdrQueue = NULL;

	if(iErr == 0)
	{
		pOtdrQueue = (OTDRMSGQUEUE *)malloc(sizeof(OTDRMSGQUEUE));
		if(NULL == pOtdrQueue)
		{
			iErr = -1;
		}
	}

	if(iErr == 0)
	{
		pOtdrQueue->queuesize = iQueueLimit;
		pOtdrQueue->head = 0;
		pOtdrQueue->tail = 0;
		pOtdrQueue->q = (int *)malloc(sizeof(int) * pOtdrQueue->queuesize);
		if(NULL == pOtdrQueue->q)
		{
			iErr = -2;
		}
	}
	
    if (iErr == 0)
    {
        //��ʼ��������
        if (InitMutex(&(pOtdrQueue->Mutex), NULL))
        {
            iErr = -3;
        }
    }
	
    //������
    switch (iErr)
    {
    case -3:
		free(pOtdrQueue->q);
    case -2:
        free(pOtdrQueue);
    case -1:
    default:
        break;
    }

	return pOtdrQueue;
}

//����0Ϊ�ǿգ����ط�0Ϊ��
int IsEmptyOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue)
{
	return ( pObjQueue->tail == pObjQueue->head );
}

//���ط�0Ϊ��
int IsFULLOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue)
{
	//printf("queuesize = %d head = %d, tail = %d\n", pObjQueue->queuesize, pObjQueue->head, pObjQueue->tail);
	return ( ((pObjQueue->tail+1) % pObjQueue->queuesize) == pObjQueue->head );
}

//��ն���
int ClearOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue)
{
	MutexLock(&(pObjQueue->Mutex));
	pObjQueue->head = pObjQueue->tail = 0;
	MutexUnlock(&(pObjQueue->Mutex));
	return 0;
}

void WriteOTDRMsgQueue(int key, OTDRMSGQUEUE *pObjQueue)
{
	int iErr = 0;
	int tail;
	if(NULL == pObjQueue)
	{
		iErr = -1;
	}

	if(!iErr)
	{
		if(!IsFULLOTDRMsgQueue(pObjQueue))
		{
			tail = (pObjQueue->tail+1)%pObjQueue->queuesize;
			pObjQueue->q[pObjQueue->tail] = key;
			pObjQueue->tail = tail;
			//printf("write head = %d, tail = %d\n", pObjQueue->head, pObjQueue->tail);
		}
		else
		{
			printf("OTDR MSG FULL\n");
		}
	}
}

void ReadOTDRMsgQueue(int *key, OTDRMSGQUEUE *pObjQueue)
{
	int iErr = 0;
	
	if(NULL == pObjQueue)
	{
		iErr = -1;
	}

	if(!iErr)
	{
		if(!IsEmptyOTDRMsgQueue(pObjQueue))
		{
			//printf("queuesize = %d head = %d, tail = %d\n", pObjQueue->queuesize, pObjQueue->head, pObjQueue->tail);
			*key = pObjQueue->q[pObjQueue->head];
			pObjQueue->head = (pObjQueue->head + 1) % pObjQueue->queuesize;
		}
		else
		{
			//LOG(LOG_ERROR, "OTDR MSG Empty\n");
		}
	}
}
/***************���ò�����������UI�������¼�����********************/
void InitWifiQueue(int iQueueLimit)
{
	pWifiMsg = CreateOTDRMsgQueue(iQueueLimit);
}

void SetWifiMsgQueue(OTDRMSGQUEUE *q)
{
	pWifiMsg = q;
}
OTDRMSGQUEUE * GetWifiMsgQueue(void)
{
	return pWifiMsg;
}
void ReadWifiMsgQueue(int *key)
{
	OTDRMSGQUEUE *pObjQueue = GetWifiMsgQueue();
	
	MutexLock(&(pObjQueue->Mutex));
	ReadOTDRMsgQueue(key, pObjQueue);
	MutexUnlock(&(pObjQueue->Mutex));
}
void WriteWifiMsgQueue(int key)
{
	OTDRMSGQUEUE *pObjQueue = GetWifiMsgQueue();
	
	MutexLock(&(pObjQueue->Mutex));
	WriteOTDRMsgQueue(key, pObjQueue);
	MutexUnlock(&(pObjQueue->Mutex));
}

