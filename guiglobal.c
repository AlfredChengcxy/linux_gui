/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guiglobal.c
* ժ    Ҫ��  ʵ����GUI��صĹ����������������ṩ����GUI�����ĳ�ʼ�����á�
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guiglobal.h"


/**************************************
* Ϊʵ��GUIGLOBAL����Ҫ���õ�����ͷ�ļ�
**************************************/
//#include ""


/******************************
* ����GUI���뻷��������صı���
******************************/
static GUIFBMAP *pEnvFbmap = NULL;
static GUIKEYPAD *pEnvKeypad = NULL;
static GUITOUCH *pEnvTouch = NULL;

static GUIEVENT *pEnvEvent = NULL;
static GUIMESSAGE *pEnvMessage = NULL;

static GUIPALETTE *pEnvPalette = NULL;
static GUIPEN *pEnvPen = NULL;
static GUIBRUSH *pEnvBrush = NULL;
static GUIFONT *pEnvFont = NULL;

static GUITHREAD thdScheduler = -1;
static GUITHREAD thdEvent = -1;


/***
  * ���ܣ�
        ��ʼ��GUI����������GUI��Դ
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int InitializeGUI(void)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //���Գ�ʼ�������˳���־
        if (InitExitFlag())
        {
            iErr = -1;
        }
    }

    if (!iErr)  //�豸������ʼ��
    {
        //������ǰGUI������֡����ӳ�����
        pEnvFbmap = CreateFbmap(DEVFILE_FB, GUI_FBTYP_STD,
                                800, 480, 
                                DefaultFbThread);
        if (NULL == pEnvFbmap)
        {
            iErr = -2;
        }
        SetCurrFbmap(pEnvFbmap);
        //������ǰGUI�����ļ��̶���
        //pEnvKeypad = CreateKeypad(DEVFILE_KEYPAD, GUIKEYPAD_TYP_CUST,
        //                          DefaultKeypadThread);
        //if (NULL == pEnvKeypad)
        //{
        //    iErr = -2;
        //}
        //SetCurrKeypad(pEnvKeypad);
        //������ǰGUI�����Ĵ���������
        pEnvTouch = CreateTouch(DEVFILE_TOUCH, GUIKEYPAD_TYP_CUST,
                                800, 480,
                                DefaultTouchThread);
        if (NULL == pEnvTouch)
        {
            iErr = -2;
        }
        SetCurrTouch(pEnvTouch);
    }

    if (!iErr)  //ϵͳ����ģ���ʼ��
    {
        //������ǰGUI�������¼�����
        pEnvEvent = CreateEvent(GUIEVENT_ITEM_LIMIT, EventPacketThread);
        if (NULL == pEnvEvent)
        {
            iErr = -3;
        }
        SetCurrEvent(pEnvEvent);
        //������ǰGUI��������Ϣ����
        pEnvMessage = CreateMessage(GUIMESSAGE_ITEM_LIMIT, 
                                    GUIMESSAGE_REG_LIMIT);
        if (NULL == pEnvMessage)
        {
            iErr = -3;
        }
        SetCurrMessage(pEnvMessage);
        //��ʼ�������̻߳�����(�����߳̽������߳�����������֮ǰ���д˲���)
        if (InitThreadLock())
        {
            iErr = -3;
        }
        //������ǰGUI�����ĵ����߳�
        if (ThreadCreate(&thdScheduler, NULL,
                         WindowSchedulerThread, pEnvMessage))
        {
            iErr = -3;
        }
        //��ʼ����ǰ����(�¼���װ�߳̽����ʵ�ǰ���壬������֮ǰ���д˲���)
        if (InitCurrWindow())
        {
            iErr = -3;
        }
        //������ǰGUI�������¼���װ�߳�
        if (ThreadCreate(&thdEvent, NULL,
                         EventPacketThread, pEnvEvent))
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //������ǰGUI�����ĵ�ɫ��
        pEnvPalette = CreatePalette(256);
        if (NULL == pEnvPalette)
        {
            iErr = -4;
        }
        SetCurrPalette(pEnvPalette);
        //������ǰGUI�����Ļ���
        pEnvPen = CreatePen(GUIPEN_TYP_SOLID, 1, 0x0);
        if (NULL == pEnvPen)
        {
            iErr = -4;
        }
        SetCurrPen(pEnvPen);
        //������ǰGUI�����Ļ�ˢ
        pEnvBrush = CreateBrush(GUIBRUSH_TYP_SOLID);
        if (NULL == pEnvBrush)
        {
            iErr = -4;
        }
        SetCurrBrush(pEnvBrush);
        //������ǰGUI����������
        pEnvFont = CreateFont(FontFileDirectory"unicode.fnt", 16, 16, 0x00FFFFFF, COLOR_TRANS);
        if (NULL == pEnvFont)
        {
            iErr = -4;
        }
        SetCurrFont(pEnvFont);
    }

    return iErr;
}


/***
  * ���ܣ�
        �ͷ�GUI������������Դ
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int ReleaseGUI(void)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //���ٵ�ǰGUI����������
        if (DestroyFont(&pEnvFont))
        {
            iErr = -1;
        }
        //���ٵ�ǰGUI�����Ļ���
        if (DestroyPen(&pEnvPen))
        {
            iErr = -1;
        }
        //���ٵ�ǰGUI�����Ļ�ˢ
        if (DestroyBrush(&pEnvBrush))
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //������ǰGUI�������¼���װ�߳�
        if (ThreadJoin(thdEvent, NULL))
        {
            iErr = -2;
        }
        //������ǰGUI�����ĵ����߳�
        if (ThreadJoin(thdScheduler, NULL))
        {
            iErr = -2;
        }
        //���ٵ�ǰGUI��������Ϣ����
        ClearMessageQueue(pEnvMessage);
        ClearMessageReg(pEnvMessage);
        if (DestroyMessage(&pEnvMessage))
        {
            iErr = -2;
        }
        //���ٵ�ǰGUI�������¼�����
        ClearEventQueue(pEnvEvent);
        if (DestroyEvent(&pEnvEvent))
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //���ٵ�ǰGUI�����Ĵ���������
        if (DestroyTouch(&pEnvTouch))
        {
            iErr = -3;
        }
        //���ٵ�ǰGUI�����İ�������
        if (DestroyKeypad(&pEnvKeypad))
        {
            //iErr = -3;
        }
        //���ٵ�ǰGUI������֡����ӳ��
        if (DestroyFbmap(&pEnvFbmap))
        {
            iErr = -3;
        }
    }

    return iErr;
}


/***
  * ���ܣ�
        ����ϵͳ��Ϣ�Ա㽨���µĴ����߳�
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ���õ��µĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendSysMsg_ThreadCreate(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //����ϵͳ��ϢGUIMESSAGE_THD_CREAT����������߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_SYS;
        pItem->iMsgCode = GUIMESSAGE_THD_CREATE;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ����ϵͳ��Ϣ�Ա��������д����߳�
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ���õ��µĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendSysMsg_ThreadDestroy(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //����ϵͳ��ϢGUIMESSAGE_THD_DESTROY����������߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_SYS;
        pItem->iMsgCode = GUIMESSAGE_THD_DESTROY;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�ִ�д����ʼ��
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ��ʼ���Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_WindowInit(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //���ʹ�����ϢGUIMESSAGE_WND_INIT�����崦���߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_WND_INIT;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�ִ�д����˳�
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ�˳��Ĵ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_WindowExit(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //���ʹ�����ϢGUIMESSAGE_WND_EXIT�����崦���߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_WND_EXIT;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�ִ�д������
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ���ƵĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_WindowPaint(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //���ʹ�����ϢGUIMESSAGE_WND_PAINT�����崦���߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_WND_PAINT;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�ִ�д���ѭ��
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ���ƵĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_WindowLoop(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //���ʹ�����ϢGUIMESSAGE_WND_LOOP�����崦���߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_WND_LOOP;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�ִ�д������
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ���ƵĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_WindowPause(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //���ʹ�����ϢGUIMESSAGE_WND_PAUSE�����崦���߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_WND_PAUSE;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�ִ�д���ָ�
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ���ƵĴ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_WindowResume(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //���ʹ�����ϢGUIMESSAGE_WND_RESUME�����崦���߳�
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_WND_RESUME;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա�������������ѭ��
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ������������ѭ���ĵ�ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_LoopEnable(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //����ϵͳ��ϢGUIMESSAGE_LOP_ENABLE�����崦���߳��Ա�������������ѭ��
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_LOP_ENABLE;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա��ֹ��ֹͣ����ѭ��
  * ������
        1.GUIWINDOW *pWndObj:   ��Ҫ��ֹ��ֹͣ����ѭ���ĵ�ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_LoopDisable(GUIWINDOW *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //����ϵͳ��ϢGUIMESSAGE_LOP_DISABLE�����崦���߳��Ա��ֹ����ѭ��
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_LOP_DISABLE;
        pItem->uiMsgValue = (unsigned int) pWndObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}


/***
  * ���ܣ�
        ���ʹ�����Ϣ�Ա���д�����
  * ������
        1.void *pErrData:   ���ݸ����������Ĵ������
        2.int iDataLen:     ָ������������������ĳ���
        3.void *pRecvObj:   ��Ҫ���մ�����Ϣ��ִ�д���Ķ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SendWndMsg_ErrorProc(void *pErrData, int iDataLen, void *pRecvObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pItem = NULL;

    pMsg = GetCurrMessage();

    //����ϵͳ��ϢGUIMESSAGE_ERR_PROC�����崦���߳��Ա�ִ�д�����
    pItem = (GUIMESSAGE_ITEM *) malloc(sizeof(GUIMESSAGE_ITEM));
    if (NULL == pItem)
    {
        iReturn = -1;
    }
    else
    {
        pItem->iMsgType = GUIMESSAGE_TYP_WND;
        pItem->iMsgCode = GUIMESSAGE_ERR_PROC;
        pItem->uiMsgValue = (unsigned int) pErrData;
        pItem->iValueLength = iDataLen;
        pItem->pRecvObj = pRecvObj;
        WriteMessageQueue(pItem, pMsg); //pItem�ɱ�����Ĵ����߳��ͷ�
    }

    return iReturn;
}

