/*
 * seven_seg.h
 *
 *  Created on: Jul 8, 2018
 *      Author: Sahar Elnagar
 */

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_
//#include "common.h"
#include "stdint.h"  //For Atmel_Studio
#define MAX_OBJECTS  4
/*
 * Seven segment pin connection
 * user must be aware of it
 * A-> pin0
 * B-> pin1
 * C-> pin2
 * D-> pin3
 * E-> pin4
 * F-> pin5
 * G-> pin6
 * DP->pin7
 * */


typedef enum{
	MINIMUM_PIN_ADDRESS=0x2F,
	BASE_D=0x30,
	BASE_C=0x33,
	BASE_B=0x36,
	BASE_A=0x39,
	MAXIMUM_PIN_ADDRESS=0x3A

}enum_PortBase_t ;

typedef enum{
	COMMON_CATHODE=1,
	COMMON_ANODE=2,
	Max_Type=3
} enum_SevenSeg_type_t ;



typedef enum{
 No_ERRORS=0,
 INVALID_ARGUMENT,
 No_FREE_OBJECTS,
 ALL_OBJECTS_FREE,
 PORT_UNINITIALIZED,

}enum_Errors_t ;


/*
 * \brief this function initiates  a seven-segment objects and returns
 *  an index represents the object number
 *
 * Input  : Port_Base , SevenSegmentt_Type
 * Output : handle_num
 * return : Errors type
 * */
enum_Errors_t Init_seven_seg_obj(uint8_t port_base,uint8_t type,uint8_t* handle_num);


/*
 * \brief this function Displays the desired number on seven segment object
 *
 * Input  : Desired number to display ,handle_num of a specific module
 * Output : None
 * return : Errors type
 * */
enum_Errors_t Display(uint8_t Num,uint8_t handle_num);


/*
 * \brief this function Displays nothing on the 7_seg
 *
 * Input  : handle_num of a specific module
 * Output : None
 * return : Errors type
 * */
enum_Errors_t Reset(uint8_t handle_num);


/*
 * \brief this function clears a module object
 *
 * Input  : handle_num of a specific module
 * Output : None
 * return : Errors type
 * */
enum_Errors_t DeInit_seven_seg_obj(uint8_t handle_num);

#endif /* SEVEN_SEG_H_ */
