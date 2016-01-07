/*******************************************************************************
* Copyright(c)2012，一诺仪器(威海)有限公司上海研发部
*
* All rights reserved
*
* 文件名称：  wnd_frminit.c
* 摘    要：  实现初始化窗体frminit的窗体处理线程及相关操作函数
*
* 当前版本：  v1.1.0
* 作    者：  lzm
* 完成日期：  2014-12-04
*
* 取代版本：  v1.0.2
* 原 作 者：  lzm
* 完成日期：  2014-11-04
*******************************************************************************/

#include "wnd_frminit.h"


/****************************************
* 为实现窗体frminit而需要引用的其他头文件
****************************************/
#include "wnd_frmmain.h"


/************************
* 窗体frminit中的字体资源
************************/
//桌面上的字体
//...

//按钮区的字体
//...


/************************
* 窗体frminit中的文本资源
************************/
//状态栏上的文本
//...

//桌面上的文本
//...

//按钮区的文本
//...

//信息栏上文本
//...


/************************
* 窗体frminit中的窗体控件
************************/
static GUIWINDOW *pFrmInit = NULL;

//状态栏、桌面、信息栏
static GUIPICTURE *pInitBgDesk = NULL;

//状态栏上的控件
//...

//桌面上的控件
//...

//按钮区的控件
//...

//信息栏上的控件
//...


/********************************
* 窗体frminit中的文本资源处理函数
********************************/
//初始化文本资源
static int InitTextRes_Init(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);
//释放文本资源
static int InitTextRes_Exit(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);


/********************************
* 窗体frmInit中的控件事件处理函数
********************************/
//窗体的按键按下事件处理函数
static int InitWndKey_Down(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
//窗体的按键弹起事件处理函数
static int InitWndKey_Up(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
//窗体的光标移动事件处理函数
static int InitWndMov_Cursor(void * pInArg, int iInLen,
                             void * pOutArg, int iOutLen);

//桌面上控件的事件处理函数
//...

//按钮区控件的事件处理函数
//...

//信息栏控件的事件处理函数
//...


/********************************
* 窗体frminit中的错误事件处理函数
********************************/
static int InitErrProc_Func(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);


/********************************
* 窗体frminit中的其它内部处理函数
********************************/
//...


/***
  * 功能：
        窗体frminit的初始化函数，建立窗体控件、注册消息处理
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmInitInit(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;
    //临时变量定义
    GUIMESSAGE *pMsg = NULL;

    //得到当前窗体对象
    pFrmInit = (GUIWINDOW *) pWndObj;

    //初始化字体资源
    //...

    //初始化文本资源
    //如果GUI存在多国语言，在此处获得对应语言的文本资源
    //初始化文本资源必须在建立文本CreateText()或建立标签CreateLabel()之前
    /****************************************************************/
    InitTextRes_Init(NULL, 0, NULL, 0);

    //建立窗体控件
    /****************************************************************/
    //建立状态栏、桌面、信息栏
    pInitBgDesk = CreatePicture(0, 0, 800, 480,
                                RESFILE_PATH"/bitmap/bg_init.bmp");
    //建立状态栏上的控件
    //...
    //建立桌面上的控件
    //...
    //建立按钮区的控件
    //...
    //建立信息栏上的控件
    //...

    //设置窗体控件的画刷、画笔及字体
    /****************************************************************/
    //设置桌面上的控件
    //...
    //设置按钮区的控件
    //...

    //注册窗体控件，只对那些需要接收事件的控件进行
    //即如果该控件没有或者不需要响应输入事件，可以无需注册
    //注册窗体控件必须在注册消息处理函数之前进行
    //***************************************************************/
    //注册窗体(因为所有的按键及光标事件都统一由窗体进行处理)
    AddWindowComp(OBJTYP_GUIWINDOW, sizeof(GUIWINDOW), pFrmInit,
                  pFrmInit);
    //注册桌面上的控件
    //...
    //注册按钮区的控件
    //...
    //注册信息栏上的控件
    //...

    //注册消息处理函数，如果消息接收对象未曾注册到窗体，将无法正常接收消息
    //即此处的操作应当在注册窗体控件的基础上进行
    //注册消息处理函数必须在注册窗体控件之后进行
    //注册消息处理函数必须在持有锁的前提下进行
    //***************************************************************/
    pMsg = GetCurrMessage();
    //注册窗体的按键消息处理
    LoginMessageReg(GUIMESSAGE_KEY_DOWN, pFrmInit,
                    InitWndKey_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_KEY_UP, pFrmInit,
                    InitWndKey_Up, NULL, 0, pMsg);
    //注册窗体的光标消息处理
    LoginMessageReg(GUIMESSAGE_MOV_CURSOR, pFrmInit,
                    InitWndMov_Cursor, NULL, 0, pMsg);
    //注册桌面上控件的消息处理
    //...
    //注册按钮区控件的消息处理
    //...
    //注册信息栏上控件的消息处理
    //...
    //注册窗体的错误处理函数
    LoginMessageReg(GUIMESSAGE_ERR_PROC, pFrmInit,
                    InitErrProc_Func, NULL, 0, pMsg);

    return iReturn;
}


/***
  * 功能：
        窗体frminit的退出函数，释放所有资源
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmInitExit(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;
    //临时变量定义

    //得到当前窗体对象
    pFrmInit = (GUIWINDOW *) pWndObj;

    //清空消息队列中的消息注册项
    //***************************************************************/
    ClearMessageReg(GetCurrMessage());

    //从当前窗体中注销窗体控件
    //***************************************************************/
    ClearWindowComp(pFrmInit);

    //销毁窗体控件
    //***************************************************************/
    //销毁状态栏、桌面、信息栏
    DestroyPicture(&pInitBgDesk);
    //销毁状态栏上的控件
    //...
    //销毁桌面上的控件
    //...
    //销毁按钮区的控件
    //...
    //销毁信息栏上的控件
    //...

    //释放文本资源
    //***************************************************************/
    InitTextRes_Exit(NULL, 0, NULL, 0);

    //释放字体资源
    //***************************************************************/
    //释放按钮区的字体
    //...

    return iReturn;
}


