/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H



/***************   Function definition    ******************/

void   STK_voidInit					(void);
void   STK_voidSetBusyWait			(u32 Copy_u32Ticks);
void   STK_voidSetIntervalSingle	(u32 Copy_u32Ticks, void (*Copy_ptr) (void));
void   STK_voidSetIntervalPeriodic	(u32 Copy_u32Ticks, void (*Copy_ptr) (void));
void   STK_voidStopInterval			(void);
u32 STK_u32GetElapedTime			(void);
u32 STK_u32GetRemainingTime		(void);

void   STK_voidDelay_ms				(u32 Copy_u32Ticks);

void STK_voidStartTimer(u32 Copy_u32Ticks);
void STK_voidStopTimer(void);

#endif /* STK_INTERFACE_H */
