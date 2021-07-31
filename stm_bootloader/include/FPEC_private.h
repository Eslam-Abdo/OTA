/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 18 July 2021                                                      */
/*********************************************************************************/
#ifndef FPEC_PRIVATE_H
#define FPEC_PRIVATE_H

#include "STD_TYPES.h"


typedef union
{
	struct{
		uint32  PG    :1 ;
		uint32  PER   :1 ;
		uint32  MER   :1 ;
		uint32  RES1  :1 ;
		uint32  OPTPG :1 ;
		uint32  OPTER :1 ;
		uint32  STRT  :1 ;
		uint32  LOCK  :1 ;
		uint32  RES2  :1 ;
		uint32  OPTWRE:1 ;
		uint32  ERRIE :1 ;
		uint32  RES3  :1 ;
		uint32  EOPIE :1 ;
		uint32  RES4  :19;
	}BitAccess;
	
	uint32 WordAccess;
}FPEC_CR_t;

#define FPEC_CR ((FPEC_CR_t*)0x40022010)


typedef struct {

	volatile uint32 ACR;
	volatile uint32 KEYR;
	volatile uint32 OPTKETR;
	volatile uint32 SR;
	volatile uint32 CR;
	volatile uint32 AR;
	volatile uint32	RESERVED;
	volatile uint32 OBR ;
	volatile uint32 WRPR   ;

}FPEC_t;

#define FPEC ( ( volatile FPEC_t* ) 0x40022000 )




#endif //FPEC_PRIVATE_H
