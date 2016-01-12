/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guipen.h
* ժ    Ҫ��  ����GUI�Ļ������ͼ�������ΪGUI��ͼģ���ʵ���ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_PEN_H
#define _GUI_PEN_H


/***********************************
* Ϊ����GUIPEN����Ҫ���õ�����ͷ�ļ�
***********************************/
#include "guibase.h"


/******************
* ����GUI�л�������
******************/
#define GUIPEN_TYP_SOLID        1   //ʵ�߻���
#define GUIPEN_TYP_DASHED       2   //���߻���


/******************
* ����GUI�л��ʽṹ
******************/
typedef struct _pen
{
    int iPenType;               //�������ͣ�Ŀǰֻ֧��ʵ�߻���
    int iPenWidth;              //���ʿ�ȣ�Ŀǰֻ֧�ֿ��Ϊ1

    unsigned int uiPenColor;    //������ɫ��RGB888��ʽ
} GUIPEN;


/**********************************
* ����GUI���뻭��������صĲ�������
**********************************/
//����ָ������Ϣֱ�ӽ������ʶ���
GUIPEN* CreatePen(int iPenType, int iPenWidth, unsigned int uiPenColor);
//ɾ�����ʶ���
int DestroyPen(GUIPEN **ppPenObj);

//�õ���ǰ�Ļ��ʶ���
GUIPEN* GetCurrPen(void);
//���õ�ǰ�Ļ��ʶ���
int SetCurrPen(GUIPEN *pPenObj);

//���û��ʵ���ɫ
int SetPenColor(unsigned int uiPenColor, GUIPEN *pPenObj);


#endif  //_GUI_PEN_H

