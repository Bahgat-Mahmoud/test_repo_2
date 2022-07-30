/*
 * LCD_cfg.h
 *
 *  Created on: Jul 22, 2022
 *      Author: DELL
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

/*control port*/
#define LCD_CTRL_PORT  DIO_PORTA

#define LCD_RS_PIN     DIO_PIN0
#define LCD_RW_PIN     DIO_PIN1
#define LCD_EN_PIN     DIO_PIN2
/*Data Port*/
#define LCD_DATA_PORT DIO_PORTD


/*
 options:
 LCD_FUNCTION_SET: 0b0011NF00
  Where NF
  00  one line display  & 5*7 dot character font
  10  Two line display  & 5*7 dot character font

  */
#define LCD_FUNCTION_SET  0b00111000

/*
 * options:
 LCD_DISPLAY_CURSOR: 0b00001DCB
	 D=1 display on   D=1 display off
	 C=0 cursor off   C=1 cursor on
	 B=0 blink off    B=0 Blink on
*/
#define LCD_DISPLAY_CURSOR 0b00001100

/*
	  0b000001 I/D SH
	  I/D  1   increment the cursor outomatic +1
	  SH=0 don`t interested now
*/
#define LCD_ENTRY_MODE_SET 0b00000110

#define MAX_IDX_OF_ROWS 1 
#define MAX_IDX_OF_COL 39
#endif /* HAL_LCD_LCD_CFG_H_ */
