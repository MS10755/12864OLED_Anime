#include "HAL.h"
#include "SDL.h"
#include <Windows.h>

void HAL_Init(){
    
}

uint32_t HAL_GetTick(){
    return  GetTickCount();
}

void HAL_Delay(uint32_t ms){
    // SDL_Delay(ms);
    Sleep(ms);
}
