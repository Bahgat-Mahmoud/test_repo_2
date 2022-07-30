/*
 * TIMERS_int.h
 *
 *  Created on: Jul 24, 2022
 *      Author: DELL
 */

#ifndef MCAL_TIMERS_TIMERS_INT_H_
#define MCAL_TIMERS_TIMERS_INT_H_

//#define   TIMER0_CALLBACK_OVF    1
//#define   TIMER0_CALLBACK_CTC    2

typedef enum
{
	TIMER0,
	TIMER1

}Timer_Id;

void MTIMERS_vInit(void);

u8 MTIMERS_u8ReadTimerReg(void);
void MTIMERS_vStartTimer(Timer_Id A_u8TimerId);
void MTIMERS_vStopTimer(Timer_Id A_u8TimerId);
void MTIMERS_vSetPreloadValue(Timer_Id A_u8TimerId , u16 A_u16Preload);
//CALL BACK
void MTIMERS_SetCallBack (Timer_Id A_u8TimerId , void (*A_fptr)(void));
void MTIMERS_vSetInterval_OVF_Asynch(Timer_Id A_u8TimerId , u16 A_u16IntervalCounts, u16 A_u16Preload);

//void MTIMERS_vSetInterval_OVF_Asynch(u16 A_u16IntervalCounts , void (*A_fptr)(void));// speak to timer after this count in timer call this fun




//for CTC
void MTIMERS_vSetCompareValue(Timer_Id A_u8TimerId,u16 A_u16CompareValue);

void MTIMERS_vSetInterval_CTC_Asynch(Timer_Id A_u8TimerId ,u16 A_u16IntervalCounts ,u16 A_u16CompareVal);




#endif /* MCAL_TIMERS_TIMERS_INT_H_ */
