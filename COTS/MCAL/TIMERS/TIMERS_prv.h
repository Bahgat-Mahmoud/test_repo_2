/*
 * TIMERS_prv.h
 *
 *  Created on: Jul 24, 2022
 *      Author: DELL
 */

#ifndef MCAL_TIMERS_TIMERS_PRV_H_
#define MCAL_TIMERS_TIMERS_PRV_H_

#define TCCR0       *((volatile u8*)(0x53))
#define TCNT0       *((volatile u8*)(0x52))
#define OCR0        *((volatile u8*)(0x5C))
#define TIMSK       *((volatile u8*)(0x59))
#define TIFR        *((volatile u8*)(0x58))

#define TCCR1A       *((volatile u8*)(0x4F))
#define TCCR1B       *((volatile u8*)(0x4E))
#define TCNT1        *((volatile u16*)(0x4C))
//#define TCNT1H       *((volatile u8*)(0x4D))
//#define TCNT1L       *((volatile u8*)(0x4C))
#define OCR1A        *((volatile u16*)(0x4A))
//#define OCR1AH       *((volatile u8*)(0x4B))
//#define OCR1AL       *((volatile u8*)(0x4A))
#define OCR1B        *((volatile u16*)(0x48))
//#define OCR1BH       *((volatile u8*)(0x49))
//#define OCR1BL       *((volatile u8*)(0x48))
#define ICR1         *((volatile u16*)(0x46))
//#define ICR1H        *((volatile u8*)(0x47))
//#define ICR1L        *((volatile u8*)(0x46))

#define  TOIE0        0
#define  OCIE0        1
#define  STOP_TIMER   0b000

/*REG TCCR0 Timer counter control register*/
#define COM00         5
#define COM01         4
#define WGM01         3
#define WGM00         6
#define FOC0          7

/*REG TIMSK Timer interrupt mask register*/
#define  TOIE0        0
#define  OCIE0        1
/*Register TIFR*/
#define  TOV0         0
#define  OCF0         1
#define  TOV1         2
#define  OCF1B        3
#define  OCF1A        4
#define  ICF1         5


#define  ENABLE       1
#define  DISABLE      0
/*
 * 001 No prescaller
 * 010 8(from prescaler)
 * 011 64(from prescaler)
 * 100 256(from prescaler)
 * 101 1024(from prescaler)
 * 110 external clock source on T0 pin   CLOCK Falling edge
 * 111 external clock source on T0 pin   CLOCK rising edge
 */
#define    TIMER_PS_1                                          0b001
#define    TIMER_PS_8                                          0b010
#define    TIMER_PS_64                                         0b011
#define    TIMER_PS_256                                        0b100
#define    TIMER_PS_1024                                       0b101
#define    TIMER_PS_EXTERNAL_CLOCK_FALLINGEDGE_FROM_PIN_T0     0b110
#define    TIMER_PS_EXTERNAL_CLOCK_RISINGEDGE_FROM_PIN_T0      0b111

#define TIMER_OVF               0 //Normal
#define TIMER_PHASECORRECT      1
#define TIMER_CTC               2
#define TIMER_FASTPWM           3

#define  TIMER0_NORMALOPRATION   0
#define  TIMER0_TOGGLE           1
#define  TIMER0_CLEAR            2
#define  TIMER0_SET              3

#define TIMER0_CALLBACK_OVF      0
#define TIMER0_CALLBACK_CTC      1

#endif /* MCAL_TIMERS_TIMERS_PRV_H_ */
