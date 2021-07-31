/*********************************************************************************/
/* Author    : Omar Lasheen                                                        */
/* Version   : V01                                                               */
/* Date      : 19 Jan 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART_t;

#define USART1     	((volatile UART_t *) 0x40013800)     //define the boundary address of USART1
#define USART2      ((volatile UART_t *)0x40004400)      //define the boundary address of USART2
#define USART3      ((volatile UART_t *)0x40004800)      //define the boundary address of USART3








#endif // USART_PRIVATE_H
