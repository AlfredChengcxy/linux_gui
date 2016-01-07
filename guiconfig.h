/*******************************************************************************
* Copyright(c) 2012 ,一诺仪器(威海)有限公司上海研发部 
*
* All rights reserved
*
* 文件名称：  guiconfig.h
* 摘    要：  GUI运行环境配置文件，配置系统环境、硬件环境以及资源环境
*
* 当前版本：  v1.1.0 (新增资源环境配置文件及设备抽象层文件)
* 作    者：  lzm
* 完成日期：  2014-12-04
*
* 取代版本：  v1.0.2 (对输入/输出设备的访问添加锁保护、重写事件及消息的接口函数)
* 原 作 者：  lzm
* 完成日期：  2014-11-04
*******************************************************************************/

#ifndef _GUI_CONFIG_H
#define _GUI_CONFIG_H

    
/*******************************
* 定义GUI所依赖的操作系统环境
* 注：以下内容需根据实际情况修改
*******************************/
#define NONE_OS             0           //无操作系统
#define LINUX_OS            1           //Linux操作系统
#define GUI_OS_ENV          LINUX_OS    //GUI当前所处的操作系统环境


/*******************************
* 定义GUI中的支持的像素格式
* 注：以下内容需根据实际情况修改
*******************************/
#define PIXEL_8BITS     0
#define PIXEL_16BITS    1
#define PIXEL_24BITS    0
#define PIXEL_32BITS    0


/*******************************
* 定义GUI中的资源环境配置
* 注：以下内容需根据实际情况修改
*******************************/
#define RUNPATH_ROOT    "/home/ubuntu/workspace/guilib/dbg"
#define RESFILE_PATH    RUNPATH_ROOT"/run"
#define FNTFILE_STD     RESFILE_PATH"/font/unicode16.fnt"


#endif  //_GUI_CONFIG_H

