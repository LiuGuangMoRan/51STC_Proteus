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

void main()
{
	SERCLK = 0;
	RCLK_1 = 0;
	
	while(1)
	{
	
		//��ʾЦ��
		show_LEDcolumn(0,0x3C);
		show_LEDcolumn(1,0x42);
		show_LEDcolumn(2,0xA9);
		show_LEDcolumn(3,0x85);
		show_LEDcolumn(4,0x85);
		show_LEDcolumn(5,0xA9);
		show_LEDcolumn(6,0x42);
		show_LEDcolumn(7,0x3C);
	}
}