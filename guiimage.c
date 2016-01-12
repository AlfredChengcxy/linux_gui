/*******************************************************************************
* Copyright(c)2012��һŵ����(����)���޹�˾�Ϻ��з���
*
* All rights reserved
*
* �ļ����ƣ�  guiimage.c
* ժ    Ҫ��  ʵ��GUIͼ�����͵���ز�������������ͼ����Ʋ���������ΪGUIͼ�οؼ�
*             ��ʵ���ṩ������
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guiimage.h"


/*************************************
* Ϊʵ��GUIIMAGE����Ҫ���õ�����ͷ�ļ�
*************************************/
//#include ""


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӽ���ͼ�����
  * ������
        1.unsigned int uiImgWidth:      ͼ���ˮƽ��ȣ���λΪ����
        2.unsigned int uiImgHeight:     ͼ��Ĵ�ֱ�߶ȣ���λΪ����
        3.unsigned int uiImgDepth:      ͼ�������ص���ɫ���
  * ���أ�
        �ɹ�������Чָ�룬ʧ�ܷ���NULL
  * ��ע��
***/
GUIIMAGE* CreateImage(unsigned int uiImgWidth, unsigned int uiImgHeight, 
                      unsigned int uiImgDepth)
{
    //�����־������ֵ����
    int iErr = 0;
    GUIIMAGE *pImageObj = NULL;
    //��ʱ��������
    unsigned int uiSize;

    if (!iErr)
    {
        //�ж�ͼ��Ŀ�Ⱥ͸߶��Ƿ���Ч
        if (0 == uiImgWidth || 0 == uiImgHeight)
        {
            iErr = -1;
        }
        //�ж�uiImgDepth�Ƿ�Ϊ��Ч��ɫ���
        if ((uiImgDepth != 1) && 
            (uiImgDepth != 8) && 
            (uiImgDepth != 24))
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�����ڴ���Դ
        pImageObj = (GUIIMAGE *) malloc(sizeof(GUIIMAGE));
        if (NULL == pImageObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //Ϊͼ�����ݷ����ڴ���Դ������ʱͼ���ÿ�����ݶ����ֽڶ���
        uiSize = round_up(uiImgWidth * uiImgDepth, 8) / 8;
        pImageObj->pImgData = (unsigned char *) malloc(uiSize * uiImgHeight);
        if (NULL == pImageObj->pImgData)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {
        //ͼ����󲿷ֳ�Ա��ֵ
        pImageObj->uiImgWidth = uiImgWidth;
        pImageObj->uiImgHeight = uiImgHeight;
        pImageObj->uiImgDepth = uiImgDepth;
        pImageObj->uiDispWidth = uiImgWidth;    //Ĭ����ʾȫ�����
        pImageObj->uiDispHeight = uiImgHeight;  //Ĭ����ʾȫ���߶�
        pImageObj->uiPlaceX = 0;
        pImageObj->uiPlaceY = 0;
        pImageObj->uiRealX = 0;
        pImageObj->uiRealY = 0;
        pImageObj->uiFgColor = COLOR_TRANS;     //ȫ͸����ǰ����Ч
        pImageObj->uiBgColor = COLOR_TRANS;     //ȫ͸����������Ч
        pImageObj->pRefPal = NULL;
    }

    //������
    switch (iErr)
    {
    case -3:
        free(pImageObj);
        //no break
    case -2:
    case -1:
        pImageObj = NULL;
        //no break
    default:
        break;
    }

    return pImageObj;
}


/***
  * ���ܣ�
        ɾ��ͼ�����
  * ������
        1.GUIIMAGE **ppImgObj:  ָ���ָ�룬ָ����Ҫ���ٵ�ͼ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        ����ɹ��������ָ�뽫���ÿ�
***/
int DestroyImage(GUIIMAGE **ppImgObj)
{
    //�����־������ֵ����
    int iErr = 0;

    if (!iErr)
    {
        //�ж�ppImgObj�Ƿ�Ϊ��Чָ��
        if (NULL == ppImgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�ж�ppImgObj��ָ����Ƿ�Ϊ��Чָ��
        if (NULL == *ppImgObj)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //�ͷ���Դ
        free((*ppImgObj)->pImgData);
        //����ͼ����󣬲���ָ���ÿ�
        free(*ppImgObj);
        *ppImgObj = NULL;
    }

    return iErr;
}


/***
  * ���ܣ�
        ֱ�����ָ����ͼ��
  * ������
        1.GUIIMAGE *pImgObj:    ͼ��ָ�룬����Ϊ��
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ���еĻ��������������ڳ�������ǰ���µ���
***/
int DisplayImage(GUIIMAGE *pImgObj)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIFBMAP *pFbmap = NULL;

    if (!iErr)
    {
        //�ж�pImgObj�Ƿ�Ϊ��Чָ��
        if (NULL == pImgObj)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ֡����ӳ������ж��Ƿ�Ϊ��Чָ��
        pFbmap = GetCurrFbmap();
        if (NULL == pFbmap)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {    
        //�ж�ͼ�����λ���Ƿ񳬳���ʾ��Χ
        if ((pImgObj->uiPlaceX >= pFbmap->uiHorDisp) || 
            (pImgObj->uiPlaceY >= pFbmap->uiVerDisp))
        {
            iErr = -3;
        }
        //�ض�λ��������
        pImgObj->uiRealX = pImgObj->uiPlaceX + pFbmap->uiHorOff;
        pImgObj->uiRealY = pImgObj->uiPlaceY + pFbmap->uiVerOff;
    }

    if (!iErr)
    {
        //����ͼ�����ʾ�Ŀ�Ⱥ͸߶ȣ��Է���֡����ӳ�������
        if (pImgObj->uiDispWidth + pImgObj->uiPlaceX > pFbmap->uiHorDisp)
        {
            pImgObj->uiDispWidth = pFbmap->uiHorDisp - pImgObj->uiPlaceX;
        }
        if (pImgObj->uiDispHeight + pImgObj->uiPlaceY > pFbmap->uiVerDisp)
        {
            pImgObj->uiDispHeight = pFbmap->uiVerDisp - pImgObj->uiPlaceY;
        }
        //���ͼ��
        MutexLock(&(pFbmap->Mutex));
        switch (pImgObj->uiImgDepth)
        {
        case 1:     //����1λɫͼ��
            switch (pFbmap->uiPixelBits)
            {
          #if (PIXEL_8BITS)
            case 8:
                _Image1Fb8(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_8BITS
          #if (PIXEL_16BITS)
            case 16:
                _Image1Fb16(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_16BITS
          #if (PIXEL_24BITS)
            case 24:
                _Image1Fb24(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_24BITS
          #if (PIXEL_32BITS)
            case 32:
                _Image1Fb32(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_32BITS
            default:
                iErr = -4;
                break;
            }
            break;
        case 8:     //����8λɫͼ��
            switch (pFbmap->uiPixelBits)
            {
          #if (PIXEL_8BITS)
            case 8:
                _Image8Fb8(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_8BITS
          #if (PIXEL_16BITS)
            case 16:
                _Image8Fb16(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_16BITS
          #if (PIXEL_24BITS)
            case 24:
                _Image8Fb24(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_24BITS
          #if (PIXEL_32BITS)
            case 32:
                _Image8Fb32(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_32BITS
            default:
                iErr = -4;
                break;
            }
            break;
        case 24:    //����24λɫͼ��
            switch (pFbmap->uiPixelBits)
            {
          #if (PIXEL_8BITS)
            case 8:
                _Image24Fb8(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_8BITS
          #if (PIXEL_16BITS)
            case 16:
                _Image24Fb16(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_16BITS
          #if (PIXEL_24BITS)
            case 24:
                _Image24Fb24(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_24BITS
          #if (PIXEL_32BITS)
            case 32:
                _Image24Fb32(pImgObj, pFbmap);
                break;
          #endif    //PIXEL_32BITS
            default:
                iErr = -4;
                break;
            }
            break;
        default:
            iErr = -4;
            break;
        }
        MutexUnlock(&(pFbmap->Mutex));
        //����ͬ����־����ǻ�������ˢ��
        SetFbmapSync(1, pFbmap);
    }

    return iErr;
}


/***
  * ���ܣ�
        ����ͼ��ķ���λ��
  * ������
        1.unsigned int uiPlaceX:    ͼ��ˮƽ����λ�ã������Ͻ�Ϊ���㣬��������
        2.unsigned int uiPlaceY:    ͼ��ֱ����λ�ã������Ͻ�Ϊ���㣬��������
        3.GUIIMAGE *pImgObj:        ��Ҫ���÷���λ�õ�ͼ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetImagePlace(unsigned int uiPlaceX, unsigned int uiPlaceY, 
                  GUIIMAGE *pImgObj)
{
    //�ж�pImgObj�Ƿ���Ч
    if (NULL == pImgObj)
    {
        return -1;
    }

    pImgObj->uiPlaceX = uiPlaceX;
    pImgObj->uiPlaceY = uiPlaceY;

    return 0;
}


/***
  * ���ܣ�
        ����ͼ���ǰ������ɫ
  * ������
        1.unsigned int uiFgColor:   ͼ��ǰ����ɫֵ��uiImgDepthΪ1ʱʹ��
        2.unsigned int uiBgColor:   ͼ�񱳾���ɫֵ��uiImgDepthΪ1ʱʹ��
        3.GUIIMAGE *pImgObj:        ��Ҫ����ǰ������ͼ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetImageColor(unsigned int uiFgColor, unsigned int uiBgColor, 
                  GUIIMAGE *pImgObj)
{
    //�ж�pImgObj�Ƿ���Ч
    if (NULL == pImgObj)
    {
        return -1;
    }

    pImgObj->uiFgColor = uiFgColor;
    pImgObj->uiBgColor = uiBgColor;

    return 0;
}


/***
  * ���ܣ�
        ����ͼ�����õĵ�ɫ��
  * ������
        1.GUIPALETTE *pRefPal:  ͼ�����õĵ�ɫ�壬��uiImgDepthΪ8ʱʹ��
        2.GUIIMAGE *pImgObj:    ��Ҫ���õ�ɫ���ͼ�����
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
***/
int SetImagePalette(GUIPALETTE *pRefPal, GUIIMAGE *pImgObj)
{
    //�ж�pRefPal��pImgObj�Ƿ�Ϊ��Чָ��
    if (NULL == pRefPal || NULL == pImgObj)
    {
        return -1;
    }

    pImgObj->pRefPal = pRefPal;

    return 0;
}


/***
  * ���ܣ�
        ����1λɫͼ��Ӧ����8λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_8BITS)
void _Image1Fb8(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    //���Ƚ�ǰ��ɫfg�뱳��ɫbgת��Ϊϵͳ��ɫ���е���ɫ����
    //ת���ķ���Ϊ:������ɫ�壬�������ɫ���и���ɫ��fg��bg�ķ���
    //������С�ߵ�������Ϊת���������

    //���image�Ĺ���������_Image1FbX()��������

    return;
}
#endif    //PIXEL_8BITS


/***
  * ���ܣ�
        ����1λɫͼ��Ӧ����16λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_16BITS)
void _Image1Fb16(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //1λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT16 *p = pfbmap->pMapBuff;   //pָ��16λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;
    UINT16 fg = ((pimg->uiFgColor & 0x0000F8) >> 3) |   //RGB565��B����:��5λ
                ((pimg->uiFgColor & 0x00FC00) >> 5) |   //RGB565��G����:�м�6λ
                ((pimg->uiFgColor & 0xF80000) >> 8);    //RGB565��R����:��5λ
    UINT16 bg = ((pimg->uiBgColor & 0x0000F8) >> 3) |   //RGB565��B����:��5λ
                ((pimg->uiBgColor & 0x00FC00) >> 5) |   //RGB565��G����:�м�6λ
                ((pimg->uiBgColor & 0xF80000) >> 8);    //RGB565��R����:��5λ
    UINT32 byte = round_up(w, 8) / 8;
    UINT32 bit, dot;

    p += pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes;
    off_p = pfbmap->uiHorRes - w;
    off_d = round_up(pimg->uiImgWidth, 8) / 8 - byte;
    t = byte;
    //��Ա�׼1λɫͼ��ǰ����ɫ����Ч
    if ((pimg->uiFgColor != COLOR_TRANS) && 
        (pimg->uiBgColor != COLOR_TRANS))
    {
        while (h--)
        {
            while (byte--)
            {
                dot = *d++;
                bit = 8;
                while (bit && w)
                {
                    bit--;
                    w--;
                    if (dot & 0x80)
                    {
                        *p++ = fg;
                    }
                    else
                    {
                        *p++ = bg;
                    }
                    dot <<= 1;
                }
            }
            p += off_p;
            d += off_d;
            w = pimg->uiDispWidth;
            byte = t;
        }
    }
    //������ⵥɫͼ��(����ģ)��ֻ��ǰ��ɫ��Ч
    if ((pimg->uiFgColor != COLOR_TRANS) && 
        (pimg->uiBgColor == COLOR_TRANS))
    {
        while (h--)
        {
            while (byte--)
            {
                dot = *d++;
                bit = 8;
                while (bit && w)
                {
                    bit--;
                    w--;
                    if (dot & 0x80)
                    {
                        *p++ = fg;
                    }
                    else
                    {
                        p++;
                    }
                    dot <<= 1;
                }
            }
            p += off_p;
            d += off_d;
            w = pimg->uiDispWidth;
            byte = t;
        }
    }

    return;
}
#endif    //PIXEL_16BITS


/***
  * ���ܣ�
        ����1λɫͼ��Ӧ����24λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_24BITS)
void _Image1Fb24(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //1λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT8 *p = pfbmap->pMapBuff;    //pָ��24λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;
    UINT8 *fg = (UINT8 *) &(pimg->uiFgColor);
    UINT8 *bg = (UINT8 *) &(pimg->uiBgColor);
    UINT32 byte = round_up(w, 8) / 8;
    UINT32 bit, dot;

    p += (pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes) * 3;
    off_p = (pfbmap->uiHorRes - w) * 3;
    off_d = round_up(pimg->uiImgWidth, 8) / 8 - byte;
    t = byte;
    //��Ա�׼1λɫͼ��ǰ����ɫ����Ч
    if ((pimg->uiFgColor != COLOR_TRANS) && 
        (pimg->uiBgColor != COLOR_TRANS))
    {
        while (h--)
        {
            while (byte--)
            {
                dot = *d++;
                bit = 8;
                while (bit && w)
                {
                    bit--;
                    w--;
                    if (dot & 0x80)
                    {
                        *p++ = fg[0];   //С�˴洢��B����:byte0
                        *p++ = fg[1];   //С�˴洢��G����:byte1
                        *p++ = fg[2];   //С�˴洢��R����:byte2
                    }
                    else
                    {
                        *p++ = bg[0];   //С�˴洢��B����:byte0
                        *p++ = bg[1];   //С�˴洢��G����:byte1
                        *p++ = bg[2];   //С�˴洢��R����:byte2
                    }
                    dot <<= 1;
                }
            }
            p += off_p;
            d += off_d;
            w = pimg->uiDispWidth;
            byte = t;
        }
    }
    //������ⵥɫͼ��(����ģ)��ֻ��ǰ��ɫ��Ч
    if ((pimg->uiFgColor != COLOR_TRANS) && 
        (pimg->uiBgColor == COLOR_TRANS))
    {
        while (h--)
        {
            while (byte--)
            {
                dot = *d++;
                bit = 8;
                while (bit && w)
                {
                    bit--;
                    w--;
                    if (dot & 0x80)
                    {
                        *p++ = fg[0];   //С�˴洢��B����:byte0
                        *p++ = fg[1];   //С�˴洢��G����:byte1
                        *p++ = fg[2];   //С�˴洢��R����:byte2
                    }
                    else
                    {
                        p += 3;
                    }
                    dot <<= 1;
                }
            }
            p += off_p;
            d += off_d;
            w = pimg->uiDispWidth;
            byte = t;
        }
    }

    return;
}
#endif    //PIXEL_24BITS


/***
  * ���ܣ�
        ����1λɫͼ��Ӧ����32λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_32BITS)
void _Image1Fb32(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //1λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT32 *p = pfbmap->pMapBuff;   //pָ��32λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;
    UINT32 fg = pimg->uiFgColor;
    UINT32 bg = pimg->uiBgColor;
    UINT32 byte = round_up(w, 8) / 8;
    UINT32 bit, dot;

    p += pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes;
    off_p = pfbmap->uiHorRes - w;
    off_d = round_up(pimg->uiImgWidth, 8) / 8 - byte;
    t = byte;
    //��Ա�׼1λɫͼ��ǰ����ɫ����Ч
    if ((pimg->uiFgColor != COLOR_TRANS) && 
        (pimg->uiBgColor != COLOR_TRANS))
    {
        while (h--)
        {
            while (byte--)
            {
                dot = *d++;
                bit = 8;
                while (bit && w)
                {
                    bit--;
                    w--;
                    if (dot & 0x80)
                    {
                        *p++ = fg;
                    }
                    else
                    {
                        *p++ = bg;
                    }
                    dot <<= 1;
                }
            }
            p += off_p;
            d += off_d;
            w = pimg->uiDispWidth;
            byte = t;
        }
    }
    //������ⵥɫͼ��(����ģ)��ֻ��ǰ��ɫ��Ч
    if ((pimg->uiFgColor != COLOR_TRANS) && 
        (pimg->uiBgColor == COLOR_TRANS))
    {
        while (h--)
        {
            while (byte--)
            {
                dot = *d++;
                bit = 8;
                while (bit && w)
                {
                    bit--;
                    w--;
                    if (dot & 0x80)
                    {
                        *p++ = fg;
                    }
                    else
                    {
                        p++;
                    }
                    dot <<= 1;
                }
            }
            p += off_p;
            d += off_d;
            w = pimg->uiDispWidth;
            byte = t;
        }
    }

    return;
}
#endif    //PIXEL_32BITS


/***
  * ���ܣ�
        ����8λɫͼ��Ӧ����8λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_8BITS)
void _Image8Fb8(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    //���Ƚ�ͼ���ɫ����ϵͳ��ɫ�彨��ӳ���map[256]
    //map[i]���±��i��ʾͼ���ɫ��������map[i]��ʾ��Ӧ��ϵͳ��ɫ������
    //ӳ������ķ���Ϊ:����ϵͳ��ɫ�壬����ϵͳ��ɫ���и���ɫ
    //��ͼ���ɫ����ĳһ��ɫ�ķ��������С�߼��ɽ���ӳ���ϵ

    //���image�Ĺ���������_Image1FbX()��������
    //*p++ = map[*d++]

    return;
}
#endif    //PIXEL_8BITS


/***
  * ���ܣ�
        ����8λɫͼ��Ӧ����16λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_16BITS)
void _Image8Fb16(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //8λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT16 *p = pfbmap->pMapBuff;   //pָ��16λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;
    UINT8 *r = pimg->pRefPal->pRedValue;
    UINT8 *g = pimg->pRefPal->pGreenValue;
    UINT8 *b = pimg->pRefPal->pBlueValue;

    p += pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes;
    off_p = pfbmap->uiHorRes - w;
    off_d = pimg->uiImgWidth - w;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = ((b[*d] & 0xF8) >> 3) |  //RGB565��B����:��5λ
                   ((g[*d] & 0xFC) << 3) |  //RGB565��G����:�м�6λ
                   ((r[*d] & 0xF8) << 8);   //RGB565��R����:��5λ
            d++;
        }
        p += off_p;
        d += off_d;
        w = t;
    }

    return;
}
#endif    //PIXEL_16BITS


/***
  * ���ܣ�
        ����8λɫͼ��Ӧ����24λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_24BITS)
void _Image8Fb24(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //8λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT8 *p = pfbmap->pMapBuff;    //pָ��24λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;
    UINT8 *r = pimg->pRefPal->pRedValue;
    UINT8 *g = pimg->pRefPal->pGreenValue;
    UINT8 *b = pimg->pRefPal->pBlueValue;

    p += (pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes) * 3;
    off_p = (pfbmap->uiHorRes - w) * 3;
    off_d = pimg->uiImgWidth - w;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = b[*d];   //С�˴洢��B����:byte0
            *p++ = g[*d];   //С�˴洢��G����:byte1
            *p++ = r[*d];   //С�˴洢��R����:byte2
            d++;
        }
        p += off_p;
        d += off_d;
        w = t;
    }

    return;
}
#endif    //PIXEL_24BITS


/***
  * ���ܣ�
        ����8λɫͼ��Ӧ����32λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_32BITS)
void _Image8Fb32(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //8λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT8 *p = pfbmap->pMapBuff;    //pָ��32λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;
    UINT8 *r = pimg->pRefPal->pRedValue;
    UINT8 *g = pimg->pRefPal->pGreenValue;
    UINT8 *b = pimg->pRefPal->pBlueValue;

    p += (pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes) * 4;
    off_p = (pfbmap->uiHorRes - w) * 4;
    off_d = pimg->uiImgWidth - w;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = b[*d];   //С�˴洢��B����:byte0
            *p++ = g[*d];   //С�˴洢��G����:byte1
            *p++ = r[*d];   //С�˴洢��R����:byte2
            p++;            //С�˴洢������͸������
            d++;
        }
        p += off_p;
        d += off_d;
        w = t;
    }

    return;
}
#endif    //PIXEL_32BITS


/***
  * ���ܣ�
        ����24λɫͼ��Ӧ����8λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_8BITS)
void _Image24Fb8(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    //����Ϊ24λɫͼ������ϵͳ��ɫ��֮�佨��ӳ��map[4096]
    //map[i]���±��i��ʾͼ����ɫֵ(RGB444)��map[i]��ʾ��Ӧ��ϵͳ��ɫ������
    //ӳ������ķ���Ϊ:����ϵͳ��ɫ�壬����ϵͳ��ɫ���и���ɫ
    //��ͼ����ɫֵ�ķ��������С�߼�����ϵͳ��ɫ����ͼ����ɫֵ�佨��ӳ���ϵ

    //���image�Ĺ���������_Image1FbX()��������
    //*p++ = map[((d[2] & 0xF0) << 8) | (d[1] & 0xF0) | ((d[0] & 0xF0) >> 4)]

    return;
}
#endif    //PIXEL_8BITS


/***
  * ���ܣ�
        ����24λɫͼ��Ӧ����16λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_16BITS)
void _Image24Fb16(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //24λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT16 *p = pfbmap->pMapBuff;   //pָ��16λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;

    p += pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes;
    off_p = pfbmap->uiHorRes - w;
    off_d = (pimg->uiImgWidth - w) * 3;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = ((d[0] & 0xF8) >> 3) |   //RGB565��B����:��5λ
                   ((d[1] & 0xFC) << 3) |   //RGB565��G����:�м�6λ
                   ((d[2] & 0xF8) << 8);    //RGB565��B����:��5λ
            d += 3;
        }
        p += off_p;
        d += off_d;
        w = t;
    }

    return;
}
#endif    //PIXEL_16BITS


/***
  * ���ܣ�
        ����24λɫͼ��Ӧ����24λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_24BITS)
void _Image24Fb24(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //24λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT8 *p = pfbmap->pMapBuff;    //pָ��24λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;

    p += (pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes) * 3;
    off_p = (pfbmap->uiHorRes - w) * 3;
    off_d = (pimg->uiImgWidth - w) * 3;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = *d++;    //С�˴洢��B����:byte0
            *p++ = *d++;    //С�˴洢��G����:byte1
            *p++ = *d++;    //С�˴洢��R����:byte2
        }
        p += off_p;
        d += off_d;
        w = t;
    }

    return;
}
#endif    //PIXEL_24BITS


/***
  * ���ܣ�
        ����24λɫͼ��Ӧ����32λɫ֡����
  * ������
        1.GUIIMAGE *pimg:   Ҫ���Ƶ�ͼ�����
        2.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
***/
#if (PIXEL_32BITS)
void _Image24Fb32(GUIIMAGE *pimg, GUIFBMAP *pfbmap)
{
    UINT8 *d = pimg->pImgData;      //24λ��ͼ�����ݣ�ʹ��8λ��ָ����з���
    UINT8 *p = pfbmap->pMapBuff;    //pָ��32λ֡����
    UINT32 h = pimg->uiDispHeight;
    UINT32 w = pimg->uiDispWidth;
    UINT32 off_p, off_d, t;

    p += (pimg->uiRealX + pimg->uiRealY * pfbmap->uiHorRes) * 4;
    off_p = (pfbmap->uiHorRes - w) * 4;
    off_d = (pimg->uiImgWidth - w) * 3;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = *d++;    //С�˴洢��B����:byte0
            *p++ = *d++;    //С�˴洢��G����:byte1
            *p++ = *d++;    //С�˴洢��R����:byte2
            p++;            //С�˴洢������͸������
        }
        p += off_p;
        d += off_d;
        w = t;
    }

    return;
}
#endif    //PIXEL_32BITS

