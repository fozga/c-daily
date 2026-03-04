#pragma once
#include <stddef.h>
#include <stdbool.h>

#define STORE_KEY_MAX 64

typedef struct {
    char key[STORE_KEY_MAX];
    int  value;
    bool occupied;
} store_slot_t;

struct store {
    store_slot_t* slots;
    int           capacity;
    int           count;
};
