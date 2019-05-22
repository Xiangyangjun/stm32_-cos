# stm32_-cos
基于STM32开发板，移植ucos-II操作系统，并创建任务进行调度。  
实验开发板：野火指南者stm32f103ze开发板。  
固件库：stm32f103标准库  
## 任务
添加主函数mian.c,主函数中有两个任务，用来实现led灯不断地闪烁，设定每1.8s任务切换一次。
## 信号量
通过添加计数信号量和互斥信号量来改变LED灯的闪烁顺序
### 计数信号量
给共享资源一个标志，该标志表示该共享资源的占用情况。  
相关函数  
1、	创建信号量：OSSemCreate(INT16U cnt)，cnt为信号量初始计数。  
2、	请求信号量：OSSemPend(OS_EVENT *pevent, INT16U timeout, INT8U *err)，使信号量计数-1，相当于P操作。  
3、	发送信号量：OSSemPost(OS_EVENT *pevent)，使信号量计数+1，相当于V操作。  
```
void task_1(void *pdata)
{	 
OSSemPend(msg_key,0,&err)
 （红灯亮）
}
void task_2(void *pdata)
{	 
（绿灯亮）	
}
void task_3(void *pdata)
{	 
（蓝灯亮）
    OSSemPost(msg_key）	   
}
```
### 互斥信号量
互斥信号量有两个功能：  
1、	给共享资源一个标志，该标志表示该共享资源的占用情况；  
2、	防止优先级反转。  
相关函数  
1、	创建信号量：OSMutexCreate(prio，*err)，prio表示要提升的优先级。  
2、	请求信号量：OSMutexPend(OS_EVENT *pevent, INT16U timeout, INT8U *err)，使信号量计数-1，相当于P操作。  
3、	发送信号量：OSMutexPost(OS_EVENT *pevent)，使信号量计数+1，相当于V操作。  
```
void task_1(void *pdata)
{	 
     OSTimeDlyHMSM(0,0,0,800);
     OSMutexPend(msg_key,0,&err)
    （红灯亮）
}
void task_2(void *pdata)
{	
     OSTimeDlyHMSM(0,0,0,800);
     （绿灯亮）	
}
void task_3(void *pdat)
{	
    OSMutexPend(msg_key,0,&err)
   OSTimeDlyHMSM(0,0,0,800);
（蓝灯亮）
    OSMutexPost(msg_key）
}

```
