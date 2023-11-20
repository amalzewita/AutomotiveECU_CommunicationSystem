/***********************************************************************/
/*Module Name: main.c (ECU1)                                           */
/*Author: Team 6                                                       */
/*Purpose: main Source file                                            */
/***********************************************************************/
#include "TM4C123GH6PM.h"
#include "Port_Config.h"
#include "SysTick.h"
#include "scheduler.h"
#include "TM4C123GH6PM.h"
#include "SPI.h"
#include "UART.h"
#include "Timer2.h"

/************************************************************************/
/*                              Definitions                             */
/************************************************************************/
#define TIMEOUT 200     /*      Time out number to check if 10 seconds passed*/


/************************************************************************/
/*                              Type Definitions                        */
/************************************************************************/
/* Enumeration for System State*/
typedef enum {
    ANTI_CLOCKWISE,
    CLOCKWISE,
    ERROR,
    INITIAL,
    IDLE
} SYSTEM_State;


/************************************************************************/
/*                              Global Variables                        */
/************************************************************************/
SYSTEM_State NextState = INITIAL;       /*      Next State to be sent to ECU2           */
SYSTEM_State CurrentState= INITIAL;     /*      Current State Recieved from ECU2        */
uint8_t count=0;                        /*      counter to increment for 10 sec check   */

/***********************************************************************/
/*Function Name: task_readSwitches                                     */       
/*Inputs: void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                             */
/*Description: Read Switches & Send Next State to ECU2 via SPI         */                           
/***********************************************************************/
void task_readSwitches() {
    if(!(GPIO_ReadPin(0)) && !(GPIO_ReadPin(4)))        /*      Check if both buttons pressed           */
    {
        Delay_ms(2);                                    /*      Debouncing                              */
        if(!(GPIO_ReadPin(0)) && !(GPIO_ReadPin(4))) 
        {
          NextState = INITIAL;                          /*      Set Next State to INITIAL               */
          count = 0;
        }
    } 
    else if(!(GPIO_ReadPin(4)))                         /*      Check if ANTICLOCKWISE button pressed   */
    { 
       Delay_ms(2);                                     /*      Debouncing                              */
       if(!(GPIO_ReadPin(4))) 
       { 
        NextState = ANTI_CLOCKWISE;                     /*      Set Next State to ANTI_CLOCKWISE        */
        count = 0;
       }
    } 
    else if(!(GPIO_ReadPin(0)))                         /*      Check if CLOCKWISE button pressed       */
    { 
        Delay_ms(2);                                    /*      Debouncing                              */
        if(!(GPIO_ReadPin(0)))
        { 
          NextState = CLOCKWISE;                        /*      Set Next State to CLOCKWISE             */
          count = 0;
         }
    } 
    else if (count>TIMEOUT)                             /*      Check if Timeout expired                */                       
    {  
        NextState = IDLE;                               /*      Set Next State to IDLE                  */
    } 
    if(NextState == CurrentState)
    {
      count++;                                          /*      Increment count if no state change happened*/
    }
    
    /*  Send Next State to ECU2 & Recieve Current State fromECU2        */
    CurrentState = (SYSTEM_State)SPI_SendData(SSI0,NextState);
}

/***********************************************************************/
/*Function Name: task_uartMessage                                      */       
/*Inputs: void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                             */
/*Description: Send String to serial monitor via UART                  */                           
/***********************************************************************/
void task_uartMessage(void)
{
  /*    Swicth for Current State        */
  switch(CurrentState) {
         case ANTI_CLOCKWISE:
            UART_SendString(UART0, "State: ANTI-CLOCKWISE\n");
            break;
        case CLOCKWISE:
            UART_SendString(UART0, "State: CLOCKWISE\n");
            break;
        case ERROR:
            UART_SendString(UART0, "State: ERROR 404 NOT FOUND\n");
            break;
        case IDLE:
            UART_SendString(UART0, "State: SIREN\n");
            break;
        case INITIAL:
            UART_SendString(UART0, "State: CODE RED\n");
            break;
        default:
            UART_SendString(UART0, "State: UNKNOWN\n");
            break;
    }
}




int main(void) {
    /*          GPIO INITIALIZATION             */
    GPIO_Init();
    
    /*          TIMER2 INITIALIZATION           */
    TIMER2_Init();
    
    /*          Enable Interrupt                */
    __asm(" CPSIE I");
    
    /*          Systick INITIALIZATION          */
    SysTick_Setup_Second();
    
    /*          SSI CONFIGURATION               */
    SSI_config strct = {SSI0,NONE,16,1000000,ONE_EDGE,LOW,FreeScale,_8_BIT};
    
    /*          UART CONFIGURATION              */
    UART_Config uart_strct ={UART0,NONE_UART,9600,NO_PARITY,_8_BIT_L,FIFO_DISABLED,ONE_STOP_BIT,NO_PARITY,NO_PARITY,BREAK_DISABLED};
    
    /*          UART INITIALIZATION             */
    UART_Init(&uart_strct);
    
    /*          SSI MASTER INITIALIZATION       */
    Master_Init(&strct);

    /*          TASKS INITIALIZATION            */
    task_init(task_uartMessage,500);
    task_init(task_readSwitches, 50);   

    /*          RUN SCHEDULER                   */
    task_sched();

    return 0;
}

