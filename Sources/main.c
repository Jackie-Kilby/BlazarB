/*
File name		: main.c
Developer		: Jack Kilby
First Bread		: 2020-05-16
Description		: The main entry of the project.
*/

/************************ Include Files ***********************************************/
#include "derivative.h" /* include peripheral declarations */
#include "app_uart.h"

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/
static unsigned int hour = 0;
static unsigned int minute = 0;
static unsigned int second = 0;

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
void dtoc(int data) 
{
	uart1_putchar(data/10 + '0');
	uart1_putchar(data%10 + '0');
}
void SysTick_Handler(void)
{
	unsigned int i;
	(void)i;			//Solve the warning "set but not used"
	static unsigned char half_sec = 0;
	
	half_sec++;
	if (half_sec % 2) {
		second++;
		if (second == 60) {
			second = 0;
			minute ++;
			if (minute == 60) {
				minute = 0;
				hour ++;
				if (hour == 24) {
					hour = 0;
				}
			}
		}
	}
	
	uart1_putchar('\r');
	//printf hour
	dtoc(hour);
	uart1_putchar(':');
	//printf minute
	dtoc(minute);
	uart1_putchar(':');
	//printf second
	dtoc(second);
	
	//Clear Interrupt flag
	i = SYST_CSR;		
}

/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	uart1_init();
	
	asm("CPSIE i");
		
	SYST_RVR = 0xA037A0;		//21MHz/2
	SYST_CVR = 0x00;
	SYST_CSR |= (1<<0) | (1<<1) | (1<<2);
	
	for (;;) {

	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

