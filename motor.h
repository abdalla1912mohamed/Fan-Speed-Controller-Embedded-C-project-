/*
 * motor.h
 *
 *  Created on: Jul 13, 2023
 *      Author: Abdalla
 */

#ifndef MOTOR_H_
#define MOTOR_H_



#endif /* MOTOR_H_ */



typedef enum {
	STOP, CW , ACW
}DcMotor_State ;





void DcMotor_Init(void) ;
void DcMotor_Rotate(DcMotor_State state,uint8 speed) ;
