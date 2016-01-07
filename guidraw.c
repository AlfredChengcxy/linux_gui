/*******************************************************************************
* Copyright (c) 2012 ,һŵ����(����)���޹�˾�Ϻ��з���
*
* All right reserved
*
* �ļ����ƣ�  guidraw.c
* ժ    Ҫ��  ����GUI������ͼ����������ΪGUIͼ�οؼ���ʵ���ṩ����.
*
* ��ǰ�汾��  v1.1.0 (������Դ���������ļ����豸������ļ�)
* ��    �ߣ�  lzm
* ������ڣ�  2014-12-04
*
* ȡ���汾��  v1.0.2 (������/����豸�ķ����������������д�¼�����Ϣ�Ľӿں���)
* ԭ �� �ߣ�  lzm
* ������ڣ�  2014-11-04
*******************************************************************************/

#include "guidraw.h"


/************************************
* Ϊʵ��GUIDRAW����Ҫ���õ�����ͷ�ļ�
************************************/
#include "guipalette.h"
#include "guipen.h"


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӻ�������
  * ������
        1.unsigned int uiPixelX:    ���ص�ĺ�����
        2.unsigned int uiPixelY:    ���ص��������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ���еĻ��������������ڳ�������ǰ���µ���
***/
int DrawPixel(unsigned int uiPixelX, unsigned int uiPixelY)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIPALETTE *pPal = NULL;
    GUIPEN *pPen = NULL;
    GUIFBMAP *pFbmap = NULL;
    GUIPOINT Pixel;
    unsigned int uiValue;

    if (!iErr)
    {
        //�õ���ǰ��ɫ������ж��Ƿ�Ϊ��Чָ��
        pPal = GetCurrPalette();
        if (NULL == pPal)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ���ʶ����ж��Ƿ�Ϊ��Чָ��
        pPen = GetCurrPen();
        if (NULL == pPen)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {    
        //�õ���ǰ֡����ӳ������ж��Ƿ�Ϊ��Чָ��
        pFbmap = GetCurrFbmap();
        if (NULL == pFbmap)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {    
        //ȷ�����ص�
        Pixel.x = uiPixelX;
        Pixel.y = uiPixelY;
        //�ж����ص�λ���Ƿ񳬳���ʾ��Χ
        if ((Pixel.x >= pFbmap->uiHorDisp) || 
            (Pixel.y >= pFbmap->uiVerDisp))
        {
            iErr = -4;
        }
        //�ض�λ��������
        Pixel.x += pFbmap->uiHorOff;
        Pixel.y += pFbmap->uiVerOff;
    }

    if (!iErr)
    {
        //����֡����������ȣ��õ�������ʾ����ɫֵ��������Ӧ�������л���
        switch (pFbmap->uiPixelBits)
        {
      #if (PIXEL_8BITS)
        case 8:
            uiValue = MatchPaletteColor(pPen->uiPenColor, pPal);    //8λɫ
            MutexLock(&(pFbmap->Mutex));
            _DrawPixel8(uiValue, uiPixelX, uiPixelY, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif    //PIXEL_8BITS
      #if (PIXEL_16BITS)
        case 16:
            uiValue = ((pPen->uiPenColor & 0x0000F8) >> 3) |        //RGB565
                      ((pPen->uiPenColor & 0x00FC00) >> 5) |        //RGB565
                      ((pPen->uiPenColor & 0xF80000) >> 8);         //RGB565
            MutexLock(&(pFbmap->Mutex));
            _DrawPixel16(uiValue, uiPixelX, uiPixelY, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif    //PIXEL_16BITS
      #if (PIXEL_24BITS)
        case 24:
            uiValue = pPen->uiPenColor & 0xFFFFFF;                  //RGB888
            MutexLock(&(pFbmap->Mutex));
            _DrawPixel24(uiValue, uiPixelX, uiPixelY, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif    //PIXEL_24BITS
      #if (PIXEL_32BITS)
        case 32:
            uiValue = pPen->uiPenColor;
            MutexLock(&(pFbmap->Mutex));
            _DrawPixel32(uiValue, uiPixelX, uiPixelY, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif    //PIXEL_32BITS
        default:
            iErr = -5;
            break;
        }
        //����ͬ����־����ǻ�������ˢ��
        SetFbmapSync(1, pFbmap);
    }

    return iErr;
}


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӻ���ֱ��
  * ������
        1.unsigned int uiStartX:    ֱ����ʼ��ĺ�����
        2.unsigned int uiStartY:    ֱ����ʼ���������
        3.unsigned int uiEndX:      ֱ���յ�ĺ�����
        4.unsigned int uiEndY:      ֱ���յ��������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ���еĻ��������������ڳ�������ǰ���µ���
***/
int DrawLine(unsigned int uiStartX, unsigned int uiStartY, 
             unsigned int uiEndX, unsigned int uiEndY)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIPALETTE *pPal = NULL;
    GUIPEN *pPen = NULL;
    GUIFBMAP *pFbmap = NULL;
    GUIPOINT Start, End;
    unsigned int uiValue;

    if (!iErr)
    {
        //�õ���ǰ��ɫ������ж��Ƿ�Ϊ��Чָ��
        pPal = GetCurrPalette();
        if (NULL == pPal)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ���ʶ����ж��Ƿ�Ϊ��Чָ��
        pPen = GetCurrPen();
        if (NULL == pPen)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {    
        //�õ���ǰ֡����ӳ������ж��Ƿ�Ϊ��Чָ��
        pFbmap = GetCurrFbmap();
        if (NULL == pFbmap)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {    
        //ȷ����ʼ�����յ�
        Start.x = uiStartX;
        Start.y = uiStartY;
        End.x = uiEndX;
        End.y = uiEndY;
        if (uiStartY == uiEndY) //���������Ϊˮƽ�ߣ�Ҫ��End.x>Start.x
        {
            Start.x = (uiStartX < uiEndX) ? uiStartX : uiEndX;
            End.x = (uiEndX > uiStartX) ? uiEndX : uiStartX;
        }
        if (uiStartX == uiEndX) //���������Ϊ��ֱ�ߣ�Ҫ��End.y>Start.y
        {
            Start.y = (uiStartY < uiEndY) ? uiStartY : uiEndY;
            End.y = (uiEndY > uiStartY) ? uiEndY : uiStartY;
        }
        //�ж���ʼ��λ�����յ�λ���Ƿ񳬳���ʾ��Χ
        if ((Start.x >= pFbmap->uiHorDisp) || 
            (Start.y >= pFbmap->uiVerDisp) || 
            (End.x >= pFbmap->uiHorDisp) || 
            (End.y >= pFbmap->uiVerDisp))
        {
            iErr = -4;
        }
        //�ض�λ��������
        Start.x += pFbmap->uiHorOff;
        Start.y += pFbmap->uiVerOff;
        End.x += pFbmap->uiHorOff;
        End.y += pFbmap->uiVerOff;
    }

    if (!iErr)
    {
        //����֡����������ȣ��õ�������ʾ����ɫֵ��������Ӧ�������л���
        switch (pFbmap->uiPixelBits)
        {
      #if (PIXEL_8BITS)
        case 8:
            uiValue = MatchPaletteColor(pPen->uiPenColor, pPal);    //8λɫ
            MutexLock(&(pFbmap->Mutex));
            if (uiStartY == uiEndY)         //��������ȣ���ˮƽ��
            {
                _DrawHor8(uiValue, Start.x, Start.y, End.x, pFbmap);
            }
            if (uiStartX == uiEndX)         //��������ȣ�����ֱ��
            {
                _DrawVer8(uiValue, Start.x, Start.y, End.y, pFbmap);
            }
            if ((uiStartX != uiEndX) &&     //�ᡢ�����궼����ȣ���б��
                (uiStartY != uiEndY))
            {
                _DrawBias8(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            }
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_8BITS
      #if (PIXEL_16BITS)
        case 16:
            uiValue = ((pPen->uiPenColor & 0x0000F8) >> 3) |        //RGB565
                      ((pPen->uiPenColor & 0x00FC00) >> 5) |        //RGB565
                      ((pPen->uiPenColor & 0xF80000) >> 8);         //RGB565
            MutexLock(&(pFbmap->Mutex));
            if (uiStartY == uiEndY)         //��������ȣ���ˮƽ��
            {
                _DrawHor16(uiValue, Start.x, Start.y, End.x, pFbmap);
            }
            if (uiStartX == uiEndX)         //��������ȣ�����ֱ��
            {
                _DrawVer16(uiValue, Start.x, Start.y, End.y, pFbmap);
            }
            if ((uiStartX != uiEndX) &&     //�ᡢ�����궼����ȣ���б��
                (uiStartY != uiEndY))
            {
                _DrawBias16(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            }
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_16BITS
      #if (PIXEL_24BITS)
        case 24:
            uiValue = pPen->uiPenColor & 0xFFFFFF;                  //RGB888
            MutexLock(&(pFbmap->Mutex));
            if (uiStartY == uiEndY)         //��������ȣ���ˮƽ��
            {
                _DrawHor24(uiValue, Start.x, Start.y, End.x, pFbmap);
            }
            if (uiStartX == uiEndX)         //��������ȣ�����ֱ��
            {
                _DrawVer24(uiValue, Start.x, Start.y, End.y, pFbmap);
            }
            if ((uiStartX != uiEndX) &&     //�ᡢ�����궼����ȣ���б��
                (uiStartY != uiEndY))
            {
                _DrawBias24(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            }
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_24BITS
      #if (PIXEL_32BITS)
        case 32:
            uiValue = pPen->uiPenColor;
            MutexLock(&(pFbmap->Mutex));
            if (uiStartY == uiEndY)         //��������ȣ���ˮƽ��
            {
                _DrawHor32(uiValue, Start.x, Start.y, End.x, pFbmap);
            }
            if (uiStartX == uiEndX)         //��������ȣ�����ֱ��
            {
                _DrawVer32(uiValue, Start.x, Start.y, End.y, pFbmap);
            }
            if ((uiStartX != uiEndX) &&     //�ᡢ�����궼����ȣ���б��
                (uiStartY != uiEndY))
            {
                _DrawBias32(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            }
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_32BITS
        default:
            iErr = -5;
            break;
        }
        //����ͬ����־����ǻ�������ˢ��
        SetFbmapSync(1, pFbmap);
    }

    return iErr;
}


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӻ��ƾ���
  * ������
        1.unsigned int uiStartX:    ������ʼ��ĺ�����
        2.unsigned int uiStartY:    ������ʼ���������
        3.unsigned int uiEndX:      �����յ�ĺ�����
        4.unsigned int uiEndY:      �����յ��������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ���еĻ��������������ڳ�������ǰ���µ���
***/
int DrawRectangle(unsigned int uiStartX, unsigned int uiStartY, 
                  unsigned int uiEndX, unsigned int uiEndY)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIPALETTE *pPal = NULL;
    GUIPEN *pPen = NULL;
    GUIFBMAP *pFbmap = NULL;
    GUIPOINT Start, End;
    unsigned int uiValue;

    if (!iErr)
    {
        //�õ���ǰ��ɫ������ж��Ƿ�Ϊ��Чָ��
        pPal = GetCurrPalette();
        if (NULL == pPal)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ���ʶ����ж��Ƿ�Ϊ��Чָ��
        pPen = GetCurrPen();
        if (NULL == pPen)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {    
        //�õ���ǰ֡����ӳ������ж��Ƿ�Ϊ��Чָ��
        pFbmap = GetCurrFbmap();
        if (NULL == pFbmap)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {    
        //ȷ����ʼ�����յ�
        Start.x = (uiStartX < uiEndX) ? uiStartX : uiEndX;
        Start.y = (uiStartY < uiEndY) ? uiStartY : uiEndY;
        End.x = (uiEndX > uiStartX) ? uiEndX : uiStartX;
        End.y = (uiEndY > uiStartY) ? uiEndY : uiStartY;
        //�ж���ʼ��λ�����յ�λ���Ƿ񳬳���ʾ��Χ
        if ((Start.x >= pFbmap->uiHorDisp) || 
            (Start.y >= pFbmap->uiVerDisp) || 
            (End.x >= pFbmap->uiHorDisp) || 
            (End.y >= pFbmap->uiVerDisp))
        {
            iErr = -4;
        }
        //�ض�λ��������
        Start.x += pFbmap->uiHorOff;
        Start.y += pFbmap->uiVerOff;
        End.x += pFbmap->uiHorOff;
        End.y += pFbmap->uiVerOff;
    }

    if (!iErr)
    {
        //����֡����������ȣ��õ�������ʾ����ɫֵ��������Ӧ�������л���
        switch (pFbmap->uiPixelBits)
        {
      #if (PIXEL_8BITS)
        case 8:
            uiValue = MatchPaletteColor(pPen->uiPenColor, pPal);    //8λɫ
            MutexLock(&(pFbmap->Mutex));
            _DrawHor8(uiValue, Start.x, Start.y, End.x, pFbmap);
            _DrawHor8(uiValue, Start.x, End.y, End.x, pFbmap);
            _DrawVer8(uiValue, Start.x, Start.y, End.y, pFbmap);
            _DrawVer8(uiValue, End.x, Start.y, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_8BITS
      #if (PIXEL_16BITS)
        case 16:
            uiValue = ((pPen->uiPenColor & 0x0000F8) >> 3) |        //RGB565
                      ((pPen->uiPenColor & 0x00FC00) >> 5) |        //RGB565
                      ((pPen->uiPenColor & 0xF80000) >> 8);         //RGB565
            MutexLock(&(pFbmap->Mutex));
            _DrawHor16(uiValue, Start.x, Start.y, End.x, pFbmap);
            _DrawHor16(uiValue, Start.x, End.y, End.x, pFbmap);
            _DrawVer16(uiValue, Start.x, Start.y, End.y, pFbmap);
            _DrawVer16(uiValue, End.x, Start.y, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_16BITS
      #if (PIXEL_24BITS)
        case 24:
            uiValue = pPen->uiPenColor & 0xFFFFFF;                  //RGB888
            MutexLock(&(pFbmap->Mutex));
            _DrawHor24(uiValue, Start.x, Start.y, End.x, pFbmap);
            _DrawHor24(uiValue, Start.x, End.y, End.x, pFbmap);
            _DrawVer24(uiValue, Start.x, Start.y, End.y, pFbmap);
            _DrawVer24(uiValue, End.x, Start.y, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_24BITS
      #if (PIXEL_32BITS)
        case 32:
            uiValue = pPen->uiPenColor;
            MutexLock(&(pFbmap->Mutex));
            _DrawHor32(uiValue, Start.x, Start.y, End.x, pFbmap);
            _DrawHor32(uiValue, Start.x, End.y, End.x, pFbmap);
            _DrawVer32(uiValue, Start.x, Start.y, End.y, pFbmap);
            _DrawVer32(uiValue, End.x, Start.y, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_32BITS
        default:
            iErr = -5;
            break;
        }
        //����ͬ����־����ǻ�������ˢ��
        SetFbmapSync(1, pFbmap);
    }

    return iErr;
}


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӻ���Բ��
  * ������
        1.unsigned int uiPointX:    ԭ��ĺ�����
        2.unsigned int uiPointY:    ԭ���������
        3.unsigned int uiCircleR:   Բ�İ뾶
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ���еĻ��������������ڳ�������ǰ���µ���
***/
int DrawCircle(unsigned int uiPointX, unsigned int uiPointY, 
               unsigned int uiCircleR)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIPALETTE *pPal = NULL;
    GUIPEN *pPen = NULL;
    GUIFBMAP *pFbmap = NULL;
    unsigned int uiValue;

    if (!iErr)
    {
        //�õ���ǰ��ɫ������ж��Ƿ�Ϊ��Чָ��
        pPal = GetCurrPalette();
        if (NULL == pPal)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ���ʶ����ж��Ƿ�Ϊ��Чָ��
        pPen = GetCurrPen();
        if (NULL == pPen)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {    
        //�õ���ǰ֡����ӳ������ж��Ƿ�Ϊ��Чָ��
        pFbmap = GetCurrFbmap();
        if (NULL == pFbmap)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {    
        //�ж�ԭ��λ����뾶�Ƿ񳬳���ʾ��Χ
        if ((uiPointX < uiCircleR) || 
            (uiPointY < uiCircleR) || 
            (uiPointX + uiCircleR >= pFbmap->uiHorDisp) || 
            (uiPointY + uiCircleR >= pFbmap->uiVerDisp))
        {
            iErr = -4;
        }
        //�ض�λ��������
        uiPointX += pFbmap->uiHorOff;
        uiPointY += pFbmap->uiVerOff;
    }

    if (!iErr)
    {
        //����֡����������ȣ��õ�������ʾ����ɫֵ��������Ӧ�������л���
        switch (pFbmap->uiPixelBits)
        {
      #if (PIXEL_8BITS)
        case 8:
            uiValue = MatchPaletteColor(pPen->uiPenColor, pPal);    //8λɫ
            MutexLock(&(pFbmap->Mutex));
            _DrawCircle8(uiValue, uiPointX, uiPointY, uiCircleR, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_8BITS
      #if (PIXEL_16BITS)
        case 16:
            uiValue = ((pPen->uiPenColor & 0x0000F8) >> 3) |        //RGB565
                      ((pPen->uiPenColor & 0x00FC00) >> 5) |        //RGB565
                      ((pPen->uiPenColor & 0xF80000) >> 8);         //RGB565
            MutexLock(&(pFbmap->Mutex));
            _DrawCircle16(uiValue, uiPointX, uiPointY, uiCircleR, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_16BITS
      #if (PIXEL_24BITS)
        case 24:
            uiValue = pPen->uiPenColor & 0xFFFFFF;                  //RGB888
            MutexLock(&(pFbmap->Mutex));
            _DrawCircle24(uiValue, uiPointX, uiPointY, uiCircleR, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_24BITS
      #if (PIXEL_32BITS)
        case 32:
            uiValue = pPen->uiPenColor;
            MutexLock(&(pFbmap->Mutex));
            _DrawCircle32(uiValue, uiPointX, uiPointY, uiCircleR, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_32BITS
        default:
            iErr = -5;
            break;
        }
    }

    return iErr;
}


/***
  * ���ܣ�
        ����ָ������Ϣֱ�ӻ��ƿ�
  * ������
        1.unsigned int uiStartX:    ����ʼ��ĺ�����
        2.unsigned int uiStartY:    ����ʼ���������
        3.unsigned int uiEndX:      ���յ�ĺ�����
        4.unsigned int uiEndY:      ���յ��������
  * ���أ�
        �ɹ������㣬ʧ�ܷ��ط���ֵ
  * ��ע��
        �������Զ�������֡����ӳ���еĻ��������������ڳ�������ǰ���µ���
***/
int DrawBlock(unsigned int uiStartX, unsigned int uiStartY, 
              unsigned int uiEndX, unsigned int uiEndY)
{
    //�����־������ֵ����
    int iErr = 0;
    //��ʱ��������
    GUIPALETTE *pPal = NULL;
    GUIPEN *pPen = NULL;
    GUIFBMAP *pFbmap = NULL;
    GUIPOINT Start, End;
    unsigned int uiValue;

    if (!iErr)
    {
        //�õ���ǰ��ɫ������ж��Ƿ�Ϊ��Чָ��
        pPal = GetCurrPalette();
        if (NULL == pPal)
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //�õ���ǰ���ʶ����ж��Ƿ�Ϊ��Чָ��
        pPen = GetCurrPen();
        if (NULL == pPen)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {    
        //�õ���ǰ֡����ӳ������ж��Ƿ�Ϊ��Чָ��
        pFbmap = GetCurrFbmap();
        if (NULL == pFbmap)
        {
            iErr = -3;
        }
    }

    if (!iErr)
    {    
        //ȷ����ʼ�����յ�
        Start.x = (uiStartX < uiEndX) ? uiStartX : uiEndX;
        Start.y = (uiStartY < uiEndY) ? uiStartY : uiEndY;
        End.x = (uiEndX > uiStartX) ? uiEndX : uiStartX;
        End.y = (uiEndY > uiStartY) ? uiEndY : uiStartY;
        //�ж���ʼ��λ�����յ�λ���Ƿ񳬳���ʾ��Χ
        if ((Start.x >= pFbmap->uiHorDisp) || 
            (Start.y >= pFbmap->uiVerDisp) || 
            (End.x >= pFbmap->uiHorDisp) || 
            (End.y >= pFbmap->uiVerDisp))
        {
            iErr = -4;
        }
        //�ض�λ��������
        Start.x += pFbmap->uiHorOff;
        Start.y += pFbmap->uiVerOff;
        End.x += pFbmap->uiHorOff;
        End.y += pFbmap->uiVerOff;
    }

    if (!iErr)
    {
        //����֡����������ȣ��õ�������ʾ����ɫֵ��������Ӧ�������л���
        switch (pFbmap->uiPixelBits)
        {
      #if (PIXEL_8BITS)
        case 8:
            uiValue = MatchPaletteColor(pPen->uiPenColor, pPal);    //8λɫ
            MutexLock(&(pFbmap->Mutex));
            _DrawBlock8(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_8BITS
      #if (PIXEL_16BITS)
        case 16:
            uiValue = ((pPen->uiPenColor & 0x0000F8) >> 3) |        //RGB565
                      ((pPen->uiPenColor & 0x00FC00) >> 5) |        //RGB565
                      ((pPen->uiPenColor & 0xF80000) >> 8);         //RGB565
            MutexLock(&(pFbmap->Mutex));
            _DrawBlock16(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_16BITS
      #if (PIXEL_24BITS)
        case 24:
            uiValue = pPen->uiPenColor & 0xFFFFFF;                  //RGB888
            MutexLock(&(pFbmap->Mutex));
            _DrawBlock24(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_24BITS
      #if (PIXEL_32BITS)
        case 32:
            uiValue = pPen->uiPenColor;
            MutexLock(&(pFbmap->Mutex));
            _DrawBlock32(uiValue, Start.x, Start.y, End.x, End.y, pFbmap);
            MutexUnlock(&(pFbmap->Mutex));
            break;
      #endif  //PIXEL_32BITS
        default:
            iErr = -5;
            break;
        }
        //����ͬ����־����ǻ�������ˢ��
        SetFbmapSync(1, pFbmap);
    }

    return iErr;
}


/***
  * ���ܣ�
        ���Ƶ������أ�Ӧ����8λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ   
        2.UINT32 pixel_x:   ��ĺ�����
        3.UINT32 pixel_y:   ���������
        4.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_8BITS)
void _DrawPixel8(COLOR value,
                 UINT32 pixel_x, UINT32 pixel_y,
                 GUIFBMAP *pfbmap)
{
    UINT8 d = (UINT8)value;
    UINT8 *p = pfbmap->pMapBuff;

    p += pixel_x + pixel_y * pfbmap->uiHorRes;
    *p = d;

    return;
}
#endif  //PIXEL_8BITS


/***
  * ���ܣ�
       ���Ƶ������أ�Ӧ����16λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ   
        2.UINT32 pixel_x:   ��ĺ�����
        3.UINT32 pixel_y:   ���������
        4.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_16BITS)
void _DrawPixel16(COLOR value, 
                  UINT32 pixel_x, UINT32 pixel_y, 
                  GUIFBMAP *pfbmap)
{
    UINT16 d = (UINT16)value;
    UINT16 *p = pfbmap->pMapBuff;

    p += pixel_x + pixel_y * pfbmap->uiHorRes;
    *p = d;

    return;
}
#endif  //PIXEL_16BITS


/***
  * ���ܣ�
       ���Ƶ������أ�Ӧ����24λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ   
        2.UINT32 pixel_x:   ��ĺ�����
        3.UINT32 pixel_y:   ���������
        4.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_24BITS)
void _DrawPixel24(COLOR value, 
                  UINT32 pixel_x, UINT32 pixel_y, 
                  GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT8 r = (d & 0xFF0000) >> 16;
    UINT8 g = (d & 0xFF00) >> 8;
    UINT8 b = d & 0xFF;

    p += (pixel_x + pixel_y * pfbmap->uiHorRes) * 3;
    *p++ = b;   //С�˴洢��B����:byte0
    *p++ = g;   //С�˴洢��G����:byte1
    *p++ = r;   //С�˴洢��R����:byte2

    return ;
}
#endif  //PIXEL_24BITS


/***
  * ���ܣ�
       ���Ƶ������أ�Ӧ����32λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ   
        2.UINT32 pixel_x:   ��ĺ�����
        3.UINT32 pixel_y:   ���������
        4.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_32BITS)
void _DrawPixel32(COLOR value, 
                  UINT32 pixel_x, UINT32 pixel_y, 
                  GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT32 *p = pfbmap->pMapBuff;

    p += pixel_x + pixel_y * pfbmap->uiHorRes;
    *p = d;

    return ;
}
#endif  //PIXEL_32BITS


/***
  * ���ܣ�
       ����ˮƽ�ߣ�Ӧ����8λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_8BITS)
void _DrawHor8(COLOR value, 
               UINT32 start_x, UINT32 start_y, 
               UINT32 end_x, 
               GUIFBMAP *pfbmap)
{
    UINT8 d = (UINT8)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT32 loop = end_x - start_x + 1;

    p += start_x + start_y * pfbmap->uiHorRes;
    while (loop--)
    {
        *p++ = d;
    }

    return;
}
#endif  //PIXEL_8BITS


/***
  * ���ܣ�
       ����ˮƽ�ߣ�Ӧ����16λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_16BITS)
void _DrawHor16(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_x, 
                GUIFBMAP *pfbmap)
{
    UINT16 d = (UINT16)value;
    UINT16 *p = pfbmap->pMapBuff;
    UINT32 loop = end_x - start_x + 1;

    p += start_x + start_y * pfbmap->uiHorRes;
    while (loop--)
    {
        *p++ = d;
    }
 
    return;
}
#endif  //PIXEL_16BITS


/***
  * ���ܣ�
       ����ˮƽ�ߣ�Ӧ����24λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_24BITS)
void _DrawHor24(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_x, 
                GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT32 loop = end_x - start_x + 1;
    UINT8 r = (d & 0xFF0000) >> 16;
    UINT8 g = (d & 0xFF00) >> 8;
    UINT8 b = d & 0xFF;

    p += (start_x + start_y * pfbmap->uiHorRes) * 3;
    while (loop--)
    {
        *p++ = b;   //С�˴洢��B����:byte0
        *p++ = g;   //С�˴洢��G����:byte1
        *p++ = r;   //С�˴洢��R����:byte2
    }

    return;
}
#endif  //PIXEL_24BITS


/***
  * ���ܣ�
       ����ˮƽ�ߣ�Ӧ����32λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_32BITS)
void _DrawHor32(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_x, 
                GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT32 *p = pfbmap->pMapBuff;
    UINT32 loop = end_x - start_x + 1;

    p += start_x + start_y * pfbmap->uiHorRes;
    while (loop--)
    {
        *p++ = d;
    }

    return;
}
#endif  //PIXEL_32BITS


/***
  * ���ܣ�
        ���ƴ�ֱ�ߣ�Ӧ����8λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_y:     �������������
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
 * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_8BITS)
void _DrawVer8(COLOR value, 
               UINT32 start_x, UINT32 start_y, 
               UINT32 end_y, 
               GUIFBMAP *pfbmap)
{
    UINT8 d = (UINT8)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT32 loop = end_y - start_y + 1;

    p += start_x + start_y * pfbmap->uiHorRes;
    while (loop--)
    { 
        *p = d;
        p += pfbmap->uiHorRes;
    }

    return;
}
#endif  //PIXEL_8BITS


/***
  * ���ܣ�
        ���ƴ�ֱ�ߣ�Ӧ����16λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_y:     �������������
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_16BITS)
void _DrawVer16(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_y, 
                GUIFBMAP *pfbmap)
{
    UINT16 d =(UINT16)value;
    UINT16 *p = pfbmap->pMapBuff;
    UINT32 loop = end_y - start_y + 1;
    
    p += start_x + start_y * pfbmap->uiHorRes;
    while (loop--)
    {
        *p = d;
        p += pfbmap->uiHorRes;
    }

    return;
}
#endif  //PIXEL_16BITS


/***
  * ���ܣ�
        ���ƴ�ֱ�ߣ�Ӧ����24λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_y:     �������������
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_24BITS)
void _DrawVer24(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_y, 
                GUIFBMAP *pfbmap)
{
    UINT32 d =(UINT32)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT32 loop = end_y - start_y + 1;
    UINT8 r = (d & 0xFF0000) >> 16;
    UINT8 g = (d & 0xFF00) >> 8;
    UINT8 b = d & 0xFF;

    p += (start_x + start_y * pfbmap->uiHorRes) * 3;
    while (loop--)
    {
        *(p + 0) = b;   //С�˴洢��B����:byte0
        *(p + 1) = g;   //С�˴洢��G����:byte1
        *(p + 2) = r;   //С�˴洢��R����:byte2
        p += pfbmap->uiHorRes * 3;
    }

    return;
}
#endif  //PIXEL_24BITS


/***
  * ���ܣ�
        ���ƴ�ֱ�ߣ�Ӧ����32λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_y:     �������������
        5.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_32BITS)
void _DrawVer32(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_y, 
                GUIFBMAP *pfbmap)
 {
    UINT32 d =(UINT32)value;
    UINT32 *p = pfbmap->pMapBuff;
    UINT32 loop = end_y - start_y + 1;

    p += start_x + start_y * pfbmap->uiHorRes;
    while (loop--)
    {
        *p = d;
        p += pfbmap->uiHorRes;
    }

    return;
}
#endif  //PIXEL_32BITS


/***
  * ���ܣ�
        ����б�ߣ�Ӧ����8λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.UINT32 end_y:     �������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_8BITS)
void _DrawBias8(COLOR value, 
                UINT32 start_x, UINT32 start_y, 
                UINT32 end_x, UINT32 end_y, 
                GUIFBMAP *pfbmap)
{
    UINT8 d = (UINT8)value;
    UINT8 *p = pfbmap->pMapBuff;
    INT32 dx, dy, sx, sy, e, t;

    if ((dy = end_y - start_y) > 0)
    {
        t = 1;
        p += start_x + start_y * pfbmap->uiHorRes;
    }
    else
    {   
        dy = -dy;
        t = -1;
        p += end_x + end_y * pfbmap->uiHorRes;
    }
    if ((dx = end_x - start_x) < 0)
    {
        dx = -dx ;
        t = -t;
    }
    if (dx >dy)
    {
        sx = t;
        sy = pfbmap->uiHorRes;
    }
    else
    {
        sx = pfbmap->uiHorRes;
        sy = t;
        t = dx;
        dx = dy;
        dy = t;
    }
    for (t=0, e= -dx; t<= dx; t++)
    {
        *p = d;
        p += sx;

        if ((e += 2 * dy) >= 0)
        {
            p += sy;
            e -= 2 * dx;
        }
    }

    return;
}
#endif  //PIXEL_8BITS


/***
  * ���ܣ�
        ����б�ߣ�Ӧ����16λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.UINT32 end_y:     �������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_16BITS)
void _DrawBias16(COLOR value, 
                 UINT32 start_x, UINT32 start_y, 
                 UINT32 end_x, UINT32 end_y, 
                 GUIFBMAP *pfbmap)
{
    UINT16 d = (UINT16)value;
    UINT16 *p = pfbmap->pMapBuff;
    INT32 dx, dy, sx, sy, e, t;

    if ((dy = end_y - start_y) >0)
    {
        t = 1;
        p += start_x + start_y * pfbmap->uiHorRes;
    }
    else
    {
        dy = -dy;
        t = -1;
        p += end_x + end_y * pfbmap->uiHorRes;
    }
    if ((dx = end_x - start_x) < 0 )
    {
        dx = -dx ;
        t = -t;
    }
    if (dx > dy)
    {
        sx = t;
        sy = pfbmap->uiHorRes;
    }
    else
    {
        sx = pfbmap->uiHorRes;
        sy = t;
        t = dx;
        dx = dy;
        dy = t;
    }
    for (t=0, e= -dx; t <= dx; t++)
    {
        *p = d;
        p += sx;

        if ((e += 2 * dy) >= 0)
        {
            p += sy;
            e -= 2 * dx;
        }
    }

    return;
}
#endif  //PIXEL_16BITS


/***
  * ���ܣ�
        ����б�ߣ�Ӧ����24λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.UINT32 end_y:     �������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_24BITS)
void _DrawBias24(COLOR value, 
                 UINT32 start_x, UINT32 start_y, 
                 UINT32 end_x, UINT32 end_y, 
                 GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT8 *p = pfbmap->pMapBuff;
    INT32 dx, dy, sx, sy, e, t;
    UINT8 r = (d & 0xFF0000) >> 16;
    UINT8 g = (d & 0xFF00) >> 8;
    UINT8 b = d & 0xFF;

    if ((dy = end_y - start_y) > 0)
    {
        t = 1;
        p += (start_x + start_y * pfbmap->uiHorRes) * 3;
    }
    else
    {
        dy = -dy;
        t = -1;
        p += (end_x + end_y * pfbmap->uiHorRes) * 3;
    }
    if ((dx = end_x - start_x) < 0)
    {
        dx = -dx;
        t = -t;
    }
    if (dx > dy)
    {
        sx = t * 3;
        sy = pfbmap->uiHorRes * 3;
    }
    else
    {
        sx = pfbmap->uiHorRes * 3;
        sy = t * 3;
        t = dx;
        dx = dy;
        dy = t;
    }
    for (t = 0, e = -dx; t <= dx; t++)
    {
        *(p + 0) = b;   //С�˴洢��B����:byte0
        *(p + 1) = g;   //С�˴洢��G����:byte1
        *(p + 2) = r;   //С�˴洢��R����:byte2
        p += sx;
        if ((e += 2 * dy) >= 0)
        {
            p += sy;
            e -= 2 * dx;
        }
    }

    return;
}
#endif  //PIXEL_24BITS


/***
  * ���ܣ�
        ����б�ߣ�Ӧ����32λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ��ʼ��ĺ�����
        3.UINT32 start_y:   ��ʼ���������
        4.UINT32 end_x:     ������ĺ�����
        5.UINT32 end_y:     �������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_32BITS)
void _DrawBias32(COLOR value, 
                 UINT32 start_x, UINT32 start_y, 
                 UINT32 end_x, UINT32 end_y, 
                 GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT32 *p = pfbmap->pMapBuff;
    INT32 dx, dy, sx, sy, e, t;

    if ((dy = end_y - start_y) >0)
    {
        t = 1;
        p += start_x + start_y * pfbmap->uiHorRes;
    }
    else
    {
        dy = -dy;
        t = -1;
        p += end_x + end_y * pfbmap->uiHorRes;
    }
    if ((dx = end_x - start_x) < 0 )
    {
        dx = -dx ;
        t = -t;
    }
    if (dx > dy)
    {
        sx = t;
        sy = pfbmap->uiHorRes;
    }
    else
    {
        sx = pfbmap->uiHorRes;
        sy = t;
        t = dx;
        dx = dy;
        dy =t;
    }
    for (t=0, e= -dx; t <= dx; t++)
    {
        *p = d;
        p += sx;

        if ((e += 2 * dy) >= 0)
        {
            p += sy;
            e -= 2 * dx;
        }
    }

    return;
}
#endif  //PIXEL_32BITS


/***
  * ���ܣ�
       ���ƿ���Բ��Ӧ����8λɫ֡����
  * ������
       1.COLOR value:       ��ɫֵ
       2.UINT32 point_x:    Բ�ĺ�����
       3.UINT32 point_y:    Բ��������
       4.UINT32 radius:     Բ�뾶
       5.GUIFBMAP *pfbmap:  ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_8BITS)
void _DrawCircle8(COLOR value,
                  UINT32 point_x, UINT32 point_y, 
                  UINT32 radius,
                  GUIFBMAP *pfbmap)
{
    UINT8 d = (UINT8)value;
    UINT8 *p = pfbmap->pMapBuff;
    int xp, yp, dy, dp, x, y, sym1, sym2, sym3, sym4;

    p += point_x + point_y * pfbmap->uiHorRes;
    xp = 0;
    yp = radius * 256 ;
    dy = 320 - yp;
    for (dp = xp - yp; dp <= 0; dp = xp - yp)
    {
        x = xp >> 8;
        y = yp >> 8;
        sym1 = y * pfbmap->uiHorRes + x;
        sym2 = sym1 - 2 * x;
        sym3 = x * pfbmap->uiHorRes + y;
        sym4 = sym3 - 2 * y;

        *(p + sym1) = d;
        *(p + sym2) = d;
        *(p - sym1) = d;
        *(p - sym2) = d;
        *(p + sym3) = d;
        *(p + sym4) = d;
        *(p - sym3) = d;
        *(p - sym4) = d;

        if (dy < 0)
        {
            dy += 2 * xp + 768;
        }
        else
        {
            dy += 2 * dp + 1280;
            yp -= 256;
        }
        xp += 256;
    }

    return;
}
#endif  //PIXEL_8BITS


/***
  * ���ܣ�
       ���ƿ���Բ��Ӧ����16λɫ֡����
  * ������
       1.COLOR value:       ��ɫֵ
       2.UINT32 point_x:    Բ�ĺ�����
       3.UINT32 point_y:    Բ��������
       4.UINT32 radius:     Բ�뾶
       5.GUIFBMAP *pfbmap:  ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_16BITS)
void _DrawCircle16(COLOR value,
                   UINT32 point_x, UINT32 point_y, 
                   UINT32 radius,
                   GUIFBMAP *pfbmap)
{
    UINT16 d = (UINT16)value;
    UINT16 *p = pfbmap->pMapBuff;
    int xp, yp, dy, dp, x, y, sym1, sym2, sym3, sym4;

    p += point_x + point_y * pfbmap->uiHorRes;
    xp = 0;
    yp = radius * 256 ;
    dy = 320 - yp;
    for (dp = xp - yp; dp <= 0; dp = xp - yp)
    {
        x = xp >> 8;
        y = yp >> 8;
        sym1 = y * pfbmap->uiHorRes + x;
        sym2 = sym1 - 2 * x;
        sym3 = x * pfbmap->uiHorRes + y;
        sym4 = sym3 - 2 * y;

        *(p + sym1) = d;
        *(p + sym2) = d;
        *(p - sym1) = d;
        *(p - sym2) = d;
        *(p + sym3) = d;
        *(p + sym4) = d;
        *(p - sym3) = d;
        *(p - sym4) = d;

        if (dy < 0)
        {
            dy += 2 * xp + 768;
        }
        else
        {
            dy += 2 * dp + 1280;
            yp -= 256;
        }
        xp += 256;
    }

    return;
}
#endif  //PIXEL_16BITS


/***
  * ���ܣ�
       ���ƿ���Բ��Ӧ����24λɫ֡����
  * ������
       1.COLOR value:       ��ɫֵ
       2.UINT32 point_x:    Բ�ĺ�����
       3.UINT32 point_y:    Բ��������
       4.UINT32 radius:     Բ�뾶
       5.GUIFBMAP *pfbmap:  ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_24BITS)
void _DrawCircle24(COLOR value,
                   UINT32 point_x, UINT32 point_y, 
                   UINT32 radius,
                   GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT8 *p = pfbmap->pMapBuff;
    int xp, yp, dy, dp, x, y, sym1, sym2, sym3, sym4;
    UINT8 r = (d & 0xFF0000) >> 16;
    UINT8 g = (d & 0xFF00) >> 8;
    UINT8 b = d & 0xFF;

    p += (point_x + point_y * pfbmap->uiHorRes) * 3;
    xp = 0;
    yp = radius * 256 ;
    dy = 320 - yp;
    for (dp = xp - yp; dp <= 0; dp = xp - yp)
    {
        x = xp >> 8;
        y = yp >> 8;
        sym1 = (y * pfbmap->uiHorRes + x) * 3;
        sym2 = sym1 - 2 * x * 3;
        sym3 = (x * pfbmap->uiHorRes + y) * 3;
        sym4 = sym3 - 2 * y * 3;

        *(p + sym1 + 0) = b;   //С�˴洢��B����:byte0
        *(p + sym1 + 1) = g;   //С�˴洢��G����:byte1
        *(p + sym1 + 2) = r;   //С�˴洢��R����:byte2
        *(p + sym2 + 0) = b;   //С�˴洢��B����:byte0
        *(p + sym2 + 1) = g;   //С�˴洢��G����:byte1
        *(p + sym2 + 2) = r;   //С�˴洢��R����:byte2
        *(p - sym1 + 0) = b;   //С�˴洢��B����:byte0
        *(p - sym1 + 1) = g;   //С�˴洢��G����:byte1
        *(p - sym1 + 2) = r;   //С�˴洢��R����:byte2
        *(p - sym2 + 0) = b;   //С�˴洢��B����:byte0
        *(p - sym2 + 1) = g;   //С�˴洢��G����:byte1
        *(p - sym2 + 2) = r;   //С�˴洢��R����:byte2
        *(p + sym3 + 0) = b;   //С�˴洢��B����:byte0
        *(p + sym3 + 1) = g;   //С�˴洢��G����:byte1
        *(p + sym3 + 2) = r;   //С�˴洢��R����:byte2
        *(p + sym4 + 0) = b;   //С�˴洢��B����:byte0
        *(p + sym4 + 1) = g;   //С�˴洢��G����:byte1
        *(p + sym4 + 2) = r;   //С�˴洢��R����:byte2
        *(p - sym3 + 0) = b;   //С�˴洢��B����:byte0
        *(p - sym3 + 1) = g;   //С�˴洢��G����:byte1
        *(p - sym3 + 2) = r;   //С�˴洢��R����:byte2
        *(p - sym4 + 0) = b;   //С�˴洢��B����:byte0
        *(p - sym4 + 1) = g;   //С�˴洢��G����:byte1
        *(p - sym4 + 2) = r;   //С�˴洢��R����:byte2

        if (dy < 0)
        {
            dy += 2 * xp + 768;
        }
        else
        {
            dy += 2 * dp + 1280;
            yp -= 256;
        }
        xp += 256;
    }

    return;
}
#endif  //PIXEL_24BITS


/***
  * ���ܣ�
       ���ƿ���Բ��Ӧ����32λɫ֡����
  * ������
       1.COLOR value:       ��ɫֵ
       2.UINT32 point_x:    Բ�ĺ�����
       3.UINT32 point_y:    Բ��������
       4.UINT32 radius:     Բ�뾶
       5.GUIFBMAP *pfbmap:  ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_32BITS)
void _DrawCircle32(COLOR value,
                   UINT32 point_x, UINT32 point_y,
                   UINT32 radius,
                   GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT32 *p = pfbmap->pMapBuff;
    int xp, yp, dy, dp, x, y, sym1, sym2, sym3, sym4;

    p += point_x + point_y * pfbmap->uiHorRes;
    xp = 0;
    yp = radius * 256 ;
    dy = 320 - yp;
    for (dp = xp - yp; dp <= 0; dp = xp - yp)
    {
        x = xp >> 8;
        y = yp >> 8;
        sym1 = y * pfbmap->uiHorRes + x;
        sym2 = sym1 - 2 * x;
        sym3 = x * pfbmap->uiHorRes + y;
        sym4 = sym3 - 2 * y;

        *(p + sym1) = d;
        *(p + sym2) = d;
        *(p - sym1) = d;
        *(p - sym2) = d;
        *(p + sym3) = d;
        *(p + sym4) = d;
        *(p - sym3) = d;
        *(p - sym4) = d;

        if (dy < 0)
        {
            dy += 2 * xp + 768;
        }
        else
        {
            dy += 2 * dp + 1280;
            yp -= 256;
        }
        xp += 256;
    }

    return;
}
#endif  //PIXEL_32BITS


/***
  * ���ܣ�
        �������飬Ӧ����8λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ����ʼ��ĺ�����
        3.UINT32 start_y:   ����ʼ���������
        4.UINT32 end_x:     �������ĺ�����
        5.UINT32 end_y:     ��������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_8BITS)
void _DrawBlock8(COLOR value, 
                 UINT32 start_x, UINT32 start_y, 
                 UINT32 end_x, UINT32 end_y, 
                 GUIFBMAP *pfbmap)
{
    UINT8 d = (UINT8)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT32 h = end_y - start_y + 1;
    UINT32 w = end_x - start_x + 1;
    UINT32 offset, t;

    p += start_x + start_y * pfbmap->uiHorRes;
    offset = pfbmap->uiHorRes - w;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = d;
        }
        p += offset;
        w= t;
    }

    return;
}
#endif  //PIXEL_8BITS


/***
  * ���ܣ�
        �������飬Ӧ����16λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ����ʼ��ĺ�����
        3.UINT32 start_y:   ����ʼ���������
        4.UINT32 end_x:     �������ĺ�����
        5.UINT32 end_y:     ��������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_16BITS)
void _DrawBlock16(COLOR value, 
                  UINT32 start_x, UINT32 start_y, 
                  UINT32 end_x, UINT32 end_y, 
                  GUIFBMAP *pfbmap)
{
    UINT16 d = (UINT16)value;
    UINT16 *p = pfbmap->pMapBuff;
    UINT32 h = end_y - start_y + 1;
    UINT32 w = end_x - start_x + 1;
    UINT32 offset, t;

    p += start_x + start_y * pfbmap->uiHorRes;
    offset = pfbmap->uiHorRes - w;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = d;
        }
        p += offset;
        w= t;
    }

    return;
}
#endif  //PIXEL_16BITS


/***
  * ���ܣ�
        �������飬Ӧ����24λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ����ʼ��ĺ�����
        3.UINT32 start_y:   ����ʼ���������
        4.UINT32 end_x:     �������ĺ�����
        5.UINT32 end_y:     ��������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
       ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_24BITS)
void _DrawBlock24(COLOR value, 
                  UINT32 start_x, UINT32 start_y, 
                  UINT32 end_x, UINT32 end_y, 
                  GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT8 *p = pfbmap->pMapBuff;
    UINT32 h = end_y - start_y + 1;
    UINT32 w = end_x - start_x + 1;
    UINT32 offset, t;
    UINT8 r = (d & 0xFF0000) >> 16;
    UINT8 g = (d & 0xFF00) >> 8;
    UINT8 b = d & 0xFF;

    p += (start_x + start_y * pfbmap->uiHorRes) * 3;
    offset = (pfbmap->uiHorRes - w) * 3;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = b;   //С�˴洢��B����:byte0
            *p++ = g;   //С�˴洢��G����:byte1
            *p++ = r;   //С�˴洢��R����:byte2
        }
        p += offset;
        w = t;
    }

    return;
}
#endif  //PIXEL_24BITS


/***
  * ���ܣ�
        �������飬Ӧ����32λɫ֡����
  * ������
        1.COLOR value:      ��ɫֵ
        2.UINT32 start_x:   ����ʼ��ĺ�����
        3.UINT32 start_y:   ����ʼ���������
        4.UINT32 end_x:     �������ĺ�����
        5.UINT32 end_y:     ��������������
        6.GUIFBMAP *pfbmap: ���Ʋ�������Ե�֡����ӳ�����
  * ���أ�
        ��
  * ��ע��
        ����ʹ��ʵ������ϵ�����߿�Ϊ1
***/
#if (PIXEL_32BITS)
void _DrawBlock32(COLOR value, 
                  UINT32 start_x, UINT32 start_y, 
                  UINT32 end_x, UINT32 end_y, 
                  GUIFBMAP *pfbmap)
{
    UINT32 d = (UINT32)value;
    UINT32 *p = pfbmap->pMapBuff;
    UINT32 h = end_y - start_y + 1;
    UINT32 w = end_x - start_x + 1;
    UINT32 offset, t;

    p += start_x + start_y * pfbmap->uiHorRes;
    offset = pfbmap->uiHorRes - w;
    t = w;
    while (h--)
    {
        while (w--)
        {
            *p++ = d;
        }
        p += offset;
        w = t;
    }

    return;
}
#endif  //PIXEL_32BITS

