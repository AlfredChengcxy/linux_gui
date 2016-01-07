/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guiwindow.h
* ժ    Ҫ��  ����GUI�Ĵ������ͼ�������Ϊʵ�ִ���ؼ��ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_WINDOW_H
#define _GUI_WINDOW_H


/**************************************
* Ϊ����GUIWINDOW����Ҫ���õ�����ͷ�ļ�
**************************************/
#include "guibase.h"
#include "guibrush.h"
#include "guipen.h"
#include "guifont.h"
#include "guimessage.h"


/********************************************
* ����GUI�д���������ܰ����ؼ�������������
********************************************/
#define GUIWINDOW_COMP_LIMIT    1000    //�����������ɰ����Ŀؼ�����


/************************************
* ����GUI�д��崦�����ĵ��ýӿ�����
************************************/
typedef int (*WNDFUNC)(void *pWndObj);


/******************
* ����GUI�д���ṹ
******************/
typedef struct _window
{
    GUIVISIBLE Visible;     //����Ŀ�����Ϣ

    GUIPEN *pWndPen;        //������ʹ�õĻ��ʣ�ΪNULL��ʹ��GUI�еĵ�ǰ����
    GUIBRUSH *pWndBrush;    //������ʹ�õĻ�ˢ��ΪNULL��ʹ��GUI�еĵ�ǰ��ˢ
    GUIFONT *pWndFont;      //������ʹ�õ����壬ΪNULL��ʹ��GUI�еĵ�ǰ����

    WNDFUNC fnWndInit;      //ָ�����ʼ�������������Դ���估��Ϣע���
    WNDFUNC fnWndExit;      //ָ�����˳������������Ϣע������Դ����
    WNDFUNC fnWndPaint;     //ָ������ƺ�������ɴ���ؼ��Ļ���
    WNDFUNC fnWndLoop;      //ָ����ѭ����������ɴ���ѭ������Ϊ�������
    WNDFUNC fnWndPause;     //ָ�������������ɹ���ǰԤ����Ϊ�������
    WNDFUNC fnWndResume;    //ָ����ָ���������ɻָ�ǰԤ����Ϊ�������

    THREADFUNC fnWndThread; //���ڴ������崦���̣߳�Ϊ��ʹ��ϵͳ�Ĵ��崦���߳�
    GUITHREAD thdWndTid;    //�����߳�ID�����崦���̵߳��̱߳�ʶ��

    GUILIST *pWndComps;     //�ؼ����У�������������GUI����ؼ�����
    GUIMUTEX Mutex;         //�����������ڿ��ƶԿؼ����еķ���
} GUIWINDOW;


/**********************************
* ����GUI���봰��������صĲ�������
**********************************/
//����ָ������Ϣֱ�ӽ����������
GUIWINDOW* CreateWindow(unsigned int uiPlaceX, unsigned int uiPlaceY, 
                        unsigned int uiWndWidth, unsigned int uiWndHeight, 
                        WNDFUNC fnWndInit, WNDFUNC fnWndExit, 
                        WNDFUNC fnWndPaint, WNDFUNC fnWndLoop, 
                        WNDFUNC fnWndPause, WNDFUNC fnWndResume,
                        THREADFUNC fnWndThread);
//ɾ���������
int DestroyWindow(GUIWINDOW **ppWndObj);

//��ʼ����ǰ����
int InitCurrWindow(void);
//��ס��ǰ�������
int LockCurrWindow(void);
//������ǰ�������
int UnlockCurrWindow(void);
//���ֵ�ǰ�Ĵ�����󲻱䣬��Ҫ��UnlockCurrWindow()�ɶ�ʹ��
GUIWINDOW* HoldCurrWindow(void);
//�õ���ǰ�Ĵ������
GUIWINDOW* GetCurrWindow(void);
//���õ�ǰ�Ĵ������
int SetCurrWindow(GUIWINDOW *pWndObj);

//���ô������Ч��������
int SetWindowArea(unsigned int uiStartX, unsigned int uiStartY, 
                  unsigned int uiEndX, unsigned int uiEndY,
                  GUIWINDOW *pWndObj);
//���ô�����ʹ�õĻ�ˢ
int SetWindowBrush(GUIBRUSH *pWndBrush, GUIWINDOW *pWndObj);
//���ô�����ʹ�õĻ���
int SetWindowPen(GUIPEN *pWndPen, GUIWINDOW *pWndObj);
//���ô�������Ӧ������
int SetWindowFont(GUIFONT *pWndFont, GUIWINDOW *pWndObj);

//���GUI����ؼ���ָ������
int AddWindowComp(int iCompTyp, int iCompLen, void *pWndComp, 
                  GUIWINDOW *pWndObj);
//��ָ������ɾ��GUI����ؼ�
int DelWindowComp(void *pWndComp, GUIWINDOW *pWndObj);
//���ָ������Ĵ���ؼ�����
int ClearWindowComp(GUIWINDOW * pWndObj);


#endif  //_GUI_WINDOW_H

