/*******************************************************************************
* Copyright(c) 2012 ,一诺仪器(威海)有限公司上海研发部 
*
* All rights reserved
*
* 文件名称：  guidevice.c
* 摘    要：  实现GUI基本输入/输出设备的用户自定义操作函数，为GUI所使用的这些设
*             备提供设备抽象层。
*
* 当前版本：  v1.1.0 (新增资源环境配置文件及设备抽象层文件)
* 作    者：  lzm
* 完成日期：  2014-12-04
*
* 取代版本：  v1.0.2 (对输入/输出设备的访问添加锁保护、重写事件及消息的接口函数)
* 原 作 者：  lzm
* 完成日期：  2014-11-04
*******************************************************************************/
    
#include "guidevice.h"
    
    
/**************************************
* 为实现GUIDEVICE而需要引用的其他头文件
**************************************/
#include "guievent.h"


/***
  * 功能：
        用户自定义的帧缓冲处理函数，用于完成自定义类型帧缓冲的处理
  * 参数：
        1.GUIFBMAP *pFbmapObj:  处理函数的帧缓冲对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
        1.必须返回-1表示无帧缓冲数据可刷新                    
        2.请根据实际情况修改代码 
***/
int CustomFbmapFunc(GUIFBMAP *pFbmapObj)
{
    //错误标志、返回值定义
    int iErr = 0;

    //加锁
    //请勿随意修改本段代码
    MutexLock(&(pFbmapObj->Mutex));

    if (pFbmapObj->iSyncFlag)
    {
        //此段根据实际情况完成相应代码
        //...
        pFbmapObj->iSyncFlag = 0;
    }
    else
    {
        iErr = -1;
    }

    //解锁
    //请勿随意修改本段代码
    MutexUnlock(&(pFbmapObj->Mutex));

    return iErr;
}


/***
  * 功能：
        用户自定义的键盘处理函数，用于完成自定义类型键盘的处理
  * 参数：
        1.GUIKEYPAD *pKeypadObj:    处理函数的键盘对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
        1.必须返回-1表示无键盘数据可读
        2.请根据实际情况修改代码 
***/
int CustomKeypadFunc(GUIKEYPAD *pKeypadObj)
{
    //错误标志、返回值定义
    int iErr = 0;
    //临时变量定义
    int iTmp;
    unsigned int uiKeyValue;
    GUIEVENT_ITEM *pEventItem = NULL;
    GUIEVENT *pEventObj = NULL;
    
    //加锁
    //请勿随意修改本段代码
    MutexLock(&(pKeypadObj->Mutex));

    if (!iErr)
    {
        //读取键盘返回的数据
        //此段根据实际情况完成相应代码
        ThreadTestcancel();
        iTmp = read(pKeypadObj->iDevFd, &uiKeyValue, sizeof(uiKeyValue));
        ThreadTestcancel();
        if (iTmp != sizeof(uiKeyValue))
        {
            iErr = -1;
        }
    }

    if (!iErr)
    {
        //尝试为按键事件项分配内存
        //请勿随意修改本段代码
        pEventItem = (GUIEVENT_ITEM *) malloc(sizeof(GUIEVENT_ITEM));
        if (NULL == pEventItem)
        {
            iErr = -2;
        }
    }

    if (!iErr)
    {
        //生成GUIEVENT_ITEM
        //此段根据实际情况完成相应代码
        pEventItem->uiEventType = GUIEVENT_TYP_IN;
        if (uiKeyValue & 0x000F0000)    //bit19~bit16:0=旋钮，1=按键
        {
            pEventItem->uiEventCode = (uiKeyValue & 0x00000F00) ?
                                      GUIEVENT_KEY_UP : GUIEVENT_KEY_DOWN;
            pEventItem->uiEventValue = uiKeyValue & 0x000000FF;
        }
        else
        {
            pEventItem->uiEventCode = (uiKeyValue & 0x0F000000) ?
                                      GUIEVENT_KNB_ANTI : GUIEVENT_KNB_CLOCK;
            pEventItem->uiEventValue = uiKeyValue & 0x000000FF;
        }
        //事件项写入事件队列
        //请勿随意修改本段代码
        pEventObj = GetCurrEvent();
        if (WriteEventQueue(pEventItem, pEventObj))
        {
            iErr = -3;
        }
    }

    //错误处理
    //此段根据实际情况完成相应代码
    switch (iErr)
    {
    case -3:
        free(pEventItem);
        //no break
    case -2:
    case -1:
    default:
        break;
    }

    //解锁
    //请勿随意修改本段代码
    MutexUnlock(&(pKeypadObj->Mutex));

    return iErr;
}


