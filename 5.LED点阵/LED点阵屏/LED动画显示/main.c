#include <REGX52.H>

//重置命名对应端口号

sbit RCLK_1 = P3^5;			//根据时钟信号使输入缓冲器搬入输出缓冲器
sbit SERCLK = P3^6; 	//根据时钟信号使数据下移8次
sbit SER  = P3^4; 		//输入数据断 


//配置74HC595,即控制阳极
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i=0 ;
	for(i=0;i<8;i++)
	{	
		//SER是位，当它被赋于大1的数，非零即1
		//通过下面算法得到每个位的0/1，算法总结
		SER = Byte & (0x80>>i); //被于有 0x80，0x40，0x20.....
		SERCLK = 1; //打开赋给时钟信号1，使数据向下移
		SERCLK = 0; //恢复0
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


//配置一列亮的LED
void show_LEDcolumn(unsigned char Column,unsigned char Data)
{
	_74HC595_WriteByte(Data); //设置阳极,一列的LED亮
	P0 = ~(0x80>>Column);     //设置阴极,哪一列亮
	
	//消影
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
			Offset++;//加多了会使数组溢出
			//防溢出
			if(Offset>40)
			{
				Offset=0;
			}
		}
		
	}
}