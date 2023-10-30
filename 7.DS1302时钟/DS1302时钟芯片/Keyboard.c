#include <REGX52.H>
#include <delay.h>
/**	4x4点阵键盘模块化
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval KeyNumber 按下按键的键码值
			如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
	@explain P1_0 ~ P1_3端是输入低电平，P1_7 ~ P1_4端是接收低电平，通过按下按键作为条件
	 		 P1 = 0xFF 使P1_0 ~ P1_7全为高电平，Delay函数消除按键前后影响
  */


/**	4键键盘模块化
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval KeyNumber 按下按键的键码值
			如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
	@explain 输入低电平为接地端，P3_0 ~ P3_3端是接收低电平，通过按下按键作为条件，Delay函数消除按键前后影响
  */

unsigned char SmallKey()
{
	unsigned char KeyNumber = 0;
	if(P1_1 == 0){Delay(20);while(P1_1==0);Delay(20);KeyNumber = 1;}
	if(P1_0 == 0){Delay(20);while(P1_0==0);Delay(20);KeyNumber = 2;}
	if(P1_2 == 0){Delay(20);while(P1_2==0);Delay(20);KeyNumber = 3;}
	if(P1_3 == 0){Delay(20);while(P1_3==0);Delay(20);KeyNumber = 4;}
	
	
	return KeyNumber;
}