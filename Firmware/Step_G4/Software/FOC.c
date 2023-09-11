#include "foc.h"
#include "fastsin.h"
FOC_parameter foc;
uint16_t bias = 0;
uint16_t Scope[200];
void FOC_Init(void)
{
	uint8_t i;
	StepCtrl(0);
	foc.lead_angle = 0;			//��ǰ�Ǽ�����Iq��ͬ�����ܳ���512��PI  PID��������(-128)--(+128)
	foc.speed_error = 0;
	for(i=0;i<200;i++)
	{
		Scope[i] = Flash_Read_Angle(i+1) - Flash_Read_Angle(i);//ÿ����Ӧ�Ƕȴ���flash�У�����ÿ���ĵ�Ƕȴ�С����֮��ļ�����
		if(Scope[i] > 200)		//200ֻ�Ǹ�����/ʵ��������82���ң�����200˵��Խ�����
		{
			Scope[i]+=16384;
			bias = i;
		}
	}
}
void Sector_tracker(void)
{
	int temp = (mt6816.angle_data / 82 + bias) % 200;//����ת�ӵ�ǰ������
	for(int i=temp-1;i<=temp+1;i++)
	{
		if(Flash_Read_Angle(i+1) > Flash_Read_Angle(i))
		{
			if(mt6816.angle_data >= Flash_Read_Angle(i) && mt6816.angle_data <= Flash_Read_Angle(i+1))
			{
				foc.sector = (i+200)%200;
				break;
			}
		}
		else if(Flash_Read_Angle(i+1) < Flash_Read_Angle(i))
		{
			if(mt6816.angle_data >= Flash_Read_Angle(i) && mt6816.angle_data <= (Flash_Read_Angle(i+1) + 16384))
			{
				foc.sector = (i+200)%200;
				break;
			}
		}
	}
	foc.scope = Scope[foc.sector];
	if(Flash_Read_Angle(foc.sector+1) > Flash_Read_Angle(foc.sector))//�����Ƕ�
		foc.angle = (mt6816.angle_data - Flash_Read_Angle(foc.sector)) * 256 / foc.scope;
	else
	{
		if(mt6816.angle_data > 16200)		//16200ֻ�Ǹ�����
			foc.angle = (mt6816.angle_data - Flash_Read_Angle(foc.sector)) * 256 / foc.scope;
		else
			foc.angle = (16384 - Flash_Read_Angle(foc.sector) + mt6816.angle_data) * 256 / foc.scope;
	}
}
void FOC_Ctrl(int16_t Iq, int16_t Id)
{
	int cost,sint;
	int Ia,Ib,x;
	x = (foc.angle + 256 * (foc.sector % 4) + foc.lead_angle) % 1024;
	sint = sin_mp[x];
	cost = sin_mp[(x+256)%1024];
	Ia = (Id * cost - Iq * sint) / 4096;//park���任
	Ib = (Iq * cost + Id * sint) / 4096;
	Set_I(Ia,Ib);
}

