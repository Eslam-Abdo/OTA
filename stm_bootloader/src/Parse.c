/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 18 July 2021                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "FPEC_interface.h"

u16 Data[100] = {0};
u32 Address= 0x08000000;

uint8 AsciToHex(uint8 Copy_u8Asci)
{
	uint8 Result;
	if( (Copy_u8Asci >= '0') && (Copy_u8Asci <= '9'))
	{
		Result = Copy_u8Asci - '0';
	}
	else
	{
		Result = Copy_u8Asci - 'A' + 0X0A; /* 0xA = 10*/
	}
	return Result;
}


void ParseData(u8* Copy_u8BufData)
{
	uint8 DigitLow,DigitHigh,CC,i;
	uint8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	uint8 DataCounter = 0;
	
	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;
	
	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & 0xFFFF0000;
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);
	
	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4); /*  9102 = 02 91*/ 
		DataCounter++;
	}

	FPEC_voidFlashWrite(Address,Data,CC/2);
}




void ParseUpperAddress(u8* Copy_u8BufData)
{
	uint8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[9]);
	DataDigit1 = AsciToHex (Copy_u8BufData[10]);
	DataDigit2 = AsciToHex (Copy_u8BufData[11]);
	DataDigit3 = AsciToHex (Copy_u8BufData[12]);

	/* Clear High Part of Address */
	Address = Address & 0x0000FFFF;
	Address = Address | ((DataDigit0 << 28) | (DataDigit1 << 24) | (DataDigit2 << 20) | (DataDigit3 << 16));

}


void Parser_voidParseRecord(u8* Copy_u8BufData)
{
	switch (Copy_u8BufData[8])
	{
	case '0': ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); 
							break;
	default : break;
	}
}




