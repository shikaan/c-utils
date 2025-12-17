// strdup (v0.0.1)
// ---
//
// Use strdup in C<23 where it's not available.
//
// ```c
// #include "strdup.h"
//
// char* hello = strdup("hi!");
// ```
// ___HEADER_END___
//
#pragma once

#if !defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200809L
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

inline char *strdup(const char *s) {
  size_t len = strlen(s) + 1;
  char *d = (char *)malloc(len);
  if (d == NULL)
    return NULL;
  memcpy(d, s, len);
  return d;
}
#endif
