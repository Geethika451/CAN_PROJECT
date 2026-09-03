#include<lpc21xx.h>

#include"lcd_defines.h"

//#include"defines.h"
#include"can_defines.h"
#include"can.h"
#include"delay.h"
#include"uitrasonic.h"

struct CAN_Frame txFrame;							

int main()

{
unsigned int dist;
InitLcd();
Init_CAN1();

INIT_Ultrasonic();

T0PR=12000000/1000000-1;

while(1)

{
cmdLcd(0x01);
cmdLcd(0x80);

strLcd("distance:");

dist=dist_cal();

u32Lcd(dist);

delay_ms(1000);                                                       
//T0PR=12000000/1000000-1;
//struct CAN_Frame txFrame;
  txFrame.Data1	=dist;
  txFrame.vbf.DLC=1;
  txFrame.ID=MAIN_ID;   txFrame.vbf.RTR=0;
  CAN1_Tx(txFrame);
} 
}