#include "w_menu.h"

void w_menu::add_itme(icont_t icon)
{
    icon_list.push_back(icon);
}

void w_menu::draw()
{
    int refer_x = 0;
    for(size_t i=0;i<icon_list.size() ;i++){
        icont_t & icon = icon_list[i];        
        u8g2.drawBitmap(refer_x + i*icon.width,pos_y,4,32,icon.icon_data);
    }
}
