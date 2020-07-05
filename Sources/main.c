/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "app_uart.h"

#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>

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
	int i = 0;
	uart1_init();
	
	for (i=0 ; i<128 ; i++) {
		uart1_putchar(i);
		if (i%16 == 0) {
			uart1_putchar('\n');
			uart1_putchar('\r');
		}
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

