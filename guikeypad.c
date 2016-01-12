/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guikeypad.c
* ժ    Ҫ��  GUIKEYPADģ����Ҫ����豸����㶨�弰ʵ�֣��Ա�GUI�ܹ������ڲ�ͬ
*             Ӳ��ƽ̨��Ӧ�ò����Ӳ�����졣guikeypad.cʵ����guikeypad.h������
*             �ļ����豸����ز���������ʵ��GUI��ͼ������豸����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guikeypad.h"


/**************************************
* Ϊʵ��GUIKEYPAD����Ҫ���õ�����ͷ�ļ�
**************************************/
#include "guidevice.h"
#include "guischeduler.h"
#include "guievent.h"


/************************
* ����GUI�еĵ�ǰ���̶���
************************/
static GUIKEYPAD *pCurrKeypad = NULL;


/***
  * ���ܣ�
        ����ָ������Ϣ�������̶���
  * ������
        1.char *strDevName:             ��Ҫ�������̶�����豸������
        2.int iFbType:                  ���̻����豸���ͣ�1��׼��2�Զ���
        3.THREADFUNC fnKeypadThread:    �ص����������ڴ���֡������߳�
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIKEYPAD* CreateKeypad(char *strDevName, int iDevType, 
                        THREADFUNC fnKeypadThread)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIKEYPAD *pKeypadObj = NULL;

    if (!iErr)
    {
        //�ж�strDevName, fnKeypadThread�Ƿ�Ϊ��Чָ��
        if (NULL == strDevName || NULL == fnKeypadThread)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�����ڴ���Դ
        pKeypadObj = (GUIKEYPAD *) malloc(sizeof(GUIKEYPAD));
        if (NULL == pKeypadObj)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:open()
    if (!iErr)
    {
        //���Դ��豸�ļ�
        pKeypadObj->iDevFd = open(strDevName, O_RDWR|O_NONBLOCK);
        if (-1 == pKeypadObj->iDevFd)
        {
            iErr = -3;
        }
        //�����½����̶����iDevType
        pKeypadObj->iDevType = iDevType;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    if (!iErr)
    {
        //�����½����̶����fnKeypadThread�������Գ�ʼ��Mutex
        pKeypadObj->fnKeypadThread = fnKeypadThread;
        if (InitMutex(&(pKeypadObj->Mutex), NULL))
        {
            iErr = -4;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:close()
    //������
    switch (iErr)
    {
    case -4:
        close(pKeypadObj->iDevFd);
        //no break
    case -3:
        free(pKeypadObj);
        //no break
    case -2:
    case -1:
        pKeypadObj = NULL;
        //no break
    default:
        break;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return pKeypadObj;
}


/***
  * ���ܣ�
        ɾ�����̶���
  * ������
        1.GUIKEYPAD **ppKeypadObj:  ָ���ָ�룬ָ����Ҫ���ٵļ��̶���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyKeypad(GUIKEYPAD **ppKeypadObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppKeypadObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppKeypadObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppKeypadObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppKeypadObj)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:close()
    if (!iErr)
    {
        //�ͷ���Դ
        if (close((*ppKeypadObj)->iDevFd))  //�豸�ļ�Ϊ������Դ������֤����ֵ
        {
            iErr = -3;
        }
        //���ټ��̶��󣬲���ָ���ÿ�
        free(*ppKeypadObj);
        *ppKeypadObj = NULL;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iErr;
}


/***
  * ���ܣ�
        ��ȡ��ǰ���̶���
  * ������
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIKEYPAD* GetCurrKeypad(void)
{
    return pCurrKeypad;
}


/***
  * ���ܣ�
        ���õ�ǰ���̶���
  * ������
        1.GUIKEYPAD *pKeypadObj:    ������Ϊ��ǰ�����豸����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetCurrKeypad(GUIKEYPAD *pKeypadObj)
{
    //�ж�pKeypadObj�Ƿ���Ч
    if (NULL == pKeypadObj)
    {
        return -1;
    }

    pCurrKeypad = pKeypadObj;

    return 0;
}


/***
  * ���ܣ�
        Ĭ�ϼ����߳���ں���
  * ������
        1.void *pThreadArg:     �߳���ں�������������Ϊ(GUIKEYPAD *)
  * ���أ�
        �����߳̽���״̬
  * ��ע��
***/
void* DefaultKeypadThread(void *pThreadArg)
{
    //�����־������ֵ����
    int iErr = 0;
    static int iReturn = 0;
    //��ʱ��������
    int iExit = 0;
    GUIKEYPAD *pKeypadObj = pThreadArg;

    while (!iExit)
    {
        //���ݽ�����־�ж��Ƿ���Ҫ���������߳�
        iExit = GetExitFlag();
        if (iExit)
        {
            break;
        }

        //�����¼��ķ�װ
        printf("pKeypadObj->iDevType = %d\n", pKeypadObj->iDevType);
        switch (pKeypadObj->iDevType)
        {
        case GUIKEYPAD_TYP_STD:
            iErr = StandardKeypadProcess(pKeypadObj);
            break;
        case GUIKEYPAD_TYP_CUST:
            iErr = CustomKeypadProcess(pKeypadObj);
            break;
        default:
            break;
        }

        //����Ϊ-1����ʾ�޼������ݿɶ���˯��50����
        if (-1 == iErr)
        {
            MsecSleep(50);
        }
    }

    //�˳��߳�
    ThreadExit(&iReturn);
    return &iReturn;    //�����ֻ��Ϊ������������������ʵ���ϲ�������
}


