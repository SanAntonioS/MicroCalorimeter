#include "ModbusRtu.h"

extern UART_HandleTypeDef huart3;
extern Data_t data;
extern Flag_t Flag;
uart3_t uart3;
Register_t Register;

uint8_t Data_Without_CRC[256];
uint8_t Register_Array[256];
uint8_t Register_Value[256];
uint8_t tx_data[256];

uint16_t Register_Addr;
int Register_Num;
uint16_t Data_CRC;
uint16_t crc_result;

extern rt_sem_t get_uart3_sem(void);
extern rt_sem_t get_eeprom_sem(void);

void data_send_thread_entry(void *parameter)
{
	while(1)
	{
		rt_sem_t uart3_sem = get_uart3_sem();
		rt_err_t result = rt_sem_take(uart3_sem, RT_WAITING_FOREVER);
		
		if(uart3.len > 0){
			ModbusRtuTask();
		}
	}
}

void ModbusRtuTask(void)
{
		//接收数据CRC16校验计算
		memset(Data_Without_CRC, 0, sizeof(Data_Without_CRC));
		memcpy(Data_Without_CRC, &uart3.rx_data, uart3.len - 2);
		size_t data_len = uart3.len - 2;
		crc_result = calculate_crc16_modbus(Data_Without_CRC, data_len);
		crc_result = LtoB_Uint16(crc_result);

		//接收到的CRC校验位
		Data_CRC = (uart3.rx_data[uart3.len - 2] << 8) + uart3.rx_data[uart3.len - 1];

		//更新寄存器值
		Register.Pv = data.averageR2;		
		Register.Kp = (data.Kp);
		Register.Ki = (data.Ki);
		Register.Sv = data.averageR1;
		Register.Resistance = (data.Voltage_Target);
		Register.OUT = data.averageR4;
		Register.NTC_A = data.averageVoltage;
		Register.NTC_B = (data.NTC_B);
		Register.NTC_C = (data.NTC_C);
		Register.NTC_D = (data.NTC_D);
		Register.NTC_E = (data.NTC_E);
		Register.NTC_F = (data.NTC_F);
		Register.Pv_OpenLoop = (data.T_OpenPID_Target);
		Register.EV1 = (Flag.EV1_State);
		Register.EV2 = (Flag.EV2_State);
		Register.EV3 = (Flag.EV3_State);
		Register.EV4 = (Flag.EV4_State);
		Register.Modbus_Switch = (Flag.Modbus_State);
		Register.Kd = (data.Kd);
		Register.Pv2 = data.averageR3;
		Register.Resistance2 = (data.Power);
		Register.NTC_A2 = (data.NTC_A2);
		Register.NTC_B2 = (data.NTC_B2);
		Register.NTC_C2 = (data.NTC_C2);
		Register.NTC_D2 = (data.NTC_D2);
		Register.NTC_E2 = (data.NTC_E2);
		Register.NTC_F2 = (data.NTC_F2);
		Register.AT = (Flag.Start_AT);
		Register.Max_Temperature = data.Max_Temperature;
		Register.Min_Temperature = data.Min_Temperature;

		
		Register.Pv = LtoB_Float(Register.Pv);
		Register.Kp = LtoB_Float(Register.Kp);
		Register.Ki = LtoB_Float(Register.Ki);
		Register.Sv = LtoB_Float(Register.Sv);
		Register.Resistance = LtoB_Float(Register.Resistance);
		Register.OUT = LtoB_Float(Register.OUT);
		Register.NTC_A = LtoB_Double(Register.NTC_A);
		Register.NTC_B = LtoB_Double(Register.NTC_B);
		Register.NTC_C = LtoB_Double(Register.NTC_C);
		Register.NTC_D = LtoB_Double(Register.NTC_D);
		Register.NTC_E = LtoB_Double(Register.NTC_E);
		Register.NTC_F = LtoB_Double(Register.NTC_F);
		Register.Pv_OpenLoop = LtoB_Float(Register.Pv_OpenLoop);
		Register.EV1 = LtoB_Uint16(Register.EV1);
		Register.EV2 = LtoB_Uint16(Register.EV2);
		Register.EV3 = LtoB_Uint16(Register.EV3);
		Register.EV4 = LtoB_Uint16(Register.EV4);
		Register.Modbus_Switch = LtoB_Uint16(Register.Modbus_Switch);
		Register.Kd = LtoB_Float(Register.Kd);
		Register.Pv2 = LtoB_Float(Register.Pv2);
		Register.Resistance2 = LtoB_Float(Register.Resistance2);
		Register.NTC_A2 = LtoB_Double(Register.NTC_A2);
		Register.NTC_B2 = LtoB_Double(Register.NTC_B2);
		Register.NTC_C2 = LtoB_Double(Register.NTC_C2);
		Register.NTC_D2 = LtoB_Double(Register.NTC_D2);
		Register.NTC_E2 = LtoB_Double(Register.NTC_E2);
		Register.NTC_F2 = LtoB_Double(Register.NTC_F2);
		Register.AT = LtoB_Uint16(Register.AT);
		Register.Max_Temperature = LtoB_Float(Register.Max_Temperature);
		Register.Min_Temperature = LtoB_Float(Register.Min_Temperature);
		

		memset(Register_Array, 0, sizeof(Register_Array));
		memcpy(Register_Array, &Register, sizeof(Register));//此处新增参数后需要重新计算长度

		if (Data_CRC == crc_result) {
			switch (uart3.rx_data[1]) {

			//读单路、多路寄存器
			case 0x03: {
				//获取读寄存器地址
				Register_Addr = (uart3.rx_data[2] << 8) + uart3.rx_data[3];

				//获取读寄存器数量
				Register_Num = (uart3.rx_data[4] << 8) + uart3.rx_data[5];

				//将要读取的所有寄存器数据写入
				memset(Register_Value, 0, sizeof(Register_Value));
				memcpy(Register_Value, Register_Array + ((Register_Addr - 0x0100) * 2), Register_Num * 2);
				
				//编辑发送数据数组tx_data
				tx_data[0] = 0x01;
				tx_data[1] = 0x03;
				tx_data[2] = Register_Num * 2;
				memcpy(tx_data + 3, Register_Value, Register_Num * 2);
				uint16_t tx_data_crc = calculate_crc16_modbus(tx_data, (Register_Num * 2) + 3);
				memcpy(tx_data + 3 + (Register_Num * 2), &tx_data_crc, 2);

				//tx_data写入发送区结构体数组uart3.tx_data中
				memset(uart3.tx_data, 0, sizeof(uart3.tx_data));
				int len = 3 + (Register_Num * 2) + 2;
				memcpy(uart3.tx_data, &tx_data, len);
				
				HAL_UART_Transmit(&huart3, uart3.tx_data, len, 0xffff);

			}break;

			//写单路寄存器
			case 0x06: {
				//获取读寄存器地址
				Register_Addr = (uart3.rx_data[2] << 8) + uart3.rx_data[3];

				switch (Register_Addr) {

				case 0x0126: {
					if (uart3.rx_data[5] == 0x01){
						Flag.EV1_State = 1;
					}
					else{
						Flag.EV1_State = 0;
					}
				}break;

				case 0x0127: {
					if (uart3.rx_data[5] == 0x01){
						Flag.EV2_State = 1;
						Flag.Start_Baseline = 1;
					}
					else{
						Flag.EV2_State = 0;
						Flag.Start_Baseline = 0;
					}
				}break;

				case 0x0128: {
					if (uart3.rx_data[5] == 0x01){
						Flag.EV3_State = 1;
						Flag.Start_AT = 1;
					}
					else{
						Flag.EV3_State = 0;
						Flag.Start_AT = 0;
					}
				}break;

				case 0x0129: {
					if (uart3.rx_data[5] == 0x01){
						Flag.EV4_State = 1;
						Flag.Start_Control= 1;
					}
					else{
						Flag.EV4_State = 0;
						Flag.Start_Control= 0;
					}
				}break;
				
				case 0x012A: {
					if (uart3.rx_data[5] == 0x01)
						Flag.Modbus_State= 1;
					else
						Flag.Modbus_State= 0;
				}break;
				
				case 0x0149: {
					if (uart3.rx_data[5] == 0x01){
						Flag.Start_AT= 1;
						Flag.Start_Control= 0;
					}
					else{
						Flag.Start_AT= 0;
					}
				}break;

				default:break;
				}

				memcpy(uart3.tx_data, uart3.rx_data, uart3.len);
				HAL_UART_Transmit(&huart3, uart3.tx_data, uart3.len, 0xffff);
			}break;

			//写多路寄存器
			case 0x10: {
				//获取读寄存器地址
				Register_Addr = (uart3.rx_data[2] << 8) + uart3.rx_data[3];
				
				switch(Register_Addr)
				{
					case 0x0102:	Flag.Save_Kp_to_EEPROM = 1;break;
					case 0x0104:	Flag.Save_Ki_to_EEPROM = 1;break;
					case 0x012B:	Flag.Save_Kd_to_EEPROM = 1;break;
					case 0x014A:	Flag.Save_MaxT_to_EEPROM = 1;break;
					case 0x014C:	Flag.Save_MinT_to_EEPROM = 1;break;
					default:break;
				}

				//获取读寄存器数量
				Register_Num = (uart3.rx_data[4] << 8) + uart3.rx_data[5];

				//获取字节数
				int Byte_Num = uart3.rx_data[6];

				memcpy(Register_Array + ((Register_Addr - 0x0100) * 2), uart3.rx_data + 7, Byte_Num);
				memcpy(&Register, Register_Array, sizeof(Register));

				//更新寄存器值至数据中
				data.Kp = LtoB_Float(Register.Kp);
				data.Ki = LtoB_Float(Register.Ki);
				data.Voltage_Target = LtoB_Float(Register.Sv);
				data.NTC_A = LtoB_Double(Register.NTC_A);
				data.NTC_B = LtoB_Double(Register.NTC_B);
				data.NTC_C = LtoB_Double(Register.NTC_C);
				data.NTC_D = LtoB_Double(Register.NTC_D);
				data.NTC_E = LtoB_Double(Register.NTC_E);
				data.NTC_F = LtoB_Double(Register.NTC_F);
				data.Baseline_Temperature = LtoB_Float(Register.Pv_OpenLoop);
				data.Kd = LtoB_Float(Register.Kd);
				data.NTC_A2 = LtoB_Double(Register.NTC_A2);
				data.NTC_B2 = LtoB_Double(Register.NTC_B2);
				data.NTC_C2 = LtoB_Double(Register.NTC_C2);
				data.NTC_D2 = LtoB_Double(Register.NTC_D2);
				data.NTC_E2 = LtoB_Double(Register.NTC_E2);
				data.NTC_F2 = LtoB_Double(Register.NTC_F2);
				data.Max_Temperature = LtoB_Float(Register.Max_Temperature);
				data.Min_Temperature = LtoB_Float(Register.Min_Temperature);
					

				//编辑发送数据数组tx_data
				tx_data[0] = 0x01;
				tx_data[1] = 0x10;
				Register_Addr = LtoB_Uint16(Register_Addr);
				Register_Num = LtoB_Uint16(Register_Num);

				memcpy(tx_data + 2, &Register_Addr, 2);
				memcpy(tx_data + 4, &Register_Num, 2);
				uint16_t tx_data_crc = calculate_crc16_modbus(tx_data, 6);
//				tx_data_crc = LtoB_Uint16(tx_data_crc);
				memcpy(tx_data + 6, &tx_data_crc, 2);

				//tx_data写入发送区结构体数组uart3.tx_data中
				memset(uart3.tx_data, 0, sizeof(uart3.tx_data));
				memcpy(uart3.tx_data, &tx_data, 8);
				
				HAL_UART_Transmit(&huart3, uart3.tx_data, 8, 0xffff);
				uart3.len = 0;
				
				rt_sem_t eeprom_sem = get_eeprom_sem();
				rt_sem_release(eeprom_sem);

			}break;
			default:break;
			}
		}
		memset(uart3.rx_data, 0, sizeof(uart3.rx_data));
}

float LtoB_Float(float data)
{
	FLOAT_CONV d1, d2;
	d1.f = data;

	d2.c[0] = d1.c[3];
	d2.c[1] = d1.c[2];
	d2.c[2] = d1.c[1];
	d2.c[3] = d1.c[0];

	return d2.f;
}

double LtoB_Double(double data)
{
	DOUBLE_CONV d1, d2;
	d1.d = data;

	d2.c[0] = d1.c[7];
	d2.c[1] = d1.c[6];
	d2.c[2] = d1.c[5];
	d2.c[3] = d1.c[4];
	d2.c[4] = d1.c[3];
	d2.c[5] = d1.c[2];
	d2.c[6] = d1.c[1];
	d2.c[7] = d1.c[0];

	return d2.d;
}

uint16_t LtoB_Uint16(uint16_t data)
{
	UINT16_CONV d1, d2;
	d1.d = data;

	d2.c[0] = d1.c[1];
	d2.c[1] = d1.c[0];

	return d2.d;
}