#include "esp_01.h"
#include "main.h"

 char Buff[100];
 uint8_t index = 0;
 extern uint8_t status_new;
 
 void clear_Buff(){
   for(int i=0;i<100;i++){
     Buff[i]= 0;
   }
   index=0;
 }
 u8 khoitao = 0;
void esp_01_init()
{   
    khoitao = 0;
    USART1_init(115200);
    clear_Buff();
    printf("connnect...");
    while(1){
         USART_Send_string(USART1,"AT\r\n");
         delayms(1000);
         if(strstr(Buff,"OK")!= NULL) break;
    }
     index=0;
     
     USART_Send_string(USART1,"AT+RST\r\n");
     delayms(2000);
     while(strstr(Buff,"ready") == NULL && strstr(Buff,"Ai-Thinker Technology") == NULL);
     clear_Buff();
     
     USART_Send_string(USART1,"AT+CWMODE=1\r\n");
     delayms(1000);
     clear_Buff();
     
     /*USART_Send_string(USART1,"AT+CWJAP=\"Realme2\",\"12346789\"\r\n");// AT+CWJAP="Realme2","12346789" 
     delayms(2000);
     if(strstr(Buff,"OK")== NULL){
       printf("khong ket noi");
     }
     clear_Buff();*/
     
      USART_Send_string(USART1,"AT+CIPMUX=1\r\n");
      delayms(1000);
      while(strstr(Buff,"OK")==NULL);
      clear_Buff();
      
      USART_Send_string(USART1,"AT+CIPSTART=3,\"TCP\",\"192.168.43.120\",8899\r\n");//AT+CIPSTART=3,"TCP","192.168.43.1",8899
      delayms(1000);
      while(strstr(Buff,"OK")==NULL);
      clear_Buff();
 
      USART_Send_string(USART1,"AT+CIPSTART=2,\"TCP\",\"192.168.43.120\",8898\r\n");//AT+CIPSTART=3,"TCP","192.168.43.1",8899
      delayms(1000);
      while(strstr(Buff,"OK")==NULL);
      clear_Buff();
      
      USART_Send_string(USART1,"AT+CIPSEND=3,12\r\n");
      delayms(100);
      USART_Send_string(USART1,"ESP8266|off@\r\n");
      delayms(100);
      clear_Buff();
      
      khoitao = 1;
}

int chek_connect(){
      USART_Send_string(USART1,"AT+CIPSTATUS\r\n");
      delayms(1000);
      if(strstr(Buff,"Realme2")==NULL) return 0;
      return 1;
}

void USART1_IRQHandler(void){
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {   
      Buff[index] = USART_ReceiveData(USART1);
      index++;
      index %= 99;
      USART_ClearITPendingBit(USART1, USART_IT_RXNE);
   }

}
