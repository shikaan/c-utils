// Panic (v0.0.1)
// ---
//
// Functions and macros to deal with unrecoverable errors.
//
// ```c
// panicif(1 == 1, "one is one"); // panics
//
// panic("this will panic");
// ```
// ___HEADER_END___
#pragma once

#include <stdio.h>
#include <stdlib.h>

static inline void __panic(const char msg[], const char file[], int line) {
  fprintf(stderr, "panic: %s\n  at %s:%d\n", msg, file, line);
  abort();
}

static inline void __panicif(int condition, const char msg[], const char file[],
                             int line) {
  if (condition) {
    __panic(msg, file, line);
  }
}

/**
 * Unconditionally panic and abort.
 * @name panic
 * @param {const char[]} Msg - The message to print on panic
 * @example
 *   panic("unrecoverable error");
 */
#define panic(Condition, Msg) __panic(Condition, Msg, __FILE__, __LINE__)

/**
 * Panic and abort if a condition is true.
 * @name panicif
 * @param {int} Condition - The condition to check
 * @param {const char[]} Msg - The message to print on panic
 * @example
 *   int x = 1;
 *   panicif(x == 1, "x is 1");
 */
#define panicif(Condition, Msg) __panicif(Condition, Msg, __FILE__, __LINE__)

/**
 * Panic and abort if a condition is true, only in debug builds.
 * @name panicdbg
 * @param {int} Condition - The condition to check
 * @param {const char[]} Msg - The message to print on panic
 * @example
 *   int y = 0;
 *   panicdbg(y == 0, "y is 0, only panics in debug");
 */
#if defined(DEBUG) || !defined(NDEBUG)
#define panicdbg(Condition, Msg) panicif(Condition, Msg)
#else
#define panicdbg(Condition, Msg)
#endif
