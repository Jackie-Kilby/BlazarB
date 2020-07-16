/*
File name		: app_pwm.c
Developer		: Jack Kilby
Created on		: Jul 16, 2020
Description		: Pwm application code
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
* Function Name		:	pwm_init
* Description		:	An example of PWM init, using PTC8 PWM0-CH4
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void pwm_init(void)
{	
	SIM_SOPT2 |= (1<<24);				//Select TMP Src
	SIM_SOPT2 &= ~(1<<16);				//Select Clock as MCGFLLCLK(21MHz)
	SIM_SCGC5 |= (1<<11);				//Enable PortC
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;	//Enable PTM0
	
	PORTC_PCR8 = 0x300;					//Config PTC8 as PWM
	
	TPM0_SC |= 0x0008 | 0x0007;			//Prescale setting: devided by 128, TPM counter increments on every TPM counter clock
	TPM0_CNT = 0;						//Init TPM counter
	TPM0_MOD = 51;						//Set TPM frequency 3.2K = 21M/128/51
	TPM0_C4SC |= 0x28;					//Set Edge-aligned PWM, setting output on reload
	TPM0_C4V = 20;						//Set duty cycle = 200/256
}

/************************ Static Functions Definitions *********************************/

/* End of File*/
