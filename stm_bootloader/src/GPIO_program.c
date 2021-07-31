/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 23 SEP 2020                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


/************* Function OF Set Pin Direction *************************/

void  GPIO_voidSetPinDirection (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Mode)
{
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            if (Copy_u8Pin <= 7)
            {//LOW
                GPIOA_CRL &= ~((0b1111)      << (Copy_u8Pin * 4));
                GPIOA_CRL |=  ((Copy_u8Mode) << (Copy_u8Pin * 4));
            }
            else if (Copy_u8Pin <= 15)
            {//HIGH
                GPIOA_CRH &= ~((0b1111)      << ((Copy_u8Pin - 8) * 4));
                GPIOA_CRH |=  ((Copy_u8Mode) << ((Copy_u8Pin - 8) * 4));
            }
            break;

        /*** PORT B ***/

        case GPIOB:
            if (Copy_u8Pin <= 7)
            {//LOW
                GPIOB_CRL &= ~((0b1111)      << (Copy_u8Pin * 4));
                GPIOB_CRL |=  ((Copy_u8Mode) << (Copy_u8Pin * 4));
            }
            else if (Copy_u8Pin <= 15)
            {//HIGH
                GPIOB_CRH &= ~((0b1111)      << ((Copy_u8Pin - 8) * 4));
                GPIOB_CRH |=  ((Copy_u8Mode) << ((Copy_u8Pin - 8) * 4));
            }
            break;

        /*** PORT C ***/

        case GPIOC:
            if (Copy_u8Pin <= 7)
            {//LOW
                GPIOC_CRL &= ~((0b1111)      << (Copy_u8Pin * 4));
                GPIOC_CRL |=  ((Copy_u8Mode) << (Copy_u8Pin * 4));
            }
            else if (Copy_u8Pin <= 15)
            {//HIGH
                GPIOC_CRH &= ~((0b1111)      << ((Copy_u8Pin - 8) * 4));
                GPIOC_CRH |=  ((Copy_u8Mode) << ((Copy_u8Pin - 8) * 4));
            }
            break;
        default:       break;
    }
}

/*************   Function OF Set Pin Value   *************************/
/***************** Options of Copy_u8Value:
                                            HIGH
                                            LOW     ******************/
void  GPIO_voidSetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            if (Copy_u8Value == HIGH)
            {
                SET_BIT (GPIOA_BSRR, Copy_u8Pin);
            }
            else if (Copy_u8Value == LOW)
            {
                SET_BIT (GPIOA_BRR, Copy_u8Pin);
            }
            break;

        /*** PORT B ***/

        case GPIOB:
            if (Copy_u8Value == HIGH)
            {
                SET_BIT (GPIOB_BSRR, Copy_u8Pin);
            }
            else if (Copy_u8Value == LOW)
            {
                SET_BIT (GPIOB_BRR, Copy_u8Pin);
            }
            break;

        /*** PORT C ***/

        case GPIOC:
            if (Copy_u8Value == HIGH)
            {
                SET_BIT (GPIOC_BSRR, Copy_u8Pin);
            }
            else if (Copy_u8Value == LOW)
            {
                SET_BIT (GPIOC_BRR, Copy_u8Pin);
            }
            break;

        default :       break;
    }
}

/*************   Function OF Get Pin Value   *************************/

u8 GPIO_u8GetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin)
{
    u8 LOC_u8Result = 0;
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            LOC_u8Result = GET_BIT (GPIOA_IDR, Copy_u8Pin);
            break;

        /*** PORT B ***/

        case GPIOB:
            LOC_u8Result = GET_BIT (GPIOB_IDR, Copy_u8Pin);
            break;

        /*** PORT C ***/

        case GPIOC:
            LOC_u8Result = GET_BIT (GPIOC_IDR, Copy_u8Pin);
            break;

        default :       break;
    }
    return LOC_u8Result;
}

/*************   Function OF Toggle Pin Value   **********************/

void  GPIO_voidTogglePinValue (u8 Copy_u8Port, u8 Copy_u8Pin)
{
    switch (Copy_u8Port)
	{
		 /*** PORT A ***/

		case GPIOA:
					TOG_BIT(GPIOA_ODR,Copy_u8Pin);
		  break;

		/*** PORT B ***/

		case GPIOB:
					TOG_BIT(GPIOB_ODR,Copy_u8Pin);
		  break;

		/*** PORT C ***/

		case GPIOC:
		  TOG_BIT(GPIOC_ODR,Copy_u8Pin);
		  break;

		default :       break;
	}
}

/*************   Function OF Set Pin PULL   *************************/
/***************** Options of Copy_u8Pull:
                                            PULL_UP
                                            PULL_DOWN ***************/
void  GPIO_voidSetPinPull (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Pull)
{
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            if (Copy_u8Pull == PULL_UP)
            {
                SET_BIT (GPIOA_ODR, Copy_u8Pin);
            }
            else if (Copy_u8Pull == PULL_DOWN)
            {
                CLR_BIT (GPIOA_ODR, Copy_u8Pin);
            }
            break;

        /*** PORT B ***/

        case GPIOB:
            if (Copy_u8Pull == PULL_UP)
            {
                SET_BIT (GPIOB_ODR, Copy_u8Pin);
            }
            else if (Copy_u8Pull == PULL_DOWN)
            {
                CLR_BIT (GPIOB_ODR, Copy_u8Pin);
            }
            break;

        /*** PORT C ***/

        case GPIOC:
            if (Copy_u8Pull == PULL_UP)
            {
                SET_BIT (GPIOC_ODR, Copy_u8Pin);
            }
            else if (Copy_u8Pull == PULL_DOWN)
            {
                CLR_BIT (GPIOC_ODR, Copy_u8Pin);
            }
            break;

        default :       break;
    }
}
