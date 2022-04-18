#ifndef _LCD12864_No_font_library_H_
#define _LCD12864_No_font_library_H_

#define LCD_DATA P2

#define uchar unsigned char
#define uint  unsigned int

sbit LCD_RS=P0^0;
sbit LCD_RW=P0^1;
sbit LCD_E=P0^2;

sbit LCD_CS2=P0^4;		//右屏选择（左右屏有时候相反）
sbit LCD_CS1=P0^3;		//左屏选择

//sbit LCD_RST=P3^7;


void LCD_check_busy()
{
	unsigned char temp;
	LCD_RS=0;
	LCD_RW=1;
	do
	{
		LCD_DATA=0xff;
		LCD_E=1;
		temp=LCD_DATA;
		LCD_E=0;
	}while((temp&0x80)==0x80);		
}
//写指令代码（cs为0选左屏，cs为1选右屏）
void LCD_W_code(unsigned char tpcode,bit cs)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_CS2=~cs;
	LCD_CS1=cs;
	LCD_DATA=tpcode;
	LCD_E=1;
	_nop_();
	LCD_E=0;
}
//写显示数据（cs为0选左屏，cs为1选右屏）
void LCD_W_data(unsigned char tpdata,bit cs)
{
	LCD_check_busy();
	LCD_RS=1;
	LCD_RW=0;
	LCD_CS2=~cs;
	LCD_CS1=cs;	
	LCD_DATA=tpdata;
	LCD_E=1;	
	_nop_();
	LCD_E=0;
}

//LCD初始化函数
void LCD_initialize()
{
//	LCD_RST=0;
	_nop_();
	_nop_();
 //   LCD_RST=1;
	LCD_W_code(0x3f,0);		//开显示设置	
	LCD_W_code(0xc0,0);		//设置显示起始行为第一行	
	LCD_W_code(0xb8,0);		//页面地址设置	
	LCD_W_code(0x40,0);		//列地址设为0
	LCD_W_code(0x3f,1);
	LCD_W_code(0xc0,1);	
	LCD_W_code(0xb8,1);
	LCD_W_code(0x40,1);
}

//LCD显示字符串函数（word表示要显示的字符串,
 //length表示要显示的字符串宽度,
 //x表示首字符所在行数,
 //y表示首字符所在列数）
void LCD_display_word(unsigned char word[],
                      unsigned int length,
					  unsigned char x,
					  unsigned char y)
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		
		LCD_W_code(0xb8+x,0);
		LCD_W_code(0xb8+x,1);
		if(y+i<64)
		{
			LCD_W_code(0x40+y+i,0);	
			LCD_W_data(word[i],0);
		}
		else
		{
			LCD_W_code(y+i,1);	
			LCD_W_data(word[i],1);
		}
	}
}
//LCD画全屏函数
void LCD_full_draw(unsigned char word[])
{
	unsigned char i,j;
	for(i=0;i<8;i++)
	{
		LCD_W_code(0xb8+i,0);
		LCD_W_code(0x40,0);	
		for(j=0;j<64;j++)
		{
			LCD_W_data(word[i*128+j],0);
		}
		LCD_W_code(0xb8+i,1);
		LCD_W_code(0x40,1);	
		for(j=0;j<64;j++)
		{
			LCD_W_data(word[i*128+64+j],1);
		}			
	}
}
//LCD显示一个字节函数（
//x表示x坐标,		X轴范围是 0 - 128
//y表示y坐标,		Y轴范围是 0 - 7
//tpdata表示要显示的数据）
void LCD_display_byte(unsigned char x,
					  unsigned char y,
					  unsigned char tpdata)
{
	if(x<64)
	{
		LCD_W_code(0xb8+y,0);
		LCD_W_code(0x40+x,0);
		LCD_W_data(tpdata,0);	
	}
	else
	{
		LCD_W_code(0xb8+y,1);
		LCD_W_code(x,1);
		LCD_W_data(tpdata,1);	
	}
} 

void LCD_draw(unsigned char word[])
{
  unsigned char i,j;
  for(i=0;i<8;i++)
  {
    LCD_W_code(0xb8+i,1);
	LCD_W_code(0x40+20,1);
	for(j=0;j<44;j++)
	{
	  LCD_W_data(word[i*44+j],1);
	}
  }
}

//LCD清屏函数
void LCD_clear()
{
	unsigned char i,j;
	for(i=0;i<8;i++)
	{
	  for(j=0;j<128;j++)
	   {
	     LCD_display_byte(j,i,0x00);
	   }
	}
}


#endif






