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

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	//LED PortC-4 Init
	SIM_SCGC5 |= (1<<11);		//Enable PortB Clock
	PORTC_PCR4 |= 0x100;
	GPIOC_PDDR |= (1<<4);
	GPIOC_PDOR &= ~(1<<4);
	
	asm("CPSIE i");
	SYST_RVR = 0x9FFD07;
	SYST_CVR = 0x00;
	SYST_CSR |= (1<<0) | (1<<1) | (1<<2);
	
	for (;;) {

	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

