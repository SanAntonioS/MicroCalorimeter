#include "MainTask.h"

extern UART_HandleTypeDef huart1;
uart1_t uart1;

//PID����
float Kp, Ki, Kd = 0;				//����ʹ�õ�PID����
float current = 0;					//��ǰ�¶�
float setpoint = 0;					//Ŀ���¶�
float error = 0;						//���
float errorSum = 0;					//�������ۻ�
float lastError = 0;				//��һ�ε����
float dError = 0;						//΢����
float output = 0;						//PID���
float prevOutput = 0;				//��һ�ε����
float alpha = 0.1;					//΢���˲�ϵ��
float Max_errorSum = 0.1;
float Max_Power = 0;

//����������
float Kp_AT, Ki_AT, Kd_AT = 0;
char Device_Status = 0;  //�豸״̬��־λ
unsigned int Tc = 0;    	//��¼�ٽ�����Tc
float Tmax = 0;        	//��¼����¶�
float Tmin = 0;        	//��¼��С�¶�
float Kc = 0;  					//�ٽ�����

float HeatRod_Power = 100; 	//���Ȱ�����(U^2/R)

float PWM_Duty[4]={0};			//�������ռ�ձ�

float last_voltage, current_voltage = 0;

extern Data_t data;
extern Flag_t Flag;

extern rt_sem_t get_eeprom_sem(void);

void main_task_thread_entry(void *parameter)
{
	while(1){
		if(Flag.Start_Control){
			PID_Controller(data.averageVoltage, data.Voltage_Target, PWM_Duty);
		}
		else if(Flag.Start_AT){
			AT_Controller(data.averageVoltage, data.T_Target, PWM_Duty);
		}
		else if(Flag.Start_Baseline){
			Baseline_Controller();
		}
		else{
			PWM_Duty[0] = 0;	
		}
		
//		//����Ŀ���¶�ʱ���������
//		if(Flag.T_Target_Update == 1){
//			errorSum = 0;
//			Flag.T_Target_Update = 0;
//		}
		rt_thread_delay(978);
	}
}

void Baseline_Controller(void)
{
	static float last_voltage = 0.0;
	static int time = 0;
	
	data.Baseline1_T = data.Baseline_Temperature;

	// ����ѹ�Ƿ��ȶ���һ����Χ��
	if (fabs(data.averageVoltage - last_voltage) < 10e-6) {
			// ��ʱ
			time++;

			// ���ʱ�䳬���趨���ȶ�ʱ�䣬ִ�в���
			if (time >= 300) { // 5���� = 300��
					// ���浱ǰ��ѹ��Ϊ����
					data.Baseline1_V = data.averageVoltage;
					Flag.Start_Baseline = 0; // ������ɺ����ñ�־λ
			}
	} else {
			// ��ѹ���ȶ������ü�ʱ��
			time = 0;
	}

	// ������һ�εĵ�ѹֵ
	last_voltage = data.averageVoltage;
}

/*******************************************************************************
* �� �� ����PID_Controller
* ����ԭ�Σ�void PID_Controller(float *T_History, float T_Target, float *PWM_Duty)
* ����������PID�¶ȿ�����
* ���������
						��1�������¶ȵ�ַ��float *T_History
						��2������Ŀ���¶ȣ�float T_Target
						��3��PWMռ�ձ������ַ float *PWM_Duty
* �����������
* ����ֵ��  
* �Ⱦ�������
* ���ú�������
* ��    �ߣ�������
* ��    ��: 2023-8-21
*******************************************************************************/
void PID_Controller(float T_History, float T_Target, float *PWM_Duty)
{
	Kp = data.Kp;
	Ki = data.Ki;
	Kd = data.Kd;
  
  //��ȡ��ǰ�¶�
	current = T_History;
	
	//��ȡĿ���¶�
	setpoint = T_Target;
	
	//�������
	error = setpoint - current;
	
	
	//���������
	if(error < Max_errorSum)
		errorSum += error;
	if(errorSum < 0)
		errorSum = 0;
	
	// ����΢����
	dError = error - lastError;

	// ����PID���
	output = Kp * error + Ki * errorSum + Kd * dError;
	
	//΢���˲�
	output = alpha * output + (1.0 - alpha) * prevOutput;
	
	//������һ�ε����
  prevOutput = output;

	// ������һ�ε����
	lastError = error;
  
	//�����������
  *(PWM_Duty+0) = output / HeatRod_Power;
	
	UpdatePWM(PWM_Duty);
}

