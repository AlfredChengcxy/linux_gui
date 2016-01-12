/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guiglobal.h
* ժ    Ҫ��  ����GUI�Ĺ������ݡ������������������ṩ����GUI�����ĳ�ʼ�����á�
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_GLOBAL_H
#define _GUI_GLOBAL_H


/**************************************
* Ϊ����GUIGLOBAL����Ҫ���õ�����ͷ�ļ�
**************************************/
#include "guibase.h"
#include "guidevice.h"
#include "guifbmap.h"
#include "guikeypad.h"
#include "guitouch.h"
#include "guievent.h"
#include "guimessage.h"
#include "guischeduler.h"
#include "guipalette.h"
#include "guibrush.h"
#include "guipen.h"
#include "guifont.h"
#include "guidraw.h"
#include "guiimage.h"
#include "guibitmap.h"
#include "guitext.h"
#include "guilabel.h"
#include "guipicture.h"
#include "guiwindow.h"

#define MntSDcardDirectory "/mnt/sdcard/"

#define BmpFileDirectory MntSDcardDirectory"bitmap/wifi/"
#define FontFileDirectory MntSDcardDirectory"font/"

/**********************************
* ������GUI������ʼ����صĲ�������
**********************************/
//��ʼ��GUI����������GUI��Դ
int InitializeGUI(void);
//�ͷ�GUI������������Դ
int ReleaseGUI(void);


/***************************************
* �������ڷ����ض�������Ϣ�Ĺ�����������
***************************************/
//����ϵͳ��Ϣ�Ա㽨���µĴ����߳�
int SendSysMsg_ThreadCreate(GUIWINDOW *pWndObj);
//����ϵͳ��Ϣ�Ա��������д����߳�
int SendSysMsg_ThreadDestroy(GUIWINDOW *pWndObj);

//���ʹ�����Ϣ�Ա�ִ�д����ʼ��
int SendWndMsg_WindowInit(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա�ִ�д����˳�
int SendWndMsg_WindowExit(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա�ִ�д������
int SendWndMsg_WindowPaint(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա�ִ�д���ѭ��
int SendWndMsg_WindowLoop(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա�ִ�д������
int SendWndMsg_WindowPause(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա�ִ�д���ָ�
int SendWndMsg_WindowResume(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա�������������ѭ��
int SendWndMsg_LoopEnable(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա��ֹ��ֹͣ����ѭ��
int SendWndMsg_LoopDisable(GUIWINDOW *pWndObj);
//���ʹ�����Ϣ�Ա���д�����
int SendWndMsg_ErrorProc(void *pErrData, int iDataLen, void *pRecvObj);


#endif  //_GUI_GLOBAL_H

