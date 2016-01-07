/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guibrush.h
* ժ    Ҫ��  ����GUI�Ļ�ˢ���ͼ�������ΪGUI��ͼģ���ʵ���ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_BRUSH_H
#define _GUI_BRUSH_H


/*************************************
* Ϊ����GUIBRUSH����Ҫ���õ�����ͷ�ļ�
*************************************/
#include "guibase.h"


/******************
* ����GUI�л�ˢ����
******************/
#define GUIBRUSH_TYP_SOLID      1   //��ɫ��ˢ
#define GUIBRUSH_TYP_IMAGE      2   //ͼ��ˢ


/******************
* ����GUI�л�ˢ�ṹ
******************/
typedef struct _brush
{
    int iBrushType;         //��ˢ���ͣ�Ŀǰֻ֧�ִ�ɫ��ˢ

    unsigned int uiFgColor; //��ˢǰ����ɫ��RGB888��ʽ
    unsigned int uiBgColor; //��ˢ������ɫ��RGB888��ʽ
} GUIBRUSH;


/**********************************
* ����GUI���뻭ˢ������صĲ�������
**********************************/
//����ָ������Ϣֱ�ӽ�����ˢ����
GUIBRUSH* CreateBrush(int iBrushType);
//ɾ����ˢ����
int DestroyBrush(GUIBRUSH **ppBrushObj);

//�õ���ǰ�Ļ�ˢ����
GUIBRUSH* GetCurrBrush(void);
//���õ�ǰ�Ļ�ˢ����
int SetCurrBrush(GUIBRUSH *pBrushObj);

//���û�ˢ��ǰ������ɫ
int SetBrushColor(unsigned int uiFgColor, unsigned int uiBgColor, 
                  GUIBRUSH *pBrushObj);


#endif  //_GUI_BRUSH_H

