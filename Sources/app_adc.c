/*
File name		: app_adc.c
Developer		: Jack Kilby
Created on		: Jan 5, 2021
Description		: 
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
* Function Name		:	adc_init
* Description		:	Initilize IO PTD1 as Continuous ADC0_SE5b
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void adc_init(void)
{
	//Clock Config
//	MCG_C1 &= ~((1<<6)|(1<<7));			//Select PLL/FLL output as clock source of MCGOUTCLK(default)
//	SIM_SCGC5 |= (1<<12);		//Enable GPIO PortD Clock Gate(not needed)
	SIM_SCGC6 |= (1<<27);		//Enable ADC0 Clock Gate	//If not config this, will cause Default_Handler();
	
	//IO Config as ADC0 Func.
//	PORTD_PCR1 &= ~(0x700);		//Config PTD1 as ADC0_SE5b(default)
	
	//ADC Func. config
//	ADC0_CFG1 &= ~(0xC);	//Select Bus Clock as Input clock(default)
//	ADC0_CFG1 &= ~(0x3);	//Choose 8-bit ADC(default)
	ADC0_CFG2 |= (1<<4);	//Select Channel ADxxb
	ADC0_SC3 |= (1<<3); 	//Continuous Conversion mode
	ADC0_SC1A &=~((1<<1)|(1<<3)|(1<<4));	//Select Input channel: AD5(0b00101)
}

/*************************************************************************
* Function Name		:	adc_read
* Description		:	Initilize IO PTD1 as Continuous ADC0_SE5b
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int adc_read(void)
{
	int adc_read = 0;
	adc_read = ADC0_RA;
	return adc_read;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/
