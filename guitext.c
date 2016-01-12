/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guitext.c
* ժ    Ҫ��  ʵ��GUI���ı����ͼ����������������ı��������������ΪGUIͼ�οؼ���
*             ʵ���ṩ����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guitext.h"


/************************************
* Ϊʵ��GUITEXT����Ҫ���õ�����ͷ�ļ�
************************************/
#include "guiimage.h"


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӽ����ı�����
  * ������
        1.unsigned short *pTextData:    ���ڽ����ı�������ı�����(���ַ�)
        2.unsigned int uiPlaceX:        �ı�ˮƽ����λ�ã������Ͻ�Ϊ����
        3.unsigned int uiPlaceY:        �ı���ֱ����λ�ã������Ͻ�Ϊ����
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUITEXT* CreateText(unsigned short *pTextData, 
                    unsigned int uiPlaceX, unsigned int uiPlaceY)
{
    //�����־������ֵ����
    int iErr = 0;
    GUITEXT *pTextObj = NULL;
    //��ʱ��������
    unsigned int uiSize;

    if (!iErr)
    {
        //�ж�pTextData�Ƿ�Ϊ��Чָ��
        if (NULL == pTextData)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�����ڴ���Դ
        pTextObj = (GUITEXT *) malloc(sizeof(GUITEXT));
        if (NULL == pTextObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //�õ��ı�����
        pTextObj->uiTextLength = 0;
        pTextObj->pTextData = pTextData;
        while (*(pTextObj->pTextData))              //�ı����ݣ���'\0'��β
        {
            pTextObj->uiTextLength++;
            pTextObj->pTextData++;
        }
        //Ϊ�����ı����ݷ����ڴ���Դ
        uiSize = 2 * (pTextObj->uiTextLength + 1);  //�ı����Ȳ���'\0'
        pTextObj->pTextData = (unsigned short *) malloc(uiSize);
        if (NULL == pTextObj->pTextData)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //�ı������Ա��ֵ
        memcpy(pTextObj->pTextData, pTextData, uiSize);
        pTextObj->uiPlaceX = uiPlaceX;
        pTextObj->uiPlaceY = uiPlaceY;
        pTextObj->uiViewWidth = 0;      //Ĭ�ϰ��ı�ʵ�ʿ����ʾ
        pTextObj->uiViewHeight = 0;     //Ĭ�ϰ��ı�ʵ�ʸ߶���ʾ
        pTextObj->ppTextMatrix = NULL;
    }

    //������
    switch (iErr)
    {
    case -3:
        free(pTextObj);
        //no break
    case -2:
    case -1:
        pTextObj = NULL;
        //no break
    default:
        break;
    }

    return pTextObj;
}


/***
  * ���ܣ�
        ɾ���ı�����
  * ������
        1.GUITEXT **ppTextObj:  ָ���ָ�룬ָ����Ҫ���ٵ��ı�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyText(GUITEXT **ppTextObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppTextObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppTextObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppTextObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppTextObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����ı�������Դ��װ�أ�����ж���ı�������Դ
        if (NULL != (*ppTextObj)->ppTextMatrix)
        {
            if (UnloadTextMatrix(*ppTextObj))
            {
                iErr = -3;
            }
        }
    }

    if (!iErr)
    {
        //�ͷ���Դ
        free((*ppTextObj)->pTextData);
        //�����ı����󣬲���ָ���ÿ�
        free(*ppTextObj);
        *ppTextObj = NULL;
    }

    return iErr;
}


/***
  * ���ܣ�
        ֱ�����ָ�����ı�
  * ������
        1.GUITEXT *pTextObj:    �ı�ָ�룬����Ϊ��
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int DisplayText(GUITEXT *pTextObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIFONT *pFont = NULL;
    GUIIMAGE *pImg = NULL;
    GUIFONT_MATRIX **ppMatrix = NULL;
    unsigned int uiX, uiY, uiTmp;

    if (!iErr)
    {
        //�ж�pTextObj�Ƿ�Ϊ��Чָ��
        if (NULL == pTextObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //���ı�������Դδװ�أ�����װ���ı�������Դ
        if (NULL == pTextObj->ppTextMatrix)
        {
            if (LoadTextMatrix(pTextObj))
            {
                iErr = -2;
            }
        }
    }

    if (!iErr)
    {
        //�õ���ǰ��������ж��Ƿ�Ϊ��Чָ��
        pFont = GetCurrFont();
        if (NULL == pFont)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //����ı��и��ַ�����Ӧ�ĵ���
        ppMatrix = pTextObj->ppTextMatrix;
        uiX = pTextObj->uiPlaceX;
        uiY = pTextObj->uiPlaceY;
        for (uiTmp = 0; uiTmp < pTextObj->uiTextLength; uiTmp++)
        {
            //�ж��Ƿ����㹻�ռ���ʾ�ı��еĵ�ǰ�ַ�
            if ((uiX + ppMatrix[uiTmp]->uiRealWidth) > 
                (pTextObj->uiPlaceX + pTextObj->uiViewWidth))
            {
                uiX = pTextObj->uiPlaceX;
                uiY += ppMatrix[uiTmp]->uiRealHeight
                     + pFont->uiTopGap + pFont->uiBottomGap;
            }
            if ((uiY + ppMatrix[uiTmp]->uiRealHeight) > 
                (pTextObj->uiPlaceY + pTextObj->uiViewHeight))
            {
                iErr = -4;
                break;
            }
            //����Ϊ�������������1λɫͼ�����
            pImg = CreateImage(pFont->uiFontWidth, pFont->uiFontHeight, 1);
            if (NULL == pImg)
            {
                iErr = -5;
                break;
            }
            //����ͼ����Դ����ʾ��С��λ������ɫ������ʾͼ��(���������)
            memcpy(pImg->pImgData, 
                   ppMatrix[uiTmp]->pMatrixData, 
                   round_up(pFont->uiFontWidth, 8) / 8 * pFont->uiFontHeight);
            pImg->uiDispWidth = ppMatrix[uiTmp]->uiRealWidth;
            pImg->uiDispHeight = ppMatrix[uiTmp]->uiRealHeight;
            pImg->uiPlaceX = uiX;
            pImg->uiPlaceY = uiY;
            pImg->uiFgColor = pFont->uiFgColor;
            pImg->uiBgColor = pFont->uiBgColor;
            if (DisplayImage(pImg))
            {
                iErr = -6;
                break;
            }
            //����ͼ����Դ
            DestroyImage(&pImg);
            //�ƶ�����һ����ʾλ��
            uiX += ppMatrix[uiTmp]->uiRealWidth 
                 + pFont->uiLeftGap + pFont->uiRightGap;
        }
    }

    //������
    switch (iErr)
    {
    case -6:
        DestroyImage(&pImg);
        //no break
    case -5:
    case -4:
    case -3:
    case -2:
    case -1:
    default:
        break;
    }

    return iErr;
}


/***
  * ���ܣ�
        �����ı�������
  * ������
        1.unsigned short *pTextData:    �ı�����(���ַ�)����'\0'��β
        2.GUITEXT *pTextObj:            ��Ҫ�����ı����ݵ��ı�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetTextData(unsigned short *pTextData, GUITEXT *pTextObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    unsigned short *pData;
    unsigned int uiLen, uiSize;

    if (!iErr)
    {
        //�ж�pTextData��pTextObj�Ƿ���Ч
        if (NULL == pTextData || NULL == pTextObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //����ı�������Դ��װ�أ�����ж���ı�������Դ
        if (NULL != pTextObj->ppTextMatrix)
        {
            if (UnloadTextMatrix(pTextObj))
            {
                iErr = -2;
            }
        }
    }

    if (!iErr)
    {
        //�õ��ı�����
        pData = pTextData;
        uiLen = 0;
        while (*pData++)                //�ı����ݣ���'\0'��β
        {
            uiLen++;
        }
        //�����ڴ���Դ�������ı�����
        uiSize = 2 * (uiLen + 1);       //�ı����Ȳ���'\0'
        pData = (unsigned short *) malloc(uiSize);
        if (NULL != pData)
        {
            memcpy(pData, pTextData, uiSize);
        }
        else
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //�ͷžɵ��ı�����
        free(pTextObj->pTextData);
        //�����ı����Ⱥ��ı�����
        pTextObj->uiTextLength = uiLen;
        pTextObj->pTextData = pData;
        //�����ı�����ʾ��С
        pTextObj->uiViewWidth = 0;
        pTextObj->uiViewHeight = 0;
    }

    return iErr;
}


/***
  * ���ܣ�
        �����ı��ķ���λ��
  * ������
        1.unsigned int uiPlaceX:    �ı�ˮƽ����λ�ã������Ͻ�Ϊ���㣬��������
        2.unsigned int uiPlaceY:    �ı���ֱ����λ�ã������Ͻ�Ϊ���㣬��������
        3.GUITEXT *pTextObj:        ��Ҫ���÷���λ�õ��ı�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetTextPlace(unsigned int uiPlaceX, unsigned int uiPlaceY, 
                  GUITEXT *pTextObj)
{
    //�ж�pTextObj�Ƿ���Ч
    if (NULL == pTextObj)
    {
        return -1;
    }

    pTextObj->uiPlaceX = uiPlaceX;
    pTextObj->uiPlaceY = uiPlaceY;

    return 0;
}


/***
  * ���ܣ�
        �����ı�����ʾ��С
  * ������
        1.unsigned int uiViewWidth:     ��ʾ��ȣ�>=0����ʼ��Ϊ0���ı�ʵ�ʿ��
        2.unsigned int uiViewHeight:    ��ʾ�߶ȣ�>=0����ʼ��Ϊ0���ı�ʵ�ʸ߶�
        3.GUITEXT *pTextObj:            ��Ҫ������ʾ��С���ı�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetTextView(unsigned int uiViewWidth, unsigned int uiViewHeight, 
                GUITEXT *pTextObj)
{
    //�ж�pTextObj�Ƿ���Ч
    if (NULL == pTextObj)
    {
        return -1;
    }

    pTextObj->uiViewWidth = uiViewWidth;
    pTextObj->uiViewHeight = uiViewHeight;

    return 0;
}


/***
  * ���ܣ�
        װ���ı�������Դ
  * ������
        1.GUITEXT *pTextObj:    �ı�ָ�룬����Ϊ��
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int LoadTextMatrix(GUITEXT *pTextObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    unsigned int uiSize, uiWidth;
    GUIFONT *pFont = NULL;
    GUIFONT_MATRIX *pMatrix = NULL;

    if (!iErr)
    {
        //�ж�pTextObj�Ƿ�Ϊ��Чָ��
        if (NULL == pTextObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�жϵ�����Դ�Ƿ��Ѽ���
        if (NULL != pTextObj->ppTextMatrix)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����Ϊ�ı�����Ӧ�ĵ�����Դ�����ڴ棬ע���ڴ������0
        uiSize = pTextObj->uiTextLength * sizeof(GUIFONT_MATRIX **);
        pTextObj->ppTextMatrix = (GUIFONT_MATRIX **) calloc(uiSize, 1);
        if (NULL == pTextObj->ppTextMatrix)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ��������ж��Ƿ�Ϊ��Чָ��
        pFont = GetCurrFont();
        if (NULL == pFont)
        {
            iErr = -4;
        }
    }

    if (!iErr)
    {
        //�����ȡ������Դ���������ı�ʵ�ʿ��
        uiWidth = 0;
        for (uiSize = 0; uiSize < pTextObj->uiTextLength; uiSize++)
        {
            pMatrix = ExtractFontMatrix(pTextObj->pTextData[uiSize], pFont);
            if (NULL == pMatrix)
            {
                iErr = -5;
                break;
            }
            pTextObj->ppTextMatrix[uiSize] = pMatrix;
            uiWidth += pMatrix->uiRealWidth
                     + pFont->uiLeftGap + pFont->uiRightGap;;
        }
    }

    if (!iErr)
    {
        //ȷ���ı�Ҫ��ʾ�Ŀ����߶�
        if ((0 == pTextObj->uiViewWidth) ||     //Ϊ0��ʵ�ʿ����ʾ
            (pTextObj->uiViewWidth > uiWidth))  //������ʵ�ʿ����ʾ
        {
            pTextObj->uiViewWidth = uiWidth;
        }
        if (0 == pTextObj->uiViewHeight)        //Ϊ0��ʵ�ʸ߶���ʾ
        {
            pTextObj->uiViewHeight = pFont->uiFontHeight;
        }
    }

    //������
    switch (iErr)
    {
    case -5:
        for (uiSize = 0; uiSize < pTextObj->uiTextLength; uiSize++)
        {
            if (NULL != pTextObj->ppTextMatrix[uiSize])
            {
                free(pTextObj->ppTextMatrix[uiSize]->pMatrixData);
                free(pTextObj->ppTextMatrix[uiSize]);
                pTextObj->ppTextMatrix[uiSize] = NULL;
            }
        }
        //no break
    case -4:
    case -3:
    case -2:
    case -1:
    default:
        break;
    }

    return iErr;
}


/***
  * ���ܣ�
        ж���ı�������Դ
  * ������
        1.GUITEXT *pTextObj:    �ı�ָ�룬����Ϊ��
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int UnloadTextMatrix(GUITEXT *pTextObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    unsigned int uiLen;

    if (!iErr)
    {
        //�ж�pTextObj�Ƿ�Ϊ��Чָ��
        if (NULL == pTextObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�pTextObj�ĵ�����Դ�Ƿ��Ѽ���
        if (NULL == pTextObj->ppTextMatrix)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //����ͷ��������
        for (uiLen = 0; uiLen < pTextObj->uiTextLength; uiLen++)
        {
            if (NULL != pTextObj->ppTextMatrix[uiLen])
            {
                free(pTextObj->ppTextMatrix[uiLen]->pMatrixData);
                free(pTextObj->ppTextMatrix[uiLen]);
            }
        }
        //ж���ı�������Դ������ָ���ÿ�
        free(pTextObj->ppTextMatrix);
        pTextObj->ppTextMatrix = NULL;
    }

    return iErr;
}

