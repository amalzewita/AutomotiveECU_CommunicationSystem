/***********************************************************************/
/*Module Name: Port_Config.c                                             */
/*Author: Team 6                                                       */
/*Purpose: Port_Config Source file                                       */
/***********************************************************************/

#include "TM4C123GH6PM.h"
#include "Port_Config.h"
#include "STD_TYPES.h"
#include "BIT_MATHS.h"

/***********************************************************************/
/* Function Name: GPIO_Init                                             */
/* Inputs: Void                                                         */
/* Outputs: Void                                                        */
/* Reentrancy: Reentrant                                                */
/* Synchronous: Synchronous                                             */                                                     
/* Description: Initializes GPIO pins for LEDs and switches on Port F. */
/*              Sets LED pins as outputs and button pins as inputs with*/
/*              pull-ups.                                               */
/***********************************************************************/
void GPIO_Init(void) {
    /* Enable clock for GPIOF (LEDs and switches are on Port F)*/
    SYSCTL_RCGCGPIO_R |= 0x20;
    
    /* Unlock PORTF to allow write access to the GPIOCR register*/
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   /* Unlock PORTF*/
    
    /* Set LED pins as outputs*/
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x0E;

    /* Set button pins as inputs with pull-ups*/
    GPIO_PORTF_DIR_R &= ~(0x11);
    GPIO_PORTF_CR_R = 0x11;  /* Allow changes to PF4 and PF0*/
    GPIO_PORTF_PUR_R |= 0x11; /* Enable pull-up resistors for PF4 and PF0*/
    GPIO_PORTF_DEN_R |= 0x11;
}

/***********************************************************************/
/* Function Name: GPIO_ReadPin                                         */
/* Inputs: uint8_t PinNum                                              */
/* Outputs: uint8_t                                                     */
/* Reentrancy: Reentrant                                                */
/* Synchronous: Synchronous                                             */
/* Description: Reads the state of the specified GPIO pin on Port F.   */
/***********************************************************************/
uint8_t GPIO_ReadPin(uint8_t PinNum) {
  return GET_BIT(GPIO_PORTF_DATA_R, PinNum);
}

/***********************************************************************/
/* Function Name: GPIO_WritePort                                       */
/* Inputs: uint8_t Data                                                */
/* Outputs: Void                                                        */
/* Reentrancy: Reentrant                                                */
/* Synchronous: Synchronous                                             */
/* Description: Writes the specified data to the GPIO port on Port F.  */
/***********************************************************************/
void GPIO_WritePort(uint8_t Data) {
  GPIO_PORTF_DATA_R = Data;
}
