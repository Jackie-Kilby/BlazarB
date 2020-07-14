/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "derivative.h" /* include peripheral declarations */

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/
static volatile int count = 0;
static volatile int irq_need_handle = 0;

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
void SysTick_Handler(void)
{
	unsigned int i;
	
	count++;
	irq_need_handle = 1;
	
	i = SYST_CSR;		//Clear Interrupt flag
}
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	//LED PortC-4 Init
	SIM_SCGC5 |= (1<<10);		//Enable PortB Clock
	PORTB_PCR17 |= 0x100;
	GPIOB_PDDR |= (1<<17);
	GPIOB_PDOR &= ~(1<<17);
	
	asm("CPSIE i");
	SYST_RVR = 0x9FFD07;
	SYST_CVR = 0x00;
	SYST_CSR |= (1<<0) | (1<<1) | (1<<2);
	
	int led_status = 0;
	for (;;) {
		if (!(count%4) && irq_need_handle) {
			irq_need_handle = 0;
			if (led_status) {
//				GPIOB_PCOR |= (1<<17);
				GPIOB_PDOR &= ~(1<<17);
				led_status = 0;
			} else {
//				GPIOB_PSOR |= (1<<17);
				GPIOB_PDOR |= (1<<17);
				led_status = 1;
			}
		}
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

