/*
 * main.c
 *
 *  Created on: Jul 14, 2022
 *      Author: DELL
 */
#include <avr/io.h>

#include <util/delay.h>
int main(void)
{

	DDRA=0b00001111 ; //PA0 -> OUTPUT
	//0x0f
	while (1)//super loop
	{
		PORTA = 0b00000001;
		for(int i=0;i<4;i++)
		{
			_delay_ms(1000);
			PORTA = PORTA << 1;
		}
		/*
		PORTA=0b00000001 ;// PA0 -> HIGH (5v)

		_delay_ms(1000);

		PORTA= 0 ;// PA0 -> LOW (0v)

		_delay_ms(1000);
		 */
		// VAR |=  (1 << (BIT))
		/*
		for(int i=0;i<4;i++)
		{
			PORTA = 0;
			PORTA =PORTA | (1 << i)  ;
			_delay_ms(1000);
		}
		for(int i=3;i>0;i--)
		{
			PORTA = 0;
			PORTA =PORTA | (1 << i)  ;
			_delay_ms(1000);


		}
		 */


	}
	return 0;

}
