#include "HAL.h"
#include "u8g2lib.h"
#include <stdio.h>
#include "anime.h"
#include "easing_functions.h"

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


int main(int argc, char*argv[])
{
  setvbuf(stdout, NULL, _IONBF, 0);
  u8g2.begin();
  anime_init(&a_move_y,0,50,5000,easing_fun_OutBounce);
  anime_play(&a_move_y);
  while(1){
    ui_loop();

  }
  
  return 0;
}

