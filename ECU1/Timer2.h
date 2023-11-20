/***********************************************************************/
/*Module Name: Timer2.h                                                */
/*Author: Team 6                                                       */
/*Purpose: Timer2 header file                                          */
/***********************************************************************/

#ifndef _TIMER_2_
#define _TIMER_2_ 

#include "TM4C123GH6PM.h"
#include "STD_TYPES.h"
#include "BIT_MATHS.h"


 
/***********************************************************************/
/* Function Name: TIMER2_Init                                          */
/* Inputs: void                                                        */
/* Outputs: Void                                                       */
/* Reentrancy: Reentrant                                               */
/* Synchronous: Synchronous                                            */
/* Description: Initializes Timer 2 for specific configuration         */
/***********************************************************************/
void TIMER2_Init(void);


/***********************************************************************/
/* Function Name: Delay_ms                                             */
/* Inputs: uint32t milliseconds                                        */
/* Outputs: Void                                                       */
/* Reentrancy: Reentrant                                               */
/* Synchronous: Synchronous                                            */
/* Description: Introduces a delay in milliseconds using Timer 2       */
/***********************************************************************/
void Delay_ms(uint32t milliseconds);


#endif
