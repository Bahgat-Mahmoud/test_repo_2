#include  "../../LIB/STD_TYPES.h"

#include  "../../MCAL/DIO/DIO_int.h"
#include <util/delay.h>
#include "LCD_cfg.h"
#include  "LCD_prv.h"
#include "LCD_int.h"



static void HLCD_svFallingEdge(void);

static void HLCD_svFallingEdge(void)
{
	/*3-Pulse on the enable pin (enable=high and delay(1msec) 
and low delay(1ms)) */
	//falling edge
	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_EN_PIN , DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_EN_PIN , DIO_LOW);
	_delay_ms(1);//the delay from data sheet of LCD interface 
timing chart minimum 230 nsec (pulse width)

}
//to send command
/*the important function Send Command and Send Character*/
void HLCD_vSendCommand (u8 A_u8Cmd)
{
	/*1-Control Rs & RW Pins*/
	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_RS_PIN , 
DIO_LOW);//enable the command


	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_RW_PIN , 
DIO_LOW);//Write on LCD
	/*2-Write Command on the data pins*/
	MDIO_vSetPortVal(LCD_DATA_PORT,A_u8Cmd);
	//falling edge
	HLCD_svFallingEdge();
}
// to send data
void HLCD_vSendChar(u8 A_u8Char) // A_u8Char from data sheet 
CGROM  HIGH LOW example '0' = 48 = 0x30 =  0b00110000
{
	/*1-Control Rs & RW Pins*/
	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_RS_PIN , 
DIO_HIGH);//enable the data


	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_RW_PIN , 
DIO_LOW);//Write on LCD
	/*2-Write Command on the data pins*/
	MDIO_vSetPortVal(LCD_DATA_PORT,A_u8Char);
	HLCD_svFallingEdge();

}
void HLCD_vInit(void)
{
	/*Set Your pin Direction*/
	MDIO_vSetPortDir(LCD_DATA_PORT,0xff);
	MDIO_vSetPinDir(LCD_CTRL_PORT , LCD_RS_PIN , DIO_OUTPUT);
	MDIO_vSetPinDir(LCD_CTRL_PORT , LCD_RW_PIN , DIO_OUTPUT);
	MDIO_vSetPinDir(LCD_CTRL_PORT , LCD_EN_PIN , DIO_OUTPUT);
	/*start initialize sequence 8bit initialization */
	/*Wait  bigger than 30ms*/
	_delay_ms(50);
	/*Function Set*/
	HLCD_vSendCommand(LCD_FUNCTION_SET);
	/*Wait bigger than 39us*/
	_delay_ms(1);
	HLCD_vSendCommand(LCD_DISPLAY_CURSOR);
	/*Wait bigger than 39us*/
	_delay_ms(1);
	/*clear the screen*/
	HLCD_vSendCommand(LCD_CLEAR_SCREEN);
	/*Wait bigger than 1.53ms*/
	_delay_ms(3);
	HLCD_vSendCommand(LCD_ENTRY_MODE_SET);

}
void HLCD_vClearCommand(void)
{
	HLCD_vSendCommand(LCD_CLEAR_SCREEN);
}

void HLCD_vPrintString (char *A_s8str)
{

	u8 L_u8i = 0;
	while(A_s8str[L_u8i] != 0)
		{
		  HLCD_vSendChar(A_s8str[L_u8i]);
		  L_u8i ++;
		}

}


void HLCD_vPrintNumber(s32 A_s32Number)
{
	u8 L_u8arr[200] ,L_u8i = 0;
if(A_s32Number==0)
{
	HLCD_vSendChar('0');
}
else if (A_s32Number < 0)
{
	HLCD_vSendChar('-');
	A_s32Number=A_s32Number *(-1);
}
while(A_s32Number !=0)
{
	L_u8arr[L_u8i] = A_s32Number % 10 ;//0 1 2 3
	A_s32Number = A_s32Number /10 ;
	L_u8i++;
}
while(L_u8i!=0)
{
	L_u8i--;// 2 1 0
	HLCD_vSendChar(L_u8arr[L_u8i] + '0'); // '0'=48
}
}
//GO TO ROW COLUMN
void HLCD_vSetCursorPostion(u8 A_u8LineNo , u8 A_u8LionPos)// row , column
{
	u8 L_u8addressDDR = 0;
	/*the if condtion data validation  ensure that the data in your range */
	if (A_u8LineNo <=MAX_IDX_OF_ROWS && A_u8LionPos <=MAX_IDS_OF_COL)
	{
		switch(A_u8LineNo)
	{
	   case LCD_LINE0 :
		   L_u8addressDDR = A_u8LionPos + FIRST_ROW_START_ADDRESS;
		   break ;
	   case LCD_LINE1 :
		   L_u8addressDDR = A_u8LionPos + SECOND_ROW_START_ADDRESS;
	   		   break ;
	   case LCD_LINE2 :
		   L_u8addressDDR = A_u8LionPos + THREE_ROW_START_ADDRESS;
	   		   break ;
	   case LCD_LINE3 :
		   L_u8addressDDR = A_u8LionPos + FOUR_ROW_START_ADDRESS;
	   		   break ;
	    default   
		     /* Do NOTHING */
	}
	L_u8addressDDR = (L_u8addressDDR | LCD_SET_DDRAM_ADDRESS);
	HLCD_vSendCommand(L_u8addressDDR);
	}
	
	

}

void HLC_vWriteInCGRAM(u8 A_u8patternIdx , u8 *A_u8patternValue)
{
	u8 Lu8LoopItrator;
	/*Step 1: Set ADDRESS COUNTER on CGRAM from command name set CGRAM ADDRES 6bit address CGRAM*/
	switch(A_u8patternIdx)
	{
	case 0:
		HLCD_vSendCommand(0x40);
		break;
	case 1:
		HLCD_vSendCommand(0x48);
		break;
	case 2:
		HLCD_vSendCommand(0x50);
		break;
	case 3:
		HLCD_vSendCommand(0x58);
		break;
	case 4:
		HLCD_vSendCommand(0x60);
		break;
	case 5:
		HLCD_vSendCommand(0x68);
		break;
	case 6:
		HLCD_vSendCommand(0x70);
		break;
	case 7:
		HLCD_vSendCommand(0x78);
		break;
		// default    :    /*Report Error */ ; break;

	}
	/* Step 2: Write pattern in CGRAM */
	for (Lu8LoopItrator=0 ; Lu8LoopItrator<8;Lu8LoopItrator++)
	{
		HLCD_vSendChar(A_u8patternValue[Lu8LoopItrator]);
	}
	/**/
}
void HLCD_vDisplayCustomChar(u8 A_u8patternIdx)
{
	HLCD_vSendChar(A_u8patternIdx);
}
