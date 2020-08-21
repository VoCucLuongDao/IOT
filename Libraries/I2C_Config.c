#include "I2C_Config.h"

 volatile uint32_t Event = 0,even = 0;
 volatile uint8_t Tx_Idx;
 volatile uint8_t Rx_Idx;
 extern uint8_t SlaveTxBuffer[];
 extern uint8_t SlaveRxBuffer[];
 
void I2C_Config()
{
   GPIO_InitTypeDef GPIO_InitStructure;
   I2C_InitTypeDef I2C_InitStructure;
   NVIC_InitTypeDef NVIC_InitStructure;
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOB, &GPIO_InitStructure);

 GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_I2C1); 
 GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_I2C1); 
 GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_I2C2); 
 GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_I2C2); 

/***************************Master ******************/
 /* I2C De-initialize */
 I2C_DeInit(I2C1);
 I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
 I2C_InitStructure.I2C_DutyCycle = I2C_DUTYCYCLE;
 I2C_InitStructure.I2C_OwnAddress1 = 0x01;
 I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
 I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
 I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
 I2C_Init(I2C1, &I2C_InitStructure);
 /* I2C ENABLE */
 I2C_Cmd(I2C1, ENABLE);
 I2C_AcknowledgeConfig(I2C1,ENABLE);

 /* Enable Interrupt */
 //I2C_ITConfig(I2C1, (I2C_IT_ERR ) , ENABLE);
 //I2C_ITConfig(I2C1, (I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF) , ENABLE);
 /************************************* Slave ******************************/
 /* I2C De-initialize */
 I2C_DeInit(I2C2);
 I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
 I2C_InitStructure.I2C_DutyCycle = I2C_DUTYCYCLE;
 I2C_InitStructure.I2C_OwnAddress1 = Slave_Address;
 I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
 I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
 I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
 I2C_Init(I2C2, &I2C_InitStructure);
 /* I2C ENABLE */
 I2C_Cmd(I2C2, ENABLE);
 /* Enable Interrupt */
 I2C_ITConfig(I2C2, (I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF) , ENABLE);

 NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn|I2C2_ER_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
 }

 void I2C2_ER_IRQHandler(void)
{
 /* Check on I2C2 AF flag and clear it */
     if (I2C_GetITStatus(I2C2, I2C_IT_AF)) 
     {
          I2C_ClearITPendingBit(I2C2, I2C_IT_AF);
     }
 }


void I2cByteWrite(u8 addr, u8 data)
{
delayms(10);
I2C_GenerateSTART(I2C1, ENABLE);
even=I2C_GetLastEvent(I2C1);
while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
I2C_Send7bitAddress(I2C1,Slave_Address,I2C_Direction_Transmitter); //?????
	
while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //??EV6
I2C_SendData(I2C1,addr); //??????????
	
while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING));//??EV8
I2C_SendData(I2C1,data); //????????
	
while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//??EV8_2
I2C_GenerateSTOP(I2C1,ENABLE); //?????
}

u8 I2cByteRead(u8 nAddr)
{
	I2C_AcknowledgeConfig(I2C1,ENABLE); //????
	I2C_GenerateSTART(I2C1,ENABLE); //???????
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)){;} //??EV5
	I2C_Send7bitAddress(I2C1,0xD0,I2C_Direction_Transmitter); //????????
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){;}//??EV6
	I2C_SendData(I2C1,nAddr);//?????
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)){;} //??EV8
	I2C_GenerateSTART(I2C1,ENABLE); //???????
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)){;} //??EV5
	I2C_Send7bitAddress(I2C1,0xD0,I2C_Direction_Receiver); //???????
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){;} //??EV6
	I2C_AcknowledgeConfig(I2C1,DISABLE); //??????
	I2C_GenerateSTOP(I2C1,ENABLE); //???????
	
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){;} //??EV7
	return I2C_ReceiveData(I2C1); //???????
}

 
 void I2C2_EV_IRQHandler(void)
{
    /* Get Last I2C Event */
    Event = I2C_GetLastEvent(I2C2);
 switch (Event)
 {
 /*
****************************************************************************/
 /* Slave Transmitter Events */
 /* */
 /*
****************************************************************************/
 /* Check on EV1 */
 case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
     Tx_Idx = 0;
     I2C_ITConfig(I2C2, I2C_IT_BUF , ENABLE);
 break;
 /* Check on EV3 */

 case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:
 case I2C_EVENT_SLAVE_BYTE_TRANSMITTED:
      I2C_SendData(I2C2, SlaveTxBuffer[Tx_Idx++]);
 break;


/****************************************************************************/
/* Slave Receiver Events */

/* check on EV1*/
 case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED:
     Rx_Idx = 0;
     break;

/* Check on EV2*/
case I2C_EVENT_SLAVE_BYTE_RECEIVED:
case (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_SR1_BTF):
    SlaveRxBuffer[Rx_Idx++] = I2C_ReceiveData(I2C2);
     break;
/* Check on EV4 */
 case I2C_EVENT_SLAVE_STOP_DETECTED:
   I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF);
   I2C_Cmd(I2C2, ENABLE);
   break;
 default:
      break;
    }
 }
