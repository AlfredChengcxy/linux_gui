/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guiwindow.c
* ժ    Ҫ��  ʵ��GUI�Ĵ������ͼ�������ΪGUI������Ȼ����ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guiwindow.h"


/**************************************
* Ϊʵ��GUIWINDOW����Ҫ���õ�����ͷ�ļ�
**************************************/
//#include ""


/******************************
* GUI�еĵ�ǰ��������以����
******************************/
//GUI�еĵ�ǰ�������
static GUIWINDOW *pCurrWindow = NULL;
//���ڿ��Ʒ��ʵ�ǰ�������Ļ�����
static GUIMUTEX mutexWndLock;


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӽ����������
  * ������
        1.unsigned int uiPlaceX:    ����ˮƽ����λ�ã������Ͻ�Ϊ����
        2.unsigned int uiPlaceY:    ���崹ֱ����λ�ã������Ͻ�Ϊ����
        3.unsigned int uiEndX:      ����ˮƽ���
        4.unsigned int uiEndY:      ���崹ֱ�߶�
        5.WNDFUNC fnWndInit:        ָ�����ʼ��������������ɴ���ĳ�ʼ��
        6.WNDFUNC fnWndExit:        ָ�����˳�������������ɴ�����˳�
        7.WNDFUNC fnWndPaint:       ָ������ƺ�����������ɴ���Ļ���
        8.WNDFUNC fnWndLoop:        ָ����ѭ��������Ϊ���򲻽���ѭ������
        9.WNDFUNC fnWndPause:       ָ�����������Ϊ���򲻽��й���ǰԤ����
        10.WNDFUNC fnWndResume:     ָ����ָ�������Ϊ���򲻽��лָ�ǰԤ����
        11.THREADFUNC fnWndThread:  �������崦���̣߳�Ϊ��ʹ��ϵͳ�Ĵ��崦���߳�
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIWINDOW* CreateWindow(unsigned int uiPlaceX, unsigned int uiPlaceY, 
                        unsigned int uiWndWidth, unsigned int uiWndHeight, 
                        WNDFUNC fnWndInit, WNDFUNC fnWndExit, 
                        WNDFUNC fnWndPaint, WNDFUNC fnWndLoop, 
                        WNDFUNC fnWndPause, WNDFUNC fnWndResume,
                        THREADFUNC fnWndThread)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIWINDOW *pWndObj = NULL;

    if (!iErr)
    {
        //�ж�uiWndWidth��uiWndHeight�Ƿ���Ч
        if (uiWndWidth < 1 || uiWndHeight < 1)
        {
            iErr = -1;
        }
        //�ж�fnWndInit��fnWndExit��fnWndPaint�Ƿ�Ϊ��Чָ��
        if (NULL == fnWndInit || NULL == fnWndExit || NULL == fnWndPaint)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�����ڴ���Դ
        pWndObj = (GUIWINDOW *) malloc(sizeof(GUIWINDOW));
        if (NULL == pWndObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //��������Ŀؼ�����
        pWndObj->pWndComps = CreateList(GUIWINDOW_COMP_LIMIT);
        if (NULL == pWndObj->pWndComps)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //��ʼ��������
        if (InitMutex(&(pWndObj->Mutex), NULL))
        {
            iErr = -4;
        }
    }

    if (!iErr)
    {
        //������������Ϣ��ֵ
        pWndObj->Visible.Area.Start.x = uiPlaceX;
        pWndObj->Visible.Area.Start.y = uiPlaceY;
        pWndObj->Visible.Area.End.x = uiPlaceX + uiWndWidth - 1;
        pWndObj->Visible.Area.End.y = uiPlaceY + uiWndHeight - 1;
        pWndObj->Visible.iEnable = 1;   //Ĭ�Ͽɼ�
        pWndObj->Visible.iLayer = 0;    //Ĭ��ͼ��Ϊ0(��ײ�)
        pWndObj->Visible.iFocus = 0;    //Ĭ���޽���
        pWndObj->Visible.iCursor = 0;   //Ĭ���޹��
        memset(&(pWndObj->Visible.Hide), 0, sizeof(GUIRECTANGLE));
        pWndObj->Visible.pResume = NULL;
        pWndObj->Visible.fnDestroy = (DESTFUNC) DestroyWindow;
        pWndObj->Visible.fnDisplay = (DISPFUNC) fnWndPaint;
        //���ô������Ĵ��崦����
        pWndObj->fnWndInit = fnWndInit;
        pWndObj->fnWndExit = fnWndExit;
        pWndObj->fnWndPaint = fnWndPaint;
        pWndObj->fnWndLoop = fnWndLoop;
        pWndObj->fnWndPause = fnWndPause;
        pWndObj->fnWndResume = fnWndResume;
        //���ô�������Ӧ���̺߳������߳�ID
        pWndObj->fnWndThread = fnWndThread;
        pWndObj->thdWndTid = -1;        //Ĭ����Ч
        //�������Ļ�ˢ�����ʼ���������
        pWndObj->pWndPen = NULL;        //Ĭ��ʹ�õ�ǰ����
        pWndObj->pWndBrush = NULL;      //Ĭ��ʹ�õ�ǰ��ˢ
        pWndObj->pWndFont = NULL;       //Ĭ��ʹ�õ�ǰ����
    }

    //������
    switch (iErr)
    {
    case -4:
        DestroyList(pWndObj->pWndComps);
        //no break
    case -3:
        free(pWndObj);
        //no break
    case -2:
    case -1:
        pWndObj = NULL;
        //no break
    default:
        break;
    }

    return pWndObj;
}


