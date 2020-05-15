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
	unsigned char mode = 1;
	
	//PortC Clock Gating
	SIM_SCGC5 |= (1<<11);
	//PortA Clock Gating
	SIM_SCGC5 |= (1<<9);
	
	//Select MUX feature as GPIO for PortC-GPIO5(LED1-Blue) and PortC-GPIO0(LED2-Green)
	PORTC_PCR5 |= 0x100;
	PORTC_PCR0 |= 0x100;
	//Select MUX feature as GPIO for PortA-GPIO5(Button-A) and PortA-GPIO12(Button-B) and PortA-GPIO19(Button-C)
	PORTA_PCR5 |= 0x100;
	PORTA_PCR12 |= 0x100;
	PORTA_PCR19 |= 0x100;
	
	//Init PortC-GPIO5(LED1-Blue) and PortC-GPIO0(LED2-Green) as output LOW
	GPIOC_PDDR |= (1<<5) | (1<<0);
	GPIOC_PDOR &= ~(1<<5);
	GPIOC_PDOR |= (1<<0);
	//Init PortA-GPIO5(Button-A) and PortA-GPIO12(Button-B) and PortA-GPIO19(Button-C) as Input Pullup
	PORTA_PCR5 |= (1<<1) | (1<<0);
	PORTA_PCR12 |= (1<<1) | (1<<0);
	PORTA_PCR19 |= (1<<1) | (1<<0);

	for(;;) {	   
	   	counter++;
//	   	delay();
	   	//Select mode
	   	if (!(GPIOA_PDIR & (1<<19))) {
	   		mode = !mode;
	   	} 
	   	
	   	if (mode) {
	   		//Mode-1
	   		if (!(GPIOA_PDIR & (1<<5)) || !(GPIOA_PDIR & (1<<12))) {
				GPIOC_PTOR |= (1<<5) | (1<<0);
			}
	   	} else {
			//Mode-2
			//Button-A control PortC-GPIO5(LED1-Blue)
			if (!(GPIOA_PDIR & (1<<5))) {
				GPIOC_PDOR |= (1<<5);
			} else {
				GPIOC_PDOR &= ~(1<<5);
			}
			//Button-B control PortC-GPIO0(LED2-Green)
			if (!(GPIOA_PDIR & (1<<12))) {
				GPIOC_PDOR |= (1<<0);
			} else {
				GPIOC_PDOR &= ~(1<<0);
			}
	   	}
	}
	
	return 0;
}
