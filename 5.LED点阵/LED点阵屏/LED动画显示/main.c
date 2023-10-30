#include <REGX52.H>

//����������Ӧ�˿ں�

sbit RCLK_1 = P3^5;			//����ʱ���ź�ʹ���뻺�����������������
sbit SERCLK = P3^6; 	//����ʱ���ź�ʹ��������8��
sbit SER  = P3^4; 		//�������ݶ� 


//����74HC595,����������
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i=0 ;
	for(i=0;i<8;i++)
	{	
		//SER��λ�����������ڴ�1���������㼴1
		//ͨ�������㷨�õ�ÿ��λ��0/1���㷨�ܽ�
		SER = Byte & (0x80>>i); //������ 0x80��0x40��0x20.....
		SERCLK = 1; //�򿪸���ʱ���ź�1��ʹ����������
		SERCLK = 0; //�ָ�0
	}
	
	RCLK_1 = 1;
	RCLK_1 = 0;
	
	//0x80 1000 0000  Byte 1001 1100
	
}

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


//����һ������LED
void show_LEDcolumn(unsigned char Column,unsigned char Data)
{
	_74HC595_WriteByte(Data); //��������,һ�е�LED��
	P0 = ~(0x80>>Column);     //��������,��һ����
	
	//��Ӱ
	Delay(1);
	P0 = 0xFF;
}

unsigned char Animation[]={
0x00,0x00,0x00,0x00,0x00,0xFF,0x08,0x08,0x08,0xFF,0x00,0x0E,0x15,0x15,0x15,0x09,0x00,0xFE,0x01,0x02,0x00,
0xFE,0x01,0x02,0x00,0x1C,0x22,0x22,0x22,0x1C,0x00,0xFB,0x00,0x00,0x00,0x00,0x00};

void main()
{
	unsigned char i ,Offset = 0 ,Count = 0;
	
	SERCLK = 0;
	RCLK_1 = 0;
	
	while(1)
	{
		for(i=0;i<8;i++)
		{
			show_LEDcolumn(i,Animation[i+Offset]);
		}
		Count++;
		if(Count>10)
		{
			Count = 0;
			Offset++;//�Ӷ��˻�ʹ�������
			//�����
			if(Offset>40)
			{
				Offset=0;
			}
		}
		
	}
}