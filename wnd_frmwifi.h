/*******************************************************************************
* Copyright(c)2014�������Ϣ����(����)���޹�˾
*
* All rights reserved
*
* �ļ����ƣ�  wnd_frmwifi.h
* ժ    Ҫ��  ʵ��wifi������
*             
*
* ��ǰ�汾��  v1.0.0
* ��    �ߣ�  wuyaju
* ������ڣ�  2014-10-28
*
* ȡ���汾��
* ԭ �� �ߣ�
* ������ڣ�
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
**							�������崦����غ���							  **
*******************************************************************************/
//����frmwifi�ĳ�ʼ����������������ؼ���ע����Ϣ����
int FrmWiFiInit(void *pWndObj);
//����frmwifi���˳��������ͷ�������Դ
int FrmWiFiExit(void *pWndObj);
//����frmwifi�Ļ��ƺ�����������������
int FrmWiFiPaint(void *pWndObj);
//����frmwifi��ѭ�����������д���ѭ��
int FrmWiFiLoop(void *pWndObj);
//����frmwifi�Ĺ����������д������ǰԤ����
int FrmWiFiPause(void *pWndObj);
//����frmwifi�Ļָ����������д���ָ�ǰԤ����
int FrmWiFiResume(void *pWndObj);

#endif
