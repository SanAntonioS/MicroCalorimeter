#include "I2C.h"

/*******************************************************************************
* ��������  I2C_Config
* ����ԭ�Σ�void I2C_Config(void)
* ��������: I2C��ʼ��
* �����������
* �����������
* ����ֵ��	   ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIO_I2C, I2C_SCL|I2C_SDA, GPIO_PIN_SET);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = I2C_SCL|I2C_SDA;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIO_I2C, &GPIO_InitStruct);
}
/*******************************************************************************
* ��������  I2C_SDA_OUT
* ����ԭ�Σ�void I2C_SDA_OUT(void)
* ��������: I2C_SDA���ó����ģʽ
* �����������
* �����������
* ����ֵ��  ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  GPIO_InitStruct.Pin = I2C_SDA;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/*******************************************************************************
* ��������  I2C_SDA_IN
* ����ԭ�Σ�void I2C_SDA_IN(void)
* ��������: I2C_SDA���ó�����ģʽ
* �����������
* �����������
* ����ֵ��	   ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  GPIO_InitStruct.Pin = I2C_SDA;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/*******************************************************************************
* ��������  I2C_Start
* ����ԭ�Σ�void I2C_Start(void)
* ��������: I2C������ʼ�ź�
* �����������
* �����������
* ����ֵ��	   ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_Start(void)
{
  I2C_SDA_OUT();
  
  I2C_SDA_H;//SDA�ߵ�ƽ
  I2C_SCL_H;//SCL�ߵ�ƽ
//  rt_hw_us_delay(5);
  I2C_SDA_L;
//  rt_hw_us_delay(6);
  I2C_SCL_L;  
}
/*******************************************************************************
* ��������  I2C_Stop
* ����ԭ�Σ�void I2C_Stop(void)
* ��������: I2C����ֹͣ�ź�
* �����������
* �����������
* ����ֵ��	   ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_Stop(void)
{
  I2C_SDA_OUT();
  
  I2C_SCL_L;
  I2C_SDA_L;
  I2C_SCL_H;
//  rt_hw_us_delay(6);
  I2C_SDA_H;
//  rt_hw_us_delay(6);
}
/*******************************************************************************
* ��������  I2C_ACK
* ����ԭ�Σ�void I2C_ACK(void)
* ��������: ��������Ӧ���ź�ACK
* �����������
* �����������
* ����ֵ��	   ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_ACK(void)
{
  I2C_SCL_L;
  I2C_SDA_OUT();
  I2C_SDA_L;
//  rt_hw_us_delay(2);
  I2C_SCL_H;
//  rt_hw_us_delay(5);
  I2C_SCL_L;  
}
/*******************************************************************************
* ��������  I2C_NACK
* ����ԭ�Σ�void I2C_NACK(void)
* ��������: ����������Ӧ���ź�NACK
* �����������
* �����������
* ����ֵ��	   ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_NACK(void)
{
  I2C_SCL_L;
  I2C_SDA_OUT();
  I2C_SDA_H;
//  rt_hw_us_delay(2);
  I2C_SCL_H;
//  rt_hw_us_delay(5);
  I2C_SCL_L; 
}
/*******************************************************************************
* ��������  I2C_Wait_ACK
* ����ԭ�Σ�u8 I2C_Wait_ACK(void)
* ��������: �ȴ��ӻ�Ӧ���ź�
* �����������
* �����������
* ����ֵ����Ϊ1����ʾ����Ӧ��ʧ�ܣ�Ϊ0����ʾ����Ӧ��ɹ�
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
uint8_t I2C_Wait_ACK(void)
{
  uint8_t tempTime = 0;
  
  I2C_SDA_IN();
  
  I2C_SDA_H;
//  rt_hw_us_delay(1);
  I2C_SCL_H;
//  rt_hw_us_delay(1);
  
  while(HAL_GPIO_ReadPin(GPIO_I2C, I2C_SDA))//��ȡI2C_SDA��״̬����Ϊ0��������˷����ź�
  {
    tempTime++;
    if(tempTime >250)
    {
      I2C_Stop();
      return 1;
    }
  }
  I2C_SCL_L; 
  return 0;
}
/*******************************************************************************
* ��������  I2C_Send_Byte
* ����ԭ�Σ�void I2C_Send_Byte(u8 txd)
* ��������: I2C����һ���ֽڣ�8��λ������
* �����������
* �����������
* ����ֵ����
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void I2C_Send_Byte(uint8_t txd)
{
  uint8_t i = 0;
  
  I2C_SDA_OUT();  
  I2C_SCL_L; //����ʱ�ӣ���ʼ�������(��֯����)
  
  for(i = 0; i < 8; i++)
  {
    if((txd&0x80)>0)//txd&0x80��ʾֻ�����߰�λ
		{
			I2C_SDA_H;
		}
		else
		{
			I2C_SDA_L;
		}
    
    txd<<=1;
    I2C_SCL_H;
//    rt_hw_us_delay(2);
    I2C_SCL_L;
//    rt_hw_us_delay(2);  
  }
}
/*******************************************************************************
* ��������  I2C_Read_Byte
* ����ԭ�Σ�u8 I2C_Read_Byte(u8 ack)
* ��������: I2C��ȡһ���ֽڣ�8��λ������
* �����������
* �����������
* ����ֵ��  I2C��ȡ������
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
uint8_t I2C_Read_Byte(uint8_t ack)
{
  uint8_t i = 0;
  uint8_t receive = 0;
  
  I2C_SDA_IN();
  for(i=0; i<8; i++)
  {
    I2C_SCL_L;
//    rt_hw_us_delay(2);
    I2C_SCL_H;
    receive <<= 1;
    if(HAL_GPIO_ReadPin(GPIO_I2C, I2C_SDA))
        receive++;
    
//    rt_hw_us_delay(1);
  }
  if(ack==0)
    I2C_NACK();
  else
    I2C_ACK();
  
  return receive;
}

