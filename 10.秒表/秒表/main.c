#include <regx52.h>
#include "Timer0.h"
#include "Better_Small_key.h"
#include "Better_Nixie.h"
#include "I2C.H"

unsigned char KeyNum;               //选秒表的功能如：1.开始 2.暂停 3.重置
unsigned char Min,Sec,MiniSec;      //分别储存：分，秒，毫秒
unsigned char RunFlag;              //控制开始


//休眠毫秒数
void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		}while (--i);
		xms--;
	}	
}

void main()
{   Timer0_Init();
    while(1)
    {
			KeyNum=Key();
			if(KeyNum==1)			//K1按键按下
			{
				RunFlag=!RunFlag;	//启动标志位翻转
			}
			if(KeyNum==2)			//K2按键按下
			{
				Min=0;				//分秒清0
				Sec=0;
				MiniSec=0;
			}
			if(KeyNum==3)			//K3按键按下
			{
				AT24C02_WriteByte(0,Min);	//将分秒写入AT24C02
				Delay(5);
				AT24C02_WriteByte(1,Sec);
				Delay(5);
				AT24C02_WriteByte(2,MiniSec);
				Delay(5);
			}
			if(KeyNum==4)			//K4按键按下
			{
				Min=AT24C02_ReadByte(0);	//读出AT24C02数据
				Sec=AT24C02_ReadByte(1);
				MiniSec=AT24C02_ReadByte(2);
			}
        //设置数码管的数值：分，秒，毫秒
				Nixie_SetBuf(1,Min/10);
        Nixie_SetBuf(2,Min%10);
        Nixie_SetBuf(3,11);
        Nixie_SetBuf(4,Sec/10);
        Nixie_SetBuf(5,Sec%10);
        Nixie_SetBuf(6,11);
        Nixie_SetBuf(7,MiniSec/10);
        Nixie_SetBuf(8,MiniSec%10);
    }

}


//根据分秒毫秒进行进制
//  1000毫秒 = 1秒
void Sec_Loop(void)
{
	if(RunFlag)
	{
		MiniSec++;
		if(MiniSec>=100)    //1000ms 进制 1s
		{
			MiniSec=0;
			Sec++;
				if(Sec>=60)     //60s    进制 1min
				{
					Sec=0;
					Min++;
						if(Min>=60)
						{
							Min=0;
						}
				}
		}
		}
}

/**
 * 在main函数中，设置中断系统函数，可以多程序一起中断
 * 思想就是：一个中断函数，可以定时执行多个中断程序
*/
void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count1,T0Count2,T0Count3;
    TL0  = 0x18;
    TH0  = 0xFC;
    T0Count1++;
    if (T0Count1>=20)       //定时20ms执行Key_Loop(),消除对Delay()影响
    {
       T0Count1 = 0;
       Key_Loop();
    } 
    T0Count2++;             
    if (T0Count2>=2)        //定时2ms执行Nixie_Loop(),消除对位选，断选的影响，更好执行8个数码管工作
    {                       //需要注意的，不得大于2ms，否则就有虚影
       T0Count2 = 0;
       Nixie_Loop();
    } 
    T0Count3++;
	if(T0Count3>=10)        //驱动秒表函数：固定10ms调用Sec_Loop(),实现秒表的进制
	{
		T0Count3=0;
		Sec_Loop();	//10ms调用一次数秒表驱动函数
	}
       
}