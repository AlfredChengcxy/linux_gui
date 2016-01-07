/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  wnd_main.c
* ժ    Ҫ��  ���GUI���̵�����
*
* ��ǰ�汾��  v1.1.0
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/


/****************************
* Ϊʹ��GUI����Ҫ���õ�ͷ�ļ�
****************************/
#include "guiglobal.h"
#include "input_china_pinyin.h"


/*********************************
* Ϊ�����׸��������Ҫ���õ�ͷ�ļ�
*********************************/
#include "wnd_frmwifi.h"


/***
  * ���ܣ�
        ��ʼ���豸����������豸�ļ�������
  * ������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int InitializeDevice(void)
{
    int iErr = 0;

    //���ؼ�������
    iErr = system("insmod /lib/modules/2.6.30/drv_keypad.ko");
    if (iErr)
    {
        printf("insmod drv_keypad.ko error\n");
    }

    //�ȴ�һ��ʱ�䣬�Ա�����豸��������
    MsecSleep(200);

    return iErr;
}

int main(int argc, char *argv[])
{
    GUITHREAD thdFb = -1;
    GUITHREAD thdKeypad = -1;
    GUITHREAD thdTouch = -1;

    GUIWINDOW *pWnd = NULL;

    int iExit = 0;

    //��ʼ���豸����
    //InitializeDevice();

    //װ�����뷨���ݿ�
    //OpenInputDb("/home/ubuntu/workspace/guilib/run/input/china.db");

    //��ʼ��GUI���������е����̼߳��¼���װ�߳�
    InitializeGUI();

    //�����豸�������߳�
    ThreadCreate(&thdFb, NULL,
                 DefaultFbThread, GetCurrFbmap());
    //ThreadCreate(&thdKeypad, NULL,
    //             DefaultKeypadThread, GetCurrKeypad());
    ThreadCreate(&thdTouch, NULL,
                 DefaultTouchThread, GetCurrTouch());
	
    //��һ�������߳�����
    pWnd = CreateWindow(0, 0, 800, 480,
                        FrmWiFiInit, FrmWiFiExit,
                        FrmWiFiPaint, FrmWiFiLoop,
                        FrmWiFiPause, FrmWiFiResume,
                        NULL);   //pWnd�ɵ����߳��ͷ�
    SendSysMsg_ThreadCreate(pWnd);

    //�ȴ�������־����
    while (!iExit)
    {
        iExit = GetExitFlag();
        if (iExit)
        {
            ThreadCancel(thdTouch);     //ȡ�����������Ĵ������߳�
            ThreadCancel(thdKeypad);    //ȡ�����������ļ����߳�
            ThreadCancel(thdFb);        //ȡ������������֡�����߳�
            break;
        }

        MsecSleep(100);
    }

    //�����豸�������߳�
    ThreadJoin(thdTouch, NULL);
    ThreadJoin(thdKeypad, NULL);
    ThreadJoin(thdFb, NULL);

    //�ͷ�GUI�����������¼���װ�̼߳������߳�
    ReleaseGUI();

    //�ͷ����뷨���ݿ�
    CloseInputDb();

    //�ͷ��豸����
    //ReleaseDevice();

    return 0;
}

