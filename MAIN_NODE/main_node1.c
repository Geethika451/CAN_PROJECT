#include<LPC21XX.h>
#include "lcd_defines.h"
#include "can_temp.c"
#include "can.h"
#include"can_defines.h"
#include "uitrasonic.c"
#include "external_int.c"
#include "delay.h"
unsigned char timeof(void);
struct CAN_Frame txFrame;
struct CAN_Frame rxFrame;
extern u32 indL;
extern u32 indR;
extern u32 mode1;
extern u32 res;
extern u32 res1;
u8 status;
u8 cgramL[8]={0x00,0x04,0x0C,0x1F,0x1F,0x0C,0x04,0x00};
u8 cgramR[8]={0x00,0x04,0x06,0x1F,0x1F,0x06,0x04,0x00};
int main()
{
s32 temp;
u8 tp,tpd;
IODIR0|=1<<LED;
IOPIN0=1<<LED;
InitLcd();
Init_CAN1();
INIT_Ultrasonic();
cmdLcd(0x01);
cmdLcd(0x80);
strLcd("temperature:");
//delay_ms(1000);
cmdLcd(0xC0);
strLcd("Indicator:L");
cmdLcd(0x40);
BuildCGRAM(cgramL,8);
cmdLcd(0xCB);
CharLcd(0);
cmdLcd(0xC0+12);
strLcd(" ");
strLcd("R");
cmdLcd(0x48);
BuildCGRAM(cgramR,8);
cmdLcd(0XCE);
CharLcd(1);
cmdLcd(0x94);
strLcd("mode:forward");
interrupt();
while(1)
{
status=timeof();
if(status==0)
{
cmdLcd(0x01);
cmdLcd(0x80);
strLcd("sensor fail");
return 0;
}
temp=ReadTemp();  //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL

		tp  = temp>>4;	  //GETTING INTEGER PART
		tpd=temp & 0x08? 0x35:0x30;//GETTING FRACTIONAL PART
		cmdLcd(0x80+12);

 		//strLcd("Temp =");

		u32Lcd(tp);

		CharLcd('.');

		CharLcd(tpd);
		CharLcd(0xDF);
		strLcd("C");
		if(indL)
		{
		while(1)
		{
		status=timeof();
		if(status==0)
		{
		cmdLcd(0x01);
        cmdLcd(0x80);
        strLcd("sensor fail");
        return 0;
		}
		if((res==1)||(indR==1))
		{
		cmdLcd(0xCB);
		CharLcd(0);
		break;
		}
		txFrame.Data1='L';
        txFrame.vbf.DLC=1;
        txFrame.ID=IND_ID;   txFrame.vbf.RTR=0;
        CAN1_Tx(txFrame);
		 cmdLcd(0xCB);
         CharLcd(0);
	     delay_ms(150);
		 cmdLcd(0xCB);
	    CharLcd(' ');
		delay_ms(50);
        cmdLcd(0xCB);
		}
		}
		if(indR)
		{
		while(1)
		{
		status=timeof();
		if(status==0)
		{
		cmdLcd(0x01);
        cmdLcd(0x80);
        strLcd("sensor fail");
        return 0;
		}
		if((res1==1)||(indL==1))
		{
		cmdLcd(0xCE);
		CharLcd(1);
		break;
		}
		txFrame.Data1='R';
        txFrame.vbf.DLC=1;
        txFrame.ID=IND_ID;   txFrame.vbf.RTR=0;
        CAN1_Tx(txFrame);
		cmdLcd(0xCE);
        CharLcd(1);
		delay_ms(150);
		cmdLcd(0xCE);
		CharLcd(' ');
		delay_ms(50);
		cmdLcd(0xCE);
		}
		}
		if(mode1==0)
		{
        cmdLcd(0x94+5);
        strLcd("forward");
        cmdLcd(0xD4);
        strLcd("              ");
		cmdLcd(0x94+13);
		 }
		if(mode1==1)
		  {
          cmdLcd(0x94);
          strLcd("mode:");
          strLcd("reverse:");
       while(1)
      {
	  status=timeof();
     if(status==0)
		{
		cmdLcd(0x01);
        cmdLcd(0x80);
        strLcd("sensor fail");
        return 0;
		}
  if(mode1==0)
  break;
CAN1_Rx(&rxFrame);
if(rxFrame.ID==MAIN_ID)
{
if(rxFrame.Data1>=20)
{
//cmdLcd(0x01);
cmdLcd(0xD4);
strLcd("                    ");
cmdLcd(0xD4);
strLcd("distance high:");
u32Lcd(rxFrame.Data1);
}
else if(rxFrame.Data1<=20)
{
cmdLcd(0xD4);
strLcd("                   ");
cmdLcd(0xD4);
strLcd("distance low:");
u32Lcd(rxFrame.Data1);
IOCLR0=1<<LED;
delay_ms(150);
IOSET0=1<<LED;
cmdLcd(0xD4);
strLcd("                ");
  }
   }
}
		  }
		}
		}


