#include "MainTask.h"

extern UART_HandleTypeDef huart1;
uart1_t uart1;

//PID参数
float Kp, Ki, Kd = 0;				//正在使用的PID参数
float current = 0;					//当前温度
float setpoint = 0;					//目标温度
float error = 0;						//误差
float errorSum = 0;					//积分项累积
float lastError = 0;				//上一次的误差
float dError = 0;						//微分项
float lastdError = 0;
float output = 0;						//PID输出
float prevOutput = 0;				//上一次的输出
float alpha = 0.1;					//微分滤波系数
float Max_errorSum = 0.1;
float Max_Power = 0;

//自整定参数
float Kp_AT, Ki_AT, Kd_AT = 0;
char Device_Status = 0;  //设备状态标志位
unsigned int Tc = 0;    	//记录临界周期Tc
float Tmax = 0;        	//记录最大温度
float Tmin = 0;        	//记录最小温度
float Kc = 0;  					//临界增益

//加热棒4.1ohm
float HeatRod_Power = 1; 	//加热棒功率(U^2/R)

float PWM_Duty[4]={0};			//功率输出占空比

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
			AT_Controller(data.averageVoltage, data.Voltage_Target, PWM_Duty);
		}
		else if(Flag.Start_Baseline){
			Baseline_Controller();
		}
		else{
			errorSum = 0;
			PWM_Duty[0] = 0;	
			data.Power = 0;
			data.Baseline_Time = 0;
			memset(uart1.tx_data,0,256);
			sprintf(uart1.tx_data, "OUTP OFF,(@1)\r\n");
			HAL_UART_Transmit(&huart1, (const uint8_t *)uart1.tx_data, sizeof(uart1.tx_data), 0xffff);
		}
		
		//重设目标温度时，清除积分
		if(Flag.T_Target_Update == 1){
			errorSum = 0;
			Flag.T_Target_Update = 0;
		}
		rt_thread_delay(978);
	}
}

#define SAMPLE_COUNT 300 // 5分钟，每秒1次采样
static double voltage_samples[SAMPLE_COUNT] = {0}; // 用于存储每次采样的电压值
static int sample_index = 0; // 当前采样索引
double peak_to_peak = 0;

void Baseline_Controller(void)
{
	static double last_voltage = 0.0;
	static int count = 0;
	
	count++;

	// 保存当前电压到数组
	voltage_samples[sample_index] = data.averageVoltage;
	sample_index = (sample_index + 1) % SAMPLE_COUNT; // 循环索引
	
	if(count > 300){
		
		double max_value = voltage_samples[0];
    double min_value = voltage_samples[0];

    for (int i = 1; i < SAMPLE_COUNT; i++) {
        if (voltage_samples[i] > max_value) {
            max_value = voltage_samples[i];
        }
        if (voltage_samples[i] < min_value) {
            min_value = voltage_samples[i];
        }
    }
		peak_to_peak = max_value - min_value;
		
		// 峰峰值单位V
		if (peak_to_peak < 0.000001) {
				// 计时
				data.Baseline_Time++;

				// 如果时间超过设定的稳定时间，执行操作
				if (data.Baseline_Time >= 300) { // 5分钟 = 300秒
						// 保存当前电压作为基线
					
						// 计算 voltage_samples 数组的平均值
						double sum = 0.0;
						for (int i = 0; i < SAMPLE_COUNT; i++) {
								sum += voltage_samples[i];
						}
						double average_voltage = sum / SAMPLE_COUNT;  // 计算平均值
						
						data.Baseline_Voltage = average_voltage;
						data.Voltage_Target = data.Baseline_Voltage;
					
						Flag.Save_Baseline_Voltage_to_EEPROM = 1;
						Flag.EV2_State = 0;
						Flag.Start_Baseline = 0; // 任务完成后，重置标志位
//						//开始PID控制
//						Flag.EV4_State = 1;
//						Flag.Start_Control= 1;
						data.Baseline_Time = 0;
						count = 0;
					
						rt_sem_t eeprom_sem = get_eeprom_sem();
						rt_sem_release(eeprom_sem);
				}
		} else {
				// 电压不稳定，重置计时器
				data.Baseline_Time = 0;
		}
	
		count = 300;
	}

	
}

