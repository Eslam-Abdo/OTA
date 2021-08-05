/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"



/* define Callback Global variable (pointer to function) */
static void (*STK_CallBack) (void);

/* define variable for interval mode 		*/
static u8 STk_u8ModeOfInterval;




/*************	 Function OF Initialize clock Source of STK  **************************/
/* Apply clock choice from configuration file
 * Disable SysTick Interrupt
 * Disable SysTick									 */

void STK_voidInit (void)
{
#if STK_CLOCK_SRC == STK_SRC_AHB
	/* Disable STK - Disable STK Interrupt - Set clock source AHB	 */
	STK->CTRL = 0x00000004;
#elif STK_CLOCK_SRC == STK_SRC_AHB_8
	/* Disable STK - Disable STK Interrupt - Set clock source AHB/8  */
	STK->CTRL = 0;
#endif
}

/*************	 Function OF Set Busy Wait  **************************/
/* This is function Like delay function stop the code until finish count
 *  9	 count 	= 1 us
 *  900	 counts = 100 us
 *  9000 counts = 1 ms
 *  and so on ...													 */

void STK_voidSetBusyWait (u32 Copy_u32Ticks)
{
	/* Load ticks to load register */
	STK->LOAD = Copy_u32Ticks;

	/* Start Timer */
	SET_BIT(STK->CTRL, 0);

	/* Wait till flag is raised */
	while( (GET_BIT(STK->CTRL, 16)) == 0);

	/* Stop Timer */
	CLR_BIT(STK->CTRL, 0);
	STK->LOAD = 0 ;
	STK->VAL = 0;

}

/*************	 Function OF Set Interval Single  **************************/
/* this function take ticks and function to do after ticks finished and do it once
 * but don't stop the code until finish count
 *  9	 count 	= 1 us
 *  900	 counts = 100 us
 *  9000 counts = 1 ms
 *  and so on ...													 */

void  STK_voidSetIntervalSingle (u32 Copy_u32Ticks, void (*Copy_ptr) (void))
{
	/* Load ticks to load register */
	STK->LOAD = Copy_u32Ticks;

	/* Start Timer */
	SET_BIT(STK->CTRL, 0);

	/* Save CallBack */
	STK_CallBack = Copy_ptr;

	/* Set Mode to Single */
	STk_u8ModeOfInterval = STK_SINGLE_INTERVAL;

	/* Enable STk Interrupt */
	SET_BIT(STK->CTRL, 1);

}

/*************	 Function OF Set Interval Periodic  **************************/
/* this function take ticks and function to do after ticks finished and do it many time until you call a function stop it
 * but don't stop the code until finish count
 *  9	 count 	= 1 us
 *  900	 counts = 100 us
 *  9000 counts = 1 ms
 *  and so on ...													 */

void  STK_voidSetIntervalPeriodic (u32 Copy_u32Ticks, void (*Copy_ptr) (void))
{
	/* Load ticks to load register */
		STK->LOAD = Copy_u32Ticks;

		/* Start Timer */
		SET_BIT(STK->CTRL, 0);

		/* Save CallBack */
		STK_CallBack = Copy_ptr;

		/* Set Mode to Period */
		STk_u8ModeOfInterval = STK_PERIOD_INTERVAL;

		/* Enable STk Interrupt */
		SET_BIT(STK->CTRL, 1);

}

/*************	 Function OF Stop Interval  **************************/

void STK_voidStopInterval (void)
{
	/* Disable STk Interrupt */
	CLR_BIT(STK->CTRL, 1);

	/* Stop Timer */
	CLR_BIT(STK->CTRL, 0);
	STK->LOAD = 0 ;
	STK->VAL = 0;
}

/*************	 Function OF Get Elaped Time  **************************/
/* Return the number of thicks that done (load - val) */
u32 STK_u32GetElapedTime (void)
{
	u32 Local_u32ElapsedTime;

	Local_u32ElapsedTime = STK -> LOAD - STK -> VAL;

	return Local_u32ElapsedTime;
}

/*************	 Function OF Get Remaining Time  **************************/
/* Return the number of thicks that will count (remaining time) (val) */

u32 STK_u32GetRemainingTime (void)
{
	u32 Local_u32ElapsedTime;

	Local_u32ElapsedTime = STK -> VAL;

	return Local_u32ElapsedTime;
}

/*************	 Function OF STK Interrupt  **************************/
/* This is function call a STK_CallBack() function to do when interrupt */

void SysTick_Handler (void)
{
	u8 Local_u8Temporary;

	if (STk_u8ModeOfInterval == STK_SINGLE_INTERVAL)
	{ /* Stop Interval */

		/* Disable STk Interrupt */
		CLR_BIT(STK->CTRL, 1);

		/* Stop Timer */
		CLR_BIT(STK->CTRL, 0);
		STK->LOAD = 0 ;
		STK->VAL = 0;
	}

	/* CallBack notification */
	STK_CallBack();

	/* Clear Interrupt Flag */
	Local_u8Temporary = GET_BIT(STK->CTRL, 16);
}

/*************	 Function OF Delay_ms  **************************/
/* This is function is call from (STK_voidSetBusyWait()), it is delay function stop the code until finish count
 *  9	 count 	= 1 us
 *  900	 counts = 100 us
 *  9000 counts = 1 ms
 *  and so on ...													 */

void STK_voidDelay_ms (u32 Copy_u32Ticks)
{
	/* convert from ms to us as
	 * 1 ms = 9000 us */
	Copy_u32Ticks *= 9000;
	STK_voidSetBusyWait(Copy_u32Ticks);
}

void STK_voidStartTimer(u32 Copy_u32Ticks)
{
	/* Load ticks to load register */
	STK->LOAD = Copy_u32Ticks;
	/* Start Timer */
	SET_BIT(STK->CTRL, 0);
}

void STK_voidStopTimer(void)
{
/* Stop Timer */
	CLR_BIT(STK->CTRL, 0);
	STK->LOAD = 0 ;
	STK->VAL = 0;
}