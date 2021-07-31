/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 31 July 2021                                                      */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "USART_INTERFACE.h"

#include "ESP8266_interface.h"
#include "FPEC_interface.h"

void Parser_voidParseRecord(uint8* Copy_u8BufData);
void clear_data(uint8* data_cleared);
void GetNewRecordLine(void);
void copy_pureData(void);

volatile uint8  u8RecBuffer[60] = {0}  ;
volatile uint8  u8RecCounter    = 0;
volatile uint8  u8TimeOutFlag   = 0;
volatile uint8  u8BLWriteReq    = 1;
uint8 data[60] ={0};
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

extern uint8 error;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08) 

	SCB_VTOR = 0x08002400;

	addr_to_call = *(Function_t*)(0x08002404);
	addr_to_call();
}

int main()
{
	RCC_voidInitSysClock(); /* Enable HSI */
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);  /*ENABLE PORTA AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN); /*ENABLE USART1 */
	RCC_voidEnableClock(RCC_AHB ,AHB_FLITF_EN); /*ENABLE FPEC */
	
	
	//RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);  /*ENABLE PORTB AS IO PINS*/
	//RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN); /*ENABLE USART3 */
	
	
	STK_voidInit();
	
	USART_voidInit(UART1,115200);
	
	//USART_voidInit(UART3,9600);
	
	ESP8266_voidResetESP();
	//ESP8266_voidConnectToWiFi("Islam","islam999");
	ESP8266_voidConnectToserver("192.168.1.11");
  ESP8266_voidSendData("192.168.1.11","53","http://192.168.1.11/upload_file/start_flash.php",data);
	GetNewRecordLine();
	STK_voidSetIntervalSingle((35*1000*1000),func); /* 35 sec */
	
	uint8 Local_u8RecStatus;
	
	//GetNewRecordLine();
	
	while(u8TimeOutFlag == 0)
	{
		clear_data(u8RecBuffer);
		
		if (data[2] == ':')
		{
			STK_voidStopInterval();
			
			copy_pureData();
		
			if (u8BLWriteReq == 1)
			{
				FPEC_voidEraseAppArea();
				u8BLWriteReq = 0;
			}
			
			/* Parse */
			Parser_voidParseRecord(u8RecBuffer);
			//USART_voidTransmit(UART3 ,u8RecBuffer,STRING);
			//USART_voidTransmit(UART3 ,"\n",STRING);
			GetNewRecordLine();
		}
		else
		{
			/* No file to burn */
		}
			
		STK_voidSetIntervalSingle((30*1000*1000),func); /* 5 sec */
			
	}
	
}


void clear_data(uint8* data_cleared)
{
	u8 LOC_u8Iterator1 = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 60 ; LOC_u8Iterator1++ ){

		data_cleared[ LOC_u8Iterator1 ] = 0 ;

	}
}

void GetNewRecordLine(void)
{
	if(error == 0)
	{
		clear_data(data);
		ESP8266_voidSendData("192.168.1.11","63","http://192.168.1.11/upload_file/start_flash.php?config=ok",data);
		
		while(strcmp(data,"") == 0)
		{
			ESP8266_voidResetESP();
			clear_data(data);
			ESP8266_voidConnectToserver("192.168.1.11");
			ESP8266_voidSendData("192.168.1.11","65","http://192.168.1.11/upload_file/start_flash.php?config=none",data);
		}
	}
}

void copy_pureData(void)
{
	while(u8RecBuffer[u8RecCounter] != '\n')
	{
		if (data[u8RecCounter+2] == '\r')
		{
			data[u8RecCounter+2] = '\n';
		}
		u8RecBuffer[u8RecCounter] = data[u8RecCounter+2];
		u8RecCounter ++ ;
	}
	u8RecCounter = 0;
}

