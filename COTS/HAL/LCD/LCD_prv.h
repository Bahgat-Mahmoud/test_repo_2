/*
 * LCD_prv.h
 *
 *  Created on: Jul 22, 2022
 *      Author: DELL
 */

#ifndef HAL_LCD_LCD_PRV_H_
#define HAL_LCD_LCD_PRV_H_
//no found majek number i.e find number in code
/*TO CLEAR SCREEN=
 * 0b00001100

 */
#define LCD_CLEAR_SCREEN 0b00000001
#define LCD_SET_DDRAM_ADDRESS  0x80 // 0b10000000 cursor location SET_ADDRESS_COUNTER_MASK
#define LCD_SET_CGRAM_ADDRESS  0x40   //0b0100 0000 the address counter ponter to CGRAM

#define  FIRST_ROW_START_ADDRESS   0x00
#define  SECOND_ROW_START_ADDRESS  0x40
#define  THREE_ROW_START_ADDRESS   0x10
#define  FOUR_ROW_START_ADDRESS    0x50

#endif /* HAL_LCD_LCD_PRV_H_ */
   