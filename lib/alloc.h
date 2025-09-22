// Alloc (v0.0.1)
// ---
//
// Functions and macros for safer memory management.
//
// ```c
// void* result = allocSafe(100);
//
// allocSafe(100); // gives a compiler warning if not checked
//
// deallocSafe(&result);
// ```
// ___HEADER_END___
#pragma once

#include <stdlib.h>

/**
 * Allocate memory and force caller to check on the result.
 * @name allocSafe
 * @param {size_t} size - Number of bytes to allocate
 * @returns {void*} Allocated memory pointer
 * @example
 *   void* result = allocSafe(100);
 */
[[nodiscard]] static inline void *allocSafe(size_t size) {
  return malloc(size);
}

/**
 * Reallocate memory and force caller to check on the result.
 * @name reallocSafe
 * @param {void**} ptr - Pointer to the pointer to be reallocated
 * @param {size_t} size - New size in bytes
 * @returns {void*} Reallocated memory pointer
 * @example
 *   void* result = allocSafe(100);
 *   result = reallocSafe(&result, 200);
 */
[[nodiscard]] static inline void *reallocSafe(void **ptr, size_t size) {
  return realloc(*ptr, size);
}

/**
 * Safely deallocate memory and set pointer to nullptr.
 * @name deallocSafe
 * @param {void**} DoublePointer - Pointer to the pointer that should be freed
 * @example
 *   char *ptr = allocSafe(100);
 *   deallocSafe(&ptr);  // ptr is now nullptr
 */
#define deallocSafe(DoublePointer)                                             \
  {                                                                            \
    if (*(DoublePointer) != nullptr) {                                         \
      free((void *)*(DoublePointer));                                          \
      *(DoublePointer) = nullptr;                                              \
    }                                                                          \
  }
