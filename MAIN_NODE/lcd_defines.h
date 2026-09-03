#include"types.h"
#define LCD_DATA 8
#define RS 18
#define RW 10
#define EN 19
//lcd commands
#define CLEAR_LCD 0x01
#define RET_CUR_HOME 0x02
#define DISP_OFF 0x08
#define DISP_ON 0x0C
#define DISP_ON_CUR_ON 0x0E
#define DISP_ON_CUR_BLINK 0X0E
#define MODE_8BIT_1LINE 0x30
#define MODE_8BIT_2LINE 0x38
#define MODE_4BIT_1LINE 0x20
#define MODE_4BIT_2LINE 0x28
#define GOT0_LINE1_POS0 0x80
#define GOTO_LINE2_POS0 0xC0
#define GOTO_LINE3_POS0 0X94
#define GOTO_LINE4_POSO 0xD4
#define SHIFT_CUR_RIGHT 0x06
#define SHIFT_DISP_LEFT 0x10
#define SHIFT_DISP_RIGHT 0x14
#define GOTO_CGRAM 0x40

void writeLcd(u8 data);
void cmdLcd(u8 cmd);
void CharLcd(u8 ascii);
void InitLcd(void);
void strLcd(s8*p);
void u32Lcd(u32 n);
void BuildCGRAM(u8 *p,u8 nb);
