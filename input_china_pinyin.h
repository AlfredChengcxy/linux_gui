/*
 * input_china_pinyin.h
 *
 *  Created on: Dec 1, 2014
 *      Author: lizhimin
 */

#ifndef INPUT_CHINA_PINYIN_H_
#define INPUT_CHINA_PINYIN_H_


/*******************************************
* Ϊʵ������ƴ�����뷨����Ҫ���õı�׼ͷ�ļ�
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*******************************************
* Ϊʵ������ƴ�����뷨����Ҫ���õ�����ͷ�ļ�
*******************************************/
#include "sqlite3.h"


typedef unsigned short UCS2;
typedef unsigned char UTF8;

#define UTF8_VALID_MAXLEN       3   //only UCS2, not supply UCS4
#define UTF8_STORE_MAXLEN       (UTF8_VALID_MAXLEN+1)


typedef sqlite3 INPUTDB;


#define PINYIN_VALID_MAXLEN     6   //long pinyin: chuang shuang zhuang
#define PINYIN_STORE_MAXLEN    (PINYIN_VALID_MAXLEN+1) //+'\0'
typedef struct 
{
    char Pinyin[PINYIN_STORE_MAXLEN];

    UCS2 *pWordCode;
    int iWordCount; //count of all word
    int iAddCount;  //when iAddCount == iWordCount, pWordCode[] Full

    int iViewLen;   //view set length
    int iHeadPos;   //view set:pWordCode[iHeadPos]~pWordCode[iTailPos]
    int iTailPos;   //view set:pWordCode[iHeadPos]~pWordCode[iTailPos]
    int iSelOffset; //select word:pWordCode[iHeadPos+iSelOffset]
} WordList;


//
UCS2* Utf8ToUcs2(UTF8 *pUtf8Code);
//
UTF8* Ucs2ToUtf8(UCS2 *pUcs2Code);


//
char* StrToLower(char *pConvStr);
//UCS2:0xFC(��) to ASCII:0x76(v)
char* TransCharU(char *pPinyinStr);
//ASCII:0x76(v) to UCS2:0xFC(��)
char* TransCharV(char *pPinyinStr);


//
int OpenInputDb(char *pDbName);
//
int CloseInputDb(void);


//
int ShowSingleRecord(void *pInpPara,
                     int iFieldNumber, char **ppFieldValue, char **ppFieldName);


//
WordList* QueryWordPinyin(char *pWordPinyin, int iViewLen);
//
int GetWordCount(void *pInpPara,
                 int iFieldNumber, char **ppFieldValue, char **ppFieldName);
//
int GetWordCode(void *pInpPara,
                int iFieldNumber, char **ppFieldValue, char **ppFieldName);


//
int CheckPinyinFile(char *pFileName);
//
int ImportPinyinFile(char *pFileName);
//
int ClearWordPinyin(void);
//
int InsertWordPinyin(char *pWordVal, char *pPinyinVal);



#endif /* INPUT_CHINA_PINYIN_H_ */

