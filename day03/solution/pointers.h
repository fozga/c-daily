#pragma once
#include <stddef.h>

/* Swaps the values pointed to by a and b. Safe to call if a == b.
   Returns 0 on success, -1 if either pointer is NULL. */
int ptr_swap(int* a, int* b);

/* Reverses the array of integers in-place.
   Returns 0 on success, -1 if arr is NULL. Does nothing if n <= 1. */
int ptr_reverse(int* arr, size_t n);

/* Finds the maximum value in the array.
   Stores a pointer to the maximum element in *out_max.
   Returns 0 on success.
   Returns -1 if arr is NULL, out_max is NULL, or n == 0. */
int ptr_max(const int* arr, size_t n, const int** out_max);

/* Copies 'count' integers from 'src' to 'dst'.
   The memory regions must NOT overlap (enforced by restrict).
   Returns 0 on success, -1 if any pointer is NULL. */
int ptr_copy_slice(const int* restrict src, int* restrict dst, size_t count);
