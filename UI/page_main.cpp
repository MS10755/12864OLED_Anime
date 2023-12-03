#include "page.h"
#include "anime.h"
#include "w_menu.h"

w_menu menu(0,16);


//icons 
#define ICON_NUMS  4

extern "C" const unsigned char gImage_about_32x32[128];
extern "C" const unsigned char gImage_clock_32x32[128];
extern "C" const unsigned char gImage_setting2_32x32[128];
extern "C" const unsigned char gImage_toolbox_32x32[128];


icont_t icons[] ={
   { gImage_clock_32x32,32,32,"timer"},
   { gImage_toolbox_32x32,32,32,"toolbox"},
   { gImage_setting2_32x32,32,32,"settings"},
   { gImage_about_32x32,32,32,"about"},
};


PAGE_DECLARE(PAGE_ID_MAIN)

static int open(){
    static bool is_init_menu = false;
    if(is_init_menu == false){
        is_init_menu= true;
        for(int i=0;i<ICON_NUMS;i++){
            menu.add_itme(icons[i]);
        }
    }

    return PAGE_OK;
}


static int close(){

    return PAGE_OK;
}

static int loop(){
    u8g2.clearBuffer();
    menu.draw();
    u8g2.sendBuffer();
    return PAGE_OK;
}

static void key_handler(int key,int event){

}

