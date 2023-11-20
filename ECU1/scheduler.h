/***********************************************************************/
/*Module Name: scheduler.h                                             */
/*Author: Team 6                                                       */
/*Purpose: scheduler Header file                                       */
/***********************************************************************/
#ifndef __Scheduler__
#define __Scheduler__

/************************************************************************/
/*                              Extern Variables                        */
/************************************************************************/
extern int counter;     /*      Counter Value from Systick                      */
extern int flag;        /*      Flag from Systick to ensure interrupt occured   */

/************************************************************************/
/*                              Type Definitions                        */
/************************************************************************/
typedef struct{
  void (*pointer)(void);        /*      Pointer to function with void input & output    */
  int period;                   /*      Period which function executes in               */
}task;



/***********************************************************************/
/*Function Name: task_init                                             */       
/*Inputs: void (*p)(void) , int period                                 */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                            */
/*Description: Initialize task into array for execution                */                           
/***********************************************************************/
void task_sched(void);

/***********************************************************************/
/*Function Name: task_sched                                            */       
/*Inputs: Void                                                         */
/*Outputs: Void                                                        */
/*Reentrancy:  Non-Reentrant                                           */
/*Synchronous: Synchronous                                            */
/*Description: Scheduler to loop through tasks                         */
/* and schedule task execution                                         */                           
/***********************************************************************/
void task_init(void (*p)(void),int period);

#endif
