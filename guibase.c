/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guibase.c
* ժ    Ҫ��  ʵ��GUI�����������͵Ĳ���������Ϊ����ģ���ṩ֧��
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guibase.h"


/***
  * ���ܣ�
        ת��C�ַ���ΪGUI�ַ���
  * ������
        1.char *pString:    Ҫת����C�ַ���
  * ���أ�
        �ɹ�������Чָ�룬���򷵻�NULL
  * ��ע��
***/
GUICHAR* TransString(char *pString)
{
    //�����־������ֵ����
    GUICHAR *pReturn = NULL;
    //��ʱ��������
    char *pTmp = NULL;
    int iSize;

    //�������
    if (NULL == pString)
    {
        return NULL;
    }

    //ͳ���ַ������ȣ�����'\0'
    for (pTmp = pString, iSize = 1; *pTmp; pTmp++)
    {
        iSize++;
    }

    //����Ϊ�ַ������ݷ����ڴ�
    pReturn = (GUICHAR *) malloc(iSize * sizeof(GUICHAR));
    if (NULL == pReturn)
    {
        return NULL;
    }

    //����ַ�����ת��
    while (--iSize >= 0)
    {
        pReturn[iSize] = pString[iSize];
    }

    return pReturn;
}


/***
  * ���ܣ�
        �ַ���ճ�������������ڱ�׼C���strcat()
  * ������
        1.GUICHAR **ppDest: ָ��Ŀ���ַ���������Ϊ��
        2.GUICHAR *pSrc:    Դ�ַ���������Ϊ��
  * ���أ�
        �ɹ�������Чָ�룬���򷵻�NULL
  * ��ע��
***/
GUICHAR* StringCat(GUICHAR **ppDest, GUICHAR *pSrc)
{
    //��ʱ��������
    GUICHAR *pTmp = NULL;
    int iDest, iSrc;

    //�������
    if (NULL == ppDest || NULL == pSrc)
    {
        return NULL;
    }

    //�ж�ppDest��ָ����Ƿ�Ϊ��Чָ��
    if (NULL == *ppDest)
    {
        return NULL;
    }

    //ͳ��Ŀ���ַ�����Դ�ַ������ȣ�������'\0'
    for (pTmp = *ppDest, iDest = 0; *pTmp; pTmp++)
    {
        iDest++;
    }
    for (pTmp = pSrc, iSrc = 0; *pTmp; pTmp++)
    {
        iSrc++;
    }

    //���ǵ�ԴΪ���ַ��������
    if (0 == iSrc)
    {
        return *ppDest;
    }

    //����Ŀ���ַ����洢�ռ�
    pTmp = (GUICHAR *) malloc((iDest + iSrc + 1) * sizeof(GUICHAR));
    if (NULL == pTmp)
    {
        return NULL;
    }

    //����ַ���ճ��
    if (iDest)
    {
        memcpy(pTmp, *ppDest, iDest * sizeof(GUICHAR));
    }
    memcpy(pTmp + iDest, pSrc, (iSrc + 1) * sizeof(GUICHAR));

    //�ͷžɵ�Ŀ���ַ������ݣ������¶���Ŀ���ַ���
    free(*ppDest);
    *ppDest = pTmp;

    return *ppDest;
}


/***
  * ���ܣ�
        �ַ������ƣ����������ڱ�׼C���strcpy()
  * ������
        1.GUICHAR **ppDest: ָ��Ŀ���ַ���������Ϊ��
        2.GUICHAR *pSrc:    Դ�ַ���������Ϊ��
  * ���أ�
        �ɹ�������Чָ�룬���򷵻�NULL
  * ��ע��
***/
GUICHAR* StringCpy(GUICHAR **ppDest, GUICHAR *pSrc)
{
    //��ʱ��������
    GUICHAR *pTmp = NULL;
    int iSize;

    //�������
    if (NULL == ppDest || NULL == pSrc)
    {
        return NULL;
    }

    //�ж�ppDest��ָ����Ƿ�Ϊ��Чָ��
    if (NULL == *ppDest)
    {
        return NULL;
    }

    //ͳ��Դ�ַ������ȣ�����'\0'
    for (pTmp = pSrc, iSize = 1; *pTmp; pTmp++)
    {
        iSize++;
    }

    //����Ŀ���ַ����洢�ռ�
    pTmp = (GUICHAR *) malloc(iSize * sizeof(GUICHAR));
    if (NULL == pTmp)
    {
        return NULL;
    }

    //����ַ�������
    memcpy(pTmp, pSrc, iSize * sizeof(GUICHAR));

    //�ͷžɵ�Ŀ���ַ������ݣ������¶���Ŀ���ַ���
    free(*ppDest);
    *ppDest = pTmp;

    return *ppDest;
}