/***
  * 功能：
        窗体frminit的绘制函数，绘制整个窗体
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmInitPaint(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;

    //得到当前窗体对象
    pFrmInit = (GUIWINDOW *) pWndObj;

    //显示状态栏、桌面、信息栏
    iReturn = DisplayPicture(pInitBgDesk);
    //显示状态栏上的控件
    //...
    //显示桌面上的控件
    //...
    //显示按钮区的控件
    //...
    //显示信息栏上的控件
    //...

    return iReturn;
}


/***
  * 功能：
        窗体frminit的循环函数，进行窗体循环
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmInitLoop(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;
    //临时变量定义
    GUIWINDOW *pWnd = NULL;

    //禁止并停止窗体循环
    SendWndMsg_LoopDisable(pWndObj);

    //设置窗体光标
    pWnd = pWndObj;
    pWnd->Visible.iCursor = 0;

    //调度frmmain
    pWnd = CreateWindow(0, 0, 800, 480,
                        FrmMainInit, FrmMainExit,
                        FrmMainPaint, FrmMainLoop,
                        FrmMainPause, FrmMainResume,
                        NULL);          //pWnd由调度线程释放
    SendWndMsg_WindowExit(pFrmInit);    //发送窗体消息以便退出当前窗体
    SendSysMsg_ThreadCreate(pWnd);      //发送系统消息以便建立新的窗体线程

    return iReturn;
}


/***
  * 功能：
        窗体frminit的挂起函数，进行窗体挂起前预处理
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmInitPause(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;

    return iReturn;
}


/***
  * 功能：
        窗体frminit的恢复函数，进行窗体恢复前预处理
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmInitResume(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;

    return iReturn;
}


//初始化文本资源
static int InitTextRes_Init(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;

    //初始化状态栏上的文本
    //...
    //初始化桌面上的文本
    //...
    //初始化按钮区的文本
    //...
    //初始化信息栏上的文本
    //...

    return iReturn;
}


//释放文本资源
static int InitTextRes_Exit(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;

    //释放状态栏上的文本
    //...
    //释放桌面上的文本
    //...
    //释放按钮区的文本
    //...
    //释放信息栏上的文本
    //...

    return iReturn;
}


//窗体的按键按下事件处理函数
static int InitWndKey_Down(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
    //临时变量定义
    unsigned int uiValue;

    uiValue = (unsigned int)pInArg;
    switch (uiValue)
    {
    case KEYCODE_MENU:
        break;
    case KEYCODE_F1:
        break;
    case KEYCODE_F2:
        break;
    case KEYCODE_F3:
        break;
    case KEYCODE_F4:
        break;
    case KEYCODE_F5:
        break;
    case KEYCODE_ESC:
        break;
    case KEYCODE_FILE:
        break;
    case KEYCODE_SCALE:
        break;
    case KEYCODE_SETUP:
        break;
    case KEYCODE_UP:
        break;
    case KEYCODE_DOWN:
        break;
    case KEYCODE_LEFT:
        break;
    case KEYCODE_RIGHT:
        break;
    case KEYCODE_ENTER:
        break;
    case KEYCODE_REALT:
        break;
    case KEYCODE_AVG:
        break;
    case KEYCODE_KNOB:
        break;
    default:
        break;
    }

    return iReturn;
}


//窗体的按键弹起事件处理函数
static int InitWndKey_Up(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
    //临时变量定义
    unsigned int uiValue;

    uiValue = (unsigned int)pInArg;
    switch (uiValue)
    {
    case KEYCODE_MENU:
        break;
    case KEYCODE_F1:
        break;
    case KEYCODE_F2:
        break;
    case KEYCODE_F3:
        break;
    case KEYCODE_F4:
        break;
    case KEYCODE_F5:
        break;
    case KEYCODE_ESC:
        break;
    case KEYCODE_FILE:
        break;
    case KEYCODE_SCALE:
        break;
    case KEYCODE_SETUP:
        break;
    case KEYCODE_UP:
        break;
    case KEYCODE_DOWN:
        break;
    case KEYCODE_LEFT:
        break;
    case KEYCODE_RIGHT:
        break;
    case KEYCODE_ENTER:
        break;
    case KEYCODE_REALT:
        break;
    case KEYCODE_AVG:
        break;
    case KEYCODE_KNOB:
        break;
    default:
        break;
    }

    return iReturn;
}


//窗体的光标移动事件处理函数
static int InitWndMov_Cursor(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;

    return iReturn;
}


//错误事件处理函数
static int InitErrProc_Func(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;

    //根据实际情况，进行错误处理

    return iReturn;
}

