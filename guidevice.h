/*******************************************************************************
* Copyright(c) 2012 ,һŵ����(����)���޹�˾�Ϻ��з��� 
*
* All rights reserved
*
* �ļ����ƣ�  guidevice.h
* ժ    Ҫ��  ����GUI��������/����豸���û��Զ������������ΪGUI��ʹ�õ���Щ��
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
    
#ifndef _GUI_DEVICE_H
#define _GUI_DEVICE_H


/**************************************
* Ϊ����GUIDEVICE����Ҫ���õ�����ͷ�ļ�
**************************************/
#include "guibase.h"
#include "guifbmap.h"
#include "guikeypad.h"
#include "guitouch.h"


/********************************
* ����GUI��ʹ�õ���������豸�ļ�
* ע���������������ʵ������޸�
********************************/
#define DEVFILE_FB      "/dev/fb0"
#define DEVFILE_KEYPAD  "/dev/keyb0"
#define DEVFILE_TOUCH   "/dev/event2"


/********************************
* ����GUI�е�ǰʹ�õİ���ӳ����ֵ
* ע���������������ʵ������޸�
********************************/
#define KEYCODE_MENU        1
#define KEYCODE_F1          2
#define KEYCODE_F2          3
#define KEYCODE_F3          4
#define KEYCODE_F4          5
#define KEYCODE_F5          6
#define KEYCODE_ESC         7
#define KEYCODE_FILE        8
#define KEYCODE_SCALE       9
#define KEYCODE_SETUP       10
#define KEYCODE_UP          11
#define KEYCODE_LEFT        12
#define KEYCODE_ENTER       13
#define KEYCODE_RIGHT       14
#define KEYCODE_DOWN        15
#define KEYCODE_REALT       16
#define KEYCODE_KNOB        17
#define KEYCODE_AVG         18


/***********************************************
* ����GUI�л�������/����豸���û��Զ����������
* ע�����º����е����������ʵ�������д
***********************************************/
//�û��Զ����֡���崦��������������Զ�������֡����Ĵ���
int CustomFbmapFunc(GUIFBMAP *pFbmapObj);
//�û��Զ���ļ��̴���������������Զ������ͼ��̵Ĵ���
int CustomKeypadFunc(GUIKEYPAD *pKeypadObj);
//�û��Զ���Ĵ���������������������Զ������ʹ������Ĵ���
int CustomTouchFunc(GUITOUCH *pTouchObj);

#endif  //_GUI_DEVICE_H

