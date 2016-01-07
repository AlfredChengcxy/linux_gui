/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  wnd_frmmain.c
* ժ    Ҫ��  ʵ��������frmmain�Ĵ��崦���̼߳���ز�������
*
* ��ǰ�汾��  v1.1.0
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "wnd_frmmain.h"


/****************************************
* Ϊʵ�ִ���frmmain����Ҫ���õ�����ͷ�ļ�
****************************************/
#include "input_china_pinyin.h"


/************************
* ����frmmain�е�������Դ
************************/
//�����ϵ�����
//...

//��ť��������
//...


/************************
* ����frmmain�е��ı���Դ
************************/
//״̬���ϵ��ı�
//...

//�����ϵ��ı�
static GUICHAR *pMainStrPinyin = NULL;
static GUICHAR *pMainStrSelect = NULL;
static GUICHAR *pMainStrWord0 = NULL;
static GUICHAR *pMainStrWord1 = NULL;
static GUICHAR *pMainStrWord2 = NULL;
static GUICHAR *pMainStrWord3 = NULL;
static GUICHAR *pMainStrWord4 = NULL;
static GUICHAR *pMainStrWord5 = NULL;
static GUICHAR *pMainStrWord6 = NULL;
static GUICHAR *pMainStrWord7 = NULL;
static GUICHAR *pMainStrWord8 = NULL;
static GUICHAR *pMainStrWord9 = NULL;
static GUICHAR *pMainStrUp = NULL;
static GUICHAR *pMainStrDown = NULL;
static GUICHAR *pMainStrSet = NULL;
static GUICHAR *pMainStrA = NULL;
static GUICHAR *pMainStrB = NULL;
static GUICHAR *pMainStrC = NULL;
static GUICHAR *pMainStrD = NULL;
static GUICHAR *pMainStrE = NULL;
static GUICHAR *pMainStrF = NULL;
static GUICHAR *pMainStrG = NULL;
static GUICHAR *pMainStrH = NULL;
static GUICHAR *pMainStrI = NULL;
static GUICHAR *pMainStrJ = NULL;
static GUICHAR *pMainStrK = NULL;
static GUICHAR *pMainStrL = NULL;
static GUICHAR *pMainStrM = NULL;
static GUICHAR *pMainStrN = NULL;
static GUICHAR *pMainStrO = NULL;
static GUICHAR *pMainStrP = NULL;
static GUICHAR *pMainStrQ = NULL;
static GUICHAR *pMainStrR = NULL;
static GUICHAR *pMainStrS = NULL;
static GUICHAR *pMainStrT = NULL;
static GUICHAR *pMainStrU = NULL;
static GUICHAR *pMainStrV = NULL;
static GUICHAR *pMainStrW = NULL;
static GUICHAR *pMainStrX = NULL;
static GUICHAR *pMainStrY = NULL;
static GUICHAR *pMainStrZ = NULL;
static GUICHAR *pMainStrBackspace = NULL;
static GUICHAR *pMainStrEnter = NULL;
//...

//��ť�����ı�
//...

//��Ϣ�����ı�
//...


/************************
* ����frmmain�еĴ���ؼ�
************************/
static GUIWINDOW *pFrmMain = NULL;

//״̬�������桢��Ϣ��
static GUIPICTURE *pMainBarStatus = NULL;
static GUIPICTURE *pMainBgDesk = NULL;
static GUIPICTURE *pMainBarInfo = NULL;
//...

//״̬���ϵĿؼ�
//...

//�����ϵĿؼ�
static GUILABEL *pMainLblPinyin = NULL;
static GUILABEL *pMainLblSelect = NULL;
static GUILABEL *pMainLblWord0 = NULL;
static GUILABEL *pMainLblWord1 = NULL;
static GUILABEL *pMainLblWord2 = NULL;
static GUILABEL *pMainLblWord3 = NULL;
static GUILABEL *pMainLblWord4 = NULL;
static GUILABEL *pMainLblWord5 = NULL;
static GUILABEL *pMainLblWord6 = NULL;
static GUILABEL *pMainLblWord7 = NULL;
static GUILABEL *pMainLblWord8 = NULL;
static GUILABEL *pMainLblWord9 = NULL;
static GUILABEL *pMainLblUp = NULL;
static GUILABEL *pMainLblDown = NULL;
static GUILABEL *pMainLblSet = NULL;
static GUILABEL *pMainLblA = NULL;
static GUILABEL *pMainLblB = NULL;
static GUILABEL *pMainLblC = NULL;
static GUILABEL *pMainLblD = NULL;
static GUILABEL *pMainLblE = NULL;
static GUILABEL *pMainLblF = NULL;
static GUILABEL *pMainLblG = NULL;
static GUILABEL *pMainLblH = NULL;
static GUILABEL *pMainLblI = NULL;
static GUILABEL *pMainLblJ = NULL;
static GUILABEL *pMainLblK = NULL;
static GUILABEL *pMainLblL = NULL;
static GUILABEL *pMainLblM = NULL;
static GUILABEL *pMainLblN = NULL;
static GUILABEL *pMainLblO = NULL;
static GUILABEL *pMainLblP = NULL;
static GUILABEL *pMainLblQ = NULL;
static GUILABEL *pMainLblR = NULL;
static GUILABEL *pMainLblS = NULL;
static GUILABEL *pMainLblT = NULL;
static GUILABEL *pMainLblU = NULL;
static GUILABEL *pMainLblV = NULL;
static GUILABEL *pMainLblW = NULL;
static GUILABEL *pMainLblX = NULL;
static GUILABEL *pMainLblY = NULL;
static GUILABEL *pMainLblZ = NULL;
static GUILABEL *pMainLblBackspace = NULL;
static GUILABEL *pMainLblEnter = NULL;
//...

