/*******************************************************************************
* Copyright(c)2014�������Ϣ����(����)���޹�˾
*
* All rights reserved
*
* �ļ����ƣ�  wnd_frmwifi.c
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

#include "wnd_frmwifi.h"

#include "wnd_msgqueue.h"

/*******************************************************************************
**						Ϊʵ�ִ���frmwifi����Ҫ���õ�����ͷ�ļ� 			  **
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
**									�궨�� 				 					  **
*******************************************************************************/	


/*******************************************************************************
**								��������				 					  **
*******************************************************************************/	
GUITHREAD thdWifi = -1;
static GUIMUTEX pWifiMutex;
static WIFI_INFO stGetWifi;
char path[512] = "/mnt/sdcard/wifi/list.txt";
static WIFI_INFO stWifi[MAX_SIGNUM];

/* ѡ��״̬ʱwifi����ͼ�� */
static char *g_pWiFiSecEncryTypePath[] = {
BmpFileDirectory"ico_wifi_no_encrypt_press.bmp", 
BmpFileDirectory"ico_wifi_encrypt_press.bmp"};

/* ѡ��״̬ʱwifi�ź�ǿ��ͼ�� */
/*static char *g_pWiFiSecStrengthPath[]  = {
BmpFileDirectory"ico_wifi_empty_press.bmp", BmpFileDirectory"ico_wifi_quar_press.bmp", 
BmpFileDirectory"ico_wifi_half_press.bmp", BmpFileDirectory"ico_wifi_three_quars_press.bmp",
BmpFileDirectory"ico_wifi_full_press.bmp"};*/

/* δѡ��״̬ʱwifi����ͼ�� */
static char *g_pWiFiUnSecEncryTypePath[] = {
BmpFileDirectory"ico_wifi_no_encrypt_unpress.bmp", 
BmpFileDirectory"ico_wifi_encrypt_unpress.bmp"};

/* δѡ��״̬ʱwifi�ź�ǿ��ͼ�� */
static char *g_pWiFiUnSecStrengthPath[]  = {
BmpFileDirectory"ico_wifi_empty_unpress.bmp", BmpFileDirectory"ico_wifi_quar_unpress.bmp", 
BmpFileDirectory"ico_wifi_half_unpress.bmp", BmpFileDirectory"ico_wifi_three_quars_unpress.bmp",
BmpFileDirectory"ico_wifi_full_unpress.bmp"};


unsigned long g_Status = 0;						// wifi�ĵ�ǰ״̬��ÿһλ����һ��״̬��ͨ���궨����в���


/*******************************************************************************
**							����frmwifi�еĿؼ����岿��					  	  **
*******************************************************************************/
static GUIWINDOW *pFrmWiFi = NULL;
static GUIFONT *pWifiFntBlack = NULL;     		//���ⰴť������

/**********************************�����ؼ�����********************************/ 
static GUIPICTURE *pWiFiBtnLeftBg  = NULL;       
static GUIPICTURE *pWiFiInfoBg = NULL;

/**********************************�˵��ؼ�����********************************/ 
static GUIPICTURE *pWiFiMenuBg = NULL;
static GUIPICTURE *pWiFiMenu[5] = {NULL};
static GUILABEL *pWiFiLblMenu[5] = {NULL};
static GUICHAR *pWiFiStrMenu[5] = {NULL};

/******************************����������ؼ�����******************************/
static GUICHAR *pWiFiStrFrmName = NULL;	  	  	//�������ϽǱ������ı�
static GUILABEL *pWiFiLblFrmName = NULL;		//���ϽǴ������ֵ�Label

/***************************�򿪹ر�wifi�ڵĿؼ�����***************************/
static GUICHAR *pWiFiStrOnOffInfo = NULL;

static GUILABEL *pWiFiLblOnOffInfo = NULL;

static GUIPICTURE *pWiFiBtnOnOffBg		= NULL;		
static GUIPICTURE *pWiFiBtnREnableOn	= NULL; 
static GUIPICTURE *pWiFiBtnREnableOff	= NULL; 


