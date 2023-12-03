#ifndef __WIDGET_COMMON__
#define __WIDGET_COMMON__
#include <stdint.h>
#include "page.h"

class w_obj
{
protected:
    int pos_x;
    int pos_y;
public:
    w_obj(int _x = 0,int _y = 0): pos_x(_x),pos_y(_y){
    };
    virtual void draw() = 0;
};


#endif // !__WIDGET_LIST__