#include <REGX52.H>


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

unsigned char Key_KeyNumber;

unsigned char SmallKey()
{
	unsigned char KeyNumber = 0;
	if(P3_1 == 0){KeyNumber = 1;}
	if(P3_0 == 0){KeyNumber = 2;}
	if(P3_2 == 0){KeyNumber = 3;}
	if(P3_3 == 0){KeyNumber = 4;}
	
	
	return KeyNumber;
}

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

}

unsigned char Key(void)
{
	unsigned char Temp = 0 ;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}


