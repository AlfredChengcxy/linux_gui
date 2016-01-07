/*******************************************************************************
* Copyright(c)2014，大豪信息技术(威海)有限公司
*
* All rights reserved
*
* 文件名称：  wnd_frmwifi.c
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

#include "wnd_frmwifi.h"

#include "wnd_msgqueue.h"

/*******************************************************************************
**						为实现窗体frmwifi而需要引用的其他头文件 			  **
*******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

#include <sys/time.h>
#include <sys/types.h>

#include "guiglobal.h"

/*******************************************************************************
**									宏定义 				 					  **
*******************************************************************************/	


/*******************************************************************************
**								变量定义				 					  **
*******************************************************************************/	
GUITHREAD thdWifi = -1;
static GUIMUTEX pWifiMutex;
static WIFI_INFO stGetWifi;
char path[512] = "/mnt/sdcard/wifi/list.txt";
static WIFI_INFO stWifi[MAX_SIGNUM];

/* 选中状态时wifi加密图标 */
static char *g_pWiFiSecEncryTypePath[] = {
BmpFileDirectory"ico_wifi_no_encrypt_press.bmp", 
BmpFileDirectory"ico_wifi_encrypt_press.bmp"};

/* 选中状态时wifi信号强度图标 */
/*static char *g_pWiFiSecStrengthPath[]  = {
BmpFileDirectory"ico_wifi_empty_press.bmp", BmpFileDirectory"ico_wifi_quar_press.bmp", 
BmpFileDirectory"ico_wifi_half_press.bmp", BmpFileDirectory"ico_wifi_three_quars_press.bmp",
BmpFileDirectory"ico_wifi_full_press.bmp"};*/

/* 未选中状态时wifi加密图标 */
static char *g_pWiFiUnSecEncryTypePath[] = {
BmpFileDirectory"ico_wifi_no_encrypt_unpress.bmp", 
BmpFileDirectory"ico_wifi_encrypt_unpress.bmp"};

/* 未选中状态时wifi信号强度图标 */
static char *g_pWiFiUnSecStrengthPath[]  = {
BmpFileDirectory"ico_wifi_empty_unpress.bmp", BmpFileDirectory"ico_wifi_quar_unpress.bmp", 
BmpFileDirectory"ico_wifi_half_unpress.bmp", BmpFileDirectory"ico_wifi_three_quars_unpress.bmp",
BmpFileDirectory"ico_wifi_full_unpress.bmp"};


unsigned long g_Status = 0;						// wifi的当前状态，每一位代表一种状态，通过宏定义进行操作


/*******************************************************************************
**							窗体frmwifi中的控件定义部分					  	  **
*******************************************************************************/
static GUIWINDOW *pFrmWiFi = NULL;
static GUIFONT *pWifiFntBlack = NULL;     		//标题按钮的字体

/**********************************背景控件定义********************************/ 
static GUIPICTURE *pWiFiBtnLeftBg  = NULL;       
static GUIPICTURE *pWiFiInfoBg = NULL;

/**********************************菜单控件定义********************************/ 
static GUIPICTURE *pWiFiMenuBg = NULL;
static GUIPICTURE *pWiFiMenu[5] = {NULL};
static GUILABEL *pWiFiLblMenu[5] = {NULL};
static GUICHAR *pWiFiStrMenu[5] = {NULL};

/******************************窗体标题栏控件定义******************************/
static GUICHAR *pWiFiStrFrmName = NULL;	  	  	//窗体左上角标题栏文本
static GUILABEL *pWiFiLblFrmName = NULL;		//左上角窗体名字的Label

/***************************打开关闭wifi内的控件定义***************************/
static GUICHAR *pWiFiStrOnOffInfo = NULL;

static GUILABEL *pWiFiLblOnOffInfo = NULL;

static GUIPICTURE *pWiFiBtnOnOffBg		= NULL;		
static GUIPICTURE *pWiFiBtnREnableOn	= NULL; 
static GUIPICTURE *pWiFiBtnREnableOff	= NULL; 