//��ť���Ŀؼ�
//...

//��Ϣ���ϵĿؼ�
//...


/********************************
* ����frmmain�е��ı���Դ������
********************************/
//��ʼ���ı���Դ
static int MainTextRes_Init(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);
//�ͷ��ı���Դ
static int MainTextRes_Exit(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);


/********************************
* ����frmmain�еĿؼ��¼�������
********************************/
//����İ��������¼�������
static int MainWndKey_Down(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
//����İ��������¼�������
static int MainWndKey_Up(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
//����Ĺ���ƶ��¼�������
static int MainWndMov_Cursor(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);

//�����Ͽؼ����¼�������
static int MainLblWord0_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord0_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord1_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord1_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord2_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord2_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord3_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord3_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord4_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord4_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord5_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord5_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord6_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord6_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord7_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord7_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord8_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord8_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblWord9_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblWord9_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
static int MainLblUp_Down(void *pInArg, int iInLen,
                          void *pOutArg, int iOutLen);
static int MainLblUp_Up(void *pInArg, int iInLen,
                        void *pOutArg, int iOutLen);
static int MainLblDown_Down(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);
static int MainLblDown_Up(void *pInArg, int iInLen,
                          void *pOutArg, int iOutLen);
static int MainLblA_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblA_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblB_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblB_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblC_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblC_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblD_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblD_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblE_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblE_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblF_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblF_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblG_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblG_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblH_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblH_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblI_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblI_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblJ_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblJ_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblK_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblK_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblL_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblL_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblM_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblM_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblN_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblN_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblO_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblO_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblP_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblP_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblQ_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblQ_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblR_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblR_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblS_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblS_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblT_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblT_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblU_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblU_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblV_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblV_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblW_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblW_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblX_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblX_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblY_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblY_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblZ_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen);
static int MainLblZ_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen);
static int MainLblBackspace_Down(void *pInArg, int iInLen,
                                 void *pOutArg, int iOutLen);
static int MainLblBackspace_Up(void *pInArg, int iInLen,
                               void *pOutArg, int iOutLen);
static int MainLblEnter_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen);
static int MainLblEnter_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen);
//...

//��ť���ؼ����¼�������
//...

//��Ϣ���ؼ����¼�������
//...


/********************************
* ����frmmain�еĴ����¼�������
********************************/
static int MainErrProc_Func(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen);


/********************************
* ����frmmain�е������ڲ����ݱ���
********************************/
static WordList *pMainWordSet = NULL;


/********************************
* ����frmmain�е������ڲ�������
********************************/
static int Main_AddPinyinChar(char cAddChar, GUILABEL *pLblChar);
static int Main_ViewWordList(void);
static int Main_WordTurnPage(int iTurnFlag, GUILABEL *pLblTurn);
static int Main_SelectPinyinWord(int iSelOff, GUILABEL *pLblWord);


