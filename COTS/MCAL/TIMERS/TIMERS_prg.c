/*
 * TIMERS_prg.c
 *
 *  Created on: Jul 24, 2022
 *      Author: Bahgat Mahmoud
 */
#include "../../LIB/STD_TYPES.h"

#include "../../LIB/BIT_MATH.h"
#include "TIMERS_int.h"
#include "TIMERS_prv.h"
#include "TIMER0_cfg.h"
#include "TIMER1_cfg.h"
#include "TIMER2_cfg.h"

////callback function pointer private  (static)
//static void (*G_TIM0_CTC_Callback)(void);//function to pointer
//another method
static void (*G_tim0_Callback[2])(void);//array of fun pointer
//static void (*G_tim1_Callback[4])(void);
u32 G_u32IntervalCount;

void MTIMERS_vInit(void)
{	/*
 * Mode: Normal overflow 00
 *  Prescaler : NoCLOCK -> timer stopped   ?? we start timer when i need from other fun
 * Interrupt:enable Overflow interrupt
 */
	/*TIMER0 Initialize*/
#if TIMER0_ENABLE==ENABLE
	/* 1-Wave Generation Mode */
	//CLR_BIT(TCCR0,FOC0);
#if TIMER0_MODE==TIMER_OVF
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	/* 2-Compare match mode */
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif TIMER0_MODE==TIMER_CTC
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	/* 2-Compare match mode */
#if TIMER0_COMPAR_MATCH_OUTPUT_MODE==TIMER0_TOGGLE
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#endif
#elif TIMER0_MODE==TIMER_FASTPWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#elif TIMER0_MODE==TIMER_PHASECORRECT
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	else
#error "please select a valid Timer Mode"
#endif
		/* 2-Compare match mode */
#if TIMER0_MODE != TIMER_OVF
#if TIMER0_COMPAR_MATCH_OUTPUT_MODE==TIMER0_NORMALOPRATION
		CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif TIMER0_COMPAR_MATCH_OUTPUT_MODE==TIMER0_CLEAR
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif TIMER0_COMPAR_MATCH_OUTPUT_MODE==TIMER0_SET
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#error "please select a valid Timer Compare output Mode"
#endif

#endif
	/* 3- Interrupt enable */
#if TIMER0_INTERRUPT_ENABLE==ENABLE
#if   TIMER0_MODE == TIMER_OVF
	SET_BIT(TIMSK,TOIE0);
	CLR_BIT(TIMSK,OCIE0);
#elif TIMER0_MODE!=TIMER_OVF
	CLR_BIT(TIMSK,TOIE0);
	SET_BIT(TIMSK,OCIE0);
#endif
#endif
#endif


	/*Timer1 Initialize*/
#if TIMER1_ENABLE==ENABLE

#endif

}


/*write on prescaler bits CoS0 1 2*/
//commen with timers
void MTIMERS_vStartTimer(Timer_Id A_u8TimerId)
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		TCCR0 = (TCCR0 & 0xF8) | (TIMER0_PRESCALER);
		break ;

	}
}

