/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  wnd_frminit.c
* ժ    Ҫ��  ʵ�ֳ�ʼ������frminit�Ĵ��崦���̼߳���ز�������
*
* ��ǰ�汾��  v1.1.0
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "wnd_frminit.h"


/****************************************
* Ϊʵ�ִ���frminit����Ҫ���õ�����ͷ�ļ�
****************************************/
#include "wnd_frmmain.h"


/************************
* ����frminit�е�������Դ
************************/
//�����ϵ�����
//...

//��ť��������
//...


/************************
* ����frminit�е��ı���Դ
************************/
//״̬���ϵ��ı�
//...

//�����ϵ��ı�
//...

//��ť�����ı�
//...

//��Ϣ�����ı�
//...


/************************
* ����frminit�еĴ���ؼ�
************************/
static GUIWINDOW *pFrmInit = NULL;

//״̬�������桢��Ϣ��
static GUIPICTURE *pInitBgDesk = NULL;

//״̬���ϵĿؼ�
//...

//�����ϵĿؼ�
//...

//��ť���Ŀؼ�
//...

//��Ϣ���ϵĿؼ�
//...


/********************************
* ����frminit�е��ı���Դ������
********************************/
//��ʼ���ı���Դ
static int InitTextRes_Init(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);
//�ͷ��ı���Դ
static int InitTextRes_Exit(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);


/********************************
* ����frmInit�еĿؼ��¼�������
********************************/
//����İ��������¼�������
static int InitWndKey_Down(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
//����İ��������¼�������
static int InitWndKey_Up(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
//����Ĺ���ƶ��¼�������
static int InitWndMov_Cursor(void * pInArg, int iInLen,
                             void * pOutArg, int iOutLen);

//�����Ͽؼ����¼�������
//...

//��ť���ؼ����¼�������
//...

//��Ϣ���ؼ����¼�������
//...


/********************************
* ����frminit�еĴ����¼�������
********************************/
static int InitErrProc_Func(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);


/********************************
* ����frminit�е������ڲ�������
********************************/
//...


/***
  * ���ܣ�
        ����frminit�ĳ�ʼ����������������ؼ���ע����Ϣ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmInitInit(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;

    //�õ���ǰ�������
    pFrmInit = (GUIWINDOW *) pWndObj;

    //��ʼ��������Դ
    //...

    //��ʼ���ı���Դ
    //���GUI���ڶ�����ԣ��ڴ˴���ö�Ӧ���Ե��ı���Դ
    //��ʼ���ı���Դ�����ڽ����ı�CreateText()������ǩCreateLabel()֮ǰ
    /****************************************************************/
    InitTextRes_Init(NULL, 0, NULL, 0);

    //��������ؼ�
    /****************************************************************/
    //����״̬�������桢��Ϣ��
    pInitBgDesk = CreatePicture(0, 0, 800, 480,
                                RESFILE_PATH"/bitmap/bg_init.bmp");
    //����״̬���ϵĿؼ�
    //...
    //���������ϵĿؼ�
    //...
    //������ť���Ŀؼ�
    //...
    //������Ϣ���ϵĿؼ�
    //...

    //���ô���ؼ��Ļ�ˢ�����ʼ�����
    /****************************************************************/
    //���������ϵĿؼ�
    //...
    //���ð�ť���Ŀؼ�
    //...

    //ע�ᴰ��ؼ���ֻ����Щ��Ҫ�����¼��Ŀؼ�����
    //������ÿؼ�û�л��߲���Ҫ��Ӧ�����¼�����������ע��
    //ע�ᴰ��ؼ�������ע����Ϣ������֮ǰ����
    //***************************************************************/
    //ע�ᴰ��(��Ϊ���еİ���������¼���ͳһ�ɴ�����д���)
    AddWindowComp(OBJTYP_GUIWINDOW, sizeof(GUIWINDOW), pFrmInit,
                  pFrmInit);
    //ע�������ϵĿؼ�
    //...
    //ע�ᰴť���Ŀؼ�
    //...
    //ע����Ϣ���ϵĿؼ�
    //...

    //ע����Ϣ�������������Ϣ���ն���δ��ע�ᵽ���壬���޷�����������Ϣ
    //���˴��Ĳ���Ӧ����ע�ᴰ��ؼ��Ļ����Ͻ���
    //ע����Ϣ������������ע�ᴰ��ؼ�֮�����
    //ע����Ϣ�����������ڳ�������ǰ���½���
    //***************************************************************/
    pMsg = GetCurrMessage();
    //ע�ᴰ��İ�����Ϣ����
    LoginMessageReg(GUIMESSAGE_KEY_DOWN, pFrmInit,
                    InitWndKey_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_KEY_UP, pFrmInit,
                    InitWndKey_Up, NULL, 0, pMsg);
    //ע�ᴰ��Ĺ����Ϣ����
    LoginMessageReg(GUIMESSAGE_MOV_CURSOR, pFrmInit,
                    InitWndMov_Cursor, NULL, 0, pMsg);
    //ע�������Ͽؼ�����Ϣ����
    //...
    //ע�ᰴť���ؼ�����Ϣ����
    //...
    //ע����Ϣ���Ͽؼ�����Ϣ����
    //...
    //ע�ᴰ��Ĵ�������
    LoginMessageReg(GUIMESSAGE_ERR_PROC, pFrmInit,
                    InitErrProc_Func, NULL, 0, pMsg);

    return iReturn;
}


/***
  * ���ܣ�
        ����frminit���˳��������ͷ�������Դ
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmInitExit(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������

    //�õ���ǰ�������
    pFrmInit = (GUIWINDOW *) pWndObj;

    //�����Ϣ�����е���Ϣע����
    //***************************************************************/
    ClearMessageReg(GetCurrMessage());

    //�ӵ�ǰ������ע������ؼ�
    //***************************************************************/
    ClearWindowComp(pFrmInit);

    //���ٴ���ؼ�
    //***************************************************************/
    //����״̬�������桢��Ϣ��
    DestroyPicture(&pInitBgDesk);
    //����״̬���ϵĿؼ�
    //...
    //���������ϵĿؼ�
    //...
    //���ٰ�ť���Ŀؼ�
    //...
    //������Ϣ���ϵĿؼ�
    //...

    //�ͷ��ı���Դ
    //***************************************************************/
    InitTextRes_Exit(NULL, 0, NULL, 0);

    //�ͷ�������Դ
    //***************************************************************/
    //�ͷŰ�ť��������
    //...

    return iReturn;
}


