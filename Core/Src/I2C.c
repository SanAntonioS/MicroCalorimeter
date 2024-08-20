#include "I2C.h"

/*******************************************************************************
* 函数名：  I2C_Config
* 函数原形：void I2C_Config(void)
* 功能描述: I2C初始化
* 输入参数：无
* 输出参数：无
* 返回值：	   无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
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
* 函数名：  I2C_SDA_OUT
* 函数原形：void I2C_SDA_OUT(void)
* 功能描述: I2C_SDA配置成输出模式
* 输入参数：无
* 输出参数：无
* 返回值：  无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
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
* 函数名：  I2C_SDA_IN
* 函数原形：void I2C_SDA_IN(void)
* 功能描述: I2C_SDA配置成输入模式
* 输入参数：无
* 输出参数：无
* 返回值：	   无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
*******************************************************************************/
void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  GPIO_InitStruct.Pin = I2C_SDA;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/*******************************************************************************
* 函数名：  I2C_Start
* 函数原形：void I2C_Start(void)
* 功能描述: I2C产生起始信号
* 输入参数：无
* 输出参数：无
* 返回值：	   无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
*******************************************************************************/
void I2C_Start(void)
{
  I2C_SDA_OUT();
  
  I2C_SDA_H;//SDA高电平
  I2C_SCL_H;//SCL高电平
//  rt_hw_us_delay(5);
  I2C_SDA_L;
//  rt_hw_us_delay(6);
  I2C_SCL_L;  
}
/*******************************************************************************
* 函数名：  I2C_Stop
* 函数原形：void I2C_Stop(void)
* 功能描述: I2C产生停止信号
* 输入参数：无
* 输出参数：无
* 返回值：	   无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
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
* 函数名：  I2C_ACK
* 函数原形：void I2C_ACK(void)
* 功能描述: 主机产生应答信号ACK
* 输入参数：无
* 输出参数：无
* 返回值：	   无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
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
* 函数名：  I2C_NACK
* 函数原形：void I2C_NACK(void)
* 功能描述: 主机产生不应答信号NACK
* 输入参数：无
* 输出参数：无
* 返回值：	   无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
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
* 函数名：  I2C_Wait_ACK
* 函数原形：u8 I2C_Wait_ACK(void)
* 功能描述: 等待从机应答信号
* 输入参数：无
* 输出参数：无
* 返回值：若为1，表示接收应答失败，为0，表示接收应答成功
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
*******************************************************************************/
uint8_t I2C_Wait_ACK(void)
{
  uint8_t tempTime = 0;
  
  I2C_SDA_IN();
  
  I2C_SDA_H;
//  rt_hw_us_delay(1);
  I2C_SCL_H;
//  rt_hw_us_delay(1);
  
  while(HAL_GPIO_ReadPin(GPIO_I2C, I2C_SDA))//读取I2C_SDA的状态，若为0，则给出了反馈信号
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
* 函数名：  I2C_Send_Byte
* 函数原形：void I2C_Send_Byte(u8 txd)
* 功能描述: I2C发送一个字节，8个位的数据
* 输入参数：无
* 输出参数：无
* 返回值：无
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
*******************************************************************************/
void I2C_Send_Byte(uint8_t txd)
{
  uint8_t i = 0;
  
  I2C_SDA_OUT();  
  I2C_SCL_L; //拉低时钟，开始输出传输(组织数据)
  
  for(i = 0; i < 8; i++)
  {
    if((txd&0x80)>0)//txd&0x80表示只保留高八位
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
* 函数名：  I2C_Read_Byte
* 函数原形：u8 I2C_Read_Byte(u8 ack)
* 功能描述: I2C读取一个字节，8个位的数据
* 输入参数：无
* 输出参数：无
* 返回值：  I2C读取的数据
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
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

