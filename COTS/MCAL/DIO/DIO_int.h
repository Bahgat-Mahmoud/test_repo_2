/*
 * DIO_int.h

file of interface
 *
 *  Created on: Jul 20, 2022
 *      Author: DELL
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

/*to very sample  */
#define DIO_PORTA  'A'
#define DIO_PORTB  'B'
#define DIO_PORTC  'C'
#define DIO_PORTD  'D'

/*where pin you need*/
#define DIO_PIN0  0
#define DIO_PIN1  1
#define DIO_PIN2  2
#define DIO_PIN3  3
#define DIO_PIN4  4
#define DIO_PIN5  5
#define DIO_PIN6  6
#define DIO_PIN7  7


#define  DIO_OUTPUT  1
#define  DIO_INPUT   0

#define  DIO_HIGH    1
#define  DIO_LOW     0

void MDIO_vSetPinDir(u8 A_u8PortNo,u8 A_u8PinNo ,u8 A_u8Dir);
void MDIO_vSetPinVal(u8 A_u8PortNo,u8 A_u8PinNo ,u8 A_u8Val);
u8 MDIO_u8GetPinVal(u8 A_u8PortNo,u8 A_u8PinNo );

void MDIO_vSetPortDir(u8 A_u8PortNo,u8 A_u8Dir);
void MDIO_vSetPortVal(u8 A_u8PortNo,u8 A_u8val);
u8 MDIO_u8GetPortVal(u8 A_u8PortNo);

void MDIO_vTogPinVal(u8 A_u8PortNo,u8 A_u8PinNo);
#endif /* MCAL_DIO_DIO_INT_H_ */
