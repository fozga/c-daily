#include "dispatcher.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int ticks;
    int clicks;
} app_state_t;

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test, const char* msg) {
    g_assertions++;
    if (!cond) {
        g_failures++;
        printf("[FAIL] %s: %s\n", test, msg);
    }
}

static void on_tick(event_id_t id, int event_data, void* ctx) {
    (void)event_data;
    if (id != EV_TIMER_TICK || ctx == NULL) {
        return;
    }
    app_state_t* st = (app_state_t*)ctx;
    st->ticks++;
}

static void on_button_count(event_id_t id, int event_data, void* ctx) {
    (void)event_data;
    if (id != EV_BUTTON_PRESS || ctx == NULL) {
        return;
    }
    app_state_t* st = (app_state_t*)ctx;
    st->clicks++;
}

static void on_button_quit(event_id_t id, int event_data, void* ctx) {
    (void)ctx;
    if (id == EV_BUTTON_PRESS && event_data == 99) {
        dispatch_request_exit();
    }
}

int main(void) {
    const char* t = "dispatcher_app_loop";
    app_state_t state = {0, 0};
    int guard = 0;

    dispatch_init();

    assert_true(dispatch_register(EV_TIMER_TICK, on_tick, &state), t,
                "register tick callback");
    assert_true(dispatch_register(EV_BUTTON_PRESS, on_button_count, &state), t,
                "register button counter callback");
    assert_true(dispatch_register(EV_BUTTON_PRESS, on_button_quit, &state), t,
                "register button quit callback");

    while (!dispatch_should_exit()) {
        dispatch_fire_event(EV_TIMER_TICK, 0);
        if (state.ticks > 5) {
            dispatch_fire_event(EV_BUTTON_PRESS, 99);
        }

        guard++;
        if (guard > 1000000) {
            /* Safety break for incomplete student implementations. */
            break;
        }
    }

    assert_true(state.ticks == 6, t, "ticks should be exactly 6");
    assert_true(state.clicks == 1, t, "clicks should be exactly 1");
    assert_true(dispatch_should_exit(), t, "exit flag should be set");

    if (g_failures == 0) {
        printf("[OK] all tests passed (%d assertions)\n", g_assertions);
        return 0;
    }

    printf("[FAIL] %d/%d assertions failed\n", g_failures, g_assertions);
    return 1;
}
