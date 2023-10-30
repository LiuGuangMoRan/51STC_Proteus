#ifndef _I2C_H_
#define _I2C_H_

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck(void);
void AT24C02_WriteByte(unsigned char WordAddress,Date);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);

#endif