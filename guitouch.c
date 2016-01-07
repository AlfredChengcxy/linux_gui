/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guitouch.c
* ժ    Ҫ��  GUIFBMAPģ����Ҫ����豸����㶨�弰ʵ�֣��Ա�GUI�ܹ������ڲ�ͬӲ
*             ��ƽ̨��Ӧ�ò����Ӳ�����졣guitouch.cʵ����guitouch.h�������Ĵ�
*             �����豸����ز���������ʵ��GUI�Ĵ����������豸����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guitouch.h"


/*************************************
* Ϊʵ��GUITOUCH����Ҫ���õ�����ͷ�ļ�
*************************************/
#include "guidevice.h"
#include "guischeduler.h"
#include "guievent.h"


/**************************
* ����GUI�еĵ�ǰ����������
**************************/
static GUITOUCH *pCurrTouch = NULL;


/***
  * ���ܣ�
        ����ָ������Ϣ��������������
  * ������
        1.char *strDevName:         ��Ҫ����������������豸������
        2.int iFbType:              �����������豸���ͣ�1��׼��2�Զ���
        3.unsigned int uiHorRes:    ������ˮƽ�ֱ���
        4.unsigned int uiVerRes:    ��������ֱ�ֱ���
        5.THREADFUNC fnTouchThread: �ص����������ڴ���֡������߳�
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUITOUCH* CreateTouch(char *strDevName, int iDevType, 
                      unsigned int uiHorRes, unsigned int uiVerRes,
                      THREADFUNC fnTouchThread)
{
    //�����־������ֵ����
    int iErr = 0;
    GUITOUCH *pTouchObj = NULL;

    if (!iErr)
    {
        //�ж�strDevName, fnTouchThread�Ƿ�Ϊ��Чָ��
        if (NULL == strDevName || NULL == fnTouchThread)
        {
            iErr = -1;
        }
        //�жϴ������ֱ����Ƿ���Ч
        if (uiHorRes > 0xFFFF || uiVerRes > 0xFFFF)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�����ڴ���Դ
        pTouchObj = (GUITOUCH *) malloc(sizeof(GUITOUCH));
        if (NULL == pTouchObj)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:open()
    if (!iErr)
    {
        //���Դ��豸�ļ�
        pTouchObj->iDevFd = open(strDevName, O_RDWR|O_NONBLOCK);
        if (-1 == pTouchObj->iDevFd)
        {
            iErr = -3;
        }
        //�����½������������iDevType
        pTouchObj->iDevType = iDevType;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    if (!iErr)
    {
        //�����½�����������ķֱ���
        pTouchObj->uiHorRes = uiHorRes;
        pTouchObj->uiVerRes = uiVerRes;
        pTouchObj->uiCursX = 0;
        pTouchObj->uiCursY = 0;
        //�����½������������fnTouchThread�������Գ�ʼ��Mutex
        pTouchObj->fnTouchThread = fnTouchThread;
        if (InitMutex(&(pTouchObj->Mutex), NULL))
        {
            iErr = -4;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:close()
    //������
    switch (iErr)
    {
    case -4:
        close(pTouchObj->iDevType);
        //no break
    case -3:
        free(pTouchObj);
        //no break
    case -2:
    case -1:
        pTouchObj = NULL;
        //no break
    default:
        break;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return pTouchObj;
}


/***
  * ���ܣ�
        ɾ������������
  * ������
        1.GUITOUCH **ppTouchObj:    ָ���ָ�룬ָ����Ҫ���ٵĴ���������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyTouch(GUITOUCH **ppTouchObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppTouchObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppTouchObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppTouchObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppTouchObj)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:close()
    if (!iErr)
    {
        //�ͷ���Դ
        if (close((*ppTouchObj)->iDevFd))   //�豸�ļ�Ϊ������Դ������֤����ֵ
        {
            iErr = -3;
        }
        //���ٴ��������󣬲���ָ���ÿ�
        free(*ppTouchObj);
        *ppTouchObj = NULL;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iErr;
}


/***
  * ���ܣ�
        ��ȡ��ǰ����������
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
GUITOUCH* GetCurrTouch(void)
{
    return pCurrTouch;
}


/***
  * ���ܣ�
        ���õ�ǰ����������
  * ������
        1.GUITOUCH *pTouchObj:  ������Ϊ��ǰ�������豸����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetCurrTouch(GUITOUCH *pTouchObj)
{
    //�ж�pTouchObj�Ƿ���Ч
    if (NULL == pTouchObj)
    {
        return -1;
    }

    pCurrTouch = pTouchObj;

    return 0;
}


/***
  * ���ܣ�
        ���ô������Ĺ��λ��
  * ������
        1.unsigned int uiCursX: ��������ǰ������ֵ��0~0xFFFF
        2.unsigned int uiCursY: ��������ǰ������ֵ��0~0xFFFF
        3.GUITOUCH *pTouchObj:  ��Ҫ���ù��λ�õĴ���������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ������������������еĻ��������������ڳ�������ǰ���µ���
***/
int SetTouchCursor(unsigned int uiCursX, unsigned int uiCursY,
                   GUITOUCH *pTouchObj)
{    
    //����
    MutexLock(&(pTouchObj->Mutex));

    //�ж�uiCursX��uiCursY��pTouchObj�Ƿ���Ч
    if (uiCursX > 0xFFFF || uiCursY > 0xFFFF || NULL == pTouchObj)
    {
        return -1;
    }

    //���ù��λ��
    pTouchObj->uiCursX = uiCursX;
    pTouchObj->uiCursY = uiCursY;

    //����
    MutexUnlock(&(pTouchObj->Mutex));

    return 0;
}


