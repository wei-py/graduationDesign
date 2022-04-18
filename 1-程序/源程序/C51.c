#include <STC89C5xRC.H>

#include <intrins.h>
#include "LCD12864_No_font_library.h"
#include "zi_ku.h"
#include "24C02.h"

uchar system_time=0;

bit s0=0;

uchar beep_time=0;				   //�������˿ڶ���
sbit beep=P0^5;					   //�������˿ڶ���
uchar key_back=16;				   //��������ֵ����

uchar ms=0;				   //��������ֵ����
bit key_flag=0;
uchar Box_number=0;

uchar xdata password[6]     ={0,0,0,0,0,0};  //�洢���������
uchar xdata password_flsh[6]={0,0,0,0,0,0};  //�洢���������
uchar password_count=0;			       //�洢����������������
uchar xdata Password_flsh2[6];			   //����洢���ǣ�Ҫ�޵����������ʱ���ٴ����������
bit Modify=0;						   //�����־λ���޸������õ�

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



void Uart1Data(uchar dat)		//�������ݷ���
{
	SBUF=dat;
	while(!TI);
	TI=0;	
}
void delay(unsigned int T)
 {
   while(T--);
 }

			  
void memory_Pass(uchar dat1,dat2,dat3,dat4,dat5,dat6,Num)	  //��������
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
void read_Pass(Num)	                                      //��ȡ����
 {
   Read_dat_24C02(password_flsh,Num*6,6);
 }


void memory_Box()	                                        //��������״̬
 {
   Write_dat_24C02(Box_state,100,8);
 }

void read_memory_Box()									   //������״̬
 {			  
   Read_dat_24C02(Box_state,100,8);
    
 }

void memory_admin()	                                        //��������״̬
 {
   Write_dat_24C02(admin,120,6);
 }

void read_memory_admin()									   //������״̬
 {			  
   Read_dat_24C02(admin,120,6);
    
 }



void Chinese_characters_8X16(unsigned char X_dat,unsigned char Y_dat,unsigned char Box_dat[]) 
 {
   unsigned char i;
   unsigned char dis_Box[16];
   for(i=0;i<16;i++) 
    {
	    dis_Box[i]=Box_dat[i];
	}
   LCD_display_byte(X_dat  ,Y_dat,dis_Box[0]); 
   LCD_display_byte(X_dat+1,Y_dat,dis_Box[1]); 
   LCD_display_byte(X_dat+2,Y_dat,dis_Box[2]); 
   LCD_display_byte(X_dat+3,Y_dat,dis_Box[3]); 
   LCD_display_byte(X_dat+4,Y_dat,dis_Box[4]); 
   LCD_display_byte(X_dat+5,Y_dat,dis_Box[5]); 
   LCD_display_byte(X_dat+6,Y_dat,dis_Box[6]); 
   LCD_display_byte(X_dat+7,Y_dat,dis_Box[7]); 

   LCD_display_byte(X_dat  ,Y_dat+1,dis_Box[8]); 
   LCD_display_byte(X_dat+1,Y_dat+1,dis_Box[9]); 
   LCD_display_byte(X_dat+2,Y_dat+1,dis_Box[10]); 
   LCD_display_byte(X_dat+3,Y_dat+1,dis_Box[11]); 
   LCD_display_byte(X_dat+4,Y_dat+1,dis_Box[12]); 
   LCD_display_byte(X_dat+5,Y_dat+1,dis_Box[13]); 
   LCD_display_byte(X_dat+6,Y_dat+1,dis_Box[14]); 
   LCD_display_byte(X_dat+7,Y_dat+1,dis_Box[15]); 

 }


void Chinese_characters_16X16(unsigned char characters_X,unsigned char characters_Y,unsigned char mu[])
 {
   unsigned char x=0,y=0;
   unsigned char characters_flsh[32];
   for(x=0;x<32;x++) 
    {
	  characters_flsh[x]= mu[x];
	}
   LCD_display_byte(characters_X,characters_Y,mu[0]); 
   LCD_display_byte(characters_X+1,characters_Y,mu[1]); 
   LCD_display_byte(characters_X+2,characters_Y,mu[2]); 
   LCD_display_byte(characters_X+3,characters_Y,mu[3]); 
   LCD_display_byte(characters_X+4,characters_Y,mu[4]); 
   LCD_display_byte(characters_X+5,characters_Y,mu[5]); 
   LCD_display_byte(characters_X+6,characters_Y,mu[6]); 
   LCD_display_byte(characters_X+7,characters_Y,mu[7]); 
   LCD_display_byte(characters_X+8,characters_Y,mu[8]); 
   LCD_display_byte(characters_X+9,characters_Y,mu[9]); 
   LCD_display_byte(characters_X+10,characters_Y,mu[10]); 
   LCD_display_byte(characters_X+11,characters_Y,mu[11]); 
   LCD_display_byte(characters_X+12,characters_Y,mu[12]); 
   LCD_display_byte(characters_X+13,characters_Y,mu[13]); 
   LCD_display_byte(characters_X+14,characters_Y,mu[14]); 
   LCD_display_byte(characters_X+15,characters_Y,mu[15]); 

   LCD_display_byte(characters_X,characters_Y+1,mu[16]); 
   LCD_display_byte(characters_X+1,characters_Y+1,mu[17]); 
   LCD_display_byte(characters_X+2,characters_Y+1,mu[18]); 
   LCD_display_byte(characters_X+3,characters_Y+1,mu[19]); 
   LCD_display_byte(characters_X+4,characters_Y+1,mu[20]); 
   LCD_display_byte(characters_X+5,characters_Y+1,mu[21]); 
   LCD_display_byte(characters_X+6,characters_Y+1,mu[22]); 
   LCD_display_byte(characters_X+7,characters_Y+1,mu[23]); 
   LCD_display_byte(characters_X+8,characters_Y+1,mu[24]); 
   LCD_display_byte(characters_X+9,characters_Y+1,mu[25]); 
   LCD_display_byte(characters_X+10,characters_Y+1,mu[26]); 
   LCD_display_byte(characters_X+11,characters_Y+1,mu[27]); 
   LCD_display_byte(characters_X+12,characters_Y+1,mu[28]); 
   LCD_display_byte(characters_X+13,characters_Y+1,mu[29]); 
   LCD_display_byte(characters_X+14,characters_Y+1,mu[30]); 
   LCD_display_byte(characters_X+15,characters_Y+1,mu[31]); 
 }




