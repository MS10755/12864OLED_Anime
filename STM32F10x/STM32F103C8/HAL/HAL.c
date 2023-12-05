#include "HAL.h"


uint32_t HAL_Passed(uint32_t pre_ms){
	uint32_t now = HAL_GetTick();
	return now >= pre_ms ? now-pre_ms : UINT32_MAX - pre_ms + now;
}