#include <REGX52.H>

/**
  * @brief  定时器0初始化
  * @param  无
  * @retval Timer0_Init()启动定时器，设置工作模式，设置定时初值
  */

void Timer0_Init()
{
	TMOD=0x01;	//不可寻址,控制定时器的模式为模式一,TMON为功能寄存器
	
	//下面为TCON控制计数器,跳变方式
	
	TF0=0;			//硬件置1或置0，清除TF0标志
	TR0=1;			//软件置1或置0，定时器0开始计时
	
	//控制计算器为1ms进行跳变,就要改变TH0,TL0的值
	//64535位十进制数,256为16的2次方,所以64535变成十六进制数,再变成8位
	//二进制数
	
	//TH0=64535/256;//获取前8位的数值
	//TL0=64535%256;//获取后8位的数值
	
    //直接采用16进制赋值
	  TH0 = 0xFC;	
    TL0 = 0x18;

	//控制中断系统,执行中断程序
	ET0=1;
	EA=1;
	PT0=0;
	
}

/**
  * @brief  执行中断程序(放在main函数中)
  * @param  无
  * @retval Timer0_Routine() interrupt 1  当定时器计数完毕，跳过当前程序，执行中断程序
  */

//主函数调用定时器模板

/*
void Timer0_Routine() interrupt 1   //初始值为1ms
{
    static unsigned int T0Count1;
    TL0  = 0x18;
    TH0  = 0xFC;
    T0Count1++;
    if (T0Count1>=)       //定时？多少ms执行中断系统
    {
      
    }     
}
*/
 


/**
  * @brief  初始化定时器(功能是不触发中断,不工作)，只需完成计数工作，完成需要其他函数
  * @param  无
  * @retval 无
  */
void Timer0_Init_NoWork()
{
	TMOD&=0xF0;		
	TMOD|=0x01;
	TH0=0;
	TL0=0;
	TF0=0;			
	TR0=0;			
}

/**
  * @brief  设置定时器的初值
  * @param  value设置定时器初值，通过/%得到前8位和后8位
  * @retval 无
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value/256;
	TL0 = Value%256;
}

/**
  * @brief  得到定时器的计数点
  * @param  无
  * @retval 返回的是以us作为单位的计数点
  */
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  控制定时器工作状态
  * @param  Flay控制定时器的开关
  * @retval 无
  */
void Timer0_Run(unsigned char Flag)
{
	TR0 = Flag;
}