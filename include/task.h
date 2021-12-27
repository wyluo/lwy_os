#ifndef TASK_H
#define TASK_H

#include "../include/FreeRTOS.h"
#include "../include/projdefs.h"

typedef void *TaskHandle_t;

TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                const char* const pcName,
                                const uint32_t ulStackDepth,
                                void* const pvParameters,
                                StackType_t* const puxStackBuffer,
                                TCB_t* const pxTaskBuffer );



#endif