/***
  * ���ܣ�
        ɾ���������
  * ������
        1.GUIWINDOW **ppWndObj: ָ���ָ�룬ָ����Ҫ���ٵĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyWindow(GUIWINDOW **ppWndObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppWndObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppWndObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppWndObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppWndObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����ؼ������Ѱ�����GUI����ؼ����󣬳������ٿؼ�����
        if (NULL != (*ppWndObj)->pWndComps)
        {
            if (DestroyList((*ppWndObj)->pWndComps))
            {
                iErr = -4;
            }
        }
    }

    if (!iErr)
    {
        //���ٴ�����󣬲���ָ���ÿ�
        free(*ppWndObj);
        *ppWndObj = NULL;
    }

    return iErr;
}


/***
  * ���ܣ�
        ��ʼ����ǰ����
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        Ĭ�Ͻ���ǰ�����ʼ��ΪNULL
***/
int InitCurrWindow(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    if (InitMutex(&mutexWndLock, NULL))
    {
        iReturn = -1;
    }
    else 
    {
        MutexLock(&mutexWndLock);   
        pCurrWindow = NULL;
        MutexUnlock(&mutexWndLock);
    }

    return iReturn;
}


/***
  * ���ܣ�
        ��ס��ǰ�������
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �����߳����л�ָ���Ӧ��һʱ����øú�������֤ʼ��ֻ��һ�������
***/
int LockCurrWindow(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = MutexLock(&mutexWndLock);

    return iReturn;
}


/***
  * ���ܣ�
        ������ǰ�������
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �����߳��˳������ǰ��������øú�������ʹ���������̵߳�������
***/
int UnlockCurrWindow(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = MutexUnlock(&mutexWndLock);

    return iReturn;
}


