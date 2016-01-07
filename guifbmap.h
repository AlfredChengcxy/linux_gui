/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guifbmap.h
* ժ    Ҫ��  GUIFBMAPģ����Ҫ����豸����㶨�弰ʵ�֣��Ա�GUI�ܹ������ڲ�ͬӲ
*             ��ƽ̨��Ӧ�ò����Ӳ�����졣guifbmap.h������GUI��֡����ӳ�����ͼ�
*             ������ز���������ʵ��GUI��ͼ������豸����
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#ifndef _GUI_FBMAP_H
#define _GUI_FBMAP_H


/********************v****************
* Ϊ����GUIFBMAP����Ҫ���õ�����ͷ�ļ�
*************************************/
#include "guibase.h"


/************************
* ����GUI��֡�����豸����
************************/
#define GUI_FBTYP_STD           1   //��׼����֡����
#define GUI_FBTYP_DUAL          2   //˫��������֡����
#define GUI_FBTYP_CUST          3   //�Զ�������֡����


/************************
* ����GUI��֡����ӳ��ṹ
************************/
typedef struct _fbmap
{
    int iDevFd;                 //֡�����豸�ļ�������
    int iDevType;               //֡�����豸���ͣ�1��׼��2˫����

    unsigned int uiMapOffset;   //mmap()ӳ��ʱ��ҳƫ�ƣ�munmap()ʱʹ�ø�ֵ
    unsigned int uiMapLength;   //mmap()ӳ��ʱ�ĳ��ȣ�munmap()ʱʹ�ø�ֵ
    void *pFbEntry;             //��mmap()ӳ���õ���֡�������

    unsigned int uiBufSize;     //֡�����С���ֽڵ�λ
    unsigned int uiPixelBits;   //������ȣ�8��16(RGB565)��24��32(����ѹ��24λ)
    unsigned int uiRedBits;     //ÿ�����к�ɫ������ռλ��
    unsigned int uiRedShift;    //ÿ�����к�ɫ������ʼλ��
    unsigned int uiGreenBits;   //ÿ��������ɫ������ռλ��
    unsigned int uiGreenShift;  //ÿ��������ɫ������ʼλ��
    unsigned int uiBlueBits;    //ÿ��������ɫ������ռλ��
    unsigned int uiBlueShift;   //ÿ��������ɫ������ʼλ��
    unsigned int uiHorRes;      //֡����ˮƽ�ֱ���
    unsigned int uiVerRes;      //֡���崹ֱ�ֱ���

    unsigned int uiHorDisp;     //ӳ���������ʾ��ˮƽ�ֱ��ʣ�����<=uiHorRes
    unsigned int uiVerDisp;     //ӳ���������ʾ�Ĵ�ֱ�ֱ��ʣ�����<=uiVerRes
    unsigned int uiHorOff;      //ˮƽƫ�ƣ�uiHorOff=(uiHorRes-uiHorDisp)/2
    unsigned int uiVerOff;      //��ֱƫ�ƣ�uiVerOff=(uiVerRes-uiVerDisp)/2

    int iSyncFlag;              //ͬ����־�������뻺����Ҫͬ��ˢ��ʱ��1
    void *pMapBuff;             //���뻺�壬GUI�������ǽ���������Ƶ��û���

    THREADFUNC fnFbThread;      //�ص����������ڴ���֡�����߳�
    GUIMUTEX Mutex;             //�����������ڿ���֡�����̶߳����뻺��ķ���
} GUIFBMAP;


/****************************************
* ����GUI����֡����ӳ��������صĲ�������
****************************************/
//����ָ������Ϣֱ�Ӵ���֡����ӳ�����
GUIFBMAP* CreateFbmap(char *strDevName, int iDevType, 
                      unsigned int uiHorDisp, unsigned int uiVerDisp, 
                      THREADFUNC fnFbThread);
//ɾ��֡����ӳ�����
int DestroyFbmap(GUIFBMAP **ppFbmapObj);

//�õ���ǰ֡����ӳ�����
GUIFBMAP* GetCurrFbmap(void);
//����Ϊ��ǰ֡����ӳ�����
int SetCurrFbmap(GUIFBMAP *pFbmapObj);

//����֡����ӳ���ͬ����־
int SetFbmapSync(int iSyncFlag, GUIFBMAP *pFbmapObj);


/**************************
* ����GUI�е�Ĭ��֡�����߳�
**************************/
//Ĭ��֡�����߳���ں���
void* DefaultFbThread(void *pThreadArg);

//��׼����֡����Ĵ��������������֡�����̵߳Ĵ���
int StandardFbmapProcess(GUIFBMAP *pFbmapObj);
//˫��������֡����Ĵ��������������֡�����̵߳Ĵ���
int DualFbmapProcess(GUIFBMAP *pFbmapObj);
//�Զ�������֡����Ĵ��������������֡�����̵߳Ĵ���
int CustomFbmapProcess(GUIFBMAP *pFbmapObj);


#endif  //_GUI_FBMAP_H

