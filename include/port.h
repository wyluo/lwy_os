#ifndef PORT_H
#define PORT_H

#include "../include/portmacro.h"
#include "../include/projdefs.h"

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack,
									TaskFunction_t pxCode,
									void *pvParameters );
BaseType_t xPortStartScheduler(void);


#endif
