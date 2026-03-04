#pragma once
#include <stddef.h>

/* Returns the minimum of two int values (using a fixed MAX macro). */
int so_min(int a, int b);

/* Clamps value between lo and hi. */
int so_clamp(int val, int lo, int hi);

/* Swaps two integers via pointers. */
void so_swap(int* a, int* b);
