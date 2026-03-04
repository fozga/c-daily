#include "fsm.h"

#include <stddef.h>

typedef void (*action_fn)(fsm_t*);

typedef struct {
    state_t   next_state;
    action_fn action;
    bool      valid;
} transition_t;

static void action_noop(fsm_t* fsm) {
    (void)fsm;
}

/* Fill in ONE transition as an example:
 * CLOSED + CMD_LISTEN -> LISTEN
 * TODO: learner should fill the remaining transitions.
 */
static const transition_t transitions[NUM_STATES][NUM_EVENTS] = {
    [STATE_CLOSED] = {
        [EV_CMD_LISTEN] = { STATE_LISTEN, action_noop, true }
    }
};

void fsm_init(fsm_t* fsm, void* ctx) {
    if (!fsm) {
        return;
    }
    fsm->current_state = STATE_CLOSED;
    fsm->user_ctx = ctx;
}

bool fsm_dispatch(fsm_t* fsm, event_t ev) {
    if (!fsm) {
        return false;
    }

    if ((int)fsm->current_state < 0 || fsm->current_state >= NUM_STATES) {
        return false;
    }
    if ((int)ev < 0 || ev >= NUM_EVENTS) {
        return false;
    }

    /* TODO:
     * - Complete transition table in this file.
     * - Keep bounds checks and invalid-transition handling.
     * - Ensure callback ordering is deterministic.
     */
    const transition_t tr = transitions[fsm->current_state][ev];
    if (!tr.valid) {
        return false;
    }

    fsm->current_state = tr.next_state;
    if (tr.action) {
        tr.action(fsm);
    }
    return true;
}

state_t fsm_get_state(const fsm_t* fsm) {
    if (!fsm) {
        return STATE_CLOSED;
    }
    return fsm->current_state;
}