/****************************������wifi�ڵĿؼ�����****************************/


/***************************ɨ�赽��wifi�ڵĿؼ�����***************************/
#define WIFIITEM   10
static GUIPICTURE *pWiFiItem[WIFIITEM] = {NULL};
static GUILABEL *pWiFiLblItem[WIFIITEM] = {NULL};
static GUICHAR *pWiFiStrItem[WIFIITEM] = {NULL};

/*****************************�Ҳ�˵����ؼ�����*******************************/

/*******************************************************************************
**	    	����frmwifi�еĳ�ʼ���ı���Դ�� �ͷ��ı���Դ�������岿��		  **
*******************************************************************************/
static int WiFiTextRes_Init(void *pInArg, int iInLen, 
							void *pOutArg, int iOutLen);
static int WiFiTextRes_Exit(void *pInArg, int iInLen, 
							void *pOutArg, int iOutLen);


/*******************************************************************************
**			    	����frmwifi�еĿؼ��¼����������岿��				  	  **
*******************************************************************************/

/***************************����İ����¼�������*****************************/
static int WiFiWndKey_Down(void *pInArg, int iInLen, 
							  void *pOutArg, int iOutLen);
static int WiFiWndKey_Up(void *pInArg, int iInLen, 
							void *pOutArg, int iOutLen);

/**************************�˵����ؼ����¼�������****************************/
static int WiFiBtnMenu_Down(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen);
static int WiFiBtnMenu_Up(void *pInArg, int iInLen, 
                           void *pOutArg, int iOutLen);



/************************��/�ر�wifi��ť�¼�������*************************/
static int WiFiBtnEnableOn_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);
static int WiFiBtnEnableOff_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);

static int WiFiBtnEnableOn_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);
static int WiFiBtnEnableOff_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);


/**************************����wifi��ť�¼�������****************************/
static int WiFiBtnItemSSID_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);
static int WiFiBtnItemSSID_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen);



