#include "HAL.h"
#include "u8g2lib.h"
#include <stdio.h>
#include "anime.h"
#include "easing_functions.h"
#include "page_manager.h"

static page_manager_t page_manager;

static anime_parms a_move_y;



class U8G2_SDL2_128x64 : public U8G2 {
  public: U8G2_SDL2_128x64(const u8g2_cb_t *rotation) : U8G2() {
    u8g2_SetupBuffer_SDL_128x64(&u8g2,rotation);
    u8x8_InitDisplay((u8x8_t*)&u8g2);
  }
};


U8G2_SDL2_128x64 u8g2(U8G2_R0);

void ui_loop(){
  anime_process(&a_move_y);
  if(a_move_y.status == ANIME_STATUS_END){
  anime_init(&a_move_y,0,50,5000,easing_fun_OutBounce);
    anime_play(&a_move_y);
  }
  u8g2.setFont(u8g2_font_7x13_tf);
  u8g2.clearBuffer();
  u8g2.drawStr(0,a_move_y.val+u8g2.getMaxCharHeight(),"Hello world");
  u8g2.sendBuffer();
  u8g_sdl_get_key();
}


static int open(){



}

static int close(){



}

static int loop(){



}

static void key_handler(int key,int event){
  printf("key:%d pressed!\r\n",key);
}

int main(int argc, char*argv[])
{
  setvbuf(stdout, NULL, _IONBF, 0);
  u8g2.begin();
  printf("size of anime_parms:%d\n",sizeof(anime_parms));
  anime_init(&a_move_y,0,50,5000,easing_fun_OutBounce);
  anime_play(&a_move_y);
  page_manager_init(&page_manager);
  page_register(&page_manager,1,open,loop,close,key_handler);
  page_switch(&page_manager,1);
  while(1){
    ui_loop();
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
  }
  
  return 0;
}

