/*******************************************************************************
* Copyright(c)2012，一诺仪器(威海)有限公司上海研发部
*
* All rights reserved
*
* 文件名称：  app_frmotdrmessage.c
* 摘    要：  GUIMESSAGE属于系统调用模块，guimessage.c实现了GUI的消息类型的相关
*             操作，用于实现消息的调度模型。
*
* 当前版本：  v1.0.0
* 作    者：  gyh
* 完成日期：  2015-1-9
*
* 取代版本：  
* 原 作 者： 
* 完成日期：  
*******************************************************************************/

#include "wnd_msgqueue.h"


/************************
* appotdr中的当前事件对象
*************************/
static OTDRMSGQUEUE *pWifiMsg = NULL;

/***
  * 功能：
        根据指定的信息直接创建消息对象
  * 参数：
        1.int iQueueLimit:      需要创建的消息对象的消息队列的最大长度
  * 返回：
        成功返回有效指针，失败返回NULL
  * 备注：
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
        //初始化互斥锁
        if (InitMutex(&(pOtdrQueue->Mutex), NULL))
        {
            iErr = -3;
        }
    }
	
    //错误处理
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

//返回0为非空，返回非0为空
int IsEmptyOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue)
{
	return ( pObjQueue->tail == pObjQueue->head );
}

//返回非0为满
int IsFULLOTDRMsgQueue(OTDRMSGQUEUE *pObjQueue)
{
	//printf("queuesize = %d head = %d, tail = %d\n", pObjQueue->queuesize, pObjQueue->head, pObjQueue->tail);
	return ( ((pObjQueue->tail+1) % pObjQueue->queuesize) == pObjQueue->head );
}

//清空队列
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
/***************设置测量过程中与UI交互的事件队列********************/
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

