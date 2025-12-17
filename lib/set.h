// set (v0.0.1)
// ---
//
// A simple hashset with owned keys. It handles conflicts through linear
// probing and has static size.
//
// ```c
// set_t* set = setCreate(10);
//
// setAdd(set, "key"); // returns result
//
// setHas(set, "key"); // returns true
// setHas(set, "another key"); // returns false
//
// setDelete(set, "key");
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

/**
 * Create a new set with the specified size.
 * @name setCreate
 * @param {set_size_t} size - The maximum number of entries the set can hold
 * @returns {set_t*} Pointer to the newly created set, or NULL on failure
 * @example
 *   set_t* set = setCreate(10);
 */
set_t *setCreate(set_size_t size);

/**
 * Add a key to the set. The key is copied and owned by the set.
 * @name setAdd
 * @param {set_t*} self - Pointer to the set
 * @param {const_set_key_t} key - The key to add
 * @returns {set_result_t} SET_RESULT_OK on success, SET_ERROR_FULL if full
 * @example
 *   setAdd(set, "key");
 */
set_result_t setAdd(set_t *self, const_set_key_t key);

/**
 * Check if a key exists in the set.
 * @name setHas
 * @param {const set_t*} self - Pointer to the set
 * @param {const_set_key_t} key - The key to look up
 * @returns {int} 1 if the key exists, 0 otherwise
 * @example
 *   if (setHas(set, "key")) {
 *     // key exists
 *   }
 */
int setHas(const set_t *self, const_set_key_t key);

/**
 * Delete a key from the set.
 * @name setDelete
 * @param {set_t*} self - Pointer to the set
 * @param {const_set_key_t} key - The key to delete
 * @example
 *   setDelete(set, "key");
 */
void setDelete(set_t *self, const_set_key_t key);

/**
 * Get the number of keys currently stored in the set.
 * @name setUsed
 * @param {const set_t*} self - Pointer to the set
 * @returns {set_size_t} The number of keys in the set
 * @example
 *   set_size_t count = setUsed(set);
 */
set_size_t setUsed(const set_t *self);

/**
 * Destroy the set and free all allocated memory.
 * @name setDestroy
 * @param {set_t**} self - Pointer to the set pointer (will be set to NULL)
 * @example
 *   setDestroy(&set);
 */
void setDestroy(set_t **self);
