#include "draw_api.h"
#include "snake.h"
#include "stdlib.h"
#include "delay.h"
#include "stm32f10x.h"
snake* head;
snake* q;
food* FOOD;
unsigned char Dir;
BOOL Gamestatus=GO;
unsigned int score=0;
unsigned int Sleep_Time=1000;
unsigned char Food_Score=10;

void TIM3_Init(unsigned int arr,unsigned int psc)
{
	TIM_TimeBaseInitTypeDef TIM_Stru;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_Stru.TIM_Prescaler=psc-1;
	TIM_Stru.TIM_Period=arr-1;
	TIM_Stru.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Stru.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_Stru);
}
void TIM2_Init(unsigned int arr,unsigned int psc)
{
	TIM_TimeBaseInitTypeDef TIM_Stru;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_Stru.TIM_Prescaler=psc-1;
	TIM_Stru.TIM_Period=arr-1;
	TIM_Stru.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Stru.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_Stru);
}

//绘制蛇的身体结点
void Draw_Snake_Point(unsigned char x,unsigned char y)
{
	Draw_Point(x,y);
	Draw_Point(x-1,y);
	Draw_Point(x-1,y+1);
	Draw_Point(x,y+1);
}


void Snake_FOOD_Init()
{
	snake* tail;
	unsigned char i;
	TIM3_Init(50,65530);
	TIM2_Init(15,65530);
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	tail=(snake*)malloc(sizeof(snake));
	FOOD=(food*)malloc(sizeof(food));
	FOOD->x=50;
	FOOD->y=44;
	tail->x=46;
	tail->y=30;
	tail->next=NULL;
	CanvasClear();
	for(i=1;i<3;i++)
	{
		head=(snake*)malloc(sizeof(snake));
		head->next=tail;
		head->x=46+i*2;
		head->y=30;
		tail=head;
	}
	while(tail)
	{
		Draw_Snake_Point(tail->x,tail->y);
		tail=tail->next;
	}
	Draw_Snake_Point(FOOD->x,FOOD->y);
	OLED_ShowStrRAM(0,0,"score:0",16);
	DisPlay();
	Dir=RIGHT;
}




//判断是否咬到自己，x,y为头结点坐标，S为蛇身，遍历检测
//若咬到返回1 否则返回0
BOOL IF_Hit(unsigned char x,unsigned char y)
{
	q=head->next;
	while(q)
	{	
		if(x==q->x&&y==q->y)
			return HIT;
		q=q->next;

	}
	return NO_HIT;
}

void Create_FOOD()
{
	FOOD->x=4+TIM3->CNT*2;
	FOOD->y=18+TIM2->CNT*2;
	while(IF_Hit(FOOD->x,FOOD->y))
	{
		FOOD->x=4+TIM3->CNT*2;
		FOOD->y=18+TIM2->CNT*2;
	}
}


//检测是否吃到食物
BOOL IF_Get_Food(unsigned char x,unsigned char y) 
{
	if(x==FOOD->x&&y==FOOD->y)
	{
		Create_FOOD();
		score+=Food_Score;
		return Get_Food;
	}
	else
	return NO_Get_Food;

}
//小蛇移动
void Snake_Move()
{
	snake* nextpoi;
	nextpoi=(snake*)malloc(sizeof(snake));
	if(Dir==UP)
	{
		nextpoi->x=head->x;
		nextpoi->y=head->y-2;
		if(nextpoi->y==14)
			nextpoi->y=62;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	if(Dir==DOWN)
	{
		nextpoi->x=head->x;
		nextpoi->y=head->y+2;
		if(nextpoi->y==64)
			nextpoi->y=16;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	if(Dir==LEFT)
	{
		nextpoi->x=head->x-2;
		nextpoi->y=head->y;
		if(nextpoi->x==0)
			nextpoi->x=126;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	if(Dir==RIGHT)
	{
		nextpoi->x=head->x+2;
		if(nextpoi->x==128)
			nextpoi->x=0;
		nextpoi->y=head->y;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	Draw_Snake_Point(FOOD->x,FOOD->y);
}



void GameCir()
{
		CanvasClear();
		Draw_Rect(0,16,127,63,0);
		Snake_Move();
		OLED_ShowStrRAM(0,0,"score:",16);
		if(score<100)
			OLED_ShowNumRAM(48,0,score,2,16);
		if(score>=100&score<1000)
			OLED_ShowNumRAM(48,0,score,3,16);
		if(score>=1000&score<10000)
			OLED_ShowNumRAM(48,0,score,4,16);
		OLED_ShowNumRAM(96,0,(1200-Sleep_Time)/100,4,16);
		DisPlay();
		delay_ms(Sleep_Time);

}




