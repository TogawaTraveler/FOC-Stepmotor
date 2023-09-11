#include "mt6816.h"
#include "stdio.h"
#include "tb67h450.h"
#include "Flash.h"
#include "led.h"
#define StartServerManageFlashAddress    ((uint32_t)0x08036000)
MT6816_SPI_Signal_Typedef	mt6816_spi;
extern uint16_t error;
extern _Bool Ce_flag;
MT6816_Typedef	mt6816;
void MT6816_Init(void)
{
	mt6816_spi.sample_data = 0;
	mt6816_spi.angle = 0;

	if(!HAL_GPIO_ReadPin(Button_GPIO_Port,Button_Pin))//按住按键上电校准
	{
		Ce_flag = 1;
		uint16_t temp[210] = {0};
		uint8_t i = 0;
		LED_RGB(0,0,1);
		TIM2->CCR4 = 200;
		TIM2->CCR3 = 200;
		StepCtrl(0);
		HAL_Delay(100);
		REIN_MT6816_Get_AngleData();
		StepCtrl(1);
		HAL_Delay(100);
		REIN_MT6816_Get_AngleData();
		StepCtrl(2);
		HAL_Delay(100);
		REIN_MT6816_Get_AngleData();
		StepCtrl(3);
		HAL_Delay(100);
		REIN_MT6816_Get_AngleData();
		while(i<201)
		{
			StepCtrl(i%4);
			HAL_Delay(100);
			REIN_MT6816_Get_AngleData();
			temp[i] = mt6816.angle_data;
//			printf("%d\r\n",mt6816.angle_data);
			i++;
		}
		temp[201] = 150;
		temp[202] = 0;
		temp[203] = 50;
		temp[204] = 30;
		temp[205] = 10;
		temp[206] = 10;
		temp[207] = 22;
		temp[208] = 0;
		temp[209] = 50;
		Flash_Write(temp,210);
	}

}

void RINE_MT6816_SPI_Get_AngleData(void)
{
	uint16_t data_t[2];
	uint16_t data_r[2];
	uint8_t h_count;
	data_t[0] = (0x80 | 0x03) << 8;
	data_t[1] = (0x80 | 0x04) << 8;
	for(uint8_t i=0; i<3; i++)
	{
		//读取SPI数据
		MT6816_SPI_CS_L();
		HAL_SPI_TransmitReceive(&MT6816_SPI_Get_HSPI, (uint8_t*)&data_t[0], (uint8_t*)&data_r[0], 1, HAL_MAX_DELAY);
		MT6816_SPI_CS_H();
		MT6816_SPI_CS_L();
		HAL_SPI_TransmitReceive(&MT6816_SPI_Get_HSPI, (uint8_t*)&data_t[1], (uint8_t*)&data_r[1], 1, HAL_MAX_DELAY);
		MT6816_SPI_CS_H();
		mt6816_spi.sample_data = ((data_r[0] & 0x00FF) << 8) | (data_r[1] & 0x00FF);
		//奇偶校验
		h_count = 0;
		for(uint8_t j=0; j<16; j++)
		{
			if(mt6816_spi.sample_data & (0x0001 << j))
				h_count++;
		}
		if(h_count & 0x01)
			{
			mt6816_spi.pc_flag = false;
		}
		else
		{
			mt6816_spi.pc_flag = true;
			break;
		}
	}
	if(mt6816_spi.pc_flag)
	{
		mt6816_spi.angle = mt6816_spi.sample_data >> 2;
		mt6816_spi.no_mag_flag = (bool)(mt6816_spi.sample_data & (0x0001 << 1));
	}
}



void REIN_MT6816_Get_AngleData(void)
{
	RINE_MT6816_SPI_Get_AngleData();
	mt6816.angle_data = mt6816_spi.angle;
}