/*******************************************************************************
* 函 数 名：PID_Controller
* 函数原形：void PID_Controller(float *T_History, float T_Target, float *PWM_Duty)
* 功能描述：PID温度控制器
* 输入参数：
						（1）测量温度地址：float *T_History
						（2）控温目标温度：float T_Target
						（3）PWM占空比数组地址 float *PWM_Duty
* 输出参数：无
* 返回值：  
* 先决条件：
* 调用函数：无
* 作    者：余明明
* 日    期: 2023-8-21
*******************************************************************************/
void PID_Controller(double T_History, double T_Target, float *PWM_Duty)
{
	Kp = data.Kp;
	Ki = data.Ki;
	Kd = data.Kd;
  
  //获取当前温度
	current = T_History;
	
	//获取目标温度
	setpoint = T_Target;
	
	//计算误差
	error = setpoint - current;
	
	
	//计算积分项
	if(error < Max_errorSum)
		errorSum += error;
	if(errorSum < 0)
		errorSum = 0;
	
	// 计算微分项
	dError = error - lastError;
	if(dError == 0)
		dError = lastdError;
	
	lastdError = dError;

	// 计算PID输出
	output = Kp * error + Ki * errorSum + Kd * dError;
	
	//微分滤波
	output = alpha * output + (1.0 - alpha) * prevOutput;
	
	//更新上一次的输出
  prevOutput = output;

	// 更新上一次的误差
	lastError = error;
  
	//输出给加热器
  *(PWM_Duty+0) = output / 500;
	
	UpdatePWM(PWM_Duty);
}

/*******************************************************************************
* 函 数 名：AT_Controller
* 函数原形：void AT_Controller(float *T_History, float T_Target, float *PWM_Duty)
* 功能描述：PID参数自整定控制器
* 输入参数：
						（1）测量温度地址：float *T_History
						（2）控温目标温度：float T_Target
						（3）PWM占空比数组地址 float *PWM_Duty
* 输出参数：data.Kp, data.Ki, data.Kd
* 返回值：  
* 先决条件：
* 调用函数：PID_Controller
* 作    者：余明明
* 日    期: 2023-8-21
*******************************************************************************/
void AT_Controller(double T_History, double T_Target, float *PWM_Duty)
{
	switch(Device_Status)
	{
		case 0:
		{
			//自整定参数初始化
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
		case 2: //第二个周期的下降段，寻找Tmin
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
		case 3:	//第二个周期的上升段，寻找Tmax
		{
			Tc ++;
			*(PWM_Duty+0) = 0;
			UpdatePWM(PWM_Duty);

			if(Tmax < T_History)
				Tmax = T_History;
			
			if(T_History < T_Target)
				Device_Status ++;
		}break;
		case 4:	//计算PID
		{
			*(PWM_Duty+0) = 0;
			UpdatePWM(PWM_Duty);
			
			Max_Power = 1.0;
			
			Kc = ((400.0 * Max_Power) / (3.142 * ((Tmax - Tmin) / 2.0)));   //计算临界增益
			
			Kp_AT = 0.6 * Kc;
			Ki_AT = Kp_AT / (0.5 * Tc);     //计算积分项系数
			Kd_AT = Kp_AT * (0.125 * Tc);   //计算微分项系
			
			
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
			PID_Controller(data.averageVoltage, data.Voltage_Target, PWM_Duty);  //进入PID控制
		}break;
		default:break;
		
	}
}

/*******************************************************************************
* 函 数 名：UpdatePWM
* 函数原形：void UpdatePWM(float *PWM_Duty)
* 功能描述：输出功率分配
* 输入参数：PWM占空比数组地址：float *PWM_Duty
* 输出参数：无
* 返回值：  
* 先决条件：
* 被调用函数：DAC_WriteData
* 作    者：余明明
* 日    期: 2023-8-21
*******************************************************************************/
void UpdatePWM(float *PWM_Duty)
{
	if(*(PWM_Duty+0) > 1) 
		*(PWM_Duty+0) = 1;
	
	if(*(PWM_Duty+0) < 0)
		*(PWM_Duty+0) = 0;

	//最大10.5W,修改成21.56W，从1.6改成2.2
	float I_OUT = *(PWM_Duty+0) * 2.2;

	data.Power = *(PWM_Duty+0);
	
	memset(uart1.tx_data,0,256);
	sprintf(uart1.tx_data, "VOLT 10,(@1)\r\n");
	HAL_UART_Transmit(&huart1, (const uint8_t *)uart1.tx_data, sizeof(uart1.tx_data), 0xffff);
	
	if(I_OUT > 0){
		memset(uart1.tx_data,0,256);
		sprintf(uart1.tx_data, "CURR %.3f,(@1)\r\n", I_OUT);
		HAL_UART_Transmit(&huart1, (const uint8_t *)uart1.tx_data, sizeof(uart1.tx_data), 0xffff);
		memset(uart1.tx_data,0,256);
		sprintf(uart1.tx_data, "OUTP ON,(@1)\r\n");
		HAL_UART_Transmit(&huart1, (const uint8_t *)uart1.tx_data, sizeof(uart1.tx_data), 0xffff);
	}
	else{
		memset(uart1.tx_data,0,256);
		sprintf(uart1.tx_data, "OUTP OFF,(@1)\r\n");
		HAL_UART_Transmit(&huart1, (const uint8_t *)uart1.tx_data, sizeof(uart1.tx_data), 0xffff);
	}
	
}
