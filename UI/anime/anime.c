#include "anime.h"
#include "HAL.h"
#include <stdlib.h>
#include <assert.h>

uint32_t animation_millis(void){
	return HAL_GetTick();
}

uint32_t animation_passed(uint32_t pre_ms){
	uint32_t now = animation_millis();
	return now >= pre_ms ? now-pre_ms : UINT32_MAX - pre_ms + now;
}

void anime_process(anime_parms_t * parms){
    if (parms->status == ANIME_STATUS_END) {
        return;
    }

    if (parms->status == ANIME_STATUS_INIT) {
        return;
    }

    if (parms->status == ANIME_STATUS_PLAYING) {
        if (parms->passed_time < parms->duration) {
            parms->passed_time = animation_passed(parms->start_time);

            if (parms->easing_fun) {
                parms->easing_fun(parms);
            }
            else {
                printf("parms->easing_fun is NULL!\r\n");
            }
//            printf("pass_time:%d  val:%d\r\n", parms->passed_time, parms->val);
        }
        else
        {
            parms->val = parms->val_target;
            parms->status = ANIME_STATUS_END;
//            printf("END pass_time:%d  val:%d\r\n", parms->passed_time, parms->val);
        }
    }
}

void anime_cancel(anime_parms_t* parms,uint16_t duration) {
    parms->val_target = parms->val_begin;
    parms->val_begin = parms->val;
    parms->duration = duration;
    parms->start_time = animation_millis();
    parms->passed_time = 0;
}


void anime_init(anime_parms_t* parms,int begin,int end,int duration,easing_fun_exec_t easing_fun) {
    parms->val_begin = begin;
    parms->val_target = end;
    parms->val = parms->val_begin;
    parms->duration = duration;
    parms->easing_fun = easing_fun;
    parms->status = ANIME_STATUS_INIT;
}


void anime_play(anime_parms_t* parms) {
    if (parms->status == ANIME_STATUS_INIT || parms->status == ANIME_STATUS_END) {
        parms->start_time = animation_millis();
        parms->val = parms->val_begin;
        parms->passed_time = 0;
        parms->status = ANIME_STATUS_PLAYING;
    }
}

anime_timeLine_t * anime_timeLine_create(void){
    anime_timeLine_t * atl = (anime_timeLine_t*)malloc(sizeof(anime_timeLine_t));
    assert(atl);
    atl->next = NULL;
    atl->a_parms = NULL;
    return atl;
}

void anime_timeLine_del(anime_timeLine_t *timeLine){
    assert(timeLine);
    anime_timeLine_t * next = NULL;
    do{
        next = timeLine->next;
        free(timeLine);
        timeLine = next;
    }while (timeLine);
}

void anime_timeLine_add(anime_timeLine_t *timeLine,anime_parms_t* parms){
    assert(timeLine);
    assert(parms);
    if(timeLine->next == NULL && timeLine->a_parms == NULL){
        timeLine->a_parms = parms;
        return;
    }
    while(timeLine->next != NULL){
        timeLine = timeLine->next;
    }
    anime_timeLine_t * atl = (anime_timeLine_t*)malloc(sizeof(anime_timeLine_t));
    atl->a_parms = parms;
    atl->next = NULL;
    timeLine->next = atl;
}

