/*
File name		: app_led.c
Developer		: Jack Kilby
Created on		: May 27, 2020
Description		: LED related code.
*/

/************************ Include Files ***********************************************/
#include "app_os.h"
#include "derivative.h"

/************************ MACRO Definitions *******************************************/
#define BREATH_PERIOD		100

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
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
	for (on_time=0 ; on_time<BREATH_PERIOD ; on_time++) {
		//on
		GPIOC_PDOR |= (1<<5);
		//delay++
		delay(on_time);
		//off
		GPIOC_PDOR &= ~(1<<5);
		//delay--
		delay(BREATH_PERIOD-on_time);
	}
	for (on_time=0 ; on_time<BREATH_PERIOD ; on_time++) {
		//on
		GPIOC_PDOR |= (1<<5);
		//delay++
		delay(BREATH_PERIOD-on_time);
		//off
		GPIOC_PDOR &= ~(1<<5);
		//delay--
		delay(on_time);
	}
}

/************************ Static Functions Definitions *********************************/

/* End of File*/



