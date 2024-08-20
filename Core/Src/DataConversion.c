#include "DataConversion.h"

unsigned long RegisterValue_AD1_Ch03 = 0;
unsigned long RegisterValue_AD1_Ch13 = 0;
unsigned long RegisterValue_AD1_Ch23 = 0;

float V_AD1_Ch03 = 0;
float V_AD1_Ch13 = 0;
float V_AD1_Ch23 = 0;

char sendBuffer[128];
rt_uint8_t AD1_Channel_State = 0;
rt_uint8_t AD_State = 0;

extern rt_sem_t get_semaphore(void);

void data_conversion_thread_entry(void *parameter)
{
	while (1)
	{
		rt_sem_t sem = get_semaphore();
		
		rt_err_t result = rt_sem_take(sem, RT_WAITING_FOREVER);
    if (result == RT_EOK) {	
			switch(AD1_Channel_State){
				case 0:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device1,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD1_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device1, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device1, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 1:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device1,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD1_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device1, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device1, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 2:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device1,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD1_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device1, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device1, AD717X_ADCMODE_REG);
					
					DisableIOSPI(1);
					AD_State = 2;
					AD1_Channel_State++;
				}break;
				case 3:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device2,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD2_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device2, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device2, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 4:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device2,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD2_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device2, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device2, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 5:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device2,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD2_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device2, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device2, AD717X_ADCMODE_REG);
					
					DisableIOSPI(2);
					AD_State = 3;
					AD1_Channel_State++;
				}break;
				case 6:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device3,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD3_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device3, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device3, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 7:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device3,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD3_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device3, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device3, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 8:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device3,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD3_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device3, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device3, AD717X_ADCMODE_REG);
					
					DisableIOSPI(3);
					AD_State = 4;
					AD1_Channel_State++;
				}break;
				case 9:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device4,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD4_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device4, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device4, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 10:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device4,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD4_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device4, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device4, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 11:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device4,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD4_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device4, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device4, AD717X_ADCMODE_REG);
					
					DisableIOSPI(4);
					AD_State = 5;
					AD1_Channel_State++;
				}break;
				case 12:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device5,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD5_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device5, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device5, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 13:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device5,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD5_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device5, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device5, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 14:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device5,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD5_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device5, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device5, AD717X_ADCMODE_REG);
					
					DisableIOSPI(5);
					AD_State = 6;
					AD1_Channel_State++;
				}break;
				case 15:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device6,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD6_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device6, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device6, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 16:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device6,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD6_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device6, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device6, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 17:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device6,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD6_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device6, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device6, AD717X_ADCMODE_REG);
					
					DisableIOSPI(6);
					AD_State = 7;
					AD1_Channel_State++;
				}break;
				case 18:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device7,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD7_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device7, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device7, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 19:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device7,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD7_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device7, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device7, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 20:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device7,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD7_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device7, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device7, AD717X_ADCMODE_REG);
					
					DisableIOSPI(7);
					AD_State = 8;
					AD1_Channel_State++;
				}break;
				case 21:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device8,AD717X_DATA_REG);
					V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
					
					sprintf(sendBuffer, "V_AD8_Ch03:%f\r\n", V_AD1_Ch03);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
					AD717X_WriteRegister(&device8, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device8, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 22:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device8,AD717X_DATA_REG);
					V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
					
					sprintf(sendBuffer, "V_AD8_Ch13:%f\r\n", V_AD1_Ch13);
					rt_kprintf("%s", sendBuffer);
					
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //�л�����ͨ��
					AD717X_WriteRegister(&device8, AD717X_CHMAP0_REG);//д������
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device8, AD717X_ADCMODE_REG);
					
					AD1_Channel_State++;
				}break;
				case 23:{
					//�ȴ�����
					AD717X_WaitRdyGoLow(1); 
					rt_hw_us_delay(2);
					//��ȡ�Ĵ���ֵ
					RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device8,AD717X_DATA_REG);
					V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
					
					sprintf(sendBuffer, "V_AD8_Ch23:%f\r\n", V_AD1_Ch23);
					rt_kprintf("%s", sendBuffer);
					
					//�л�����ͨ��
					ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
					+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x00);
					AD717X_WriteRegister(&device8, AD717X_CHMAP0_REG);
					
					ad7177_2_regs[1].value = 0x0020;//ѡ��������ģʽ
					AD717X_WriteRegister(&device8, AD717X_ADCMODE_REG);
					
					DisableIOSPI(8);
					AD_State = 1;
					AD1_Channel_State=0;
				}break;
				default: break;
			}
			
			rt_thread_delay(1000);
			
			ad7177_2_regs[1].value = 0x0200;
			switch(AD_State){
				case 1:	AD717X_WriteRegister(&device1, AD717X_ADCMODE_REG);break;
				case 2:	AD717X_WriteRegister(&device2, AD717X_ADCMODE_REG);break;
				case 3:	AD717X_WriteRegister(&device3, AD717X_ADCMODE_REG);break;
				case 4:	AD717X_WriteRegister(&device4, AD717X_ADCMODE_REG);break;
				case 5:	AD717X_WriteRegister(&device5, AD717X_ADCMODE_REG);break;
				case 6:	AD717X_WriteRegister(&device6, AD717X_ADCMODE_REG);break;
				case 7:	AD717X_WriteRegister(&device7, AD717X_ADCMODE_REG);break;
				case 8:	AD717X_WriteRegister(&device8, AD717X_ADCMODE_REG);break;
				default:break;
			}
    }
	}
}

float RegValue_To_Voltage(uint32_t RegValue)
{	
	float Volt=0;//�ȵ�ż��Ӧ����ֵ
  Volt=(((float)RegValue/2147483648.0-1)*2.5); //�Ŵ�10����2.5V�ο���ѹ
  return Volt;//���ض�Ӧ����ֵ  
}