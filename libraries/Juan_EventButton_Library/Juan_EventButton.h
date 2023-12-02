#ifndef __JUAN_EVENTBUTTON_H__
#define __JUAN_EVENTBUTTON_H__
#define	__STDC_LIMIT_MACROS
#ifdef ARDUINO
#include "Arduino.h"
#define BUTTON_GET_MS()		millis()
#else
#include "frame_stm32f10x.h"
#define BUTTON_GET_MS()		millis()
#endif

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef enum{
    BUTTON_STATUS_RELEASE,
    BUTTON_STATUS_PRESS,
}ButtonStatus_t;


typedef enum{
	BUTTON_EVENT_PRESSED,
	BUTTON_EVENT_PRESSING,
	BUTTON_EVENT_LONG_PRESSED,
	BUTTON_EVENT_LONG_PRESSED_REPEAT,
	BUTTON_EVENT_RELEASEED,
	BUTTON_EVENT_CLICKED,
	BUTTON_EVENT_DOUBLE_CLICKED,
}ButtonEvent_t;

typedef void(*event_handler_t)(void * btn,ButtonEvent_t event);


typedef struct{
		//settings
			uint8_t _noPressStatus;
			uint16_t _doubleClickTime;
			uint16_t _longPressTime;
			uint16_t _longPressRepeatTime;
			event_handler_t _event_handler;
	
			//data
			uint8_t _lastStatus;
			bool _timer_longPressed_en;
			uint32_t _pressed_start_time;
			uint8_t _longPressedRepeatCount;

			bool _timer_double_clicked_en;
			uint32_t _clicked_start_time;

}Juan_EventButton_t;


Juan_EventButton_t * Juan_EventButtonCreate(
			uint8_t noPressStatus,
			uint16_t doubleClickTime,
			uint16_t longPressTime,
			uint16_t longPressRepeatTime
);


void Juan_EventButtonDelete(Juan_EventButton_t * btn);
void Juan_AddEventHandler(Juan_EventButton_t * btn,event_handler_t event_handler);
void Juan_EventMonitor(Juan_EventButton_t * btn,uint8_t now_status);

#ifdef __cplusplus
}
#endif
#endif




