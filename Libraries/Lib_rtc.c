#include "Lib_rtc.h"

__IO uint32_t uwAsynchPrediv = 0;
__IO uint32_t uwSynchPrediv = 0;
char date_week[7][10]={"CN","T2","T3","T4","T5","T6","T7"};

void Config_RTC()
{
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
  /* LSE used as RTC source clock*/
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  /* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
  uwSynchPrediv = 0xFF;
  uwAsynchPrediv = 0x7F;
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  /* Write to the first RTC Backup Data Register */
 // RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    
  RTC_InitTypeDef   RTC_InitStructure;
  RTC_TimeTypeDef   RTC_TimeStructure;
  RTC_DateTypeDef   RTC_DateStructure;
  
  RTC_InitStructure.RTC_AsynchPrediv = uwAsynchPrediv;
  RTC_InitStructure.RTC_SynchPrediv =  uwSynchPrediv;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  
  RTC_TimeStructure.RTC_Hours = 0x00;
  RTC_TimeStructure.RTC_Minutes = 0x00;
  RTC_TimeStructure.RTC_Seconds = 0x00;
  RTC_TimeStructInit(&RTC_TimeStructure);
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);  

  RTC_DateStructure.RTC_WeekDay = 0x01;
  RTC_DateStructure.RTC_Date = 0x01;
  RTC_DateStructure.RTC_Month = 0x01;  
  RTC_DateStructure.RTC_Year = 0x01; 
  RTC_DateStructInit(&RTC_DateStructure);
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure); 
  
  RTC_AlarmTypeDef RTC_AlarmStructure;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0x00;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_None; 
  RTC_AlarmStructure.RTC_AlarmDateWeekDay= 0x00;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel=RTC_AlarmDateWeekDaySel_Date;
  
  /* Configure the RTC Alarm A register */
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
 // RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);

  
  /* RTC Alarm A Interrupt Configuration */
  /* EXTI configuration *******************************************************/
  EXTI_ClearITPendingBit(EXTI_Line17); 
  EXTI_InitTypeDef  EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  NVIC_InitTypeDef  NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable RTC Alarm A Interrupt */
  RTC_ITConfig(RTC_IT_ALRA, DISABLE);
  /* Enable the alarm */
  RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
  
  RTC_ClearFlag(RTC_FLAG_ALRAF);
  Config_Led();
}

char showtime[50];
void TimeShow(void)
{
  RTC_TimeTypeDef   RTC_TimeStructure;
  /* Get the current Time */
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  /* Display time Format : hh:mm:ss */
  sprintf((char*)showtime,"Time: %0.2d:%0.2d:%0.2d",RTC_TimeStructure.RTC_Hours,
             RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
}

 char showdate[50];
void DateShow(void)
{
  RTC_DateTypeDef   RTC_DateStructure;
  /* Get the current Date */
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  /* Display date Format : hh:mm:ss */
  sprintf((char*)showdate,"Date: %s:%0.2d:%0.2d:%0.2d",date_week[RTC_DateStructure.RTC_WeekDay],
          RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Year);
}

 char showalarm[50];
void  AlarmShow(void)
{
  RTC_AlarmTypeDef RTC_AlarmStructure;
  /* Get the current Alarm */
  RTC_GetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
  sprintf((char*)showalarm,"Time: %0.2d:%0.2d:%0.2d", RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours,
          RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes, RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds);
}

void RTC_Settime(uint8_t yyyy, uint8_t mm, uint8_t dd, uint8_t wd, uint8_t h, uint8_t m, uint8_t s){
  RTC_TimeTypeDef   RTC_TimeStructure;
  RTC_DateTypeDef   RTC_DateStructure;
  
  /* Set Time hh:mm:ss */
  RTC_TimeStructure.RTC_Hours   = h;  
  RTC_TimeStructure.RTC_Minutes = m;
  RTC_TimeStructure.RTC_Seconds = s;
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

  /* Set Date Week/Date/Month/Year */
  RTC_DateStructure.RTC_WeekDay = wd;
  RTC_DateStructure.RTC_Date = dd;
  RTC_DateStructure.RTC_Month = mm;
  RTC_DateStructure.RTC_Year = yyyy;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
  
    /* Write BkUp DR0 */
  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
}

void setAlarm(u8 wd, u8 h , u8 m, u8 s){
  
  RTC_AlarmTypeDef RTC_AlarmStructure;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = s;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = m;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = h;
  RTC_AlarmStructure.RTC_AlarmDateWeekDay= wd;
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
}

