#include "HAL.h"
#include <stdio.h>
#include "anime.h"
#include "easing_functions.h"
#include "page.h"

page_manager_t page_manager;
U8G2_SDL2_128x64 u8g2(U8G2_R0);

int main(int argc, char*argv[])
{
  setvbuf(stdout, NULL, _IONBF, 0);
  u8g2.begin();

  PAGE_INIT(PAGE_ID_MAIN);
  PAGE_INIT(PAGE_ID_MENU);
  page_switch(&page_manager,PAGE_ID_MENU);

  while(1){
    page_manager_loop(&page_manager);
    char key = u8g_sdl_get_key();
    if(key == 'a'){
      page_key_event_send(&page_manager,1,0);
    }else if(key == 's'){
      page_key_event_send(&page_manager,2,0);
    }else if(key == 'd'){
      page_key_event_send(&page_manager,3,0);
    }else if(key == 'f'){
      page_key_event_send(&page_manager,4,0);
    }
    HAL_Delay(10);
  }
  
  return 0;
}

