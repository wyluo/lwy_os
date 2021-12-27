
#include "../include/task.h"

List_t pxReadyTasksLists[configMax_PRIORITIES];

static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,
								  const char* const pcName.
								  const uint32_t ulStackDepth,
								  void* const pvParameters,
								  TaskHandle_t* const pxCreatedTask,
								  TCB_t *pxNewTCB );


#if (configSUPPORT_STACK_ALLOCATION == 1)
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                const char* const pcName,
                                const uint32_t ulStackDepth,
                                void* const pvParameters,
                                StackType_t* const puxStackBuffer,
                                TCB_t* const pxTaskBuffer )
{
    TCB_t *pxNewTCB;
	TaskHandle_t xReturn;
	if( (puxStackBuffer != NULL) && (pxTaskBuffer != NULL) )
	{
		pxNewTCB = TCB_t *pxTaskBuffer;
		pxNewTCB->pxStack = StackType_t *puxStackBuffer;
		
		//创建新的任务
		prvInitialiseNewTask( pxTaskCode,
							  pcName,
							  ulStackDepth,
							  pvParameters,
							  &xReturn,
							  pxNewTCB );
	}
	else
	{
		xReturn = NULL;
	}
	return xReturn;
}                                
#endif

static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,
								  const char* const pcName.
								  const uint32_t ulStackDepth,
								  void* const pvParameters,
								  TaskHandle_t* const pxCreatedTask,
								  TCB_t *pxNewTCB )
{
	StackType_t *pxTopOfStack;
	UBaseType_t x;
	
	//获取栈顶地址
	pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - (uint32_t) 1 );
	//向下做8字节对齐
	pxTopOfStack = (StackType_t*) (((uint32_t) pxTopOfStack) & (~((uint32_t) 0x0007 )));
	
	//将任务的名字存储在TCB中
	for(x = (UBaseType_t) 0; x < (UBaseType_t) configMAX_TASK_NAME_LEN; x++)
	{
		pxNewTCB->pcTaskName[x] = pcName[x];
		if(pcName[x] == 0x00)
		{
			break;
		}
	}
	//限制任务名字长度
	pxNewTCB->pcTaskName[configMAX_TASK_NAME_LEN - 1] = '\0';
	//初始化任务栈
	pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pxTaskCode, pvParameters);
	if((void*) pxCreatedTask != NULL)
	{
		*pxCreatedTask = (TaskHandle_t) pxNewTCB;
	}
}

void vTaskStartScheduler(void)
{
	pxCurrentTCB = &Task1TCB;

	if(xPortStartScheduler() != pdFALSE)
	{
		//
	}
}