void MTIMERS_vStopTimer(Timer_Id A_u8TimerId)
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		TCCR0 = (TCCR0 & 0xF8) | (STOP_TIMER);
		break ;

	}

}
//CALL BACK  A_u16IntervalCounts= count= Covf calculate for self in
void MTIMERS_SetCallBack (Timer_Id A_u8TimerId ,void (*A_fptr)(void))
{
	switch(A_u8TimerId)
	{
	case TIMER0 :

#if TIMER0_MODE == TIMER_OVF
		//	G_TIM0_OVF_Callback = A_fptr;
		G_tim0_Callback[TIMER0_CALLBACK_OVF]=A_fptr;
#elif TIMER0_MODE==TIMER_CTC
		G_tim0_Callback[TIMER0_CALLBACK_CTC]=A_fptr;
#endif
		break ;
	case TIMER1:

		break;
	}
}
void MTIMERS_vSetInterval_OVF_Asynch(Timer_Id A_u8TimerId , u16 A_u16IntervalCounts, u16 A_u16Preload)// speak to timer after this count in timer call this fun
{
	G_u32IntervalCount = A_u16IntervalCounts;
	MTIMERS_vSetPreloadValue( A_u8TimerId,A_u16Preload);
	MTIMERS_vStartTimer(A_u8TimerId);
}
void MTIMERS_vSetPreloadValue(Timer_Id A_u8TimerId , u16 A_u16Preload)
{
	if(A_u16Preload < 256)
	{
		switch(A_u8TimerId)
		{
		case TIMER0 :
			TCNT0 = A_u16Preload ;//the value that this counter start count from this value i.e ex if preload=100 100 ...101..102
			break ;
		case TIMER1:
			TCNT1 = A_u16Preload;
			break;
		}

	}
}
//ISR
//void __vector_x(void) __attribute__((signal));
//from table number of vector page 42 TIMR0 OVF (12-1)=11
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u32 LS_u32Counter=0 ;
	LS_u32Counter++;
	if(LS_u32Counter == G_u32IntervalCount )
	{
		if(G_tim0_Callback[TIMER0_CALLBACK_OVF] != NULL)
		{
			G_tim0_Callback[TIMER0_CALLBACK_OVF]();
			LS_u32Counter=0;
		}
	}

}
//in ctc,fast pwm mode
void MTIMERS_vSetInterval_CTC_Asynch(Timer_Id A_u8TimerId ,u16 A_u16IntervalCounts ,u16 A_u16CompareVal)// speak to timer after this count in timer call this fun
{
	G_u32IntervalCount = A_u16IntervalCounts;
	MTIMERS_vSetCompareValue(A_u8TimerId,A_u16CompareVal);
	MTIMERS_vStartTimer(A_u8TimerId);
}
void MTIMERS_vSetCompareValue(Timer_Id A_u8TimerId , u16 A_u16CompareValue)
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		if(A_u16CompareValue<=255)
		{
			OCR0=A_u16CompareValue;
		}
		break ;
	case TIMER1:

		break;
	}

}

/*Timer 0 CTC ISR */
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u32 LS_u32Counter=0 ;
	LS_u32Counter++;
	if(LS_u32Counter == G_u32IntervalCount )
	{
		if(G_tim0_Callback[TIMER0_CALLBACK_CTC] != NULL)
		{
			G_tim0_Callback[TIMER0_CALLBACK_CTC]();
			//			G_TIM0_CTC_Callback();
			LS_u32Counter=0;
		}
	}
}



u8 MTIMERS_u8ReadTimerReg(void)
{
	static u8 L_u8Ret = 0;
	TCCR0 = (TCCR0 & 0xF8) | (0b111);
	L_u8Ret = TCNT0 ;
	return L_u8Ret ;
}












/*
void MTIMERS_vSetInterval_OVF_Asynch(u16 A_u16IntervalCounts , void (*A_fptr)(void))// speak to timer after this count in timer call this fun
{
	G_u32IntervalCount = A_u16IntervalCounts;
	G_TIM0_OVF_Callback = A_fptr;
	//	G_tim0_Callback[TIMER0_CALLBACK_OVF]=A_fptr;
	MTIMERS_vStartTimer();
}
 */
/*
void __vector_11(void)
{
	static u32 LS_u32Counter=0 ;
			LS_u32Counter++;
	if(LS_u32Counter == G_u32IntervalCount )
	{
		if(G_TIM0_OVF_Callback != NULL)
			{
				G_TIM0_OVF_Callback();
				LS_u32Counter=0;
			}
	}

}
 */
////for CTC
//void MTIMERS_vInit_CTC(void)
//{
//	/*
//	 * Mode:CTC mode 00
//	 *  Prescaler : NoCLOCK -> timer stopped   ?? we start timer when i need from other fun
//	 * Interrupt:enable CTC interrupt
//	 */
//	TCCR0 =0x08;
//	SET_BIT( TIMSK , OCIE0);//OCIE0 = 1 bit1 enable interrupt for compare match register(CTC)
//
//}





