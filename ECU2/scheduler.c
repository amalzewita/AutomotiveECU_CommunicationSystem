/***********************************************************************/
/*Module Name: scheduler.c                                             */
/*Author: Team 6                                                       */
/*Purpose: scheduler Source file                                       */
/***********************************************************************/

#include "scheduler.h"

/************************************************************************/
/*                              Global Variables                        */
/************************************************************************/
task t_identifier;      /*      Temporary task variable to store task Data      */
task array[20];         /*      Array to store all tasks initialized            */
int task_i=0;           /*      Task index which also is number of tasks        */
int i=0;                /*      variable to store Systick counter value         */



/***********************************************************************/
/*Function Name: task_init                                             */       
/*Inputs: void (*p)(void) , int period                                 */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Asynchronous                                            */
/*Description: Initialize task into array for execution                */                           
/***********************************************************************/
void task_init(void (*p)(void),int period)
{
  /*Enter Inputs into temporary task variable*/
  t_identifier.pointer=p;
  t_identifier.period=period;
  
  /*Enter Task into array with index "task_i"*/
  array[task_i]=t_identifier;
  
  /*Increment task_i for next iteration of needed*/
  task_i++;
}


/***********************************************************************/
/*Function Name: task_sched                                            */       
/*Inputs: Void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Asynchronous                                            */
/*Description: Scheduler to loop through tasks                         */
/* and schedule task execution                                         */                           
/***********************************************************************/
void task_sched(void)
{
  /*    System Super Loop       */
  while(1)
  {
    
    i=counter;          /*      Store Systick Counter Value     */
    
    __asm(" CPSID I");  /*      Disable Interrupts              */
    
    if(i==0)            /*      Check if counter not equal 0    */
    {
    }
    else{
        if(flag==0)     /*      Check Flag is reset             */
        {
          /*    Loop on all tasks from task[0] -> task[task_i]*/
          for(int x=0;x<task_i;x++)
          {

            if(i%(array[x].period)==0)          /*      Check if each task's period has come    */
            {
              (*array[x].pointer)();            /*      Execute Task                            */
              counter++;
            }
          }
          flag=1;                               /*      Set Flag to avoid reentry                */
        }
    }

    
    __asm(" CPSIE I");                          /*      Re-enable interrupts for systick        */
    
  }
  
}
