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
	unsigned char data;
	uart1_init();
	
	uart1_putchar('\t');
	uart1_putchar('A');
	uart1_putchar('S');
	uart1_putchar('C');
	uart1_putchar('I');
	uart1_putchar('I');
	uart1_putchar(' ');
	uart1_putchar('S');
	uart1_putchar('e');
	uart1_putchar('a');
	uart1_putchar('r');
	uart1_putchar('c');
	uart1_putchar('h');

	uart1_putchar('\r');
	uart1_putchar('\n');
	
	for (;;) {
		data = uart1_getchar();
		char_to_ascii_table(data);
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

