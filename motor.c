/*
 * motor.c
 *
 *  Created on: Jul 13, 2023
 *      Author: Abdalla
 */

#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "motor.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "std_types.h"
#include "adc.h"


void DcMotor_Init(void) {
	GPIO_setupPinDirection(PORTB,PIN0_ID,PIN_OUTPUT) ;
	GPIO_setupPinDirection(PORTB,PIN1_ID,PIN_OUTPUT) ;
	  GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW) ;
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW) ; //stop

	}
void Timer0_PWM_Init(unsigned char duty_cycle , int pin_num )
{
	TCNT0 = 0; // Set Timer Initial Value to 0



	OCR0  = duty_cycle ; //Set Compare value

	DDRB  = DDRB | (1<<pin_num); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}


void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch(state) {

	case STOP :    GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW) ;
	               GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW) ;
             break ;

	case CW   :  GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH) ;
	       GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW) ;
                 break ;

	case ACW  :       GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH) ;
                      GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW) ;
                    break ;
	default :   GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW) ;
	 GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW) ;
    break ;
	}

	switch( speed ){

	case 25 : speed = 64 ;
	break ;
	case 50 : speed = 128 ;
	break ;
	case 75 : speed = 192 ;
			break ;
	case 100 : speed = 255 ;
	break ;
	default : speed = (uint8)((uint32) (speed *256) /(100)) ;
	break;
	}
//     speed  =  speed *256 ;
//     speed = speed/100 ;

    Timer0_PWM_Init(speed ,PB3) ;
	}





































