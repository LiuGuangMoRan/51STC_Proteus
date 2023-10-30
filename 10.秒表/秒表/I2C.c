#include <REGX52.H>

//储存器件的地址
#define AT24C02_ADDRESS 0XA0 

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//I2C数据通信

/**·
  * @brief  I2C开始(数据传输开始)
  * @param  无
  * @retval 通信准备开始
  */
void I2C_Start(void)
{	
	I2C_SCL = 1;		//  先让时钟信号置1，SCL某些情况不是1
	I2C_SDA = 1;		//	同上
	I2C_SDA = 0;		//	当SCL,SDAc从高电平变低电平
	I2C_SCL = 0;		//	代表数据传输开始
}

/**
  * @brief  I2C结束(数据传输结束)
  * @param  无
  * @retval 通信结束
  */
void I2C_Stop(void)
{
	I2C_SDA = 0;		//	此时SDA在表达ACK时，可能为0/1，所以要先置0；
	I2C_SCL = 1;		//  最后一位的应答信时，最后SCL要置0的	
	I2C_SDA = 1;		//	只需要把SCL,SDA从低到高即可
}

//CPU发送数据到AT24C02,调用I2C_SendByte()函数把数据发送到AT24C02，其中根据SCL时钟信号统一步调
//AT24C02怎么接收存储，无需关心

//而把AT24C02发送数据到CPU，调用的是I2C_ReceiveByte(),它怎么发送的无需关心，其cpu接收是统一步调

/**
  * @brief  I2C数据发送
  * @param  无
  * @retval 数据帧为1个字节
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	//一个数据帧
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);		//获得传来的Byte的数据
		I2C_SCL = 1;	
		I2C_SCL = 0;
	}
}

/**
  * @brief  I2C数据接收
  * @param  无
  * @retval 数据帧为1个字节
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte = 0x00;
	I2C_SDA = 1;  //释放数据总线
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA)
		{
			Byte |= (0x80>>i);  //接收一个数据帧
		}
		I2C_SCL = 0;
	}
	return Byte;
}

/**
  * @brief  I2C数据发送应答0/1
  * @param  无
  * @retval 数据一个比特位
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

/**
  * @brief  I2C数据接收应答0/1
  * @param  无
  * @retval 数据一个比特位
  */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit =I2C_SDA;
	I2C_SCL=0;
	return AckBit;
}

//每个数据帧发送，要加前缀的，如：哪个存储器件，哪个存储位置
//而接收端需要的是需求数据，就要打开，怎么打开的无需关心

/**
  * @brief  用I2C写入存储器件
  * @param  无
  * @retval 发送数据不一个数据帧，包含发送存储器件，数据存储位置的地址等
  */
void AT24C02_WriteByte(unsigned char WordAddress,Date)
{
	I2C_Start();	//数据传输开始
	I2C_SendByte(AT24C02_ADDRESS); //发送到的储存器件
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress); //发送数据存储位置
	I2C_ReceiveAck();
	I2C_SendByte(Date);//发送需求数据
	I2C_ReceiveAck();
	I2C_Stop();//数据传输停止
}

/**
  * @brief  用I2C读取存储器件的内存
  * @param  无
  * @retval 发送数据不一个数据帧，包含发送存储器件，数据存储位置的地址等
  */
//读取存储器件内容(定死了存储器件只有一个)
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Date;
	I2C_Start(); 
	I2C_SendByte(AT24C02_ADDRESS);  //选定哪个存储器件读取
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);   //选定哪个数据位读取
	I2C_ReceiveAck();
	I2C_Start();		//读取数据位的规定
	
	I2C_SendByte(AT24C02_ADDRESS |0x01); //说明是读取规定数据位的字节
	I2C_ReceiveAck();
	Date = I2C_ReceiveByte(); //获取到数据
	I2C_SendAck(1);
	I2C_Stop();
	return Date;
}
