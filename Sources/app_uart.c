/*
File name		: app_uart.c
Developer		: Jack Kilby
Created on		: Jul 4, 2020
Description		: 
*/

/************************ Include Files ***********************************************/
#include "derivative.h" /* include peripheral declarations */

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/
static inline unsigned char dtoa(unsigned int data);

/************************ Externed Functions Definitions ******************************/
/*************************************************************************
* Function Name		:	uart0_init
* Description		:	Init Uart0 Tx and Rx func. with MCGFLLCLK clock(21MHz) and baud rate is 9600 bps
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void uart0_init(void)
{
	//Enable UART0 clock
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);		//MCGFLLCLK clock, or MCGPLLCLK/2
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;	//MCGFLLCLK clock (21MHz)

	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;		//Enable UART0 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		//Enable PortA clock
	
	//Select UART0 IO
	PORTA_PCR2 |= (1<<9);			//Select PortA-2 as UART0 Tx
	PORTA_PCR1 |= (1<<9);			//Select PortA-1 as UART0 Rx
	
	//Init UART
	UART0_BDH = 0x00;
	UART0_BDL = 0x88;				//Set baud rate as 9600 (MCGFLLCLK clock is 21MHz)
	UART0_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);			//Enable Tx
}

/*************************************************************************
* Function Name		:	uart1_init
* Description		:	Init Uart1 Tx and Rx Func. with Bus clock(10.485MHz) and buad rate is 9600 bps
* Parameters		:	void
* Returns			:	void
*************************************************************************/
void uart1_init(void)
{
	SIM_SCGC4 |= (1<<11);			//Enable UART1 clock
	SIM_SCGC5 |= (1<<13);			//Enable PortE clock
	
	//Select UART1 IO
	PORTE_PCR0 |= (3<<8);			//Select PortE-0 as UART1 Tx
	PORTE_PCR1 |= (3<<8);			//Select PortE-1 as UART1 Rx
	
	UART1_BDH = 0x00;
	UART1_BDL = 0x44;				//Set baud rate as 9600 (Bus Clock = 10.485MHz)
	UART1_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);			//Enable Tx
}

/*************************************************************************
* Function Name		:	uart0_putchar
* Description		:	Send a char to UART0 data register when Transmit data register empty (Block method) 
* Parameters		:	unsigned char data, the char going to be sent
* Returns			:	void
*************************************************************************/
void uart0_putchar(unsigned char data)
{
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	UART0_D = data;
}

/*************************************************************************
* Function Name		:	uart0_getchar
* Description		:	Get a char from UART0 data register when Receive data register full (Block method) 
* Parameters		:	void
* Returns			:	unsigned char, the data got
*************************************************************************/
unsigned char uart0_getchar(void)
{
	while(!(UART0_S1 & UART_S1_RDRF_MASK));
	return UART0_D;
}

/*************************************************************************
* Function Name		:	uart1_putchar
* Description		:	Send a char to UART1 data register when Transmit data register empty (Block method) 
* Parameters		:	unsigned char data, the char going to be sent
* Returns			:	void
*************************************************************************/
void uart1_putchar(unsigned char data)
{
	while(!(UART1_S1 & UART_S1_TDRE_MASK));
	UART1_D = data;
}

/*************************************************************************
* Function Name		:	uart1_getchar
* Description		:	Get a char from UART1 data register when Receive data register full (Block method) .
* Parameters		:	void
* Returns			:	unsigned char, the data got
*************************************************************************/
unsigned char uart1_getchar(void)
{
	while(!(UART1_S1 & UART_S1_RDRF_MASK));
	return UART1_D;
}

/*************************************************************************
* Function Name		:	uart1_putstring
* Description		:	Print string out.
* Parameters		:	char *, the string to be printed out.
* Returns			:	void
*************************************************************************/
void uart1_putstring(char * str)
{
	while(*str != 0) {
		uart1_putchar(*str);
		str++;
	}
}

/*************************************************************************
* Function Name		:	char_to_decimal
* Description		:	Change input char to ASCII output in decimal and print it out.
* Parameters		:	unsigned char, the input char
* Returns			:	void
*************************************************************************/
void char_to_decimal(unsigned char data)
{
	uart1_putchar(data/100+'0');
	uart1_putchar(data%100/10+'0');
	uart1_putchar(data%10+'0');
}

/*************************************************************************
* Function Name		:	char_to_hex
* Description		:	Change input char to ASCII output in hex and print it out.
* Parameters		:	unsigned char, the input char
* Returns			:	void
*************************************************************************/
void char_to_hex(unsigned char data)
{
	uart1_putchar(dtoa((data&0xF0)>>4));
	uart1_putchar(dtoa(data&0x0F));
}

/*************************************************************************
* Function Name		:	char_to_ascii_table
* Description		:	Change input char to ASCII output in hex and decimal and print it out as table.
* Parameters		:	unsigned char, the input char
* Returns			:	void
*************************************************************************/
void char_to_ascii_table(unsigned char data)
{
	uart1_putchar(data);
	uart1_putchar('\t');
	
	uart1_putchar('0');
	uart1_putchar('x');
	char_to_hex(data);

	uart1_putchar('\t');
	char_to_decimal(data);
	
	uart1_putchar('\r');
	uart1_putchar('\n');
}

/************************ Static Functions Definitions *********************************/
/*************************************************************************
* Function Name		:	dtoa
* Description		:	Decimal number to ASCII in hex.
* Parameters		:	unsigned int, the input dicimal number
* Returns			:	unsigned char, the hex output in ASCII char
*************************************************************************/
static inline unsigned char dtoa(unsigned int data)
{
	return data<10 ? data+'0' : data+'A'-10;
}

/* End of File*/
