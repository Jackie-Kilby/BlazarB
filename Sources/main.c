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
/*************************************************************************
* Function Name		:	main
* Description		:	The User Program Entry
* Parameters		:	void
* Returns			:	int
*************************************************************************/
int main(void) 
{
	int button_st = 0;
	
	led_init();
	button_init();
	
	for (;;) {
		button_st = button_read();
		if ( button_st & (1<<3))
			led_blink_mode_breath_blink();
	}

	return 0;
}

/************************ Static Functions Definitions *********************************/

/* End of File*/

