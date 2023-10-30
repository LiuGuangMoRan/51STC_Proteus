#include <REGX52.H>
#include <LCD1602.H>

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



void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;
	SCON = 0x50;
	TMOD &= 0x0F;	
	TMOD |= 0x20;		
	TL1 = 0xFD;	
	TH1 = 0xFD;		
	ET1 = 0;		
	TR1 = 1;		
}



void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(T1==0); //�����ݷ��ͽ���ʱ��Ӳ���Զ���1�����Ѿ������������жϣ����жϵ�·û������
	T1=0;					//����ָ���0��
	
}

void main()
{
	UartInit();
	
	while(1)
	{
	UART_SendByte(0x66);
	}
}