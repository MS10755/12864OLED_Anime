#ifndef __WIDGET_LIST__
#define __WIDGET_LIST__
#include "w_obj.h"
#include <string>
#include <vector>
#include <map>
#include "anime.h"
#include "easing_functions.h"

using namespace std;

#ifndef W_LIST_MAX_LINE
#define W_LIST_MAX_LINE 8
#endif // !W_LIST_MAX_LINE


#ifndef W_LIST_MAX_CHAR
#define W_LIST_MAX_CHAR 16
#endif // !W_LIST_MAX_CHAR

class w_list : w_obj
{
private:
    /* data */
    vector<string> items;
    anime_parms a_list_y;
    anime_parms a_cursor_y;
    anime_parms a_cursor_width;

    int cursor = 0;
    int show_area_begin = 0;
    int show_area_end = 5;
    int show_area_size = 6;
    vector<int> move_cursor(int step);
    bool need_set_anime = true;
public:
    w_list();
    w_list(int x, int y): w_obj(x,y){
    };
    ~w_list(){
        
    };
    void add_itme(string itme);
    void add_itme(vector<string> itmes);
    void draw() override;
    void scroll(int step);
    void setAnime();

};


#endif // !__WIDGET_LIST__