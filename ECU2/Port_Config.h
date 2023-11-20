/***********************************************************************/
/*Module Name: Port_Config.h                                             */
/*Author: Team 6                                                       */
/*Purpose: Port_Config Header file                                       */
/***********************************************************************/

#ifndef __PORT_Configuration__
#define __PORT_Configuration__ 

#include "STD_TYPES.h"

/* GPIO Pins Configuration for LEDs */
#define RedLed   (1<<1)
#define BlueLed  (1<<2)
#define GreenLed (1<<3)

/***********************************************************************/
/* Function Name: GPIO_Init                                            */
/* Inputs: Void                                                        */
/* Outputs: Void                                                       */
/* Reentrancy: Reentrant                                                */
/* Synchronous: Synchronous                                             */
/* Description: Initializes GPIO pins for LEDs and switches.           */
/*              Configures Red, Blue, and Green LEDs as outputs.       */
/***********************************************************************/
void GPIO_Init(void);

/***********************************************************************/
/* Function Name: GPIO_ReadPin                                         */
/* Inputs: uint8_t PinNum                                              */
/* Outputs: uint8_t                                                     */
/* Reentrancy: Reentrant                                                */
/* Synchronous: Synchronous                                             */
/* Description: Reads the state of the specified GPIO pin.             */
/***********************************************************************/
uint8_t GPIO_ReadPin(uint8_t PinNum);

/***********************************************************************/
/* Function Name: GPIO_WritePort                                       */
/* Inputs: uint8_t Data                                                */
/* Outputs: Void                                                        */
/* Reentrancy: Reentrant                                                */
/* Synchronous: Synchronous                                             */
/* Description: Writes the specified data to the GPIO port.            */
/***********************************************************************/
void GPIO_WritePort(uint8_t Data);

#endif 
