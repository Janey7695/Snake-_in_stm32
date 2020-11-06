#ifndef __AT24CXX_H
#define __AT24CXX_H

#include "i2c.h"

#define AT24C32		4095
#define Score_Addres  0


unsigned char AT24CXX_ReadOneByte(unsigned int ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24CXX_WriteOneByte(unsigned int WriteAddr,unsigned char DataToWrite);		//ָ����ַд��һ���ֽ�
void AT24CXX_WriteLenByte(unsigned int WriteAddr,unsigned long int DataToWrite,unsigned char Len);//ָ����ַ��ʼд��ָ�����ȵ�����
unsigned long int AT24CXX_ReadLenByte(unsigned int ReadAddr,unsigned char Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(unsigned int WriteAddr,unsigned char *pBuffer,unsigned int NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(unsigned int ReadAddr,unsigned char *pBuffer,unsigned int NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

unsigned char AT24CXX_Check(void);  //�������
void AT24CXX_Init(void); //��ʼ��IIC

#endif

