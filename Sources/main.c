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
#include <stdlib.h>		//For rand func.

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
void uart1_putstring(char * str)
{
	while(*str != 0) {
		uart1_putchar(*str);
		str++;
	}
}


/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	unsigned int answer = 3;
	unsigned char data = 0;
	int gnum = 0;
	int r = 0;
	uart1_init();
	uart1_putstring("Press any key to start.\r\n");
	for (;;) {
		
		while(!(UART1_S1 & UART_S1_RDRF_MASK)) r++;
		answer = r%10;
		uart1_putchar(' ');
		uart1_putchar(answer+'0');
		uart1_putchar('\r');
		uart1_putchar('\n');
		
		while(1) {
			
			uart1_putstring("Guess number:");
			data = uart1_getchar();
			uart1_putchar(data);
			if (answer == (data-'0')) {
				uart1_putstring(" Bingo!\r\n");
				break;
			} else {
				uart1_putstring(" is ");
				if (data-'0' > answer) {
					uart1_putstring("more.\r\n");
				} else {
					uart1_putstring("less.\r\n");
				}
			}
			gnum++;
		} 
		uart1_putstring("You have guessed for ");
		uart1_putchar(gnum+'0');
		uart1_putstring(" times.\r\nTry again, press any key to start.\r\n");
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

