#ifndef __ANIME_H__
#define __ANIME_H__
#include <stdint.h>
#include <stdio.h>

struct anime_parms;

typedef void (*easing_fun_exec_t)(struct anime_parms* parms);
enum {
	ANIME_STATUS_INIT,
	ANIME_STATUS_PLAYING,
	ANIME_STATUS_END,
};
typedef struct anime_parms{
	uint8_t status;
	uint16_t start_time;
	uint16_t passed_time;
	int val_begin;
	int val;
	int val_target;
	uint16_t duration;
	easing_fun_exec_t easing_fun;
}anime_parms_t;

#ifdef __cplusplus
extern "C" {
#endif

void anime_init(anime_parms_t* parms, int begin, int end, int duration, easing_fun_exec_t easing_fun);
void anime_play(anime_parms_t* parms);
void anime_process(anime_parms_t* parms);
void anime_cancel(anime_parms_t* parms, uint16_t duration);

#ifdef __cplusplus
}
#endif
#endif


