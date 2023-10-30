#include <REGX52.H>


/**	4x4点阵键盘模块化
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval KeyNumber 按下按键的键码值
			如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
	@explain P1_0 ~ P1_3端是输入低电平，P1_7 ~ P1_4端是接收低电平，通过按下按键作为条件
	 		 P1 = 0xFF 使P1_0 ~ P1_7全为高电平，Delay函数消除按键前后影响
  */

/**
 * 使用定时器固定扫描该函数：实现去除Delay函数带来的坏影响
 * 
 * 1.Keey_Loop()作用：固定获取2种状态：Key_keyNumber的位数/0 -----位数为(低电平/按下) ，0为(空闲和松开按键)
 * 2.定时器的用途，每隔20ms调用Kee_Loop()，去除20ms的抖动
 * 3.去抖动原理：抖动只有20ms,当获取到抖动的20ms中的1/0时，为1时没关系。为0时，表示按下了，但是后也至少有20ms的低电平
 * 也就是说，即使触发抖动的值，但也有至少20ms的保持状态
 * 4.按键为向上沿有效，即松开就有效
 * 5，SmallKey()为辅助，作用就是获取端口的按键按下的低电平
 * 6，Key_Loop()实时监控向下沿的状态
 * 7. key()判断按下以及松手，并且传值
*/


unsigned char BigKey()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){KeyNumber=1;}
	if(P1_6==0){KeyNumber=5;}
	if(P1_5==0){KeyNumber=9;}
	if(P1_4==0){KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){KeyNumber=2;}
	if(P1_6==0){KeyNumber=6;}
	if(P1_5==0){KeyNumber=10;}
	if(P1_4==0){KeyNumber=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){KeyNumber=3;}
	if(P1_6==0){KeyNumber=7;}
	if(P1_5==0){KeyNumber=11;}
	if(P1_4==0){KeyNumber=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){KeyNumber=4;}
	if(P1_6==0){KeyNumber=8;}
	if(P1_5==0){KeyNumber=12;}
	if(P1_4==0){KeyNumber=16;}
	
	return KeyNumber;
}



unsigned char Key_KeyNumber;

void Key_Loop(void)
{
	static unsigned char NowState, LastState;
	LastState  = NowState;
	NowState = SmallKey();
	if(LastState == 1  && NowState == 0)
	{
		Key_KeyNumber = 1;		
	}
	if(LastState == 2  && NowState == 0)
	{
		Key_KeyNumber = 2;		
	}
	if(LastState == 3  && NowState == 0)
	{
		Key_KeyNumber = 3;		
	}
	if(LastState == 4  && NowState == 0)
	{
		Key_KeyNumber = 4;		
	}
    if(LastState == 5  && NowState == 0)
	{
		Key_KeyNumber = 5;		
	}
    if(LastState == 6  && NowState == 0)
	{
		Key_KeyNumber = 6;		
	}
    if(LastState == 7  && NowState == 0)
	{
		Key_KeyNumber = 7;		
	}
    if(LastState == 8  && NowState == 0)
	{
		Key_KeyNumber = 8;		
	}
    if(LastState == 9  && NowState == 0)
	{
		Key_KeyNumber = 9;		
	}
    if(LastState == 10  && NowState == 0)
	{
		Key_KeyNumber = 10;		
	}
    if(LastState == 11  && NowState == 0)
	{
		Key_KeyNumber = 11;		
	}
    if(LastState == 12  && NowState == 0)
	{
		Key_KeyNumber = 12;		
	}
    if(LastState == 13  && NowState == 0)
	{
		Key_KeyNumber = 13;		
	}
    if(LastState == 14  && NowState == 0)
	{
		Key_KeyNumber = 14;		
	}
    if(LastState == 15  && NowState == 0)
	{
		Key_KeyNumber = 15;		
	}
    if(LastState == 16  && NowState == 0)
	{
		Key_KeyNumber = 16;		
	}

}

unsigned char Key(void)
{
	unsigned char Temp = 0 ;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}