/***********************************************************************/
/*Module Name: SPI.h                                                   */
/*Author: Team 6                                                       */
/*Purpose: SPI Header file                                             */
/***********************************************************************/

#ifndef __SPI_Configuration__
#define __SPI_Configuration__ 

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
/************************************************************************/
/*                              Definitions                             */
/************************************************************************/
/* System clock frequency in Hz */
#define SYS_CLK 16000000


/************************************************************************/
/*                              Type Definitions                        */
/************************************************************************/
/* Enumeration for SPI module numbers*/
typedef enum {
  SSI0=0, SSI1, SSI2, SSI3
} SSI_Num;

/* Enumeration for SPI port options*/
typedef enum {
  NONE=0, PORTD_ID=0x08, PORTF_ID=0X20
} SSI1_PORT;

/* Enumeration for SPI clock edge options*/
typedef enum {
  ONE_EDGE=0, TWO_EDGE
} SSI_SPH;

/* Enumeration for SPI clock polarity options*/
typedef enum {
  LOW=0, HIGH
} SSI_SPO;

/* Enumeration for SPI frame format options*/
typedef enum {
  FreeScale=0, TEXAS, MICROWIRE
} SSI_FRF;

/* Enumeration for SPI data size options*/
typedef enum {
  _4_BIT=0X3, _5_BIT, _6_BIT, _7_BIT, _8_BIT, _9_BIT, _10_BIT, _11_BIT, _12_BIT, _13_BIT, _14_BIT, _15_BIT, _16_BIT
} SSI_DSS;

/* Structure to hold SPI configuration parameters*/
typedef struct {
  SSI_Num number;   /*  SSI Number                  */
  SSI1_PORT port;   /*  SS1 Port Number if Required */
  uint8_t Prescale; /*  Prescaler Value             */
  uint32t BR;     /*  Baud Rate                   */
  SSI_SPH SPH;      /* Clock Phase                  */
  SSI_SPO SPO;      /* Clock Polarity               */
  SSI_FRF FRF;      /* Frame Format                 */
  SSI_DSS DSS;      /* Data Size Select             */
} SSI_config;




/***********************************************************************/
/*Function Name: SPI_SendData                                          */
/*Inputs: Enum , uint16_t                                              */
/*Outputs: uint16_t                                                    */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Asynchronous                                            */
/*Description: Send data over SPI in Master mode                       */   
/***********************************************************************/
uint16_t SPI_SendData(SSI_Num mode, uint16_t data);

/***********************************************************************/
/*Function Name: Master_Init                                           */
/*Inputs: SSI_config* config_struct                                    */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Asynchronous                                             */
/*Description: Initialize SPI in master mode                           */                           
/***********************************************************************/
void Master_Init(SSI_config* config_struct);

/***********************************************************************/
/*Function Name: Slave_Init                                            */
/*Inputs: SSI_config* config_struct                                    */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Asynchronous                                            */
/*Description: Initialize SPI in slave mode                            */   
/***********************************************************************/
void Slave_Init(SSI_config* config_struct);

#endif
