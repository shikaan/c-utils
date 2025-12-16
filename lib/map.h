// Map (v0.0.1)
// ---
//
// A simple hashmap with owned keys and non-owned values. It handles conflicts
// through linear probing and has static size.
//
// ```c
// map_t* map = mapCreate(10);
//
// my_type_t value;
// mapSet("key", &value);
//
// my_type_t *resolved;
// resolved = mapGet("key");
//
// my_type_t *deleted;
// deleted = mapDelete("key");
// myTypeDestroy(deleted);    // values are owned by the caller
//
// mapDestroy(&map);
// ```
// ___HEADER_END___

#pragma once

#include <stdint.h>

typedef char *map_key_t;
typedef const char *const_map_key_t;
typedef void *value_t;
typedef uint64_t map_size_t;

typedef enum {
  MAP_RESULT_OK = 0,
  MAP_ERROR_FULL,
  MAP_ERROR_NOT_FOUND
} map_result_t;

typedef struct {
  map_size_t size;
  map_key_t *keys;
  value_t *values;
} map_t;

/**
 * Create a new map with the specified size.
 * @name mapCreate
 * @param {map_size_t} size - The maximum number of entries the map can hold
 * @returns {map_t*} Pointer to the newly created map, or NULL on failure
 * @example
 *   map_t* map = mapCreate(10);
 */
map_t *mapCreate(map_size_t size);

/**
 * Set a key-value pair in the map. The key is copied and owned by the map.
 * @name mapSet
 * @param {map_t*} self - Pointer to the map
 * @param {const_map_key_t} key - The key to set
 * @param {value_t} value - The value to associate with the key
 * @returns {map_result_t} MAP_RESULT_OK on success, MAP_ERROR_FULL if full
 * @example
 *   my_type_t value;
 *   mapSet(map, "key", &value);
 */
map_result_t mapSet(map_t *self, const_map_key_t key, value_t value);

/**
 * Get a value from the map by its key.
 * @name mapGet
 * @param {const map_t*} self - Pointer to the map
 * @param {const_map_key_t} key - The key to look up
 * @returns {value_t} The value associated with the key, or NULL if not found
 * @example
 *   my_type_t* result = mapGet(map, "key");
 */
value_t mapGet(const map_t *self, const_map_key_t key);

/**
 * Delete a key-value pair from the map and return the value.
 * @name mapDelete
 * @param {map_t*} self - Pointer to the map
 * @param {const_map_key_t} key - The key to delete
 * @returns {value_t} The deleted value, or NULL if key was not found
 * @example
 *   my_type_t* deleted = mapDelete(map, "key");
 *   myTypeDestroy(deleted);
 */
value_t mapDelete(map_t *self, const_map_key_t key);

/**
 * Destroy the map and free all allocated memory.
 * @name mapDestroy
 * @param {map_t**} self - Pointer to the map pointer (will be set to NULL)
 * @example
 *   mapDestroy(&map);
 */
void mapDestroy(map_t **self);
