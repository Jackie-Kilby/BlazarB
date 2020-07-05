/*
File name		: app_uart.h
Developer		: Jack Kilby
Created on		: Jul 4, 2020
Description		: Uart Func. Implement
*/
#ifndef APP_UART_H_
#define APP_UART_H_
/************************ Include Files ***********************************************/

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Prototypes ******************************/
void uart0_init(void);
void uart1_init(void);
void uart0_putchar(unsigned char data);
void uart1_putchar(unsigned char data);
unsigned char uart0_getchar(void);
unsigned char uart1_getchar(void);

void char_to_decimal(unsigned char data);
void char_to_hex(unsigned char data);
void char_to_ascii_table(unsigned char data);
/************************ Static Functions Definitions *********************************/

#endif /* APP_UART_H_ */
/* End of File*/
