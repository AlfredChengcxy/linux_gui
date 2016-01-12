/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guifbmap.h
* ժ    Ҫ��  GUIFBMAPģ����Ҫ����豸����㶨�弰ʵ�֣��Ա�GUI�ܹ������ڲ�ͬӲ
*             ��ƽ̨��Ӧ�ò����Ӳ�����졣guifbmap.cʵ����guifbmap.h��������֡
*             �����豸����ز���������ʵ��GUI��ͼ������豸����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guifbmap.h"


/*************************************
* Ϊʵ��GUIFBMAP����Ҫ���õ�����ͷ�ļ�
*************************************/
#include "guidevice.h"
#include "guischeduler.h"


/**************************
* ����GUI�еĵ�ǰ֡����ӳ��
**************************/
static GUIFBMAP *pCurrFbmap = NULL;


/***
  * ���ܣ�
        ����ָ������Ϣֱ�Ӵ���֡����ӳ�����
  * ������
        1.char *strDevName:         ��Ҫ����֡����ӳ�������豸������
        2.int iDevType:             ֡�����豸���ͣ�0��׼��1˫���塢2ҳ����
        3.unsigned int uiHorDisp:   ӳ���������ʾ��ˮƽ�ֱ���
        4.unsigned int uiVerDisp:   ӳ���������ʾ�Ĵ�ֱ�ֱ���
        5.THREADFUNC fnFbThread:    �ص����������ڴ���֡������߳�
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIFBMAP* CreateFbmap(char *strDevName, int iDevType, 
                      unsigned int uiHorDisp, unsigned int uiVerDisp, 
                      THREADFUNC fnFbThread)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIFBMAP *pFbmapObj = NULL;
    //��ʱ��������
  #if (GUI_OS_ENV == LINUX_OS)  //OS���:fb_var_screeninfo,fb_fix_screeninfo
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    if (!iErr)
    {
        //�ж�strDevName��fnFbThread�Ƿ�Ϊ��Чָ��
        if (NULL == strDevName || NULL == fnFbThread)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //����Ϊ֡����ӳ����������Դ
        pFbmapObj = (GUIFBMAP *) malloc(sizeof(GUIFBMAP));
        if (NULL == pFbmapObj)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:open(),ioctl(),mmap(),fb_fix,fb_var
    if (!iErr)
    {
        //���Դ��豸�ļ�
        pFbmapObj->iDevFd = open(strDevName, O_RDWR);
        if (-1 == pFbmapObj->iDevFd)
        {
            iErr = -3;
        }
        //����֡����ӳ������iDevType
        pFbmapObj->iDevType = iDevType;
    }

    if (!iErr)
    {
        //���Ե���ioctl ()����ȡfb_fix_screeninfo��fb_var_screeninfo
        if ((-1 == ioctl(pFbmapObj->iDevFd, FBIOGET_FSCREENINFO, &fb_fix)) ||
            (-1 == ioctl(pFbmapObj->iDevFd, FBIOGET_VSCREENINFO, &fb_var)))
        {
            iErr = -4;
        }
    }

    if (!iErr)
    {
        //����uiMapOffset��uiMapLength������ִ��mmap()������pFbEntry
        pFbmapObj->uiMapOffset = fb_fix.smem_start & (sysconf(_SC_PAGESIZE) - 1);
        pFbmapObj->uiMapLength = fb_fix.smem_len + pFbmapObj->uiMapOffset;
        pFbmapObj->pFbEntry = mmap(NULL, pFbmapObj->uiMapLength, 
                                   PROT_READ|PROT_WRITE, MAP_SHARED, 
                                   pFbmapObj->iDevFd, pFbmapObj->uiMapOffset);
        if (pFbmapObj->pFbEntry == MAP_FAILED)
        {
            iErr = -5;
        }
    }

    if (!iErr)
    {
        //���֡����ӳ��������������Ƿ��ܹ�֧��
        if ((fb_var.bits_per_pixel != 8) && 
            (fb_var.bits_per_pixel != 16) && 
            (fb_var.bits_per_pixel != 24) && 
            (fb_var.bits_per_pixel != 32))
        {
            iErr = -6;
        }
        //�����������Ϊ16λ��֡����ӳ����󣬼������Ƿ�ΪRGB565
        if (16 == fb_var.bits_per_pixel)
        {
            if ((fb_var.red.length != 5) || 
                (fb_var.red.offset != 11) ||
                (fb_var.green.length != 6) || 
                (fb_var.green.offset != 5) ||
                (fb_var.blue.length != 5) ||
                (fb_var.blue.offset != 0))
            {
                iErr = -6;
            }
        }
        //ȷ��������ʾ�ķֱ���С��֡����ֱ���
        if ((uiHorDisp > fb_var.xres) || 
            (uiVerDisp > fb_var.yres))
        {
            iErr = -6;
        }
    }

    if (!iErr)
    {
        //֡����ӳ���������ϵͳ��صĲ��ֳ�Ա��ֵ
        pFbmapObj->uiBufSize = fb_fix.smem_len;
        pFbmapObj->uiPixelBits = fb_var.bits_per_pixel;
        pFbmapObj->uiRedBits = fb_var.red.length;
        pFbmapObj->uiRedShift = fb_var.red.offset;
        pFbmapObj->uiGreenBits = fb_var.green.length;
        pFbmapObj->uiGreenShift = fb_var.green.offset;
        pFbmapObj->uiBlueBits = fb_var.blue.length;
        pFbmapObj->uiBlueShift = fb_var.blue.offset;
        pFbmapObj->uiHorRes = fb_var.xres;
        pFbmapObj->uiVerRes = fb_var.yres;
        //��uiHorDisp��uiVerDisp�������ã�������uiHorOff��uiVerOff
        pFbmapObj->uiHorDisp = uiHorDisp;
        pFbmapObj->uiVerDisp = uiVerDisp;
        pFbmapObj->uiHorOff = (pFbmapObj->uiHorRes - uiHorDisp) / 2;
        pFbmapObj->uiVerOff= (pFbmapObj->uiVerRes - uiVerDisp) / 2;
        //iSyncFlag��ʼ��Ϊ0��������iDevType��ֵ��pMapBuff��������
        pFbmapObj->iSyncFlag = 0;
        switch (iDevType)
        {
        case GUI_FBTYP_STD:
            pFbmapObj->pMapBuff = pFbmapObj->pFbEntry;
            break;
        case GUI_FBTYP_DUAL:
        case GUI_FBTYP_CUST:
            pFbmapObj->pMapBuff = malloc(pFbmapObj->uiBufSize);
            if (NULL == pFbmapObj->pMapBuff)
            {
                iErr = -7;
            }
            break;
        default:
            iErr = -7;
            break;
        }
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    if (!iErr)
    {
        //�����½�֡����ӳ������fnFbThread�������Գ�ʼ��Mutex
        pFbmapObj->fnFbThread = fnFbThread;
        if (InitMutex(&(pFbmapObj->Mutex), NULL))
        {
            iErr = -8;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:munmap(),close()
    //������
    switch (iErr)
    {
    case -8:
        if (iDevType == GUI_FBTYP_DUAL)
        {
            free(pFbmapObj->pMapBuff);
        }
        //no break
    case -7:
    case -6:
        munmap(pFbmapObj->pFbEntry, pFbmapObj->uiMapLength);
        //no break
    case -5:
    case -4:
        close(pFbmapObj->iDevFd);
        //no break
    case -3:
        free(pFbmapObj);
        //no break
    case -2:
    case -1:
        pFbmapObj = NULL;
        //no break
    default:
        break;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return pFbmapObj;
}


/***
  * ���ܣ�
        ɾ��֡����ӳ�����
  * ������
        1.GUIFBMAP **ppFbmapObj:    ָ���ָ�룬ָ����Ҫ���ٵ�֡����ӳ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyFbmap(GUIFBMAP **ppFbmapObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppFbmapObj�Ƿ���Ч
        if (NULL == ppFbmapObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppFbmapObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppFbmapObj)
        {
            iErr = -2;
        }
    }

  #if (GUI_OS_ENV == LINUX_OS)  //OS���:munmap(),close()
    if (!iErr)
    {
        //�ͷ����뻺��
        if ((*ppFbmapObj)->iDevType == GUI_FBTYP_DUAL)
        {
            free((*ppFbmapObj)->pMapBuff);
        }
        //�����ڴ�ӳ��
        if (munmap((*ppFbmapObj)->pFbEntry, (*ppFbmapObj)->uiMapLength))
        {
            iErr = -3;
        }
        //�ر��豸
        if (close((*ppFbmapObj)->iDevFd))   //�豸�ļ�Ϊ������Դ������֤����ֵ
        {
            iErr = -4;
        }
        //����֡����ӳ����󣬲���ָ���ÿ�
        free(*ppFbmapObj);
        *ppFbmapObj = NULL;
    }
  #else
  #error "Unknown GUI_OS_ENV, not supported current GUI_OS_ENV!"
  #endif    //GUI_OS_ENV == LINUX_OS

    return iErr;
}


/***
  * ���ܣ�
        �õ���ǰ֡����ӳ�����
  * ������
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIFBMAP* GetCurrFbmap(void)
{
    return pCurrFbmap;
}


/***
  * ���ܣ�
        ���õ�ǰ֡����ӳ�����
  * ������
        1.GUIFBMAP *pFbmapObj:  ������Ϊ��ǰ֡����ӳ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetCurrFbmap(GUIFBMAP *pFbmapObj)
{
    //�ж�pFbmapObj�Ƿ���Ч
    if (NULL == pFbmapObj)
    {
        return -1;
    }

    pCurrFbmap = pFbmapObj;

    return 0;
}


/***
  * ���ܣ�
        ����֡����ӳ���ͬ����־
  * ������
        1.int iSyncFlag:        ���뻺����Ҫͬ��ˢ��ʱ��ͬ����־λ
        2.GUIFBMAP *pFbmapObj:  ��Ҫ����ͬ����־��֡����ӳ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ������еĻ��������������ڳ�������ǰ���µ���
***/
int SetFbmapSync(int iSyncFlag, GUIFBMAP *pFbmapObj)
{
    //����
    MutexLock(&(pFbmapObj->Mutex));

    //�ж�pFbmapObj�Ƿ���Ч
    if (NULL == pFbmapObj)
    {
        return -1;
    }

    //����ͬ����־λ
    pFbmapObj->iSyncFlag = iSyncFlag;

    //����
    MutexUnlock(&(pFbmapObj->Mutex));

    return 0;
}


