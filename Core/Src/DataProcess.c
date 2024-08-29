#include "DataProcess.h"

#define AVERAGE_SIZE 20		//滑动平均窗口大小

Data_t data;
Flag_t Flag;

extern rt_sem_t get_data_process_sem(void);

// 滑动平均数据结构
typedef struct {
    float values[AVERAGE_SIZE];  // 保存滑动窗口内的值
    int size;        // 滑动窗口的大小
    int index;       // 当前插入值的位置
    int count;       // 当前已填入的元素数量
    float sum;      // 当前窗口内所有值的和
} SlidingAverage;

// 初始化滑动平均结构
void init_sliding_average(SlidingAverage *avg, int size) {
    avg->size = size;
    avg->index = 0;
    avg->count = 0;
    avg->sum = 0.0;
    for (int i = 0; i < size; i++) {
        avg->values[i] = 0.0;  // 初始化数组为0
    }
}

// 计算新的滑动平均值
float update_sliding_average(SlidingAverage *avg, float new_value) {
    // 如果窗口已满，移除最旧的值
    if (avg->count == avg->size) {
        avg->sum -= avg->values[avg->index];
    } else {
        avg->count++;
    }

    // 添加新值到窗口
    avg->values[avg->index] = new_value;
    avg->sum += new_value;

    // 更新当前插入位置
    avg->index = (avg->index + 1) % avg->size;

    // 返回当前滑动平均值
    return avg->sum / avg->count;
}

void data_process_thread_entry(void *parameter)
{
	// 使用静态数组初始化滑动平均结构
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

