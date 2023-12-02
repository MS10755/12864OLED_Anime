#include "Juan_EventButton.h"

Juan_EventButton eventButton_key1;
Juan_EventButton eventButton_key2;

void key_event_handler(void * btn,ButtonEvent_t event){
  if(event==BUTTON_EVENT_CLICKED){
    if(btn == &eventButton_key1){
      //do some thing when key1 clicked
    }
    if(btn == &eventButton_key2){
      //do some thing when key2 clicked
    }
   }
  if(event == BUTTON_EVENT_LONG_PRESSED && btn ==&eventButton_key1){
    //do some thing when key1 long pressed
  }
}

void setup(){
  eventButton_key1.addEventHandler(key_event_handler);
  eventButton_key2.addEventHandler(key_event_handler);
}


void loop(){
  eventButton_key1.monitor(!digitalRead(PB1));
  eventButton_key2.monitor(!digitalRead(PB2));
}
