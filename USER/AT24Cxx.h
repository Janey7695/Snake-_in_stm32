#ifndef __AT24CXX_H
#define __AT24CXX_H

#include "myiic.h"
#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C32

#define Score_Addres  0


unsigned char AT24CXX_ReadOneByte(unsigned int ReadAddr);							//指定地址读取一个字节
void AT24CXX_WriteOneByte(unsigned int WriteAddr,unsigned char DataToWrite);		//指定地址写入一个字节
void AT24CXX_WriteLenByte(unsigned int WriteAddr,unsigned long DataToWrite,unsigned char Len);//指定地址开始写入指定长度的数据
unsigned long  AT24CXX_ReadLenByte(unsigned int ReadAddr,unsigned char Len);					//指定地址开始读取指定长度数据
void AT24CXX_Write(unsigned int WriteAddr,unsigned char *pBuffer,unsigned int NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read(unsigned int ReadAddr,unsigned char *pBuffer,unsigned int NumToRead);   	//从指定地址开始读出指定长度的数据

unsigned char AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC

#endif

