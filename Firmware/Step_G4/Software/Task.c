#include "task.h"
uint8_t uart1_rx_buffer[16];
uint8_t uart1_tx_buffer[16];
uint8_t uart1_rx_count = 0;
uint8_t uart1_tx_count = 0;
int cmd_speed;
int low_speed;
int cmd_Iq;
_Bool Ce_flag = 0;
char updata_info[33] = "V=+0000.0/U=00.0/T=00.0/P=00000\r\n";
void Enable_IT(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
}
void Enable_DMA(void)
{
	HAL_UART_Receive_DMA(&huart1, (uint8_t *)&uart1_rx_buffer, 16);
	HAL_UART_Transmit_DMA(&huart1,(uint8_t *)updata_info,33);
}
void Manage_Command(void)//命令解析
{
	if(uart1_rx_buffer[0] == 'P' && uart1_rx_buffer[9] == ID)
	{
		uint32_t temp;
		cmd_speed = 0;
		low_speed = 0;

		temp = (uart1_rx_buffer[2]-'0')*1000000 + (uart1_rx_buffer[3]-'0')*100000 + (uart1_rx_buffer[4]-'0')*10000 + (uart1_rx_buffer[5]-'0')*1000 + (uart1_rx_buffer[6]-'0')*100 + (uart1_rx_buffer[7]-'0')*10 + (uart1_rx_buffer[8]-'0');
		if(uart1_rx_buffer[1] == '+')
		{
			pid.Bias_Positoin -= temp;
			pid.Integral_bias_speed -= temp;
		}
		if(uart1_rx_buffer[1] == '-')
		{
			pid.Bias_Positoin += temp;
			pid.Integral_bias_speed += temp;
		}
		uart1_rx_count = 0;
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
	if(uart1_rx_buffer[0] == 'V' && uart1_rx_buffer[6] == ID)
	{
		uint16_t temp;
		low_speed = 0;

		temp = (uart1_rx_buffer[2]-'0')*1000 + (uart1_rx_buffer[3]-'0')*100 + (uart1_rx_buffer[4]-'0')*10 + (uart1_rx_buffer[5]-'0');
		if(uart1_rx_buffer[1] == '+')
		{
			cmd_speed = temp;
		}
		if(uart1_rx_buffer[1] == '-')
		{
			cmd_speed = -temp;
		}
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
	if(uart1_rx_buffer[0] == 'S' && uart1_rx_buffer[4] == ID)
	{
		uint16_t temp;
		cmd_speed = 0;

		temp = (uart1_rx_buffer[2]-'0')*10 + (uart1_rx_buffer[3]-'0');
		if(uart1_rx_buffer[1] == '+')
		{
			low_speed = temp;
		}
		if(uart1_rx_buffer[1] == '-')
		{
			low_speed = -temp;
		}
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
	if(uart1_rx_buffer[0] == 'R' && uart1_rx_buffer[1] == 'E' && uart1_rx_buffer[2] == 'S' && uart1_rx_buffer[5] == ID)
	{
		cmd_speed = 0;
		low_speed = 0;

		int64_t temp = pid.Integral_bias_speed;
		
		pid.Integral_bias_speed = 0;
		pid.Bias_Positoin -= temp;
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
	if(uart1_rx_buffer[0] == 'L' && uart1_rx_buffer[4] == ID)
	{
		int temp;
		cmd_speed = 0;
		low_speed = 0;

		temp = (uart1_rx_buffer[1]-'0')*100 + (uart1_rx_buffer[2]-'0')*10 + (uart1_rx_buffer[3]-'0');
		temp%=360;
		pid.T_position = (int)((temp+180)/360.0*16384 + Flash_Read_Parameter(ZERO))%16384;
		pid.Bias_Positoin = pid.T_position - mt6816.angle_data;
		if(pid.Bias_Positoin < -8192)
			pid.Bias_Positoin = 16384 - mt6816.angle_data + pid.T_position;
		if(pid.Bias_Positoin > 8192)
			pid.Bias_Positoin = (pid.T_position - mt6816.angle_data) - 16384;
		pid.Integral_bias_speed+=pid.Bias_Positoin;
		uart1_rx_count = 0;
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
	if(uart1_rx_buffer[0] == 'O' && uart1_rx_buffer[5] == ID)
	{
		uint16_t temp;
		cmd_speed = 0;
		low_speed = 0;

		temp = (uart1_rx_buffer[2]-'0')*100 + (uart1_rx_buffer[3]-'0')*10 + (uart1_rx_buffer[4]-'0');
		if(uart1_rx_buffer[1] == '+')
			cmd_Iq = temp;
		else
			cmd_Iq = -temp;
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
	if(uart1_rx_buffer[0] == 'U' && uart1_rx_buffer[1] == 'P' && uart1_rx_buffer[2] == 'D' && uart1_rx_buffer[3] == 'A'  && uart1_rx_buffer[4] == 'T'  && uart1_rx_buffer[5] == 'A' && uart1_rx_buffer[6] == ID)
	{
		cmd_speed = 0;
		low_speed = 0;
		Updata(mt6816.angle_data,&pid);
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
		PID_init();
	}
	if(uart1_rx_buffer[0] == 'P' && uart1_rx_buffer[1] == 'I' && uart1_rx_buffer[2] == 'D' && uart1_rx_buffer[8] == ID)
	{
		if(uart1_rx_buffer[3] == 'I')
		{
			uint16_t temp;
			temp = (uart1_rx_buffer[5] - '0')*100 + (uart1_rx_buffer[6] - '0') * 10 + (uart1_rx_buffer[7] - '0');
			if(uart1_rx_buffer[4] == 'P')
			{
				pid.Iqkp = temp/10.0;
			}
			if(uart1_rx_buffer[4] == 'I')
			{
				pid.Iqki = temp/10.0;
			}
			if(uart1_rx_buffer[4] == 'D')
			{
				pid.Iqkd = temp/10.0;
			}
		}
		if(uart1_rx_buffer[3] == 'P')
		{
			uint16_t temp;
			temp = (uart1_rx_buffer[5] - '0')*100 + (uart1_rx_buffer[6] - '0') * 10 + (uart1_rx_buffer[7] - '0');
			if(uart1_rx_buffer[4] == 'P')
			{
				pid.Pkp = temp/1000.0;
			}
			if(uart1_rx_buffer[4] == 'I')
			{
				pid.Pki = temp/1000.0;
			}
			if(uart1_rx_buffer[4] == 'D')
			{
				pid.Pkd = temp/1000.0;
			}
		}
		if(uart1_rx_buffer[3] == 'A')
		{
			uint16_t temp;
			temp = (uart1_rx_buffer[5] - '0')*100 + (uart1_rx_buffer[6] - '0') * 10 + (uart1_rx_buffer[7] - '0');
			if(uart1_rx_buffer[4] == 'P')
			{
				pid.Akp = temp/10.0;
			}
			if(uart1_rx_buffer[4] == 'I')
			{
				pid.Aki = temp/10.0;
			}
			if(uart1_rx_buffer[4] == 'D')
			{
				pid.Akd = temp/10.0;
			}
		}
	}
	if(uart1_rx_buffer[0] == 'P' && uart1_rx_buffer[9] == 'T' && uart1_rx_buffer[14] == ID)
	{
		uint32_t temp;
		cmd_speed = 0;
		low_speed = 0;
		
		
		temp = (uart1_rx_buffer[2]-'0')*1000000 + (uart1_rx_buffer[3]-'0')*100000 + (uart1_rx_buffer[4]-'0')*10000 + (uart1_rx_buffer[5]-'0')*1000 + (uart1_rx_buffer[6]-'0')*100 + (uart1_rx_buffer[7]-'0')*10 + (uart1_rx_buffer[8]-'0');
		if(uart1_rx_buffer[1] == '+')
		{
			pid.L_position += temp;
		}
		if(uart1_rx_buffer[1] == '-')
		{
			pid.L_position -= temp;
		}
		pid.Tim_limit += (uart1_rx_buffer[10]-'0')*1000 + (uart1_rx_buffer[11]-'0')*100 + (uart1_rx_buffer[12]-'0')*10 + (uart1_rx_buffer[13]-'0');
		pid.L_speed = (float)pid.L_position/pid.Tim_limit;
		uart1_rx_count = 0;
		memset(uart1_rx_buffer,0,16);
		pid.O_Iposition = 0;
	}
}
void Close_loop(void)
{
	REIN_MT6816_Get_AngleData();
	Sector_tracker();
	FOC_Ctrl(pid.T_iq,0);
}
void Inform_Updata(float speed,float volt,float tem)//数据上传
{
	uint16_t re_angle = (-mt6816.angle_data+Flash_Read_Parameter(ZERO) + 16384)%16384;
	if(speed>=0)
		updata_info[2] = '+';
	else
	{
		updata_info[2] = '-';
		speed = -speed;
	}
	updata_info[3]=(int)speed/1000 + '0';
	updata_info[4]=((int)speed/100)%10 + '0';
	updata_info[5]=((int)speed/10)%10 + '0';
	updata_info[6]=((int)speed%10) + '0';
	updata_info[8]=(int)(speed*10)%10 + '0';
	updata_info[12]=((int)volt/10) + '0';
	updata_info[13]=((int)volt%10) + '0';
	updata_info[15]=(int)(volt*10)%10 + '0';
	updata_info[19]=((int)tem/10) + '0';
	updata_info[20]=((int)tem%10) + '0';
	updata_info[22]=(int)(tem*10)%10 + '0';
	updata_info[26]=re_angle/10000+'0';
	updata_info[27]=re_angle/1000%10+'0';
	updata_info[28]=re_angle/100%10+'0';
	updata_info[29]=re_angle/10%10+'0';
	updata_info[30]=re_angle%10+'0';
	HAL_UART_Transmit_DMA(&huart1,(uint8_t *)updata_info,33);
}



