/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

void delay(void)
{
	unsigned short i,j;
	for (i=0 ; i<3000 ; i++) {
		for (j=0 ; j<200 ; j++) {
//			asm{"nop"};
		}
	}
}

int main(void)
{
	int counter = 0;
	
	//PortC Init
	SIM_SCGC5 |= (1<<11);
	
	//Select MUX feature as GPIO for PortC-GPIO5(LED1-Blue)
	PORTC_PCR5 |= (1<<8);
	
	//Init PortC-GPIO5(LED1-Blue) as output
	GPIOC_PDDR |= (1<<5);

	for(;;) {	   
	   	counter++;
	   	delay();
	   	
	   	//Toggle PortC-GPIO5(LED1-Blue)
	   	GPIOC_PTOR |= (1<<5);
	}
	
	return 0;
}
