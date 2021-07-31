/*********************************************************************************/
/* Author    : Omar Lasheen                                                        */
/* Version   : V01                                                               */
/* Date      : 16 NOV 2020                                                       */
/*********************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BIT)        VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)        VAR &= ~(1 << (BIT))
#define GET_BIT(VAR,BIT)        ((VAR >> BIT) & 1  )
#define TOG_BIT(VAR,BIT)        VAR ^=  (1 << (BIT))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#endif // BIT_MATH_H
