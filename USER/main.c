#include "stm32f10x.h"
#include "oled.h"
#include "bmp.h"
#include "delay.h"
#include "draw_api.h"
#include "snake.h"
#include "button.h"

#if AT24C_XX_EN
#include "24cxx.h" 
#endif


BOOL flag=1;
BOOL flag1=1;

BOOL Choice=1;
void Menu(void)
{
	
	OLED_DrawBMP(0,0,128,8,BMP2);
	
	while(flag)
	{
		if(Choice==2)
		{
			OLED_ShowString(70,3,"Start",8);
			OLED_ShowString_Reverse(60,4,"Highlight",8);
		}
		#if AT24C_XX_EN

		if(Choice==1)
		{
			OLED_ShowString_Reverse(70,3,"Start",8);
			OLED_ShowString(60,4,"Highlight",8);
		}
		while(Choice==2&&flag1==0)
		{
			unsigned long int i=0;	
			CanvasClear();
			OLED_ShowStrRAM(0,0,"   The Highest   ",8);
			i=(unsigned int)AT24CXX_ReadLenByte(Score_ADDR,2);
			OLED_ShowNumRAM(48,2,i,4,16);
			DisPlay();
			
		}
		
		#endif
	}
}


int main(void)
{		
	#if AT24C_XX_EN
	unsigned long int i=0;
	#endif
		
	SystemInit();	
	delay_init(72);
	OLED_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_Exit_Init();
	OLED_Clear();
	
	#if AT24C_XX_EN
	
	AT24CXX_Init();
	while(AT24CXX_Check())
	{
		OLED_ShowString(70,4,"Init ",8);
		OLED_ShowString(70,5,"Falled",8);
	}
	
	#endif
	
	
	Menu();
	Snake_FOOD_Init();
	
	while(Gamestatus)
	{
		GameCir();
	}
	OLED_DrawBMP(0,0,128,8,BMP3);
	delay_ms(1000);
	CanvasClear();
	OLED_ShowStrRAM(0,0,"Your Final Score ",8);
	OLED_ShowNumRAM(48,1,score,4,16);
	
	
	#if AT24C_XX_EN
	
	OLED_ShowStrRAM(0,3,"   The Highest   ",8);
	//从24c32中读取最高分
	i=(unsigned int)AT24CXX_ReadLenByte(Score_ADDR,2);
	if(score>i)
	{
		AT24CXX_WriteLenByte(Score_ADDR,score,2);
		OLED_ShowNumRAM(48,4,score,4,16);
	}
	else
	{
		OLED_ShowNumRAM(48,4,i,4,16);
	}
	
	#endif
	
	DisPlay();
	while(1);

}

void EXTI0_IRQHandler()
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
		if(Dir!=RIGHT)
		Dir=LEFT;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler()
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
	if(Dir!=DOWN)
		Dir=UP;	
}
	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler()
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
	if(Dir!=UP)
		Dir=DOWN;
}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler()
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0)
	{
	if(Dir!=LEFT)
		Dir=RIGHT;
}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI9_5_IRQHandler()
{
	delay_ms(2);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)
		{
			if(!flag)
			{
				Food_Score+=5;
				Sleep_Time-=100;
				if(Sleep_Time<200)
					Sleep_Time=200;
				if(Food_Score>50)
					Food_Score=50;
				delay_ms(30);
			}
			#if AT24C_XX_EN
			else
			{
				Choice-=1;
				if(Choice==0)
					Choice=2;
				delay_ms(40);
			}
			#endif
			
			
			EXTI_ClearITPendingBit(EXTI_Line5);
			
			//反转
		}
		else
		{
			if(!flag)
			{
				Food_Score-=5;
				Sleep_Time+=100;
				if(Sleep_Time>1100)
					Sleep_Time=1100;
				if(Food_Score<5)
					Food_Score=5;
				delay_ms(30);
			}
			#if AT24C_XX_EN
			else
			{
				Choice+=1;
				if(Choice>2)
					Choice=1;
				delay_ms(40);
			}
			#endif
			
			
			EXTI_ClearITPendingBit(EXTI_Line5);
			//正转
		}
	}
	delay_ms(9);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)
	{
		if(Choice==1)
			flag=0;
		if(Choice==2)
		{
			OLED_Clear();
			if(flag1==0)
			{
				flag1=1;
				OLED_DrawBMP(0,0,128,8,BMP2);
			}
				
			else
				flag1=0;
						
		}
			
		
		delay_ms(100);
		EXTI_ClearITPendingBit(EXTI_Line9);
		//按下
	}
}
