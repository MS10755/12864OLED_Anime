#include "page.h"
#include "anime.h"
#include "w_list.h"

PAGE_DECLARE(PAGE_ID_MENU)
w_list list1(0,0);

static int open(){
    static bool is_added_item = false;
    if(is_added_item == false){
        is_added_item = true;
        list1.add_itme("exiadft4");
        list1.add_itme("exiadft4");
        list1.add_itme("setting");
        list1.add_itme("help");
        list1.add_itme("about");
        list1.add_itme("time");
        list1.add_itme("ex32it1");
        list1.add_itme("exit2");
        list1.add_itme("about");
        list1.add_itme("exit3");
        list1.add_itme("ex1it231");
        list1.add_itme("exit2131");
        list1.add_itme("123213");
        list1.add_itme("adwew");
        list1.add_itme("2231");
    }
    list1.reset();
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
    }else if( key== 4 && list1.isPlayingAnime() ==false){
        page_switch(&page_manager,PAGE_ID_MAIN);
    }

}

