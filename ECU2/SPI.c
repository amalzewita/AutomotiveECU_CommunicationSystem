/***********************************************************************/
/*Module Name: SPI.c                                                   */
/*Author: Team 6                                                       */
/*Purpose: SPI Source file                                             */
/***********************************************************************/

#include "TM4C123GH6PM.h"
#include "SPI.h"
#include "STD_TYPES.h"
#include "BIT_MATHS.h"


/***********************************************************************/
/*Function Name: Master_Init                                           */
/*Inputs: SSI_config* config_struct                                    */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Asynchronous                                             */
/*Description: Initialize SPI in master mode                           */                           
/***********************************************************************/
void Master_Init(SSI_config* config_struct){
  uint16_t SCR;
  
  /* Enable clock for the specified SPI module*/
  SET_BIT(SYSCTL_RCGCSSI_R, config_struct->number);
  

  
  
  switch(config_struct->number) {
    case SSI0:
      /* Enable clock for the GPIO port associated with SSI0*/
      SET_BIT(SYSCTL_RCGCGPIO_R, 0);
      
      /* Configure GPIO pins for SSI0*/
      GPIO_PORTA_AFSEL_R |= 0x3C;
      GPIO_PORTA_PCTL_R |= 0x00222200;
      GPIO_PORTA_DEN_R |= 0X3C;
      CLEAR_BIT(SSI0_CR1_R, 1); /* Disable SSI0 during configuration*/
      
      /* Set SSI0 as master, configure clock and data parameters*/
      SSI0_CR1_R = 0x0; /* Master operations*/
      SSI0_CC_R = 0x0; /* System Clock*/
      
      /* Calculate SCR value for the desired baud rate*/
      SCR = ((SYS_CLK) / ((config_struct->BR) * (config_struct->Prescale))) - 1;
      SSI0_CPSR_R = ((config_struct->Prescale) / 2) * 2;
      
      /* Configure SSI0 settings*/
      SSI0_CR0_R = (SCR << 8) | (SSI0_CR0_R & 0XFF);
      SSI0_CR0_R |= (config_struct->SPH) << 7;
      SSI0_CR0_R |= (config_struct->SPO) << 6;
      SSI0_CR0_R |= (config_struct->FRF) << 4;
      SSI0_CR0_R |= (config_struct->DSS);
      
      /* Enable SSI0*/
      SET_BIT(SSI0_CR1_R, 1);
      
      break;
      
    case SSI1:
    if(config_struct->port == PORTD_ID)
    {
    
    SYSCTL_RCGCGPIO_R |= (1<<3);
    
    GPIO_PORTD_AFSEL_R = 0x0F;
    GPIO_PORTD_PCTL_R =0x00002222;
    GPIO_PORTD_DEN_R = 0X0F;
    
    SSI1_CR1_R &= ~(1<<1);
    SSI1_CR1_R = 0x0; //Master operations
    
    SSI1_CC_R =0x0; //System Clock
    
    SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
    SSI1_CPSR_R = ((config_struct->Prescale) /2)*2;
    
    SSI1_CR0_R = (SCR << 8) | (SSI1_CR0_R & 0XFF);
    SSI1_CR0_R |=  (config_struct -> SPH) << 7;
    SSI1_CR0_R |=  (config_struct -> SPO) << 6;
    SSI1_CR0_R |=  (config_struct -> FRF) << 4;
    SSI1_CR0_R |=  (config_struct -> DSS);
    
    SSI1_CR1_R |= (1<<1); 
    }
    else if( config_struct-> port == PORTF_ID)
    {
    
    SYSCTL_RCGCGPIO_R |= (1<<5);
    GPIO_PORTF_AFSEL_R = 0x0F;
    GPIO_PORTF_PCTL_R =0x00002222;
    GPIO_PORTF_DEN_R = 0X0F;
    SSI1_CR1_R &= ~(1<<1);
    SSI1_CR1_R = 0x0; //Master operations
    SSI1_CC_R =0x0; //System Clock
    
    SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
    SSI1_CPSR_R = ((config_struct->Prescale) /2)*2;
    
    SSI1_CR0_R = (SCR << 8) | (SSI1_CR0_R & 0XFF);
    SSI1_CR0_R |=  (config_struct -> SPH) << 7;
    SSI1_CR0_R |=  (config_struct -> SPO) << 6;
    SSI1_CR0_R |=  (config_struct -> FRF) << 4;
    SSI1_CR0_R |=  (config_struct -> DSS);
    
    SSI1_CR1_R |= (1<<1);


    }   
    
    break;

  case SSI2:
  
    SYSCTL_RCGCGPIO_R |= (1<<1);    
    GPIO_PORTB_AFSEL_R = 0xF0;
    GPIO_PORTB_PCTL_R =0x22220000;
    GPIO_PORTB_DEN_R = 0XF0;
    SSI2_CR1_R &= ~(1<<1);
    SSI2_CR1_R = 0x0; //Master operations
    SSI2_CC_R =0x0; //System Clock
    
    SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
    SSI2_CPSR_R = ((config_struct->Prescale) /2)*2;
    
    SSI2_CR0_R = (SCR << 8) | (SSI2_CR0_R & 0XFF);
    SSI2_CR0_R |=  (config_struct -> SPH) << 7;
    SSI2_CR0_R |=  (config_struct -> SPO) << 6;
    SSI2_CR0_R |=  (config_struct -> FRF) << 4;
    SSI2_CR0_R |=  (config_struct -> DSS);
    
    SSI2_CR1_R |= (1<<1);
  
    break;
    
  case SSI3:

        SYSCTL_RCGCGPIO_R |= (1<<3);
        GPIO_PORTD_AFSEL_R = 0x0F;
        GPIO_PORTD_PCTL_R =0x00001111;
        GPIO_PORTD_DEN_R = 0X0F;
        SSI3_CR1_R &= ~(1<<1);
        SSI3_CR1_R = 0x0; //Master operations
        SSI3_CC_R =0x0; //System Clock

        SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
        SSI3_CPSR_R = ((config_struct->Prescale) /2)*2;
        
        SSI3_CR0_R = (SCR << 8) | (SSI3_CR0_R & 0XFF);
        SSI3_CR0_R |=  (config_struct -> SPH) << 7;
        SSI3_CR0_R |=  (config_struct -> SPO) << 6;
        SSI3_CR0_R |=  (config_struct -> FRF) << 4;
        SSI3_CR0_R |=  (config_struct -> DSS);
    
        SSI3_CR1_R |= (1<<1);

    
    break;
  }
}

