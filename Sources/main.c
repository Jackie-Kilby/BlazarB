/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "derivative.h" /* include peripheral declarations */
#include "app_button.h"

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
void SysTick_Handler(void)
{
	unsigned int i;
	(void)i;			//Solve the warning "set but not used"
	
	//User Code
	static int led_status = 0;
	
	if (led_status) {
		GPIOC_PCOR |= (1<<4);
		led_status = 0;
	} else {
		GPIOC_PSOR |= (1<<4);
		led_status = 1;
	}
	
	//Clear Interrupt flag
	i = SYST_CSR;		
}

void PORTA_IRQHandler(void)
{
	static unsigned char frequency = 1;
	if (frequency == 1) {
		SYST_RVR = 0x9FFD07 / 2;
		frequency = 2;
	} else if (frequency == 2) {
		SYST_RVR = 0x9FFD07;
		frequency = 1;
	}
	
	PORTA_PCR5 |= (1<<24);
}
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	//LED PortC-4 (D4 Green) Init
	SIM_SCGC5 |= (1<<11) | (1<<9);		//Enable PortC and PortA Clock
	PORTC_PCR4 |= 0x100;
	GPIOC_PDDR |= (1<<4);
	GPIOC_PDOR &= ~(1<<4);
	
	//Button PortA-5 (Key A) Init
	PORTA_PCR5 |= 0x100;
	GPIOC_PDDR &= ~(1<<5);
	PORTA_PCR5 |= (1<<1) | (1<<0);
	
	asm("CPSIE i");
	
	NVIC_ISER |= (1<<30);		//Enable PortA GPIO Interrupt
	PORTA_PCR5 |= (10<<16);		//Interrupt on falling-edge
	PORTA_PCR5 |= (1<<24);		//Clear Interrupt
	
	SYST_RVR = 0x9FFD07;
	SYST_CVR = 0x00;
	SYST_CSR |= (1<<0) | (1<<1) | (1<<2);
	
	for (;;) {

	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

