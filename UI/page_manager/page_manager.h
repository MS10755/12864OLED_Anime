#ifndef __PAGE_MANAGER_H_
#define __PAGE_MANAGER_H_
#include <stdint.h>
#include <assert.h>
#include <string.h>

#ifndef PAGE_MANAGER_MAX_PAGE
#define PAGE_MANAGER_MAX_PAGE 8
#endif // !PAGE_MANAGER_MAX_PAGE

typedef int(*page_callback_t)(void);
typedef void(*page_key_handler_t)(int key,int event);

#define PAGE_OK                 0x0
#define PAGE_OPEN_FAIL          0x01
#define PAGE_CLOSE_FAIL         0x02
#define PAGE_FULL               0x03
#define PAGE_ALWAYS_REGISTED    0x04
#define PAGE_ERROR_PARMS        0x05

enum{
    PAGE_PANAGER_SIGNAL_SWITCH = (0x01 << 0),
};

typedef struct page_s
{
    int page_id;
    page_callback_t open;
    page_callback_t loop;
    page_callback_t close;
    page_key_handler_t key_event_handler;
}page_t;


typedef struct page_manager_s
{
    int current_page_id;
    int last_page_id;
    int switch_page_id;
    uint8_t page_num;
    page_t page_list[PAGE_MANAGER_MAX_PAGE];
    uint32_t signals;
}page_manager_t;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void page_manager_init(page_manager_t *page_manager);

int page_register(
    page_manager_t *page_manager, int id,
    page_callback_t open, page_callback_t loop,
    page_callback_t close,page_key_handler_t key_event_handler);

int page_switch(page_manager_t *page_manager, int id);

void page_key_event_send(page_manager_t *page_manager, int key, int event);

void page_manager_loop(page_manager_t *page_manager);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // __PAGE_MANAGER_H_

