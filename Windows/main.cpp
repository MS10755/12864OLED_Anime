#include "HAL.h"
#include <stdio.h>
#include "anime.h"
#include "easing_functions.h"
#include "page.h"

page_manager_t page_manager;
U8G2_SDL2_128x64 u8g2(U8G2_R0);


int get_key(){
 char key = u8g_sdl_get_key();
 if(key == 'a'){
      return 1;
    }else if(key == 's'){
      return 2;
    }else if(key == 'd'){
      return 3;
    }else if(key == 'f'){
      return 4;
    }
    return 0;
}

int main(int argc, char*argv[])
{
  setvbuf(stdout, NULL, _IONBF, 0);
  u8g2.begin();

  PAGE_INIT(PAGE_ID_MAIN);
  PAGE_INIT(PAGE_ID_MENU);
  PAGE_INIT(PAGE_ID_CLOCK);
  PAGE_INIT(PAGE_ID_TOOLBOX);
  page_switch(&page_manager,PAGE_ID_MAIN);

  while(1){
    page_manager_loop(&page_manager);
    int key = get_key();
    if(key > 0 ){
      page_key_event_send(&page_manager,key,0);
    }
    HAL_Delay(1);
  }
  
  return 0;
}

