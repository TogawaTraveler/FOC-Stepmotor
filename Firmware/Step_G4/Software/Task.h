#ifndef __TASK_H__
#define __TASK_H__
#include "main.h"
#include "stdio.h"
#include "foc.h"
#include "usart.h"
#include "tim.h"
#include "pid.h"
#include "analog.h"
#define ID 'E'
extern uint8_t uart1_rx_buffer[16];
extern uint8_t uart1_tx_buffer[16];
extern uint8_t uart1_rx_count;
extern uint8_t uart1_tx_count;
extern int cmd_speed;
extern int low_speed;
extern char updata_info[33];
void Enable_IT(void);
void Enable_DMA(void);
void Close_loop(void);
void Manage_Command(void);
void Inform_Updata(float speed,float volt,float tem);
#endif