/***********************************************************************/
/*Function Name: Slave_Init                                            */
/*Inputs: SSI_config* config_struct                                    */
/*Outputs: Void                                                        */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Asynchronous                                            */
/*Description: Initialize SPI in slave mode                            */   
/***********************************************************************/
void Slave_Init(SSI_config* config_struct){
  uint16_t SCR;
  
  /* Enable clock for the specified SPI module*/
  SYSCTL_RCGCSSI_R |= config_struct->number;
  
  switch(config_struct->number) {
    case SSI0:
      /* Enable clock for the GPIO port associated with SSI0*/
      SYSCTL_RCGCGPIO_R |= (1 << 0);
      
      /* Configure GPIO pins for SSI0*/
      GPIO_PORTA_AFSEL_R |= 0x3C;
      GPIO_PORTA_PCTL_R |= 0x00222200;
      GPIO_PORTA_DEN_R |= 0X3C;
      CLEAR_BIT(SSI0_CR1_R, 1); /* Disable SSI0 during configuration*/
      
      /* Set SSI0 as slave, configure clock and data parameters*/
      SSI0_CR1_R &= ~(1 << 1);
      SSI3_CR1_R = 0x4; /* Slave Output Enable*/
      SSI0_CC_R = 0x0; /* System Clock*/
      
      /* Calculate SCR value for the desired baud rate*/
      SCR = ((SYS_CLK) / ((config_struct->BR) * (config_struct->Prescale))) - 1;
      SSI0_CPSR_R = ((config_struct->Prescale) / 2) * 2;
      
      /* Configure SSI0 settings*/
      SSI0_CR0_R = (SCR << 8) | (SSI0_CR0_R & 0XFF);
      SSI0_CR0_R |= (config_struct->SPH) << 7;
      SSI0_CR0_R |= (config_struct->SPO) << 6;
      SSI0_CR0_R |= (config_struct->FRF) << 4;
      SSI0_CR0_R |= (config_struct->DSS);
      
      /* Enable SSI0*/
      SET_BIT(SSI0_CR1_R, 1);
      
      break;
      
    case SSI1:
    if(config_struct->port == PORTD_ID)
    {
    
    SYSCTL_RCGCGPIO_R |= (1<<3);
    
    GPIO_PORTD_AFSEL_R = 0x0F;
    GPIO_PORTD_PCTL_R =0x00002222;
    GPIO_PORTD_DEN_R = 0X0F;
    
    SSI1_CR1_R &= ~(1<<1);
    SSI1_CR1_R = 0x4; //Slave Output Enable
    
    SSI1_CC_R =0x0; //System Clock
    
    SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
    SSI1_CPSR_R = ((config_struct->Prescale) /2)*2;
    
    SSI1_CR0_R = (SCR << 8) | (SSI1_CR0_R & 0XFF);
    SSI1_CR0_R |=  (config_struct -> SPH) << 7;
    SSI1_CR0_R |=  (config_struct -> SPO) << 6;
    SSI1_CR0_R |=  (config_struct -> FRF) << 4;
    SSI1_CR0_R |=  (config_struct -> DSS);
    
    SSI1_CR1_R |= (1<<1);


   
    
    }
    else if( config_struct-> port == PORTF_ID)
    {
    
    SYSCTL_RCGCGPIO_R |= (1<<5);
    GPIO_PORTF_AFSEL_R = 0x0F;
    GPIO_PORTF_PCTL_R =0x00002222;
    GPIO_PORTF_DEN_R = 0X0F;
    SSI1_CR1_R &= ~(1<<1);
    SSI1_CR1_R = 0x4; //Slave Output Enable
    SSI1_CC_R =0x0; //System Clock
    
    SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
    SSI1_CPSR_R = ((config_struct->Prescale) /2)*2;
    
    SSI1_CR0_R = (SCR << 8) | (SSI1_CR0_R & 0XFF);
    SSI1_CR0_R |=  (config_struct -> SPH) << 7;
    SSI1_CR0_R |=  (config_struct -> SPO) << 6;
    SSI1_CR0_R |=  (config_struct -> FRF) << 4;
    SSI1_CR0_R |=  (config_struct -> DSS);
    
    SSI1_CR1_R |= (1<<1);

    } 
    break;
  case SSI2:
  
    SYSCTL_RCGCGPIO_R |= (1<<1);    
    GPIO_PORTB_AFSEL_R = 0xF0;
    GPIO_PORTB_PCTL_R =0x22220000;
    GPIO_PORTB_DEN_R = 0XF0;
    SSI2_CR1_R &= ~(1<<1);
    SSI2_CR1_R = 0x4; //Slave Output Enable
    SSI2_CC_R =0x0; //System Clock
    
    SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
    SSI2_CPSR_R = ((config_struct->Prescale) /2)*2;
    
    SSI2_CR0_R = (SCR << 8) | (SSI2_CR0_R & 0XFF);
    SSI2_CR0_R |=  (config_struct -> SPH) << 7;
    SSI2_CR0_R |=  (config_struct -> SPO) << 6;
    SSI2_CR0_R |=  (config_struct -> FRF) << 4;
    SSI2_CR0_R |=  (config_struct -> DSS);
    
    SSI2_CR1_R |= (1<<1);
  
    break;
    
  case SSI3:

        SYSCTL_RCGCGPIO_R |= (1<<3);
        GPIO_PORTD_AFSEL_R = 0x0F;
        GPIO_PORTD_PCTL_R =0x00001111;
        GPIO_PORTD_DEN_R = 0X0F;
        SSI3_CR1_R &= ~(1<<1);
        SSI3_CR1_R = 0x4; //Slave Output Enable
        SSI3_CC_R =0x0; //System Clock

        SCR= ((SYS_CLK)/((config_struct->BR)*(config_struct->Prescale)))-1;
        SSI3_CPSR_R = ((config_struct->Prescale) /2)*2;
        
        SSI3_CR0_R = (SCR << 8) | (SSI3_CR0_R & 0XFF);
        SSI3_CR0_R |=  (config_struct -> SPH) << 7;
        SSI3_CR0_R |=  (config_struct -> SPO) << 6;
        SSI3_CR0_R |=  (config_struct -> FRF) << 4;
        SSI3_CR0_R |=  (config_struct -> DSS);
    
        SSI3_CR1_R |= (1<<1);

    
    break;
  }
}

/***********************************************************************/
/*Function Name: SPI_SendData                                          */
/*Inputs: Enum , uint16_t                                              */
/*Outputs: uint16_t                                                    */
/*Reentrancy:  Reentrant                                               */
/*Synchronous: Asynchronous                                            */
/*Description: Send data over SPI in Master mode                       */   
/***********************************************************************/
uint16_t SPI_SendData(SSI_Num num, uint16_t data) {
  switch(num){
    case SSI0:
      while (!(GET_BIT(SSI0_SR_R, 1))); /* Wait until FIFO is empty*/
      SSI0_DR_R = data; /* Send data*/
      return SSI0_DR_R; /* Return received data*/
      break;

    case SSI1: 
      while (!(GET_BIT(SSI1_SR_R,1)));    
      SSI1_DR_R = data;     /* Send data*/
      break;
            
    case SSI2: 
      while (!(GET_BIT(SSI2_SR_R,1)));    
      SSI2_DR_R = data;    /* Send data*/
      break;
             
    case SSI3:        
      while (!(GET_BIT(SSI3_SR_R,1)));      
      SSI3_DR_R = data;    /* Send data*/
      break;
              
  }
  return 0;
}