/****************************已连接wifi内的控件定义****************************/


/***************************扫描到的wifi内的控件定义***************************/
#define WIFIITEM   10
static GUIPICTURE *pWiFiItem[WIFIITEM] = {NULL};
static GUILABEL *pWiFiLblItem[WIFIITEM] = {NULL};
static GUICHAR *pWiFiStrItem[WIFIITEM] = {NULL};

/*****************************右侧菜单栏控件定义*******************************/

/*******************************************************************************
**	    	窗体frmwifi中的初始化文本资源、 释放文本资源函数定义部分		  **
*******************************************************************************/
static int WiFiTextRes_Init(void *pInArg, int iInLen, 
							void *pOutArg, int iOutLen);
static int WiFiTextRes_Exit(void *pInArg, int iInLen, 
							void *pOutArg, int iOutLen);


/*******************************************************************************
**			    	窗体frmwifi中的控件事件处理函数定义部分				  	  **
*******************************************************************************/

/***************************窗体的按键事件处理函数*****************************/
static int WiFiWndKey_Down(void *pInArg, int iInLen, 
							  void *pOutArg, int iOutLen);
static int WiFiWndKey_Up(void *pInArg, int iInLen, 
							void *pOutArg, int iOutLen);

/**************************菜单栏控件的事件处理函数****************************/
static int WiFiBtnMenu_Down(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen);
static int WiFiBtnMenu_Up(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen);



/************************打开/关闭wifi按钮事件处理函数*************************/
static int WiFiBtnEnableOn_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);
static int WiFiBtnEnableOff_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);

static int WiFiBtnEnableOn_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);
static int WiFiBtnEnableOff_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);


/**************************连接wifi按钮事件处理函数****************************/
static int WiFiBtnItemSSID_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);
static int WiFiBtnItemSSID_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);



/*******************************************************************************
**			    			窗体内的其他函数声明					 		  **
*******************************************************************************/
static void WifiOpen();
static void WifiScan();	
static void WifiScan_r();
static void SortByLevel(int num);
static int CalcWifiCell(int iLevel);

int vsystem(const char * cmdstring)
{
    pid_t pid;
    int status;

    if (cmdstring == NULL)
    {
        return 1;
    }

    if ((pid = vfork()) < 0)
    {
        status = -1;
    }
    else if (pid == 0) //child
    {
        execl("/bin/sh", "sh", "-c", cmdstring, NULL);
        _exit(127); //get here when 'execl' failed & return value '127'
    }
    else
    {
        while (waitpid(pid, &status, 0) == -1)
        {
        	printf("waitpid\n");
            if (errno != EINTR) //not interrupted by signal
            {
                status = -1;
                break;
            }
        }
    }

    return status;
}

void* DefaultWifiThread(void *pThreadArg)
{
    int iExit = 0;
	int iRecv = 0;
	OTDRMSGQUEUE *pWifiMsg = NULL;
	pWifiMsg = GetWifiMsgQueue();
	printf("enter thd\n");
	if(pWifiMsg == NULL)
	{
		printf("error, pWifiMsg is NULL\n");
		return NULL;
	}
	else
	{
		ClearOTDRMsgQueue(pWifiMsg);
	}
	
    while (!iExit)
    {		
        iExit = GetExitFlag();
		
        if (iExit == 1)
        {
            break;
        }

		iRecv = 0;
		ReadWifiMsgQueue(&iRecv);
		if(iRecv)
		{
			printf("wifiTHD Recv = %d\n", iRecv);
			switch(iRecv)
			{
				case ENUM_OPEN:
					WifiOpen();
					break;
				case ENUM_SCAN:
					WifiScan();
					break;
				case ENUM_SCAN_R:
					WifiScan_r();
					break;
				default:
					break;
			}
		}
		else
		{
			MsecSleep(30);
		}
		
    }	
	printf("exit thd\n");
	return NULL;
}

