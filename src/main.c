// Copyright (C) ferraith. All rights reserved.

///
/// @brief Demo application main
/// @author ferraith
///

#include "FreeRTOS.h"
#include "LPC17xx.h"
#include "board.h"
#include "queue_demo.h"
#include "task.h"

void vConfigureTimerForRunTimeStats(void) {
	const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

	/* This function configures a timer that is used as the time base when
	collecting run time statistical information - basically the percentage
	of CPU time that each task is utilising.  It is called automatically when
	the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set
	to 1). */

	/* Power up and feed the timer. */
	LPC_SC->PCONP |= 0x02UL;
	LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & (~(0x3<<2))) | (0x01 << 2);

	 /* Reset Timer 0 */
	LPC_TIM0->TCR = TCR_COUNT_RESET;

	/* Just count up. */
	LPC_TIM0->CTCR = CTCR_CTM_TIMER;

	/* Prescale to a frequency that is good enough to get a decent resolution,
	but not too fast so as to overflow all the time. */
	LPC_TIM0->PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

	/* Start the counter. */
	LPC_TIM0->TCR = TCR_COUNT_ENABLE;
}


void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	 /* This function will get called if a task overflows its stack. */

	(void) pxTask;
	(void) pcTaskName;

	for( ;; );
}


int main(void) {
	/* Init hardware */
	console_init();

	/* Run demos */
	run_queue_demo();

	/* Start the tasks running. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running. If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for(;;);
	return 0;
}
