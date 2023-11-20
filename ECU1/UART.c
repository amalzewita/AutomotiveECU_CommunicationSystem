/***********************************************************************/
/*Module Name: SPI.c                                                   */
/*Author: Team 6                                                       */
/*Purpose: UART Header file                                            */
/***********************************************************************/

#include "TM4C123GH6PM.h"
#include "UART.h"
#include "STD_TYPES.h"
#include "BIT_MATHS.h"

/***********************************************************************/
/*Function Name: UART_Init                                             */
/*Inputs: UART_Config* config_struct                                   */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                            */
/*Description: Initialize UART                                         */   
/***********************************************************************/
/* This function initializes a UART master peripheral based on the settings specified in the passed configuration structure */
void UART_Init(UART_Config* config_struct) 
{
  uint16_t BRD;  /* Integer part of baud rate divisor */
  uint8_t FBRD;  /* Fractional part of baud rate divisor */

  /* Enable the UART module specified by the 'number' member in the config_struct */
  SET_BIT(SYSCTL_RCGCUART_R, config_struct -> number);

   /* Switch case to handle initialization based on the UART module number */
  switch(config_struct->number) 
  {
    case UART0:
        /* Enable clock for GPIO Port A, which UART0 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);
        
        /* Enable digital function for PA0 and PA1 */
        GPIO_PORTA_DEN_R   = 0x03;
        /* Enable alternate function for PA0 and PA1 (UART0 Rx and Tx pins) */
        GPIO_PORTA_AFSEL_R = 0x03;
        /* Set the alternate function for PA0 and PA1 to UART0 */
        GPIO_PORTA_PCTL_R  = 0x00000011; 

        /* Calculate the integer part of the baud rate divisor for 16MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART0 peripheral for configuration */
        CLEAR_BIT(UART0_CTL_R, 0);        

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART0_IBRD_R = BRD;
        UART0_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART0_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART0_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART0_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART0_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART0_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART0_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART0_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART0_CC_R   = 0x0; 

        /* Re-enable the UART0 peripheral after configuration */
        SET_BIT(UART0_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART0_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART0_CTL_R, 8);
        
        break;

      case UART1:
        if(config_struct->port == UART1_PB)
        {
          /* Enable clock for GPIO Port B, which UART1 pins are mapped to */
          SET_BIT(SYSCTL_RCGCGPIO_R, 0);

          /* Enable alternate function for PB0 and PB1 (UART1 Rx and Tx pins) */
          GPIO_PORTB_AFSEL_R = 0x03;
          /* Set the alternate function for PB0 and PB1 to UART1 */
          GPIO_PORTB_PCTL_R  = 0x00000011;
          /* Enable digital function for PB0 and PB1 */
          GPIO_PORTB_DEN_R   = 0x03;

          /* Calculate the integer part of the baud rate divisor for 16MHz clock */
          BRD = 16e6 / (16 * config_struct->baudRate);
          /* Calculate the fractional part of the baud rate divisor */
          FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

          /* Disable the UART1 peripheral for configuration */
          CLEAR_BIT(UART1_CTL_R, 0);

          /* Assign calculated baud rate divisors to the appropriate registers */
          UART1_IBRD_R = BRD;
          UART1_FBRD_R = FBRD;

          /* Configure the Line Control register based on the configuration structure */
          UART1_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
          UART1_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
          UART1_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
          UART1_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
          UART1_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
          UART1_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
          UART1_LCRH_R |=  (config_struct -> BRK);        /* Send break */

          /* Set the UART clock source as the system clock */
          UART1_CC_R   = 0x0; 

          /* Re-enable the UART1 peripheral after configuration */
          SET_BIT(UART1_CTL_R, 0);
          /* Enable transmitter */
          SET_BIT(UART1_CTL_R, 9);
          /* Enable receiver */
          SET_BIT(UART1_CTL_R, 8);

          break;
        }
        else if( config_struct-> port == UART1_PC)
        {
          /* Enable clock for GPIO Port C, which UART1 pins are mapped to */
          SET_BIT(SYSCTL_RCGCGPIO_R, 0);

          /* Enable alternate function for PC4 and PC5 (UART1 Rx and Tx pins) */
          GPIO_PORTC_AFSEL_R = 0x30;
          /* Set the alternate function for PC4 and PC5 to UART1 */
          GPIO_PORTC_PCTL_R  = 0x00220000;
          /* Enable digital function for PC4 and PC5 */
          GPIO_PORTC_DEN_R   = 0x30;

          /* Calculate the integer part of the baud rate divisor for 16MHz clock */
          BRD = 16e6 / (16 * config_struct->baudRate);
          /* Calculate the fractional part of the baud rate divisor */
          FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

          /* Disable the UART1 peripheral for configuration */
          CLEAR_BIT(UART1_CTL_R, 0);

          /* Assign calculated baud rate divisors to the appropriate registers */
          UART1_IBRD_R = BRD;
          UART1_FBRD_R = FBRD;

          /* Configure the Line Control register based on the configuration structure */
          UART1_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
          UART1_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
          UART1_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
          UART1_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
          UART1_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
          UART1_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
          UART1_LCRH_R |=  (config_struct -> BRK);        /* Send break */

          /* Set the UART clock source as the system clock */
          UART1_CC_R   = 0x0; 

          /* Re-enable the UART1 peripheral after configuration */
          SET_BIT(UART1_CTL_R, 0);
          /* Enable transmitter */
          SET_BIT(UART1_CTL_R, 9);
          /* Enable receiver */
          SET_BIT(UART1_CTL_R, 8);

          break;
        }

      case UART2:
        /* Enable clock for GPIO Port D, which UART2 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        /* Enable alternate function for PD6 and PD7 (UART2 Rx and Tx pins) */
        GPIO_PORTD_AFSEL_R = 0xC0;
        /* Set the alternate function for PD6 and PD7 to UART2 */
        GPIO_PORTD_PCTL_R  = 0x11000000;
        /* Enable digital function for PD6 and PD7 */
        GPIO_PORTD_DEN_R   = 0xC0;

        /* Calculate the integer part of the baud rate divisor for 16MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART2 peripheral for configuration */
        CLEAR_BIT(UART2_CTL_R, 0);

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART2_IBRD_R = BRD;
        UART2_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART2_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART2_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART2_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART2_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART2_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART2_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART2_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART2_CC_R   = 0x0; 

        /* Re-enable the UART2 peripheral after configuration */
        SET_BIT(UART2_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART2_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART2_CTL_R, 8);

        break;
      
      case UART3:
        /* Enable clock for GPIO Port C, which UART3 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        /* Enable alternate function for PC6 and PC7 (UART3 Rx and Tx pins) */
        GPIO_PORTC_AFSEL_R = 0xC0;
        /* Set the alternate function for PC6 and PC7 to UART3 */
        GPIO_PORTC_PCTL_R  = 0x11000000;
        /* Enable digital function for PC6 and PC7 */
        GPIO_PORTC_DEN_R   = 0xC0;

        /* Calculate the integer part of the baud rate divisor for 16MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART3 peripheral for configuration */
        CLEAR_BIT(UART3_CTL_R, 0);

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART3_IBRD_R = BRD;
        UART3_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART3_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART3_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART3_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART3_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART3_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART3_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART3_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART3_CC_R   = 0x0; 

        /* Re-enable the UART3 peripheral after configuration */
        SET_BIT(UART3_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART3_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART3_CTL_R, 8);

        break;

      case UART4:
        /* Enable clock for GPIO Port C, which UART4 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        /* Enable alternate function for PC4 and PC5 (UART4 Rx and Tx pins) */
        GPIO_PORTC_AFSEL_R = 0x30;
        /* Set the alternate function for PC4 and PC5 to UART4 */
        GPIO_PORTC_PCTL_R  = 0x00110000;
        /* Enable digital function for PC4 and PC5 */
        GPIO_PORTC_DEN_R   = 0x30;

        /* Calculate the integer part of the baud rate divisor for 16MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART4 peripheral for configuration */
        CLEAR_BIT(UART4_CTL_R, 0);

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART4_IBRD_R = BRD;
        UART4_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART4_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART4_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART4_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART4_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART4_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART4_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART4_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART4_CC_R   = 0x0; 

        /* Re-enable the UART4 peripheral after configuration */
        SET_BIT(UART4_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART4_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART4_CTL_R, 8);

        break;

      case UART5:
        /* Enable clock for GPIO Port E, which UART5 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        /* Enable alternate function for PE4 and PE5 (UART5 Rx and Tx pins) */
        GPIO_PORTE_AFSEL_R = 0x30;
        /* Set the alternate function for PE4 and PE5 to UART5 */
        GPIO_PORTE_PCTL_R  = 0x00110000;
        /* Enable digital function for PE4 and PE5 */
        GPIO_PORTE_DEN_R   = 0x30;

        /* Calculate the integer part of the baud rate divisor for 16MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART5 peripheral for configuration */
        CLEAR_BIT(UART5_CTL_R, 0);

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART5_IBRD_R = BRD;
        UART5_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART5_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART5_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART5_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART5_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART5_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART5_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART5_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART5_CC_R   = 0x0; 

        /* Re-enable the UART5 peripheral after configuration */
        SET_BIT(UART5_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART5_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART5_CTL_R, 8);

        break;

      case UART6:
        /* Enable clock for GPIO Port D, which UART6 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        /* Enable alternate function for PD4 and PD5 (UART6 Rx and Tx pins) */
        GPIO_PORTD_AFSEL_R = 0x30;
        /* Set the alternate function for PD4 and PD5 to UART6 */
        GPIO_PORTD_PCTL_R  = 0x00110000;
        /* Enable digital function for PD4 and PD5 */
        GPIO_PORTD_DEN_R   = 0x30;

        /* Calculate the integer part of the baud rate divisor for 16MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART6 peripheral for configuration */
        CLEAR_BIT(UART6_CTL_R, 0);

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART6_IBRD_R = BRD;
        UART6_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART6_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART6_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART6_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART6_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART6_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART6_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART6_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART6_CC_R   = 0x0; 

        /* Re-enable the UART6 peripheral after configuration */
        SET_BIT(UART6_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART6_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART6_CTL_R, 8);

        break;

      case UART7:
        /* Enable clock for GPIO Port E, which UART7 pins are mapped to */
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        /* Enable alternate function for PE0 and PE1 (UART7 Rx and Tx pins) */
        GPIO_PORTE_AFSEL_R = 0x03;
        /* Set the alternate function for PE0 and PE1 to UART7 */
        GPIO_PORTE_PCTL_R  = 0x00000011;
        /* Enable digital function for PE0 and PE1 */
        GPIO_PORTE_DEN_R   = 0x03;

        /* Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock */
        BRD = 16e6 / (16 * config_struct->baudRate);
        /* Calculate the fractional part of the baud rate divisor */
        FBRD = (uint8_t)((16e6 / (16.0 * config_struct->baudRate) - BRD) * 64 + 0.5);

        /* Disable the UART7 peripheral for configuration */
        CLEAR_BIT(UART7_CTL_R, 0);

        /* Assign calculated baud rate divisors to the appropriate registers */
        UART7_IBRD_R = BRD;
        UART7_FBRD_R = FBRD;

        /* Configure the Line Control register based on the configuration structure */
        UART7_LCRH_R |=  (config_struct -> SPS)  << 7;  /* Sticky parity select */
        UART7_LCRH_R |=  (config_struct -> WLEN) << 5;  /* Word length */
        UART7_LCRH_R |=  (config_struct -> FEN)  << 4;  /* FIFO enable */
        UART7_LCRH_R |=  (config_struct -> STP2) << 3;  /* Two stop bits select */
        UART7_LCRH_R |=  (config_struct -> EPS)  << 2;  /* Even parity select */
        UART7_LCRH_R |=  (config_struct -> PEN)  << 1;  /* Parity enable */
        UART7_LCRH_R |=  (config_struct -> BRK);        /* Send break */

        /* Set the UART clock source as the system clock */
        UART7_CC_R   = 0x0; 

        /* Re-enable the UART7 peripheral after configuration */
        SET_BIT(UART7_CTL_R, 0);
        /* Enable transmitter */
        SET_BIT(UART7_CTL_R, 9);
        /* Enable receiver */
        SET_BIT(UART7_CTL_R, 8);

        break;
  } 
}
/*
// This function initializes a UART slave peripheral based on the settings specified in the passed configuration structure
void UART_Slave_Init(UART_Config* config_struct) 
{
  uint16_t BRD;  // Integer part of baud rate divisor
  uint8_t FBRD;  // Fractional part of baud rate divisor

  // Enable the UART module specified by the 'number' member in the config_struct
  SET_BIT(SYSCTL_RCGCUART_R, config_struct -> number);

  // Switch case to handle initialization based on the UART module number 
  switch(config_struct->number) 
  {
    case UART0:
        // Enable clock for GPIO Port A, which UART0 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PA0 and PA1 (UART0 Rx and Tx pins)
        GPIO_PORTA_AFSEL_R = 0x03;
        // Set the alternate function for PA0 and PA1 to UART0
        GPIO_PORTA_PCTL_R  = 0x00000011;
        // Enable digital function for PA0 and PA1
        GPIO_PORTA_DEN_R   = 0x03;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART0 peripheral for configuration
        CLR_BIT(UART0_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART0_IBRD_R = BRD;
        UART0_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART0_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART0_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART0_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART0_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART0_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART0_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART0_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART0_CC_R   = 0x0; 

        // Re-enable the UART0 peripheral after configuration
        SET_BIT(UART0_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART0_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART0_CTL_R, 8);

        break;

      case UART1:
        if(config_struct->port == UART1_PB)
        {
          // Enable clock for GPIO Port B, which UART1 pins are mapped to
          SET_BIT(SYSCTL_RCGCGPIO_R, 0);

          // Enable alternate function for PB0 and PB1 (UART1 Rx and Tx pins)
          GPIO_PORTB_AFSEL_R = 0x03;
          // Set the alternate function for PB0 and PB1 to UART1
          GPIO_PORTB_PCTL_R  = 0x00000011;
          // Enable digital function for PB0 and PB1
          GPIO_PORTB_DEN_R   = 0x03;

          // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
          BRD = 20e6 / (16 * 115200);
          // Calculate the fractional part of the baud rate divisor
          FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

          // Disable the UART1 peripheral for configuration
          CLR_BIT(UART1_CTL_R, 0);

          // Assign calculated baud rate divisors to the appropriate registers
          UART1_IBRD_R = BRD;
          UART1_FBRD_R = FBRD;

          // Configure the Line Control register based on the configuration structure
          UART1_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
          UART1_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
          UART1_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
          UART1_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
          UART1_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
          UART1_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
          UART1_LCRH_R |=  (config_struct -> BRK);        // Send break

          // Set the UART clock source as the system clock
          UART1_CC_R   = 0x0; 

          // Re-enable the UART0 peripheral after configuration
          SET_BIT(UART1_CTL_R, 0);
          // Enable transmitter
          SET_BIT(UART1_CTL_R, 9);
          // Enable receiver
          SET_BIT(UART1_CTL_R, 8);

          break;
        }
        else if( config_struct-> port == UART1_PC)
        {
        
          // Enable clock for GPIO Port C, which UART1 pins are mapped to
          SET_BIT(SYSCTL_RCGCGPIO_R, 0);

          // Enable alternate function for PC4 and PC5 (UART1 Rx and Tx pins)
          GPIO_PORTC_AFSEL_R = 0x30;
          // Set the alternate function for PC4 and PC5 to UART1
          GPIO_PORTC_PCTL_R  = 0x00220000;
          // Enable digital function for PC4 and PC5
          GPIO_PORTC_DEN_R   = 0x30;

          // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
          BRD = 20e6 / (16 * 115200);
          // Calculate the fractional part of the baud rate divisor
          FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

          // Disable the UART1 peripheral for configuration
          CLR_BIT(UART1_CTL_R, 0);

          // Assign calculated baud rate divisors to the appropriate registers
          UART1_IBRD_R = BRD;
          UART1_FBRD_R = FBRD;

          // Configure the Line Control register based on the configuration structure
          UART1_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
          UART1_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
          UART1_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
          UART1_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
          UART1_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
          UART1_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
          UART1_LCRH_R |=  (config_struct -> BRK);        // Send break

          // Set the UART clock source as the system clock
          UART1_CC_R   = 0x0; 

          // Re-enable the UART1 peripheral after configuration
          SET_BIT(UART1_CTL_R, 0);
          // Enable transmitter
          SET_BIT(UART1_CTL_R, 9);
          // Enable receiver
          SET_BIT(UART1_CTL_R, 8);

          break;
        }

      case UART2:
        // Enable clock for GPIO Port D, which UART2 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PD6 and PD7 (UART2 Rx and Tx pins)
        GPIO_PORTD_AFSEL_R = 0xC0;
        // Set the alternate function for PD6 and PD7 to UART2
        GPIO_PORTD_PCTL_R  = 0x11000000;
        // Enable digital function for PD6 and PD7
        GPIO_PORTD_DEN_R   = 0xC0;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART2 peripheral for configuration
        CLR_BIT(UART2_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART2_IBRD_R = BRD;
        UART2_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART2_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART2_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART2_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART2_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART2_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART2_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART2_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART2_CC_R   = 0x0; 

        // Re-enable the UART2 peripheral after configuration
        SET_BIT(UART2_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART2_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART2_CTL_R, 8);

        break;
      
      case UART3:
        // Enable clock for GPIO Port C, which UART3 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PC6 and PC7 (UART3 Rx and Tx pins)
        GPIO_PORTC_AFSEL_R = 0xC0;
        // Set the alternate function for PC6 and PC7 to UART3
        GPIO_PORTC_PCTL_R  = 0x11000000;
        // Enable digital function for PC6 and PC7
        GPIO_PORTC_DEN_R   = 0xC0;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART3 peripheral for configuration
        CLR_BIT(UART3_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART3_IBRD_R = BRD;
        UART3_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART3_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART3_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART3_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART3_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART3_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART3_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART3_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART3_CC_R   = 0x0; 

        // Re-enable the UART3 peripheral after configuration
        SET_BIT(UART3_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART3_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART3_CTL_R, 8);

        break;

      case UART4:
        // Enable clock for GPIO Port C, which UART4 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PC4 and PC5 (UART4 Rx and Tx pins)
        GPIO_PORTC_AFSEL_R = 0x30;
        // Set the alternate function for PC4 and PC5 to UART4
        GPIO_PORTC_PCTL_R  = 0x00110000;
        // Enable digital function for PC4 and PC5
        GPIO_PORTC_DEN_R   = 0x30;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART4 peripheral for configuration
        CLR_BIT(UART4_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART4_IBRD_R = BRD;
        UART4_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART4_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART4_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART4_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART4_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART4_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART4_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART4_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART4_CC_R   = 0x0; 

        // Re-enable the UART4 peripheral after configuration
        SET_BIT(UART4_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART4_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART4_CTL_R, 8);

        break;

      case UART5:
        // Enable clock for GPIO Port E, which UART5 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PE4 and PE5 (UART5 Rx and Tx pins)
        GPIO_PORTE_AFSEL_R = 0x30;
        // Set the alternate function for PE4 and PE5 to UART5
        GPIO_PORTE_PCTL_R  = 0x00110000;
        // Enable digital function for PE4 and PE5
        GPIO_PORTE_DEN_R   = 0x30;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART5 peripheral for configuration
        CLR_BIT(UART5_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART5_IBRD_R = BRD;
        UART5_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART5_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART5_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART5_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART5_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART5_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART5_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART5_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART5_CC_R   = 0x0; 

        // Re-enable the UART5 peripheral after configuration
        SET_BIT(UART5_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART5_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART5_CTL_R, 8);

        break;

      case UART6:
        // Enable clock for GPIO Port D, which UART6 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PD4 and PD5 (UART6 Rx and Tx pins)
        GPIO_PORTD_AFSEL_R = 0x30;
        // Set the alternate function for PD4 and PD5 to UART6
        GPIO_PORTD_PCTL_R  = 0x00110000;
        // Enable digital function for PD4 and PD5
        GPIO_PORTD_DEN_R   = 0x30;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART6 peripheral for configuration
        CLR_BIT(UART6_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART6_IBRD_R = BRD;
        UART6_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART6_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART6_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART6_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART6_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART6_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART6_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART6_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART6_CC_R   = 0x0; 

        // Re-enable the UART6 peripheral after configuration
        SET_BIT(UART6_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART6_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART6_CTL_R, 8);

        break;

      case UART7:
        // Enable clock for GPIO Port E, which UART7 pins are mapped to
        SET_BIT(SYSCTL_RCGCGPIO_R, 0);

        // Enable alternate function for PE0 and PE1 (UART7 Rx and Tx pins)
        GPIO_PORTE_AFSEL_R = 0x03;
        // Set the alternate function for PE0 and PE1 to UART7
        GPIO_PORTE_PCTL_R  = 0x00000011;
        // Enable digital function for PE0 and PE1 
        GPIO_PORTE_DEN_R   = 0x03;

        // Calculate the integer part of the baud rate divisor for a 115200 baud rate and 20MHz clock
        BRD = 20e6 / (16 * 115200);
        // Calculate the fractional part of the baud rate divisor
        FBRD = (uint8_t)((20e6 / (16 * 115200.0) - BRD) * 64 + 0.5);

        // Disable the UART7 peripheral for configuration
        CLR_BIT(UART7_CTL_R, 0);

        // Assign calculated baud rate divisors to the appropriate registers
        UART7_IBRD_R = BRD;
        UART7_FBRD_R = FBRD;

        // Configure the Line Control register based on the configuration structure
        UART7_LCRH_R |=  (config_struct -> SPS)  << 7;  // Sticky parity select
        UART7_LCRH_R |=  (config_struct -> WLEN) << 5;  // Word length
        UART7_LCRH_R |=  (config_struct -> FEN)  << 4;  // FIFO enable
        UART7_LCRH_R |=  (config_struct -> STP2) << 3;  // Two stop bits select
        UART7_LCRH_R |=  (config_struct -> EPS)  << 2;  // Even parity select
        UART7_LCRH_R |=  (config_struct -> PEN)  << 1;  // Parity enable
        UART7_LCRH_R |=  (config_struct -> BRK);        // Send break

        // Set the UART clock source as the system clock
        UART7_CC_R   = 0x0; 

        // Re-enable the UART7 peripheral after configuration
        SET_BIT(UART7_CTL_R, 0);
        // Enable transmitter
        SET_BIT(UART7_CTL_R, 9);
        // Enable receiver
        SET_BIT(UART7_CTL_R, 8);

        break;
  } 
}
*/
/***********************************************************************/
/*Function Name: UART_SendData                                         */
/*Inputs: Enum , uint8_t                                               */
/*Outputs: void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Send data over UART                                     */   
/***********************************************************************/
void UART_SendData(UART_Num mode, uint8_t data) 
{
    /* Switch based on the UART module specified */
    switch(mode)
    {
      /* UART0 case */
      case UART0:
          /* Wait until the transmit FIFO for UART0 is not full */
          while ( (UART0_FR_R & (1<<5)) != 0 );
          /* Load the data into the UART0 data register to send it */
          UART0_DR_R = data;
          break;
      
      /* UART1 case */
      case UART1:
          /* Wait until the transmit FIFO for UART1 is not full */
          while ( (UART1_FR_R & (1<<5)) != 0 );
          /* Load the data into the UART1 data register to send it */
          UART1_DR_R = data;
          break;

      /* UART2 case */
      case UART2:
          /* Wait until the transmit FIFO for UART2 is not full */
          while ( (UART2_FR_R & (1<<5)) != 0 );
          /* Load the data into the UART2 data register to send it */
          UART2_DR_R = data;
          break;

      /* UART3 case */
      case UART3:
          /* Wait until the transmit FIFO for UART3 is not full */
          while ( (UART3_FR_R & (1<<5)) != 0 );
          /* Load the data into the UART3 data register to send it */
          UART3_DR_R = data;
          break;

        /* UART4 case */
        case UART4:
            /* Wait until the transmit FIFO for UART4 is not full */
            while ( (UART4_FR_R & (1<<5)) != 0 );
            /* Load the data into the UART4 data register to send it */
            UART4_DR_R = data;
            break;

        /* UART5 case */
        case UART5:
            /* Wait until the transmit FIFO for UART5 is not full */
            while ( (UART5_FR_R & (1<<5)) != 0 );
            /* Load the data into the UART5 data register to send it */
            UART5_DR_R = data;
            break;

        /* UART6 case */
        case UART6:
            /* Wait until the transmit FIFO for UART6 is not full */
            while ( (UART6_FR_R & (1<<5)) != 0 );
            /* Load the data into the UART6 data register to send it */
            UART6_DR_R = data;
            break;

        /* UART7 case */
        case UART7: 
            /* Wait until the transmit FIFO for UART7 is not full */
            while ( (UART7_FR_R & (1<<5)) != 0 );
            /* Load the data into the UART7 data register to send it */
            UART7_DR_R = data;
            break;
    }
}

