/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 22 SEP 2020                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInitSysClock(void)
{
    #if     RCC_CLOCK_TYPE == RCC_HSI
       // CLR_BIT(RCC_CFGR,0);     /* HSI selected as system clock */
        //CLR_BIT(RCC_CFGR,1);
				//SET_BIT(RCC_CR, 0);	   /* Enable HSI + Trimming = 0 */
				//SET_BIT(RCC_CR, 7);
	
   	RCC_CR   = 0x00000081; /* Enable HSI + Trimming = 0 */
		RCC_CFGR = 0x00000000;
	
    #elif   RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
        SET_BIT(RCC_CFGR,0);	  /* HSE selected as system clock */
        CLR_BIT(RCC_CFGR,1);     
    	SET_BIT(RCC_CR, 16);     /* Enable HSE with no bypass */
    #elif   RCC_CLOCK_TYPE == RCC_HSE_RC
        SET_BIT(RCC_CFGR,0);	  /* HSE selected as system clock */
        CLR_BIT(RCC_CFGR,1);
        SET_BIT(RCC_CR, 18);    /* Enable HSE with bypass */
        SET_BIT(RCC_CR, 16);
    #elif    RCC_CLOCK_TYPE == RCC_PLL
        /* PLL selected as system clock */
            CLR_BIT(RCC_CFGR,0);	  
            SET_BIT(RCC_CFGR,1); 
        /* PLL MUL FECTOR */
            RCC_CFGR &= ~((0b1111) << 18);
            RCC_CFGR |= (RCC_PLL_MUL_VAL) << 18; 
        #if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
            CLR_BIT(RCC_CFGR, 16); 	/* Enable HSI + Trimming = 0 + ENABLE PLL*/
	    
        #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
        /* Enable HSE with no bypass   */
    	    SET_BIT(RCC_CR, 16);  
    	 /* 	HSE/2 selected		*/   
    	    SET_BIT(RCC_CFGR,16);
    	    SET_BIT(RCC_CFGR,17);

        #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
        /* Enable HSE with no bypass   */
    	    SET_BIT(RCC_CR, 16);     
    	/* 	HSE selected		*/
    	    SET_BIT(RCC_CFGR,16);
    	    CLR_BIT(RCC_CFGR,17);
        #endif // RCC_PLL_INPUT
				SET_BIT(RCC_CFGR,10); //divide APB1 clk by 2 for clk not to exceed 36MHZ
	/* Enable PLL */
	SET_BIT(RCC_CR, 24); 
	while(GET_BIT(RCC_CR,25)== 0){}     
    #else
        #error("You chosed Wrong Clock type")

    #endif
}

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB  : SET_BIT(RCC_AHBENR  ,Copy_u8PerId);    break;
            case RCC_APB1 : SET_BIT(RCC_APB1ENR ,Copy_u8PerId);    break;
            case RCC_APB2 : SET_BIT(RCC_APB2ENR ,Copy_u8PerId);    break;
            //default       : /* Return Error */          break;
        }
    }

    else
    {
        /* Return Error */
    }
}


void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB  : CLR_BIT(RCC_AHBENR  ,Copy_u8PerId);    break;
            case RCC_APB1 : CLR_BIT(RCC_APB1ENR ,Copy_u8PerId);    break;
            case RCC_APB2 : CLR_BIT(RCC_APB2ENR ,Copy_u8PerId);    break;
            //default       : /* Return Error */          break;
        }
    }

    else
    {
        /* Return Error */
    }
}

