#include "button.h"

void My_Exit_Init()
{
	
	//GPIO³õÊ¼»¯ PA0->LEFT PA1->UP PA2->DOWN PA3->RIGHT PB5->A PB6->HIT PB7->B
	GPIO_InitTypeDef GPIO_S;
	EXTI_InitTypeDef EXTI_S;
	NVIC_InitTypeDef NVIC_S;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_S.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_S.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_S);

	GPIO_S.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_5;
	GPIO_S.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_S);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	
	EXTI_S.EXTI_Line=EXTI_Line0;
	EXTI_S.EXTI_LineCmd=ENABLE;
	EXTI_S.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_S.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_S);
	
	EXTI_S.EXTI_Line=EXTI_Line1;
	EXTI_S.EXTI_LineCmd=ENABLE;
	EXTI_S.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_S.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_S);
	
	EXTI_S.EXTI_Line=EXTI_Line2;
	EXTI_S.EXTI_LineCmd=ENABLE;
	EXTI_S.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_S.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_S);
	
	EXTI_S.EXTI_Line=EXTI_Line3;
	EXTI_S.EXTI_LineCmd=ENABLE;
	EXTI_S.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_S.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_S);
	
	EXTI_S.EXTI_Line=EXTI_Line5;
	EXTI_S.EXTI_LineCmd=ENABLE;
	EXTI_S.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_S.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_S);
	
	EXTI_S.EXTI_Line=EXTI_Line9;
	EXTI_S.EXTI_LineCmd=ENABLE;
	EXTI_S.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_S.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_S);
	
	NVIC_S.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
	NVIC_S.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_S.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_S);
	
	NVIC_S.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
	NVIC_S.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_S.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_S);
	
	NVIC_S.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
	NVIC_S.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_S.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_S);
	
	NVIC_S.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
	NVIC_S.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_S.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_S);
	
	NVIC_S.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_S.NVIC_IRQChannelCmd=ENABLE;
	NVIC_S.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_S.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_S);
}


