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

class w_menu : w_obj
{
private:
    /* data */
    vector<icont_t> icon_list;
public:
    w_menu(/* args */);
    w_menu(int x, int y): w_obj(x,y){
    };
    void add_itme(icont_t icon);
    void draw() override;
    ~w_menu(){
        
    }
};



#endif
