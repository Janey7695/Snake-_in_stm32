#include "draw_api.h"
#include "snake.h"
#include "stdlib.h"
#include "delay.h"
#include "stm32f10x.h"

snake* head;				//定义蛇头结构体指针
snake* q;					//定义蛇结点结构体指针
food* FOOD;					//定义食物结构体指针
unsigned char Dir;			//方向
BOOL Gamestatus=GO;			//游戏状态指示
unsigned int score=0;		//分数
unsigned int Sleep_Time=1000;//移动间隔（游戏难度）
unsigned char Food_Score=10;//每个食物加分

//初始化定时器
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


//绘制蛇的身体结点 由于0.96 oled的像素点比较小，因此每个蛇或食物结点都用4个像素点来表示。
void Draw_Snake_Point(unsigned char x,unsigned char y)
{
	Draw_Point(x,y);
	Draw_Point(x-1,y);
	Draw_Point(x-1,y+1);
	Draw_Point(x,y+1);
}

//初始化蛇身与食物
void Snake_FOOD_Init()
{
	snake* tail;			//定义蛇尾指针
	unsigned char i;
	TIM3_Init(50,65530);	//使用定时器生成0-50的伪随机数
	TIM2_Init(15,65530);	//使用定时器生成0-15的伪随机数
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	tail=(snake*)malloc(sizeof(snake));//为蛇尾结构体申请空间
	FOOD=(food*)malloc(sizeof(food));//为食物结构体申请空间
	FOOD->x=50;			//初始食物x=50 y=44
	FOOD->y=44;
	tail->x=46;			//蛇的初始末节在x=46 y=30
	tail->y=30;
	tail->next=NULL;
	CanvasClear();		//清除画布
	
	//通过for循环生成3个蛇身节点作为初始蛇身
	for(i=1;i<3;i++)
	{
		head=(snake*)malloc(sizeof(snake));
		head->next=tail;
		head->x=46+i*2;
		head->y=30;
		tail=head;
	}
	
	//将初始好的蛇身画到 画布缓存 上去
	while(tail)
	{
		Draw_Snake_Point(tail->x,tail->y);
		tail=tail->next;
	}
	Draw_Snake_Point(FOOD->x,FOOD->y);
	
	//在画布缓存上写字符串
	OLED_ShowStrRAM(0,0,"score:0",16);
	//显示 画布缓存 的内容
	DisPlay();
	//初始方向为 右
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

//生成一个新的食物，需要保证：1. 食物结点必须是偶数（因为4个像素点才算一个食物结点） 2.不能生成在蛇身上
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
	//先提前创建蛇头结点下一步移动到的结点
	snake* nextpoi;
	nextpoi=(snake*)malloc(sizeof(snake));
	
	if(Dir==UP)
	{
		//将结点逐个推进，然后删除末节点（没吃到食物的话）
		nextpoi->x=head->x;
		nextpoi->y=head->y-2;
		if(nextpoi->y==14)
			nextpoi->y=62;
		nextpoi->next=head;
		head=nextpoi;
		//如果吃到食物 不删除末结点
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
		//如果碰到自己 游戏结束
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


//游戏循环主体
void GameCir()
{
		//清空画布缓存
		CanvasClear();
		//绘制一个矩形 作为游戏边框
		Draw_Rect(0,16,127,63,0);
		//蛇移动一次
		Snake_Move();
		//往缓存写字符串，显示当前分数
		OLED_ShowStrRAM(0,0,"score:",16);
		if(score<100)
			OLED_ShowNumRAM(48,0,score,2,16);
		if(score>=100&score<1000)
			OLED_ShowNumRAM(48,0,score,3,16);
		if(score>=1000&score<10000)
			OLED_ShowNumRAM(48,0,score,4,16);
		//往缓存写字符串，显示当前难度
		OLED_ShowNumRAM(96,0,(1200-Sleep_Time)/100,4,16);
		//显示刚刚绘制到缓存内的一帧画面
		DisPlay();
		//延时
		delay_ms(Sleep_Time);

}