/***
  * 功能：
        窗体FrmWiFi的初始化函数，建立窗体控件、注册消息处理
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmWiFiInit(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;
	int i = 0;

	GUIMESSAGE *pMsg = NULL;
    //得到当前窗体对象
    pFrmWiFi = (GUIWINDOW *) pWndObj;
	
    pWifiFntBlack = CreateFont(FontFileDirectory"unicode.fnt", 
                                 16, 16, 0x0000000, 0xFFFFFFFF);

   	//初始化文本资源必须在建立文本CreateText()或建立标签CreateLabel()之前
    WiFiTextRes_Init(NULL, 0, NULL, 0);

	/* 桌面背景图片 */
	pWiFiBtnLeftBg = CreatePicture(0, 0, 681, 480, 
                                     	BmpFileDirectory"bg_wifi.bmp");
	/*菜单部分*/
	pWiFiMenuBg = CreatePicture(681, 39, 119, 441, 
										BmpFileDirectory"wifi_global_menu_bg.bmp");
	int y = 40;
	for (i = 0; i < 5; ++i) 
	{
		pWiFiMenu[i] = CreatePicture(681, y + 51 * i, 119, 51, 
												BmpFileDirectory"wifi_menu_item_unpress.bmp");
	
		pWiFiLblMenu[i] = CreateLabel(681, y + 51 * i + 13, 119, 24,												   
											pWiFiStrMenu[i]);
		SetLabelAlign(GUILABEL_ALIGN_CENTER, pWiFiLblMenu[i]);
	}
	
	/* 窗体标题Label */
	pWiFiLblFrmName = CreateLabel(0, 20, 100, 24, pWiFiStrFrmName);
	SetLabelAlign(GUILABEL_ALIGN_CENTER, pWiFiLblFrmName);	
	SetLabelFont(pWifiFntBlack, pWiFiLblFrmName);

	/* 打开关闭WiFi区域控件定义 */	
	pWiFiBtnREnableOn   = CreatePicture(350, 45, 84, 32, BmpFileDirectory"btn_wifi_on_unpress.bmp");
	pWiFiBtnREnableOff  = CreatePicture(434, 45, 84, 32, BmpFileDirectory"btn_wifi_off_unpress.bmp");

	pWiFiBtnOnOffBg = CreatePicture(28, 74, 313, 24, BmpFileDirectory"btn_wifi_ssid_unpress.bmp");
	pWiFiLblOnOffInfo = CreateLabel(28, 76, 300, 24,  pWiFiStrOnOffInfo);
	
	/* wifi列表 */
	for(i = 0; i < WIFIITEM; i++)
	{
		pWiFiItem[i] = CreatePicture(10, 170+(i*30), 313, 28, BmpFileDirectory"btn_wifi_ssid_unpress.bmp");
		pWiFiLblItem[i] = CreateLabel(10, 170+(i*30), 313, 28, pWiFiStrItem[i]);
		SetLabelFont(pWifiFntBlack, pWiFiLblItem[i]);
	}
	
    AddWindowComp(OBJTYP_GUIWINDOW, sizeof(GUIWINDOW), pFrmWiFi, 
                  pFrmWiFi);
	
	//注册桌面上的控件
    AddWindowComp(OBJTYP_GUIPICTURE, sizeof(GUIPICTURE), pWiFiBtnREnableOn, 
                  pFrmWiFi);
    AddWindowComp(OBJTYP_GUIPICTURE, sizeof(GUIPICTURE), pWiFiBtnREnableOff, 
                  pFrmWiFi);	
	
	for(i= 0; i < 5; i++)
	{
		AddWindowComp(OBJTYP_GUIPICTURE, sizeof(GUIPICTURE), pWiFiMenu[i], 
					  pFrmWiFi);
	}
	for(i = 0; i < WIFIITEM; i++)
	{
		AddWindowComp(OBJTYP_GUIPICTURE, sizeof(GUIPICTURE), pWiFiItem[i], 
					  pFrmWiFi);
	}

    pMsg = GetCurrMessage();
    
    //注册窗体的按键消息处理
    LoginMessageReg(GUIMESSAGE_KEY_DOWN, pFrmWiFi, 
                    WiFiWndKey_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_KEY_UP, pFrmWiFi, 
                    WiFiWndKey_Up, NULL, 0, pMsg);


    //注册桌面上控件的消息处理
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pWiFiBtnREnableOn, 
                    WiFiBtnEnableOn_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pWiFiBtnREnableOff, 
                    WiFiBtnEnableOff_Down, NULL, 0, pMsg);	

    LoginMessageReg(GUIMESSAGE_TCH_UP, pWiFiBtnREnableOn, 
                    WiFiBtnEnableOn_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pWiFiBtnREnableOff, 
                    WiFiBtnEnableOff_Up, NULL, 0, pMsg);	

	for(i= 0; i < 5; i++)
	{
		LoginMessageReg(GUIMESSAGE_TCH_DOWN, pWiFiMenu[i], 
						WiFiBtnMenu_Down, NULL, i, pMsg);	
		
		LoginMessageReg(GUIMESSAGE_TCH_UP, pWiFiMenu[i], 
						WiFiBtnMenu_Up, NULL, i, pMsg);	
	}
	for(i = 0; i < WIFIITEM; i++)
	{
		LoginMessageReg(GUIMESSAGE_TCH_DOWN, pWiFiItem[i], 
						WiFiBtnItemSSID_Down, NULL, i, pMsg);	
		
		LoginMessageReg(GUIMESSAGE_TCH_UP, pWiFiItem[i], 
						WiFiBtnItemSSID_Up, NULL, i, pMsg);	
	}
    return iReturn;
}


