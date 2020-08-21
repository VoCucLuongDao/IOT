#include "main.h"
#include "string.h"
#include "stdio.h"
#include "hsleep.h"
#include "hup.h"
#include "hbrocken.h"
#define wifi
extern char showtime[100];
extern char showdate[100];
extern uint16_t ADC_value;
extern char Buff[100];

uint16_t adc_max =0, adc_min =4096, hieudung_max =0;

uint8_t status_new = 0,status_current = 0;

uint8_t mode = 0, A = 0,B = 0, C = 0, out =0;

uint8_t *t, settime = 0;
char *setton="Lighton:23:00";
char *settoff="Lightoff:05:00";
char ton[100],toff[100];

uint8_t datetime[7];
uint8_t timecount;
char ttime[128];
char tdate[128];

char nhietdo[30];
  void main(){
  // uint 8_t
#ifdef wifi
   esp_01_init();
#endif
   Config_RTC();
   RTC_Settime(0x20,0x07,0x10,0x06-1,0x14,0x00,0x00);
   LCD_config();
   
   Config_Led();
   Config_Pin_Input();
   //Pin_interrup();
   ADC1_DMA_init();
 
   TIM3_Init();
   TIM5_Init();
   TIM2_Init();
   //iwdg_init();*/
   printf("okokk");
   while(1){
     
   #ifdef wifi
        if(strstr(Buff,"on@") != NULL){
            
            USART_Send_string(USART1,"AT+CIPSEND=3,6\r\n");
            delayms(100);
            mode = 1;
            status_new = 1;
            USART_Send_string(USART1,"ok|on@\r\n");
            delayms(100);
            printf(Buff);
            clear_Buff();
      }
      if(strstr(Buff,"off@") != NULL){
              USART_Send_string(USART1,"AT+CIPSEND=3,7\r\n");
              delayms(100);
              mode = 1;
              status_new = 0;
              USART_Send_string(USART1,"ok|off@\r\n");
              delayms(100);
              printf(Buff);
              clear_Buff();
      }
            if(strstr(Buff,"reset@") != NULL){
              mode = 0;
      }
       #endif
   }
 }

 void load_image(int count){
   LCD_SetRegion(24,0,103,79);
   switch(count){
   case 0:
 	for(u8 i=0;i<80;i++)
	{
 	    for(u8 j=0;j<80;j++)
	      {
 		LCD_WR_DATA2(hup[i][j]);
	      }
	}
          break;
   case 1:
 	for(u8 i=0;i<80;i++)
	{
 	    for(u8 j=0;j<80;j++)
	      {
 		LCD_WR_DATA2(hsleep[i][j]);
	      }
	}
          break;
   case 2:
 	for(u8 i=0;i<80;i++)
	{
 	    for(u8 j=0;j<80;j++)
	      {
 		LCD_WR_DATA2(hbrocken[i][j]);
	      }
	}
          break;
   }
 }
 
 void setC(){
        RTC_TimeTypeDef   RTC_TimeStructure;
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
      
        t = time_process(setton, settoff);
        u8 th = RTC_TimeStructure.RTC_Hours;
        u8 tm = RTC_TimeStructure.RTC_Minutes;
        if(dectobcd(th) == t[0] && dectobcd(tm) == t[1]) C=1;
        if(dectobcd(th) == t[2] && dectobcd(tm) == t[3]) C=0;
 }
 
 uint8_t time[4];
 uint8_t *time_process(char *timeon, char *timeoff){
   while(*timeon!=':'){ timeon++; }
      time[0] = ((u8)timeon[1] - 48)*16+((u8)timeon[2] - 48);
      time[1] = ((u8)timeon[4] - 48)*16+((u8)timeon[5] - 48);
   while(*timeoff!=':'){ timeoff++; }
      time[2] = ((u8)timeoff[1] - 48)*16+((u8)timeoff[2] - 48);
      time[3] = ((u8)timeoff[4] - 48)*16+((u8)timeoff[5] - 48);
      return time;
 }
 
int dem = 0;  //timer 1s nen chuyen dong phai lau hon 1s moi bat duoc
void TIM3_IRQHandler(void)      // sub = 2
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {     
    if(mode == 0){ 
        setC();     
        A = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
        B = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6); 
        //cam bien chuyen dong delay 20-22 s//
        switch(C){
        case 0:  out = A; //do sang trung binh
                 break;
        case 1:  out = B; //bat chuyen dong 1-3s...delay 15-18s
                 break;
        default: break;
       }
    }
       if(status_new != status_current & mode != 3){
          mode = 1;
          status_current = status_new;
          out = status_current;
          if(out == 0 ||mode == 3){
               GPIO_SetBits(GPIOE, GPIO_Pin_0);
#ifdef wifi
               delayms(2000);
               USART_Send_string(USART1,"AT+CIPSEND=2,8\r\n");
               delayms(100);
               USART_Send_string(USART1,"off|off@\r\n");
               delayms(100);
                clear_Buff();
#endif
            }
            if(out == 1 &&mode != 3){
               GPIO_ResetBits(GPIOE, GPIO_Pin_0);
#ifdef wifi
               delayms(2000);
               USART_Send_string(USART1,"AT+CIPSEND=2,6\r\n");
               delayms(100);
               USART_Send_string(USART1,"on|on@\r\n");
               delayms(100);
                clear_Buff();
#endif
            }
        }
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}



uint8_t mode_wake_up=0;
void RTC_Alarm_IRQHandler(void)  //sun=3
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
    mode_wake_up = 1;
    printf("OKOKOKOKOK");
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}

void DMA2_Stream0_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
    { 
      if(out == 1){
        if (ADC_value > adc_max) adc_max = ADC_value;
        if (ADC_value < adc_min) adc_min = ADC_value;
        } 
        DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);  
      }
}

 
void TIM5_IRQHandler(void)      // sub = 2
{
if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
{
       int hieudung = adc_max - adc_min ;
            adc_max = 0;
            adc_min = 4096;
            if(hieudung > hieudung_max) hieudung_max = hieudung;
            if(dem == 30) {
              /*  if(hieudung_max<200 & out == 1){
                       printf("bi mat dien (den hong roi!!!)");
                       mode =3;
                 }*/
           hieudung_max = 0;
           dem = 0;
        } 
        else dem++;
        
        
       TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    }
}

void TIM2_IRQHandler(void)      // sub = 2
{
if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
{  
       TimeShow();
       DateShow();
      // sprintf(nhietdo,"Nhiet do: %0.2f *C    ",get_temperature());
       sprintf(ton,"time on:  %0.2x:%0.2x:00",t[0],t[1]);
       sprintf(toff,"time off: %0.2x:%0.2x:00",t[2],t[3]);
       
     //  LCD_PutStr(5,98,nhietdo,BLACK,WHITE);
       LCD_PutStr(5,108,showtime,BLACK,WHITE);
       LCD_PutStr(5,118,showdate,BLACK,WHITE);
       LCD_PutStr(5,138,ton,BLACK,WHITE);
       LCD_PutStr(5,148, toff,BLACK,WHITE);
        
       TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}