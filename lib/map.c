#include "map.h"
#include "alloc.h"
#include "panic.h"
#include <string.h>

static char MAP_TOMBSTONE[] = "___TOMBSTONE!!@@##";

static map_size_t mapMakeKey(const map_t *self, const_map_key_t key) {
  uint64_t hash = 14695981039346656037U;
  const uint64_t prime = 1099511628211U;

  for (size_t i = 0; i < strlen(key); i++) {
    hash ^= (uint64_t)(unsigned char)key[i];
    hash *= prime;
  }

  return hash % self->size;
}

static map_result_t mapGetIndex(const map_t *self, const_map_key_t key,
                                map_size_t *result) {
  panicif(!self, "map cannot be null");
  const map_size_t index = mapMakeKey(self, key);

  for (map_size_t i = 0; i < self->size; i++) {
    map_size_t probed_idx = (index + i) % self->size;
    const map_key_t probed_key = self->keys[probed_idx];

    if (!probed_key) {
      return MAP_ERROR_NOT_FOUND;
    }

    // Not a mistake! Tombstones are pointers to the constant string
    if (probed_key == MAP_TOMBSTONE) {
      continue;
    }

    if (strcmp(probed_key, key) == 0) {
      *result = probed_idx;
      return MAP_RESULT_OK;
    }
  }

  return MAP_ERROR_NOT_FOUND;
}

map_t *mapCreate(map_size_t size) {
  panicif(size == 0, "size cannot be zero");

  map_t *self = (map_t *)allocate(sizeof(map_t));
  if (!self)
    return NULL;

  self->keys = (map_key_t *)allocate(sizeof(const char *) * size);
  if (!self->keys) {
    deallocate(&self);
    return NULL;
  }

  self->values = (value_t *)allocate(sizeof(void *) * size);
  if (!self->values) {
    deallocate(&self->keys);
    deallocate(&self);
    return NULL;
  }

  self->size = size;

  return self;
}

map_result_t mapSet(map_t *self, const_map_key_t key, value_t value) {
  panicif(!self, "map cannot be null");
  map_size_t index = mapMakeKey(self, key);
  map_key_t old_key = self->keys[index];
  int collides_with_old_key =
      !!old_key && strcmp(key, old_key) != 0 && old_key != MAP_TOMBSTONE;

  // When there is a collision with another key, look for the next free index
  if (collides_with_old_key) {
    uint8_t i;

    for (i = 1; i < self->size; i++) {
      map_size_t probed_idx = (index + i) % self->size;
      const map_key_t probed_key = self->keys[probed_idx];

      // We write on the index when:
      //  - probed_key is null -> the key was not touched
      //  - probed_key is MAP_TOMBSTONE -> the key was written and then deleted
      //  - probed_key equals key -> we are overriding an existing key
      const int should_write_on_index = !probed_key ||
                                        probed_key == MAP_TOMBSTONE ||
                                        (!strcmp(probed_key, key));

      if (should_write_on_index) {
        index = probed_idx;
        goto set;
      }
    }

    if (i == self->size) {
      return MAP_ERROR_FULL;
    }
  }

set:
  if (self->keys[index] && self->keys[index] != MAP_TOMBSTONE) {
    deallocate(&self->keys[index]);
  }
  self->values[index] = value;
  return MAP_RESULT_OK;
}

value_t mapGet(const map_t *self, const_map_key_t key) {
  panicif(!self, "map cannot be null");
  map_size_t index;
  if (mapGetIndex(self, key, &index) == MAP_RESULT_OK) {
    return self->values[index];
  }
  return NULL;
}

value_t mapDelete(map_t *self, const_map_key_t key) {
  panicif(!self, "map cannot be null");
  map_size_t index;
  if (mapGetIndex(self, key, &index) == MAP_RESULT_OK) {
    value_t previous = self->values[index];
    self->values[index] = NULL;

    map_key_t old_key = self->keys[index];
    deallocate(&old_key);

    self->keys[index] = MAP_TOMBSTONE;
    return previous;
  }
  return NULL;
}

void mapDestroy(map_t **self) {
  if (!self || !*self)
    return;

  for (size_t i = 0; i < (*self)->size; i++) {
    if ((*self)->keys[i] != MAP_TOMBSTONE) {
      deallocate(&(*self)->keys[i]);
    }
  }

  deallocate(&(*self)->keys);
  deallocate(&(*self)->values);
  deallocate(self);
}

