/***********************************************************************/
/*Module Name: UART.h                                                  */
/*Author: Team 6                                                       */
/*Purpose: UART Header file                                            */
/***********************************************************************/

/* Guard to prevent multiple inclusions of this header file */
#ifndef __UART_Configuration__
#define __UART_Configuration__

/* Including standard data types header */
#include "STD_TYPES.h"
/* Including bit operations header */
#include "BIT_MATHS.h"

/************************************************************************/
/*                              Definitions                             */
/************************************************************************/
/* System clock frequency in Hz */
#define SYS_CLK 16000000


/************************************************************************/
/*                              Type Definitions                        */
/************************************************************************/
/* Enumeration for UART numbers/modules */
typedef enum{
    UART0 = 0,  /* UART Module 0 */
    UART1,      /* UART Module 1 */
    UART2,      /* UART Module 2 */
    UART3,      /* UART Module 3 */
    UART4,      /* UART Module 4 */
    UART5,      /* UART Module 5 */
    UART6,      /* UART Module 6 */
    UART7,      /* UART Module 7 */
}UART_Num;

/* Enumeration for different base addresses of UART1 ports */
typedef enum{
    NONE_UART = 0,
    UART1_PB = 0x40005000, /* UART1 Port B base address */
    UART1_PC = 0x40006000, /* UART1 Port C base address */
}UART1_PORT;

/* Enumeration to define number of stop bits */
typedef enum{
    ONE_STOP_BIT = 0,   /* One stop bit */
    TWO_STOP_BITS       /* Two stop bits */
}UART_STP2;

/* Enumeration for parity configurations */
typedef enum{
    NO_PARITY = 0,      /* No parity */
    EVEN_PARITY,        /* Even parity */
    ODD_PARITY          /* Odd parity */
}UART_PARITY;

/* Enumeration for data word lengths */
typedef enum{
    _5_BIT_L = 0,   /* 5 bit data word length */
    _6_BIT_L,       /* 6 bit data word length */
    _7_BIT_L,       /* 7 bit data word length */
    _8_BIT_L        /* 8 bit data word length */
}UART_WLEN;

/* Enumeration for UART FIFO Enable */
typedef enum{
    FIFO_DISABLED = 0,  /* FIFOs are disabled */
    FIFO_ENABLED        /* FIFOs are enabled */
}UART_FEN;

/* Enumeration for UART Break */
typedef enum{
    BREAK_DISABLED = 0, /* UART Break is disabled */
    BREAK_ENABLED       /* UART Break is enabled */
}UART_BRK;

/* Structure for UART configuration parameters */
typedef struct{
    UART_Num number;       /* UART module number */
    UART1_PORT port;       /* UART port base address */
    uint32t baudRate;     /* Baud rate for UART communication */
    UART_PARITY SPS;       /* Stick Parity Select */
    UART_WLEN WLEN;        /* Word length */
    UART_FEN FEN;          /* FIFO Enable/Disable configuration */
    UART_STP2 STP2;        /* Number of stop bits configuration */
    UART_PARITY EPS;       /* Even parity select */
    UART_PARITY PEN;       /* Parity enable/disable */
    UART_BRK BRK;          /* UART Break enable/disable */
}UART_Config;

/***********************************************************************/
/*Function Name: UART_Init                                             */
/*Inputs: UART_Config* config                                          */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Initialize UART with given configuration                */   
/***********************************************************************/
void UART_Init(UART_Config* config);

/***********************************************************************/
/*Function Name: UART_SendData                                         */
/*Inputs: Enum, uint8_t                                                */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Send data over UART                                     */   
/***********************************************************************/
void UART_SendData(UART_Num mode, uint8_t data);

/***********************************************************************/
/*Function Name: UART_ReceiveData                                      */
/*Inputs: Enum                                                         */
/*Outputs: uint16_t                                                    */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Receive data from UART                                  */   
/***********************************************************************/
uint16_t UART_ReceiveData(UART_Num mode);

/***********************************************************************/
/*Function Name: UART_SendString                                       */
/*Inputs: Enum, const char                                             */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Synchronous                                            */
/*Description: Send a string over UART                                 */   
/***********************************************************************/
void UART_SendString(UART_Num uart_base_addr, const char *str);

#endif  /* Closing guard for header file */