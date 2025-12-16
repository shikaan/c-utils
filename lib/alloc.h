// Alloc (v0.1.0)
// ---
//
// Functions and macros for safer memory management.
//
// ```c
// void* result = allocate(100);
//
// allocate(100); // gives a compiler warning if not checked
//
// deallocate(&result);
// ```
// ___HEADER_END___
#pragma once

#include <stdlib.h>

/**
 * Allocate zero-ed memory and force caller to check on the result.
 * @name allocate
 * @param {size_t} size - Number of bytes to allocate
 * @returns {void*} Allocated memory pointer
 * @example
 *   void* result = allocate(100);
 */
[[nodiscard]] static inline void *allocate(size_t size) {
  return calloc(1, size);
}

/**
 * Reallocate memory and force caller to check on the result.
 * @name reallocate
 * @param {void**} ptr - Pointer to the pointer to be reallocated
 * @param {size_t} size - New size in bytes
 * @returns {void*} Reallocated memory pointer
 * @example
 *   void* result = allocate(100);
 *   result = reallocate(&result, 200);
 */
[[nodiscard]] static inline void *reallocate(void **ptr, size_t size) {
  return realloc(*ptr, size);
}

/**
 * Safely deallocate memory and set pointer to NULL.
 * @name deallocate
 * @param {void**} DoublePointer - Pointer to the pointer that should be freed
 * @example
 *   char *ptr = allocate(100);
 *   deallocate(&ptr);  // ptr is now NULL
 */
#define deallocate(DoublePointer)                                              \
  {                                                                            \
    if (*(DoublePointer) != NULL) {                                            \
      free((void *)*(DoublePointer));                                          \
      *(DoublePointer) = NULL;                                                 \
    }                                                                          \
  }
