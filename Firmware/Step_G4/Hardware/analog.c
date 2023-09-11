#include "analog.h"
#include "temp_tab.h"
#include "usart.h"
adcs myADC;
uint16_t adcBuf[2];
void ADC_Updata(void)//供电电压和驱动器温度计算
{
	float res;
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&adcBuf,2);
	myADC.adc1 = adcBuf[0];
	myADC.adc2 = adcBuf[1];
	myADC.volt = myADC.adc2*0.00886+1.0;
	res = 10.89/(myADC.adc1*0.000805) - 3.3;
	for(int i=0;i<39;i++)
	{
		if(res > temperature[i])
		{
			myADC.temperature = (res - temperature[i])/(temperature[i-1] - temperature[i])*5 + (i-1) * 5 - 40;
			break;
		}
	}
}
