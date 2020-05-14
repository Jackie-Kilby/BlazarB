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
	
	//Select MUX feature as GPIO for PortC-GPIO5(LED1-Blue) and PortC-GPIO0(LED2-Green)
	PORTC_PCR5 |= (1<<8);
	PORTC_PCR0 |= (1<<8);
	
	//Init PortC-GPIO5(LED1-Blue) and PortC-GPIO0(LED2-Green) as output LOW
	GPIOC_PDDR |= (1<<5) | (1<<0);
	GPIOC_PDOR &= ~(1<<5);
	GPIOC_PDOR |= (1<<0);

	for(;;) {	   
	   	counter++;
	   	delay();
	   	
	   	//Toggle PortC-GPIO5(LED1-Blue)
	   	GPIOC_PTOR |= (1<<5)|(1<<0);
	}
	
	return 0;
}
