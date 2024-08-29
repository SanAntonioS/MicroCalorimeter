#include "InitAD7177.h"

//����ADC 1-3 �����ṹ��--------------------------------------------------------
struct ad717x_device device1 ={.slave_select_id=1};
struct ad717x_device device2 ={.slave_select_id=2};
struct ad717x_device device3 ={.slave_select_id=3};
struct ad717x_device device4 ={.slave_select_id=4};
struct ad717x_device device5 ={.slave_select_id=5};
struct ad717x_device device6 ={.slave_select_id=6};
struct ad717x_device device7 ={.slave_select_id=7};
struct ad717x_device device8 ={.slave_select_id=8};

//����AD7177���Ĵ�������Ϣ------------------------------------------------------
ad717x_st_reg ad7177_2_regs[] =
{
  { AD717X_STATUS_REG,    0x00,  1},
  { AD717X_ADCMODE_REG,   0x0000,2},
  { AD717X_IFMODE_REG,    AD717X_IFMODE_REG_DOUT_RESET | AD717X_IFMODE_REG_CRC_EN,  2},
  { AD717X_REGCHECK_REG,  0x0000,3},
  { AD717X_DATA_REG,      0x0000,4},
  { AD717X_GPIOCON_REG,   0x0000,2},
  { AD717X_ID_REG,        0x0000,2},
  { AD717X_CHMAP0_REG,    AD717X_CHMAP_REG_CH_EN | AD717X_CHMAP_REG_AINNEG(2),2},
  { AD717X_CHMAP1_REG,    0x0000,2},
  { AD717X_CHMAP2_REG,    0x0000,2},
  { AD717X_CHMAP3_REG,    0x0000,2},
  { AD717X_SETUPCON0_REG, 0x0000,2},
  { AD717X_SETUPCON1_REG, 0x0000,2},
  { AD717X_SETUPCON2_REG, 0x0000,2},
  { AD717X_SETUPCON3_REG, 0x0000,2},
  { AD717X_FILTCON0_REG,  AD717X_FILT_CONF_REG_ENHFILT(2) | AD717X_FILT_CONF_REG_ODR(10),2},
  { AD717X_FILTCON1_REG,  AD717X_FILT_CONF_REG_ENHFILT(2),2},
  { AD717X_FILTCON2_REG,  AD717X_FILT_CONF_REG_ENHFILT(2),2},
  { AD717X_FILTCON3_REG,  AD717X_FILT_CONF_REG_ENHFILT(2),2},
  { AD717X_OFFSET0_REG,   0, 3 },
  { AD717X_OFFSET1_REG,   0, 3 },
  { AD717X_OFFSET2_REG,   0, 3 },
  { AD717X_OFFSET3_REG,   0, 3 },
  { AD717X_GAIN0_REG,     0, 3 },
  { AD717X_GAIN1_REG,     0, 3 },
  { AD717X_GAIN2_REG,     0, 3 },
  { AD717X_GAIN3_REG,     0, 3 },
};
//------------------------------------------------------------------------------

/*******************************************************************************
* �� �� ����InitAD7177
* ����ԭ�Σ�void InitAD7177(void)
* ��������: AD7177 ��ʼ������ 
* �����������
* �����������
* �� �� ֵ����
* �Ⱦ�������
* �����ú�����
* ��    �ߣ�������
* ��    ��: 2016-02-25
*******************************************************************************/
void InitAD7177(struct ad717x_device *device,uint32_t addr)
{
  unsigned char ID_testy=0;//�Ĵ�����ȡ�����ݴ����
  
	//�ٳ�ʼ��AD IOSPI 1 ------------------------------------------------------
	AD_IOSPI_Init(device->slave_select_id);
	//�ڸ�λADC-----------------------------------------------------------------
	device->num_regs = 27;    //27���Ĵ���
	device->useCRC = AD717X_DISABLE; //CRCУ�����
	AD717X_Reset(device); //��λ AD
	AD1_SCLK_HIGH;
	AD1_MOSI_HIGH;
	rt_hw_us_delay(600);        //��ʱ 500us����
	//�ۼĴ�������-------------------------------------------------------------
	for (unsigned char AD7177_initCNT = 0; AD7177_initCNT < device->num_regs; AD7177_initCNT++)
	{
		ad7177_2_regs[AD7177_initCNT].value = 0;
		device->regs = &ad7177_2_regs[AD7177_initCNT];
		if (AD717X_ReadRegister(device, ad7177_2_regs[AD7177_initCNT].addr) < 0)
		{
			ID_testy = 0xff;  //��AD7177�Ĵ�������  
		}
	}
	device->regs = &ad7177_2_regs[0]; 
	//�ܳ�ʼ�����Ĵ���ֵ------------------------------------------------------
	//��1�����ò������ͨ��
	ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
		+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
	AD717X_WriteRegister( device, AD717X_CHMAP0_REG);  
	//��2���ӿڼĴ�����ѡ��ת��λ��
	ad7177_2_regs[2].value =  AD717X_IFMODE_REG_WL32;                       
	AD717X_WriteRegister( device, AD717X_IFMODE_REG); 
	//��3������ADCģʽ�Ĵ���
	ad7177_2_regs[1].value = AD717X_ADCMODE_REG_HIDE_DELAY //��ʱ����
		+AD717X_ADCMODE_SING_CYC(0)
			+AD717X_ADCMODE_REG_MODE(0)      //����ת��ģʽ
				//+AD717X_ADCMODE_REG_MODE(1)      //����ת��ģʽ
				+AD717X_ADCMODE_REG_CLKSEL(0);//ѡ��ʱ��Դ 0-�ڲ�ʱ��
	AD717X_WriteRegister( device, AD717X_ADCMODE_REG);  
	//��4������ADC���üĴ���-
	ad7177_2_regs[11].value = AD717X_SETUP_CONF_REG_BI_UNIPOLAR // ����ADC ���� ���˴�Ϊ˫����
		+ AD717X_SETUP_CONF_REG_REFBUF_P //   (1 << 11)
			+ AD717X_SETUP_CONF_REG_REFBUF_N //   (1 << 10)
				+ AD717X_SETUP_CONF_REG_AINBUF_P //   (1 << 9)
					+ AD717X_SETUP_CONF_REG_AINBUF_N //   (1 << 8)
						+ AD717X_SETUP_CONF_REG_REF_SEL(0);   // ѡ���ⲿ��׼��ѹԴ
	AD717X_WriteRegister( device, AD717X_SETUPCON0_REG);
	 //��5�������˲������üĴ��� ��ѡ���˲�����ADC������ʣ�
	ad7177_2_regs[15].value = AD717X_FILT_CONF_REG_SINC3_MAP(0) // SINC3_MAP0  
		+ AD717X_FILT_CONF_REG_ORDER(0)  // �����˲�������
			+ AD717X_FILT_CONF_REG_ODR(0x09); // ADC ����������� 0x14-> 5sps ;0x13-> 10sps ;0x12-> 16.66sps
	AD717X_WriteRegister( device, AD717X_FILTCON0_REG);  
  DisableIOSPI(device->slave_select_id);
}