#ifdef MAP_C_TEST

#include "test.h"

void getSet(void) {
  map_t *map = mapCreate(5);
  map_result_t result;

  int value = 189, another_value = 185;
  result = mapSet(map, "key", &value);
  panicif(result != MAP_RESULT_OK, "set failed");

  int *resolved = mapGet(map, "key");
  expectEqli(value, *resolved, "retrieves the value");

  value = 2034;
  result = mapSet(map, "key", &value);
  panicif(result != MAP_RESULT_OK, "set failed");
  expectEqli(value, *resolved, "overrides the value");

  resolved = mapGet(map, "another");
  expectNull(resolved, "returns NULL if value is missing");

  result = mapSet(map, "key1", &value);
  result = mapSet(map, "key2", &value);
  result = mapSet(map, "key3", &value);
  result = mapSet(map, "key4", &value);
  result = mapSet(map, "key5", &value);
  expectEqlu(result, MAP_ERROR_FULL, "does not insert with full map");
  result = mapSet(map, "key4", &value);
  expectEqlu(result, MAP_RESULT_OK, "allows updates with full map");

  resolved = mapGet(map, "key1");
  panicif(!resolved, "resolve set value");
  resolved = mapDelete(map, "key1");
  expectEqli(value, *resolved, "returns deleted value");

  resolved = mapGet(map, "key1");
  expectNull(resolved, "does not resolve deleted value");

  result = mapSet(map, "key1", &another_value);
  expectEqlu(result, MAP_RESULT_OK, "deleted value can be reset");
  resolved = mapGet(map, "key1");
  expectEqli(*resolved, another_value,
             "returns correct value set after delete");
  mapDestroy(&map);
}

void collisions(void) {
  map_t *map = mapCreate(5);
  map_result_t result;

  int value1 = 145;
  int value2 = 545;

  // These two strings are known to clash in FNV-1
  const char *key1 = "liquid";
  const char *key2 = "costarring";

  result = mapSet(map, key1, &value1);
  panicif(result != MAP_RESULT_OK, "set failed");

  result = mapSet(map, key2, &value2);
  panicif(result != MAP_RESULT_OK, "set failed");

  int *resolved1 = mapGet(map, key1);
  int *resolved2 = mapGet(map, key2);
  expectNeqi(*resolved1, *resolved2, "values don't overlap");
  expectEqli(*resolved1, value1, "retrieves correct value");
  expectEqli(*resolved2, value2, "retrieves correct other value");

  map_t *map2 = mapCreate(1);

  // setting with key1 and trying to retrieve with colliding key2
  result = mapSet(map2, key1, &value1);
  panicif(result != MAP_RESULT_OK, "set failed");

  expectNull(mapGet(map2, key2), "doesn't return item from colliding key");

  map_t *map3 = mapCreate(5);
  (void)mapSet(map3, key1, &value1);
  (void)mapSet(map3, key2, &value1);
  (void)mapSet(map3, key2, &value2);

  int *resolved3 = mapGet(map3, key2);
  expectEqli(value2, *resolved3,
             "correct value when updating linearly-probed key");

  map_t *map4 = mapCreate(2);
  (void)mapSet(map4, key1, &value1);
  (void)mapSet(map4, key2, &value2);

  mapDelete(map, key1);

  int *resolved = mapGet(map, key2);
  panicif(!resolved, "did not find the colliding key");
  expectEqli(*resolved, value2, "correct value on removing colliding key");

  map_t *map5 = mapCreate(2);
  int v1 = 11, v2 = 22;
  (void)mapSet(map5, key1, &v1);
  (void)mapSet(map5, key2, &v2);
  (void)mapDelete(map5, key1);
  int *p = mapGet(map5, key2);
  panicif(!p, "tail of chain retrievable after deleting head");
  expectEqli(*p, v2, "tail value intact");

  mapDestroy(&map5);
  mapDestroy(&map4);
  mapDestroy(&map3);
  mapDestroy(&map2);
  mapDestroy(&map);
}

int main(void) {
  suite(getSet);
  suite(collisions);

  return report();
}
#endif
