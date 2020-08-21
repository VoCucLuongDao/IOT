#include "iwdg.h"

#define uwLsiFreq  40000

void iwdg_init(){
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: LSI/256 */
  IWDG_SetPrescaler(IWDG_Prescaler_256);

  /* Set counter reload value to obtain 250ms IWDG TimeOut.
     IWDG counter clock Frequency = LsiFreq/256
     Counter Reload Value = 64000ms/IWDG counter clock period
                          = 64s / (256/LsiFreq)
                          = LsiFreq/(256 /64)
                          = LsiFreq/4
   */
   
  IWDG_SetReload(uwLsiFreq/4);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
  }

void iwdg_reload(){
  IWDG_ReloadCounter();
}