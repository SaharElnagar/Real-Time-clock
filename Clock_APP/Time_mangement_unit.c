/*
 * Time_mangement_unit.c
 *
 *  Created on: Jul 14, 2018
 *  Author: Sahar Elnagar
 */

#include "Time_mangement_unit.h"
#define MIN_TIME_DURATION 5     //5 ms
#define NULL ((void *)0)
#define ZERO 0
#define ONE  1
static uint8_t max_inited_obj ;

static inline void set_handlers_register(uint8_t count){
 while(count){
    max_inited_obj|=1<<(--count);}
}
static uint8_t handlers_register=0;

typedef struct{
 void(*Timer_handle)(void);
 uint16_t time_duaration;
 uint16_t temp;
 bool_t blocked;

}strTimersHandlers_t;

strTimersHandlers_t Timer_objects[MAX_TIMER_OBJECTS];
 static uint8_t timer0_flag=0;

 
/*
 *
 * void Timer_handler(void){  //every 1ms
 *
 * counter++;
 *
 * }
 * */
 ISR(TIMER0_OVF_vect) {
	
  //every 5ms
     TCNT0=190;
	
	 timer0_flag=1;
	for(int i=0;i<MAX_TIMER_OBJECTS;i++){
		if(Timer_objects[i].temp>0)
		Timer_objects[i].temp--;
	}
	
	 
	
 }
  static void timer0_hardware_init(void){
	  DDRD |= 0x08;
	  PORTB &=~ 0x08;
	  TCCR0|=0x83;
	  TCNT0=190;
	  TIMSK|=0x01;
	  sei();
	   
  }
  static void timer0_hardware_deinit(void){}

enum_timer_errors_t Init(uint16_t timer_duration,uint8_t* Handle_num,void(*Timer_Handle)(void))
{
	uint8_t handlers_count=0;
	uint8_t rtn_val=No_ERRORS_ ;
	if(timer_duration>=MIN_TIME_DURATION&&Handle_num!=NULL&&Timer_Handle!=NULL)
	{
     if(handlers_register==ZERO)
     {
    	 timer0_hardware_init();
    	 set_handlers_register(MAX_TIMER_OBJECTS);
     }
      if(handlers_register==max_inited_obj)
     { return No_FREE_OBJECT_ ;

     }
     else
     {
	 /*
	  * search which bit  in the handlers_register is not initiated =0
	  * */
		 while(( handlers_register&(1<<handlers_count)))
			 {
			 	 handlers_count++;
			 }
	 /*
	  * Set the uninitiated bit in the handlers_register
	  * */
		 handlers_register|=(1<<handlers_count);

		 /*
		  * save data in an object
		  * */
		 Timer_objects[handlers_count].Timer_handle = Timer_Handle;
		 Timer_objects[handlers_count].time_duaration = timer_duration;
		 Timer_objects[handlers_count].temp= timer_duration;
		 Timer_objects[handlers_count].blocked = TRUE ;
	 /*
	  * return handler index
	  * */
		 *Handle_num = handlers_count;

     }
	 }
	else
	{
		rtn_val=INVALID_ARGUMENT_ ;
	}
	return rtn_val;
}

enum_timer_errors_t Timer_Enable(uint8_t handle_num){

	uint8_t rtn_val=No_ERRORS_ ;
    if(handle_num<MAX_TIMER_OBJECTS)
    {
     if(Timer_objects[handle_num].time_duaration!=ZERO)
     {
    	 Timer_objects[handle_num].blocked=FALSE ;  //Not blocked
     }
     else
     {
    	 return TIMER_UNINITIALIZED_;
     }
    }
    else
    {
		rtn_val=INVALID_ARGUMENT_ ;

    }
	return rtn_val;

}
enum_timer_errors_t Timer_Disable(uint8_t handle_num){

	uint8_t rtn_val=No_ERRORS_ ;
    if(handle_num<MAX_TIMER_OBJECTS)
    {
     if(Timer_objects[handle_num].time_duaration!=ZERO)
     {
    	 Timer_objects[handle_num].blocked=TRUE ;  // blocked
     }
     else
     {
    	 return TIMER_UNINITIALIZED_;
     }
    }
    else
    {
		rtn_val=INVALID_ARGUMENT_ ;

    }
	return rtn_val;

}


 void Timers_dispatcher(void){

//  static uint16_t temp_timer_duration[MAX_TIMER_OBJECTS]={0} ;

	for(int i=0;i<MAX_TIMER_OBJECTS;i++)
	{

	if(Timer_objects[i].blocked==FALSE&&timer0_flag==1)
	{
	

		if(Timer_objects[i].temp==0)
	
	
		{
			Timer_objects[i].temp=Timer_objects[i].time_duaration;
			(*Timer_objects[i].Timer_handle)();

		}
	}
	

	}
	
	timer0_flag=0;

}

 enum_timer_errors_t DeInit(uint8_t handle_num){
		uint8_t rtn_val=No_ERRORS_ ;
		if(handle_num<MAX_TIMER_OBJECTS)
		{
		  if(handlers_register==0)
		  {
			timer0_hardware_deinit();
			return ALL_OBJECTS_FREE_;
		  }
		   Timer_objects[handle_num].blocked=TRUE;
		   Timer_objects[handle_num].time_duaration=0;

		  /*
		   * Clear the specified handler bit in the handlers_register
		   * */
		  handlers_register&=~(1<<handle_num);

		}
		else
		{
			rtn_val=INVALID_ARGUMENT_;
		}

		return rtn_val;

 }




