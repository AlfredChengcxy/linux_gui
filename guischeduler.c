/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guischeduler.h
* ժ    Ҫ��  ����GUI�Ĵ�����Ȼ��Ƽ���ز���������ʵ�ֶര�塢���߳����С�
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guischeduler.h"


/*****************************************
* Ϊʵ��GUISCHEDULER����Ҫ���õ�����ͷ�ļ�
*****************************************/
#include "guibase.h"
#include "guievent.h"
#include "guimessage.h"
#include "guiwindow.h"
#include "guiglobal.h"


/**********************************
* ����GUI�еĽ����˳���־���以����
**********************************/
//GUI�еĽ����˳���־
static int iExitFlag = 0;
//���ڿ��Ʒ��ʽ����˳���־�Ļ�����
static GUIMUTEX mutexExitFlag;


/**************************
* ����GUI�еĴ����̻߳�����
**************************/
//���ڿ��ƴ����߳������Ļ�����(GUIĿǰֻ֧��һ�������߳�����)
static GUIMUTEX mutexThreadLock;


/***
  * ���ܣ�
        ��ʼ��GUI�����˳���־
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        Ĭ�Ͻ������˳���־��ʼ��Ϊ0
***/
int InitExitFlag(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    if (InitMutex(&mutexExitFlag, NULL))
    {
        iReturn = -1;
    }
    else 
    {
        MutexLock(&mutexExitFlag);   
        iExitFlag = 0;
        MutexUnlock(&mutexExitFlag);
    }

    return iReturn;
}


/***
  * ���ܣ�
        �õ�GUI�����˳���־
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int GetExitFlag(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    MutexLock(&mutexExitFlag);   
    iReturn = iExitFlag;
    MutexUnlock(&mutexExitFlag);

    return iReturn;
}


/***
  * ���ܣ�
        ����GUI�����˳���־
  * ������
        1.int iFlag:    ��Ҫ��Ϊ��GUI�����˳���־
  * ���أ�
        ��
  * ��ע��
***/
void SetExitFlag(int iFlag)
{
    MutexLock(&mutexExitFlag);   
    iExitFlag = iFlag;
    MutexUnlock(&mutexExitFlag);
}


