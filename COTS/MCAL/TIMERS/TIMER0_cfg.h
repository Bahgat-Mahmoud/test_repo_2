/*
 * TIMER0_cfg.h
 *
 *  Created on: Jul 26, 2022
 *      Author: DELL
 */

#ifndef MCAL_TIMERS_TIMER0_CFG_H_
#define MCAL_TIMERS_TIMER0_CFG_H_



/*-----------------Timer 0 configuration-----------------*/
/**
 * options:
        ENABLE
        DISABLE
 * */
#define TIMER0_ENABLE  ENABLE

/**
 *TIMER MODE
 * options:
 *     1- TIMER_OVF
 *     2- TIMER_CTC
 *     3- TIMER_FASTPWM
 *     4- TIMER_PHASECORRECT
 */
#define TIMER0_MODE  TIMER_CTC
/*TIMER INTURRUPT
 * Options:
 *        1- ENABLE
 *        2- DISABLE
 */
#define  TIMER0_INTERRUPT_ENABLE     ENABLE
/* CHOOSE COMPARE OUTPUT MODE ON BIN OC0*/
/*
 * OPTIONS TIMER0_X
  a- if used  CTC MODE:
          1-TIMER0_NORMALOPRATION     //OC0 disconnected
          2-TIMER0_TOGGLE       //toggle OC0 pin on compare match
          3-TIMER0_CLEAR        //clear OC0 pin on compare match  only
          4-TIMER0_SET
  b- if used FASTPWM MODE:
          1-TIMER0_NORMALOPRATION
          2-TIMER0_CLEAR           //Clear OC0 pin On compare match & set OC0 at Top
          3-TIMER0_SET             //Set OC0 pin On compare match & Clear OC0 at Top
  c- if used FASTPWM MODE:
          1-TIMER0_NORMALOPRATION
          2-TIMER0_CLEAR           //Clear OC0 pin On compare match & set OC0 at Top
          3-TIMER0_SET             //Set OC0 pin On compare match & Clear OC0 at Top
*/
#define     TIMER0_COMPAR_MATCH_OUTPUT_MODE    TIMER0_TOGGLE

/*
 * choose the prescaler
 * options:  TIMER_PS_x
 * where  x:
 *          1
 *          8
 *          64
 *          256
 *          1024
 *          EXTERNAL_CLOCK_FALLINGEDGE_FROM_PIN_T0
 *          EXTERNAL_CLOCK_RISINGEDGE_FROM_PIN_T0
 */
#define     TIMER0_PRESCALER  TIMER_PS_8

#endif /* MCAL_TIMERS_TIMER0_CFG_H_ */