/***
  * 功能：
        窗体FrmWiFi的退出函数，释放所有资源
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmWiFiExit(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;
	int i = 0;

    GUIMESSAGE *pMsg = NULL;
    //得到当前窗体对象
    pFrmWiFi = (GUIWINDOW *) pWndObj;

	//清空消息队列中的消息注册项
    //***************************************************************/
    pMsg = GetCurrMessage();
    ClearMessageReg(pMsg);

    //从当前窗体中注销窗体控件
    //***************************************************************/
    ClearWindowComp(pFrmWiFi);

    //销毁窗体控件
    //***************************************************************/
    //销毁桌面背景图片
    DestroyPicture(&pWiFiBtnLeftBg);

	//销毁菜单
	DestroyPicture(&pWiFiMenuBg);

	for(i = 0;i < 5;i++)
	{
		DestroyPicture(&pWiFiMenu[i]);
		DestroyLabel(&pWiFiLblMenu[i]);
	}
	for(i = 0; i < WIFIITEM; i++)
	{
		DestroyPicture(&pWiFiItem[i]);
		DestroyLabel(&pWiFiLblItem[i]);
	}

    //销毁桌面上的控件
    DestroyPicture(&pWiFiBtnREnableOn);
	DestroyPicture(&pWiFiBtnREnableOff);
	DestroyPicture(&pWiFiBtnOnOffBg);

	//销毁窗体左上角窗体Label
	DestroyLabel(&pWiFiLblFrmName);
	DestroyLabel(&pWiFiLblOnOffInfo);
	
	DestroyFont(&pWifiFntBlack);
	//释放文本资源
    //***************************************************************/
    WiFiTextRes_Exit(NULL, 0, NULL, 0);
	
    return iReturn;
}


