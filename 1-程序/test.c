uchar system_time=0;
bit s0=0;
uchar beep_time=0;				   //蜂鸣器端口定义
sbit beep=P0^5;					   //蜂鸣器端口定义
uchar key_back=16;				   
uchar ms=0;				    
bit key_flag=0;
uchar Box_number=0;	
uchar xdata password[6]     ={0,0,0,0,0,0};  //存储密码的数组
uchar xdata password_flsh[6]={0,0,0,0,0,0};  //存储密码的数组
uchar password_count=0;			       //存储密码的数组计数变量
uchar xdata Password_flsh2[6];
bit Modify=0;						   //这个标志位是修改密码用的
uchar Box_state[8];
uchar Surplus=0;
uchar admin[6];
uchar state=0;
uchar state_clear=0;
bit clear_flag=1;
sbit led0=P3^0;
sbit led1=P3^1;
sbit led2=P3^2;
sbit led3=P3^3;
sbit led4=P3^4;
sbit led5=P3^5;
sbit led6=P3^6;
sbit led7=P3^7;
uchar led0_time=0;
uchar led1_time=0;
uchar led2_time=0;
uchar led3_time=0;
uchar led4_time=0;
uchar led5_time=0;
uchar led6_time=0;
uchar led7_time=0;
void Uart1Data(uchar dat)		
{
	SBUF=dat;
	while(!TI);
	TI=0;	
}
void delay(unsigned int T)
 {
   while(T--);
 }
		  
void memory_Pass(uchar dat1,dat2,dat3,dat4,dat5,dat6,Num)	 
 {
   unsigned char tab[6];
   tab[0]=dat1;
   tab[1]=dat2;
   tab[2]=dat3;
   tab[3]=dat4;
   tab[4]=dat5;
   tab[5]=dat6;
   Write_dat_24C02(tab,Num*6,6);
 }
void read_Pass(Num)	                                     
{
	Read_dat_24C02(password_flsh,Num*6,6);
}
void memory_Box()	                                        
 {
   Write_dat_24C02(Box_state,100,8);
 }
void read_memory_Box()									 
 {			  
   Read_dat_24C02(Box_state,100,8);  
 }
void memory_admin()	                                       
 {
   Write_dat_24C02(admin,120,6);
 }
void read_memory_admin()									  
 {			  
   Read_dat_24C02(admin,120,6)
 }
void Time0_int()
 {
	TMOD = 0x01;		
	TL0 = 0x00;		
	TH0 = 0x4C;		
	TR0 = 1;		
	ET0	= 1;
 }

void Uart_int()
 {
	PCON &= 0x7F;		
	SCON = 0x50;		
	AUXR &= 0xBF;		
	AUXR &= 0xFE;		
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	TL1 = 0xFD;		
	TH1 = 0xFD;		
	ET1 = 0;		
	TR1 = 1;
 }
void key_back_dispose()
 {
   unsigned char Key_Flsh1=0,Key_Flsh2=0;
   P1=0x0F;
   delay(55);
   if(P1!=0x0F)
    {
	    if(key_flag) 
		 {
		   key_flag=0;
		   Key_Flsh1=P1;
		   P1=0xf0;
		   if(P1!=0xf0)	  //
			  {
				  Key_Flsh2=P1|Key_Flsh1;
				  switch(Key_Flsh2)
				   {
				     case 0xE7 : key_back=1;   break;
				     case 0xD7 : key_back=2;   break;
				     case 0xB7 : key_back=3;   break;
				     case 0x77 : key_back=12;  break;
		
				     case 0xEB : key_back=4;   break;
				     case 0xDB : key_back=5;   break;
				     case 0xBB : key_back=6;   break;
				     case 0x7B : key_back=13;  break;
		
				     case 0xED : key_back=7;   break;
				     case 0xDD : key_back=8;   break;
				     case 0xBD : key_back=9;   break;
				     case 0x7D : key_back=14;  break;
		
				     case 0xEE : key_back=10;  break;
				     case 0xDE : key_back=0;   break;
				     case 0xBE : key_back=11;  break;
				     case 0x7E : key_back=15;  break;	  
				   }
				   beep_time=1;
		             if(state!=0)system_time=10;
			 }
		 }
	}		
	else 
	 {
	   key_flag=1;
	 }
 }
void led_dispose()
 {
 	if(led0_time!=0) led0_time--;
	else led0=1;
 	if(led1_time!=0) led1_time--;
	else led1=1;
 	if(led2_time!=0) led2_time--;
	else led2=1;
 	if(led3_time!=0) led3_time--;
	else led3=1;
 	if(led4_time!=0) led4_time--;
	else led4=1;
 	if(led5_time!=0) led5_time--;  
	else led5=1;
 	if(led6_time!=0) led6_time--;
	else led6=1;
 	if(led7_time!=0) led7_time--;
	else led7=1;
 }

void main()
 {
	Time0_int();
//	Uart_int();
	EA=1;
    LCD_initialize();
    LCD_clear();   
	read_memory_Box();
	read_memory_admin();
   while(1) 
    { 	 

      key_back_dispose();
	  dispaly();
	  key_dispose();
	}
 }
void time0() interrupt 1
 {
   TH0=0x3C;
   TL0=0xb0;
   ms++;  
   led_dispose();
   if(beep_time!=0) 
    {
	  if(beep_time!=0) 
	   {
	   	 beep_time--;
		 beep=~beep;
	   }
	}else  beep=1;

   if(ms%10==0) s0=~s0;

   if(ms>=20) 
    {
	  ms=0;	  

	     if(system_time!=0) system_time--;
		  else 
		   {
		     if(state==15||state==14)  
			  {
			    system_time=10;	  state=8;
			  }
			 else	 state=0;
		   }	  
	}
 }
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
void LCD_initialize()
{
	_nop_();
	_nop_();
	LCD_W_code(0x3f,0);		
	LCD_W_code(0xc0,0);		
	LCD_W_code(0xb8,0);		
	LCD_W_code(0x40,0);		
	LCD_W_code(0x3f,1);
	LCD_W_code(0xc0,1);	
	LCD_W_code(0xb8,1);
	LCD_W_code(0x40,1);
}
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
void Start_24C02(void)
{
 	SDA_24C02=1;
 	SCL_24C02=1;
 	NOP_24C02();
 	SDA_24C02=0;
 	NOP_24C02();
}
void Stop_24C02(void)
{
 	SDA_24C02=0;
 	SCL_24C02=1;
 	NOP_24C02();
 	SDA_24C02=1;
 	NOP_24C02();
}
void Ack_24C02(void)
{
	SDA_24C02=0;
	NOP_24C02();
	SCL_24C02=1;
	NOP_24C02();
	SCL_24C02=0;
}
void NoAck_24C02(void)
{
 	SDA_24C02=1;
 	NOP_24C02();
 	SCL_24C02=1;
 	NOP_24C02();
 	SCL_24C02=0;
}
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
