#include "fsm.h"

#include <stdbool.h>
#include <stdio.h>

static int g_assertions = 0;
static int g_failures = 0;

static void assert_true(bool cond, const char* test, const char* msg) {
    g_assertions++;
    if (!cond) {
        g_failures++;
        printf("[FAIL] %s: %s\n", test, msg);
    }
}

static void assert_state(state_t expected, state_t actual, const char* test, const char* msg) {
    g_assertions++;
    if (expected != actual) {
        g_failures++;
        printf("[FAIL] %s: %s (expected=%d actual=%d)\n",
               test, msg, (int)expected, (int)actual);
    }
}

static void test_initial_state_closed(void) {
    const char* t = "initial_state_closed";
    int counter = 0;
    fsm_t fsm;

    fsm_init(&fsm, &counter);
    assert_state(STATE_CLOSED, fsm_get_state(&fsm), t, "initial state must be CLOSED");
}

static void test_valid_handshake_sequence(void) {
    const char* t = "valid_handshake_sequence";
    int counter = 0;
    fsm_t fsm;
    fsm_init(&fsm, &counter);

    assert_true(fsm_dispatch(&fsm, EV_CMD_LISTEN), t, "CLOSED->LISTEN should be valid");
    assert_state(STATE_LISTEN, fsm_get_state(&fsm), t, "state should be LISTEN");

    assert_true(fsm_dispatch(&fsm, EV_RCV_SYN), t, "LISTEN->SYN_RCVD should be valid");
    assert_state(STATE_SYN_RCVD, fsm_get_state(&fsm), t, "state should be SYN_RCVD");

    assert_true(fsm_dispatch(&fsm, EV_RCV_ACK), t, "SYN_RCVD->ESTABLISHED should be valid");
    assert_state(STATE_ESTABLISHED, fsm_get_state(&fsm), t, "state should be ESTABLISHED");
}

static void test_valid_close_from_listen(void) {
    const char* t = "valid_close_from_listen";
    int counter = 0;
    fsm_t fsm;
    fsm_init(&fsm, &counter);

    assert_true(fsm_dispatch(&fsm, EV_CMD_LISTEN), t, "CLOSED->LISTEN should be valid");
    assert_state(STATE_LISTEN, fsm_get_state(&fsm), t, "must be LISTEN before close");

    assert_true(fsm_dispatch(&fsm, EV_CMD_CLOSE), t, "LISTEN->CLOSED should be valid");
    assert_state(STATE_CLOSED, fsm_get_state(&fsm), t, "state should return to CLOSED");
}

static void test_invalid_ack_while_closed(void) {
    const char* t = "invalid_ack_while_closed";
    int counter = 0;
    fsm_t fsm;
    fsm_init(&fsm, &counter);

    assert_true(!fsm_dispatch(&fsm, EV_RCV_ACK), t, "ACK in CLOSED should be invalid");
    assert_state(STATE_CLOSED, fsm_get_state(&fsm), t, "state must stay CLOSED");
}

static void test_callback_counter_increments(void) {
    const char* t = "callback_counter_increments";
    int counter = 0;
    fsm_t fsm;
    fsm_init(&fsm, &counter);

    assert_true(counter == 0, t, "counter starts at zero");
    assert_true(fsm_dispatch(&fsm, EV_CMD_LISTEN), t, "LISTEN transition should dispatch");
    assert_true(counter > 0, t, "callback should increment counter via user_ctx");
}

int main(void) {
    test_initial_state_closed();
    test_valid_handshake_sequence();
    test_valid_close_from_listen();
    test_invalid_ack_while_closed();
    test_callback_counter_increments();

    if (g_failures == 0) {
        printf("[OK] all tests passed (%d assertions)\n", g_assertions);
        return 0;
    }

    printf("[FAIL] %d/%d assertions failed\n", g_failures, g_assertions);
    return 1;
}
