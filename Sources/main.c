/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

#define JITTER_CNT	1
#define PERIOD		100


void delay(int delay_time) {
	unsigned short i, j;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < delay_time; j++) {
//			asm{"nop"};
		}
	}
}

int main(void) {
	int counter = 0;
	int on_time = 300;

	//PortC Clock Gating
	SIM_SCGC5 |= (1 << 11);
	//PortA Clock Gating
	SIM_SCGC5 |= (1 << 9);

	//Select MUX feature as GPIO for PortC-GPIO5(LED1-Blue) and PortC-GPIO0(LED2-Green)
	PORTC_PCR5 |= 0x100;
	PORTC_PCR0 |= 0x100;
	//Select MUX feature as GPIO for PortA-GPIO5(Button-A) and PortA-GPIO12(Button-B) and PortA-GPIO19(Button-C)
	PORTA_PCR5 |= 0x100;
	PORTA_PCR12 |= 0x100;
	PORTA_PCR19 |= 0x100;

	//Init PortC-GPIO5(LED1-Blue) and PortC-GPIO0(LED2-Green) as output LOW
	GPIOC_PDDR |= (1 << 5) | (1 << 0);
	GPIOC_PDOR &= ~(1 << 5);
	GPIOC_PDOR |= (1 << 0);
	//Init PortA-GPIO5(Button-A) and PortA-GPIO12(Button-B) and PortA-GPIO19(Button-C) as Input Pullup
	PORTA_PCR5 |= (1<<1) | (1<<0);
	PORTA_PCR12 |= (1<<1) | (1<<0);
	PORTA_PCR19 |= (1<<1) | (1<<0);

	for (;;) {
		counter++;
		//Breathing light
		//Step 1
		for (on_time=0 ; on_time<PERIOD ; on_time++) {
			//on
			GPIOC_PDOR |= (1<<5);
			//delay++
			delay(on_time);
			//off
			GPIOC_PDOR &= ~(1<<5);
			//delay--
			delay(PERIOD-on_time);
		}
		for (on_time=0 ; on_time<PERIOD ; on_time++) {
			//on
			GPIOC_PDOR |= (1<<5);
			//delay++
			delay(PERIOD-on_time);
			//off
			GPIOC_PDOR &= ~(1<<5);
			//delay--
			delay(on_time);
		}
		GPIOC_PTOR |= (1<<0);
	}

	return 0;
}

//Blink with delay
void led_blink_mode_1(void)					
{
	delay(200);
	GPIOC_PTOR |= (1<<5) | (1<<0);
}

//Button press -> LED on.
void led_blink_mode_2(void)
{
	static int jitterA = 0, jitterB = 0;
	
	//Button-A control PortC-GPIO5(LED1-Blue)
	if (!(GPIOA_PDIR & (1 << 5))) {
		jitterA++;
		if (jitterA == JITTER_CNT) {
			GPIOC_PDOR |= (1 << 5);
		}
	} else {
		GPIOC_PDOR &= ~(1 << 5);
		if (jitterA) {
			jitterA = 0;
		}
	}
	//Button-B control PortC-GPIO0(LED2-Green)
	if (!(GPIOA_PDIR & (1 << 12))) {
		jitterB ++;
		if (jitterB == JITTER_CNT) {
			GPIOC_PDOR |= (1 << 0);
		}
	} else {
		GPIOC_PDOR &= ~(1 << 0);
		if (jitterB) {
			jitterB = 0;
		}
	}
}

//Breathing Blink
void led_blink_mode_3(void)
{
	
}
