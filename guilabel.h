/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guilabel.h
* ժ    Ҫ��  ����GUI�ı�ǩ���ͼ�������Ϊʵ�ֱ�ǩ�ؼ��ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_LABEL_H
#define _GUI_LABEL_H


/*************************************
* Ϊ����GUILABEL����Ҫ���õ�����ͷ�ļ�
*************************************/
#include "guibase.h"
#include "guibrush.h"
#include "guipen.h"
#include "guifont.h"
#include "guitext.h"


/****************************************
* ����GUI�б�ǩ��������֧�ֵ��ı����뷽ʽ
****************************************/
#define GUILABEL_ALIGN_LEFT         0   //��ǩ�ı��������
#define GUILABEL_ALIGN_RIGHT        1   //��ǩ�ı����Ҷ���
#define GUILABEL_ALIGN_CENTER       2   //��ǩ�ı����ж���


/******************
* ����GUI�б�ǩ�ṹ
******************/
typedef struct _label
{
    GUIVISIBLE Visible;         //������Ϣ���κδ���ؼ������뽫����Ϊ��һ����Ա

    GUIPEN *pLblPen;            //��ǩʹ�õĻ��ʣ�ΪNULL��ʹ��GUI�еĵ�ǰ����
    GUIBRUSH *pLblBrush;        //��ǩʹ�õĻ�ˢ��ΪNULL��ʹ��GUI�еĵ�ǰ��ˢ
    GUIFONT *pLblFont;          //��ǩʹ�õ����壬ΪNULL��ʹ��GUI�еĵ�ǰ����

    int iLblAlign;              //��ǩ�ı����뷽ʽ��0����1���ң�2���У�Ĭ��0
    GUITEXT *pLblText;          //��ǩ����Ӧ���ı���Դ
} GUILABEL;


/**********************************
* ����GUI�����ǩ������صĲ�������
**********************************/
//����ָ������Ϣֱ�ӽ�����ǩ����
GUILABEL* CreateLabel(unsigned int uiPlaceX, unsigned int uiPlaceY, 
                      unsigned int uiLblWidth, unsigned int uiLblHeight, 
                      unsigned short *pTextData);
//ɾ����ǩ����
int DestroyLabel(GUILABEL **ppLblObj);

//ֱ�����ָ���ı�ǩ
int DisplayLabel(GUILABEL *pLblObj);

//���ñ�ǩ����Ч����
int SetLabelArea(unsigned int uiStartX, unsigned int uiStartY, 
                 unsigned int uiEndX, unsigned int uiEndY, 
                 GUILABEL *pLblObj);
//���ñ�ǩ�Ŀɼ���
int SetLabelEnable(int iEnable, GUILABEL *pLblObj);
//���ñ�ǩ��ʹ�õĻ�ˢ
int SetLabelBrush(GUIBRUSH *pLblBrush, GUILABEL *pLblObj);
//���ñ�ǩ��ʹ�õĻ���
int SetLabelPen(GUIPEN *pLblPen, GUILABEL *pLblObj);
//���ñ�ǩ����Ӧ������
int SetLabelFont(GUIFONT *pLblFont, GUILABEL *pLblObj);
//���ñ�ǩ�ı��Ķ��뷽ʽ
int SetLabelAlign(int iLblAlign, GUILABEL *pLblObj);
//���ñ�ǩ����Ӧ���ı���Դ
int SetLabelText(unsigned short *pTextData, GUILABEL *pLblObj);


#endif  //_GUI_LABEL_H

