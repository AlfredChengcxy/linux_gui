/*******************************************************************************
* Copyright(c)2012，一诺仪器(威海)有限公司上海研发部
*
* All rights reserved
*
* 文件名称：  wnd_frminit.h
* 摘    要：  声明初始化窗体frminit的窗体处理线程及相关操作函数
*
* 当前版本：  v1.1.0
* 作    者：  lzm
* 完成日期：  2014-12-04
*
* 取代版本：  v1.0.2
* 原 作 者：  lzm
* 完成日期：  2014-11-04
*******************************************************************************/

#ifndef _WND_FRMINIT_H
#define _WND_FRMINIT_H


/****************************
* 为使用GUI而需要引用的头文件
****************************/
#include "guiglobal.h"


/*********************
* 声明窗体处理相关函数
*********************/
//窗体frminit的初始化函数，建立窗体控件、注册消息处理
int FrmInitInit(void *pWndObj);
//窗体frminit的退出函数，释放所有资源
int FrmInitExit(void *pWndObj);
//窗体frminit的绘制函数，绘制整个窗体
int FrmInitPaint(void *pWndObj);
//窗体frminit的循环函数，进行窗体循环
int FrmInitLoop(void *pWndObj);
//窗体frminit的挂起函数，进行窗体挂起前预处理
int FrmInitPause(void *pWndObj);
//窗体frminit的恢复函数，进行窗体恢复前预处理
int FrmInitResume(void *pWndObj);


#endif  //_WND_FRMLOGO_H

