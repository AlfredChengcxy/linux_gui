/*******************************************************************************
* Copyright(c)2014，大豪信息技术(威海)有限公司
*
* All rights reserved
*
* 文件名称：  wnd_frmwifi.h
* 摘    要：  实现wifi的连接
*             
*
* 当前版本：  v1.0.0
* 作    者：  wuyaju
* 完成日期：  2014-10-28
*
* 取代版本：
* 原 作 者：
* 完成日期：
*******************************************************************************/
#ifndef _WND_FRMWIFI_H_
#define _WND_FRMWIFI_H_

#define MAX_SIGNUM 35
typedef struct _wifi_info
{
	int able;
	char ssid[512];
	int iLevel;
	int iCell;

}WIFI_INFO, *PWIFI_INFO;

typedef enum _wifi_state
{
	ENUM_OPEN = 1,
	ENUM_SCAN,
	ENUM_SCAN_R,
	ENUM_CONNECT,//victor
}WIFI_S;

/*******************************************************************************
**							声明窗体处理相关函数							  **
*******************************************************************************/
//窗体frmwifi的初始化函数，建立窗体控件、注册消息处理
int FrmWiFiInit(void *pWndObj);
//窗体frmwifi的退出函数，释放所有资源
int FrmWiFiExit(void *pWndObj);
//窗体frmwifi的绘制函数，绘制整个窗体
int FrmWiFiPaint(void *pWndObj);
//窗体frmwifi的循环函数，进行窗体循环
int FrmWiFiLoop(void *pWndObj);
//窗体frmwifi的挂起函数，进行窗体挂起前预处理
int FrmWiFiPause(void *pWndObj);
//窗体frmwifi的恢复函数，进行窗体恢复前预处理
int FrmWiFiResume(void *pWndObj);

#endif