/***
  * ���ܣ�
        Ĭ��֡�����߳���ں���
  * ������
        1.void *pThreadArg:     �߳���ں�������������Ϊ(GUIFBMAP *)
  * ���أ�
        �����߳̽���װ̬
  * ��ע��
***/
void* DefaultFbThread(void *pThreadArg)
{
    //�����־������ֵ����
    int iErr = 0;
    static int iReturn = 0;
    //��ʱ��������
    int iExit = 0;
    GUIFBMAP *pFbmapObj = pThreadArg;

    while (!iExit)
    {
        //���ݽ�����־�ж��Ƿ���Ҫ����֡�����߳�
        iExit = GetExitFlag();
        if (iExit)
        {
            break;
        }

        //���ͬ��ˢ�����뻺��
        switch (pFbmapObj->iDevType)
        {
        case GUI_FBTYP_STD:
            iErr = StandardFbmapProcess(pFbmapObj);
            break;
        case GUI_FBTYP_DUAL:
            iErr = DualFbmapProcess(pFbmapObj);
            break;
        case GUI_FBTYP_CUST:
            iErr = CustomFbmapProcess(pFbmapObj);
            break;
        default:
            break;
        }

        //����Ϊ-1����ʾ��֡�������ݿ�ˢ�£�˯��50����
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
        ��׼����֡����Ĵ��������������֡�����̵߳Ĵ���
  * ������
        1.GUIFBMAP *pFbmapObj:  ������Ҫ�����֡�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ��֡�������ݿ�ˢ��                    
***/
int StandardFbmapProcess(GUIFBMAP *pFbmapObj)
{
    //�����־������ֵ����
    int iErr = 0;

    //����
    MutexLock(&(pFbmapObj->Mutex));

    //��׼����֡���岻�����κδ���
    if (pFbmapObj->iSyncFlag)
    {
        pFbmapObj->iSyncFlag = 0;
    }
    else
    {
        iErr = -1;
    }

    //����
    MutexUnlock(&(pFbmapObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        ˫��������֡����Ĵ��������������֡�����̵߳Ĵ���
  * ������
        1.GUIFBMAP *pFbmapObj:  ������Ҫ�����֡�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ��֡�������ݿ�ˢ��                    
***/
int DualFbmapProcess(GUIFBMAP *pFbmapObj)
{
    //�����־������ֵ����
    int iErr = 0;

    //����
    MutexLock(&(pFbmapObj->Mutex));

    //�ж��Ƿ���Ҫͬ��ˢ�����뻺��
    if (pFbmapObj->iSyncFlag)
    {
        //���˫��������֡�����ͬ��
        memcpy(pFbmapObj->pFbEntry, pFbmapObj->pMapBuff, pFbmapObj->uiBufSize);
        pFbmapObj->iSyncFlag = 0;
    }
    else
    {
        iErr = -1;
    }

    //����
    MutexUnlock(&(pFbmapObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �Զ�������֡����Ĵ��������������֡�����̵߳Ĵ���
  * ������
        1.GUIFBMAP *pFbmapObj:  ������Ҫ�����֡�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����-1��ʾ��֡�������ݿ�ˢ��                    
***/
int CustomFbmapProcess(GUIFBMAP *pFbmapObj)
{
    //�����־������ֵ����
    int iErr = 0;

    //�����豸����㺯������Զ�������֡����Ĵ���
    iErr = CustomFbmapFunc(pFbmapObj);

    return iErr;
}

