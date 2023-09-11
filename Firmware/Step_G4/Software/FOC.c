#include "foc.h"
#include "fastsin.h"
FOC_parameter foc;
uint16_t bias = 0;
uint16_t Scope[200];
void FOC_Init(void)
{
	uint8_t i;
	StepCtrl(0);
	foc.lead_angle = 0;			//超前角极性与Iq相同，不能超过512即PI  PID适用区间(-128)--(+128)
	foc.speed_error = 0;
	for(i=0;i<200;i++)
	{
		Scope[i] = Flash_Read_Angle(i+1) - Flash_Read_Angle(i);//每步对应角度存在flash中，计算每步的电角度大小减少之后的计算量
		if(Scope[i] > 200)		//200只是个概数/实际数据是82左右，大于200说明越过零点
		{
			Scope[i]+=16384;
			bias = i;
		}
	}
}
void Sector_tracker(void)
{
	int temp = (mt6816.angle_data / 82 + bias) % 200;//计算转子当前的扇区
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
	if(Flash_Read_Angle(foc.sector+1) > Flash_Read_Angle(foc.sector))//计算电角度
		foc.angle = (mt6816.angle_data - Flash_Read_Angle(foc.sector)) * 256 / foc.scope;
	else
	{
		if(mt6816.angle_data > 16200)		//16200只是个概数
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
	Ia = (Id * cost - Iq * sint) / 4096;//park反变换
	Ib = (Iq * cost + Id * sint) / 4096;
	Set_I(Ia,Ib);
}

