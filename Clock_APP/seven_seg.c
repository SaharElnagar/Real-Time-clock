/*
 * seven_seg.c
 *
 *  Created on: Jul 8, 2018
 *      Author: Sahar Elnagar
 */

#include"seven_seg.h"

#define PORT_OFFSET 2
#define DDR_OFFSET  1
#define BITS8_0     0xFF
#define NULL (uint8_t *)0

typedef struct{

    enum_PortBase_t Port;
    enum_SevenSeg_type_t Type;

}strPortTypeInfo_t;

static strPortTypeInfo_t Handler[MAX_OBJECTS];
static uint8_t Seven_seg_patterns[]={0x3F,0x06,0x5B,0x4F,0x66,0xED,0x7D,0x07,0xFF,0x6F};

/*
 * this variable is used as register each bit represents a handler
 * */
static uint8_t handlers_register=0;

enum_Errors_t Init_seven_seg_obj(uint8_t port_base,uint8_t type,uint8_t* handle_num){
    	uint8_t handlers_count=0;
	enum_Errors_t rtn_value = No_ERRORS;
	if(port_base>MINIMUM_PIN_ADDRESS && port_base<MAXIMUM_PIN_ADDRESS && type<Max_Type && handle_num!= NULL)
	  {
		if(handlers_register==0xF)
		 return No_FREE_OBJECTS ;

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
		  * configure port as output
		  * */
		 *((volatile uint8_t*)(port_base+DDR_OFFSET))  |=BITS8_0;    //output
		 if(type==COMMON_ANODE)
		  {
		    *((volatile uint8_t*)(Handler[handlers_count].Port +PORT_OFFSET))|=BITS8_0 ; //clear port by 0xFF if common_anode
		  }
		 else
		  {
			*((volatile uint8_t*)(Handler[handlers_count].Port +PORT_OFFSET))&=~BITS8_0 ; //clear port by 0x00 if common_cathode
		  }
		 /*
		  * initiate and save the object
		  * */
		 Handler[handlers_count].Port=port_base;
		 Handler[handlers_count].Type=type;
		 /*
		  * return object handler number
		  * */
		 *handle_num=handlers_count;

	  }
	else
	  {
		rtn_value= INVALID_ARGUMENT ;
	  }
	return rtn_value ;
}


enum_Errors_t Display(uint8_t Num,uint8_t handle_num){

	enum_Errors_t rtn_value = No_ERRORS;
    if(Num<10 &&handle_num<MAX_OBJECTS)
    {

      if(Handler[handle_num].Port!=0)
      {

      if(Handler[handle_num].Type==COMMON_ANODE)
      {
       *((volatile uint8_t*)(Handler[handle_num].Port+PORT_OFFSET))|=BITS8_0 ; //clear port by 0xFF if common_anode
       *((volatile uint8_t*)(Handler[handle_num].Port+PORT_OFFSET))&=~Seven_seg_patterns[Num] ;
      }
      else
      {
       *((volatile uint8_t*)(Handler[handle_num].Port+PORT_OFFSET))&=~BITS8_0 ; //clear port by 0x00 if common_cathode
       *((volatile uint8_t*)(Handler[handle_num].Port+PORT_OFFSET))|=Seven_seg_patterns[Num] ;
      }
      }
      else
      {
    	  return PORT_UNINITIALIZED;
      }


    }
    else
    {
    	rtn_value=INVALID_ARGUMENT ;
    }

	return rtn_value ;

}



enum_Errors_t Reset(uint8_t handle_num){
	enum_Errors_t rtn_value = No_ERRORS;

    if(handle_num<MAX_OBJECTS)
    {

      if(Handler[handle_num].Port!=0)
      {
    	if(Handler[handle_num].Type==COMMON_ANODE)
    	{
         *((volatile uint8_t*)(Handler[handle_num].Port+PORT_OFFSET))|=BITS8_0 ; //clear port by 0xFF if common_anode
    	}
        else
    	 {
    	 *((volatile uint8_t*)(Handler[handle_num].Port+PORT_OFFSET))&=~BITS8_0 ; //clear port by 0x00 if common_cathode
    	 }

      }
      else
      {
    	  return PORT_UNINITIALIZED;
      }

   }
   else
   {
    	rtn_value=INVALID_ARGUMENT ;
   }

	return rtn_value ;

}


enum_Errors_t DeInit_seven_seg_obj(uint8_t handle_num){
	enum_Errors_t rtn_value = No_ERRORS;
	if(handle_num<MAX_OBJECTS)
	{
	  if(handlers_register==0)
	  {
		return ALL_OBJECTS_FREE;
	  }
	  Handler[handle_num].Port=0;
	  Handler[handle_num].Type=0;
	  /*
	   * Clear the specified handler bit in the handlers_register
	   * */
	  handlers_register&=~(1<<handle_num);

	}
	else
	{
		rtn_value=INVALID_ARGUMENT;
	}
	return rtn_value ;
}
