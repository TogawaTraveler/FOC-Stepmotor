#ifndef _FLASH_H_
#define _FLASH_H_
#include "main.h"
#include "stm32g4xx_hal_flash_ex.h" 
#include "pid.h"
#define ZERO 1145
#define PIDIP 900
#define PIDII 901
#define PIDID	902
#define PIDPP	903
#define PIDPI 904
#define PIDPD 905
#define PIDAP 906
#define PIDAI 907
#define PIDAD 908
 
#define STM32_FLASH_SIZE 	128 	 	//��ѡSTM32��FLASH������С(��λΪK)
    #if     STM32_FLASH_SIZE < 256      //����������С
    #define STM_SECTOR_SIZE     1024    //1K�ֽ�
    #else 
    #define STM_SECTOR_SIZE	    2048    //2K�ֽ�
#endif
 
#define STM32_FLASH_BASE            0x08000000 		//STM32 FLASH����ʼ��ַ
#define FLASH_USER_START_ADDR   ( STM32_FLASH_BASE + STM_SECTOR_SIZE * 120 ) //дFlash�ĵ�ַ������ӵ�62ҳ��ʼ
#define FLASH_USER_END_ADDR     ( STM32_FLASH_BASE + STM_SECTOR_SIZE * 128 ) //дFlash�ĵ�ַ�������Ե�64ҳ����
 
 
void Flash_Erase(void); 
void Flash_Write(uint16_t *pBuffer,uint16_t NumToWrite);
uint16_t Flash_Read_Angle(int addr);
uint16_t Flash_Read_Parameter(int addr);
void Updata(uint16_t zero,PID_parameter *pid);
 
#endif