/***
  * ���ܣ�
        ��������߳���ں���
  * ������
        1.void *pThreadArg:     �߳���ں�������������Ϊ(GUIMESSAGE *)
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
void* WindowSchedulerThread(void *pThreadArg)
{
    //�����־������ֵ����
    static int iReturn = 0;
    //��ʱ��������
    int iExit = 0;
    GUIMESSAGE *pMsg = (GUIMESSAGE *) pThreadArg;
    GUIMESSAGE_ITEM *pRecv = NULL;
    GUIWINDOW *pWnd = NULL;
    GUITHREAD thdWnd = -1;
    THREADFUNC fnThread = NULL;

    //�ȴ�100ms���Ա�GUI������׼������Դ
    MsecSleep(100);

    //������ѭ��
    while (!iExit)
    {
        //���ݽ�����־�ж��Ƿ���Ҫ���������߳�
        //ע��˴����������˳�������ѭ��������ᵼ�����ٴ����޷���ɣ��γɽ�ʬ
        iExit = GetExitFlag();

        //����Ϣ���ж��ض�������Ϣ��(ϵͳ��Ϣ)
        pRecv = RecvSpecialMessage(GUIMESSAGE_TYP_SYS, pMsg);
        if (NULL == pRecv)
        {
            MsecSleep(50);          //��û��ϵͳ��Ϣ��˯��50����
            continue;
        }

        //���ݲ�ͬϵͳ��Ϣ���������Ӧ����
        switch (pRecv->iMsgCode)
        {
        case GUIMESSAGE_SYS_EXIT:
            //ϵͳ�˳�����GUI�����˳���־
            SetExitFlag(1);
            //�ͷŶ�������Ϣ��
            free(pRecv);
            break;
        case GUIMESSAGE_THD_CREATE:
            //���������̣߳���ThreadCreate()
            pWnd = (GUIWINDOW *) (pRecv->uiMsgValue);
            if (NULL != pWnd)                           //����Ϣֵ��Ч
            {                                           //���õ�Ҫ�����Ĵ���ṹ
                if (NULL != pWnd->fnWndThread)          //�ж��Ƿ�ָ���̺߳���
                {                                       //����ָ�������̺߳���
                    fnThread = pWnd->fnWndThread;       //ʹ��ָ�����̺߳�����
                }                                       //���������߳�
                else                                    //����
                {                                       //��δָ�������̺߳���
                    fnThread = DefaultWindowThread;     //ʹ��Ĭ�ϵ��̺߳�����
                }                                       //���������߳�ǰ
                if (LockWindowThread())                 //���ԶԴ����߳�����
                {                                       //������ʧ��
                    WriteMessageQueue(pRecv, pMsg);     //���Ѷ�������Ϣ���д
                    MsecSleep(50);                      //����ʧ�ܺ�˯��50����
                    break;                              //�жϽ����������
                }                                       //����ס�����߳���
                ThreadCreate(&thdWnd, NULL,             //��Ĭ���߳�����
                             fnThread, pWnd);           //��ɴ����̵߳Ĵ���
                pWnd->thdWndTid = thdWnd;               //�����߳�ID
            }
            //�ͷŶ�������Ϣ��
            free(pRecv);
            break;
        case GUIMESSAGE_THD_DESTROY:
            //���ٴ����̣߳���ThreadJoin()
            pWnd = (GUIWINDOW *) (pRecv->uiMsgValue);
            if (NULL != pWnd)                           //����Ϣֵ��Ч
            {                                           //���õ�Ҫ�����Ĵ���ṹ
                thdWnd = pWnd->thdWndTid;               //��ȡ�����Ӧ���߳�ID
                ThreadJoin(thdWnd, NULL);               //�ȴ��߳̽�����������Դ
                DestroyWindow(&pWnd);                   //���پɵĴ���
                SetCurrWindow(NULL);                    //��ǰ�����ÿ�
                UnlockWindowThread();                   //���������߳�
            }
            //�ͷŶ�������Ϣ��
            free(pRecv);
            break;
        default:
            //�ͷŶ�������Ϣ��
            free(pRecv);
            break;
        }

    }

    //�˳��߳�
    ThreadExit(&iReturn);
    return &iReturn;    //�����ֻ��Ϊ������������������ʵ���ϲ�������
}


/***
  * ���ܣ�
        Ĭ�ϴ��崦���߳���ں���
  * ������
        1.void *pThreadArg:     �߳���ں�������������Ϊ(GUIWINDOW *)
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
        Ĭ�ϵĴ��崦���̺߳��������ڴ�������ʱ����δָ��fnWndThread����ʹ�øú�
        ���������崦���̡߳������Ҫʹ���Զ���ĺ�������Ϊ���崦���̣߳���ο�
        �������Ŀ�ܽṹ��
***/
void* DefaultWindowThread(void *pThreadArg)
{
    //�����־������ֵ����
    static int iReturn = 0;
    //��ʱ��������
    int iRun = 1;
    int iLoop = 1;
    int iExec = 0;
    GUIWINDOW *pWnd = (GUIWINDOW *) pThreadArg;
    GUIMESSAGE *pMsg = NULL;
    GUIMESSAGE_ITEM *pRecv = NULL;

    //�õ���ǰ��Ϣ����
    pMsg = GetCurrMessage();

    //��ʼ���崦��ǰ�����֮ǰ������ܲ������¼�����Ϣ
    ClearEventQueue(GetCurrEvent());
    ClearSpecialMessage(GUIMESSAGE_TYP_WND, pMsg);

    //��������ϢGUIMESSAGE_WND_INIT
    SendWndMsg_WindowInit(pWnd);

    //���崦��
    while (iRun)
    {
        //����Ϣ���ж�������Ϣ��
        pRecv = RecvSpecialMessage(GUIMESSAGE_TYP_WND, pMsg);
        if (NULL == pRecv)
        {
            MsecSleep(50);          //��û�д�����Ϣ��˯��50����
            continue;
        }

        //���ݲ�ͬ������Ϣ���������Ӧ����
        switch (pRecv->iMsgCode)
        {
        case GUIMESSAGE_WND_INIT:
            if (NULL != pWnd->fnWndInit)
            {
                pWnd->fnWndInit(pWnd);          //�����ʼ��
                SendWndMsg_WindowPaint(pWnd);   //׼��ִ�д������
            }
            break;
        case GUIMESSAGE_WND_EXIT:
            if (NULL != pWnd->fnWndExit)
            {
                pWnd->fnWndExit(pWnd);              //�����˳�
                iRun = 0;                           //���б�־��0
                SendSysMsg_ThreadDestroy(pWnd);     //׼�������߳�
            }
            break;
        case GUIMESSAGE_WND_PAINT:
            if (NULL != pWnd->fnWndPaint)
            {
                pWnd->fnWndPaint(pWnd);             //�������
                pWnd->Visible.iFocus = 1;           //���ý��㣬Ӱ�찴���¼���װ
                SetCurrWindow(pWnd);                //���õ�ǰ���壬Ӱ���¼���װ
                iExec = 1;                          //ִ�б�־��1
                SendWndMsg_WindowLoop(pWnd);        //׼��ִ�д���ѭ��
            }
            break;
        case GUIMESSAGE_WND_LOOP:
            if (NULL != pWnd->fnWndLoop)
            {
                if (iLoop)                          //�ж��Ƿ�������ѭ��
                {                                   //������
                    pWnd->fnWndLoop(pWnd);          //ִ��һ�δ���ѭ��
                    SendWndMsg_WindowLoop(pWnd);    //׼��ִ����һ�δ���ѭ�� 
                }
            }
            break;
        case GUIMESSAGE_WND_PAUSE:
            if (NULL != pWnd->fnWndPause)
            {
                ClearEventQueue(GetCurrEvent());                //����¼�����
                ClearSpecialMessage(GUIMESSAGE_TYP_WND, pMsg);  //��մ�����Ϣ
                iExec = 0;                                      //ִ�б�־��0
                //...
                UnlockWindowThread();                           //���������߳�
            }
            break;
        case GUIMESSAGE_WND_RESUME:
            if (NULL != pWnd->fnWndResume)
            {
                LockWindowThread();
                //...
                iExec = 1;
            }
            break;
        case GUIMESSAGE_LOP_ENABLE:
            iLoop = 1;                      //ѭ����־��1��������ѭ��
            SendWndMsg_WindowLoop(pWnd);    //׼��ִ�д���ѭ��
            break;
        case GUIMESSAGE_LOP_DISABLE:
            iLoop = 0;                      //ѭ����־��0����ֹ����ѭ��
            break;
        default:
            if (iExec)                          //�ж��Ƿ�����ִ����Ϣ�ַ�����
            {                                   //������
                ExecMessageProc(pRecv, pMsg);   //��������������Ϣ����
            }
            break;
        }

        //�ͷŶ�������Ϣ��
        free(pRecv);
    }

    //�˳��߳�
    ThreadExit(&iReturn);
    return &iReturn;    //�����ֻ��Ϊ������������������ʵ���ϲ�������
}


/***
  * ���ܣ�
        ��ʼ�������̻߳�����
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int InitThreadLock(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    if (InitMutex(&mutexThreadLock, NULL))
    {
        iReturn = -1;
    }

    return iReturn;
}


/***
  * ���ܣ�
        ��ס��ǰ�����߳�
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �����߳����к�Ӧ����һʱ����øú������Ա�֤GUI��ʼ��ֻ��һ�������߳�
***/
int LockWindowThread(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = MutexTrylock(&mutexThreadLock);

    return iReturn;
}


/***
  * ���ܣ�
        ������ǰ�����߳�
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �����߳��˳�ǰ��������øú�������ʹ���������̵߳�������
***/
int UnlockWindowThread(void)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = MutexUnlock(&mutexThreadLock);

    return iReturn;
}

