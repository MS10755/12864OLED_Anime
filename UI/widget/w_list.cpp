#include "w_list.h"

#define ITEM_FONT u8g2_font_6x10_tf
#define ANIME_TIME 240
#define SHOW_AREA_MOVE_SPACE 1  //光标距离页面边缘多少行开始滚动列表

static anime_timeLine_t *timeline;

vector<int> w_list::move_cursor(int step)
{
    vector<int> move(2);
    int show_area_move,cursor_move;
    show_area_move = show_area_begin;
    cursor_move = cursor;
    int next_cursor = step + cursor;
    if(next_cursor>= (show_area_begin + SHOW_AREA_MOVE_SPACE)  && next_cursor<= (show_area_end - SHOW_AREA_MOVE_SPACE)){
        cursor = next_cursor;
    }else if(next_cursor < (show_area_begin + SHOW_AREA_MOVE_SPACE)){
        int next_show_area_begin = next_cursor - SHOW_AREA_MOVE_SPACE;
        if(next_show_area_begin < 0){
            next_show_area_begin = 0;
        }
        if(next_cursor < 0){
            next_cursor = 0;
        }
        cursor = next_cursor;
        show_area_begin = next_show_area_begin;
        show_area_end = show_area_begin + show_area_size -1;
    }else if(next_cursor > (show_area_end - SHOW_AREA_MOVE_SPACE)){
        int next_show_area_end = next_cursor + SHOW_AREA_MOVE_SPACE;
        int last_item_index = (int)items.size() - 1;
        if(next_show_area_end > last_item_index){
            next_show_area_end = last_item_index;
        }
        if(next_cursor > last_item_index){
            next_cursor = last_item_index;
        }
        cursor = next_cursor;
        show_area_end = next_show_area_end;
        show_area_begin = show_area_end - show_area_size + 1;
    }
    show_area_move = show_area_begin - show_area_move;
    cursor_move = cursor - cursor_move;
    move[0] = show_area_move;
    move[1] = cursor_move;
    return move;
}

void w_list::add_itme(string itme)
{
    items.push_back(itme);
}

void w_list::add_itme(vector<string> itmes)
{
    for(string item : itmes){
        items.push_back(item);
    }
}


void w_list::draw()
{
    if(timeline){
       bool finish = anime_timeLine_process(timeline);
       if(finish){
        anime_timeLine_del(timeline);
        timeline = NULL;
       }
    }

    setAnime();
    anime_process(&a_list_y);
    anime_process(&a_cursor_y);
    anime_process(&a_cursor_width);
    
    int font_height = u8g2.getMaxCharHeight();

    int list_ref_y = a_list_y.val;
    int shift_x = 10;
    u8g2.setDrawColor(1);
    u8g2.drawRBox(shift_x + pos_x,list_ref_y + pos_y + a_cursor_y.val,a_cursor_width.val ,font_height,4);
    u8g2.setFontMode(1);
    u8g2.setDrawColor(2);

    int i = 0;
    u8g2.setFont(ITEM_FONT);
    for(string item : items){
        int shifout_x = 0;
        if( i< W_LIST_SHIFTOUT_NUM){
            shifout_x = a_shiftOut[i].val;
        }
        u8g2.drawStr(shifout_x + shift_x + pos_x, list_ref_y + pos_y + (i+1) * font_height,item.c_str());
        i++;
    }
}

bool w_list::isPlayingAnime()
{ 
    if(a_list_y.status != ANIME_STATUS_PLAYING && 
        a_cursor_y.status != ANIME_STATUS_PLAYING &&
        a_cursor_width.status != ANIME_STATUS_PLAYING
    ){
        return false;
    }
    return true;
}

void w_list::scroll(int step)
{
    vector<int> move = move_cursor(step);
    need_set_anime = true;
    printf("step:%d  cursor:%d begin:%d end:%d \r\n",step,cursor,show_area_begin,show_area_end);    


}

void w_list::setAnime()
{
    if(need_set_anime == false) return;
    if(a_list_y.status == ANIME_STATUS_PLAYING || 
        a_cursor_y.status == ANIME_STATUS_PLAYING || 
        a_cursor_width.status == ANIME_STATUS_PLAYING){
        return;
    }
    u8g2.setFont(ITEM_FONT);
    int font_height = u8g2.getMaxCharHeight();
    int font_width = u8g2.getMaxCharWidth();
    int cursor_pos_char_num = items[cursor].size();
    
    anime_init(&a_cursor_width,a_cursor_width.val,cursor_pos_char_num * font_width,ANIME_TIME ,easing_fun_OutQuad);
    anime_play(&a_cursor_width);

    anime_init(&a_list_y,a_list_y.val, -show_area_begin * font_height, ANIME_TIME ,easing_fun_OutQuad);
    anime_play(&a_list_y);

    anime_init(&a_cursor_y,a_cursor_y.val,cursor * font_height,ANIME_TIME ,easing_fun_OutQuad);
    anime_play(&a_cursor_y);

    need_set_anime = false;
}

void w_list::reset()
{
    timeline = anime_timeLine_create();
    for(int i=0;i<W_LIST_SHIFTOUT_NUM;i++){
        anime_init(&a_shiftOut[i],-50,0,ANIME_TIME,easing_fun_OutQuad);
        anime_timeLine_add(timeline,&a_shiftOut[i]);
    }

    memset(&a_list_y,0x00,sizeof(anime_parms));
    memset(&a_cursor_y,0x00,sizeof(anime_parms));
    memset(&a_cursor_width,0x00,sizeof(anime_parms));
    
    cursor = 0;
    show_area_begin = 0;
    show_area_end = 5;
    show_area_size = 6;
    need_set_anime = true;
}
