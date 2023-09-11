#include "adc.h"
#include "main.h"

typedef struct{
	uint16_t	adc1;	
	uint16_t	adc2;	
	float volt;
	float temperature;
}adcs;
extern adcs myADC;
void ADC_Updata(void);