/***
  * ���ܣ�
        ����frmmain�ĳ�ʼ����������������ؼ���ע����Ϣ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmMainInit(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIMESSAGE *pMsg = NULL;

    //�õ���ǰ�������
    pFrmMain = (GUIWINDOW *) pWndObj;

    //��ʼ��������Դ
    //...

    //��ʼ���ı���Դ
    //���GUI���ڶ�����ԣ��ڴ˴���ö�Ӧ���Ե��ı���Դ
    //��ʼ���ı���Դ�����ڽ����ı�CreateText()������ǩCreateLabel()֮ǰ
    /****************************************************************/
    MainTextRes_Init(NULL, 0, NULL, 0);

    //��������ؼ�
    /****************************************************************/
    //����״̬�������桢��Ϣ��
    pMainBarStatus = CreatePicture(0, 0, 800, 30,
                                   RESFILE_PATH"/bitmap/bar_status.bmp");
    pMainBgDesk = CreatePicture(0, 30, 800, 420,
                                RESFILE_PATH"/bitmap/bg_main.bmp");
    pMainBarInfo = CreatePicture(0, 450, 800, 30,
                                 RESFILE_PATH"/bitmap/bar_info.bmp");
    //����״̬���ϵĿؼ�
    //...
    //���������ϵĿؼ�
    pMainLblPinyin = CreateLabel(150, 150, 50, 20, pMainStrPinyin);
    pMainLblSelect = CreateLabel(250, 150, 50, 20, pMainStrSelect);
    pMainLblWord0 = CreateLabel(150, 175, 20, 20, pMainStrWord0);
    pMainLblWord1 = CreateLabel(170, 175, 20, 20, pMainStrWord1);
    pMainLblWord2 = CreateLabel(190, 175, 20, 20, pMainStrWord2);
    pMainLblWord3 = CreateLabel(210, 175, 20, 20, pMainStrWord3);
    pMainLblWord4 = CreateLabel(230, 175, 20, 20, pMainStrWord4);
    pMainLblWord5 = CreateLabel(250, 175, 20, 20, pMainStrWord5);
    pMainLblWord6 = CreateLabel(270, 175, 20, 20, pMainStrWord6);
    pMainLblWord7 = CreateLabel(290, 175, 20, 20, pMainStrWord7);
    pMainLblWord8 = CreateLabel(310, 175, 20, 20, pMainStrWord8);
    pMainLblWord9 = CreateLabel(330, 175, 20, 20, pMainStrWord9);
    pMainLblUp = CreateLabel(450, 175, 100, 20, pMainStrUp);
    pMainLblDown = CreateLabel(550, 175, 100, 20, pMainStrDown);
    pMainLblSet = CreateLabel(150, 200, 500, 100, pMainStrSet);
    pMainLblQ = CreateLabel(150, 300, 50, 50, pMainStrQ);
    pMainLblW = CreateLabel(200, 300, 50, 50, pMainStrW);
    pMainLblE = CreateLabel(250, 300, 50, 50, pMainStrE);
    pMainLblR = CreateLabel(300, 300, 50, 50, pMainStrR);
    pMainLblT = CreateLabel(350, 300, 50, 50, pMainStrT);
    pMainLblY = CreateLabel(400, 300, 50, 50, pMainStrY);
    pMainLblU = CreateLabel(450, 300, 50, 50, pMainStrU);
    pMainLblI = CreateLabel(500, 300, 50, 50, pMainStrI);
    pMainLblO = CreateLabel(550, 300, 50, 50, pMainStrO);
    pMainLblP = CreateLabel(600, 300, 50, 50, pMainStrP);
    pMainLblA = CreateLabel(150, 350, 50, 50, pMainStrA);
    pMainLblS = CreateLabel(200, 350, 50, 50, pMainStrS);
    pMainLblD = CreateLabel(250, 350, 50, 50, pMainStrD);
    pMainLblF = CreateLabel(300, 350, 50, 50, pMainStrF);
    pMainLblG = CreateLabel(350, 350, 50, 50, pMainStrG);
    pMainLblH = CreateLabel(400, 350, 50, 50, pMainStrH);
    pMainLblJ = CreateLabel(450, 350, 50, 50, pMainStrJ);
    pMainLblK = CreateLabel(500, 350, 50, 50, pMainStrK);
    pMainLblL = CreateLabel(550, 350, 50, 50, pMainStrL);
    pMainLblBackspace = CreateLabel(600, 350, 50, 50, pMainStrBackspace);
    pMainLblZ = CreateLabel(150, 400, 50, 50, pMainStrZ);
    pMainLblX = CreateLabel(200, 400, 50, 50, pMainStrX);
    pMainLblC = CreateLabel(250, 400, 50, 50, pMainStrC);
    pMainLblV = CreateLabel(300, 400, 50, 50, pMainStrV);
    pMainLblB = CreateLabel(350, 400, 50, 50, pMainStrB);
    pMainLblN = CreateLabel(400, 400, 50, 50, pMainStrN);
    pMainLblM = CreateLabel(450, 400, 50, 50, pMainStrM);
    pMainLblEnter = CreateLabel(500, 400, 100, 50, pMainStrEnter);
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
    AddWindowComp(OBJTYP_GUIWINDOW, sizeof(GUIWINDOW), pFrmMain,
                  pFrmMain);
    //ע�������ϵĿؼ�
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord0,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord1,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord2,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord3,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord4,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord5,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord6,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord7,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord8,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblWord9,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblUp,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblDown,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblA,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblB,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblC,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblD,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblE,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblF,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblG,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblH,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblI,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblJ,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblK,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblL,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblM,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblN,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblO,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblP,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblQ,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblR,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblS,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblT,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblU,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblV,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblW,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblX,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblY,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblZ,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblBackspace,
                  pFrmMain);
    AddWindowComp(OBJTYP_GUILABEL, sizeof(GUILABEL), pMainLblEnter,
                  pFrmMain);
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
    LoginMessageReg(GUIMESSAGE_KEY_DOWN, pFrmMain,
                    MainWndKey_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_KEY_UP, pFrmMain,
                    MainWndKey_Up, NULL, 0, pMsg);
    //ע�ᴰ��Ĺ����Ϣ����
    LoginMessageReg(GUIMESSAGE_MOV_CURSOR, pFrmMain,
                    MainWndMov_Cursor, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord0,
                    MainLblWord0_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord0,
                    MainLblWord0_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord1,
                    MainLblWord1_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord1,
                    MainLblWord1_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord2,
                    MainLblWord2_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord2,
                    MainLblWord2_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord3,
                    MainLblWord3_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord3,
                    MainLblWord3_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord4,
                    MainLblWord4_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord4,
                    MainLblWord4_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord5,
                    MainLblWord5_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord5,
                    MainLblWord5_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord6,
                    MainLblWord6_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord6,
                    MainLblWord6_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord7,
                    MainLblWord7_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord7,
                    MainLblWord7_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord8,
                    MainLblWord8_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord8,
                    MainLblWord8_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblWord9,
                    MainLblWord9_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblWord9,
                    MainLblWord9_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblUp,
                    MainLblUp_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblUp,
                    MainLblUp_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblDown,
                    MainLblDown_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblDown,
                    MainLblDown_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblA,
                    MainLblA_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblA,
                    MainLblA_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblB,
                    MainLblB_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblB,
                    MainLblB_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblC,
                    MainLblC_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblC,
                    MainLblC_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblD,
                    MainLblD_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblD,
                    MainLblD_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblE,
                    MainLblE_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblE,
                    MainLblE_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblF,
                    MainLblF_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblF,
                    MainLblF_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblG,
                    MainLblG_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblG,
                    MainLblG_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblH,
                    MainLblH_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblH,
                    MainLblH_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblI,
                    MainLblI_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblI,
                    MainLblI_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblJ,
                    MainLblJ_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblJ,
                    MainLblJ_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblK,
                    MainLblK_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblK,
                    MainLblK_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblL,
                    MainLblL_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblL,
                    MainLblL_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblM,
                    MainLblM_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblM,
                    MainLblM_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblN,
                    MainLblN_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblN,
                    MainLblN_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblO,
                    MainLblO_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblO,
                    MainLblO_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblP,
                    MainLblP_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblP,
                    MainLblP_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblQ,
                    MainLblQ_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblQ,
                    MainLblQ_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblR,
                    MainLblR_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblR,
                    MainLblR_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblS,
                    MainLblS_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblS,
                    MainLblS_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblT,
                    MainLblT_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblT,
                    MainLblT_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblU,
                    MainLblU_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblU,
                    MainLblU_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblV,
                    MainLblV_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblV,
                    MainLblV_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblW,
                    MainLblW_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblW,
                    MainLblW_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblX,
                    MainLblX_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblX,
                    MainLblX_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblY,
                    MainLblY_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblY,
                    MainLblY_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblZ,
                    MainLblZ_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblZ,
                    MainLblZ_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblBackspace,
                    MainLblBackspace_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblBackspace,
                    MainLblBackspace_Up, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_DOWN, pMainLblEnter,
                    MainLblEnter_Down, NULL, 0, pMsg);
    LoginMessageReg(GUIMESSAGE_TCH_UP, pMainLblEnter,
                    MainLblEnter_Up, NULL, 0, pMsg);
    //ע�������Ͽؼ�����Ϣ����
    //...
    //ע�ᰴť���ؼ�����Ϣ����
    //...
    //ע����Ϣ���Ͽؼ�����Ϣ����
    //...
    //ע�ᴰ��Ĵ�������
    LoginMessageReg(GUIMESSAGE_ERR_PROC, pFrmMain,
                    MainErrProc_Func, NULL, 0, pMsg);

    return iReturn;
}


