/*
 * Time_mangement_unit.h
 *
 *  Created on: Jul 14, 2018
 *      Author: Sahar Elnagar
 */

#ifndef TIME_MANGEMENT_UNIT_H_
#define TIME_MANGEMENT_UNIT_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common.h"
#define MAX_TIMER_OBJECTS 5

typedef enum
{
 No_ERRORS_=0,
 INVALID_ARGUMENT_,
 No_FREE_OBJECT_,
 ALL_OBJECTS_FREE_,
 TIMER_UNINITIALIZED_ ,

}enum_timer_errors_t ;

/*
 * \brief this function initiates  a timer object and returns
 *  an index represents the object number and SW interrupt to the timer
 *
 *
 * Input  : Timer_Duration
 * Output : Handle_num ,
 * return : Timer_errors
 * */
enum_timer_errors_t Init(uint16_t timer_duration,uint8_t* Handle_num,void(*Timer_Handle)(void));


/*
 * \brief this function Enables the desired timer
 *
 * Input  : Number of desired timer to enable
 * Output : None
 * return : Timer_errors
 * */
enum_timer_errors_t Timer_Enable(uint8_t handle_num);



/*
 * \brief this function must be called continuously if any timer is enabled
 *
 * Input  : None
 * Output : None
 * return : Timer_errors
 * */
void Timers_dispatcher(void);



/*
 * \brief this function Disables the desired timer
 *
 * Input  : Number of desired timer to disables
 * Output : None
 * return : Timer_errors
 * */
enum_timer_errors_t Timer_Disable(uint8_t handle_num);



/*
 * \brief this function clears a timer object
 *
 * Input  : handle_num of a specific module
 * Output : None
 * return : Errors type
 * */
enum_timer_errors_t DeInit(uint8_t handle_num);

#endif /* TIME_MANGEMENT_UNIT_H_ */
