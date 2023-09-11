#include "led.h"
void init_LED(void)
{
	TIM1->CCR1 = 1000;
	TIM1->CCR2 = 1000;
	TIM1->CCR3 = 1000;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
}
void LED_RGB(_Bool R,_Bool G,_Bool B)
{
	if(R)
		TIM1->CCR2 = 0;
	else
		TIM1->CCR2 = 1000;
	if(G)
		TIM1->CCR1 = 0;
	else
		TIM1->CCR1 = 1000;
	if(B)
		TIM1->CCR3 = 0;
	else
		TIM1->CCR3 = 1000;
}

