/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  wnd_frminit.h
* ժ    Ҫ��  ������ʼ������frminit�Ĵ��崦���̼߳���ز�������
*
* ��ǰ�汾��  v1.1.0
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _WND_FRMINIT_H
#define _WND_FRMINIT_H


/****************************
* Ϊʹ��GUI����Ҫ���õ�ͷ�ļ�
****************************/
#include "guiglobal.h"


/*********************
* �������崦����غ���
*********************/
//����frminit�ĳ�ʼ����������������ؼ���ע����Ϣ����
int FrmInitInit(void *pWndObj);
//����frminit���˳��������ͷ�������Դ
int FrmInitExit(void *pWndObj);
//����frminit�Ļ��ƺ�����������������
int FrmInitPaint(void *pWndObj);
//����frminit��ѭ�����������д���ѭ��
int FrmInitLoop(void *pWndObj);
//����frminit�Ĺ����������д������ǰԤ����
int FrmInitPause(void *pWndObj);
//����frminit�Ļָ����������д���ָ�ǰԤ����
int FrmInitResume(void *pWndObj);


#endif  //_WND_FRMLOGO_H

