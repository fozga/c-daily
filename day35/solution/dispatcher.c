#include "dispatcher.h"

#include <signal.h>
#include <stddef.h>

typedef struct {
    event_id_t id;
    event_cb_t cb;
    void*      ctx;
    bool       in_use;
} callback_slot_t;

static callback_slot_t g_slots[MAX_CALLBACKS];
static volatile sig_atomic_t g_exit_flag = 0;

void dispatch_init(void) {
    for (int i = 0; i < MAX_CALLBACKS; ++i) {
        g_slots[i].id = 0;
        g_slots[i].cb = NULL;
        g_slots[i].ctx = NULL;
        g_slots[i].in_use = false;
    }
    g_exit_flag = 0;
}

bool dispatch_register(event_id_t id, event_cb_t cb, void* ctx) {
    if (cb == NULL) {
        return false;
    }

    for (int i = 0; i < MAX_CALLBACKS; ++i) {
        if (!g_slots[i].in_use) {
            g_slots[i].id = id;
            g_slots[i].cb = cb;
            g_slots[i].ctx = ctx;
            g_slots[i].in_use = true;
            return true;
        }
    }

    return false;
}

void dispatch_fire_event(event_id_t id, int event_data) {
    for (int i = 0; i < MAX_CALLBACKS; ++i) {
        if (g_slots[i].in_use && g_slots[i].id == id && g_slots[i].cb != NULL) {
            g_slots[i].cb(id, event_data, g_slots[i].ctx);
        }
    }
}

bool dispatch_should_exit(void) {
    return g_exit_flag != 0;
}

void dispatch_request_exit(void) {
    g_exit_flag = 1;
}
