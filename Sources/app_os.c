/*
File name		: app_os.c
Developer		: Jack Kilby
Created on		: May 27, 2020
Description		: 
*/

/************************ Include Files ***********************************************/

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Definitions ******************************/
/*************************************************************************
* Function Name		:	delay
* Description		:	Used to delay a period of time, occupying CPU.
* Parameters		:	int	delay_cnt, the cnt of the period.
* Returns			:	void
*************************************************************************/
void delay(int delay_cnt) 
{
	unsigned short i, j;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < delay_cnt; j++) {
			asm("nop");
		}
	}
}

/*************************************************************************
* Function Name		:	global_interrupt_enable
* Description		:	Enable global interrupt.
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void global_interrupt_enable(void)
{
	asm("CPSIE i");
}

/*************************************************************************
* Function Name		:	global_interrupt_disable
* Description		:	Disable global interrupt.
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void global_interrupt_disable(void)
{
	asm("CPSID i");
}

/************************ Static Functions Definitions *********************************/

/* End of File*/
