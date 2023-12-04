#include "page.h"
#include "anime.h"
#include "w_menu.h"

w_menu menu(0,0);


anime_parms a_menu_y;

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

int switch_page_id = 0;

static void anime_finised_cb(anime_parms * parms){
    page_switch(&page_manager,*(int*)parms->user_data);
}

static int open(){
    u8g2.setDrawColor(1);
    static bool is_init_menu = false;
    if(is_init_menu == false){
        is_init_menu= true;
        for(int i=0;i<ICON_NUMS;i++){
            menu.add_itme(icons[i]);
        }
    }
    anime_init(&a_menu_y,u8g2.getHeight(),0,500,easing_fun_OutQuad);
    anime_play(&a_menu_y);
    return PAGE_OK;
}


static int close(){

    return PAGE_OK;
}

static int loop(){
    anime_process(&a_menu_y);
    vector<int> pos = menu.getPos();
    int menu_x = pos[0];
    int menu_y = a_menu_y.val;
    menu.setPos(menu_x,menu_y);
    u8g2.clearBuffer();
    menu.draw();
    u8g2.sendBuffer();
    return PAGE_OK;
}

static void key_handler(int key,int event){
    if(key == 1 && menu.isPlayingAnime() == false){
        int select_index = menu.getCursor();
        switch (select_index)
        {
        case 0:
            printf("clicked timer\n");
            anime_init(&a_menu_y,a_menu_y.val,-u8g2.getHeight(),500,easing_fun_OutQuad);
            a_menu_y.finished_cb = anime_finised_cb;
            switch_page_id = PAGE_ID_CLOCK;
            a_menu_y.user_data = &switch_page_id;
            anime_play(&a_menu_y);
            break;
        case 1:
            printf("clicked toolbox\n");
            anime_init(&a_menu_y,a_menu_y.val,-u8g2.getHeight(),500,easing_fun_OutQuad);
            a_menu_y.finished_cb = anime_finised_cb;
            switch_page_id = PAGE_ID_TOOLBOX;
            a_menu_y.user_data = &switch_page_id;
            anime_play(&a_menu_y);
            break;
        case 2:
            printf("clicked settings\n");
            anime_init(&a_menu_y,a_menu_y.val,-u8g2.getHeight(),500,easing_fun_OutQuad);
            a_menu_y.finished_cb = anime_finised_cb;
            switch_page_id = PAGE_ID_MENU;
            a_menu_y.user_data = &switch_page_id;
            anime_play(&a_menu_y);
            break;
        case 3:
            printf("clicked about\n");
            break;    
        default:
            break;
        }
    }

    if(key == 2){
        menu.scroll(-1);
    }else if(key == 3){
        menu.scroll(1);
    }

}