/***********************************************************************/
/*Function Name: UART_ReceiveData                                      */
/*Inputs: Enum                                                         */
/*Outputs: uint16_t                                                    */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Receive data over UART                                  */   
/***********************************************************************/
uint16_t UART_ReceiveData(UART_Num mode) 
{
    switch(mode) 
    {
        /* UART0 case */
        case UART0:
            /* Wait until the receive FIFO for UART0 has data (is not empty) */
            while ( (UART0_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART0 data register */
            return (uint8_t)UART0_DR_R;
            break;

        /* UART1 case */
        case UART1:
            /* Wait until the receive FIFO for UART1 has data (is not empty) */
            while ( (UART1_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART1 data register */
            return (uint8_t)UART1_DR_R;
            break;

        /* UART2 case */
        case UART2:
            /* Wait until the receive FIFO for UART2 has data (is not empty) */
            while ( (UART2_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART2 data register */
            return (uint8_t)UART2_DR_R;
            break;

        /* UART3 case */
        case UART3:
            /* Wait until the receive FIFO for UART3 has data (is not empty) */
            while ( (UART3_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART3 data register */
            return (uint8_t)UART3_DR_R;
            break;

        /* UART4 case */
        case UART4:
            /* Wait until the receive FIFO for UART4 has data (is not empty) */
            while ( (UART4_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART4 data register */
            return (uint8_t)UART4_DR_R;
            break;

        /* UART5 case */
        case UART5:
            /* Wait until the receive FIFO for UART5 has data (is not empty) */
            while ( (UART5_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART5 data register */
            return (uint8_t)UART5_DR_R;
            break;

        /* UART6 case */
        case UART6:
            /* Wait until the receive FIFO for UART6 has data (is not empty) */
            while ( (UART6_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART6 data register */
            return (uint8_t)UART6_DR_R;
            break;
            
        /* UART7 case */
        case UART7:
            /* Wait until the receive FIFO for UART7 has data (is not empty) */
            while ( (UART7_FR_R & (1<<4)) != 0 );
            /* Read the data from the UART7 data register */
            return (uint8_t)UART7_DR_R;
            break;
    }
}

/***********************************************************************/
/*Function Name: UART_SendString                                          */
/*Inputs: Enum , const char                                            */
/*Outputs: void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Send string of data over UART                           */   
/***********************************************************************/
void UART_SendString(UART_Num uart_base_addr, const char *str) {
    while(*str != '\0') {  /* Loop until end of string */
      UART_SendData(uart_base_addr, *str); /* Send the current character */
      str++; /* Move to next character     */
    }
}
