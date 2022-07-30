
#ifndef LCD_interface_H_
#define LCD_interface_H_

#define LCD_LINE0  0
#define LCD_LINE1  1
#define LCD_LINE2  2
#define LCD_LINE3  3


void HLCD_vInit(void); // initialize
void HLCD_vSendCommand (u8 A_u8Cmd); // command
void HLCD_vSendChar(u8 A_u8Char);// print data
void HLCD_vPrintString (char A_s8String[]);
void HLCD_vPrintNumber(s32 A_s32Number);
void HLCD_vSetCursorPostion(u8 A_u8LinePos , u8 A_u8LionNo);//A_u8LionPostion x axcis
void HLCD_vClearCommand(void);
void HLC_vWriteInCGRAM(u8 A_u8patternIdx , u8 *A_u8patternValue);
void HLCD_vDisplayCustomChar(u8 A_u8patternIdx);




#endif
