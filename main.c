
#include "stm32f10x.h"
#include "bsp_led.h"
#include "includes.h"

#define SOFT_DELAY Delay(0x0FFFFF);

//void Delay(__IO u32 nCount); 

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

#define LED0_TASK_PRIO       	5

#define LED0_STK_SIZE  	    	64

OS_STK LED0_TASK_STK[LED0_STK_SIZE];

void led0_task(void *pdata);
 
 

#define LED1_TASK_PRIO       	6

#define LED1_STK_SIZE  	64

OS_STK LED1_TASK_STK[LED1_STK_SIZE];

void led1_task(void *pdata);
 
#define LED2_TASK_PRIO       	7

#define LED2_STK_SIZE  	64

OS_STK LED2_TASK_STK[LED1_STK_SIZE];

void led2_task(void *pdata);
 
INT8U err;
 
OS_EVENT *msg_key;

 
int main(void)
{
 
	
	
	LED_GPIO_Config();
OSInit();   
	//OSTmrCreate();
	SysTick_Init();
	//msg_key=OSSemCreate(0);
	msg_key=OSMutexCreate(4,&err);
	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);
	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);
	OSTaskCreate(led2_task,(void *)0,(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],LED2_TASK_PRIO);
OSStart();	  	 
    
    while(1)
{
 
}	 
}
 
void led0_task(void *pdata)
{	 

while(1)
{
	//OSSemPend(msg_key,0,&err);
	OSMutexPend(msg_key,0,&err);
	//OSMutexPend(msg_key,0,&err);
LED1(ON);
	//Delay(10000000);
LED1(OFF);
	OSMutexPost(msg_key);
	OSTimeDlyHMSM(0,0,0,500);
	OSMutexPend(msg_key,0,&err);
	OSMutexPost(msg_key);
	//OSMutexPost(msg_key);
	OSTaskSuspend(LED0_TASK_PRIO);	

	
}
}
 
void led1_task(void *pdata)
{	 

while(1)
{

LED2(ON);
		//Delay(10000000);
LED2(OFF);
	//OSTaskSuspend(LED1_TASK_PRIO);	
	OSTimeDlyHMSM(0,0,0,500);
	
}
}

void led2_task(void *pdata)
{	 

while(1)
{
  OSMutexPend(msg_key,0,&err);
LED3(ON);
		//Delay(10000000);
LED3(OFF);
	OSTimeDlyHMSM(0,0,0,500);
	//OSSemPost(msg_key);
	OSMutexPost(msg_key);
	LED2(ON);
	LED2(OFF);
	OSTaskSuspend(LED2_TASK_PRIO);	
		
	
}
}
