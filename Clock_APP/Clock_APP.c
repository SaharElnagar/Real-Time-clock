/*
 * Seven_.c
 *
 * Created: 7/8/2018 08:41:58 م
 *  Author: Sahar Elnagar
 */ 




#include <stdio.h>
#include <stdlib.h>
#include "seven_seg.h"
#include "Time_mangement_unit.h"
uint8_t counter=1;
void Every_second(void){
	
	Display(counter%10,0);
	counter++;
	if(counter==61)counter=1;
	
}
void Every_10_seconds(void){

	Display((counter/10)%6,1);
	
}
void Every_minute(void){
	
	Display(counter/60,2);

}

int main(void) {
uint8_t handle;	 
Init_seven_seg_obj(BASE_D,COMMON_CATHODE,&handle);
Init_seven_seg_obj(BASE_C,COMMON_CATHODE,&handle);
Init_seven_seg_obj(BASE_A,COMMON_CATHODE,&handle);
Init(190,&handle,Every_second);
Timer_Enable(handle);
Init(1900,&handle,Every_10_seconds);
Timer_Enable(handle);	
Init(11380,&handle,Every_minute);
Timer_Enable(handle);
Display(0,0);
Display(0,1);
Display(0,2);
	while(1)
	{
	Timers_dispatcher();
	}
	
	return 0;
}







