#ifndef __PAGE_H__
#define __PAGE_H__
#include "page_manager.h"
#include "u8g2lib.h"
enum  {
    PAGE_ID_NONE = 0,
    PAGE_ID_MAIN,
    PAGE_ID_MENU,
    PAGE_ID_CLOCK,
    PAGE_ID_TOOLBOX,
    PAGE_ID_GAME,
};

#ifdef PLATFORM_WIN32
class U8G2_SDL2_128x64 : public U8G2 {
  public: U8G2_SDL2_128x64(const u8g2_cb_t *rotation) : U8G2() {
    u8g2_SetupBuffer_SDL_128x64(&u8g2,rotation);
    u8x8_InitDisplay((u8x8_t*)&u8g2);
  }
};
extern U8G2_SDL2_128x64 u8g2;
#endif // PLATFORM_WIN32

extern page_manager_t page_manager;
extern int get_key(void);
#endif // !__PAGE_H__
