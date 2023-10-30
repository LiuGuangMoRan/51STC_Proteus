#include <REGX52.H>
#include <delay.h>

sbit LCD_RS = P3^0;				//	RS:	数据/指令端，1为数据，0为指令
sbit LCD_RW = P3^1;				//	RW:	读写/写端，1为读，0为写
sbit LCD_E  = P3^2;				//	E：	使1数据有效，下降沿执行命令

#define LCD_DataPort P2		////数据输入端，传16进制数，0000 0000 

/** 
  * @brief  1.延迟函数
  * @param  xms为所需的延迟时间(单位：ms)
  * @retval Delay(xms)作用于等待或消除时间对程序的影响,根据单片机晶振频率计算得来
  */



	
/** 
  * @brief  3.LCD1602液晶显示屏模块化
  * @include 3.1 写入功能指令，LCD1602器件有指令集  	        3.2写入数据
  * 		 		 3.3对LCD进行初始化								                3.4选定屏幕位置
  * 		     3.6展示字符串									                  3.7展示无符号的数字	
  * 	       3.8.展示符号的数字
  */

/** 
  * @brief   3.1写入功能指令，LCD1602器件有指令集
  * @param   Command为写入指定内容
  * @retval  LCD_WriteCommand(Command)写入功能指令，对LCD1602进行初始化  
  */

void LCD_WriteCommand(unsigned char Command)
{	
	//根据写入数据/指令(时序结构)
	
	LCD_RS = 0;								// 0为指令
	LCD_RW = 0;								// 0为写入
	LCD_DataPort = Command;					// 写入指定内容
	LCD_E  = 1;								// 下降沿执行命令
	Delay(1);								
	LCD_E  = 0;
	Delay(1);
}


/** 
  * @brief   //3.2写入数据
  * @param   Data为写入指定内容
  * @retval  LCD_WriteData(Data)写入数据内容
  */

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;								// 1为指令
	LCD_RW = 0;								// 0为写入
	LCD_DataPort = Data;					// 写入指定内容
	LCD_E  = 1;								// 下降沿执行命?
	Delay(1);								// 执行指令的时间为ms级
	LCD_E  = 0;								// 而E的执行时间为ns级 ,所以要延迟以防E执行过快
	Delay(1);								// 前面的Delay1ms都不能少，少了就通信不了
}

/** 
  * @brief   //3.3对LCD进行初始化
  * @param   无
  * @retval  LCD_Init(void)对LCD选定所需功能一些指令
  */

void LCD_Init(void)
{
	//选定所需功能
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

/** 
  * @brief   //3.4选定屏幕位置
  * @param   Line是选定LCD的行  Column是选定LCD列的
  * @retval  LCD_Pleace(Line,Column)选定LCD屏幕位置
  */

void LCD_Pleace(unsigned char Line,unsigned char Column)
{
	if(Line == 1)
	{
		LCD_WriteCommand(0x80|(Column-1));			//设置数据位置(光标位置)
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);
	}
}

/** 
  * @brief   //3.5展示单字节
  */

void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_Pleace(Line,Column);
	LCD_WriteData(Char);
}

/** 
  * @brief   //3.6展示字符串
  */
 
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char*String)
{
	unsigned char i;
	LCD_Pleace(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/** 
  * @brief   //3.6Pow平方运算(功能函数)
  */

int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result = 1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/** 
  * @brief  3.7展示无符号的数字
  */

void LCD_ShowNum(unsigned char Line,unsigned Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_Pleace(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');	//得到整数的每个数字
	}
}

/** 
  * @brief  3.8.展示符号的数
  */