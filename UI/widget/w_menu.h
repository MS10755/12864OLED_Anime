#ifndef __WIDGET_MENU__
#define __WIDGET_MENU__
#include "w_obj.h"
#include "anime.h"
#include "easing_functions.h"

#include <vector>
using namespace std;
typedef struct{
    const unsigned char * icon_data;
    int height;
    int width;
    const char * text;
}icont_t;

class w_menu : public w_obj
{
private:
    /* data */
    vector<icont_t> icon_list;
    int cursor = 0;
    int last_cursor;
    anime_parms a_shiftOut_y;
    anime_parms a_shiftIn_y;
    anime_parms a_list_x;

    bool need_set_anime = false;
public:
    w_menu(/* args */);
    w_menu(int x, int y): w_obj(x,y){
    };
    void add_itme(icont_t icon);
    void draw() override;
    bool isPlayingAnime() override;
    void scroll(int dir);
    void set_Anime();
    int getCursor();
    void reset();
    ~w_menu(){

    }
};



#endif
