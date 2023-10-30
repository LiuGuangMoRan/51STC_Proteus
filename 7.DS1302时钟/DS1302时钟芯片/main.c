#include "DS1302.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "Keyboard.h"
#include <REGX52.H>

unsigned char KeyNum,Mode;

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"  -  -  ");//?????????
	LCD_ShowString(2,1,"  :  :  ");

	DS1302_SetTime();
	while(1)
	{
		KeyNum = SmallKey();
		if(KeyNum == 1)		//????,????
		{
			if(Mode == 0){Mode = 1;}
			else if (Mode == 1){Mode = 0;}
		}
		switch(Mode)
		{
			case 0:TimeShow();break;
			case 1:TimeSet(KeyNum);break;
		}
  }
}

