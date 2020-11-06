#ifndef __SNAKE_H
#define __SNAKE_H

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define HIT 1
#define NO_HIT 0
#define Get_Food 1
#define NO_Get_Food 0
#define GO 1
#define OVER 0
#define BOOL unsigned char
	


typedef struct Snake
{
	unsigned char x;
	unsigned char y;
	struct Snake* next;
}snake;

typedef struct Food
{
	unsigned char x;
	unsigned char y;
}food;


//extern snake* head;
//extern snake* q;
extern unsigned char Food_Score;
extern unsigned int score;
extern unsigned int Sleep_Time;
extern BOOL Gamestatus;
extern unsigned char Dir;
void TIM3_Init(unsigned int arr,unsigned int psc);
void TIM2_Init(unsigned int arr,unsigned int psc);
void Snake_FOOD_Init(void);
void GameCir(void);

#endif


