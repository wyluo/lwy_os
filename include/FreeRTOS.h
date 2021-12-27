#ifndef FREERTOS_H
#define FREERTOS_H

#include "portmacro.h"
#include "FreeRTOSConfig.h"

typedef struct taskTaskControlBlock{
    volatile StackType_t *pxTopOfStack;//栈顶指针
    ListItem_t xStateListItem;
    StackType_t *pxStack;//任务栈起始地址
    char pcTaskName[configMAX_TASK_NAME_LEN];
}tskTCB;
typedef tskTCB TCB_t;

#endif