/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guimessage.c
* ժ    Ҫ��  GUIMESSAGE����ϵͳ����ģ�飬guimessage.cʵ����GUI����Ϣ���͵����
*             ����������ʵ����Ϣ�ĵ���ģ�͡�
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guimessage.h"


/***************************************
* Ϊʵ��GUIMESSAGE����Ҫ���õ�����ͷ�ļ�
***************************************/
//#include ""


/********************
* GUI�еĵ�ǰ��Ϣ����
********************/
static GUIMESSAGE *pCurrMessage = NULL;


/***
  * ���ܣ�
        ����ָ������Ϣֱ�Ӵ�����Ϣ����
  * ������
        1.int iQueueLimit:      ��Ҫ��������Ϣ�������Ϣ���е���󳤶�
        2.int iRegLimit:        ��Ҫ��������Ϣ�������Ϣע����е���󳤶�
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIMESSAGE* CreateMessage(int iQueueLimit, int iRegLimit)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIMESSAGE *pMsgObj = NULL;

    if (!iErr)
    {
        //���Է����ڴ�
        pMsgObj = (GUIMESSAGE *) malloc(sizeof(GUIMESSAGE));
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //������Ϣ�������Ϣ����
        pMsgObj->pMsgQueue = CreateList(iQueueLimit);
        if (NULL == pMsgObj->pMsgQueue)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //������Ϣ�������Ϣע�����
        pMsgObj->pMsgReg = CreateList(iRegLimit);
        if (NULL == pMsgObj->pMsgReg)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //��ʼ��������
        if (InitMutex(&(pMsgObj->Mutex), NULL))
        {
            iErr = -4;
        }
    }

    //������
    switch (iErr)
    {
    case -4:
        DestroyList(pMsgObj->pMsgReg);
        //no break
    case -3:
        DestroyList(pMsgObj->pMsgQueue);
        //no break
    case -2:
        free(pMsgObj);
        //no break
    case -1:
        pMsgObj = NULL;
        //no break
    default:
        break;
    }

    return pMsgObj;
}


/***
  * ���ܣ�
        ɾ����Ϣ����
  * ������
        1.GUIMESSAGE **ppMsgObj:    ָ���ָ�룬ָ����Ҫ���ٵ���Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyMessage(GUIMESSAGE **ppMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppMsgObj)
        {
            iErr = -1; 
        }
    }

    if (!iErr)
    {
        //�ж�ppMsgObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppMsgObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //������Ϣ�������Ϣ����
        if (DestroyList((*ppMsgObj)->pMsgQueue))
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //������Ϣ�������Ϣע�����
        if (DestroyList((*ppMsgObj)->pMsgReg))
        {
            iErr = -4;
        }
    }

    if (!iErr)
    {
        //������Ϣ���󣬲���ָ���ÿ�
        free(*ppMsgObj);
        *ppMsgObj = NULL;
    }

    return iErr;
}


/***
  * ���ܣ�
        �õ���ǰ��Ϣ����
  * ������
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIMESSAGE* GetCurrMessage(void)
{
    return pCurrMessage;
}


/***
  * ���ܣ�
        ����Ϊ��ǰ��Ϣ����
  * ������
        1.GUIMESSAGE *pEventObj:    ������Ϊ��ǰ��Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetCurrMessage(GUIMESSAGE *pMsgObj)
{
    //�ж�pEventObj�Ƿ���Ч
    if (NULL == pMsgObj)
    {
        return -1;
    }

    pCurrMessage = pMsgObj;

    return 0;
}


/***
  * ���ܣ�
        ��ָ����Ϣ�����н���һ���ض����͵���Ϣ��
  * ������
        1.int iMsgType:         ��Ҫ���յ���Ϣ������
        2.GUIMESSAGE *pMsgObj:  ָ������Ϣ����
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
GUIMESSAGE_ITEM* RecvSpecialMessage(int iMsgType, GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIMESSAGE_ITEM *pReturn = NULL;
    //��ʱ��������
    int iPos;
    GUILIST_ITEM *pItem = NULL;
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж���Ϣ�����Ƿ���Чָ�����Ϣ�����Ƿ�Ϊ��
        if ((NULL == pMsgObj->pMsgQueue) || 
            ListEmpty(pMsgObj->pMsgQueue))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //������Ϣ�����ҵ�����ƥ�����Ϣ��
        list_next_each(pItem, pMsgObj->pMsgQueue, iPos)
        {
            pPkt = container_of(pItem, GUIOBJ, List);
            pReturn = (GUIMESSAGE_ITEM *) (pPkt->pObj);

            if (pReturn->iMsgType == iMsgType)
            {
                //�ҵ�����ƥ�����Ϣ������Ϣ������ɾ��
                if (ListDel(pItem, pMsgObj->pMsgQueue))
                {
                    iErr = -3;
                }
                break;
            }
        }

        //���û���ҵ�����ƥ�����Ϣ��
        if (-1 == iPos)
        {
            iErr = -4;
        }
    }

    if (!iErr)
    {
        //�ͷ���Դ
        free(pPkt);    
    }

    //������
    switch (iErr)
    {
    case -4:
    case -3:
        pReturn = NULL;
        //no break
    case -2:
    case -1:
    default:
        break;
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return pReturn;
}


/***
  * ���ܣ�
        ��ָ����Ϣ��������������ض����͵���Ϣ��
  * ������
        1.int iMsgType:         ��Ҫ�������Ϣ������
        2.GUIMESSAGE *pMsgObj:  ָ������Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int ClearSpecialMessage(int iMsgType, GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    int iPos;
    GUILIST_ITEM *pItem = NULL;
    GUIOBJ *pPkt = NULL;
    GUIMESSAGE_ITEM *pMsg = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж���Ϣ�����Ƿ���Чָ�����Ϣ�����Ƿ�Ϊ��
        if ((NULL == pMsgObj->pMsgQueue) ||
            ListEmpty(pMsgObj->pMsgQueue))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //������Ϣ�����ҵ�����ƥ�����Ϣ��
        list_next_each(pItem, pMsgObj->pMsgQueue, iPos)
        {
            pPkt = container_of(pItem, GUIOBJ, List);
            pMsg = (GUIMESSAGE_ITEM *) (pPkt->pObj);

            if (pMsg->iMsgType == iMsgType)
            {
                //ɾ���������޸��б���ṹ����������ƶ�pItem
                pItem = pItem->pPrev;
                //�ҵ�����ƥ�����Ϣ������Ϣ������ɾ��
                if (ListDel(pItem->pNext, pMsgObj->pMsgQueue))
                {
                    iErr = -3;
                    break;
                }

                //�ͷ���Դ
                free(pMsg);
                free(pPkt);

                //list_next_each����iPos����ѭ�����ƣ���ɾ�����������iPos����
                iPos--;
                //�ж��Ƿ��ѱ������
                if (-1 == iPos)
                {
                    break;
                }
            }
        }
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        ����ָ����Ϣ�����ж���ͷ������Ϣ��
  * ������
        1.GUIMESSAGE *pMsgObj:  ӵ������¼����е��¼�����
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
GUIMESSAGE_ITEM* ReadMessageQueue(GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIMESSAGE_ITEM *pReturn = NULL;
    //��ʱ��������
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж���Ϣ�����Ƿ�Ϊ��Чָ�����Ϣ�����Ƿ�Ϊ��
        if ((NULL == pMsgObj->pMsgQueue) || 
            ListEmpty(pMsgObj->pMsgQueue))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //ͨ��pMsgObj��GUILIST_ITEM��Ա���pPkt�ĵ�ַ
        pPkt = container_of(pMsgObj->pMsgQueue->pHead, GUIOBJ, List);
        pReturn = (GUIMESSAGE_ITEM *) (pPkt->pObj);
        //����Ϣ������ɾ��ͷ�б���
        if (ListDel(pMsgObj->pMsgQueue->pHead, pMsgObj->pMsgQueue))
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //�ͷ���Դ
        free(pPkt);
    }

    //������
    switch (iErr)
    {
    case -3:
        pReturn = NULL;
        //no break
    case -2:
    case -1:
    default:
        break;
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return pReturn;
}


/***
  * ���ܣ�
        д����Ϣ�ָ����Ϣ����Ķ���β��
  * ������
        1.GUIMESSAGE_ITEM *pMsgItem:    ��Ҫ��д����Ϣ�����е���Ϣ��
        2.GUIMESSAGE *pMsgObj:          ָ������Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int WriteMessageQueue(GUIMESSAGE_ITEM *pMsgItem, GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgItem��pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgItem || NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�pMsgQueue�Ƿ�Ϊ��Чָ�����Ϣ�����Ƿ�����
        if ((NULL == pMsgObj->pMsgQueue) || 
            ListFull(pMsgObj->pMsgQueue))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //�����ڴ�
        pPkt = (GUIOBJ *) malloc(sizeof(GUIOBJ));
        if (NULL == pPkt)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //�����Ϣ���Ϣ����
        pPkt->pObj = pMsgItem;
        if (ListAdd(&(pPkt->List), pMsgObj->pMsgQueue))
        {
            iErr = -4;
        }
    }

    //������
    switch (iErr)
    {
    case -4:
        free(pPkt);
        //no break
    case -3:
    case -2:
    case -1:
    default:
        break;
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �����Ϣ����
  * ������
        1.GUIMESSAGE *pMsgObj:      ��Ҫ�������Ϣ���е���Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int ClearMessageQueue(GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIOBJ *pPkt = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж��¼�����pMsgQueue�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj->pMsgQueue)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����ɾ����Ϣ������
        while (pMsgObj->pMsgQueue->iCount)
        {
            pPkt= container_of(pMsgObj->pMsgQueue->pHead, GUIOBJ, List);
            pItem = (GUIMESSAGE_ITEM *) (pPkt->pObj);

            if (ListDel(pMsgObj->pMsgQueue->pHead, pMsgObj->pMsgQueue))
            {
                iErr = -3;
                break;
            }

            //�ͷ���Դ
            free(pItem);
            free(pPkt);
        }
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        ע����Ϣע���ָ����Ϣ����
  * ������
        1.int iMsgCode:         ��Ϣע�������Ϣ����
        2.void *pRecvObj:       ��Ϣע�������Ϣ���ն���
        3.MSGFUNC fnMsgFunc:    ��Ϣע����Ĵ�����Ϣ�ĺ���
        4.void *pOutArg:        ��Ϣע�������Ϣ�������Ĵ�������
        5.int iOutLength:       ��Ϣע����Ĵ��������ĳ���
        6.GUIMESSAGE *pMsgObj:  ӵ����Ϣע����е���Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        1.�������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
        2.��ע����Ϣע����ʱ������Ϣ�������Ϣ���ն������ָ���Ϣע��������
        ע��ʱ�������ȶ���Ϣע������б�����������������ͬ����Ϣע�����Ϣ��
        �뼰��Ϣ���ն����ֵ��ͬ�����ú���������
***/
int LoginMessageReg(int iMsgCode, void *pRecvObj, 
                    MSGFUNC fnMsgFunc, void *pOutArg, int iOutLength, 
                    GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    int iPos;
    GUILIST_ITEM *pItem = NULL;
    GUIOBJ *pPkt = NULL;
    GUIMESSAGE_REG *pReg = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�pMsgReg�Ƿ�Ϊ��Чָ�����Ϣ�����Ƿ�����
        if ((NULL == pMsgObj->pMsgReg) || 
            ListFull(pMsgObj->pMsgReg))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //�����б�
        list_next_each(pItem, pMsgObj->pMsgReg, iPos)
        {
            pPkt = container_of(pItem, GUIOBJ, List);
            pReg = (GUIMESSAGE_REG *) (pPkt->pObj);

            //�ж��Ƿ�������ͬ����Ϣע����
            if ((pReg->iMsgCode == iMsgCode) &&
                (pReg->pRecvObj == pRecvObj))
            {
                iErr = -3;
                break;
            }
        }
    }

    if (!iErr)
    {
        //ΪpReg�����ڴ�
        pReg = (GUIMESSAGE_REG *) malloc(sizeof(GUIMESSAGE_REG));
        if (NULL == pReg)
        {
            iErr = -4;
        }
    }

    if (!iErr)
    {
        //ΪpMsg�����ڴ�
        pPkt = (GUIOBJ *) malloc(sizeof(GUIOBJ));
        if (NULL == pPkt)
        {
            iErr = -5;
        }
    }

    if (!iErr)
    {
        //������Ϣע����ĳ�Ա����
        pReg->iMsgCode = iMsgCode;
        pReg->pRecvObj = pRecvObj;
        pReg->fnMsgFunc = fnMsgFunc;
        pReg->pOutArg = pOutArg;
        pReg->iOutLength = iOutLength;
        //�����Ϣע�����Ϣע�����
        pPkt->pObj = pReg;
        if (ListAdd(&(pPkt->List), pMsgObj->pMsgReg))
        {
            iErr = -6;
        }
    }

    //������
    switch (iErr)
    {
    case -6:
        free(pPkt);
        //no break
    case -5:
        free(pReg);
        //no break
    case -4:
    case -3:
    case -2:
    case -1:
    default:
        break;
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        ��ָ����Ϣ����ע����Ϣע����
  * ������
        1.int iMsgCode:         ��Ҫע������Ϣע�������Ϣ����
        2.void *pRecvObj:       ��Ҫע������Ϣע�������Ϣ���ն���
        3.GUIMESSAGE *pMsgObj:  ӵ����ע����Ϣע����е��¼�����
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int LogoutMessageReg(int iMsgCode, void *pRecvObj, GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    int iPos;
    GUILIST_ITEM *pItem = NULL;
    GUIOBJ *pPkt = NULL;
    GUIMESSAGE_REG *pReg = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж���Ϣע������Ƿ�����Чָ�����Ϣע������Ƿ�Ϊ��
        if ((NULL == pMsgObj->pMsgReg) || 
            ListEmpty(pMsgObj->pMsgReg))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //�����б�
        list_next_each(pItem, pMsgObj->pMsgReg, iPos)
        {
            pPkt = container_of(pItem, GUIOBJ, List);
            pReg = (GUIMESSAGE_REG *) (pPkt->pObj);

            //���¼�������ɾ����Ϣע����
            if ((pReg->iMsgCode == iMsgCode) && 
                (pReg->pRecvObj == pRecvObj))
            {
                if (ListDel(pItem, pMsgObj->pMsgReg))
                {
                    iErr = -3;
                }
                break;
            }
        }

        //û���ҵ�ƥ�����Ϣע����
        if (-1 == iPos)
        {
            iErr = -4;
        }
    }

    //�ͷ���Դ
    if (!iErr)
    {
        free(pReg);
        free(pPkt);
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �����Ϣע����Ϣ
  * ������
        1.GUIMESSAGE *pMsgObj:      ��Ҫ�������Ϣע����е���Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int ClearMessageReg(GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIOBJ *pPkt = NULL;
    GUIMESSAGE_REG *pItem = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж���Ϣ����pMsgReg�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgObj->pMsgReg)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����ɾ����Ϣע�������
        while (pMsgObj->pMsgReg->iCount)
        {
            pPkt= container_of(pMsgObj->pMsgReg->pHead, GUIOBJ, List);
            pItem = (GUIMESSAGE_REG *) (pPkt->pObj);

            if (ListDel(pMsgObj->pMsgReg->pHead, pMsgObj->pMsgReg))
            {
                iErr = -3;
                break;
            }

            //�ͷ���Դ
            free(pItem);
            free(pPkt);
        }
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
       ��ָ����Ϣ������ƥ������Ϣ���Ӧ����Ϣע����
  * ������
        1.GUIMESSAGE_ITEM *pMsgItem:    ��ƥ�����Ϣ������
        2.GUIMESSAGE *pMsgObj:          ��ƥ�����Ϣ����
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ��ؿ�ָ��
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
GUIMESSAGE_REG* MatchMessageReg(GUIMESSAGE_ITEM *pMsgItem, 
                                GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIMESSAGE_REG *pReturn = NULL;
    //��ʱ��������
    int iPos;
    GUILIST_ITEM *pItem = NULL;
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pMsgObj->Mutex));

    if (!iErr)
    {
        //�ж�pMsgItem��pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgItem || NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�pMsgReg�Ƿ�Ϊ��Чָ����Ƿ�Ϊ��
        if ((NULL == pMsgObj->pMsgReg) || 
            ListEmpty(pMsgObj->pMsgReg))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //������Ϣע�����
        list_next_each(pItem, pMsgObj->pMsgReg, iPos)
        {
            pPkt = container_of(pItem, GUIOBJ, List);
            pReturn = (GUIMESSAGE_REG *) (pPkt->pObj);

            if ((pReturn->iMsgCode == pMsgItem->iMsgCode) &&
                (pReturn->pRecvObj == pMsgItem->pRecvObj))
            {
                break;
            }
        }

        //û���ҵ�ƥ�����Ϣע����
        if (-1 == iPos)
        {
            iErr = -3;
        }
    }

    //������
    switch (iErr)
    {
    case -3:
        pReturn = NULL;
        //no break
    case -2:
    case -1:
    default:
        break;
    }

    //����
    MutexUnlock(&(pMsgObj->Mutex));

    return pReturn;
}


/***
  * ���ܣ�
       ��ָ����Ϣ������ƥ����Ϣ��ִ�ж�Ӧ����Ϣ������
  * ������
        1.GUIMESSAGE_ITEM *pMsgItem:    ����ƥ����Ϣע�������Ϣ��
        2.GUIMESSAGE *pMsgObj:          ָ������Ϣ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �����ڳ���������Ϣ�����еĻ���������ǰ���µ��ã�����ᵼ������
***/
int ExecMessageProc(GUIMESSAGE_ITEM *pMsgItem, GUIMESSAGE *pMsgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIMESSAGE_REG *pReg = NULL;

    if (!iErr)
    {
        //�ж�pMsgItem��pMsgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pMsgItem || NULL == pMsgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //������Ϣ����ƥ����Ϣע����
        pReg = MatchMessageReg(pMsgItem, pMsgObj);
        if (NULL == pReg)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //ִ��ƥ�䵽����Ϣע�����еĴ�����
        if (pReg->fnMsgFunc((void *)(pMsgItem->uiMsgValue), 
                            pMsgItem->iValueLength, 
                            pReg->pOutArg, 
                            pReg->iOutLength))
        {
            iErr = -3;
        }
    }

    return iErr;
}

