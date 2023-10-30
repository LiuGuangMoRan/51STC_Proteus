#include <regx52.h>
#include <key.h>
#include <lcd1602.h>

unsigned char KeyNum;
unsigned int Password = 1234;
unsigned int count;
unsigned int word ;

void main()
{
	unsigned int num = 1000;
	
	LCD_Init();
	LCD_ShowNum(1,1,Password,4);
	LCD_ShowString(1,5,"password");
	while(1)
	{
		KeyNum = KEY();
		if(KeyNum)
		{
			if(KeyNum<=10)
			{
				if(count<4)
				{
					word *= 10;
					word += KeyNum%10;
					count++;
				}
				
				LCD_ShowNum(2,1,word,4);
			  if(word == Password)
				{
					LCD_ShowString(2,10,"OK");
				}
				else
				{
					LCD_ShowString(2,10,"NO");
				}
			}
		}
	}
	
}