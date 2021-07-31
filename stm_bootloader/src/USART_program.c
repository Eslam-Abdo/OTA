/*********************************************************************************/
/* Author    : Omar Lasheen                                                        */
/* Version   : V01                                                               */
/* Date      : 19 Jan 2021                                                       */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "USART_INTERFACE.h"
#include "USART_Config.h"
#include "GPIO_private.h"
#include "USART_PRIVATE.h"

#include "GPIO_private.h"
#include "RCC_CONFIG.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

void USART_voidInit(u8 Copy_u8uart, u32 Copy_u32BaudRate)
{
	
switch(Copy_u8uart)
{
	case UART1:
	
	GPIOA_CRH&=~0x00000FF0;
  GPIOA_CRH|= 0x000008B0; 	// RX1=input with pull-up, TX1=alt. func output
	GPIOA_ODR |= (1<<10);  //pull-up PA10
	
	USART1->CR1 = 0x200C; //enable uart,Tx,&Rx
	#if  RCC_CLOCK_TYPE  == RCC_HSI
	USART1->BRR = 8000000/Copy_u32BaudRate;	  // Fclk/bps 
	#elif RCC_CLOCK_TYPE  == RCC_PLL
	USART1->BRR = 72000000/Copy_u32BaudRate;	  // Fclk/bps 
	#endif
	
	break;
	case UART2:
	
	GPIOA_CRL&=~0x0000FF00;
  GPIOA_CRL|= 0x00008B00; 	// RX1=input with pull-up, TX1=alt. func output
	GPIOA_ODR |= (1<<3);  //pull-up PA3
	
	USART2->CR1 = 0x200C; //enable uart,Tx,&Rx
	#if  RCC_CLOCK_TYPE  == RCC_HSI
	USART2->BRR = 4000000/Copy_u32BaudRate;	  // Fclk/bps 
	#elif RCC_CLOCK_TYPE  == RCC_PLL
	USART2->BRR = 36000000/Copy_u32BaudRate;	  // Fclk/bps 
	#endif
	
	
	break;
  case UART3:
	
	
	GPIOB_CRH&=~0x0000FF00;
  GPIOB_CRH|= 0x00008B00; 	// RX1=input with pull-up, TX1=alt. func output
	GPIOB_ODR |= (1<<11);  //pull-up PA3
	
	USART3->CR1 = 0x200C; //enable uart,Tx,&Rx
	#if  RCC_CLOCK_TYPE  == RCC_HSI
	USART3->BRR = 4000000/Copy_u32BaudRate;	  // Fclk/bps 
	#elif RCC_CLOCK_TYPE  == RCC_PLL
	USART3->BRR = 36000000/Copy_u32BaudRate;	  // Fclk/bps 
	#endif
	
	
	
	break;
  default: break;
}


}
void USART_voidTransmit(u8 Copy_u8uart,void* Copy_u8data, u8 Copy_u8type){
  
	char array[16];

	u32 LOC_u32TimeOut = 0;

	switch(Copy_u8uart)
{
	case UART1:
	
	if(Copy_u8type == INT)
	{
	
  sprintf(array, "%d", *(int *)Copy_u8data);
	
	for(int i=0;(array[i]!='\0');i++)
	{
	while((USART1->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TXE flag is set 
	USART1->DR = array[i];
	LOC_u32TimeOut = 0;
	while((USART1->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
	}
  
	}
	else if(Copy_u8type == FLOAT)
	{
	
		float f1,f2;
		int i1,i2;
		f1=floor(*(float *)Copy_u8data);
		f2=(*(float *)Copy_u8data) - f1;
		i1 = (int)f1;
		i2 = (int)1000*f2;
		sprintf(array,"%d.%d", i1,i2);
	for(int i=0;(array[i]!='\0');i++)
	{
		while((USART1->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TXE flag is set 
	USART1->DR = array[i];
	LOC_u32TimeOut = 0;
	while((USART1->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
	}
  
	}
	else if(Copy_u8type == STRING)
	{
	 for(int i=0;*(char*)(Copy_u8data+i)!='\0';i++)
		{
			while((USART1->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TXE flag is set 
	USART1->DR = *(char*)(Copy_u8data+i);
	LOC_u32TimeOut = 0;
	while((USART1->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
		}
  }
	else if(Copy_u8type == CHAR)
	{
			   while((USART1->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TXE flag is set 
	USART1->DR = *(char*)(Copy_u8data);
	LOC_u32TimeOut = 0;
	while((USART1->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000 ){
	LOC_u32TimeOut++;
	}  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
	}
	break;
	
	
	case UART2:
	
	if(Copy_u8type == INT)
	{
	
  sprintf(array, "%d", *(int *)Copy_u8data);
	
	for(int i=0;(array[i]!='\0');i++)
	{
	while((USART2->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TXE flag is set 
	USART2->DR = array[i];
	LOC_u32TimeOut=0;
	while((USART2->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} //wait until the TC flag is set 
	USART2->SR &= ~(1<<6);
	}
  
	}
	else if(Copy_u8type == FLOAT)
	{
	
		float f1,f2;
		int i1,i2;
		f1=floor(*(float *)Copy_u8data);
		f2=(*(float *)Copy_u8data) - f1;
		i1 = (int)f1;
		i2 = (int)1000*f2;
		sprintf(array,"%d.%d", i1,i2);
	for(int i=0;(array[i]!='\0');i++)
	{
	while((USART2->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TXE flag is set 
	USART2->DR = array[i];
	LOC_u32TimeOut=0;
	while((USART2->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TC flag is set 
	USART2->SR &= ~(1<<6);
	
	}
  
	}
	else if(Copy_u8type == STRING)
	{
	 for(int i=0;*(char*)(Copy_u8data+i)!='\0';i++)
		{
	   while((USART2->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TXE flag is set 
	USART2->DR = *(char*)(Copy_u8data+i);
	LOC_u32TimeOut=0;
	while((USART2->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TC flag is set 
	USART2->SR &= ~(1<<6);
		}
  }
	else if(Copy_u8type == CHAR)
	{
			   while((USART2->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}   //wait until the TXE flag is set 
	USART2->DR = *(char*)(Copy_u8data);
	LOC_u32TimeOut=0;
	while((USART2->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}   //wait until the TC flag is set 
	USART2->SR &= ~(1<<6);
	}
	break;
	
		case UART3:
	
	if(Copy_u8type == INT)
	{
	
  sprintf(array, "%d", *(int *)Copy_u8data);
	
	for(int i=0;(array[i]!='\0');i++)
	{
	while((USART3->SR&(1<<7)) == 0  && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} //wait until the TXE flag is set 
	USART3->DR = array[i];
	LOC_u32TimeOut=0;
	while((USART3->SR&(1<<6)) == 0  && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} //wait until the TC flag is set 
	USART3->SR &= ~(1<<6);
	}
  
	}
	else if(Copy_u8type == FLOAT)
	{
	
		float f1,f2;
		int i1,i2;
		f1=floor(*(float *)Copy_u8data);
		f2=(*(float *)Copy_u8data) - f1;
		i1 = (int)f1;
		i2 = (int)1000*f2;
		sprintf(array,"%d.%d", i1,i2);
	for(int i=0;(array[i]!='\0');i++)
	{
	while((USART3->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TXE flag is set 
	USART3->DR = array[i];
	LOC_u32TimeOut=0;
	while((USART3->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} //wait until the TC flag is set 
	USART3->SR &= ~(1<<6);
	
	}
  
	}
	else if(Copy_u8type == STRING)
	{
	 for(int i=0;*(char*)(Copy_u8data+i)!='\0';i++)
		{
	   while((USART3->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TXE flag is set 
	USART3->DR = *(char*)(Copy_u8data+i);
	LOC_u32TimeOut=0;
	while((USART3->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TC flag is set 
	USART3->SR &= ~(1<<6);
		}
  }
	else if(Copy_u8type == CHAR)
	{
			   while((USART3->SR&(1<<7)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TXE flag is set 
	USART3->DR = *(char*)(Copy_u8data);
	LOC_u32TimeOut=0;
	while((USART3->SR&(1<<6)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}  //wait until the TC flag is set 
	USART3->SR &= ~(1<<6);
	}
	break;
		default:break;
} 

}
char USART_charReceive(u8 Copy_u8uart)
{
	u32 LOC_u32TimeOut=0;
switch(Copy_u8uart)
{
	case UART1:
	
	while((USART1->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}	//wait until the RXNE flag is set
	if (LOC_u32TimeOut ==100000){return 255;}
	return USART1->DR;
	break;
	
	case UART2:
	
	while((USART2->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}	//wait until the RXNE flag is set
	if (LOC_u32TimeOut ==100000){return 255;}
	return USART2->DR;
	break;
	
	case UART3:

	while((USART3->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}	//wait until the RXNE flag is set
	if (LOC_u32TimeOut ==100000){return 255;}
	return USART3->DR;
	break;
	
	default:
	return 0;	
	break;
}


}
void USART_voidReceiveString(u8 Copy_u8uart,char* Copy_charData,u8 Copy_u8Size){
u32 LOC_u32TimeOut=0;
	
switch(Copy_u8uart)
{
	case UART1:
	{
	unsigned char i = 0;
	unsigned char c;
	
	strcpy(Copy_charData,"");
	
		while((USART1->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}        //wait until the RXNE flag is set
	  Copy_charData[i] = USART1->DR;
	   i++;

	while (i < Copy_u8Size-1 ) {              // check space is available (including additional null char at end)
		while((USART1->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  c = USART1->DR;
		if (c == '\0') break;                   // break on NULL character
		Copy_charData[i] = c;                       // write into the supplied buffer
		i++;
	}
	Copy_charData[i] = '\0';                           // ensure string is null terminated

		
	break;
 }
	case UART2:
	{
	
	unsigned char i = 0;
	unsigned char c;
	
		strcpy(Copy_charData,"");
	while((USART2->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  Copy_charData[i] = USART2->DR;
	   i++;

	while (i < Copy_u8Size-1 ) {              // check space is available (including additional null char at end)
		while((USART2->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  c = USART2->DR;
		if (c == '\0') break;                   // break on NULL character
		Copy_charData[i] = c;                       // write into the supplied buffer
		i++;
	}
	Copy_charData[i] = '\0';                           // ensure string is null terminated

	
	
	break;
 }
	case UART3:
	{
	unsigned char i = 0;
	unsigned char c;
	
		strcpy(Copy_charData,"");
	
while((USART3->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  Copy_charData[i] = USART3->DR;
	   i++;

	while (i < Copy_u8Size-1 ) {              // check space is available (including additional null char at end)
	while((USART3->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  c = USART3->DR;
		if (c == '\0') break;                   // break on NULL character
		Copy_charData[i] = c;                       // write into the supplied buffer
		i++;
	}
	Copy_charData[i] = '\0';                           // ensure string is null terminated

	break;
 }
	default:
	break;
}

}

void USART_voidReceiveStringUntil(u8 Copy_u8uart,char* Copy_charData,char Copy_charLetter){

	u32 LOC_u32TimeOut=0;

	switch(Copy_u8uart)
{
	case UART1:
	{
		strcpy(Copy_charData,"");
	unsigned char i = 0;
	unsigned char a;
	
	  while((USART1->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;}         //wait until the RXNE flag is set
	  Copy_charData[i] = USART1->DR;
	   i++;
		
	if(Copy_charData[i]!=Copy_charLetter)
	{
		while (1) 
	{              	
	while((USART1->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	//wait until the RXNE flag is set
		a = USART1->DR;
		Copy_charData[i] = a;                       // write into the supplied buffer
		i++;
		if(a == Copy_charLetter)
		{
		break;
		}
	}
	
	}
	Copy_charData[i] = '\0';                           // ensure string is null terminated

	break;
 }
	case UART2:
	
		{
		strcpy(Copy_charData,"");
	unsigned char i = 0;
	unsigned char a;
	
	  while((USART2->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  Copy_charData[i] = USART2->DR;
	   i++;
		
	if(Copy_charData[i]!=Copy_charLetter)
	{
		while (1) 
	{              	
	while((USART2->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	//wait until the RXNE flag is set
		a = USART2->DR;
		Copy_charData[i] = a;                       // write into the supplied buffer
		i++;
		if(a == Copy_charLetter)
		{
		break;
		}
	}
	
	}
	Copy_charData[i] = '\0';                           // ensure string is null terminated

	break;
 }
	case UART3:
	{
		strcpy(Copy_charData,"");
	unsigned char i = 0;
	unsigned char a;
	
	  while((USART3->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	        //wait until the RXNE flag is set
	  Copy_charData[i] = USART3->DR;
	   i++;
		
	if(Copy_charData[i]!=Copy_charLetter)
	{
		while (1) 
	{              	
	while((USART3->SR&(1<<5)) == 0 && LOC_u32TimeOut<100000){LOC_u32TimeOut++;} 	//wait until the RXNE flag is set
		a = USART3->DR;
		Copy_charData[i] = a;                       // write into the supplied buffer
		i++;
		if(a == Copy_charLetter)
		{
		break;
		}
	}
	
	}
	Copy_charData[i] = '\0';                           // ensure string is null terminated

	break;
 }
	
	default:
	break;
}

}