/*******************************************************************************
* �� �� ����AT_Controller
* ����ԭ�Σ�void AT_Controller(float *T_History, float T_Target, float *PWM_Duty)
* ����������PID����������������
* ���������
						��1�������¶ȵ�ַ��float *T_History
						��2������Ŀ���¶ȣ�float T_Target
						��3��PWMռ�ձ������ַ float *PWM_Duty
* ���������data.Kp, data.Ki, data.Kd
* ����ֵ��  
* �Ⱦ�������
* ���ú�����PID_Controller
* ��    �ߣ�������
* ��    ��: 2023-8-21
*******************************************************************************/
void AT_Controller(float T_History, float T_Target, float *PWM_Duty)
{
	switch(Device_Status)
	{
		case 0:
		{
			//������������ʼ��
			Tmax 	= 0;
			Tmin 	= 0;
			Tc		= 0;
			
			*(PWM_Duty+0) = 1;
			UpdatePWM(PWM_Duty);
			
			if(T_History > T_Target)
				Device_Status ++;
		}break;
		case 1:
		{
			*(PWM_Duty+0) = 0;
			UpdatePWM(PWM_Duty);
			Tmin = T_History;
			
			if(T_History < T_Target)
				Device_Status ++;
		}break;
		case 2: //�ڶ������ڵ��½��Σ�Ѱ��Tmin
		{
			Tc ++;
			
			*(PWM_Duty+0) = 1;
			UpdatePWM(PWM_Duty);
			Tmax = T_History;
			
			if(Tmin > T_History)
				Tmin = T_History;
			
			if(T_History > T_Target)
				Device_Status ++;
		}break;
		case 3:	//�ڶ������ڵ������Σ�Ѱ��Tmax
		{
			Tc ++;
			*(PWM_Duty+0) = 0;
			UpdatePWM(PWM_Duty);

			if(Tmax < T_History)
				Tmax = T_History;
			
			if(T_History < T_Target)
				Device_Status ++;
		}break;
		case 4:	//����PID
		{
			*(PWM_Duty+0) = 0;
			UpdatePWM(PWM_Duty);
			
			Max_Power = 1.0;
			
			Kc = ((400.0 * Max_Power) / (3.142 * ((Tmax - Tmin) / 2.0)));   //�����ٽ�����
			
			Kp_AT = 0.6 * Kc;
			Ki_AT = Kp_AT / (0.5 * Tc);     //���������ϵ��
			Kd_AT = Kp_AT * (0.125 * Tc);   //����΢����ϵ
			
			
			data.Kp = Kp_AT;
			data.Ki = Ki_AT;
			data.Kd = Kd_AT;
			
			Flag.Save_Kp_to_EEPROM = 1;
			Flag.Save_Ki_to_EEPROM = 1;
			Flag.Save_Kd_to_EEPROM = 1;
			
			rt_sem_t eeprom_sem = get_eeprom_sem();
			rt_sem_release(eeprom_sem);
			
			Device_Status ++;
		}break;
		case 5:
		{
			PID_Controller(data.averageVoltage, data.Voltage_Target, PWM_Duty);  //����PID����
		}break;
		default:break;
		
	}
}

/*******************************************************************************
* �� �� ����UpdatePWM
* ����ԭ�Σ�void UpdatePWM(float *PWM_Duty)
* ����������������ʷ���
* ���������PWMռ�ձ������ַ��float *PWM_Duty
* �����������
* ����ֵ��  
* �Ⱦ�������
* �����ú�����DAC_WriteData
* ��    �ߣ�������
* ��    ��: 2023-8-21
*******************************************************************************/
void UpdatePWM(float *PWM_Duty)
{
	if(*(PWM_Duty+0) > 1) 
		*(PWM_Duty+0) = 1;
	
	if(*(PWM_Duty+0) < 0)
		*(PWM_Duty+0) = 0;

	float I_OUT = *(PWM_Duty+0) * 5.0;

	data.Power = *(PWM_Duty+0);
	
	sprintf(uart1.tx_data, "CURR%.2f,(@1)\r\n", I_OUT);
	HAL_UART_Transmit(&huart1, (const uint8_t *)uart1.tx_data, sizeof(uart1.tx_data), 0xffff);
	
}
