#include <REGX52.H>

//数码管段码表
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

//延时子函数
void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

//数码管显示子函数
void Nixie(unsigned char Location,Number)
{
	switch(Location)		//位码输出
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P1=NixieTable[Number];	//段码输出
	Delay(1);				//显示一段时间
}

unsigned char KEY()
{
	unsigned char KeyNumber = 0;
	if(P3_1 == 0){Delay(20);while(P3_1==0);Delay(20);KeyNumber = 1;}
	if(P1_0 == 0){Delay(20);while(P1_0==0);Delay(20);KeyNumber = 2;}
	if(P1_2 == 0){Delay(20);while(P1_2==0);Delay(20);KeyNumber = 3;}
	if(P1_3 == 0){Delay(20);while(P1_3==0);Delay(20);KeyNumber = 4;}
	
	return KeyNumber;
}

void Timer0_Init()
{
	TMOD=0x01;
	
	TL0=0x9C;
	TH0=0xFF;
	
	TF0=0;
	TR0=1;
	
	ET0=1;
	EA=1;
	PT0=0;
	
}

unsigned char Counter,Compare;
unsigned char KeyNum,Speed;
sbit Motor = P0^0;

void main()
{	
	Timer0_Init();
	Nixie(1,0);
	while(1)
	{	
			KeyNum = KEY();
			if(KeyNum == 1)
			{
				Speed++;
				Speed%=4;
				KeyNum = 0;
			}
			Nixie(1,Speed);
			Delay(20);
	}
}

void Timer0_Routine() interrupt 1
{
	TL0=0x9C;
	TH0=0xFF;
	
	Counter++;
	Counter %= 100;
	if(Counter < Compare)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
	
}
