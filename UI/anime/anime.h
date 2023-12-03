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

typedef struct anime_timeLine
{
	struct anime_timeLine * next;
	anime_parms_t * a_parms;
}anime_timeLine_t;


#ifdef __cplusplus
extern "C" {
#endif

void anime_init(anime_parms_t* parms, int begin, int end, int duration, easing_fun_exec_t easing_fun);
void anime_play(anime_parms_t* parms);
void anime_process(anime_parms_t *parms);
void anime_cancel(anime_parms_t* parms, uint16_t duration);

anime_timeLine_t *anime_timeLine_create(void);
void anime_timeLine_del(anime_timeLine_t *timeLine);
void anime_timeLine_add(anime_timeLine_t *timeLine, anime_parms_t *parms);

#ifdef __cplusplus
}
#endif
#endif
