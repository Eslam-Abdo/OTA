/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 18 July 2021                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "FPEC_interface.h"
#include "FPEC_config.h"
#include "FPEC_private.h"


void FPEC_voidEraseAppArea(void)
{
	uint8 i;
	for (i = BOOTLOADER_SIZE ; i < 64 ; i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}
	
void FPEC_voidFlashPageErase(uint8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while(GET_BIT(FPEC->SR,0) == 1);
	
	/* Check if FPEC is locked or not */
	if(GET_BIT(FPEC->CR,7) == 1) /* LOCK BIT */	
	{
		WRITE_REG(FPEC->KEYR, 0x45670123);
		WRITE_REG(FPEC->KEYR, 0xCDEF89AB);
	}		
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,1);
	
	/* Write Page address */
	WRITE_REG(FPEC->AR, ((uint32)(Copy_u8PageNumber * 1024) + 0x08000000));
	
	/* Start operation */
	SET_BIT(FPEC->CR,6);
	
	/* Wait Busy Flag */
	while(GET_BIT(FPEC->SR,0) == 1);
	
	/* EOP */
	SET_BIT(FPEC->SR,5); /* RESET EOP BIT */
	CLR_BIT(FPEC->CR,1); /* CLEAR Page Erase Operation */
}


void FPEC_voidFlashWrite(uint32 Copy_u32Address, uint16* Copy_u16Data, uint8 Copy_u8Length)
{
	/* Wait Busy Flag */
	while(GET_BIT(FPEC->SR,0) == 1);
	
	/* Check if FPEC is locked or not */
	if(GET_BIT(FPEC->CR,7) == 1) /* LOCK BIT */	
	{
		WRITE_REG(FPEC->KEYR, 0x45670123);
		WRITE_REG(FPEC->KEYR, 0xCDEF89AB);
	}		
	
	for(uint8 i=0; i<Copy_u8Length ; i++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,0);
		
		/* Half word operation */
		
		*((volatile uint16*) Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2;
		
		/* Wait Busy Flag */
		while(GET_BIT(FPEC->SR,0) == 1);
		
		/* EOP */
		SET_BIT(FPEC->SR,5); /* RESET EOP BIT */
		CLR_BIT(FPEC->CR,0); /* CLEAR Flash programming chosen */
	}
	
}


