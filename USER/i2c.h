#ifndef __I2C_H
#define __I2C_H

#include "sys.h"

#define SDA_IN() {GPIOB->CRL&=0x0FFFFFFF;GPIOB->CRL|=(unsigned long int)8<<12;}
#define SDA_OUT() {GPIOB->CRL&=0x0FFFFFFF;GPIOB->CRL|=(unsigned long int)3<<12;}

#define IIC_SCL PBout(4) //PB4->SCL
#define IIC_SDA PBout(3) //PB3->SDA
#define READ_SDA PBin(3)


void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(unsigned char txd);
unsigned char IIC_Read_Byte(unsigned char ack);


#endif

