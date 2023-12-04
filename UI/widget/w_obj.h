#ifndef __WIDGET_COMMON__
#define __WIDGET_COMMON__
#include <stdint.h>
#include "page.h"
#include <vector>
using namespace std;
class w_obj
{
protected:
    int pos_x;
    int pos_y;
public:
    w_obj(int _x = 0,int _y = 0): pos_x(_x),pos_y(_y){
    };
    virtual void draw() = 0;
    virtual bool isPlayingAnime(){
        return false;
    };
    vector<int> getPos(){
        vector<int> pos(2);
        pos[0] = pos_x;
        pos[1] = pos_y;
        return pos;
    };
    void setPos(int _x = 0,int _y = 0){
        pos_x = _x;
        pos_y = _y;
    };
};


#endif // !__WIDGET_LIST__