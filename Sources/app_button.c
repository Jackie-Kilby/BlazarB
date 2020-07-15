/*
File name		: app_button.c
Developer		: Jack Kilby
Created on		: May 27, 2020
Description		: Button related code.
*/

/************************ Include Files ***********************************************/
#include "derivative.h"

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
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
* Function Name		:	button_read
* Description		:	read button state and return
* Parameters		:	void
* Returns			:	int, bit0-up, bit1-down, bit2-right, bit3-left, bit4-A, bit5-B, bit6-C, bit7-D
*************************************************************************/
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

#if EXAMPLE_CODE
/*************************************************************************
* Function Name		:	gpio_interrupt_enable
* Description		:	An example code of gpio(PA5) interrupt config
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void gpio_interrupt_enable(void)
{
	NVIC_ISER |= (1<<30);		//Enable PortA GPIO Interrupt
	PORTA_PCR5 |= (10<<16);		//Interrupt on falling-edge
	PORTA_PCR5 |= (1<<24);		//Clear Interrupt
}
#endif

/************************ Static Functions Definitions *********************************/

/* End of File*/