/***
  * ���ܣ�
        ����frmmain���˳��������ͷ�������Դ
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmMainExit(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������

    //�õ���ǰ�������
    pFrmMain = (GUIWINDOW *) pWndObj;

    //�����Ϣ�����е���Ϣע����
    //***************************************************************/
    ClearMessageReg(GetCurrMessage());

    //�ӵ�ǰ������ע������ؼ�
    //***************************************************************/
    ClearWindowComp(pFrmMain);

    //���ٴ���ؼ�
    //***************************************************************/
    //����״̬�������桢��Ϣ��
    DestroyPicture(&pMainBarStatus);
    DestroyPicture(&pMainBgDesk);
    DestroyPicture(&pMainBarInfo);
    //����״̬���ϵĿؼ�
    //...
    //���������ϵĿؼ�
    DestroyLabel(&pMainLblPinyin);
    DestroyLabel(&pMainLblSelect);
    DestroyLabel(&pMainLblWord0);
    DestroyLabel(&pMainLblWord1);
    DestroyLabel(&pMainLblWord2);
    DestroyLabel(&pMainLblWord3);
    DestroyLabel(&pMainLblWord4);
    DestroyLabel(&pMainLblWord5);
    DestroyLabel(&pMainLblWord6);
    DestroyLabel(&pMainLblWord7);
    DestroyLabel(&pMainLblWord8);
    DestroyLabel(&pMainLblWord9);
    DestroyLabel(&pMainLblUp);
    DestroyLabel(&pMainLblDown);
    DestroyLabel(&pMainLblSet);
    DestroyLabel(&pMainLblA);
    DestroyLabel(&pMainLblB);
    DestroyLabel(&pMainLblC);
    DestroyLabel(&pMainLblD);
    DestroyLabel(&pMainLblE);
    DestroyLabel(&pMainLblF);
    DestroyLabel(&pMainLblG);
    DestroyLabel(&pMainLblH);
    DestroyLabel(&pMainLblI);
    DestroyLabel(&pMainLblJ);
    DestroyLabel(&pMainLblK);
    DestroyLabel(&pMainLblL);
    DestroyLabel(&pMainLblM);
    DestroyLabel(&pMainLblN);
    DestroyLabel(&pMainLblO);
    DestroyLabel(&pMainLblP);
    DestroyLabel(&pMainLblQ);
    DestroyLabel(&pMainLblR);
    DestroyLabel(&pMainLblS);
    DestroyLabel(&pMainLblT);
    DestroyLabel(&pMainLblU);
    DestroyLabel(&pMainLblV);
    DestroyLabel(&pMainLblW);
    DestroyLabel(&pMainLblX);
    DestroyLabel(&pMainLblY);
    DestroyLabel(&pMainLblZ);
    DestroyLabel(&pMainLblBackspace);
    DestroyLabel(&pMainLblEnter);
    //...
    //���ٰ�ť���Ŀؼ�
    //...
    //������Ϣ���ϵĿؼ�
    //...

    //�ͷ��ı���Դ
    //***************************************************************/
    MainTextRes_Exit(NULL, 0, NULL, 0);

    //�ͷ�������Դ
    //***************************************************************/
    //�ͷŰ�ť��������
    //...

    return iReturn;
}


