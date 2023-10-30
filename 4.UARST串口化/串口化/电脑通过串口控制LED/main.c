#include <REGX52.H>
#include <LCD1602.H>

void UART_Init()
{ 
PCON &= 0x7F;
	SCON = 0x50;
	TMOD &= 0x0F;	
	TMOD |= 0x20;		
	TL1 = 0xFD;	
	TH1 = 0xFD;		
	ET1 = 0;		
	TR1 = 1;			
	
	//打开中断，执行中断代码
	EA=1;
	ES=1;
	
}


void main()
{
	UART_Init();
	LCD_Init();
	
	while(1)
	{
	LCD_ShowChar(2,1,'f');
	}
}

//运用传过来的数据进行操作控制
void UART_Routine() interrupt 4
{
	if(RI=1)
	{
		P2= SBUF;
		LCD_ShowChar(2,1,SBUF);
		RI=0;
	}
}

