/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/*******************   BASE Address Definition    *********************/

#define STK_BASE_ADDRESS	(u32)(0xE000E010) 		//define the boundary address of STK

/*******************   Register Definition     ***********************/

typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}STK_t;

#define STK			((volatile STK_t *) STK_BASE_ADDRESS)

/******************   STK Clock Source Definition   ******************/

#define STK_SRC_AHB_8				0
#define STK_SRC_AHB					1

/******************   STK interval mode Definition   ******************/

#define STK_SINGLE_INTERVAL			0
#define STK_PERIOD_INTERVAL			1

#endif /* STK_PRIVATE_H */
