#include<reg51.h>
char display[100];	
sbit Rs1=P3^2;
sbit Rw1=P3^3;
sbit En1=P3^4;
void delay(unsigned int time)
{
int i,j;
for(i=0;i<time;i++)
for(j=0;j<1275;j++);
}
void cmd(unsigned char cm)
{
P2=cm;
Rs1=0;   //command mode
Rw1=0;
En1=1;
delay(1);
En1=0;
}
void lcd_data(unsigned char dat)
{
P2=dat;
Rs1=1;   //data mode
Rw1=0;
En1=1;
delay(1);
En1=0;
}
void lcd_init()
{
cmd(0x38);    //select 8 bit 2 line
cmd(0x0e);    //lcd on cursor on
cmd(0x01);    //clear lcd
cmd(0x80);    //et cursor on first position
}
void lcd_print(unsigned char *c)     //to print string with c pointer
{
while(*c!=0)       //till c ptr is not equal to zero
{
lcd_data(*c++);   //put on lcd data and ptr moves to next bit
}
}
void serial_int()
{
TMOD=0x20;
SCON=0x50;
TH1=0xFD;
TR1=1;
}
void tx(unsigned char dat)
{
SBUF=dat;
while(TI==0);
TI=0;
}
void send(unsigned char *c)
{
while(*c!=0)
{
tx(*c++);
}
}
unsigned char rx()
{
while(RI==0);
RI=0;
return SBUF;
}
void main()
{
int i,k,m,j;	
lcd_init();
serial_int();
cmd(0x01);
cmd(0x80);
lcd_print("Wireless Notice");
delay(100);
cmd(0xC0);
lcd_print(".....Board......");
delay(100);
 while(1)
{
   k=0;
   while(rx()!='*');		
  for(i=0;i<100;i++)
{
    display[i]=rx();	
    if(display[i]=='#'||display[i]=='*')
 {
       k=i;
      m=i;
      i=101;
 }
    
 }	
	
cmd(0x01);
cmd(0x80);
if(k<16)
{
for(i=0;i<k;i++)
lcd_data(display[i]);
delay(100);
}

else if(k>15&&k<32)
{
for(i=0;i<16;i++)
lcd_data(display[i]);
delay(100);
cmd(0xC0);
for(i=16;i<k;i++)
lcd_data(display[i]);
delay(100);
}

else if(k>31)
{
for(i=0;i<k;i++)
{
cmd(0x80);
for(j=0;j<16;j++)
{
if((i+j)<=k)
{
lcd_data(display[i+j]);
}
else
{
j=17;
i=k+1;
}
}
cmd(0xC0);
for(j=16;j<32;j++)
{
or(j=16;j<32;j++)
{
lcd_data(display[i+j]);
}
else
{
j=45;
i=k+1;
}
}
delay(50)
}
}
}
}
