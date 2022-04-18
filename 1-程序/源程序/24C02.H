#ifndef _24C02_H_
#define _24C02_H_

#include<intrins.h>

sbit SCL_24C02=P0^6;			//24C02串行时钟
sbit SDA_24C02=P0^7;			//24C02串行数据

void mDelay(uint t) //延时
{ 
	uchar i;
   	while(t--)
   	{
   		for(i=0;i<125;i++)
   		{;}
   	}
}

void NOP_24C02(void)		  //空操作
{
 	_nop_();
 	_nop_();
 	_nop_();
 	_nop_();
}


/*起始条件*/

void Start_24C02(void)
{
 	SDA_24C02=1;
 	SCL_24C02=1;
 	NOP_24C02();
 	SDA_24C02=0;
 	NOP_24C02();
}


 /*停止条件*/
void Stop_24C02(void)
{
 	SDA_24C02=0;
 	SCL_24C02=1;
 	NOP_24C02();
 	SDA_24C02=1;
 	NOP_24C02();
}

/*应答位*/
void Ack_24C02(void)
{
	SDA_24C02=0;
	NOP_24C02();
	SCL_24C02=1;
	NOP_24C02();
	SCL_24C02=0;
}

/*反向应答位*/
void NoAck_24C02(void)
{
 	SDA_24C02=1;
 	NOP_24C02();
 	SCL_24C02=1;
 	NOP_24C02();
 	SCL_24C02=0;
}

 /*发送数据子程序，Data为要求发送的数据*/
void Send_24C02(uchar Data)
{
   	uchar BitCounter=8;
   	uchar temp;
   	do
   	{
   		temp=Data;
   		SCL_24C02=0;
   		NOP_24C02();
   		if((temp&0x80)==0x80)
   		SDA_24C02=1;
   		else 
   		SDA_24C02=0;
   		SCL_24C02=1;
   		temp=Data<<1;
   		Data=temp;
   		BitCounter--;
   	}
   	while(BitCounter);
   	SCL_24C02=0;
}

/*读一字节的数据，并返回该字节值*/
uchar Read_24C02(void)
{
    uchar temp=0;
	uchar temp1=0;
	uchar BitCounter=8;
	SDA_24C02=1;
	do{
	SCL_24C02=0;
	NOP_24C02();
	SCL_24C02=1;
	NOP_24C02();
	if(SDA_24C02)
	temp=temp|0x01;
	else
	temp=temp&0xfe;
	if(BitCounter-1)
	{
	temp1=temp<<1;
	temp=temp1;
	}
	BitCounter--;
	}
	while(BitCounter);
	return(temp);
	}

void Write_dat_24C02(uchar Data[],uchar Address,uchar Num)
{
	uchar i;
	uchar *PData;
	PData=Data;
	for(i=0;i<Num;i++)
	{
		Start_24C02();
		Send_24C02(0xa0);
		Ack_24C02();
		Send_24C02(Address+i);
		Ack_24C02();
		Send_24C02(*(PData+i));
		Ack_24C02();
		Stop_24C02();
		mDelay(20);
	}
}

void Read_dat_24C02(uchar Data[],uchar Address,uchar Num)
{
	uchar i;
	uchar *PData;
	PData=Data;
	for(i=0;i<Num;i++)
	{
		Start_24C02();
		Send_24C02(0xa0);
		Ack_24C02();
		Send_24C02(Address+i);
		Ack_24C02();
		Start_24C02();
		Send_24C02(0xa1);
		Ack_24C02();
		*(PData+i)=Read_24C02();
		SCL_24C02=0;
		NoAck_24C02();
		Stop_24C02();
	}
}

#endif