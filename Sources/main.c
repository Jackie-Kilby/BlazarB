/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "app_button.h"
#include "app_led.h"
#include "app_os.h"

#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>
#include <stdlib.h>		//For rand func.

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/
static int bMode = 0;

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
void PORTA_IRQHandler(void)
{
	if (!(GPIOA_PDIR & (1<<5))) {
		bMode = ~bMode;
		if (bMode) {
			GPIOB_PDOR &= ~(1<<18);
			GPIOC_PDOR &= ~(1<<2);
		} else {
			GPIOB_PDOR &= ~(1<<18);
			GPIOC_PDOR |= (1<<2);
		}
	}
	PORTA_PCR5 |= (1<<24);		//Clear Interrupt
}

void global_interrupt_enable(void)
{
	asm("CPSIE i");
}

void global_interrupt_disable(void)
{
	asm("CPSID i");
}

void gpioA5_interrupt_enable(void)
{
	NVIC_ISER |= (1<<30);		//Enable PortA GPIO Interrupt
	PORTA_PCR5 |= (10<<16);		//Interrupt on falling-edge
	PORTA_PCR5 |= (1<<24);		//Clear Interrupt
}

/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	led_init();
	button_init();
	global_interrupt_enable();
	gpioA5_interrupt_enable();

	for (;;) {
		delay(10000);
		GPIOC_PTOR |= (1<<2);
		GPIOB_PTOR |= (1<<18);
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