/***
  * ���ܣ�
        Ĭ�ϴ������߳���ں���
  * ������
        1.void *pThreadArg:     �߳���ں�������������Ϊ(GUITOUCH *)
  * ���أ�
        �����߳̽���״̬
  * ��ע��
***/
void* DefaultTouchThread(void *pThreadArg)
{
    //�����־������ֵ����
    int iErr = 0;
    static int iReturn = 0;
    //��ʱ��������
    int iExit = 0;
    GUITOUCH *pTouchObj = pThreadArg;

    while (!iExit)
    {
        //���ݽ�����־�ж��Ƿ���Ҫ�����������߳�
        iExit = GetExitFlag();
        if (iExit)
        {
            break;
        }

        //�������¼��ķ�װ
        switch (pTouchObj->iDevType)
        {
        case GUITOUCH_TYP_STD:
            iErr = StandardTouchProcess(pTouchObj);
            break;
        case GUITOUCH_TYP_CUST:
            iErr = CustomTouchProcess(pTouchObj);
            break;
        default:
            break;
        }

        //����Ϊ-1����ʾ�޴��������ݿɶ���˯��50����
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
        ��׼���ʹ�����(PC���)�Ĵ�������������ɴ������̵߳Ĵ���
  * ������
        1.GUITOUCH *pTouchObj:  ������Ҫ����Ĵ���������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ�޴��������ݿɶ�
***/
int StandardTouchProcess(GUITOUCH *pTouchObj)
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
    MutexLock(&(pTouchObj->Mutex));

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:read()
    if (!iErr)
    {
        //��ȡ���������ص�����
        ThreadTestcancel();
        iTmp = read(pTouchObj->iDevFd, &event, sizeof(event));
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
        //����Ϊ�������¼�������ڴ�
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
        switch (event.type)
        {
        case EV_KEY:
            if (BTN_MOUSE == event.code)
            {
                if (event.value)    //0:KeyUp��1:KeyDown
                {
                    pEventItem->uiEventType = GUIEVENT_TYP_IN;
                    pEventItem->uiEventCode = GUIEVENT_ABS_DOWN;
                    pEventItem->uiEventValue = (pTouchObj->uiCursX << 16) |
                                               (pTouchObj->uiCursY);
                }
                else
                {
                    pEventItem->uiEventType = GUIEVENT_TYP_IN;
                    pEventItem->uiEventCode = GUIEVENT_ABS_UP;
                    pEventItem->uiEventValue = (pTouchObj->uiCursX << 16) |
                                               (pTouchObj->uiCursY);
                }
            }
            else
            {
                iErr = -3;
            }
            break;
        case EV_REL:
            switch (event.code)
            {
            case REL_X:
                iTmp = (int) (pTouchObj->uiCursX);
                iTmp += event.value;
                if (iTmp < 0)
                {
                    iTmp = 0;
                }
                if (iTmp > ((int) pTouchObj->uiHorRes))
                {
                    iTmp = (int) pTouchObj->uiHorRes;
                }
                pTouchObj->uiCursX = (unsigned int) iTmp;
                pEventItem->uiEventType = GUIEVENT_TYP_IN;
                pEventItem->uiEventCode = GUIEVENT_MOV_CURSOR;
                pEventItem->uiEventValue = (pTouchObj->uiCursX << 16) |
                                           (pTouchObj->uiCursY);
                break;
            case REL_Y:
                iTmp = (int) (pTouchObj->uiCursY);
                iTmp += event.value;
                if (iTmp < 0)
                {
                    iTmp = 0;
                }
                if (iTmp > ((int) pTouchObj->uiVerRes))
                {
                    iTmp = (int) pTouchObj->uiVerRes;
                }
                pTouchObj->uiCursY = (unsigned int) iTmp;
                pEventItem->uiEventType = GUIEVENT_TYP_IN;
                pEventItem->uiEventCode = GUIEVENT_MOV_CURSOR;
                pEventItem->uiEventValue = (pTouchObj->uiCursX << 16) |
                                           (pTouchObj->uiCursY);
                break;
            default:
                iErr = -3;
                break;
            }
            break;
        default:
            iErr = -3;
            break;
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
    MutexUnlock(&(pTouchObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �Զ������ʹ������Ĵ�������������ɴ������̵߳Ĵ���
  * ������
        1.GUITOUCH *pTouchObj:  ������Ҫ����Ĵ���������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ�޴��������ݿɶ�
***/
int CustomTouchProcess(GUITOUCH *pTouchObj)
{
    //�����־������ֵ����
    int iErr = 0;

    //�����豸����㺯������Զ������ʹ������Ĵ���
    iErr = CustomTouchFunc(pTouchObj);

    return iErr;
}