/***
  * ���ܣ�
        �ַ����Ƚϣ����������ڱ�׼C���strcmp()
  * ������
        1.GUICHAR *pS1: Ҫ�Ƚϵ��ַ���1������Ϊ��
        2.GUICHAR *pS2: Ҫ�Ƚϵ��ַ���2������Ϊ��
  * ���أ�
        pS1<pS2�����ظ�����pS1>pS2��������������ȣ�������
  * ��ע��
***/
int StringCmp(GUICHAR *pS1, GUICHAR *pS2)
{
    //�����־������ֵ����
    int iCmp = 0;
    //��ʱ��������
    GUICHAR *a = NULL, *b = NULL;

    //�ж�pS1��pS2�Ƿ�Ϊ��Чָ��
    if (NULL == pS1 || NULL == pS2)
    {
        return 0;
    }

    //�Ƚ��ַ���
    for (a = pS1, b = pS2; !(iCmp = *a - *b); a++, b++)
    {
        if (0 == *a || 0 == *b) //�ַ�����'\0'��β
        {
            break;
        }
    }

    return iCmp;
}


/***
  * ���ܣ�
        �Ƚ��������Σ����о��ι�ϵ����
  * ������
        1.GUIRECTANGLE *pS1:    Ҫ�Ƚϵľ���1������Ϊ��
        2.GUIRECTANGLE *pS2:    Ҫ�Ƚϵľ���2������Ϊ��
  * ���أ�
        ���ؾ��ι�ϵö��ֵ
  * ��ע��
***/
GUIRECTANGLE_RELA RectangleCompare(GUIRECTANGLE *pR1, GUIRECTANGLE *pR2)
{
    if (RectangleSeparate(pR1, pR2))        //�ж��Ƿ�˴˷���
    {
        return enuSeparate;
    }
    else
    {
        if (RectangleOverlay(pR1, pR2))     //�ж��Ƿ���ȫ����
        {
            return enuOverlay;
        }
        if (RectanglePortion(pR1, pR2))     //�ж��Ƿ���ȫ����
        {
            return enuPortion;
        }
    }

    return enuOverlap;
}


/***
  * ���ܣ�
        �ȽϾ���pR1�����pR2�Ƿ���룬���뷵��1�����򷵻�0
  * ������
        1.GUIRECTANGLE *pS1:    Ҫ�Ƚϵľ���1������Ϊ��
        2.GUIRECTANGLE *pS2:    Ҫ�Ƚϵľ���2������Ϊ��
  * ���أ�
        ���뷵��1�����򷵻�0
  * ��ע��
***/
int RectangleSeparate(GUIRECTANGLE *pR1, GUIRECTANGLE *pR2)
{
    //��ʱ��������
    GUIPOINT p;

    //���pR1���ĸ��˵��Ƿ�λ��pR2��
    p.x = pR1->Start.x;
    p.y = pR1->Start.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���Ͻ��Ƿ�λ��pR2��
    {
        return 0;
    }
    p.x = pR1->End.x;
    p.y = pR1->Start.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���Ͻ��Ƿ�λ��pR2��
    {
        return 0;
    }
    p.x = pR1->Start.x;
    p.y = pR1->End.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���½��Ƿ�λ��pR2��
    {
        return 0;
    }
    p.x = pR1->End.x;
    p.y = pR1->End.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���½��Ƿ�λ��pR2��
    {
        return 0;
    }

    //���pR2���ĸ��˵��Ƿ�λ��pR1��
    p.x = pR2->Start.x;
    p.y = pR2->Start.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���Ͻ��Ƿ�λ��pR1��
    {
        return 0;
    }
    p.x = pR2->End.x;
    p.y = pR2->Start.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���Ͻ��Ƿ�λ��pR1��
    {
        return 0;
    }
    p.x = pR2->Start.x;
    p.y = pR2->End.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���½��Ƿ�λ��pR1��
    {
        return 0;
    }
    p.x = pR2->End.x;
    p.y = pR2->End.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���½��Ƿ�λ��pR1��
    {
        return 0;
    }

    return 1;
}


