#ifndef __TIMER0_H__
#define __TIMER0_H__

//定时器计数且触发外部中断
void Timer0_Init(void);

//定时器由函数控制工作，且做为计数时间的工具，返回计数时间点
void Timer0_Init_NoWork();
void Timer0_SetCounter(unsigned int Value);
unsigned int Timer0_GetCounter(void);
void Timer0_Run(unsigned char Flag);

#endif