/***
  * 功能：
        窗体FrmWiFi的绘制函数，绘制整个窗体
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmWiFiPaint(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;
	int i = 0;
    //得到当前窗体对象
    pFrmWiFi = (GUIWINDOW *) pWndObj;

    //显示桌面背景图片
    DisplayPicture(pWiFiBtnLeftBg);

	//显示菜单
    DisplayPicture(pWiFiMenuBg);
	for(i = 0; i < 5; i++)
	{
		DisplayPicture(pWiFiMenu[i]);
		DisplayLabel(pWiFiLblMenu[i]);
	}

	//显示状态栏上的图片
	DisplayPicture(pWiFiBtnOnOffBg);
	
	//显示窗体左上角窗体Label
	DisplayLabel(pWiFiLblFrmName);
	DisplayLabel(pWiFiLblOnOffInfo);

	SetPictureBitmap(BmpFileDirectory"btn_wifi_on_unpress.bmp", pWiFiBtnREnableOn);
	SetPictureBitmap(BmpFileDirectory"btn_wifi_off_press.bmp", pWiFiBtnREnableOff);

	DisplayPicture(pWiFiBtnREnableOn);
	DisplayPicture(pWiFiBtnREnableOff);	
	
	for(i = 0; i < WIFIITEM; i++)
	{
		DisplayPicture(pWiFiItem[i]);
		DisplayLabel(pWiFiLblItem[i]);
	}

	//初始化wifi，创建wifi线程
	InitMutex(&pWifiMutex, NULL);
	InitWifiQueue(10);
	ThreadCreate(&thdWifi, NULL, DefaultWifiThread, NULL);

    return iReturn;
}


/***
  * 功能：
        窗体FrmWiFi的循环函数，进行窗体循环
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmWiFiLoop(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;

    return iReturn;
}


/***
  * 功能：
        窗体FrmWiFi的挂起函数，进行窗体挂起前预处理
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmWiFiPause(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;

    return iReturn;
}


/***
  * 功能：
        窗体FrmWiFi的恢复函数，进行窗体恢复前预处理
  * 参数：
        1.void *pWndObj:    指向当前窗体对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int FrmWiFiResume(void *pWndObj)
{
    //错误标志、返回值定义
    int iReturn = 0;

    return iReturn;
}


/*******************************************************************************
**	    	窗体frmwifi中的初始化文本资源、 释放文本资源函数定义部分		  **
*******************************************************************************/
/***
  * 功能：
		初始化文本资源
  * 参数：
		1.void *pInArg	:	指向输入参数的指针
		2.int iInLen	:	输入参数的长度
		3.void *pOutArg :	指向传出参数的指针
		4.int iOutLen	:	输出参数的长度
  * 返回：
		成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiTextRes_Init(void *pInArg, int iInLen, 
                            void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
	int i;
	//窗体左上角的文本
	pWiFiStrFrmName = TransString("WLAN");
	pWiFiStrOnOffInfo  = TransString("oooo");

	pWiFiStrMenu[0] = TransString("Menu1");
	pWiFiStrMenu[1] = TransString("Menu2");
	pWiFiStrMenu[2] = TransString("Menu3");
	pWiFiStrMenu[3] = TransString("Menu4");
	pWiFiStrMenu[4] = TransString("Menu5");
	for(i = 0; i < WIFIITEM; i++)
	{
		pWiFiStrItem[i] = TransString("Item");
	}

	//桌面上的文本
	//pWiFiStrLEnable = GetCurrLanguageText(WIFI_STARTWLAN);
	//pWiFiStrConnectedCap = GetCurrLanguageText(WIFI_CONNECTED_CAP);
	//pWiFiStrScanCap =  GetCurrLanguageText(WIFI_AVAILABLE);

	
    return iReturn;
}


/***
  * 功能：
		释放文本资源
  * 参数：
		1.void *pInArg	:	指向输入参数的指针
		2.int iInLen	:	输入参数的长度
		3.void *pOutArg :	指向传出参数的指针
		4.int iOutLen	:	输出参数的长度
  * 返回：
		成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiTextRes_Exit(void *pInArg, int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
	int i = 0;
	
	//释放左上角的文本
	free(pWiFiStrFrmName);

	for(i = 0; i < 5; i++)
	{
		free(pWiFiStrMenu[i]);
	}
	for(i = 0; i < WIFIITEM; i++)
	{
		free(pWiFiStrItem[i]);
	}
	
    return iReturn;
}


/**********************************************************************************
**			    			窗体的按键事件处理函数				 				 **
***********************************************************************************/
/***
  * 功能：
        窗体的按键按下事件处理函数
  * 参数：
        1.void *pInArg	:   指向输入参数的指针
        2.int iInLen	:	输入参数的长度
        3.void *pOutArg	:	指向传出参数的指针
        4.int iOutLen	:	输出参数的长度
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiWndKey_Down(void *pInArg, int iInLen, 
                             void *pOutArg, int iOutLen)
{
    int iReturn = 0;

    return iReturn;
}


/***
  * 功能：
        窗体的按键弹起事件处理函数
  * 参数：
        1.void *pInArg	:   指向输入参数的指针
        2.int iInLen	:	输入参数的长度
        3.void *pOutArg	:	指向传出参数的指针
        4.int iOutLen	:	输出参数的长度
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiWndKey_Up(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen)
{
    int iReturn = 0;
	
    return iReturn;
}


//read a line into buffer, excluding '\r' & '\n'
static char * mfgets(char * buffer, int size, FILE * stream)
{
    int index, ret;

    for (index = 0; index < size; index++)
    {
        ret = fgetc(stream);

        if ('\n' == ret || '\r' == ret)
        {
            buffer[index] = 0;
            return buffer;
        }
        else if (EOF == ret)
        {
            buffer[index] = 0;

            if (!index)
            {
                return NULL;
            }
            else
            {
                return buffer;
            }
        }

        buffer[index] = (char)ret;
    }

    buffer[size - 1] = 0;
    return buffer;
}


/*******************************************************************************
**			    		打开/关闭wifi按钮事件处理函数				 		  **
*******************************************************************************/
/***
  * 功能：
        打开WiFi down事件
  * 参数：
        1.void *pInArg	:   指向输入参数的指针
        2.int iInLen	:	输入参数的长度
        3.void *pOutArg	:	指向传出参数的指针
        4.int iOutLen	:	输出参数的长度
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiBtnEnableOn_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
	
	return iReturn;
}	


/***
  * 功能：
        关闭WiFi down事件
  * 参数：
        1.void *pInArg	:   指向输入参数的指针
        2.int iInLen	:	输入参数的长度
        3.void *pOutArg	:	指向传出参数的指针
        4.int iOutLen	:	输出参数的长度
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiBtnEnableOff_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
	return iReturn;
}                               


/***
  * 功能：
        打开WiFi up事件
  * 参数：
        1.void *pInArg	:   指向输入参数的指针
        2.int iInLen	:	输入参数的长度
        3.void *pOutArg	:	指向传出参数的指针
        4.int iOutLen	:	输出参数的长度
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiBtnEnableOn_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //错误标志、返回值定义
    int iReturn = 0;
	printf("on up\n");
	WriteWifiMsgQueue(ENUM_OPEN);

	return iReturn;
}  


/***
  * 功能：
        关闭WiFi up事件
  * 参数：
        1.void *pInArg	:   指向输入参数的指针
        2.int iInLen	:	输入参数的长度
        3.void *pOutArg	:	指向传出参数的指针
        4.int iOutLen	:	输出参数的长度
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
static int WiFiBtnEnableOff_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    int iReturn = 0;
	
	return iReturn;
}   

static int WiFiBtnItemSSID_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    int iReturn = 0;
	
	return iReturn;
}
static int WiFiBtnItemSSID_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    int iReturn = 0;
	
	printf("WiFiBtnItemSSID_Up %d\n", iOutLen);
	MutexLock(&pWifiMutex);
	
	memcpy(&stGetWifi, &(stWifi[iOutLen]), sizeof(WIFI_INFO));
	
	MutexUnlock(&pWifiMutex);
	
	return iReturn;
}


/*******************************************************************************
**			    			连接wifi事件处理函数				 		      **
*******************************************************************************/