/***
  * ���ܣ�
        ���ֵ�ǰ�Ĵ�����󲻱䣬��Ҫ��UnlockCurrWindow()�ɶ�ʹ��
  * ������
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIWINDOW* HoldCurrWindow(void)
{
    //�����־������ֵ����
    GUIWINDOW *pReturn = NULL;

    MutexLock(&mutexWndLock);
    pReturn = pCurrWindow;

    return pReturn;
}


/***
  * ���ܣ�
        �õ���ǰ�Ĵ������
  * ������
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIWINDOW* GetCurrWindow(void)
{
    //�����־������ֵ����
    GUIWINDOW *pReturn = NULL;

    MutexLock(&mutexWndLock);
    pReturn = pCurrWindow;
    MutexUnlock(&mutexWndLock);

    return pReturn;
}


/***
  * ���ܣ�
        ���õ�ǰ�Ĵ������
  * ������
        1.GUIWINDOW *pWndObj:   ������Ϊ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetCurrWindow(GUIWINDOW *pWndObj)
{
    //�ж�pWndObj�Ƿ���Ч
    if (NULL == pWndObj)
    {
        return -1;
    }

    MutexLock(&mutexWndLock);   
    pCurrWindow = pWndObj;
    MutexUnlock(&mutexWndLock);

    return 0;
}


/***
  * ���ܣ�
        ���ô������Ч����
  * ������
        1.unsigned int uiStartX:    ������Ч�������ϽǺ����꣬�����Ͻ�Ϊ����
        2.unsigned int uiStartY:    ������Ч�������Ͻ������꣬�����Ͻ�Ϊ����
        3.unsigned int uiEndX:      ������Ч�������½Ǻ����꣬�����Ͻ�Ϊ����
        4.unsigned int uiEndY:      ������Ч�������½������꣬�����Ͻ�Ϊ����
        5.GUIWINDOW *pWndObj:       ��Ҫ������Ч����Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetWindowArea(unsigned int uiStartX, unsigned int uiStartY, 
                  unsigned int uiEndX, unsigned int uiEndY,
                  GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�uiEndX��uiEndY�Ƿ���Ч
        if (uiEndX < uiStartX || uiEndY < uiStartY)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //���������Ч����ֵ
        pWndObj->Visible.Area.Start.x = uiStartX;
        pWndObj->Visible.Area.Start.y = uiStartY;
        pWndObj->Visible.Area.End.x = uiEndX;
        pWndObj->Visible.Area.End.y = uiEndY;
        //����ؼ������Ѱ�����GUI����ؼ������޸ĸ��ؼ�����ʾ��С
    }

    return iErr;
}


/***
  * ���ܣ�
        ���ô�����ʹ�õĻ�ˢ
  * ������
        1.GUIBRUSH *pWndBrush:  ���ڴ������Ļ�ˢ
        2.GUIWINDOW *pWndObj:   ��Ҫ������ʹ�û�ˢ�Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetWindowBrush(GUIBRUSH *pWndBrush, GUIWINDOW *pWndObj)
{
    //�ж�pWndBrush��pWndObj�Ƿ���Ч
    if (NULL == pWndBrush || NULL == pWndObj)
    {
        return -1;
    }

    pWndObj->pWndBrush = pWndBrush;

    return 0;
}


/***
  * ���ܣ�
        ���ô�����ʹ�õĻ���
  * ������
        1.GUIPEN *pWndPen:      ���ڴ������Ļ���
        2.GUIWINDOW *pWndObj:   ��Ҫ������ʹ�û��ʵĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetWindowPen(GUIPEN *pWndPen, GUIWINDOW *pWndObj)
{
    //�ж�pWndPen��pWndObj�Ƿ���Ч
    if (NULL == pWndPen || NULL == pWndObj)
    {
        return -1;
    }

    pWndObj->pWndPen = pWndPen;

    return 0;
}


/***
  * ���ܣ�
        ���ô�������Ӧ������
  * ������
        1.GUIFONT *pWndFont:    ���ڴ�����������
        2.GUIWINDOW *pWndObj:   ��Ҫ������ʹ������Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetWindowFont(GUIFONT *pWndFont, GUIWINDOW *pWndObj)
{
    //�ж�pWndFont��pWndObj�Ƿ���Ч
    if (NULL == pWndFont || NULL == pWndObj)
    {
        return -1;
    }

    pWndObj->pWndFont = pWndFont;

    return 0;
}


/***
  * ���ܣ�
        ���GUI����ؼ���ָ������Ĵ���ؼ�����
  * ������
        1.int iCompTyp:         GUI����ؼ����������
        2.int iCompLen:         GUI����ؼ�������ռ�õ��ڴ�ռ�
        3.void *pWndComp:       ָ�룬ָ��Ҫ��ӵ�GUI����ؼ�
        4.GUIWINDOW *pWndObj:   ��Ҫ���GUI����ؼ��Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int AddWindowComp(int iCompTyp, int iCompLen, void *pWndComp, 
                  GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pWndObj->Mutex));

    if (!iErr)
    {
        //�ж�pWndComp��pWndObj�Ƿ���Ч
        if (NULL == pWndComp || NULL == pWndObj)
        {
            return -1;
        }
    }

    if (!iErr)
    {
        //�ж�pWndComps�Ƿ�Ϊ��Чָ��Ϳؼ������Ƿ�����
        if ((NULL == pWndObj->pWndComps) || 
            ListFull(pWndObj->pWndComps))
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
        //���GUI����ؼ����ؼ�����
        pPkt->iType = iCompTyp;
        pPkt->iLength = iCompLen;
        pPkt->pObj = pWndComp;
        if (ListAdd(&(pPkt->List), pWndObj->pWndComps))
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
    MutexUnlock(&(pWndObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        ��ָ������Ĵ���ؼ�����ɾ��GUI����ؼ�
  * ������
        1.void *pWndComp:       ָ�룬ָ��Ҫɾ����GUI����ؼ�
        2.GUIWINDOW *pWndObj:   ��Ҫɾ��GUI����ؼ��Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int DelWindowComp(void *pWndComp, GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    int iPos;
    GUILIST_ITEM *pItem = NULL;
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pWndObj->Mutex));

    if (!iErr)
    {
        //�ж�pWndComp��pWndObj�Ƿ���Ч
        if (NULL == pWndComp || NULL == pWndObj)
        {
            return -1;
        }
    }

    if (!iErr)
    {
        //�ж�pWndComps�Ƿ�Ϊ��Чָ��Ϳؼ������Ƿ�Ϊ��
        if ((NULL == pWndObj->pWndComps) || 
            ListEmpty(pWndObj->pWndComps))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //�����ؼ������ҵ�ƥ���GUI����ؼ�
        list_next_each(pItem, pWndObj->pWndComps, iPos)
        {
            pPkt = container_of(pItem, GUIOBJ, List);
            if (pPkt->pObj == pWndComp)
            {
                //�ҵ�����ƥ��Ĵ���ؼ���ӿؼ�������ɾ��
                if (ListDel(pItem, pWndObj->pWndComps))
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

    //����
    MutexUnlock(&(pWndObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        ���ָ������Ĵ���ؼ�����
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ����մ���ؼ����еĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ���������Ϣ�����еĻ��������������ڳ�������ǰ���µ���
***/
int ClearWindowComp(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIOBJ *pPkt = NULL;

    //����
    MutexLock(&(pWndObj->Mutex));

    if (!iErr)
    {
        //�ж�pWndObj�Ƿ�Ϊ��Чָ��
        if (NULL == pWndObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�жϴ���ؼ�����pWndComps�Ƿ�Ϊ��Чָ��
        if (NULL == pWndObj->pWndComps)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����ɾ������ؼ�������
        while (pWndObj->pWndComps->iCount)
        {
            pPkt= container_of(pWndObj->pWndComps->pHead, GUIOBJ, List);
            if (ListDel(pWndObj->pWndComps->pHead, pWndObj->pWndComps))
            {
                iErr = -3;
                break;
            }

            //�ͷ���Դ
            free(pPkt);
        }
    }

    //����
    MutexUnlock(&(pWndObj->Mutex));

    return iErr;
}

