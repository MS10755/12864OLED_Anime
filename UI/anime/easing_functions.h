#ifndef __EASING_FUNCTIONS_H__
#define __EASING_FUNCTIONS_H__
#include "anime.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void easing_fun_linear(anime_parms_t* parms);
void easing_fun_OutQuad(anime_parms_t* parms);
void easing_fun_InElastic(anime_parms_t* parms);
void easing_fun_InBounce(anime_parms_t* parms);
void easing_fun_OutBounce(anime_parms_t* parms);
#ifdef __cplusplus
}
#endif
#endif


