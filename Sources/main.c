/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "app_led.h"
#include "app_button.h"
#include "app_os.h"

#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
void UART0_PutChar(char c)
{
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	UART0_D = c;
}

unsigned char UART0_GetChar(void)
{
	while(!(UART0_S1 & UART_S1_RDRF_MASK));
	return UART0_D;
}

void UART0_Init(void)
{
	//Enable UART0 clock
	SIM_SOPT2 |= (1<<26);			//MCGFLLCLK clock, or MCGPLLCLK/2
	SIM_SOPT2 &= ~(1<<16);			//MCGFLLCLK clock
	SIM_SCGC4 |= (1<<10);			//Enable UART0 clock
	SIM_SCGC5 |= (1<<9);			//Enable PortA clock
	
	//Select UART0 IO
	PORTA_PCR2 |= (1<<9);			//Select PortA-2 as UART0 Tx
	PORTA_PCR1 |= (1<<9);			//Select PortA-1 as UART0 Rx
	
	//Init UART
	UART0_BDH = 0x00;
	UART0_BDL = 137;				//Set baud rate as 9600
	UART0_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);			//Enable Tx
}
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	UART0_Init();
	
	for (;;) {
		UART0_PutChar('D');
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