/***
  * ���ܣ�
        ��׼���ͼ���(PC����)�Ĵ�������������ɼ����̵߳Ĵ���
  * ������
        1.GUIKEYPAD *pKeypadObj:    ������Ҫ����ļ��̶���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ�޼������ݿɶ�
***/
int StandardKeypadProcess(GUIKEYPAD *pKeypadObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    int iTmp;
    GUIEVENT_ITEM *pEventItem = NULL;
    GUIEVENT *pEventObj = NULL;
  #if (GUI_OS_ENV == LINUX_OS)  //OS���:input_event
    struct input_event event;
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS
  
    //����
    MutexLock(&(pKeypadObj->Mutex));

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:read()
    if (!iErr)
    {
        //��ȡ���̷��ص�����
        ThreadTestcancel();
        iTmp = read(pKeypadObj->iDevFd, &event, sizeof(event));
        ThreadTestcancel();
        if (iTmp != sizeof(event))
        {
            iErr = -1;
        }
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    if (!iErr)
    {
        //����Ϊ�����¼�������ڴ�
        pEventItem = (GUIEVENT_ITEM *) malloc(sizeof(GUIEVENT_ITEM));
        if (NULL == pEventItem)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:event
    if (!iErr)
    {
        //����GUIEVENT_ITEM
        if (EV_KEY == event.type)
        {
            switch (event.value)    //0:KeyUp��1:KeyDown
            {
            case 0:
                pEventItem->uiEventType = GUIEVENT_TYP_IN;
                pEventItem->uiEventCode = GUIEVENT_KEY_UP;
                pEventItem->uiEventValue = (unsigned int) event.code;
                break;
            case 1:
                pEventItem->uiEventType = GUIEVENT_TYP_IN;
                pEventItem->uiEventCode = GUIEVENT_KEY_DOWN;
                pEventItem->uiEventValue = (unsigned int) event.code;
                break;
            default:
                iErr = -3;
                break;
            }
        }
        else
        {
            iErr = -3;
        }
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    if (!iErr)
    {
        //�¼���д���¼�����
        pEventObj = GetCurrEvent();
        if (WriteEventQueue(pEventItem, pEventObj))
        {
            iErr = -4;
        }
    }

    //������
    switch (iErr)
    {
    case -4:
    case -3:
        free(pEventItem);
        //no break
    case -2:
    case -1:
    default:
        break;
    }

    //����
    MutexUnlock(&(pKeypadObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �Զ������ͼ��̵Ĵ�������������ɼ����̵߳Ĵ���
  * ������
        1.GUIKEYPAD *pKeypadObj:    ������Ҫ����ļ��̶���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ�޼������ݿɶ�
***/
int CustomKeypadProcess(GUIKEYPAD *pKeypadObj)
{
    //�����־������ֵ����
    int iErr = 0;

    //�����豸����㺯������Զ������ͼ��̵Ĵ���
    iErr = CustomKeypadFunc(pKeypadObj);

    return iErr;
}

