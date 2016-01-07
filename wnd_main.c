/*******************************************************************************
* Copyright(c)2012，一诺仪器(威海)有限公司上海研发部
*
* All rights reserved
*
* 文件名称：  wnd_main.c
* 摘    要：  完成GUI进程的启动
*
* 当前版本：  v1.1.0
* 作    者：  lzm
* 完成日期：  2014-12-04
*
* 取代版本：  v1.0.2
* 原 作 者：  lzm
* 完成日期：  2014-11-04
*******************************************************************************/


/****************************
* 为使用GUI而需要引用的头文件
****************************/
#include "guiglobal.h"
#include "input_china_pinyin.h"


/*********************************
* 为建立首个窗体而需要引用的头文件
*********************************/
#include "wnd_frmwifi.h"


/***
  * 功能：
        初始化设备驱动，获得设备文件描述符
  * 参数：
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int InitializeDevice(void)
{
    int iErr = 0;

    //加载键盘驱动
    iErr = system("insmod /lib/modules/2.6.30/drv_keypad.ko");
    if (iErr)
    {
        printf("insmod drv_keypad.ko error\n");
    }

    //等待一段时间，以便完成设备驱动加载
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

    //初始化设备驱动
    //InitializeDevice();

    //装载输入法数据库
    //OpenInputDb("/home/ubuntu/workspace/guilib/run/input/china.db");

    //初始化GUI环境，运行调度线程及事件封装线程
    InitializeGUI();

    //运行设备抽象层的线程
    ThreadCreate(&thdFb, NULL,
                 DefaultFbThread, GetCurrFbmap());
    //ThreadCreate(&thdKeypad, NULL,
    //             DefaultKeypadThread, GetCurrKeypad());
    ThreadCreate(&thdTouch, NULL,
                 DefaultTouchThread, GetCurrTouch());
	
    //第一个窗体线程运行
    pWnd = CreateWindow(0, 0, 800, 480,
                        FrmWiFiInit, FrmWiFiExit,
                        FrmWiFiPaint, FrmWiFiLoop,
                        FrmWiFiPause, FrmWiFiResume,
                        NULL);   //pWnd由调度线程释放
    SendSysMsg_ThreadCreate(pWnd);

    //等待结束标志设立
    while (!iExit)
    {
        iExit = GetExitFlag();
        if (iExit)
        {
            ThreadCancel(thdTouch);     //取消可能阻塞的触摸屏线程
            ThreadCancel(thdKeypad);    //取消可能阻塞的键盘线程
            ThreadCancel(thdFb);        //取消可能阻塞的帧缓冲线程
            break;
        }

        MsecSleep(100);
    }

    //回收设备抽象层的线程
    ThreadJoin(thdTouch, NULL);
    ThreadJoin(thdKeypad, NULL);
    ThreadJoin(thdFb, NULL);

    //释放GUI环境，回收事件封装线程及调度线程
    ReleaseGUI();

    //释放输入法数据库
    CloseInputDb();

    //释放设备驱动
    //ReleaseDevice();

    return 0;
}

