#ifndef __PID_H__
#define __PID_H__
#include "main.h"
#include "mt6816.h"
typedef struct{
	int64_t IS_bias;
	float T_speed;
	int64_t Tim_limit;
	int64_t L_position;
	int L_speed;
	int64_t T_position;
	double R_speed;
	double O_Iposition;
	int64_t Bias_Positoin;
	int64_t Integral_bias_speed;
	float Iqkp;
	float Iqki;
	float Iqkd;
	float Pkp;
	float Pki;
	float Pkd;
	float Akp;
	float Aki;
	float Akd;
	int T_iq;
	int T_id;
	int last_angle;
}PID_parameter;
extern PID_parameter pid;
void PID_init(void);
void Position_PID(void);
void Speed_PID_Iq(void);
void PID_Ctrl(void);
#endif

