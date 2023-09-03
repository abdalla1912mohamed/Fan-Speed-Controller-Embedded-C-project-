#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "motor.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "std_types.h"
#include "adc.h"

const ADC_ConfigType * Config_Ptr ;
/*
 * main.c
 *
 *  Created on: Jul 15, 2023
 *      Author: Abdalla
 */
	int main(void)
	{
		uint8 temp;
		ADC_ConfigType ADC_parameter  ;
		ADC_parameter.prescaler = prescaler_value ;
		ADC_parameter.ref_volt = ref_volt_value ;   //structure holding the value
		Config_Ptr = &ADC_parameter ;
		DcMotor_State initial = STOP ;
		LCD_init(); /* initialize LCD driver */
		ADC_init(Config_Ptr); /* initialize ADC driver */
		DcMotor_Init() ;
		/* Display this string "Temp =   C" only once on LCD at the first row */
		LCD_displayString("Temp =    C");
        DcMotor_Rotate(initial, 0) ;
	    while(1)
	    {

	    	temp = LM35_getTemperature();
			/* Display the temperature value every time at same position */
			LCD_moveCursor(0,7);
			if(temp < 30)
			{
				DcMotor_Rotate(STOP, 0) ;
				LCD_intgerToString(temp);
				LCD_moveCursor(1,2);
				LCD_displayString("fan is off ") ;

			}else if((temp>=30) && (temp<60)){
				DcMotor_Rotate(CW, 64) ;
				LCD_intgerToString(temp);
								LCD_moveCursor(1,2);
								LCD_displayString("fan is ON 25% ") ;

			}else if ( temp>=60 && temp<90){
				DcMotor_Rotate(CW, 128) ;
								LCD_intgerToString(temp);
												LCD_moveCursor(1,2);
												LCD_displayString("fan is ON 50% ") ;



			}else if ( temp>=90 && temp < 120){
				DcMotor_Rotate(CW, 192) ;
								LCD_intgerToString(temp);
												LCD_moveCursor(1,2);
												LCD_displayString("fan is ON 75% ") ;
			}
			else
			{
			DcMotor_Rotate(CW, 255) ;
			LCD_intgerToString(temp);
			LCD_moveCursor(1,2);
			LCD_displayString("fan is ON 100% ") ;
			}
	    }
	}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
/*
 ================================================================================================
 Name        : temp_sensor_example.c
 Author      : Mohamed Tarek
 Description : Test the ADC driver designed with polling technique using LM35 Temperature Sensor
 Date        : 5/9/2015
 ================================================================================================
 */

