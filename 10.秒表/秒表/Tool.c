#include <REGX52.H>


/** 
  * @brief  2.模块化数码管操作
  * @param  Number控制数码管显示的数字(函数NixieTable)，Location选择对应的数码管，Number作用效果(Nixie)
  * @retval NixieTable(Number)控制数码管显示数值,Nixie(Location,Number)控制选定数码管
  * @explain P0端控制显示对应数值，P2_2 ~ P2_4控制数码管的选择，通过3个端口输入二进制代码，用译码器输出8种状态      
  */

//数码管显示缓存区
unsigned char Nixie_Buf[9]={0,10,10,10,10,10,10,10,10};

//数码管段码表
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40};

//控制选定数码管
void Nixie(unsigned char Location,unsigned char Number)
{	P0=0x00;
	 switch(Location)
	{
		case 1: P2_4=1;P2_3=1;P2_2=1;break;
		case 2: P2_4=1;P2_3=1;P2_2=0;break;
		case 3: P2_4=1;P2_3=0;P2_2=1;break;
		case 4: P2_4=1;P2_3=0;P2_2=0;break;
		case 5: P2_4=0;P2_3=1;P2_2=1;break;
		case 6: P2_4=0;P2_3=1;P2_2=0;break;
		case 7: P2_4=0;P2_3=0;P2_2=1;break;
		case 8: P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//段码输出
}


void Nixie_Loop(void)
{
	static unsigned char i = 1;
	Nixie(i,Nixie_Buf[i]);
	i++;
	if(i>=9){i=1;}
}

void Nixie_SetBuf(unsigned char Location,Number)
{
	Nixie_Buf[Location] = Number;
}

