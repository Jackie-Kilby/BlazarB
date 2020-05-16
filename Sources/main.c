/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>

/************************ MACRO Definitions *******************************************/
#define PERIOD		100

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/
void delay(int delay_cnt);
void led_init(void);
void button_init(void);
void led_blink_mode_normal_blink(int on_cnt, int off_cnt);
void led_blink_mode_breath_blink(void);

/************************ Externed Functions Definitions ******************************/
int button_read(void)
{
	int button_ret = 0;
	
	if ( !(GPIOC_PDIR & (1<<9)) )
		button_ret |= (1<<0);
	if ( !(GPIOC_PDIR & (1<<7)) )
		button_ret |= (1<<1);
	if ( !(GPIOC_PDIR & (1<<8)) )
		button_ret |= (1<<2);
	if ( !(GPIOC_PDIR & (1<<6)) )
		button_ret |= (1<<3);
	if ( !(GPIOA_PDIR & (1<<5)) )
		button_ret |= (1<<4);
	if ( !(GPIOA_PDIR & (1<<12)) )
		button_ret |= (1<<5);
	if ( !(GPIOA_PDIR & (1<<19)) )
		button_ret |= (1<<6);
	if ( !(GPIOA_PDIR & (1<<13)) )
		button_ret |= (1<<7);
	
	return button_ret;
}
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	int button_st = 0;
	
	led_init();
	button_init();
	
	for (;;) {
		button_st = button_read();
		if ( button_st & (1<<3))
			led_blink_mode_breath_blink();
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/
/*************************************************************************
* Function Name		:	led_init
* Description		:	Initilize LED GPIOs
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void led_init(void)
{
	/*
	 * Led List:	
	 * 				D4			D7			D8
	 * Red:			PortC-3		PortB-19	PortB-16
	 * Green:		PortC-4		PortC-0		PortB-17
	 * Blue:		PortC-5		PortC-2		PortB-18
	 */
	//Enable Port Clock gate
	SIM_SCGC5 |= (1<<10) | (1<<11);
	//Select MUX as GPIO
	PORTC_PCR3 |= 0x100;
	PORTC_PCR4 |= 0x100;
	PORTC_PCR5 |= 0x100;
	PORTB_PCR19 |= 0x100;
	PORTC_PCR0 |= 0x100;
	PORTC_PCR2 |= 0x100;
	PORTB_PCR16 |= 0x100;
	PORTB_PCR17 |= 0x100;
	PORTB_PCR18 |= 0x100;
	//Init GPIO as output
	GPIOC_PDDR |= (1<<3) | (1<<4) | (1<<5) | (1<<0) | (1<<2);
	GPIOB_PDDR |= (1<<19) | (1<<16) | (1<<17) | (1<<18);
	//Init GPIO as LOW
	GPIOC_PDOR &= ~( (1<<3) | (1<<4) | (1<<5) | (1<<0) | (1<<2) );
	GPIOB_PDOR &= ~( (1<<19) | (1<<16) | (1<<17) | (1<<18) );
}

/*************************************************************************
* Function Name		:	button_init
* Description		:	Initilize Button GPIOs
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void button_init(void)
{
	/*
	 * Button List:
	 * 				UP			DOWN		LEFT		RIGHT
	 * Direction	PortC-9		PortC-7		PortC-8		PortC-6
	 * 				A			B			C			D
	 * Function		PortA-5		PortA-12	PortA-19	PortA-13
	 */
	//Enable Port Clock gate
	SIM_SCGC5 |= (1<<9) | (1<<11);
	//Select MUX as GPIO
	PORTC_PCR9 |= 0x100;
	PORTC_PCR7 |= 0x100;
	PORTC_PCR8 |= 0x100;
	PORTC_PCR6 |= 0x100;
	PORTA_PCR5 |= 0x100;
	PORTA_PCR12 |= 0x100;
	PORTA_PCR19 |= 0x100;
	PORTA_PCR13 |= 0x100;
	//Init GPIO as input
	GPIOC_PDDR &= ~( (1<<9) | (1<<7) | (1<<8) | (1<<6) );
	GPIOA_PDDR &= ~( (1<<5) | (1<<12) | (1<<19) | (1<<13) );
	//Init GPIO as pullup
	PORTC_PCR9 |= (1<<1) | (1<<0);
	PORTC_PCR7 |= (1<<1) | (1<<0);
	PORTC_PCR8 |= (1<<1) | (1<<0);
	PORTC_PCR6 |= (1<<1) | (1<<0);
	PORTA_PCR5 |= (1<<1) | (1<<0);
	PORTA_PCR12 |= (1<<1) | (1<<0);
	PORTA_PCR19 |= (1<<1) | (1<<0);
	PORTA_PCR13 |= (1<<1) | (1<<0);
}

/*************************************************************************
* Function Name		:	delay
* Description		:	Used to delay a period of time, occupying CPU.
* Parameters		:	int	delay_cnt, the cnt of the period.
* Returns			:	void
*************************************************************************/
void delay(int delay_cnt) 
{
	unsigned short i, j;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < delay_cnt; j++) {
			asm("nop");
		}
	}
}

/*************************************************************************
* Function Name		:	led_blink_mode_normal_blink
* Description		:	Normal blink with a certain on and off time
* Parameters		:	int	on_cnt,	The on_cnt of Normal blink
* 						int off_cnt, The off_cnt of Normal blink
* Returns			:	void
*************************************************************************/
void led_blink_mode_normal_blink(int on_cnt, int off_cnt)
{
	GPIOC_PDOR |= (1<<2) | (1<<0);
	GPIOB_PDOR |= (1<<18);
	delay(on_cnt);
	GPIOC_PDOR &= ~( (1<<2) | (1<<0) );
	GPIOB_PDOR &= ~(1<<18);
	delay(off_cnt);
}

/*************************************************************************
* Function Name		:	led_blink_mode_breath_blink
* Description		:	Breath blink
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void led_blink_mode_breath_blink(void)
{
	static int on_time = 0;
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
}

/* End of File*/