static int WiFiBtnMenu_Down(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen)
{
	int iReturn = 0;

	printf("getwifi ssid %s  level %d\n", stGetWifi.ssid, stGetWifi.iLevel);
	return iReturn;	
}

static int WiFiBtnMenu_Up(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen)
{
	int iReturn = 0;
	
	return iReturn;	
}


/*******************************************************************************
**			    			连接wifi事件处理函数				 		      **
*******************************************************************************/
static void WifiOpen()
{
	WriteWifiMsgQueue(ENUM_SCAN);
}

static void WifiScan()
{
	vsystem("wpa_cli scan");
	MsecSleep(10000);
	WriteWifiMsgQueue(ENUM_SCAN_R);
}

static void WifiScan_r()
{
	FILE *fstream;
    char buffer[512] = {0};
    char buffer1[512] = {0};
	
	vsystem("wpa_cli scan_r > /mnt/sdcard/wifi/list.txt");
	MsecSleep(1000);

	vsystem("awk '{print $5}' /mnt/sdcard/wifi/list.txt | tail -n +3 > /mnt/sdcard/scan");
		
	MutexLock(&pWifiMutex);
	
    if (NULL == (fstream = fopen("/mnt/sdcard/scan", "r")))
    {
        perror("fopen");
        return;
    }
	int index = 0;
    while (NULL != mfgets(buffer, sizeof(buffer), fstream))
    {
        if (index >= MAX_SIGNUM)
        {
            break;
        }
        strncpy(stWifi[index].ssid, buffer, sizeof(stWifi[index].ssid) - 1);
        index++;
    }
    fclose(fstream);

	vsystem("awk '{print $3}' /mnt/sdcard/wifi/list.txt | tail -n +3 > /mnt/sdcard/scan");
		
    if (NULL == (fstream = fopen("/mnt/sdcard/scan", "r")))
    {
        perror("fopen");
        return;
    }
	index = 0;
    while (NULL != mfgets(buffer, sizeof(buffer), fstream))
    {
        if (index >= MAX_SIGNUM)
        {
            break;
        }
		stWifi[index].iLevel = atoi(buffer);
		stWifi[index].iCell = CalcWifiCell(stWifi[index].iLevel);
        index++;
    }
    fclose(fstream);
	
	SortByLevel(index);
	
	int i;
	for(i = 0; i < index; i++)
	{
		if(i < WIFIITEM)
		{
			snprintf(buffer1, sizeof(buffer1), "%s", stWifi[i].ssid);
			if(NULL == pWiFiStrItem[i])
			{
				free(pWiFiStrItem[i]);
				pWiFiStrItem[i] = NULL;
			}
			pWiFiStrItem[i] = TransString(buffer1);
			SetLabelText(pWiFiStrItem[i], pWiFiLblItem[i]);
			DisplayPicture(pWiFiItem[i]);
			DisplayLabel(pWiFiLblItem[i]);
		}
		printf("sig%d %s  %d %d\n", i, stWifi[i].ssid, stWifi[i].iCell, stWifi[i].iLevel);
	}
	
	MutexUnlock(&pWifiMutex);
	
	WriteWifiMsgQueue(ENUM_SCAN);
}

