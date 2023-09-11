#include "Flash.h"
#include <stdio.h>
#include "mt6816.h"
#include "tb67h450.h"

static FLASH_EraseInitTypeDef EraseInitStruct;
uint32_t PAGEError = 0;
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }

  return page;
}
void Flash_Erase(void)
{  	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page = GetPage(FLASH_USER_START_ADDR);
	EraseInitStruct.NbPages     = 2;
	EraseInitStruct.Banks = FLASH_BANK_1;
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)  
	{
		HAL_FLASH_Lock();  
		printf(" Error...1\r\n");
		Error_Handler( );
	}
}   
void Flash_Write(uint16_t *pBuffer,uint16_t NumToWrite)
{
	uint16_t  i=0;
	uint32_t Address = FLASH_USER_START_ADDR;

	HAL_FLASH_Unlock();	    //解锁
	Flash_Erase( );         //先擦除
	while( (Address < FLASH_USER_END_ADDR) && (i<NumToWrite))    
	{
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, pBuffer[i]) == HAL_OK)
		{
				Address = Address + 8;  //地址后移4个字节
				i++;
		}
	}
	HAL_FLASH_Lock();   //上锁
}

uint16_t Flash_Read_Angle(int addr)
{
	if(addr>=0 && addr<400)
	{
		if(addr < 0) addr += 200;
		if(addr >= 200) addr %= 200;
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + addr * 8);
	}
}
uint16_t Flash_Read_Parameter(int addr)
{
	if(addr == ZERO)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 200 * 8);
	}
	if(addr == PIDIP)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 201 * 8);
	}
	if(addr == PIDII)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 202 * 8);
	}
	if(addr == PIDID)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 203 * 8);
	}
	if(addr == PIDPP)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 204 * 8);
	}
	if(addr == PIDPI)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 205 * 8);
	}
	if(addr == PIDPD)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 206 * 8);
	}
	if(addr == PIDAP)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 207 * 8);
	}
	if(addr == PIDAI)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 208 * 8);
	}
	if(addr == PIDAD)
	{
		return *(__IO uint32_t *)(FLASH_USER_START_ADDR + 209 * 8);
	}
}
void Updata(uint16_t zero,PID_parameter *pid)
{
	uint16_t temp[210];
	for(int i = 0;i<200;i++)
	{
		temp[i] = Flash_Read_Angle(i);
	}
	temp[200] = zero;
	temp[201] = (pid->Iqkp*10);
	temp[202] = (pid->Iqki*10);
	temp[203] = (pid->Iqkd*10);
	temp[204] = (pid->Pkp*1000);
	temp[205] = (pid->Pki*1000);
	temp[206] = (pid->Pkd*1000);
	temp[207] = (pid->Akp*10);
	temp[208] = (pid->Aki*10);
	temp[209] = (pid->Akd*10);
	Flash_Write(temp,210);
}

