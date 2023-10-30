#include <regx52.h>
#include <lcd1602.h>

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowNum(2,1,1234,4);
	while(1)
	{
	
	}
}