/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  wnd_frmmain.h
* ժ    Ҫ��  ����������frmmain�Ĵ��崦���̼߳���ز�������
*
* ��ǰ�汾��  v1.1.0
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _WND_FRMMAIN_H
#define _WND_FRMMAIN_H


/****************************
* Ϊʹ��GUI����Ҫ���õ�ͷ�ļ�
****************************/
#include "guiglobal.h"


/*********************
* �������崦����غ���
*********************/
//����frmmain�ĳ�ʼ����������������ؼ���ע����Ϣ����
int FrmMainInit(void *pWndObj);
//����frmmain���˳��������ͷ�������Դ
int FrmMainExit(void *pWndObj);
//����frmmain�Ļ��ƺ�����������������
int FrmMainPaint(void *pWndObj);
//����frmmain��ѭ�����������д���ѭ��
int FrmMainLoop(void *pWndObj);
//����frmmain�Ĺ����������д������ǰԤ����
int FrmMainPause(void *pWndObj);
//����frmmain�Ļָ����������д���ָ�ǰԤ����
int FrmMainResume(void *pWndObj);


#endif  //_WND_FRMMAIN_H

