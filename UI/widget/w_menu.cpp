#include "w_menu.h"
#include <string.h>

#define ONE_ICON_SPACE 64
#define ANIME_TIME  400
#define ICON_HIDE_POS_Y 32
#define ICON_SHIFT_OFFSET   24

void w_menu::add_itme(icont_t icon)
{
    icon_list.push_back(icon);
}

void w_menu::draw()
{
    set_Anime();
    anime_process(&a_list_x);
    anime_process(&a_shiftOut_y);
    anime_process(&a_shiftIn_y);
    // printf("shiftOut:%d shiftIn:%d\r\n",a_shiftOut_y.val,a_shiftIn_y.val);
    int refer_x = pos_x;
    int refer_y = pos_y;
    u8g2.setFont(u8g2_font_7x13_tf);
    for(size_t i=0;i<icon_list.size() ;i++){
        icont_t & icon = icon_list[i];
        int y_shift = 0;
        if(a_shiftIn_y.user_data == &icon) y_shift = a_shiftIn_y.val;
        if(a_shiftOut_y.user_data == &icon) y_shift = a_shiftOut_y.val;
        u8g2.drawBitmap(a_list_x.val+refer_x + (i+1)* ONE_ICON_SPACE - 16,
                       refer_y + ICON_HIDE_POS_Y + y_shift,
                        4,32,icon.icon_data);
        int str_width = strlen(icon.text) * u8g2.getMaxCharWidth();
        u8g2.drawStr(refer_x + a_list_x.val + (i+1)* ONE_ICON_SPACE - str_width/2,
                    refer_y + ICON_HIDE_POS_Y + y_shift + icon.height + u8g2.getMaxCharHeight(),
                    icon.text);
    }
}

bool w_menu::isPlayingAnime()
{
    if(a_list_x.status != ANIME_STATUS_PLAYING && 
        a_shiftOut_y.status != ANIME_STATUS_PLAYING &&
        a_shiftIn_y.status != ANIME_STATUS_PLAYING
    ){
        return false;
    }
    return true;
}

void w_menu::scroll(int dir)
{
    if(dir < 0){
        // move left
        if(cursor > 0){
            last_cursor = cursor;
            cursor --;
            need_set_anime = true;
        }
    }else if(dir >0){
        // move right
        if(cursor < (int)icon_list.size() - 1){
            last_cursor = cursor;
            cursor ++;
            need_set_anime = true;
        }
    }
    // printf("last_curosr:%d cursosr:%d\r\n",last_cursor,cursor);
}

void w_menu::set_Anime()
{  
    if(need_set_anime == false) return;
    anime_init(&a_list_x,a_list_x.val,-cursor * ONE_ICON_SPACE,ANIME_TIME,easing_fun_linear);
    anime_play(&a_list_x);
    int last_shift_out_val = a_shiftOut_y.val;
    int last_shift_in_val = a_shiftIn_y.val;

    anime_init(&a_shiftOut_y,last_shift_in_val, - ICON_SHIFT_OFFSET,ANIME_TIME,easing_fun_linear);
    a_shiftOut_y.user_data = &icon_list[cursor];
    anime_play(&a_shiftOut_y);

    anime_init(&a_shiftIn_y,last_shift_out_val,0,ANIME_TIME,easing_fun_linear);
    a_shiftIn_y.user_data = &icon_list[last_cursor];
    anime_play(&a_shiftIn_y);

    need_set_anime = false;
}

int w_menu::getCursor()
{
    return cursor;
}

void w_menu::reset()
{
    need_set_anime = true;
}
