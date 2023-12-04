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

uint32_t HAL_Passed(uint32_t pre_ms){
	uint32_t now = HAL_GetTick();
	return now >= pre_ms ? now-pre_ms : UINT32_MAX - pre_ms + now;
}