#include "pid.h"
#include "math.h"
#include "foc.h"
#include "led.h"
#include "usart.h"
#include "flash.h"
#include "task.h"
PID_parameter pid;
void PID_init(void)
{
	pid.T_position = Flash_Read_Parameter(ZERO);//��flash��ȡ���
	pid.T_speed = 30;//Ŀ���ٶ�  ��ֵ��Ч
	pid.T_id = 0;//Ŀ��id
	pid.T_iq = 0;//Ŀ��iq
	
	pid.Iqkp = Flash_Read_Parameter(PIDIP)/10.0;//������pid����
	pid.Iqki = Flash_Read_Parameter(PIDII)/10.0;
	pid.Iqkd = Flash_Read_Parameter(PIDID)/10.0;//��flash��ȡת������
	
	pid.Pkp = Flash_Read_Parameter(PIDPP)/1000.0;//λ�û�pid����
	pid.Pki = Flash_Read_Parameter(PIDPI)/1000.0;
	pid.Pkd = Flash_Read_Parameter(PIDPD)/1000.0;
	
	pid.Akp = Flash_Read_Parameter(PIDAP)/10.0;//��ǰ��pid����
	pid.Aki = Flash_Read_Parameter(PIDAI)/10.0;
	pid.Akd = Flash_Read_Parameter(PIDAD)/10.0;
//	pid.Iqkp = 15;//������pid����
//	pid.Iqki = 0;
//	pid.Iqkd = 5;//��flash��ȡת������
//	
//	pid.Pkp = 0.03;//λ�û�pid����
//	pid.Pki = 0.01;
//	pid.Pkd = 0.01;
//	
//	pid.Akp = 2.2;//��ǰ��pid����
//	pid.Aki = 0;
//	pid.Akd = 5;
	
	pid.IS_bias = 0;//�ۼƽǶ�
	pid.Tim_limit = 0;//ʱ������
	pid.O_Iposition = 0;//λ�û�����
	REIN_MT6816_Get_AngleData();//��ȡ�������Ƕ�
	pid.last_angle = mt6816.angle_data;//���ڼ���΢��
	pid.Bias_Positoin = pid.T_position - mt6816.angle_data;//����λ��ƫ��/�ͽ�����ͽǶȿ���ʹ��
	pid.Integral_bias_speed = 0;//�ٶȻ�����
	if(pid.Bias_Positoin < -8192)
		pid.Bias_Positoin = 16384 - mt6816.angle_data + pid.T_position;
	if(pid.Bias_Positoin > 8192)
		pid.Bias_Positoin = (pid.T_position - mt6816.angle_data) - 16384;

}
void Position_PID(void)//λ��pid
{
	static int64_t Last_Bias,Bias;
	Bias=-pid.Bias_Positoin;
	if(Bias < 2000 && Bias > -2000)
		if((pid.O_Iposition*pid.Pki < -30 && Bias > 0)||(pid.O_Iposition*pid.Pki > 30 && Bias < 0)||(pid.O_Iposition*pid.Pki >= -30 && pid.O_Iposition*pid.Pki <= 30))
			pid.O_Iposition+=Bias;
	pid.T_speed=(pid.Pkp*Bias+pid.Pki*pid.O_Iposition+pid.Pkd*(Bias-Last_Bias));
	Last_Bias=Bias;
	if(Bias > 100 || Bias < -100)
		LED_RGB(1,0,0);
	else
		LED_RGB(0,1,0);
}
void Speed_PID_Iq(void)//�ٶ�pid
{
	static double Bias,Last_BiasSpeed,Integral_bias=0;
	Bias=pid.T_speed - pid.R_speed;
	foc.speed_error = Bias-Last_BiasSpeed;
	if(Integral_bias * pid.Iqki > -300 && Integral_bias * pid.Iqki < 300)
		Integral_bias+=Bias;
	pid.T_iq=(pid.Iqkp*Bias+pid.Iqki*Integral_bias+pid.Iqkd*(Bias-Last_BiasSpeed));
	if(pid.T_iq > 500)pid.T_iq=500;
	if(pid.T_iq < -500)pid.T_iq=-500;
	Last_BiasSpeed=Bias;

}
void Angle_PID(void)//��ǰ��pid
{
	static double Last_Bias,Integral_bias=0,Bias;
		Bias=-pid.R_speed;
	if(Integral_bias * pid.Aki < 64 && Integral_bias * pid.Aki > -64)
		Integral_bias+=Bias;
	foc.lead_angle=(int)(pid.Akp*Bias+pid.Aki*Integral_bias+pid.Akd*(Bias-Last_Bias));
	if(foc.lead_angle > 512)
		foc.lead_angle = 512;
	if(foc.lead_angle < -512)
		foc.lead_angle = -512;
	foc.lead_angle+=1024;
	Last_Bias=Bias;
}
void PID_Ctrl(void)//����һЩpid��Ҫ�����ݺ�pid����
{
	static uint8_t count = 0;
	static int tbias = 0;
	tbias = (pid.last_angle - (int)mt6816.angle_data);
	if(tbias > 15000)tbias-=16384;
	if(tbias < -15000)tbias+=16384;
	pid.Bias_Positoin += tbias;
	pid.IS_bias += tbias;
	pid.last_angle = mt6816.angle_data;
	count++;
	if(count == 10)
	{
		pid.R_speed = pid.IS_bias / 10.0;
		Position_PID();
		Speed_PID_Iq();
		Angle_PID();
		pid.IS_bias = 0;
		count = 0;
	}
}