/***
  * ���ܣ�
        ����frmmain�Ļ��ƺ�����������������
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmMainPaint(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    //�õ���ǰ�������
    pFrmMain = (GUIWINDOW *) pWndObj;

    //��ʾ״̬�������桢��Ϣ��
    DisplayPicture(pMainBarStatus);
    DisplayPicture(pMainBgDesk);
    DisplayPicture(pMainBarInfo);
    //...
    //��ʾ״̬���ϵĿؼ�
    //...
    //��ʾ�����ϵĿؼ�
    DisplayLabel(pMainLblUp);
    DisplayLabel(pMainLblDown);
    DisplayLabel(pMainLblA);
    DisplayLabel(pMainLblB);
    DisplayLabel(pMainLblC);
    DisplayLabel(pMainLblD);
    DisplayLabel(pMainLblE);
    DisplayLabel(pMainLblF);
    DisplayLabel(pMainLblG);
    DisplayLabel(pMainLblH);
    DisplayLabel(pMainLblI);
    DisplayLabel(pMainLblJ);
    DisplayLabel(pMainLblK);
    DisplayLabel(pMainLblL);
    DisplayLabel(pMainLblM);
    DisplayLabel(pMainLblN);
    DisplayLabel(pMainLblO);
    DisplayLabel(pMainLblP);
    DisplayLabel(pMainLblQ);
    DisplayLabel(pMainLblR);
    DisplayLabel(pMainLblS);
    DisplayLabel(pMainLblT);
    DisplayLabel(pMainLblU);
    DisplayLabel(pMainLblV);
    DisplayLabel(pMainLblW);
    DisplayLabel(pMainLblX);
    DisplayLabel(pMainLblY);
    DisplayLabel(pMainLblZ);
    DisplayLabel(pMainLblBackspace);
    DisplayLabel(pMainLblEnter);
    //...
    //��ʾ��ť���Ŀؼ�
    //...
    //��ʾ��Ϣ���ϵĿؼ�
    //...

    return iReturn;
}


/***
  * ���ܣ�
        ����frmmain��ѭ�����������д���ѭ��
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmMainLoop(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    GUIWINDOW *pWnd = NULL;

    //��ֹ��ֹͣ����ѭ��
    SendWndMsg_LoopDisable(pWndObj);

    //���ô�����
    pWnd = pWndObj;
    pWnd->Visible.iCursor = 1;

    return iReturn;
}


/***
  * ���ܣ�
        ����frmmain�Ĺ����������д������ǰԤ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmMainPause(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


/***
  * ���ܣ�
        ����frmmain�Ļָ����������д���ָ�ǰԤ����
  * ������
        1.void *pWndObj:    ָ��ǰ�������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int FrmMainResume(void *pWndObj)
{
    //�����־������ֵ����
    int iReturn = 0;

    return iReturn;
}


//��ʼ���ı���Դ
static int MainTextRes_Init(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    //��ʼ��״̬���ϵ��ı�
    //...
    //��ʼ�������ϵ��ı�
    pMainStrPinyin = TransString("");
    pMainStrSelect = TransString("");
    pMainStrWord0 = TransString("");
    pMainStrWord1 = TransString("");
    pMainStrWord2 = TransString("");
    pMainStrWord3 = TransString("");
    pMainStrWord4 = TransString("");
    pMainStrWord5 = TransString("");
    pMainStrWord6 = TransString("");
    pMainStrWord7 = TransString("");
    pMainStrWord8 = TransString("");
    pMainStrWord9 = TransString("");
    pMainStrUp = TransString("PageUp");
    pMainStrDown = TransString("PageDn");
    pMainStrSet = TransString("");
    pMainStrA = TransString("a");
    pMainStrB = TransString("b");
    pMainStrC = TransString("c");
    pMainStrD = TransString("d");
    pMainStrE = TransString("e");
    pMainStrF = TransString("f");
    pMainStrG = TransString("g");
    pMainStrH = TransString("h");
    pMainStrI = TransString("i");
    pMainStrJ = TransString("j");
    pMainStrK = TransString("k");
    pMainStrL = TransString("l");
    pMainStrM = TransString("m");
    pMainStrN = TransString("n");
    pMainStrO = TransString("o");
    pMainStrP = TransString("p");
    pMainStrQ = TransString("q");
    pMainStrR = TransString("r");
    pMainStrS = TransString("s");
    pMainStrT = TransString("t");
    pMainStrU = TransString("u");
    pMainStrV = TransString("v");
    pMainStrW = TransString("w");
    pMainStrX = TransString("x");
    pMainStrY = TransString("y");
    pMainStrZ = TransString("z");
    pMainStrBackspace = TransString("<--");
    pMainStrEnter = TransString("Enter");
    //...
    //��ʼ����ť�����ı�
    //...
    //��ʼ����Ϣ���ϵ��ı�
    //...

    return iReturn;
}


//�ͷ��ı���Դ
static int MainTextRes_Exit(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    //�ͷ�״̬���ϵ��ı�
    //...
    //�ͷ������ϵ��ı�
    free(pMainStrPinyin);
    free(pMainStrSelect);
    free(pMainStrWord0);
    free(pMainStrWord1);
    free(pMainStrWord2);
    free(pMainStrWord3);
    free(pMainStrWord4);
    free(pMainStrWord5);
    free(pMainStrWord6);
    free(pMainStrWord7);
    free(pMainStrWord8);
    free(pMainStrWord9);
    free(pMainStrUp);
    free(pMainStrDown);
    free(pMainStrSet);
    free(pMainStrA);
    free(pMainStrB);
    free(pMainStrC);
    free(pMainStrD);
    free(pMainStrE);
    free(pMainStrF);
    free(pMainStrG);
    free(pMainStrH);
    free(pMainStrI);
    free(pMainStrJ);
    free(pMainStrK);
    free(pMainStrL);
    free(pMainStrM);
    free(pMainStrN);
    free(pMainStrO);
    free(pMainStrP);
    free(pMainStrQ);
    free(pMainStrR);
    free(pMainStrS);
    free(pMainStrT);
    free(pMainStrU);
    free(pMainStrV);
    free(pMainStrW);
    free(pMainStrX);
    free(pMainStrY);
    free(pMainStrZ);
    free(pMainStrBackspace);
    free(pMainStrEnter);
    //...
    //�ͷŰ�ť�����ı�
    //...
    //�ͷ���Ϣ���ϵ��ı�
    //...

    return iReturn;
}


//����İ��������¼�������
static int MainWndKey_Down(void *pInArg, int iInLen,
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
static int MainWndKey_Up(void *pInArg, int iInLen,
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
static int MainWndMov_Cursor(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    static unsigned int uiFlag = 0, uiPrevX = 0, uiPrevY = 0;
    static char Cursor[5][5*4];
    GUIFBMAP *pFbmap = NULL;
    UINT32 *pBuff = NULL;
    unsigned int uiCursAbs, uiCursX, uiCursY;

    pFbmap = GetCurrFbmap();
    pBuff = pFbmap->pMapBuff;
    if (uiFlag)
    {
        memcpy(pBuff + (uiPrevY + pFbmap->uiVerOff + 0) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiPrevX), &Cursor[0][0], 5*4);
        memcpy(pBuff + (uiPrevY + pFbmap->uiVerOff + 1) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiPrevX), &Cursor[1][0], 5*4);
        memcpy(pBuff + (uiPrevY + pFbmap->uiVerOff + 2) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiPrevX), &Cursor[2][0], 5*4);
        memcpy(pBuff + (uiPrevY + pFbmap->uiVerOff + 3) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiPrevX), &Cursor[3][0], 5*4);
        memcpy(pBuff + (uiPrevY + pFbmap->uiVerOff + 4) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiPrevX), &Cursor[4][0], 5*4);
    }

    uiCursAbs = (unsigned int) pInArg;
    uiCursX = (uiCursAbs >> 16) & 0xFFFF;
    uiCursY = uiCursAbs & 0xFFFF;
    uiPrevX = uiCursX;
    uiPrevY = uiCursY;

    memcpy(&Cursor[0][0], pBuff + (uiCursY + pFbmap->uiVerOff + 0) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiCursX), 5*4);
    memcpy(&Cursor[1][0], pBuff + (uiCursY + pFbmap->uiVerOff + 1) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiCursX), 5*4);
    memcpy(&Cursor[2][0], pBuff + (uiCursY + pFbmap->uiVerOff + 2) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiCursX), 5*4);
    memcpy(&Cursor[3][0], pBuff + (uiCursY + pFbmap->uiVerOff + 3) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiCursX), 5*4);
    memcpy(&Cursor[4][0], pBuff + (uiCursY + pFbmap->uiVerOff + 4) * pFbmap->uiHorRes + (pFbmap->uiHorOff + uiCursX), 5*4);
    uiFlag = 1;

    DrawBlock(uiCursX, uiCursY, uiCursX + 4, uiCursY + 4);

    return iReturn;
}


static int MainLblWord0_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(0, pMainLblWord0);

    return iReturn;
}


static int MainLblWord0_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord0);

    return iReturn;
}


static int MainLblWord1_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(1, pMainLblWord1);

    return iReturn;
}


static int MainLblWord1_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord1);

    return iReturn;
}


static int MainLblWord2_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(2, pMainLblWord2);

    return iReturn;
}


static int MainLblWord2_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord2);

    return iReturn;
}


static int MainLblWord3_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(3, pMainLblWord3);

    return iReturn;
}


static int MainLblWord3_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord3);

    return iReturn;
}


static int MainLblWord4_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(4, pMainLblWord4);

    return iReturn;
}


static int MainLblWord4_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord4);

    return iReturn;
}


static int MainLblWord5_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(5, pMainLblWord5);

    return iReturn;
}


static int MainLblWord5_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord5);

    return iReturn;
}


static int MainLblWord6_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(6, pMainLblWord6);

    return iReturn;
}


static int MainLblWord6_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord6);

    return iReturn;
}


static int MainLblWord7_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(7, pMainLblWord7);

    return iReturn;
}


static int MainLblWord7_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord7);

    return iReturn;
}


static int MainLblWord8_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(8, pMainLblWord8);

    return iReturn;
}


static int MainLblWord8_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord8);

    return iReturn;
}


static int MainLblWord9_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_SelectPinyinWord(9, pMainLblWord9);

    return iReturn;
}


static int MainLblWord9_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblWord9);

    return iReturn;
}


static int MainLblUp_Down(void *pInArg, int iInLen,
                          void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_WordTurnPage(0, pMainLblUp);

    return iReturn;
}


static int MainLblUp_Up(void *pInArg, int iInLen,
                        void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblUp);

    return iReturn;
}


static int MainLblDown_Down(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_WordTurnPage(1, pMainLblDown);

    return iReturn;
}


static int MainLblDown_Up(void *pInArg, int iInLen,
                          void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblDown);

    return iReturn;
}


static int MainLblA_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('a', pMainLblA);

    return iReturn;
}


static int MainLblA_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblA);

    return iReturn;
}


static int MainLblB_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('b', pMainLblB);

    return iReturn;
}


static int MainLblB_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblB);

    return iReturn;
}


static int MainLblC_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('c', pMainLblC);

    return iReturn;
}


static int MainLblC_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblC);

    return iReturn;
}


static int MainLblD_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('d', pMainLblD);

    return iReturn;
}


static int MainLblD_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblD);

    return iReturn;
}


static int MainLblE_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('e', pMainLblE);

    return iReturn;
}


static int MainLblE_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblE);

    return iReturn;
}


static int MainLblF_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('f', pMainLblF);

    return iReturn;
}


static int MainLblF_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblF);

    return iReturn;
}


static int MainLblG_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('g', pMainLblG);

    return iReturn;
}


static int MainLblG_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblG);

    return iReturn;
}


static int MainLblH_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('h', pMainLblH);

    return iReturn;
}


static int MainLblH_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblH);

    return iReturn;
}


static int MainLblI_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('i', pMainLblI);

    return iReturn;
}


static int MainLblI_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblI);

    return iReturn;
}


static int MainLblJ_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('j', pMainLblJ);

    return iReturn;
}


static int MainLblJ_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblJ);

    return iReturn;
}


static int MainLblK_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('k', pMainLblK);

    return iReturn;
}


static int MainLblK_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblK);

    return iReturn;
}


static int MainLblL_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('l', pMainLblL);

    return iReturn;
}


static int MainLblL_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblL);

    return iReturn;
}


static int MainLblM_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('m', pMainLblM);

    return iReturn;
}


static int MainLblM_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblM);

    return iReturn;
}


static int MainLblN_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('n', pMainLblN);

    return iReturn;
}


static int MainLblN_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblN);

    return iReturn;
}


static int MainLblO_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('o', pMainLblO);

    return iReturn;
}


static int MainLblO_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblO);

    return iReturn;
}


static int MainLblP_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('p', pMainLblP);

    return iReturn;
}


static int MainLblP_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblP);

    return iReturn;
}


static int MainLblQ_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('q', pMainLblQ);

    return iReturn;
}


static int MainLblQ_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblQ);

    return iReturn;
}


static int MainLblR_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('r', pMainLblR);

    return iReturn;
}


static int MainLblR_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblR);

    return iReturn;
}


static int MainLblS_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('s', pMainLblS);

    return iReturn;
}


static int MainLblS_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblS);

    return iReturn;
}


static int MainLblT_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('t', pMainLblT);

    return iReturn;
}


static int MainLblT_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblT);

    return iReturn;
}


static int MainLblU_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('u', pMainLblU);

    return iReturn;
}


static int MainLblU_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblU);

    return iReturn;
}


static int MainLblV_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('v', pMainLblV);

    return iReturn;
}


static int MainLblV_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblV);

    return iReturn;
}


static int MainLblW_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('w', pMainLblW);

    return iReturn;
}


static int MainLblW_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblW);

    return iReturn;
}


static int MainLblX_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('x', pMainLblX);

    return iReturn;
}


static int MainLblX_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblX);

    return iReturn;
}


static int MainLblY_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('y', pMainLblY);

    return iReturn;
}


static int MainLblY_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblY);

    return iReturn;
}


static int MainLblZ_Down(void *pInArg, int iInLen,
                         void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    iReturn = Main_AddPinyinChar('z', pMainLblZ);

    return iReturn;
}


static int MainLblZ_Up(void *pInArg, int iInLen,
                       void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblZ);

    return iReturn;
}


static int MainLblBackspace_Down(void *pInArg, int iInLen,
                                 void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    SetFontColor(0x0, COLOR_TRANS, GetCurrFont());
    DisplayLabel(pMainLblBackspace);
    SetFontColor(0x00FFFFFF, COLOR_TRANS, GetCurrFont());

    if (pMainLblPinyin->pLblText->uiTextLength)
    {
        pMainLblPinyin->pLblText->pTextData[pMainLblPinyin->pLblText->uiTextLength - 1] = '\0';
        SetLabelText(pMainLblPinyin->pLblText->pTextData, pMainLblPinyin);

        DrawBlock(pMainLblPinyin->Visible.Area.Start.x, pMainLblPinyin->Visible.Area.Start.y,
                  pMainLblPinyin->Visible.Area.End.x, pMainLblPinyin->Visible.Area.End.y);
        DisplayLabel(pMainLblPinyin);
    }

    return iReturn;
}


static int MainLblBackspace_Up(void *pInArg, int iInLen,
                               void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblBackspace);

    return iReturn;
}


static int MainLblEnter_Down(void *pInArg, int iInLen,
                             void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    int iTemp;
    char Pinyin[PINYIN_STORE_MAXLEN];
    GUICHAR *pSet = NULL;

    SetFontColor(0x0, COLOR_TRANS, GetCurrFont());
    DisplayLabel(pMainLblEnter);
    SetFontColor(0x00FFFFFF, COLOR_TRANS, GetCurrFont());

    for (iTemp = 0; iTemp < PINYIN_STORE_MAXLEN; iTemp++)
    {
        Pinyin[iTemp] = pMainLblPinyin->pLblText->pTextData[iTemp];
    }
    if (NULL != pMainWordSet)
    {
        if (pMainWordSet->iWordCount)
        {
            free(pMainWordSet->pWordCode);
        }
        free(pMainWordSet);
    }
    pMainWordSet = QueryWordPinyin(Pinyin, 10);

    if ((NULL != pMainWordSet) &&
        pMainWordSet->iWordCount)
    {
        pSet = malloc(2 * (pMainWordSet->iWordCount + 1));
        if (NULL != pSet)
        {
            memcpy(pSet, pMainWordSet->pWordCode, pMainWordSet->iWordCount * 2);
            pSet[pMainWordSet->iWordCount] = '\0';
        }
        Main_ViewWordList();

        DrawBlock(pMainLblSet->Visible.Area.Start.x, 
                  pMainLblSet->Visible.Area.Start.y,
                  pMainLblSet->Visible.Area.End.x,
                  pMainLblSet->Visible.Area.End.y);
        SetLabelText(pSet, pMainLblSet);
        DisplayLabel(pMainLblSet);
    }

    return iReturn;
}


static int MainLblEnter_Up(void *pInArg, int iInLen,
                           void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    DisplayLabel(pMainLblEnter);

    return iReturn;
}


//�����¼�������
static int MainErrProc_Func(void *pInArg, int iInLen,
                            void *pOutArg, int iOutLen)
{
    //�����־������ֵ����
    int iReturn = 0;

    //����ʵ����������д�����

    return iReturn;
}


static int Main_AddPinyinChar(char cAddChar, GUILABEL *pLblChar)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    char Char[2] = { 0, 0 };
    GUICHAR *pChar = NULL;

    SetFontColor(0x0, COLOR_TRANS, GetCurrFont());
    DisplayLabel(pLblChar);
    SetFontColor(0x00FFFFFF, COLOR_TRANS, GetCurrFont());

    if (pMainLblPinyin->pLblText->uiTextLength < PINYIN_VALID_MAXLEN)
    {
        Char[0] = cAddChar;
        pChar = TransString(Char);
        StringCat(&(pMainLblPinyin->pLblText->pTextData), pChar);
        free(pChar);
        SetLabelText(pMainLblPinyin->pLblText->pTextData, pMainLblPinyin);

        DrawBlock(pMainLblPinyin->Visible.Area.Start.x, 
                  pMainLblPinyin->Visible.Area.Start.y,
                  pMainLblPinyin->Visible.Area.End.x, 
                  pMainLblPinyin->Visible.Area.End.y);
        DisplayLabel(pMainLblPinyin);
    }

    return iReturn;
}


static int Main_ViewWordList(void)
{
    //�����־������ֵ����
    int iReturn = 0;
    //��ʱ��������
    int iTemp;
    GUICHAR Word[2] = { 0, 0 };
    GUILABEL *pWordCell[10] = {
        pMainLblWord0,
        pMainLblWord1,
        pMainLblWord2,
        pMainLblWord3,
        pMainLblWord4,
        pMainLblWord5,
        pMainLblWord6,
        pMainLblWord7,
        pMainLblWord8,
        pMainLblWord9
    };

    if (NULL == pMainWordSet)
    {
        return iReturn;
    }

    if (pMainWordSet->iViewLen > 10)
    {
        return iReturn;
    }

    DrawBlock(pMainLblWord0->Visible.Area.Start.x,
              pMainLblWord0->Visible.Area.Start.y,
              pMainLblWord9->Visible.Area.End.x,
              pMainLblWord9->Visible.Area.End.y);

    for (iTemp = pMainWordSet->iHeadPos; 
         iTemp < pMainWordSet->iTailPos; 
         iTemp++)
    {
        Word[0] = pMainWordSet->pWordCode[iTemp];
        SetLabelText(Word, pWordCell[iTemp - pMainWordSet->iHeadPos]);
        DisplayLabel(pWordCell[iTemp - pMainWordSet->iHeadPos]);
    }

    return iReturn;
}


static int Main_WordTurnPage(int iTurnFlag, GUILABEL *pLblTurn)
{
    //�����־������ֵ����
    int iReturn = 0;

    SetFontColor(0x0, COLOR_TRANS, GetCurrFont());
    DisplayLabel(pLblTurn);
    SetFontColor(0x00FFFFFF, COLOR_TRANS, GetCurrFont());

    if (NULL == pMainWordSet)
    {
        return iReturn;
    }

    if (0 == iTurnFlag)
    {
        if (0 == pMainWordSet->iHeadPos)
        {
            return iReturn;
        }

        pMainWordSet->iHeadPos -= pMainWordSet->iViewLen;
        if (pMainWordSet->iHeadPos < 0)
        {
            pMainWordSet->iHeadPos = 0;
        }
    }
    else
    {
        if (pMainWordSet->iTailPos == pMainWordSet->iWordCount)
        {
            return iReturn;
        }

        pMainWordSet->iHeadPos += pMainWordSet->iViewLen;
        if (pMainWordSet->iHeadPos >= pMainWordSet->iWordCount)
        {
            pMainWordSet->iHeadPos -= pMainWordSet->iViewLen;
        }
    }    
    pMainWordSet->iTailPos = pMainWordSet->iHeadPos + pMainWordSet->iViewLen;
    if (pMainWordSet->iTailPos > pMainWordSet->iWordCount)
    {
        pMainWordSet->iTailPos = pMainWordSet->iWordCount;
    }

    Main_ViewWordList();

    return iReturn;
}


static int Main_SelectPinyinWord(int iSelOff, GUILABEL *pLblWord)
{
    //�����־������ֵ����
    int iReturn = 0;

    SetFontColor(0x0, COLOR_TRANS, GetCurrFont());
    DisplayLabel(pLblWord);
    SetFontColor(0x00FFFFFF, COLOR_TRANS, GetCurrFont());

    SetLabelText(pLblWord->pLblText->pTextData, pMainLblSelect);
    DrawBlock(pMainLblSelect->Visible.Area.Start.x, 
              pMainLblSelect->Visible.Area.Start.y,
              pMainLblSelect->Visible.Area.End.x, 
              pMainLblSelect->Visible.Area.End.y);
    DisplayLabel(pMainLblSelect);

    return iReturn;
}

