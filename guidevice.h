/*******************************************************************************
* Copyright(c) 2012 ,一诺仪器(威海)有限公司上海研发部 
*
* All rights reserved
*
* 文件名称：  guidevice.h
* 摘    要：  声明GUI基本输入/输出设备的用户自定义操作函数，为GUI所使用的这些设
*             备提供设备抽象层。
*
* 当前版本：  v1.1.0 (新增资源环境配置文件及设备抽象层文件)
* 作    者：  lzm
* 完成日期：  2014-12-04
*
* 取代版本：  v1.0.2 (对输入/输出设备的访问添加锁保护、重写事件及消息的接口函数)
* 原 作 者：  lzm
* 完成日期：  2014-11-04
*******************************************************************************/
    
#ifndef _GUI_DEVICE_H
#define _GUI_DEVICE_H


/**************************************
* 为定义GUIDEVICE而需要引用的其他头文件
**************************************/
#include "guibase.h"
#include "guifbmap.h"
#include "guikeypad.h"
#include "guitouch.h"


/********************************
* 定义GUI中使用的输入输出设备文件
* 注：以下内容需根据实际情况修改
********************************/
#define DEVFILE_FB      "/dev/fb0"
#define DEVFILE_KEYPAD  "/dev/keyb0"
#define DEVFILE_TOUCH   "/dev/event2"


/********************************
* 定义GUI中当前使用的按键映射码值
* 注：以下内容需根据实际情况修改
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
* 定义GUI中基本输入/输出设备的用户自定义操作函数
* 注：以下函数中的内容需根据实际情况编写
***********************************************/
//用户自定义的帧缓冲处理函数，用于完成自定义类型帧缓冲的处理
int CustomFbmapFunc(GUIFBMAP *pFbmapObj);
//用户自定义的键盘处理函数，用于完成自定义类型键盘的处理
int CustomKeypadFunc(GUIKEYPAD *pKeypadObj);
//用户自定义的触摸屏处理函数，用于完成自定义类型触摸屏的处理
int CustomTouchFunc(GUITOUCH *pTouchObj);

#endif  //_GUI_DEVICE_H