/*******************************************************************************
**			    			�����ڵ�������������					 		  **
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
  * ���ܣ�
        ����FrmWiFi�ĳ�ʼ����������������ؼ���ע����Ϣ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmWiFiInit(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
	int i = 0;

	GUIMESSAGE *pMsg = NULL;
    //�õ���ǰ�������
    pFrmWiFi = (GUIWINDOW *) pWndObj;
	
    pWifiFntBlack = CreateFont(FontFileDirectory"unicode.fnt", 
                                 16, 16, 0x0000000, 0xFFFFFFFF);

   	//��ʼ���ı���Դ�����ڽ����ı�CreateText()������ǩCreateLabel()֮ǰ
    WiFiTextRes_Init(NULL, 0, NULL, 0);

	/* ���汳��ͼƬ */
	pWiFiBtnLeftBg = CreatePicture(0, 0, 681, 480, 
                                     	BmpFileDirectory"bg_wifi.bmp");
	/*�˵�����*/
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
	
	/* �������Label */
	pWiFiLblFrmName = CreateLabel(0, 20, 100, 24, pWiFiStrFrmName);
	SetLabelAlign(GUILABEL_ALIGN_CENTER, pWiFiLblFrmName);	
	SetLabelFont(pWifiFntBlack, pWiFiLblFrmName);

	/* �򿪹ر�WiFi����ؼ����� */	
	pWiFiBtnREnableOn   = CreatePicture(350, 45, 84, 32, BmpFileDirectory"btn_wifi_on_unpress.bmp");
	pWiFiBtnREnableOff  = CreatePicture(434, 45, 84, 32, BmpFileDirectory"btn_wifi_off_unpress.bmp");

	pWiFiBtnOnOffBg = CreatePicture(28, 74, 313, 24, BmpFileDirectory"btn_wifi_ssid_unpress.bmp");
	pWiFiLblOnOffInfo = CreateLabel(28, 76, 300, 24,  pWiFiStrOnOffInfo);
	
	/* wifi�б� */
	for(i = 0; i < WIFIITEM; i++)
	{
		pWiFiItem[i] = CreatePicture(10, 170+(i*30), 313, 28, BmpFileDirectory"btn_wifi_ssid_unpress.bmp");
		pWiFiLblItem[i] = CreateLabel(10, 170+(i*30), 313, 28, pWiFiStrItem[i]);
		SetLabelFont(pWifiFntBlack, pWiFiLblItem[i]);
	}
	
    AddWindowComp(OBJTYP_GUIWINDOW, sizeof(GUIWINDOW), pFrmWiFi, 
                  pFrmWiFi);
	
	//ע�������ϵĿؼ�
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
    
    //ע�ᴰ��İ�����Ϣ����
    LoginMessageReg(GUIMESSAGE_KEY_DOWN, pFrmWiFi, 
                    WiFiWndKey_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_KEY_UP, pFrmWiFi, 
                    WiFiWndKey_Up, NULL, 0, pMsg);


    //ע�������Ͽؼ�����Ϣ����
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
  * ���ܣ�
        ����FrmWiFi���˳��������ͷ�������Դ
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmWiFiExit(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
	int i = 0;

    GUIMESSAGE *pMsg = NULL;
    //�õ���ǰ�������
    pFrmWiFi = (GUIWINDOW *) pWndObj;

	//�����Ϣ�����е���Ϣע����
    //***************************************************************/
    pMsg = GetCurrMessage();
    ClearMessageReg(pMsg);

    //�ӵ�ǰ������ע������ؼ�
    //***************************************************************/
    ClearWindowComp(pFrmWiFi);

    //���ٴ���ؼ�
    //***************************************************************/
    //�������汳��ͼƬ
    DestroyPicture(&pWiFiBtnLeftBg);

	//���ٲ˵�
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

    //���������ϵĿؼ�
    DestroyPicture(&pWiFiBtnREnableOn);
	DestroyPicture(&pWiFiBtnREnableOff);
	DestroyPicture(&pWiFiBtnOnOffBg);

	//���ٴ������ϽǴ���Label
	DestroyLabel(&pWiFiLblFrmName);
	DestroyLabel(&pWiFiLblOnOffInfo);
	
	DestroyFont(&pWifiFntBlack);
	//�ͷ��ı���Դ
    //***************************************************************/
    WiFiTextRes_Exit(NULL, 0, NULL, 0);
	
    return iReturn;
}


