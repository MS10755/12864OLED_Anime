#include  "page_manager.h"
#include <stdio.h>

static page_t* page_manager_find_page_by_id(page_manager_t * page_manager,int id){
    if(id <= 0) return NULL;
    for(uint8_t i=0;i< page_manager->page_num;i++){
        page_t * page = &page_manager->page_list[i];
        if(page->page_id == id){
            return page;
        }
    }
    return NULL;
}

static void page_manager_signal_set(page_manager_t * page_manager,uint32_t signals){
    page_manager->signals |= signals;
}

static void page_manager_signal_clear(page_manager_t * page_manager,uint32_t signals){
    page_manager->signals &= ~signals;
}



void page_manager_init(page_manager_t * page_manager){
    assert(page_manager);
    if(!page_manager) return;
    memset(page_manager,0x00,sizeof(page_manager));
}

int page_register(
    page_manager_t * page_manager,
    int id,
    page_callback_t open,
    page_callback_t loop,
    page_callback_t close,
    page_key_handler_t key_event_handler
){
    assert(page_manager);
    assert(open);
    assert(loop);
    assert(close);

    if(!page_manager || !open || !loop || !close) return PAGE_ERROR_PARMS;
    
    if(page_manager->page_num > PAGE_MANAGER_MAX_PAGE) return PAGE_FULL;

    page_t * page = page_manager_find_page_by_id(page_manager,id);
    assert(page == NULL);
    if(page){
        return PAGE_ALWAYS_REGISTED;
    }

    page = &page_manager->page_list[page_manager->page_num++];
    page->page_id = id;
    page->open = open;
    page->loop = loop;
    page->close = close;
    page->key_event_handler = key_event_handler;
}

int page_switch(page_manager_t * page_manager, int id){
    assert(page_manager);
    assert(id != page_manager->current_page_id);
    page_manager->switch_page_id = id;
    page_manager_signal_set(page_manager,PAGE_PANAGER_SIGNAL_SWITCH);
}


void page_key_event_send(page_manager_t * page_manager,int key,int event){
    assert(page_manager);
    page_t * loop_page = page_manager_find_page_by_id(page_manager,page_manager->current_page_id);
    if(loop_page && loop_page->key_event_handler){
        loop_page->key_event_handler(key,event);
    }
}

void page_manager_loop(page_manager_t * page_manager){
    assert(page_manager);
    printf("current_page:%d last_page:%d \r\n",page_manager->current_page_id,page_manager->last_page_id);
    if(page_manager->signals & PAGE_PANAGER_SIGNAL_SWITCH){
        page_manager_signal_clear(page_manager,PAGE_PANAGER_SIGNAL_SWITCH);

        page_t * close_page = page_manager_find_page_by_id(page_manager,page_manager->current_page_id);
        if(close_page){
            if(close_page->close){
                close_page->close();
            }
        }

        page_manager->last_page_id = page_manager->current_page_id;

        page_manager->current_page_id = page_manager->switch_page_id;

        page_t * open_page = page_manager_find_page_by_id(page_manager,page_manager->current_page_id);
        if(open_page){
            if(open_page->open){
                open_page->open();
            }
        }
    }else{
        page_t * loop_page = page_manager_find_page_by_id(page_manager,page_manager->current_page_id);
        if(loop_page){
            if(loop_page->loop){
                loop_page->loop();
            }
        }
    }
}