/*
 * KEYPAD_prog.c
 *
 *  Created on: Jul 20, 2022
 *      Author: DELL
 */
#include  "../../LIB/STD_TYPES.h"

#include  "../../MCAL/DIO/DIO_int.h"

#include "KEYPAD_int.h"
#include "KEYPAD_cfg.h"
#include "util/delay.h"


void HKEYPAD_vInit (void)
{
	/* PORTB -> inputs/outputs (c1 & c2 & c3 & c4) are output from B0 to B3  and from B4 to B7 are input  */
	MDIO_vSetPortDir(KEYPAD_PORT, 0x0f);
	/* PULL UP RESISTORS ACTIVATION ON INPUTS B4 to B7 pull up*/
	MDIO_vSetPortVal(KEYPAD_PORT, 0xff);
}

u8 HKEYPAD_u8GetPressdKey(void)
{
	u8 Pressed_Key = NOTPRESSED; // if the return = 0 this is mean not pressed key
	while(Pressed_Key==NOTPRESSED)
	{
		for(u8 col=0;col<4;col++)
		{
			/*activate current column*/
			MDIO_vSetPinVal(KEYPAD_PORT,col,DIO_LOW);
			//CLR_BIT(PORTB, col);
			for(u8 row=0;row<4;row++)
			{
				if(MDIO_u8GetPinVal(KEYPAD_PORT,row+4)== 0)//GET_BIT(PINB,row+4)
				{
					_delay_ms(20);
					if(MDIO_u8GetPinVal(KEYPAD_PORT,row+4)== 0)
					{
						Pressed_Key = (row+(col*4)+1);/* key number */ //4 number of rows
						/*for debouncing*/
				        while (MDIO_u8GetPinVal(KEYPAD_PORT,row+4) == 0);
				        _delay_ms(20);
					}
					
				}
				if(Pressed_Key!=NOTPRESSED)
				{
					return Pressed_Key;
					
				}
			}
			/*deactivate column*/
			//SET_BIT(PORTB, col);
			MDIO_vSetPinVal(KEYPAD_PORT,col,DIO_HIGH);
		}
	}


}
