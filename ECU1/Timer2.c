/************************************************************************/
/*Module Name: Timer2.c                                                 */
/*Author: Team 6                                                        */
/*Purpose: Timer2 Source file                                           */
/************************************************************************/

#include "Timer2.h"  /* Include the Timer2 header file */

/***********************************************************************/
/* Function Name: TIMER2_Init                                          */
/* Inputs: void                                                        */
/* Outputs: Void                                                       */
/* Reentrancy: Reentrant                                               */
/* Synchronous: Synchronous                                            */
/* Description: Initializes Timer 2 for specific configuration         */
/***********************************************************************/
void TIMER2_Init() {
  SYSCTL_RCGCTIMER_R = (1 << 2);  /* Enable and provide a clock to Timer 2 */
  while (!(GET_BIT(SYSCTL_PRTIMER_R, 2)));  /* Wait until Timer 2 is ready */

  TIMER2_CTL_R = 0;  /* Disable Timer 2 during configuration */
  TIMER2_CFG_R = 0;  /* Set Timer 2 to a 32-bit configuration */
  TIMER2_TAMR_R = 2;  /* Set Timer 2 to operate in periodic mode */
  TIMER2_TAILR_R = 16000 - 1;  /* Set the load value for Timer 2 to achieve the desired delay */
  TIMER2_ICR_R = 1;  /* Clear the Timer 2A timeout flag */
  TIMER2_CTL_R = 1;  /* Enable Timer 2 */
}

/***********************************************************************/
/* Function Name: Delay_ms                                             */
/* Inputs: uint32t milliseconds                                        */
/* Outputs: Void                                                       */
/* Reentrancy: Reentrant                                               */
/* Synchronous: Synchronous                                             */
/* Description: Introduces a delay in milliseconds using Timer 2       */
/***********************************************************************/
void Delay_ms(uint32t milliseconds) {
    for (uint32t i = 0; i < milliseconds; i++) {
        TIMER2_ICR_R = 0x1;  /* Clear the Timer 2A timeout flag */
        while ((TIMER2_RIS_R & 0x1) == 0);  /* Wait for the timeout flag to be set */
    }
}
