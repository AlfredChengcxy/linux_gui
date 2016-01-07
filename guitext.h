/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guitext.h
* ժ    Ҫ��  ����GUI���ı����ͼ�������������GUI�������ı��������������ΪGUIͼ
*             �οؼ���ʵ���ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_TEXT_H
#define _GUI_TEXT_H


/************************************
* Ϊ����GUITEXT����Ҫ���õ�����ͷ�ļ�
************************************/
#include "guibase.h"
#include "guifont.h"


/******************
* ����GUI���ı��ṹ
******************/
typedef struct _text
{
    unsigned int uiTextLength;      //�ı����ȣ����ı����ַ��ĸ���������'\0'
    unsigned short *pTextData;      //�ı����ݣ���'\0'��β

    unsigned int uiPlaceX;          //�ı�ˮƽ����λ�ã������Ͻ�Ϊ���㣬�������
    unsigned int uiPlaceY;          //�ı���ֱ����λ�ã������Ͻ�Ϊ���㣬�������
    unsigned int uiViewWidth;       //��ʾ��ȣ�>=0����ʼ��Ϊ0���ı�ʵ�ʿ��
    unsigned int uiViewHeight;      //��ʾ�߶ȣ�>=0����ʼ��Ϊ0���ı�ʵ�ʸ߶�

    GUIFONT_MATRIX **ppTextMatrix;  //�ı�����Ӧ�ĵ�����Դ���
} GUITEXT;


/**********************************
* ����GUI�����ı�������صĲ�������
**********************************/
//����ָ������Ϣֱ�ӽ����ı�����
GUITEXT* CreateText(unsigned short *pTextData, 
                    unsigned int uiPlaceX, unsigned int uiPlaceY);
//ɾ���ı�����
int DestroyText(GUITEXT **ppTextObj);

//ֱ�����ָ�����ı�
int DisplayText(GUITEXT *pTextObj);

//�����ı�������
int SetTextData(unsigned short *pTextData, GUITEXT *pTextObj);
//�����ı��ķ���λ��
int SetTextPlace(unsigned int uiPlaceX, unsigned int uiPlaceY, 
                  GUITEXT *pTextObj);
//�����ı�����ʾ��С
int SetTextView(unsigned int uiViewWidth, unsigned int uiViewHeight, 
                GUITEXT *pTextObj);

//װ���ı�������Դ
int LoadTextMatrix(GUITEXT *pTextObj);
//ж���ı�������Դ
int UnloadTextMatrix(GUITEXT *pTextObj);


#endif  //_GUI_TEXT_H

