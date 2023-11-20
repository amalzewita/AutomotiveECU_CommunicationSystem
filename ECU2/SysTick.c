/***********************************************************************/
/*Module Name: Systick.c                                               */
/*Author: Team 6                                                       */
/*Purpose: Systick Source file                                         */
/***********************************************************************/
#include "TM4C123GH6PM.h"
#include "SysTick.h"

/************************************************************************/
/*                              Global Variables                        */
/************************************************************************/
unsigned int counter=0;         /*      Counter indicates ms passed     */
int flag=0;                     /*      Flag to indicate if ISR occured */


/***********************************************************************/
/*Function Name: SysTick_Setup_Second                                  */       
/*Inputs: Void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Initialize Systick to interrupt every 1ms               */                           
/***********************************************************************/
void SysTick_Setup_Second (void){
	/*      Initialize the SysTick Timer    */
        NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 16000 -1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x7;
}

/***********************************************************************/
/*Function Name: SysTick_Handler                                       */       
/*Inputs: Void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                            */
/*Description: Systick Interrupt Handler to increment counter          */      
/* and reset flag                                                      */                           
/***********************************************************************/
void SysTick_Handler (void){
  /*    Increment Counter       */
  counter++;
  if(counter>5001)
    counter=0;
  
  /*    Reset Flag              */
  flag=0;
}

