/*
File name		: app_led.h
Developer		: Jack Kilby
Created on		: May 27, 2020
Description		: Header file of app_led.c 
*/
#ifndef APP_LED_H_
#define APP_LED_H_
/************************ Include Files ***********************************************/

/************************ MACRO Definitions *******************************************/

/************************ Type Definitions ********************************************/

/************************ Externed Varibles *******************************************/

/************************ Static Varibles *********************************************/

/************************ Static Functions Prototypes *********************************/

/************************ Externed Functions Prototypes ******************************/
void led_init(void);
void led_blink_mode_normal_blink(int on_cnt, int off_cnt);
void led_blink_mode_breath_blink(void);

/************************ Static Functions Definitions *********************************/

#endif /* APP_LED_H_ */

/* End of File*/
