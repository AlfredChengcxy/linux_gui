/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guibrush.c
* ժ    Ҫ��  ʵ��GUI�Ļ�ˢ���ͼ�������ΪGUI��ͼģ���ʵ���ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guibrush.h"


/*************************************
* Ϊʵ��GUIBRUSH����Ҫ���õ�����ͷ�ļ�
*************************************/
//#include ""


/********************
* GUI�еĵ�ǰ��ˢ����
********************/
static GUIBRUSH *pCurrBrush = NULL;


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӽ�����ˢ����
  * ������
        1.int iBrushType:   ָ��Ҫ�����Ļ�ˢ����
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIBRUSH* CreateBrush(int iBrushType)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIBRUSH *pBrushObj = NULL;

    if (!iErr)
    {
        //����Ϊ��ˢ��������ڴ�
        pBrushObj = (GUIBRUSH *) malloc(sizeof(GUIBRUSH));
        if (NULL == pBrushObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //��ˢ�����Ա��ֵ
        pBrushObj->iBrushType = iBrushType;
        pBrushObj->uiFgColor = COLOR_TRANS; //ȫ͸����ʾǰ����ɫ��Ч
        pBrushObj->uiBgColor = COLOR_TRANS; //ȫ͸����ʾ������ɫ��Ч
    }

    return pBrushObj;
}


/***
  * ���ܣ�
        ɾ����ˢ����
  * ������
        1.GUIBRUSH **ppBrushObj:    ָ���ָ�룬ָ����Ҫ���ٵĻ�ˢ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int DestroyBrush(GUIBRUSH **ppBrushObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppBrushObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppBrushObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppBrushObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppBrushObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //���ٻ�ˢ���󣬲���ָ���ÿ�
        free(*ppBrushObj);
        *ppBrushObj = NULL;
    }

    return iErr;
}


/***
  * ���ܣ�
        �õ���ǰ�Ļ�ˢ����
  * ������
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIBRUSH* GetCurrBrush(void)
{
    return pCurrBrush;
}


/***
  * ���ܣ�
        ���õ�ǰ�Ļ�ˢ����
  * ������
        1.GUIBRUSH *pBrushObj:  ������Ϊ��ǰ��ˢ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetCurrBrush(GUIBRUSH *pBrushObj)
{
    //�ж�pBrushObj�Ƿ���Ч
    if (NULL == pBrushObj)
    {
        return -1;
    }

    pCurrBrush = pBrushObj;

    return 0;
}


/***
  * ���ܣ�
        ���û�ˢ��ǰ������ɫ
  * ������
        1.unsigned int uiFgColor:   ��ˢǰ����ɫֵ����ˢ����Ϊ��ɫ��ˢʱʹ��
        2.unsigned int uiBgColor:   ��ˢ������ɫֵ����ˢ����Ϊ��ɫ��ˢʱʹ��
        3.GUIBRUSH *pBrushObj:      ��Ҫ����ǰ�����Ļ�ˢ����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetBrushColor(unsigned int uiFgColor, unsigned int uiBgColor, 
                  GUIBRUSH *pBrushObj)
{
    //�ж�pBrushObj�Ƿ���Ч
    if (NULL == pBrushObj)
    {
        return -1;
    }

    //����ǰ������ɫ
    pBrushObj->uiFgColor = uiFgColor;
    pBrushObj->uiBgColor = uiBgColor;

    return 0;
}