/***
  * 功能：
        自定义的触摸屏处理函数，用于完成触摸屏线程的处理
  * 参数：
        1.GUIKEYPAD *pTouchObj:    处理函数的键盘对象
  * 返回：
        成功返回零，失败返回非零值
  * 备注：
***/
int CustomTouchFunc(GUITOUCH *pTouchObj)
{
    //错误标志、返回值定义
    int iErr = 0;
    //临时变量定义
    static int iPrevX = -1, iPrevY = -1; 
    struct input_event Event[5];
    int iLen, iTouchAct, iAbsX, iAbsY, iTmp;
    GUIEVENT_ITEM *pEventItem = NULL;
    GUIEVENT *pEventObj = NULL;

    if (iErr == 0)
    {
        //读取触摸屏返回的数据
        ThreadTestcancel();
        iLen = read(pTouchObj->iDevFd, Event, sizeof(Event));
        ThreadTestcancel();
        if ( (iLen < sizeof(struct input_event)) || (iLen < 0))
        {
            iErr = -1;
        }
    }
    if (iErr == 0)
    {
        //初始化触摸动作标志及坐标值标志
        iTouchAct = -1;
        iAbsX = -1;
        iAbsY = -1;
        //从读取的数据中寻找触摸动作及坐标值
        iLen /= sizeof(struct input_event);
        for (iTmp = 0; iTmp < iLen; iTmp++)
        {
            //找到触摸动作，修改触摸动作标志
            if (Event[iTmp].type == EV_KEY)         //类型为按键
            {
                if (Event[iTmp].code == BTN_TOUCH)  //编码为触摸动作
                {
                    iTouchAct = Event[iTmp].value;  //得到触摸动作
                }
            }
            //找到坐标值，修改坐标值标志
            if (Event[iTmp].type == EV_REL)         //类型为坐标值
            {
                if (Event[iTmp].code == REL_X)      //编码为横坐标
                {
                    iAbsX = Event[iTmp].value;      //得到横坐标值
                }
                if (Event[iTmp].code == REL_Y)      //编码为纵坐标
                {
                    iAbsY = Event[iTmp].value;      //得到纵坐标值
                }
            }
            //得到点击触摸屏，直接忽略(点击触摸屏将由横纵坐标值来生成)
            if (iTouchAct == 1)
            {
                iTouchAct = -1;                     //重置触摸动作标志
            }
            //得到离开触摸屏或横纵坐标值，生成事件项
            if ((iTouchAct == 0) || 
                (iAbsX >= 0 && iAbsY >= 0))
            {
                //尝试为触摸屏事件项分配内存
                pEventItem = (GUIEVENT_ITEM *) malloc(sizeof(GUIEVENT_ITEM));
                if (NULL == pEventItem)
                {
                    iErr = -2;
                    break;
                }
                //生成GUIEVENT_ITEM
                pEventItem->uiEventType = GUIEVENT_TYP_IN;
                if (iTouchAct == 0)                 //离开触摸屏
                {
                    pEventItem->uiEventCode = GUIEVENT_ABS_UP;
                    pEventItem->uiEventValue = (iPrevX << 16) | iPrevY;
                    iTouchAct = -1;                 //重置触摸动作标志               
                }
                if (iAbsX >= 0 && iAbsY >= 0)       //横纵坐标值
                {
                    pEventItem->uiEventCode = GUIEVENT_ABS_DOWN;
                    pEventItem->uiEventValue = (iAbsX << 16) | iAbsY;
                    iPrevX = iAbsX;                 //保存横坐标
                    iPrevY = iAbsY;                 //保存纵坐标
                    iAbsX = -1;                     //重置横坐标标志
                    iAbsY = -1;                     //重置纵坐标标志
                }
				
				//if(g_ucKeyEnable)
				if(1)
				{
		            //事件项写入事件队列
	                pEventObj = GetCurrEvent();

	                if (WriteEventQueue(pEventItem, pEventObj))
	                {
		                    iErr = -3;
	                    break;
	                }
				}
  
            }
        }
    }

    //错误处理
    switch (iErr)
    {
    case -3:
        MutexUnlock(&(pEventObj->Mutex));
        free(pEventItem);
    case -2:
    case -1:
    default:
        break;
    }

    return iErr;
}

