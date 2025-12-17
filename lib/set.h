// set (v0.0.1)
// ---
//
// A simple hashset with owned keys. It handles conflicts through linear
// probing and has static size.
//
// ```c
// set_t* set = setCreate(10);
//
// setAdd("key"); // returns result
//
// setHas("key"); // returns true
// setHas("another key"); // returns false
//
// setDelete("key");
//
// setDestroy(&set);
// ```
// ___HEADER_END___

#pragma once

#include <stdint.h>

typedef char *set_key_t;
typedef const char *const_set_key_t;
typedef uint64_t set_size_t;

typedef enum {
  SET_RESULT_OK = 0,
  SET_ERROR_FULL,
  SET_ERROR_NOT_FOUND
} set_result_t;

typedef struct {
  set_size_t size;
  set_key_t *keys;
} set_t;

set_t *setCreate(set_size_t size);
set_result_t setAdd(set_t *self, const_set_key_t key);
int setHas(const set_t *self, const_set_key_t key);
void setDelete(set_t *self, const_set_key_t key);
set_size_t setUsed(const set_t *self);
void setDestroy(set_t **self);
