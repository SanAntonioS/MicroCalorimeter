#include "DataProcess.h"

#define AVERAGE_SIZE 20		//����ƽ�����ڴ�С

Data_t data;
Flag_t Flag;

extern rt_sem_t get_data_process_sem(void);

// ����ƽ�����ݽṹ
typedef struct {
    float values[AVERAGE_SIZE];  // ���滬�������ڵ�ֵ
    int size;        // �������ڵĴ�С
    int index;       // ��ǰ����ֵ��λ��
    int count;       // ��ǰ�������Ԫ������
    float sum;      // ��ǰ����������ֵ�ĺ�
} SlidingAverage;

// ��ʼ������ƽ���ṹ
void init_sliding_average(SlidingAverage *avg, int size) {
    avg->size = size;
    avg->index = 0;
    avg->count = 0;
    avg->sum = 0.0;
    for (int i = 0; i < size; i++) {
        avg->values[i] = 0.0;  // ��ʼ������Ϊ0
    }
}

// �����µĻ���ƽ��ֵ
float update_sliding_average(SlidingAverage *avg, float new_value) {
    // ��������������Ƴ���ɵ�ֵ
    if (avg->count == avg->size) {
        avg->sum -= avg->values[avg->index];
    } else {
        avg->count++;
    }

    // �����ֵ������
    avg->values[avg->index] = new_value;
    avg->sum += new_value;

    // ���µ�ǰ����λ��
    avg->index = (avg->index + 1) % avg->size;

    // ���ص�ǰ����ƽ��ֵ
    return avg->sum / avg->count;
}

void data_process_thread_entry(void *parameter)
{
	// ʹ�þ�̬�����ʼ������ƽ���ṹ
	SlidingAverage avg1;
	SlidingAverage avg2;
	SlidingAverage avg3;
	SlidingAverage avg4;
	SlidingAverage avg5;

	init_sliding_average(&avg1, AVERAGE_SIZE);
	init_sliding_average(&avg2, AVERAGE_SIZE);
	init_sliding_average(&avg3, AVERAGE_SIZE);
	init_sliding_average(&avg4, AVERAGE_SIZE);
	init_sliding_average(&avg5, AVERAGE_SIZE);
	while(1)
	{
		rt_sem_t data_process_sem = get_data_process_sem();
		rt_err_t result = rt_sem_take(data_process_sem, RT_WAITING_FOREVER);
		
		if(result == RT_EOK){
			
			if(data.R1 > 3000)
				data.R1 = 3000;
			if(data.R1 < 0)
				data.R1 = 0;
			
			if(data.R2 > 3000)
				data.R2 = 3000;
			if(data.R2 < 0)
				data.R2 = 0;
			
			if(data.R3 > 3000)
				data.R3 = 3000;
			if(data.R3 < 0)
				data.R3 = 0;
			
			if(data.R4 > 3000)
				data.R4 = 3000;
			if(data.R4 < 0)
				data.R4 = 0;
			
			data.averageVoltage = update_sliding_average(&avg1, data.Voltage);
			data.averageR1 = update_sliding_average(&avg2, data.R1);
			data.averageR2 = update_sliding_average(&avg3, data.R2);
			data.averageR3 = update_sliding_average(&avg4, data.R3);
			data.averageR4 = update_sliding_average(&avg5, data.R4);
//			rt_kprintf("Voltage: %d mV, Sliding Average: %d mV\r\n", (int)(data.Voltage * 1000.0), (int)(data.averageVoltage * 1000.0));
		}
	}
}