/***
  * ���ܣ�
        �ȽϾ���pR1�����pR2�Ƿ���ȫ���ǣ�pR1��ȫ����pR2����1�����򷵻�0
  * ������
        1.GUIRECTANGLE *pS1:    Ҫ�Ƚϵľ���1������Ϊ��
        2.GUIRECTANGLE *pS2:    Ҫ�Ƚϵľ���2������Ϊ��
  * ���أ�
        ��ȫ���Ƿ���1�����򷵻�0
  * ��ע��
***/
int RectangleOverlay(GUIRECTANGLE *pR1, GUIRECTANGLE *pR2)
{
    if ((pR1->Start.x <= pR2->Start.x) &&
        (pR1->Start.y <= pR2->Start.y) &&
        (pR1->End.x >= pR2->End.x) &&
        (pR1->End.y >= pR2->End.y))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/***
  * ���ܣ�
        �ȽϾ���pR1�����pR2�Ƿ���ȫ������pR1��ȫ��pR2��������1�����򷵻�0
  * ������
        1.GUIRECTANGLE *pS1:    Ҫ�Ƚϵľ���1������Ϊ��
        2.GUIRECTANGLE *pS2:    Ҫ�Ƚϵľ���2������Ϊ��
  * ���أ�
        ��ȫ��������1�����򷵻�0
  * ��ע��
***/
int RectanglePortion(GUIRECTANGLE *pR1, GUIRECTANGLE *pR2)
{
    if ((pR1->Start.x >= pR2->Start.x) &&
        (pR1->Start.y >= pR2->Start.y) &&
        (pR1->End.x <= pR2->End.x) &&
        (pR1->End.y <= pR2->End.y))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/***
  * ���ܣ�
        �ȽϾ���pR1�����pR2�Ƿ񲿷��ص��������ص�����1�����򷵻�0
  * ������
        1.GUIRECTANGLE *pS1:    Ҫ�Ƚϵľ���1������Ϊ��
        2.GUIRECTANGLE *pS2:    Ҫ�Ƚϵľ���2������Ϊ��
  * ���أ�
        �����ص�����1�����򷵻�0
  * ��ע��
***/
int RectangleOverlap(GUIRECTANGLE *pR1, GUIRECTANGLE *pR2)
{
    //��ʱ��������
    GUIPOINT p;

    //���pR1���ĸ��˵��Ƿ�λ��pR2��
    p.x = pR1->Start.x;
    p.y = pR1->Start.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���Ͻ��Ƿ�λ��pR2��
    {
        return 1;
    }
    p.x = pR1->End.x;
    p.y = pR1->Start.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���Ͻ��Ƿ�λ��pR2��
    {
        return 1;
    }
    p.x = pR1->Start.x;
    p.y = pR1->End.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���½��Ƿ�λ��pR2��
    {
        return 1;
    }
    p.x = pR1->End.x;
    p.y = pR1->End.y;
    if ((p.x >= pR2->Start.x) &&
        (p.x <= pR2->End.x) &&
        (p.y >= pR2->Start.y) &&
        (p.y <= pR2->End.y))    //���pR1���½��Ƿ�λ��pR2��
    {
        return 1;
    }

    //���pR2���ĸ��˵��Ƿ�λ��pR1��
    p.x = pR2->Start.x;
    p.y = pR2->Start.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���Ͻ��Ƿ�λ��pR1��
    {
        return 1;
    }
    p.x = pR2->End.x;
    p.y = pR2->Start.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���Ͻ��Ƿ�λ��pR1��
    {
        return 1;
    }
    p.x = pR2->Start.x;
    p.y = pR2->End.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���½��Ƿ�λ��pR1��
    {
        return 1;
    }
    p.x = pR2->End.x;
    p.y = pR2->End.y;
    if ((p.x >= pR1->Start.x) &&
        (p.x <= pR1->End.x) &&
        (p.y >= pR1->Start.y) &&
        (p.y <= pR1->End.y))    //���pR2���½��Ƿ�λ��pR1��
    {
        return 1;
    }

    return 0;
}


/***
  * ���ܣ�
        �����µ��߳�
  * ������
        1.GUITHREAD *pThread:       ָ�򴴽������̵߳��߳�ID
        2.GUITHREAD_ATTR *pAttr:    ָ�����̵߳�����
        3.THREADFUNC fnEntry:       �������߳�ʱָ�����߳���ں���
        4.void *pArg:               �������߳�ʱ���ݵĲ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int ThreadCreate(GUITHREAD *pThread, GUITHREAD_ATTR *pAttr,
                 THREADFUNC fnEntry, void *pArg)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_create()
    iReturn = pthread_create(pThread, pAttr, fnEntry, pArg);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}


/***
  * ���ܣ�
        �˳���ǰ�߳�
  * ������
        1.void *pReturn:    �߳̽���״̬
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int ThreadExit(void *pReturn)
{
  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_exit()
    pthread_exit(pReturn);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return 0;
}


/***
  * ���ܣ�
        �ȴ��߳̽���
  * ������
        1.GUITHREAD Thread:     ָ����Ҫ�ȴ����̵߳��߳�ID
        2.void **ppReturn:      ָ���߳̽���״̬����������pthread_exit()
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int ThreadJoin(GUITHREAD Thread, void **ppReturn)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_join()
    iReturn = pthread_join(Thread, ppReturn);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}

/***
  * ���ܣ�
        ȡ���߳�
  * ������
        1.GUITHREAD Thread:     ָ����Ҫȡ�����̵߳��߳�ID
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int ThreadCancel(GUITHREAD Thread)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_cancel()
    iReturn = pthread_cancel(Thread);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}

/***
  * ���ܣ�
        �����߳�ȡ����
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int ThreadTestcancel(void)
{
  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_testcancel()
    pthread_testcancel();
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return 0;
}

/***
  * ���ܣ�
        ��ʼ����
  * ������
        1.GUIMUTEX *pMutex:     ָ�룬ָ����Ҫ��ʼ���Ļ�����
        2.GUIMUTEX_ATTR *pAttr: ָ�룬ָ�򻥳���������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int InitMutex(GUIMUTEX *pMutex, GUIMUTEX_ATTR *pAttr)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_mutex_init()
    iReturn = pthread_mutex_init(pMutex, pAttr);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}


/***
  * ���ܣ�
        ��������
  * ������
        1.GUIMUTEX *pMutex:   ָ�룬ָ����Ҫ�����ϵĻ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int MutexLock(GUIMUTEX *pMutex)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_mutex_lock()
    iReturn = pthread_mutex_lock(pMutex);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}


/***
  * ���ܣ�
        ���Լ���
  * ������
        1.GUIMUTEX *pMutex:   ָ�룬ָ����Ҫ���Լ����Ļ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int MutexTrylock(GUIMUTEX *pMutex)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_mutex_trylock()
    iReturn = pthread_mutex_trylock(pMutex);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}


/***
  * ���ܣ�
        ��������
  * ������
        1.GUIMUTEX *pMutex:   ָ�룬ָ����Ҫ���Խ����Ļ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int MutexUnlock(GUIMUTEX *pMutex)
{
    //�����־������ֵ����
    int iReturn = 0;

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:pthread_mutex_unlock()
    iReturn = pthread_mutex_unlock(pMutex);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}


/***
  * ���ܣ�
        �������ɺ���
  * ������
        1.unsigned long ulMsec:   ��Ҫ˯�ߵĺ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int MsecSleep(unsigned long ulMsec)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
  #if (GUI_OS_ENV == LINUX_OS)  //OS���:timeval,select()
    struct timeval tv;

    tv.tv_sec = ulMsec / 1000;
    tv.tv_usec = ulMsec % 1000 * 1000;
    iReturn = select(0, NULL, NULL, NULL, &tv);
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iReturn;
}


/***
  * ���ܣ�
        �½�һ���б����б��������iLimit����Ŀ
  * ������
        1.int iLimit:  Ҫ�������б�����������ɵ���Ŀ����iLimit����С��1
  * ���أ�
        �ɹ�����ָ�����б����Чָ�룬���򷵻�NULL
  * ��ע��
        ʹ��CreateList�����½����б��������Ϊ�ա�
***/
GUILIST* CreateList(int iLimit)
{
    //�����־������ֵ����
    GUILIST *pList = NULL;

    //�������
    if (iLimit < 0)
    {
        return NULL;    
    }

    //������Դ
    pList = (GUILIST *) malloc(sizeof(GUILIST));
    if (NULL == pList)
    {
        return NULL;    
    }

    //��ʼ���б�
    pList->iCount = 0;
    pList->iLimit = iLimit;
    pList->pHead = NULL;
    pList->pTail = NULL;

    return pList;
}


/***
  * ���ܣ�
        ɾ���б�pList�����ͷ�pListռ�õ�������Դ���ɹ�������
  * ������
        1.GUILIST *pList:   ָ�룬ָ����CreateList�������б����
  * ���أ�
        �ɹ������㣬���򷵻ش������
  * ��ע��
        DestroyList��֤�������pListΪ�ǿ�ָ�룬����б�pListΪ�գ�
        DestroyList�᷵�ش������-2��
***/
int DestroyList(GUILIST *pList)
{
    //�ж�pList�Ƿ�Ϊ��Чָ��
    if (NULL == pList)
    {
        return -1;      
    }

    //�ж�pList�Ƿ�Ϊ�գ����ǿ�������б����ɾ���ɳ���Ա�Լ�����
    if (!ListEmpty(pList))
    {
        return -2;
    }

    //�����б����
    free(pList);

    return 0;
}


/***
  * ���ܣ�
        ��ʼ���б�pList�� �ɹ������㣬���򷵻ط���ֵ
  * ������
        1.GUILIST *pList:   ָ�룬ָ����CreateList�������б����
  * ���أ�
        �ɹ������㣬���򷵻ش������
  * ��ע��
        ��ʼ��pList��iCount = 0��pHead = pTail = NULL
***/
inline int InitList(GUILIST *pList)
{
    //�ж�pList�Ƿ�Ϊ��Чָ��
    if (NULL == pList)
    {
        return -1;
    }

    //��ʼ���б�
    pList->iCount = 0;
    pList->pHead = NULL;
    pList->pTail = NULL;

    return 0;
}


/***
  * ���ܣ�
        �����б���pItem���б�pListβ��
  * ������
        1.GUILIST_ITEM *pItem:  ָ�룬ָ����Ҫ������б���
        2.GUILIST *pList:       ָ�룬ָ����CreateList�������б����
  * ���أ�
        �ɹ������㣬���򷵻ش������
  * ��ע��
        ����ListAddҪ��pList��ָ����б�δ���������ǽ�����Ŀ���뵽
        �б�pList��β�ˣ�����б���������������
***/
int ListAdd(GUILIST_ITEM *pItem, GUILIST *pList)
{
    //�ж�pItem��pList�Ƿ�Ϊ��Чָ��
    if (NULL == pList || NULL == pItem)
    {
        return -1;
    }

    // �ж�pList�Ƿ�Ϊ��
    if (ListFull(pList))
    {
        return -2;
    }

    //���pItem��pListβ��
    if (ListEmpty(pList))
    {
        //�б�pListΪ��ʱ
        pItem->pPrev = pItem;
        pItem->pNext = pItem;
        pList->pHead = pItem;
        pList->pTail = pItem;
    }
    else
    {
        //�б�pList��Ϊ��ʱ
        pItem->pPrev = pList->pTail;
        pItem->pNext = pList->pHead;
        pList->pTail->pNext = pItem;
        pList->pHead->pPrev = pItem;
        pList->pTail = pItem;
    }
    pItem->pOwner = pList;
    pList->iCount++;

    return 0;
}


/***
  * ���ܣ�
        ���б�pList��ɾ���б���pItem
  * ������
        1.GUIITEM *pItem:   ָ�룬ָ����Ҫɾ�����б���
        2.GUILIST *pList:   ָ�룬ָ����CreateList�������б����
  * ���أ�
        �ɹ������㣬���򷵻ش������
  * ��ע��
        ����ListAddҪ��pList��ָ����б�δ�գ�����б��ѿգ���������
***/
int ListDel(GUILIST_ITEM *pItem, GUILIST *pList)
{
    //�ж�pItem��pList�Ƿ�Ϊ��Чָ��
    if (NULL == pList || NULL == pItem)
    {
        return -1;
    }

    //�ж�pItem�Ƿ���pList�к�pList�Ƿ�Ϊ��
    if ((pItem->pOwner != pList) || 
        ListEmpty(pList))
    {
        return -2;
    }

    //ɾ��pList��pItem
    if (1 == pList->iCount)
    {
        //�б���ֻ��һ���б���
        pList->pHead = NULL;
        pList->pTail = NULL;
    }
    else
    {
        //�б����ж���б���
        pItem->pNext->pPrev = pItem->pPrev;
        pItem->pPrev->pNext = pItem->pNext;
        if (pItem == pList->pHead)
        {
            pList->pHead = pItem->pNext;
        }
        else if (pItem == pList->pTail)
        {
            pList->pTail = pItem->pPrev;
        }
    }

    //ɾ������pItem����ԱΪNULL
    pItem->pOwner = NULL;
    pItem->pNext = NULL;
    pItem->pPrev = NULL;
    pList->iCount--;

    return 0;
}


/***
  * ���ܣ�
        ��һ���б����б���pItem�Ƶ���һ���б�β��
  * ������
        1.GUIITEM *pItem:   ָ�룬ָ����Ҫ�ƶ����б���
        2.GUILIST *pList:   ָ�룬ָ����CreateList�������б����
  * ���أ�
        �ɹ������㣬���򷵻ش������
  * ��ע��
***/
int ListMove(GUILIST_ITEM *pItem, GUILIST *pList)
{
    //�ж�pItem��pList�Ƿ�Ϊ��Чָ��
    if (NULL == pList || NULL == pItem)
    {
        return -1;
    }

    //�ж�pList�Ƿ�Ϊ��
    if (ListFull(pList))
    {
        return -2;
    }

    //��pItem->pOwnerɾ���б���pItem
    if (ListDel(pItem, pItem->pOwner))
    {
        return -3;
    }

    //���pItem��pListβ��
    ListAdd(pItem, pList);

    return 0;
}


/***
  * ���ܣ�
        �ϲ��б�pAttach����һ�б�pList��β�˲���ʼ��ԭ�б�  
  * ������
        1.GUILIST *pAttach: ָ�룬ָ����Ҫ�ϲ����б����
        2.GUILIST *pList:   ָ�룬ָ����CreateList�������б����
  * ���أ�
        �ѿշ���0��ʧ�ܷ��ط���
  * ��ע��
        �豣֤pAttach��Ϊ�գ���Ϊ���򷵻ش������-2��
        ��pList�ϲ�pAttach����Ҫδ��,��pAttach->iCount����pList->iCountҪ����
        ��pList->iLimit��
***/
int ListSplice(GUILIST *pAttach, GUILIST *pList)
{
    //��ʱ��������
    int iCnt;
    GUILIST_ITEM *pTmp = NULL;

    //�ж�pAttach��pList�Ƿ�Ϊ��Чָ��
    if (NULL == pList || NULL == pAttach)
    {
        return -1;
    }

    //�ж�pAttach�Ƿ�Ϊ�պ�pList�Ƿ�δ��
    if (ListEmpty(pAttach) || 
        ListFull(pList))
    {
        return -2;
    }

    //�жϺϲ���pList���ȴ���iLimit
    if (pList->iCount + pAttach->iCount > pList->iLimit)
    {
        return -3;
    }

    //�ϲ�pAttach��pListβ�˲�����iCount
    if (pList->iCount)
    {
        pAttach->pHead->pPrev = pList->pTail;
        pList->pTail->pNext = pAttach->pHead;
        pAttach->pTail->pNext = pList->pHead;
        pList->pHead->pPrev = pAttach->pTail;
        pList->pTail = pAttach->pTail;
    }
    else
    {
        pList->pHead = pAttach->pHead;
        pList->pTail = pAttach->pTail;
    }
    pList->iCount +=  pAttach->iCount;

    iCnt = pAttach->iCount;
    pTmp = pAttach->pHead;

    //����pAttach�ı����б����pOwner
    while (iCnt--)
    {
        pTmp->pOwner = pList;
        pTmp = pTmp->pNext;
    }

    //��ʼ��pAttach
    InitList(pAttach);

    return 0;
}


/***
  * ���ܣ�
        ���pList�Ƿ�Ϊ�գ��ѿշ���1���ǿշ���0
  * ������
        1.CGList *pList:    ָ�룬ָ����GreateList�������б����
  * ���أ�
        �ѿշ���1���ǿշ���0
  * ��ע��
***/
inline int ListEmpty(GUILIST *pList)
{
    return !(pList->iCount);
}


/***
  * ���ܣ�
        ���pList�Ƿ�Ϊ������������1��δ������0
  * ������
        1.CGList *pList:    ָ�룬ָ����GreateList�������б����
  * ���أ�
        ��������1��δ������0
  * ��ע��
***/
inline int ListFull(GUILIST *pList)
{
    return pList->iCount >= pList->iLimit;
}

