#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"

sbit  DS1302_SCLK = P3^6;       //时序端口
sbit  DS1302_IO   = P3^4;       //输入输出端
sbit  DS1302_CE   = P3^5;       //使能控制端

//写入命令指令
#define DS1302_SECOND    0x80   //写入秒     
#define DS1302_MINUTE    0x82   //写入分钟
#define DS1302_HOUR      0x84   //写入小时
#define DS1302_DATE      0x86   //写入日
#define DS1302_MONTH     0x88   //写入月
#define DS1302_DAY       0x8A   //写入星期
#define DS1302_YEAR      0x8C   //写入年
#define DS1302_WP        0x8E   //写保护状态
//读入命令，为了减少定义，只要将低8位的0位置置1，即为读

unsigned char DS1302_Time[] = {23,3,21,10,29,30,2};

//初始化DS1302,将控制使能，时序端置0
void DS1302_Init(void)
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

//写入数据到DS1302存储器件中，写入命令指令和数据都是向上沿有效
//程序将信号输入到I0口上，DS1302接收数据无需关心
void DS1302_WriteByte(unsigned char Command,Data)
{
    unsigned char i;
    DS1302_CE = 1;          //使能端置1，表时序过程有效
    //写入命令指令
    for (i = 0;i < 8;i++)
    {   
        DS1302_IO = Command & (0x01<<i);//传入一位比特位放入IO，0x01与Command进行位运算,Command对应的位为1就是1,0就是0
        DS1302_SCLK = 1;    //开始SCLK就是0,置1代表数据有效，再置0恢复状态
        DS1302_SCLK = 0;
    }
    //写入数据
    for(i = 0;i<8;i++)
    {
        DS1302_IO = Data & (0x01<<i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
   DS1302_CE = 0;
}

//读出数据，包含写入命令指令(上沿有效)，读出数据(下沿有效)
//无需关心DS1302怎么发出数据的，当指令写入读数据时，DS1302开始写入数据，只需接收即可
unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i ,Data = 0x00;
    //第0位表示读写，0为写，1位读
    Command |= 0x01;//设置读的功能，能运用define
    DS1302_CE = 1;
    for(i = 0;i < 8;i++)
    {
        DS1302_IO = Command & (0x01<<i);
        DS1302_SCLK = 0;  //与上述相同，改变0/1位置，但效果不变，使读数据的下沿有效，不产生冲突
        DS1302_SCLK = 1;                
    }

    //读出数据
    for(i = 0;i < 8;i++)
    {   
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;   
        if(DS1302_IO) {Data |= (0x01<<i);} //当DS1302_IO为1时，Data对应的位置置1，当DS1302_IO为0时，Data为0            
    }
    DS1302_CE = 0;
    DS1302_IO = 0; //能解决数据不稳定的问题
    return Data;
}


//设置DS1302时间
 void DS1302_SetTime(void)
 {  //十进制转BCD码后写入
    DS1302_WriteByte(DS1302_WP,0x00);
    DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
 }

//读取DS1302时间
 void DS1302_ReadTime(void)
 {  //BCD码转十进制后读取
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
 }
 
 
  /*
    设置可调时钟的函数如下，与初始化DS1302模块化并不冲突，如果冲突可放在主函数中
 */

unsigned char TimeSelect,TimeSetFlashFlag;

void TimeShow(void)
{
  DS1302_ReadTime();//读取时间
	LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
}


void TimeSet(unsigned char KeyNum)
{   
    //选择数组位置
    if(KeyNum == 2)
    {
        TimeSelect++;
        TimeSelect %= 6;
    }
    //加对应的值
    if(KeyNum == 3)
    {
        DS1302_Time[TimeSelect]++;
        if(DS1302_Time[0]>99){DS1302_Time[0]=0;}//年越界判断
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}//月越界判断
		if( DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)//日越界判断
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}//大月
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}//小月
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}//闰年2月
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}//平年2月
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}//时越界判断
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}//分越界判断
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}//秒越界判断
    }
    //减对应的值
    if(KeyNum == 4)
    {
        DS1302_Time[TimeSelect]--;
        if(DS1302_Time[0]<0){DS1302_Time[0]=99;}//年越界判断
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}//月越界判断
		if( DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)//日越界判断
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}//大月
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}//小月
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}//闰年2月
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}//平年2月
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}//时越界判断
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}//分越界判断
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}//秒越界判断
    }
    if(TimeSelect==0 && TimeSetFlashFlag==1){LCD_ShowString(1,1,"  ");}
		else {LCD_ShowNum(1,1,DS1302_Time[0],2);}
		if(TimeSelect==1 && TimeSetFlashFlag==1){LCD_ShowString(1,4,"  ");}
		else {LCD_ShowNum(1,4,DS1302_Time[1],2);}
		if(TimeSelect==2 && TimeSetFlashFlag==1){LCD_ShowString(1,7,"  ");}
		else {LCD_ShowNum(1,7,DS1302_Time[2],2);}
		if(TimeSelect==3 && TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
		else {LCD_ShowNum(2,1,DS1302_Time[3],2);}
		if(TimeSelect==4 && TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
		else {LCD_ShowNum(2,4,DS1302_Time[4],2);}
		if(TimeSelect==5 && TimeSetFlashFlag==1){LCD_ShowString(2,7,"  ");}
		else {LCD_ShowNum(2,7,DS1302_Time[5],2);}

}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//??????
	TH0 = 0xFC;		//??????
	T0Count++;
	if(T0Count>=500)//?500ms????
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;//???????
	}
}