/***
  * ���ܣ�
        ����FrmWiFi�Ļ��ƺ�����������������
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmWiFiPaint(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
	int i = 0;
    //�õ���ǰ�������
    pFrmWiFi = (GUIWINDOW *) pWndObj;

    //��ʾ���汳��ͼƬ
    DisplayPicture(pWiFiBtnLeftBg);

	//��ʾ�˵�
    DisplayPicture(pWiFiMenuBg);
	for(i = 0; i < 5; i++)
	{
		DisplayPicture(pWiFiMenu[i]);
		DisplayLabel(pWiFiLblMenu[i]);
	}

	//��ʾ״̬���ϵ�ͼƬ
	DisplayPicture(pWiFiBtnOnOffBg);
	
	//��ʾ�������ϽǴ���Label
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

	//��ʼ��wifi������wifi�߳�
	InitMutex(&pWifiMutex, NULL);
	InitWifiQueue(10);
	ThreadCreate(&thdWifi, NULL, DefaultWifiThread, NULL);

    return iReturn;
}


/***
  * ���ܣ�
        ����FrmWiFi��ѭ�����������д���ѭ��
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmWiFiLoop(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


/***
  * ���ܣ�
        ����FrmWiFi�Ĺ����������д������ǰԤ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmWiFiPause(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


/***
  * ���ܣ�
        ����FrmWiFi�Ļָ����������д���ָ�ǰԤ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmWiFiResume(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


/*******************************************************************************
**	    	����frmwifi�еĳ�ʼ���ı���Դ�� �ͷ��ı���Դ�������岿��		  **
*******************************************************************************/
/***
  * ���ܣ�
		��ʼ���ı���Դ
  * ������
		1.void *pInArg	:	ָ�����������ָ��
		2.int iInLen	:	��������ĳ���
		3.void *pOutArg :	ָ�򴫳�������ָ��
		4.int iOutLen	:	��������ĳ���
  * ���أ�
		�ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
static int WiFiTextRes_Init(void *pInArg, int iInLen, 
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
	int i;
	//�������Ͻǵ��ı�
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

	//�����ϵ��ı�
	//pWiFiStrLEnable = GetCurrLanguageText(WIFI_STARTWLAN);
	//pWiFiStrConnectedCap = GetCurrLanguageText(WIFI_CONNECTED_CAP);
	//pWiFiStrScanCap =  GetCurrLanguageText(WIFI_AVAILABLE);

	
    return iReturn;
}


/***
  * ���ܣ�
		�ͷ��ı���Դ
  * ������
		1.void *pInArg	:	ָ�����������ָ��
		2.int iInLen	:	��������ĳ���
		3.void *pOutArg :	ָ�򴫳�������ָ��
		4.int iOutLen	:	��������ĳ���
  * ���أ�
		�ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
static int WiFiTextRes_Exit(void *pInArg, int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
	int i = 0;
	
	//�ͷ����Ͻǵ��ı�
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
**			    			����İ����¼�������				 				 **
***********************************************************************************/
/***
  * ���ܣ�
        ����İ��������¼�������
  * ������
        1.void *pInArg	:   ָ�����������ָ��
        2.int iInLen	:	��������ĳ���
        3.void *pOutArg	:	ָ�򴫳�������ָ��
        4.int iOutLen	:	��������ĳ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
static int WiFiWndKey_Down(void *pInArg, int iInLen, 
                             void *pOutArg, int iOutLen)
{
    int iReturn = 0;

    return iReturn;
}


/***
  * ���ܣ�
        ����İ��������¼�������
  * ������
        1.void *pInArg	:   ָ�����������ָ��
        2.int iInLen	:	��������ĳ���
        3.void *pOutArg	:	ָ�򴫳�������ָ��
        4.int iOutLen	:	��������ĳ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
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
**			    		��/�ر�wifi��ť�¼�������				 		  **
*******************************************************************************/
/***
  * ���ܣ�
        ��WiFi down�¼�
  * ������
        1.void *pInArg	:   ָ�����������ָ��
        2.int iInLen	:	��������ĳ���
        3.void *pOutArg	:	ָ�򴫳�������ָ��
        4.int iOutLen	:	��������ĳ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
static int WiFiBtnEnableOn_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
	
	return iReturn;
}	


/***
  * ���ܣ�
        �ر�WiFi down�¼�
  * ������
        1.void *pInArg	:   ָ�����������ָ��
        2.int iInLen	:	��������ĳ���
        3.void *pOutArg	:	ָ�򴫳�������ָ��
        4.int iOutLen	:	��������ĳ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
static int WiFiBtnEnableOff_Down(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
	return iReturn;
}                               


/***
  * ���ܣ�
        ��WiFi up�¼�
  * ������
        1.void *pInArg	:   ָ�����������ָ��
        2.int iInLen	:	��������ĳ���
        3.void *pOutArg	:	ָ�򴫳�������ָ��
        4.int iOutLen	:	��������ĳ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
static int WiFiBtnEnableOn_Up(void *pInArg,   int iInLen, 
                               void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
	printf("on up\n");
	WriteWifiMsgQueue(ENUM_OPEN);

	return iReturn;
}  


/***
  * ���ܣ�
        �ر�WiFi up�¼�
  * ������
        1.void *pInArg	:   ָ�����������ָ��
        2.int iInLen	:	��������ĳ���
        3.void *pOutArg	:	ָ�򴫳�������ָ��
        4.int iOutLen	:	��������ĳ���
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
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
**			    			����wifi�¼�������				 		      **
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
**			    			����wifi�¼�������				 		      **
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