void dispaly()
 {

   if(state_clear!=state)
    {
	  state_clear=state;
	  LCD_clear();	password_count=0;
	} 
   if(state==0)		 //��������
    {
			password_count=0;

		   //��ʾ����״̬
		   if(Box_state[0]==0) Chinese_characters_16X16(0,0,num1);
		    else 			   Chinese_characters_16X16(0,0,numEnd);	 
		   if(Box_state[1]==0) Chinese_characters_16X16(0,2,num2);
		    else 			   Chinese_characters_16X16(0,2,numEnd);	 
		   if(Box_state[2]==0) Chinese_characters_16X16(0,4,num3);
		    else 			   Chinese_characters_16X16(0,4,numEnd);	 
		   if(Box_state[3]==0) Chinese_characters_16X16(0,6,num4);
		    else 			   Chinese_characters_16X16(0,6,numEnd);	 
		   if(Box_state[4]==0) Chinese_characters_16X16(112,0,num5);
		    else 			   Chinese_characters_16X16(112,0,numEnd);	 
		   if(Box_state[5]==0) Chinese_characters_16X16(112,2,num6);
		    else 			   Chinese_characters_16X16(112,2,numEnd);	 
		   if(Box_state[6]==0) Chinese_characters_16X16(112,4,num7);
		    else 			   Chinese_characters_16X16(112,4,numEnd);	 
		   if(Box_state[7]==0) Chinese_characters_16X16(112,6,num8);
		    else 			   Chinese_characters_16X16(112,6,numEnd);	 

		   //��ʾ��ӭ����
	       Chinese_characters_16X16(32,0,huan);
	       Chinese_characters_16X16(48,0,ying);
	       Chinese_characters_16X16(64,0,guang);
	       Chinese_characters_16X16(80,0,lin);
		   //��ʾʣ��
		   Surplus=8-(Box_state[0]+Box_state[1]+Box_state[2]+Box_state[3]+Box_state[4]+Box_state[5]+Box_state[6]+Box_state[7]);

		   if(Surplus!=0) 
		    {
		       Chinese_characters_16X16(32,2,sheng);
		       Chinese_characters_16X16(48,2,yu);
		       Chinese_characters_16X16(64,2,xiang);
			   Chinese_characters_8X16(80,2,Ascii_mao_hao);
			   switch(Surplus) 
			    {
				  case 1 :  Chinese_characters_8X16(88,2,Ascii_1);     break;
				  case 2 :  Chinese_characters_8X16(88,2,Ascii_2);     break;
				  case 3 :  Chinese_characters_8X16(88,2,Ascii_3);     break;
				  case 4 :  Chinese_characters_8X16(88,2,Ascii_4);     break;
				  case 5 :  Chinese_characters_8X16(88,2,Ascii_5);     break;
				  case 6 :  Chinese_characters_8X16(88,2,Ascii_6);     break;
				  case 7 :  Chinese_characters_8X16(88,2,Ascii_7);     break;
				  case 8 :  Chinese_characters_8X16(88,2,Ascii_8);     break;
				}

				   //��ʾ��ʾ��
			       Chinese_characters_16X16(24,4,cun);
			       Chinese_characters_16X16(40,4,wu);
			       Chinese_characters_16X16(56,4,qing3);
				   Chinese_characters_16X16(72,4,an);
				   Chinese_characters_16X16(88,4,cun);
			
			       Chinese_characters_16X16(24,6,qu);
			       Chinese_characters_16X16(40,6,wu);
			       Chinese_characters_16X16(56,6,qing3);
				   Chinese_characters_16X16(72,6,an); 
				   Chinese_characters_16X16(88,6,qu);
			}
			else 
			 {
		       Chinese_characters_16X16(32,2,ci);
		       Chinese_characters_16X16(48,2,gui);
		       Chinese_characters_16X16(64,2,yi);
		       Chinese_characters_16X16(80,2,man);
			 }


		   
	}
	else if(state==1)  //�������
	 {
	       Chinese_characters_16X16(8,0,qing3);
	       Chinese_characters_16X16(24,0,she);
	       Chinese_characters_16X16(40,0,zhi);
		   Chinese_characters_16X16(56,0,shu_zi_liu);
		   Chinese_characters_16X16(72,0,wei);
		   Chinese_characters_16X16(88,0,mi);
		   Chinese_characters_16X16(104,0,ma);		  ///��ʾ���������λ����

	       Chinese_characters_16X16(0,2,bing);
	       Chinese_characters_16X16(16,2,an);
	       Chinese_characters_16X16(32,2,xia);
		   Chinese_characters_16X16(48,2,que);
		   Chinese_characters_16X16(64,2,ren);
		   Chinese_characters_16X16(80,2,jian);
		   Chinese_characters_16X16(96,2,que);
		   Chinese_characters_16X16(112,2,ding);


	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			}   
		   Chinese_characters_16X16(16,6,mi);
		   Chinese_characters_16X16(32,6,ma);
 		   Chinese_characters_8X16(48,6,Ascii_mao_hao);


		   if(password_count>=1)  Chinese_characters_8X16(56,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(56,6,Ascii_kong);

		   if(password_count>=2)  Chinese_characters_8X16(64,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(64,6,Ascii_kong);
			
		   if(password_count>=3)  Chinese_characters_8X16(72,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(72,6,Ascii_kong);

		   if(password_count>=4)  Chinese_characters_8X16(80,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(80,6,Ascii_kong);
				
		   if(password_count>=5)  Chinese_characters_8X16(88,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(88,6,Ascii_kong);
				
		   if(password_count>=6)  Chinese_characters_8X16(96,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(96,6,Ascii_kong);
		

 
	 }
	else if(state==2)  //ȡ�����-�������
	 {
	       Chinese_characters_16X16(8,0,qing3);
	       Chinese_characters_16X16(24,0,shu);
	       Chinese_characters_16X16(40,0,ru);
		   Chinese_characters_16X16(56,0,qu);
		   Chinese_characters_16X16(72,0,wu);
		   Chinese_characters_16X16(88,0,xiang);
		   Chinese_characters_16X16(104,0,hao);

	       Chinese_characters_16X16(0,2,bing);
	       Chinese_characters_16X16(16,2,an);
	       Chinese_characters_16X16(32,2,xia);
		   Chinese_characters_16X16(48,2,que);
		   Chinese_characters_16X16(64,2,ren);
		   Chinese_characters_16X16(80,2,jian);
		   Chinese_characters_16X16(96,2,jixu_ji);
		   Chinese_characters_16X16(112,2,xu);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			} 
			
		   Chinese_characters_16X16(40,6,xiang);
		   Chinese_characters_16X16(56,6,hao);
 		   Chinese_characters_8X16(72,6,Ascii_mao_hao);
		   	  
 		   if(password_count==0) 
		    {
			   if(s0) 
			    {							  
				  Chinese_characters_8X16(80,6,Ascii_xia_hua_xian);
				}
				else 
				 {
				  Chinese_characters_8X16(80,6,Ascii_kong); 
				 }
			}
			else 
			 {
			  	  switch(Box_number%10) 
				    {
					  case 0 :  Chinese_characters_8X16(80,6,Ascii_0);     break; 
					  case 1 :  Chinese_characters_8X16(80,6,Ascii_1);     break;
					  case 2 :  Chinese_characters_8X16(80,6,Ascii_2);     break;
					  case 3 :  Chinese_characters_8X16(80,6,Ascii_3);     break;
					  case 4 :  Chinese_characters_8X16(80,6,Ascii_4);     break;
					  case 5 :  Chinese_characters_8X16(80,6,Ascii_5);     break;
					  case 6 :  Chinese_characters_8X16(80,6,Ascii_6);     break;
					  case 7 :  Chinese_characters_8X16(80,6,Ascii_7);     break;
					  case 8 :  Chinese_characters_8X16(80,6,Ascii_8);     break;
					  case 9 :  Chinese_characters_8X16(80,6,Ascii_9);     break;
					}
			 }
	 }
	else if(state==3)  //ȡ�����-��������
	 {
	       Chinese_characters_16X16(8,0,qing3);
	       Chinese_characters_16X16(24,0,shu);
	       Chinese_characters_16X16(40,0,ru);
		   Chinese_characters_16X16(56,0,qu);
		   Chinese_characters_16X16(72,0,wu);
		   Chinese_characters_16X16(88,0,mi);
		   Chinese_characters_16X16(104,0,ma);

	       Chinese_characters_16X16(0,2,bing);
	       Chinese_characters_16X16(16,2,an);
	       Chinese_characters_16X16(32,2,xia);
		   Chinese_characters_16X16(48,2,que);
		   Chinese_characters_16X16(64,2,ren);
		   Chinese_characters_16X16(80,2,jian);
		   Chinese_characters_16X16(96,2,que);
		   Chinese_characters_16X16(112,2,ding);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			}  


		   Chinese_characters_16X16(16,6,mi);
		   Chinese_characters_16X16(32,6,ma);
 		   Chinese_characters_8X16(48,6,Ascii_mao_hao);
			
		   if(password_count>=1)  Chinese_characters_8X16(56,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(56,6,Ascii_kong);

		   if(password_count>=2)  Chinese_characters_8X16(64,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(64,6,Ascii_kong);
			
		   if(password_count>=3)  Chinese_characters_8X16(72,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(72,6,Ascii_kong);

		   if(password_count>=4)  Chinese_characters_8X16(80,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(80,6,Ascii_kong);
				
		   if(password_count>=5)  Chinese_characters_8X16(88,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(88,6,Ascii_kong);
				
		   if(password_count>=6)  Chinese_characters_8X16(96,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(96,6,Ascii_kong);
	 }
	else if(state==4)  //����ɹ����棬����ɹ������XX �����μ�����
	 {
	       Chinese_characters_16X16(32,0,cun);
	       Chinese_characters_16X16(48,0,wu);
	       Chinese_characters_16X16(64,0,cheng);
		   Chinese_characters_16X16(80,0,gong);

	       Chinese_characters_16X16(16,2,qing3);
		   Chinese_characters_16X16(32,2,nin);
		   Chinese_characters_16X16(48,2,lao);
		   Chinese_characters_16X16(64,2,ji);
		   Chinese_characters_16X16(80,2,mi);
		   Chinese_characters_16X16(96,2,ma);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			} 

		   Chinese_characters_16X16(40,6,xiang);
		   Chinese_characters_16X16(56,6,hao);
 		   Chinese_characters_8X16(72,6,Ascii_mao_hao);
		  
	  	  switch(Box_number%10) 
		    {
			  case 0 :  Chinese_characters_8X16(80,6,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(80,6,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(80,6,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(80,6,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(80,6,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(80,6,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(80,6,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(80,6,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(80,6,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(80,6,Ascii_9);     break;
			} 
		   

	 }
	else if(state==5)  //ȡ�����-ȡ��ɹ�����  ȡ��ɹ��� ��ӭ�ٴι���
	 {
	       Chinese_characters_16X16(32,0,qu);
	       Chinese_characters_16X16(48,0,wu);
	       Chinese_characters_16X16(64,0,cheng);
		   Chinese_characters_16X16(80,0,gong);
 
	  	  switch(Box_number%10) 
		    {
			  case 0 :  Chinese_characters_8X16(24,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(24,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(24,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(24,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(24,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(24,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(24,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(24,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(24,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(24,2,Ascii_9);     break;
			} 
		   

		   Chinese_characters_16X16(32,2,xiang);
		   Chinese_characters_16X16(48,2,men);
		   Chinese_characters_16X16(64,2,yi);
		   Chinese_characters_16X16(80,2,kai);

		   Chinese_characters_16X16(16,6,huan);
		   Chinese_characters_16X16(32,6,ying);
		   Chinese_characters_16X16(48,6,zai);
		   Chinese_characters_16X16(64,6,xia_ci_ci);
		   Chinese_characters_16X16(80,6,guang);
		   Chinese_characters_16X16(96,6,lin);
	 }
	else if(state==6)  //���� ����
	 {
	       Chinese_characters_16X16(32,0,cun);
	       Chinese_characters_16X16(48,0,wu);
	       Chinese_characters_16X16(64,0,shi);
		   Chinese_characters_16X16(80,0,bai);
									         
	       Chinese_characters_8X16(24,2,Ascii_1);
		   Chinese_characters_16X16(32,2,xiang);
		   Chinese_characters_16X16(48,2,men);
		   Chinese_characters_16X16(64,2,yi);
		   Chinese_characters_16X16(80,2,kai);

		   Chinese_characters_16X16(16,6,huan);
		   Chinese_characters_16X16(32,6,ying);
		   Chinese_characters_16X16(48,6,zai);
		   Chinese_characters_16X16(64,6,xia_ci_ci);
		   Chinese_characters_16X16(80,6,guang);
		   Chinese_characters_16X16(96,6,lin);
	 }
	else if(state==7)  //����Ա��¼����
	 {
	       Chinese_characters_16X16(24,0,guan);
	       Chinese_characters_16X16(40,0,li);
	       Chinese_characters_16X16(56,0,yuan);
		   Chinese_characters_16X16(72,0,deng);
		   Chinese_characters_16X16(88,0,lu);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			} 

		   Chinese_characters_16X16(16,6,mi);
		   Chinese_characters_16X16(32,6,ma);
 		   Chinese_characters_8X16(48,6,Ascii_mao_hao);

		   if(password_count>=1)  Chinese_characters_8X16(56,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(56,6,Ascii_kong);

		   if(password_count>=2)  Chinese_characters_8X16(64,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(64,6,Ascii_kong);
			
		   if(password_count>=3)  Chinese_characters_8X16(72,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(72,6,Ascii_kong);

		   if(password_count>=4)  Chinese_characters_8X16(80,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(80,6,Ascii_kong);
				
		   if(password_count>=5)  Chinese_characters_8X16(88,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(88,6,Ascii_kong);
				
		   if(password_count>=6)  Chinese_characters_8X16(96,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(96,6,Ascii_kong); 
	 }
	else if(state==8)  //����Ա��¼����,��ͷָ���һ��ѡ�����Աȡ�
	 {
	       Chinese_characters_16X16(24,0,guan);
	       Chinese_characters_16X16(40,0,li);
	       Chinese_characters_16X16(56,0,yuan);
		   Chinese_characters_16X16(72,0,jie);
		   Chinese_characters_16X16(88,0,mian);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,2,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,2,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,2,Ascii_9);     break;
			} 


		   Chinese_characters_8X16(8,4,Ascii_1);
		   Chinese_characters_8X16(16,4,Ascii_mao_hao);
		   Chinese_characters_16X16(32,4,guan);
		   Chinese_characters_16X16(48,4,li);
		   Chinese_characters_16X16(64,4,yuan);
		   Chinese_characters_16X16(80,4,qu);
		   Chinese_characters_16X16(96,4,wu);
		   Chinese_characters_8X16(112,4,Ascii_zuo_jiantou);

		   Chinese_characters_8X16(8,6,Ascii_2);
		   Chinese_characters_8X16(16,6,Ascii_mao_hao);
		   Chinese_characters_16X16(32,6,geng);
		   Chinese_characters_16X16(48,6,gai);
		   Chinese_characters_16X16(64,6,mi);
		   Chinese_characters_16X16(80,6,ma);
	 }
	else if(state==9)  //����Ա����,��ͷָ���2��ѡ��������롱
	 {
	       Chinese_characters_16X16(24,0,guan);
	       Chinese_characters_16X16(40,0,li);
	       Chinese_characters_16X16(56,0,yuan);
		   Chinese_characters_16X16(72,0,jie);
		   Chinese_characters_16X16(88,0,mian);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,2,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,2,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,2,Ascii_9);     break;
			} 

		   Chinese_characters_8X16(8,4,Ascii_1);
		   Chinese_characters_8X16(16,4,Ascii_mao_hao);
		   Chinese_characters_16X16(32,4,guan);
		   Chinese_characters_16X16(48,4,li);
		   Chinese_characters_16X16(64,4,yuan);
		   Chinese_characters_16X16(80,4,qu);
		   Chinese_characters_16X16(96,4,wu);


		   Chinese_characters_8X16(8,6,Ascii_2);
		   Chinese_characters_8X16(16,6,Ascii_mao_hao);
		   Chinese_characters_16X16(32,6,geng);
		   Chinese_characters_16X16(48,6,gai);
		   Chinese_characters_16X16(64,6,mi);
		   Chinese_characters_16X16(80,6,ma);
		   Chinese_characters_8X16(112,6,Ascii_zuo_jiantou);
	 }
	 else if(state==10) 	 //����Աȡ�����
	  {
	       Chinese_characters_16X16(24,0,guan);
	       Chinese_characters_16X16(40,0,li);
	       Chinese_characters_16X16(56,0,yuan);
		   Chinese_characters_16X16(72,0,qu);
		   Chinese_characters_16X16(88,0,wu);

	       Chinese_characters_16X16(0,2,an);
	       Chinese_characters_16X16(16,2,xia);
	       Chinese_characters_16X16(32,2,dui);
		   Chinese_characters_16X16(48,2,ying4);

		   Chinese_characters_16X16(64,2,xiang);
		   Chinese_characters_16X16(80,2,hao);
		   Chinese_characters_16X16(96,2,kai);
		   Chinese_characters_16X16(112,2,xiang);


	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			}

		   if(Box_state[0]==0) Chinese_characters_16X16(0,6,num1);
		    else 			   Chinese_characters_16X16(0,6,numEnd);	 
		   if(Box_state[1]==0) Chinese_characters_16X16(16,6,num2);
		    else 			   Chinese_characters_16X16(16,6,numEnd);	 
		   if(Box_state[2]==0) Chinese_characters_16X16(32,6,num3);
		    else 			   Chinese_characters_16X16(32,6,numEnd);	 
		   if(Box_state[3]==0) Chinese_characters_16X16(48,6,num4);
		    else 			   Chinese_characters_16X16(48,6,numEnd);	 
		   if(Box_state[4]==0) Chinese_characters_16X16(64,6,num5);
		    else 			   Chinese_characters_16X16(64,6,numEnd);	 
		   if(Box_state[5]==0) Chinese_characters_16X16(80,6,num6);
		    else 			   Chinese_characters_16X16(80,6,numEnd);	 
		   if(Box_state[6]==0) Chinese_characters_16X16(96,6,num7);
		    else 			   Chinese_characters_16X16(96,6,numEnd);	 
		   if(Box_state[7]==0) Chinese_characters_16X16(112,6,num8);
		    else 			   Chinese_characters_16X16(112,6,numEnd);	 	 

	  }
	 else if(state==11) 	 //����Աȡ�����
	  {
	       Chinese_characters_16X16(16,0,geng);
	       Chinese_characters_16X16(32,0,gai);
	       Chinese_characters_16X16(48,0,guan);
	       Chinese_characters_16X16(64,0,li);
	       Chinese_characters_16X16(80,0,mi);
		   Chinese_characters_16X16(96,0,ma);
	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,2,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,2,Ascii_9);     break;
			}   			  
	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,2,Ascii_9);     break;
			}

	       Chinese_characters_16X16(0,4,shu);
	       Chinese_characters_16X16(16,4,ru);
	       Chinese_characters_16X16(32,4,mi);
	       Chinese_characters_16X16(48,4,ma);
		   Chinese_characters_8X16(64,4,Ascii_mao_hao);

		   if(password_count>=1)  Chinese_characters_8X16(72,4,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(72,4,Ascii_kong);

		   if(password_count>=2)  Chinese_characters_8X16(80,4,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(80,4,Ascii_kong);
			
		   if(password_count>=3)  Chinese_characters_8X16(88,4,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(88,4,Ascii_kong);

		   if(password_count>=4)  Chinese_characters_8X16(96,4,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(96,4,Ascii_kong);
				
		   if(password_count>=5)  Chinese_characters_8X16(104,4,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(104,4,Ascii_kong);
				
		   if(password_count>=6)  Chinese_characters_8X16(112,4,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(112,4,Ascii_kong);

	       Chinese_characters_16X16(0,6,zai);
	       Chinese_characters_16X16(16,6,ci);
	       Chinese_characters_16X16(32,6,shu);
	       Chinese_characters_16X16(48,6,ru);
		   Chinese_characters_8X16(64,6,Ascii_mao_hao);


		   if(password_count>=7)  Chinese_characters_8X16(72,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(72,6,Ascii_kong);

		   if(password_count>=8)  Chinese_characters_8X16(80,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(80,6,Ascii_kong);
			
		   if(password_count>=9)  Chinese_characters_8X16(88,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(88,6,Ascii_kong);

		   if(password_count>=10)  Chinese_characters_8X16(96,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(96,6,Ascii_kong);
				
		   if(password_count>=11)  Chinese_characters_8X16(104,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(104,6,Ascii_kong);
				
		   if(password_count>=12)  Chinese_characters_8X16(112,6,Ascii_xing_hao);
		   else 				  Chinese_characters_8X16(112,6,Ascii_kong);


	  }
	  else if(state==12)	  //��ʾ���棬�������ţ�û�д������
	   {
	       Chinese_characters_16X16(32,0,ti);
	       Chinese_characters_16X16(48,0,ti_shi_shi);
	       Chinese_characters_16X16(64,0,jie);
	       Chinese_characters_16X16(80,0,mian);
					  

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			} 

	       Chinese_characters_16X16(16,6,ci);
	       Chinese_characters_16X16(32,6,xiang);
	       Chinese_characters_16X16(48,6,mei);
	       Chinese_characters_16X16(64,6,you);
	       Chinese_characters_16X16(80,6,cun);
	       Chinese_characters_16X16(96,6,wu);
	   }

	  else if(state==13)	  //��ʾ���棬ȡ��ʧ�ܣ��������
	   {
	       Chinese_characters_16X16(32,0,qu);
	       Chinese_characters_16X16(48,0,wu);
	       Chinese_characters_16X16(64,0,shi);
	       Chinese_characters_16X16(80,0,bai);
					  


	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,2,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,2,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,2,Ascii_9);     break;
			} 
																														 	
	       Chinese_characters_16X16(32,4,mi);
	       Chinese_characters_16X16(48,4,ma);
	       Chinese_characters_16X16(64,4,cuo_wu_cuo);
	       Chinese_characters_16X16(80,4,cuo_wu_wu);
           Chinese_characters_16X16(96,4,dou_hao);
	       Chinese_characters_16X16(112,4,yi_wang_yi);


	       Chinese_characters_16X16(0,6,yi_wang_wang);
	       Chinese_characters_16X16(16,6,mi);
	       Chinese_characters_16X16(32,6,ma);
	       Chinese_characters_16X16(48,6,lian);
	       Chinese_characters_16X16(64,6,xi);
	       Chinese_characters_16X16(80,6,guan);
	       Chinese_characters_16X16(96,6,li);
	       Chinese_characters_16X16(112,6,yuan);
	   }
	 else if(state==14) 	 //����Ա��������ɹ�����	  ying
	  {
	       Chinese_characters_16X16(16,0,geng);
	       Chinese_characters_16X16(32,0,gai);
	       Chinese_characters_16X16(48,0,guan);
	       Chinese_characters_16X16(64,0,li);
	       Chinese_characters_16X16(80,0,mi);
		   Chinese_characters_16X16(96,0,ma);
	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,2,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,2,Ascii_9);     break;
			}   			  
	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,2,Ascii_9);     break;
			}

	       Chinese_characters_16X16(32,6,geng);
	       Chinese_characters_16X16(48,6,gai);
	       Chinese_characters_16X16(64,6,cheng);
	       Chinese_characters_16X16(80,6,gong);


	  }
	 else if(state==15) 	 //����Ա��������ʧ�ܽ���
	  {
	       Chinese_characters_16X16(16,0,geng);
	       Chinese_characters_16X16(32,0,gai);
	       Chinese_characters_16X16(48,0,guan);
	       Chinese_characters_16X16(64,0,li);
	       Chinese_characters_16X16(80,0,mi);
		   Chinese_characters_16X16(96,0,ma);
	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,2,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,2,Ascii_9);     break;
			}   			  
	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,2,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,2,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,2,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,2,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,2,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,2,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,2,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,2,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,2,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,2,Ascii_9);     break;
			}

	       Chinese_characters_16X16(32,6,geng);
	       Chinese_characters_16X16(48,6,gai);
	       Chinese_characters_16X16(64,6,shi);
	       Chinese_characters_16X16(80,6,bai);
	  }
	else if(state==16)  //����Ա��¼����
	 {
	       Chinese_characters_16X16(24,0,guan);
	       Chinese_characters_16X16(40,0,li);
	       Chinese_characters_16X16(56,0,yuan);
		   Chinese_characters_16X16(72,0,deng);
		   Chinese_characters_16X16(88,0,lu);

	  	  switch(system_time/10%10) 
		    {
			  case 0 :  Chinese_characters_8X16(56,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(56,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(56,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(56,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(56,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(56,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(56,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(56,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(56,4,Ascii_8);     break;
 			  case 9 :  Chinese_characters_8X16(56,4,Ascii_9);     break;
			}   			  

	  	  switch(system_time%10) 
		    {
			  case 0 :  Chinese_characters_8X16(64,4,Ascii_0);     break; 
			  case 1 :  Chinese_characters_8X16(64,4,Ascii_1);     break;
			  case 2 :  Chinese_characters_8X16(64,4,Ascii_2);     break;
			  case 3 :  Chinese_characters_8X16(64,4,Ascii_3);     break;
			  case 4 :  Chinese_characters_8X16(64,4,Ascii_4);     break;
			  case 5 :  Chinese_characters_8X16(64,4,Ascii_5);     break;
			  case 6 :  Chinese_characters_8X16(64,4,Ascii_6);     break;
			  case 7 :  Chinese_characters_8X16(64,4,Ascii_7);     break;
			  case 8 :  Chinese_characters_8X16(64,4,Ascii_8);     break;
			  case 9 :  Chinese_characters_8X16(64,4,Ascii_9);     break;
			} 

	       Chinese_characters_16X16(24,6,mi);
	       Chinese_characters_16X16(40,6,ma);
	       Chinese_characters_16X16(56,6,cuo_wu_cuo);
		   Chinese_characters_16X16(72,6,cuo_wu_wu);
	 }



 }

void Time0_int()
 {

	TMOD = 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x4C;		//���ö�ʱ��ֵ
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0	= 1;
 }

void Uart_int()
 {
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
 }



/*
   4*4������̴�������
���ڵ�ǰ������Ӳ����˵�ļ�ֵ��
      1��0xE7   2��0xD7   3��0xB7  ��  ��0x77
	  4��0xEB   5��0xDB	6��0xBB	ȡ  ��0x7B
	  7��0xED   8��0xDD	9��0xBD	������0x7D
	  1��0xEE   1��0xDE	1��0xBE	ѡ���0x7E
*/
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
		//		   while(P1!=0x0F)	  //������ѭ���ͷ�
		//		    {
		//			  P1=0x0f;		  //�ȸ�ֵ����ֵ֮�����ʱ�ȶ�һ�����ݣ�Ȼ�����ж�����
		//			  delay(333);
		//			};
		             if(state!=0)system_time=10;
			 }
		 }
	}		
	else 
	 {
	   key_flag=1;
	 }
 }

void key_dispose()
 {
   if(key_back!=16) 
    {
	       if(state==0) //���˵�Ǵ�������  ,ֻ�д�ȡ�����͹����������
		    {
			   if(key_back==12) 		  //�水������
			    {
				  key_back=16;			  //�������ֵ
				  system_time=10;
				  state=1;
				  password_count=0;
				}
			   else  if(key_back==13) 	  //ȡ��������
				{
				  key_back=16;			  //�������ֵ
				  system_time=10;
				  state=2;
				}
			   else if(key_back==14) 	 //������������
				{
				  key_back=16;			 //�������ֵ
				  system_time=10;
				  state=7;
				}			 
			}
		   else if(state==1) //��ת��������棬��������ֻ��0-9��ɾ��/�˳�  ȷ�� ��������
		    {
				  if(key_back>=0&&key_back<=9)	   //��������0-9��˵������������
				   {
				     if(password_count<6) 		   //�ж���������λ����������λ
					  {
					    password[password_count]=key_back;
						password_count++;
					  }
					  else 
					   {
					     beep_time=4;
					   }
	                 key_back=16;			       //�������ֵ
				   }
				  else if(key_back==10) 		   //�˸񰴼����£�ֻҪ���벻Ϊ�գ�����һλ
				   { 
				     key_back=16;			       //�������ֵ
				     if(password_count>0) password_count--;
	
				   }
				  else if(key_back==11) 		   //ȷ�ϰ�������
				   { key_back=16;			       //�������ֵ
				     
					if(password_count==6) 
					   {
							 if(Box_state[0]==0) 
							  {	 Box_state[0]=1;
							     memory_Box();	   Box_number=1;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number); 
								 led0_time=40;  led0=0; 
							  }
							  else if(Box_state[1]==0) 
							   { Box_state[1]=1;
							     memory_Box();	   Box_number=2;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number); 
								 led1_time=40;  led1=0; 
							   }
							  else if(Box_state[2]==0) 
							   { Box_state[2]=1;
							     memory_Box();	   Box_number=3;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number);
								 led2_time=40;  led2=0;  
							   }
							  else if(Box_state[3]==0) 
							   {Box_state[3]=1;				
							     memory_Box();	   Box_number=4;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number);
								 led3_time=40;  led3=0; 
							   }
							  else if(Box_state[4]==0) 
							   { Box_state[4]=1;
							     memory_Box();	  Box_number=5;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number);
								 led4_time=40;  led4=0; 
							   }
							  else if(Box_state[5]==0) 
							   { Box_state[5]=1;
							     memory_Box();	  Box_number=6;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number); 
								 led5_time=40;  led5=0; 
							   }
							  else if(Box_state[6]==0) 
							   { Box_state[6]=1;
							     memory_Box();	  Box_number=7;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number); 
								 led6_time=40;  led6=0; 
							   }
							  else if(Box_state[7]==0) 
							   { Box_state[7]=1;
							     memory_Box();	 Box_number=8;
								 memory_Pass(password[0],password[1],password[2],password[3],password[4],password[5],Box_number); 
								 led7_time=40;  led7=0; 
							   }
							   system_time=3;
							   state=4;
					  }
					  else 
					   {
					      beep_time=4;
					   }
				   }
				  else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }
			}
		   else if(state==2) //��ת��ȡ����棬��������ֻ��0-9��ɾ��/�˳� ��������	������ȡ�����ѡ�������ݴ�������  
		    {
				  if(key_back>=0&&key_back<=9)	   //��������0-9��˵�������������Ӻ�
				   {
				     if(password_count<=1) 		   //�ж���������λ��������һλ
					  {
					    Box_number=key_back;
						if(password_count!=1) password_count++;
					  }
					  else 
					   {
					     beep_time=4;
					   }
	                 key_back=16;			       //�������ֵ
				   }
				  else if(key_back==10) 		   //�˸񰴼����£�ֻҪ���벻Ϊ�գ�����һλ
				   { 
				     key_back=16;			       //�������ֵ
				     if(password_count>0) password_count--;
				   }
				 else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }
				  else if(key_back==11) 		   //ȷ�ϰ�������
				   { key_back=16;			       //�������ֵ
					  if(password_count==1&&Box_number!=0&&Box_number!=9)  //���ж��Ƿ�����ȷ���������
						 {

							 if(Box_state[Box_number-1]==1)	//ȷ��һ��������������ж���
							  {
								 state=3;	
								 password_count=0;    
							  }
							  else							//����Ƿȱһ�����棬��ʾ������ԭ���ǿյĽ��洦��
							   {
							     beep_time=4;  system_time=1; state=12;
							   }
						 }
					  else  //���ﻹ��������һ�����棬��ʾ������д�����벻��ȷ�Ľ���
						 {
						    beep_time=10;
						 }
				   }	    
			}
		   else if(state==3)
		    {
				  if(key_back>=0&&key_back<=9)	   //��������0-9��˵������������
				   {
				     if(password_count<6) 		   //�ж���������λ����������λ
					  {
					    password[password_count]=key_back;
						password_count++;
					  }
					  else 
					   {
					     beep_time=4;
					   }
	                 key_back=16;			       //�������ֵ
				   }
				  else if(key_back==10) 		   //�˸񰴼����£�ֻҪ���벻Ϊ�գ�����һλ
				   { 
				     key_back=16;			       //�������ֵ
				     if(password_count>0) password_count--;
	
				   }
				  else if(key_back==11) 		   //ȷ�ϰ�������
				   { key_back=16;			       //�������ֵ
				     
					if(password_count==6) 
					   {
						  read_Pass(Box_number);

						  if(password_flsh[0]==password[0]&&password_flsh[1]==password[1]&&password_flsh[2]==password[2]&&password_flsh[3]==password[3]&&password_flsh[4]==password[4]&&password_flsh[5]==password[5])
						   {
						   	  memory_Pass(0,0,0,0,0,0,Box_number);   //����ȷ����ȷ���������
							  Box_state[Box_number-1]=0;
							  state=5;
							  system_time=1;	
							  memory_Box();
							  switch(Box_number)
							   {
							   	  case 1 :  led0_time=40;  led0=0;    break;
							   	  case 2 :  led1_time=40;  led1=0;    break;
							   	  case 3 :  led2_time=40;  led2=0;    break;
							   	  case 4 :  led3_time=40;  led3=0;    break;
							   	  case 5 :  led4_time=40;  led4=0;    break;
							   	  case 6 :  led5_time=40;  led5=0;    break;
							   	  case 7 :  led6_time=40;  led6=0;    break;							   
							   	  case 8 :  led7_time=40;  led7=0;    break;							   
							   }

						   }  
						   else 
						    {
							   state=13; system_time=2;
							} 	 
					   }
					  else 
					   {
					      beep_time=4;
					   }
				   }
				  else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }
			}
			else if(state==4||state==15||state==14||state==16) 
			 {
			   if(key_back!=16)
			    {
				  if(state==15||state==14) 
				   {
				   	  state=8;	 
				   }
				   else 
				    {
					  state=0; 
					}
				
				  key_back=16;
				
				} 

			 }
		   else if(state==7) //��ת����������, ��������ֻ��0-9��ɾ��/�˳� ����ѡ�������
		    {
			
				  if(key_back>=0&&key_back<=9)	   //��������0-9��˵������������
				   {
				     if(password_count<6) 		   //�ж���������λ����������λ
					  {
					    password[password_count]=key_back;
						password_count++;
					  }
					  else 
					   {
					     beep_time=4;
					   }
	                 key_back=16;			       //�������ֵ
				   }
				  else if(key_back==10) 		   //�˸񰴼����£�ֻҪ���벻Ϊ�գ�����һλ
				   { 
				     key_back=16;			       //�������ֵ
				     if(password_count>0) password_count--;
	
				   }
				  else if(key_back==11) 		   //ȷ�ϰ�������
				   { key_back=16;			       //�������ֵ
				     
					if(password_count==6) 
					   {
						  if((password[0]==1&&password[1]==3&&password[2]==1&&password[3]==4&&password[4]==2&&password[5]==0)||(password[0]==admin[0]&&password[1]==admin[1]&&password[2]==admin[2]&&password[3]==admin[3]&&password[4]==admin[4]&&password[5]==admin[5])) 
						   {
						     password_count=0;
							 state=8;
						   }
						   else 
						    {
							  state=16; system_time=2;
							}
					   }
				   }
				  else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }


			}
            else if(state==8||state==9)
			 {
                 if(key_back==1) 		  	   //ѡ�񰴼���ѡ���һ���Ӳ˵�
				   { 
					  state=8;
					  key_back=16;		    
				   }
                  else if(key_back==2) 		  //ѡ�񰴼���ѡ��ڶ����Ӳ˵�
				   { 
					  state=9;
					  key_back=16;		    
				   }
				  else if(key_back==11) 	  //ȷ�ϰ�������
				   {  key_back=16;			 
				      if(state==8) 			 //������ڵ�һ���Ӳ˵�������ת����ָ������Ľ���
					   {
					       state=10;
					   }
					   else 
					    {
						   state=11;	Modify=0;
						}

				   }
				  else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }
			 }
		   else if(state==10) 
		    {
				  if(key_back>=1&&key_back<=8)
				   {	
				        Box_number=key_back;
						memory_Pass(0,0,0,0,0,0,Box_number);   //����ȷ����ȷ���������
						Box_state[Box_number-1]=0;
						memory_Box();
						switch(Box_number)
						{
						  case 1 :  led0_time=40;  led0=0;    break;
						  case 2 :  led1_time=40;  led1=0;    break;
						  case 3 :  led2_time=40;  led2=0;    break;
						  case 4 :  led3_time=40;  led3=0;    break;
						  case 5 :  led4_time=40;  led4=0;    break;
						  case 6 :  led5_time=40;  led5=0;    break;
						  case 7 :  led6_time=40;  led6=0;    break;							   
						  case 8 :  led7_time=40;  led7=0;    break;							   
						} 
						key_back=16;	  
				   }
				  else if(key_back==11) 	  //ȷ�ϰ�������
				   {  key_back=16;			 
					  state=8;
				   }
				  else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }
				   else  key_back=16;
			}
		   else if(state==11) 
		    {
                  if(key_back>=0&&key_back<=9)	   //��������0-9��˵�������������Ӻ�
				   {
				     if(Modify==0)				   //�޸����ݱ�־λΪ0��˵��������дҪ�޸ĵ�����
					  {
					    if(password_count<6) 	   //����Լ�¼��һ������������¼
						 {
						   password[password_count]=key_back;
						   password_count++;
						 }
					  }
					  else						   //����Լ�¼�ڶ�������������¼
					   {
						   if(password_count>=6&&password_count<12) 
							 {
							   Password_flsh2[password_count-6]=key_back;
							   password_count++;
							 }
					   }
	                 key_back=16;			       //�������ֵ
				   }
				  else if(key_back==10) 		   //�˸񰴼����£�ֻҪ���벻Ϊ�գ�����һλ
				   { 
				     key_back=16;			       //�������ֵ
				     if(password_count>0)   password_count--;
					 if(password_count<=5)  Modify=0;
				   }
				 else if(key_back==15) 		   //�ص������水������
				   { key_back=16;			       //�������ֵ
				     password_count=0;			   //��������Ҳ����
					 state=0;					   //�ص����������
				   }
				  else if(key_back==11) 		   //ȷ�ϰ�������
				   {
				      key_back=16;			       //�������ֵ
					  if(password_count==6) 
					   {
					       Modify=1;
					   }
					   if(password_count==12)
					    {
							if(password[0]==Password_flsh2[0]&&password[1]==Password_flsh2[1]&&password[2]==Password_flsh2[2]&&password[3]==Password_flsh2[3]&&password[4]==Password_flsh2[4]&&password[5]==Password_flsh2[5])
							 {	   	 
								 admin[0]=password[0];
								 admin[1]=password[1];
								 admin[2]=password[2];
								 admin[3]=password[3];
								 admin[4]=password[4];
								 admin[5]=password[5];
								 memory_admin();
								 state=14; system_time=2;		 
							 }
							 else 
							  {
							    state=15; system_time=2;	
							  }
						} 
				   }	    
			}


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

//void uart() interrupt 4 
// {
//   if(RI) 
//    {
//	  RI=0;
//	}
// }

