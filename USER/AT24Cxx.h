#ifndef __AT24CXX_H
#define __AT24CXX_H

#include "i2c.h"

#define AT24C32		4095
#define Score_Addres  0


unsigned char AT24CXX_ReadOneByte(unsigned int ReadAddr);							//指定地址读取一个字节
void AT24CXX_WriteOneByte(unsigned int WriteAddr,unsigned char DataToWrite);		//指定地址写入一个字节
void AT24CXX_WriteLenByte(unsigned int WriteAddr,unsigned long int DataToWrite,unsigned char Len);//指定地址开始写入指定长度的数据
unsigned long int AT24CXX_ReadLenByte(unsigned int ReadAddr,unsigned char Len);					//指定地址开始读取指定长度数据
void AT24CXX_Write(unsigned int WriteAddr,unsigned char *pBuffer,unsigned int NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read(unsigned int ReadAddr,unsigned char *pBuffer,unsigned int NumToRead);   	//从指定地址开始读出指定长度的数据

unsigned char AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC

#endif