/***
  * ���ܣ�
        ����frminit�Ļ��ƺ�����������������
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmInitPaint(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    //�õ���ǰ�������
    pFrmInit = (GUIWINDOW *) pWndObj;

    //��ʾ״̬�������桢��Ϣ��
    iReturn = DisplayPicture(pInitBgDesk);
    //��ʾ״̬���ϵĿؼ�
    //...
    //��ʾ�����ϵĿؼ�
    //...
    //��ʾ��ť���Ŀؼ�
    //...
    //��ʾ��Ϣ���ϵĿؼ�
    //...

    return iReturn;
}


/***
  * ���ܣ�
        ����frminit��ѭ�����������д���ѭ��
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmInitLoop(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIWINDOW *pWnd = NULL;

    //��ֹ��ֹͣ����ѭ��
    SendWndMsg_LoopDisable(pWndObj);

    //���ô�����
    pWnd = pWndObj;
    pWnd->Visible.iCursor = 0;

    //����frmmain
    pWnd = CreateWindow(0, 0, 800, 480,
                        FrmMainInit, FrmMainExit,
                        FrmMainPaint, FrmMainLoop,
                        FrmMainPause, FrmMainResume,
                        NULL);          //pWnd�ɵ����߳��ͷ�
    SendWndMsg_WindowExit(pFrmInit);    //���ʹ�����Ϣ�Ա��˳���ǰ����
    SendSysMsg_ThreadCreate(pWnd);      //����ϵͳ��Ϣ�Ա㽨���µĴ����߳�

    return iReturn;
}


/***
  * ���ܣ�
        ����frminit�Ĺ����������д������ǰԤ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmInitPause(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


/***
  * ���ܣ�
        ����frminit�Ļָ����������д���ָ�ǰԤ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmInitResume(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


//��ʼ���ı���Դ
static int InitTextRes_Init(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    //��ʼ��״̬���ϵ��ı�
    //...
    //��ʼ�������ϵ��ı�
    //...
    //��ʼ����ť�����ı�
    //...
    //��ʼ����Ϣ���ϵ��ı�
    //...

    return iReturn;
}


//�ͷ��ı���Դ
static int InitTextRes_Exit(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    //�ͷ�״̬���ϵ��ı�
    //...
    //�ͷ������ϵ��ı�
    //...
    //�ͷŰ�ť�����ı�
    //...
    //�ͷ���Ϣ���ϵ��ı�
    //...

    return iReturn;
}


//����İ��������¼�������
static int InitWndKey_Down(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
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


//����İ��������¼�������
static int InitWndKey_Up(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
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


//����Ĺ���ƶ��¼�������
static int InitWndMov_Cursor(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


//�����¼�������
static int InitErrProc_Func(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    //����ʵ����������д�����

    return iReturn;
}

