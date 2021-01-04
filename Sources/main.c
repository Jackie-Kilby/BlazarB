/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "derivative.h" /* include peripheral declarations */
#include "app_uart.h"
#include "app_os.h"
#include "app_adc.h"

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	adc_init();
	uart0_init();
	
	for (;;) {
		//Print out the value ADC get
		char_to_hex(adc_read());
		uart0_putstring("\r\n");
		//Delay
		delay(10000);
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

