#pragma once
#include <stdbool.h>

#define MAX_CALLBACKS 16

typedef enum {
    EV_BUTTON_PRESS = 1,
    EV_TIMER_TICK,
    EV_NETWORK_RECV
} event_id_t;

/* Callback signature. 'ctx' is user-provided state. 'event_data' is event-specific payload. */
typedef void (*event_cb_t)(event_id_t id, int event_data, void* ctx);

/* Initializes the dispatcher. */
void dispatch_init(void);

/* Registers a callback for a specific event_id. Returns false if full. */
bool dispatch_register(event_id_t id, event_cb_t cb, void* ctx);

/* Fires an event, synchronously invoking all registered callbacks for that event. */
void dispatch_fire_event(event_id_t id, int event_data);

/* Returns the value of the global exit flag. */
bool dispatch_should_exit(void);

/* Sets the global exit flag to true. */
void dispatch_request_exit(void);
