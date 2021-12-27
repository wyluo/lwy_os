#include "../include/port.h"
#include "stdint.h"

#define portINITIAL_XPSR  (0x01000000)
#define portSTART_ADDRESS_MASK ((StackType_t) 0xfffffffeUL)
#define portNVIC_SYSPRI2_REG (*((volatile uint32_t*) 0xe00ed20))
#define portNVIC_PENDSV_PRI (((uint32_t) configKERNEL_INTERRUPT_PRIORITY) << 16UL)
#define portNVIC_SYSTICK_PRI (((uint32_t) configKERNEL_INTERRUPT_PRIORITY) << 24UL)

static void prvTaskExitError(void);


__asm void prvStartFirstTask(void)
{
	PRESERVE8

	ldr r0, =0xE000ED08
	ldr r0, [r0]
	ldr r0, [r0]

	//设置主堆栈指针msp的值
	msr msp, r0

	cpsie i
	cpsie f
	dsb
	isb

	svc 0
	nop
	nop
}

static void prvTaskExitError(void)
{
	for(;;);
}

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack,
											TaskFunction_t pxCode,
											void *pvParameters )
{
	//异常发生时，自动加载到cpu寄存器的内容
	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_XPSR;
	pxTopOfStack--;
	*pxTopOfStack = ((StackType_t) pxCode) & portSTART_ADDRESS_MASK;
	pxTopOfStack--;
	*pxTopOfStack = (StackType_t) prvTaskExitError;
	pxTopOfStack -= 5;
	*pxTopOfStack = (StackType_t) pvParameters;

	//异常发生时，手动加载到cpu寄存器的内容
	pxTopOfStack -= 8;

	//返回栈顶指针，此时pxTopOfStack指向空闲栈
	return pxTopOfStack;	
}

BaseType_t xPortStartScheduler(void)
{
	portNVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
	portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;

	prvStartFirstTask();
	return 0;
}


