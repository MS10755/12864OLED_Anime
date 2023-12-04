#include <stdio.h>
#include "page.h"
#include "anime.h"
#include "easing_functions.h"
#include <math.h>
#include <String>
#include "HAL.h"
using namespace std;

#define min(a,b) ((a<b)? a: b)

static anime_parms a_clock_x;

int hours = 9;
int minutes = 30;
int seconds = 1;
const char *number[12]={"6","5","4","3","2","1","12","11","10","9","8","7"};
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
float radius = min(SCREEN_HEIGHT, SCREEN_WIDTH)/2-1;

const int X_CENTER = SCREEN_WIDTH / 2;
const int Y_CENTER = SCREEN_HEIGHT / 2;

int x1, y1, x2, y2;
double angle;


PAGE_DECLARE(PAGE_ID_CLOCK)


static void draw(void) {
   int x_offst = a_clock_x.val;

  //u8g.drawCircle(X_CENTER, Y_CENTER, radius);
  u8g2.drawCircle(x_offst+ X_CENTER, Y_CENTER, 1);
  //draw minute's ticks (60 lines)
  for(int j=1; j<=60; j++){
    angle = j*6;
    angle = angle * 0.0174533;

    x1 = X_CENTER + (sin(angle) * radius);
    y1 = Y_CENTER + (cos(angle) * radius);
    x2 = X_CENTER + (sin(angle) * (radius));
    y2 = Y_CENTER + (cos(angle) * (radius));
    u8g2.drawLine(x_offst+ x1,y1,x_offst+ x2,y2);
    
  }
  //draw hour's ticks (12 lines)
  for(int j=0; j<12; j++){
    angle = j*30;
    angle = angle * 0.0174533;

    x1 = X_CENTER + (sin(angle) * radius);
    y1 = Y_CENTER + (cos(angle) * radius);
    x2 = X_CENTER + (sin(angle) * (radius - 4));
    y2 = Y_CENTER + (cos(angle) * (radius - 4));
    u8g2.drawLine(x_offst+ x1,y1,x_offst + x2,y2);
    //draw hour digits(12 lines)
    x2 = X_CENTER + (sin(angle) * (radius - 8));
    y2 = Y_CENTER + (cos(angle) * (radius - 8));
    u8g2.setFont(u8g_font_chikita);
    u8g2.drawStr(x_offst+ x2-2, y2+3, string(number[j]).c_str());

    angle = seconds*6;
    angle = angle * 0.0174533;
    x2 = X_CENTER + (sin(angle) * (radius - 1));
    y2 = Y_CENTER - (cos(angle) * (radius - 1));
    u8g2.drawLine(x_offst+ X_CENTER,Y_CENTER,x_offst+ x2,y2);

    angle = minutes*6;
    angle = angle * 0.0174533;
    x2 = X_CENTER + (sin(angle) * (radius - 10));
    y2 = Y_CENTER - (cos(angle) * (radius - 10));
    u8g2.drawLine(x_offst+ X_CENTER,Y_CENTER,x_offst+ x2,y2);

    angle = hours*30 + ((minutes / 12) * 6);
    angle = angle * 0.0174533;
    x2 = X_CENTER + (sin(angle) * (radius / 2));
    y2 = Y_CENTER - (cos(angle) * (radius / 2));
    u8g2.drawLine(x_offst +(int) X_CENTER,Y_CENTER,x_offst + (int)x2,y2);

    /*
    //draw sweep hand
    float fraction = getCurrentTime() - floor(getCurrentTime());
    angle = (fraction * 360) / 0.0174533;
    x1 = X_CENTER + (sin(angle) * radius - 1);
    y1 = Y_CENTER - (cos(angle) * radius - 1);
    x2 = X_CENTER + (sin(angle) * (radius - 4));
    y2 = Y_CENTER - (cos(angle) * (radius - 4));
    u8g.drawLine(x1,y1,x2,y2);
    */
  }
}

static void anime_finfised_cb(anime_parms * parms){
    page_switch(&page_manager,PAGE_ID_MAIN);
}

static int open(){
    memset(&a_clock_x,0x00,sizeof(anime_parms));
    anime_init(&a_clock_x,64,0,700,easing_fun_OutBounce);
    anime_play(&a_clock_x);
 return PAGE_OK;
}

static int close(){

    return PAGE_OK;
}

static int loop(){
    
 static uint32_t last_millist;
 if(HAL_Passed(last_millist)> 1000){
    last_millist = HAL_GetTick();
     seconds +=1;
 }
  if(seconds==60){ seconds=seconds-60; minutes +=1;}
  if(minutes==60){ minutes=0; hours +=1;}
  if(hours==24){hours=1;}
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
  anime_process(&a_clock_x);
return PAGE_OK;
}


static void key_handler(int key,int event){
    if(key >= 1){
        anime_init(&a_clock_x,a_clock_x.val,64,500,easing_fun_OutBounce);
        a_clock_x.finished_cb = anime_finfised_cb;
        anime_play(&a_clock_x);
    }
}