static void SortByLevel(int num)
{
	int i,j;
	WIFI_INFO stWifiTmp;

	for(i = 0; i < num; i++)
	{
		for(j = i; j < num; j++)
		{
			if(stWifi[i].iLevel < stWifi[j].iLevel)
			{
				memcpy(&stWifiTmp, &(stWifi[i]), sizeof(WIFI_INFO));
				memcpy(&(stWifi[i]), &(stWifi[j]), sizeof(WIFI_INFO));
				memcpy(&(stWifi[j]), &stWifiTmp, sizeof(WIFI_INFO));
			}
		}
	}
}

static int CalcWifiCell(int iLevel)
{
	int iReturn = 0;

	if(iLevel > 208)
		iReturn = 4;
	else if(iLevel > 193)
		iReturn = 3;
	else if(iLevel > 179)
		iReturn = 2;
	else if(iLevel > 165)
		iReturn = 1;
	else
		iReturn = 0;

	return iReturn;
}

static int Connect2Wifi(char *ssid, char *psk)
{
	char buff[512];
	FILE *fstream;
	vsystem("wpa_cli add_n | tail -n +2 > /mnt/sdcard/nid");
	
	if (NULL == (fstream = fopen("/mnt/sdcard/nid", "r")))
	{
		perror("fopen");
		return;
	}
	while (NULL != mfgets(buff, sizeof(buff), fstream))
	{
		
	}
	fclose(fstream);
}

