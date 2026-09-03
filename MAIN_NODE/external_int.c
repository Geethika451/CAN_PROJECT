#include<lpc21xx.h>
#include"types.h"
//#include"delay.h"
#include "can.h"
#include "can_defines.h"
#include "lcd_defines.h"
#include "interrupt.h"
//#include"uitrasonic.c"

#define eint0_pin 0x0000000C
#define eint0_vic_chn0 14
//#define eint0_status_pin  0

#define eint1_pin 0x000000C0
#define eint1_vic_chn0 15
//#define eint1_status_pin 0

#define eint2_pin 0x0000C000
#define eint2_vic_chn0 16
#define LED 0
//#define eint2_status_pin 0
struct CAN_Frame txFrame;
struct CAN_Frame rxFrame;
volatile static int flag=0;
volatile static int val=0;
volatile static int val1=0;
u32 indL=0;
u32 indR=0;
u32 mode1=0;
u32 res=0;
u32 res1=0;
void interrupt(void)
{
 PINSEL0&=(((u32)~3<<14)|((u32)~3<<6)|((u32)~3<<2)); 
 PINSEL0|=  eint0_pin|eint1_pin | eint2_pin;
 VICIntEnable=1<< eint0_vic_chn0|1<<eint1_vic_chn0|1<<eint2_vic_chn0;
 VICVectCntl0=(1<<5)|eint0_vic_chn0;
 VICVectAddr0=(u32)eint0_isr;
 VICVectCntl1=(1<<5)|eint1_vic_chn0;
 VICVectAddr1=(u32)eint1_isr;
 VICVectCntl2=(1<<5)| eint2_vic_chn0;
 VICVectAddr2=(u32)eint2_isr;
 EXTMODE=((1<<0)|(1<<1)|(1<<2));
                                                                                                                                                                                                                                                                                                                                                                            
}

void eint0_isr(void)__irq
{
  res=val;
  val=!val;
  indL=1;
  indR=0; 
  EXTINT=1<<0;
  VICVectAddr=0;
}

void eint1_isr(void)__irq
 {
  res1=val1;
  val1=!val1;
   indR=1;
   indL=0;
  EXTINT=1<<1;
  VICVectAddr=0;
  }

void eint2_isr(void)__irq
{
indL=0;
indR=0;
if(flag==0)
{
  mode1=flag;
  flag=!flag;	
  EXTINT=1<<2;
  VICVectAddr=0;
  }
  else
  {
   mode1=flag;
   flag=!flag;
   EXTINT=1<<2;
   VICVectAddr=0;
  }
}