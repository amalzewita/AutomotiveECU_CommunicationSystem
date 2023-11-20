/***********************************************************************/
/*Module Name: Systick.h                                               */
/*Author: Team 6                                                       */
/*Purpose: Systick Header file                                         */
/***********************************************************************/
#ifndef __SysTick__
#define __SysTick__


#include "STD_TYPES.h"

/***********************************************************************/
/*Function Name: SysTick_Setup_Second                                  */       
/*Inputs: Void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Initialize Systick to interrupt every 1ms               */                           
/***********************************************************************/
void SysTick_Setup_Second (void);

#endif
