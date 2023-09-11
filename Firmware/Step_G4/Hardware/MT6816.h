#ifndef __MT6816_H__
#define __MT6816_H__
#include "main.h"
#include "spi.h"
#include <stdbool.h>	
#include <string.h>		
#include <stdlib.h>		
#include <stdio.h>			
#include <main.h>		

#define MT6816_SPI_CS_H()	   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET) 
#define MT6816_SPI_CS_L()		 HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET) 
#define MT6816_SPI_Get_HSPI		    (hspi1)
#define MT6816_Mode_SPI		        (0x03)	


typedef struct{
	uint16_t	sample_data;	
	uint16_t	angle;				
	bool		no_mag_flag;	
	bool		pc_flag;			
}MT6816_SPI_Signal_Typedef;

void MT6816_Init(void);		
void RINE_MT6816_SPI_Get_AngleData(void);	

typedef struct{
	uint16_t	angle_data;			
	uint16_t	rectify_angle;		
	bool			rectify_valid;		
}MT6816_Typedef;

extern MT6816_Typedef	mt6816;
					
void REIN_MT6816_Get_AngleData(void);


#endif



