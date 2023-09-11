#include "tb67h450.h"
#include "math.h"
void init_TB67H450(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	HAL_GPIO_WritePin(AP_GPIO_Port,AP_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AM_GPIO_Port,AM_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BP_GPIO_Port,BP_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BM_GPIO_Port,BM_Pin,GPIO_PIN_RESET);
	Set_I(300,300);
}
void StepCtrl(uint8_t step)
{
	static uint8_t last_step = 5;
	if(step != last_step)
	{
		if(step == 0)
		{
			HAL_GPIO_WritePin(GPIOA,AP_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,AM_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,BP_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,BM_Pin,GPIO_PIN_RESET);
		}
		if(step == 1)
		{
			HAL_GPIO_WritePin(GPIOA,AP_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,AM_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,BP_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,BM_Pin,GPIO_PIN_RESET);
		}
		if(step == 2)
		{
			HAL_GPIO_WritePin(GPIOA,AP_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,AM_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,BP_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,BM_Pin,GPIO_PIN_RESET);
		}
		if(step == 3)
		{
			HAL_GPIO_WritePin(GPIOA,AP_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,AM_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,BP_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,BM_Pin,GPIO_PIN_SET);
		}
		last_step = step;
	}
}

void Set_I(int Ia,int Ib)//实际电流 = I * 3.3 / 1000
{
	if(Ia > 0)
	{
		HAL_GPIO_WritePin(GPIOA,AM_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,AP_Pin,GPIO_PIN_RESET);
	}
	else
	{
		Ia = -Ia;
		HAL_GPIO_WritePin(GPIOA,AM_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,AP_Pin,GPIO_PIN_SET);
	}
	if(Ib > 0)
	{
		HAL_GPIO_WritePin(GPIOA,BM_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,BP_Pin,GPIO_PIN_RESET);
	}
	else
	{
		Ib = -Ib;
		HAL_GPIO_WritePin(GPIOA,BM_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,BP_Pin,GPIO_PIN_SET);
	}
	TIM2->CCR4 = Ia;
	TIM2->CCR3 = Ib;
}
