/*******************************************************************************
* Copyright(c) 2012 ,һŵ����(����)���޹�˾�Ϻ��з��� 
*
* All rights reserved
*
* �ļ����ƣ�  guidevice.c
* ժ    Ҫ��  ʵ��GUI��������/����豸���û��Զ������������ΪGUI��ʹ�õ���Щ��
*             ���ṩ�豸����㡣
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/
    
#include "guidevice.h"
    
    
/**************************************
* Ϊʵ��GUIDEVICE����Ҫ���õ�����ͷ�ļ�
**************************************/
#include "guievent.h"


/***
  * ���ܣ�
        �û��Զ����֡���崦��������������Զ�������֡����Ĵ���
  * ������
        1.GUIFBMAP *pFbmapObj:  ��������֡�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        1.���뷵��-1��ʾ��֡�������ݿ�ˢ��                    
        2.�����ʵ������޸Ĵ��� 
***/
int CustomFbmapFunc(GUIFBMAP *pFbmapObj)
{
    //�����־������ֵ����
    int iErr = 0;

    //����
    //���������޸ı��δ���
    MutexLock(&(pFbmapObj->Mutex));

    if (pFbmapObj->iSyncFlag)
    {
        //�˶θ���ʵ����������Ӧ����
        //...
        pFbmapObj->iSyncFlag = 0;
    }
    else
    {
        iErr = -1;
    }

    //����
    //���������޸ı��δ���
    MutexUnlock(&(pFbmapObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �û��Զ���ļ��̴���������������Զ������ͼ��̵Ĵ���
  * ������
        1.GUIKEYPAD *pKeypadObj:    �������ļ��̶���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        1.���뷵��-1��ʾ�޼������ݿɶ�
        2.�����ʵ������޸Ĵ��� 
***/
int CustomKeypadFunc(GUIKEYPAD *pKeypadObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    int iTmp;
    unsigned int uiKeyValue;
    GUIEVENT_ITEM *pEventItem = NULL;
    GUIEVENT *pEventObj = NULL;
    
    //����
    //���������޸ı��δ���
    MutexLock(&(pKeypadObj->Mutex));

    if (!iErr)
    {
        //��ȡ���̷��ص�����
        //�˶θ���ʵ����������Ӧ����
        ThreadTestcancel();
        iTmp = read(pKeypadObj->iDevFd, &uiKeyValue, sizeof(uiKeyValue));
        ThreadTestcancel();
        if (iTmp != sizeof(uiKeyValue))
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //����Ϊ�����¼�������ڴ�
        //���������޸ı��δ���
        pEventItem = (GUIEVENT_ITEM *) malloc(sizeof(GUIEVENT_ITEM));
        if (NULL == pEventItem)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����GUIEVENT_ITEM
        //�˶θ���ʵ����������Ӧ����
        pEventItem->uiEventType = GUIEVENT_TYP_IN;
        if (uiKeyValue & 0x000F0000)    //bit19~bit16:0=��ť��1=����
        {
            pEventItem->uiEventCode = (uiKeyValue & 0x00000F00) ?
                                      GUIEVENT_KEY_UP : GUIEVENT_KEY_DOWN;
            pEventItem->uiEventValue = uiKeyValue & 0x000000FF;
        }
        else
        {
            pEventItem->uiEventCode = (uiKeyValue & 0x0F000000) ?
                                      GUIEVENT_KNB_ANTI : GUIEVENT_KNB_CLOCK;
            pEventItem->uiEventValue = uiKeyValue & 0x000000FF;
        }
        //�¼���д���¼�����
        //���������޸ı��δ���
        pEventObj = GetCurrEvent();
        if (WriteEventQueue(pEventItem, pEventObj))
        {
            iErr = -3;
        }
    }

    //������
    //�˶θ���ʵ����������Ӧ����
    switch (iErr)
    {
    case -3:
        free(pEventItem);
        //no break
    case -2:
    case -1:
    default:
        break;
    }

    //����
    //���������޸ı��δ���
    MutexUnlock(&(pKeypadObj->Mutex));

    return iErr;
}


/***
  * ���ܣ�
        �Զ���Ĵ�������������������ɴ������̵߳Ĵ���
  * ������
        1.GUIKEYPAD *pTouchObj:    �������ļ��̶���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int CustomTouchFunc(GUITOUCH *pTouchObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    static int iPrevX = -1, iPrevY = -1; 
    struct input_event Event[5];
    int iLen, iTouchAct, iAbsX, iAbsY, iTmp;
    GUIEVENT_ITEM *pEventItem = NULL;
    GUIEVENT *pEventObj = NULL;

    if (iErr == 0)
    {
        //��ȡ���������ص�����
        ThreadTestcancel();
        iLen = read(pTouchObj->iDevFd, Event, sizeof(Event));
        ThreadTestcancel();
        if ( (iLen < sizeof(struct input_event)) || (iLen < 0))
        {
            iErr = -1;
        }
    }
    if (iErr == 0)
    {
        //��ʼ������������־������ֵ��־
        iTouchAct = -1;
        iAbsX = -1;
        iAbsY = -1;
        //�Ӷ�ȡ��������Ѱ�Ҵ�������������ֵ
        iLen /= sizeof(struct input_event);
        for (iTmp = 0; iTmp < iLen; iTmp++)
        {
            //�ҵ������������޸Ĵ���������־
            if (Event[iTmp].type == EV_KEY)         //����Ϊ����
            {
                if (Event[iTmp].code == BTN_TOUCH)  //����Ϊ��������
                {
                    iTouchAct = Event[iTmp].value;  //�õ���������
                }
            }
            //�ҵ�����ֵ���޸�����ֵ��־
            if (Event[iTmp].type == EV_REL)         //����Ϊ����ֵ
            {
                if (Event[iTmp].code == REL_X)      //����Ϊ������
                {
                    iAbsX = Event[iTmp].value;      //�õ�������ֵ
                }
                if (Event[iTmp].code == REL_Y)      //����Ϊ������
                {
                    iAbsY = Event[iTmp].value;      //�õ�������ֵ
                }
            }
            //�õ������������ֱ�Ӻ���(������������ɺ�������ֵ������)
            if (iTouchAct == 1)
            {
                iTouchAct = -1;                     //���ô���������־
            }
            //�õ��뿪���������������ֵ�������¼���
            if ((iTouchAct == 0) || 
                (iAbsX >= 0 && iAbsY >= 0))
            {
                //����Ϊ�������¼�������ڴ�
                pEventItem = (GUIEVENT_ITEM *) malloc(sizeof(GUIEVENT_ITEM));
                if (NULL == pEventItem)
                {
                    iErr = -2;
                    break;
                }
                //����GUIEVENT_ITEM
                pEventItem->uiEventType = GUIEVENT_TYP_IN;
                if (iTouchAct == 0)                 //�뿪������
                {
                    pEventItem->uiEventCode = GUIEVENT_ABS_UP;
                    pEventItem->uiEventValue = (iPrevX << 16) | iPrevY;
                    iTouchAct = -1;                 //���ô���������־               
                }
                if (iAbsX >= 0 && iAbsY >= 0)       //��������ֵ
                {
                    pEventItem->uiEventCode = GUIEVENT_ABS_DOWN;
                    pEventItem->uiEventValue = (iAbsX << 16) | iAbsY;
                    iPrevX = iAbsX;                 //���������
                    iPrevY = iAbsY;                 //����������
                    iAbsX = -1;                     //���ú������־
                    iAbsY = -1;                     //�����������־
                }
				
				//if(g_ucKeyEnable)
				if(1)
				{
		            //�¼���д���¼�����
	                pEventObj = GetCurrEvent();

	                if (WriteEventQueue(pEventItem, pEventObj))
	                {
		                    iErr = -3;
	                    break;
	                }
				}
  
            }
        }
    }

    //������
    switch (iErr)
    {
    case -3:
        MutexUnlock(&(pEventObj->Mutex));
        free(pEventItem);
    case -2:
    case -1:
    default:
        break;
    }

    return iErr;
}

