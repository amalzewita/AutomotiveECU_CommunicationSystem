#include "Timer2.h"

void TIMER2_Init() {
  SYSCTL_RCGCTIMER_R = (1<<2);
  while(!(GET_BIT(SYSCTL_PRTIMER_R,2)));
  TIMER2_CTL_R = 0;
  TIMER2_CFG_R = 0;
  TIMER2_TAMR_R = 2;
  TIMER2_TAILR_R = 16000-1;
  TIMER2_ICR_R = 1;
  TIMER2_CTL_R = 1;
}

void Delay_ms(uint32t milliseconds) {
    for (uint32t i = 0; i < milliseconds; i++) {
        TIMER2_ICR_R = 0x1;          // Clear the Timer0A timeout flag
        while ((TIMER2_RIS_R & 0x1) == 0); // Wait for timeout
    }
}