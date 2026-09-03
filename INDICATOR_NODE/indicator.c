#include<lpc21xx.h>
#include"types.h"
#include "lcd_defines.h"
#include "can.h"
#include "can_defines.h"
#include "delay.h"
#include "interrupt.h"

struct CAN_Frame rxFrame;

int main()
{
s32 i;
//InitLcd();
Init_CAN1();
IODIR0|=255<<0;
IOSET0=255<<0;
while(1)
{
   CAN1_Rx(&rxFrame);
	 if(rxFrame.ID==IND_ID)
	 {
  if(rxFrame.Data1=='L')

  {
  for(i=7;i>=0;i--)
  {
  IOCLR0=1<<i;
   delay_ms(150);
   IOSET0=1<<i;
  }
  }
  else if(rxFrame.Data1=='R')
  {	
 for(i=0;i<8;i++)
 {
  IOCLR0=1<<i;
  delay_ms(150);
  IOSET0=1<<i;
  }
  }
  }
  }
  }