#pragma once
#include <stdbool.h>

typedef enum {
    STATE_CLOSED = 0,
    STATE_LISTEN,
    STATE_SYN_RCVD,
    STATE_ESTABLISHED,
    NUM_STATES
} state_t;

typedef enum {
    EV_CMD_LISTEN = 0,
    EV_RCV_SYN,
    EV_RCV_ACK,
    EV_CMD_CLOSE,
    NUM_EVENTS
} event_t;

typedef struct {
    state_t current_state;
    void*   user_ctx;
} fsm_t;

/* Initializes FSM to STATE_CLOSED. */
void fsm_init(fsm_t* fsm, void* ctx);

/* Dispatches an event. Returns true if transition was valid, false if invalid. */
bool fsm_dispatch(fsm_t* fsm, event_t ev);

/* Returns current state. */
state_t fsm_get_state(const fsm_t* fsm);
