#ifndef __FOC_H__
#define __FOC_H__
#include "main.h"
#include "mt6816.h"
#include "tb67h450.h"
#include "math.h"
#include "flash.h"

typedef struct{
	uint8_t	sector;	
	int	scope;	
	int16_t angle;
	int lead_angle;
	float speed_error;
}FOC_parameter;
extern FOC_parameter foc;

void FOC_Init(void);
void Sector_tracker(void);
void FOC_Ctrl(int16_t Iq, int16_t Id);


#endif
