#include "button.h"
#include "main.h"
extern uint8_t status_new, status_current;
extern uint8_t mode, settime, out;
void Config_Led()
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  
  GPIO_InitTypeDef GPIO_Initstructure;
  GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Initstructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Initstructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE,&GPIO_Initstructure);
  GPIO_SetBits(GPIOE,GPIO_Pin_0);
}

void Config_Pin_Input()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void Pin_interrup(){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_Init(GPIOD,&GPIO_InitStruct);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);
    
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 10;
    NVIC_Init(&NVIC_InitStruct);
  
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 10;
    NVIC_Init(&NVIC_InitStruct);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line4;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 10;
    NVIC_Init(&NVIC_InitStruct);
}

extern uint8_t datetime[7];
extern uint8_t timecount, settime;
extern char ttime[128];
extern char tdate[128];
uint8_t dectobcd(int x){
   int dv = (int)x%10;
   int ch = (int)(x-dv)/10*16;
   return  ch+dv;
}
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1))
    { 
        /*datetime[timecount-1]++;
        datetime[6]%=60;
        datetime[5]%=60;
        datetime[4]%=24;
        datetime[3]%=8;
        datetime[2]%=32;
        datetime[1]%=13;
        datetime[0]%=100;
        if( datetime[3]== 0) datetime[3] = 1;
        if( datetime[2]== 0) datetime[2] = 1;
        if( datetime[1]== 0) datetime[1] = 1;
        if( datetime[0]== 0) datetime[0] = 1;
      
        sprintf(ttime,"set date: %0.2d:%0.2d:%0.2d:%0.2d", 
        datetime[3],datetime[2],datetime[1],datetime[0]);
        sprintf(tdate,"set time: %0.2d:%0.2d:%0.2d",
                datetime[4],datetime[5],datetime[6]);
        LCD_PutStr(0,35,ttime,BLACK,WHITE);
        LCD_PutStr(0,50,tdate,BLACK,WHITE);
        
        RTC_Settime(dectobcd(datetime[0]), dectobcd(datetime[1]), dectobcd(datetime[2]), dectobcd(datetime[3]),
                    dectobcd(datetime[4]), dectobcd(datetime[5]), dectobcd(datetime[6]) );*/
      /***********************************************/
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2))
    { 
         settime = 1;
         timecount++;
              LCD_Clear(WHITE); 
              LCD_PutStr(5,20,"SETTING TIME",BLACK,WHITE);
              RTC_DateTypeDef   RTC_DateStructure;
              RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
              RTC_TimeTypeDef   RTC_TimeStructure;
              RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
              datetime[3] = RTC_DateStructure.RTC_WeekDay;
              datetime[2] = RTC_DateStructure.RTC_Date;
              datetime[1] = RTC_DateStructure.RTC_Month;
              datetime[0] = RTC_DateStructure.RTC_Year;
              datetime[4] = RTC_TimeStructure.RTC_Hours;
              datetime[5] = RTC_TimeStructure.RTC_Minutes;
              datetime[6] = RTC_TimeStructure.RTC_Seconds;
              
              sprintf(ttime,"set date: %0.2d:%0.2d:%0.2d:%0.2d", 
              datetime[3],datetime[2],datetime[1],datetime[0]);
              sprintf(tdate,"set time: %0.2d:%0.2d:%0.2d",
                      datetime[4],datetime[5],datetime[6]);
              LCD_PutStr(0,35,ttime,BLACK,WHITE);
              LCD_PutStr(0,50,tdate,BLACK,WHITE);
              
         if(timecount == 8){
              timecount = 0;
              settime = 0;   
              LCD_Clear(WHITE);
         }
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
u8 cnt;
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3))
    { 
      //cnt++;
       /// status_new = ~status_current;
      ///  out = ~out;
        delayms(100);
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line4))
    { 
         cnt++;
          mode =0;
          delayms(100);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}












