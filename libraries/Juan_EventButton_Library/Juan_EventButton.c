/*
* File Name          : Juan_EventButton.cpp
* Author             : Juan
* Version            : v1.0
* email       			 : 1075502955@qq.com


Copyright © 2021 Juan.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "Juan_EventButton.h"
#include <stdlib.h>

/**
  * @brief	:	create an eventbutton
  * @param	: 
  * @param	: 
  * @retval	:	
  */
Juan_EventButton_t * Juan_EventButtonCreate(
			uint8_t noPressStatus,
			uint16_t doubleClickTime,
			uint16_t longPressTime,
			uint16_t longPressRepeatTime
){
		Juan_EventButton_t* btn = (Juan_EventButton_t*)malloc(sizeof(Juan_EventButton_t));
		if(btn==NULL) return NULL;
		btn->_noPressStatus = !!noPressStatus;
		btn->_doubleClickTime = doubleClickTime;
		btn->_longPressTime = longPressTime;
		btn->_longPressRepeatTime = longPressRepeatTime;
		btn->_event_handler = NULL;
		btn->_lastStatus = btn->_noPressStatus;
		btn->_timer_longPressed_en = false;
		btn->_timer_double_clicked_en = false;
		return btn;
}
void Juan_EventButtonInitStatic(
			Juan_EventButton_t * btn,
			uint8_t noPressStatus,
			uint16_t doubleClickTime,
			uint16_t longPressTime,
			uint16_t longPressRepeatTime
){
		if(btn==NULL) return;
		btn->_noPressStatus = !!noPressStatus;
		btn->_doubleClickTime = doubleClickTime;
		btn->_longPressTime = longPressTime;
		btn->_longPressRepeatTime = longPressRepeatTime;
		btn->_event_handler = NULL;
		btn->_lastStatus = btn->_noPressStatus;
		btn->_timer_longPressed_en = false;
		btn->_timer_double_clicked_en = false;
}

/**
  * @brief	:	delete an eventbutton
  * @param	: 
  * @param	: 
  * @retval	:	
  */
void Juan_EventButtonDelete(Juan_EventButton_t * btn){
	free(btn);
}

/**
  * @brief	:	and a eventhandler for species eventbutton
  * @param	: 
  * @param	: 
  * @retval	:	
  */
void Juan_AddEventHandler(Juan_EventButton_t * btn,event_handler_t event_handler){
	btn->_event_handler = event_handler;
}


static uint32_t time_elaps(uint32_t prev_time)
{
    uint32_t act_time = BUTTON_GET_MS();
    if(act_time >= prev_time) {
        prev_time = act_time - prev_time;
    } else {
        prev_time = UINT32_MAX - prev_time + 1;
        prev_time += act_time;
    }
    return prev_time;
}
void Juan_EventMonitor(Juan_EventButton_t * btn,uint8_t now_status){
 //check pressed
	 if(now_status != btn->_noPressStatus && btn->_lastStatus != now_status){
		 btn->_event_handler(btn,BUTTON_EVENT_PRESSED);
	 }
	 
	 //check pressing
	 if(now_status !=btn->_noPressStatus && btn->_lastStatus == now_status){
		 btn->_event_handler(btn,BUTTON_EVENT_PRESSING);
		 			//calculate pressing time
		 if(btn->_timer_longPressed_en == false){
				btn->_timer_longPressed_en=true; 
			 btn->_longPressedRepeatCount = 0;
			 btn->_pressed_start_time = BUTTON_GET_MS(); 
		 }
	 }
	 
	 //check longpressed and longpressed repeat
	 if(btn->_timer_longPressed_en == true && time_elaps(btn->_pressed_start_time) >= btn->_longPressTime){
		 if(btn->_longPressedRepeatCount ==0){
			btn->_event_handler(btn,BUTTON_EVENT_LONG_PRESSED);
		 }else{
			btn->_event_handler(btn,BUTTON_EVENT_LONG_PRESSED_REPEAT);
		 }
			
		 btn->_pressed_start_time = BUTTON_GET_MS();
		 btn->_longPressedRepeatCount += btn->_longPressedRepeatCount< UINT8_MAX ? 1:0;
	 }
	 
	  //chec released
	 if(now_status ==btn->_noPressStatus && btn->_lastStatus != now_status){
		 btn->_event_handler(btn,BUTTON_EVENT_RELEASEED);
		 
		 //check clicked
		 if(time_elaps(btn->_pressed_start_time) < btn->_longPressTime && btn->_longPressedRepeatCount==0){
			btn->_event_handler(btn,BUTTON_EVENT_CLICKED);
			 if(btn->_timer_double_clicked_en == false){
					btn->_timer_double_clicked_en =true;
					btn->_clicked_start_time = BUTTON_GET_MS();
			 }else{
				 //check double clicked
				 if(time_elaps(btn->_clicked_start_time)<=btn->_doubleClickTime){
					 btn->_event_handler(btn,BUTTON_EVENT_DOUBLE_CLICKED);
					 btn->_timer_double_clicked_en = false;
				 }
			 }
		 }
		 btn->_timer_longPressed_en = false;
		 btn->_longPressedRepeatCount = 0;
	 }
	 
	 if(btn->_timer_double_clicked_en == true && time_elaps(btn->_clicked_start_time)>btn->_doubleClickTime){
		 btn->_timer_double_clicked_en = false;
	 }
	 
	btn->_lastStatus = now_status;
}
 

