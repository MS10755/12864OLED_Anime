#ifndef __HAL_H__
#define __HAL_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void HAL_Init();
uint32_t HAL_GetTick();
void HAL_Delay(uint32_t ms);
uint32_t HAL_Passed(uint32_t pre_ms);
#ifdef __cplusplus
}
#endif

#endif // !__HAL_H__
