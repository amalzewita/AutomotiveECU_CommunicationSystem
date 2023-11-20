/***********************************************************************/
/*Module Name: main.c (ECU2)                                           */
/*Author: Team 6                                                       */
/*Purpose: main Source file                                            */
/***********************************************************************/
#include "TM4C123GH6PM.h"
#include "Port_Config.h"
#include "SysTick.h"
#include "scheduler.h"
#include "TM4C123GH6PM.h"
#include "SPI.h"


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

/* Enumeration for led State*/
typedef enum {
    WHITE=0,
    RED,
    GREEN,
    BLUE
      
} LEDState;

/************************************************************************/
/*                              Global Variables                        */
/************************************************************************/
LEDState StateLed = RED;                        /*      Variable for LED state  */
SYSTEM_State NextState = ANTI_CLOCKWISE;        /*      Next State from ECU1    */
SYSTEM_State CurrentState = ANTI_CLOCKWISE;     /*      Current State of ECU2   */
SYSTEM_State SendState = ANTI_CLOCKWISE;        /*      State to send to ECU1   */



/***********************************************************************/
/*Function Name: task_swicthSwitches                                   */       
/*Inputs: void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                             */
/*Description: Read Switches & Send Next State to ECU2 via SPI         */                           
/***********************************************************************/
void task_switchStates() {
    /*Turn RED LED if state is ERROR*/
    if(SendState == ERROR) {
    GPIO_WritePort(0x02);
  }
  
  else if(CurrentState == CLOCKWISE)    /*CLOCKWISE state*/
  {
    /*INCREMENT LED STATE*/
    if(StateLed==BLUE)
    {
      StateLed=RED;
    }
    else
    {
      StateLed++;
    }
    /*Switch for LED state*/
    switch (StateLed) {
        case WHITE:
          GPIO_WritePort(0x0E);
            break;
        case RED:
            GPIO_WritePort(0x02);
            break;
        case GREEN:
            GPIO_WritePort(0x08);
            break;
        case BLUE:
            GPIO_WritePort(0x04);
            break;
    }
  }
  else if(CurrentState == ANTI_CLOCKWISE)       /*ANTI_CLOCKWISE state*/
  {
    /*DECREMENT LED STATE*/
    if(StateLed==RED)
    {
      StateLed=BLUE;
    }
    else
    {
      StateLed--;
    }
    /*Switch for LED state*/
    switch (StateLed) {
        case WHITE:
          GPIO_WritePort(0x0E);
            break;
        case RED:
            GPIO_WritePort(0x02);
            break;
        case GREEN:
            GPIO_WritePort(0x08);
            break;
        case BLUE:
            GPIO_WritePort(0x04);
            break;
    }
  }
  else if(CurrentState == INITIAL)  {   /*INITIAL state*/
    GPIO_WritePort(0x02);
  }
  else if(CurrentState == IDLE)  {      /*IDLE state*/
    GPIO_WritePort(0x0E);
  }

  
}

/***********************************************************************/
/*Function Name: task_readState                                        */       
/*Inputs: void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                             */
/*Description: Read Switches & Send Next State to ECU2 via SPI         */                           
/***********************************************************************/
void task_readState(void)
{
  /* Set SendState as CurrentState*/
  SendState = CurrentState;
  
  /*ERROR DETECTING*/
  if(!(GPIO_ReadPin(0)) || !(GPIO_ReadPin(4)) || CurrentState > IDLE)
    SendState = ERROR;
    
  /*Send & Recieve*/
  for(int i=0;i<100;i++)
  {
      CurrentState = (SYSTEM_State)SPI_SendData(SSI0,SendState);
  }

}

 int main(void) {
    /*          GPIO INITIALIZATION             */
    GPIO_Init();
    
    /*          Enable Interrupt                */
    __asm(" CPSIE I");
    
    /*          Systick INITIALIZATION          */
    SysTick_Setup_Second();
    
    /*          SSI CONFIGURATION               */
    SSI_config strct = {SSI0,NONE,16,1000000,ONE_EDGE,LOW,FreeScale,_8_BIT};
    
    /*          SSI SLAVE INITIALIZATION       */
    Slave_Init(&strct);

    /*          TASKS INITIALIZATION            */
    task_init(task_switchStates, 1000);   
    task_init(task_readState,10);

    /*          RUN SCHEDULER                   */
    task_sched();

    return 0;
}

