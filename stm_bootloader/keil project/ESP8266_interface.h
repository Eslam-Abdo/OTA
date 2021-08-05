/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 9  MAY 2021                                                       */
/*********************************************************************************/

#ifndef ESP8266_INTERFACE_H
#define ESP8266_INTERFACE_H

#include "STD_TYPES.h"

#define ENABLE		1
#define DISABLE   0

void ESP8266_voidInit(void);

void ESP8266_voidConnectToWiFi(uint8* SSID , uint8 * Password );

/* input of fun is string with " "  */
void ESP8266_voidConnectToserver(uint8* IP);
void ESP8266_voidSendDataLength(uint8* local_u8DataLength); /* 	 add 5 for datalegth because "GET " + 1 */
void ESP8266_voidSendDataURL(uint8* local_u8DataURL);
void ESP8266_voidRecieveData( uint8* RecivedData);
void ESP8266_voidSendData(uint8* IP , uint8* local_u8DataLength, uint8* local_u8DataURL , uint8* RecivedData);

uint8 ESP8266_u8ValidateCmd(void);
void ESP8266_voidClearBuffer ( void );
void ESP8266_voidSendCmd(uint8* cmd);
 
/* to debug output */
void ESP8266_voidDebugOutput(uint8* local_u8DebugData); 

void ESP8266_voidResetESP(void);

#endif // ESP8266_INTERFACE_H
