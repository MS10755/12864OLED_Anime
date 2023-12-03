#include "page.h"
#include "anime.h"
#include "w_list.h"

PAGE_DECLARE(PAGE_ID_MENU)
w_list list1(0,0);

static int open(){
    list1.add_itme("game1");
    list1.add_itme("game12");
    list1.add_itme("setting");
    list1.add_itme("help");
    list1.add_itme("about");
    list1.add_itme("time");
    list1.add_itme("exit");
    return PAGE_OK;
}


static int close(){

    return PAGE_OK;
}

static int loop(){
    u8g2.clearBuffer();
    list1.draw();
    u8g2.sendBuffer();
    return PAGE_OK;
}

static void key_handler(int key,int event){
    if(key == 2){
        list1.scroll(-1);

    }else if(key == 3){
        list1.scroll(1);
    }

}

