#include <lpc21xx.h>
#include"defines1.h"
#include"lcd_defines.h"
#include"delay.h"
#include"types.h"
void writeLcd(u8 data)
{
IOCLR0=1<<RW;
WBYTE(IOPIN0,LCD_DATA,data);
SSETBIT(IOSET0,EN);
delay_us(1);
SCLRBIT(IOCLR0,EN);
delay_ms(1);
}
void cmdLcd(u8 cmd)
{
SCLRBIT(IOCLR0,RS);
writeLcd(cmd);
}
void CharLcd(u8 ascii)
{
SSETBIT(IOSET0,RS);
writeLcd(ascii);
}
void InitLcd(void)
{
WBYTE(IODIR0,LCD_DATA,255);
SETBIT(IODIR0,RS);
SETBIT(IODIR0,RW);
SETBIT(IODIR0,EN);
delay_ms(15);
cmdLcd(MODE_8BIT_1LINE);
delay_ms(5);
cmdLcd(MODE_8BIT_1LINE);
delay_us(100);
cmdLcd(MODE_8BIT_1LINE);
cmdLcd(DISP_ON);
cmdLcd(0x0f);
cmdLcd(MODE_8BIT_2LINE); 
cmdLcd(CLEAR_LCD);
cmdLcd(SHIFT_CUR_RIGHT);
}
void strLcd(s8*p)
{
while(*p)
CharLcd(*p++);
}
void u32Lcd(u32 n)
{
u8 a[10];
s32 i=0;
if(n==0)
{
CharLcd('0');
}
else
{
while(n)
{
a[i++]=(n%10)+48;
n/=10;
}
for(--i;i>=0;i--)
{
CharLcd(a[i]);
}
}
}

void BuildCGRAM(u8 *p,u8 nb)
{
s32 i;
//cmdLcd(GOTO_CGRAM);
for(i=0;i<=nb;i++)
{
CharLcd(p[i]);
}
//cmdLcd(0x80);
}



