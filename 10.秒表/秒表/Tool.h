#ifndef __TOOL_H__
#define __TOOL_H__

//1.????
void Delay(unsigned int xms);

//2.????????
void NixieTable(unsigned char Number);
void Nixie(unsigned char Location,unsigned char Number);


//3.LCD1602???
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Init(void);
void LCD_Pleace(unsigned char Line,unsigned char Column);
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char);
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char*String);
void LCD_Pow(int X,int Y);
void LCD_ShowNum(unsigned char Line,unsigned Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);

void Nixie_SetBuf(unsigned char Location,Number);
void Nixie_Loop(void);
#endif