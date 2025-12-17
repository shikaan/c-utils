#include "alloc.h"
#include "panic.h"
#include "strdup.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef char *set_key_t;
typedef const char *const_set_key_t;
typedef uint64_t set_size_t;

static char SET_TOMBSTONE[] = "___TOMBSTONE!!@@##";

typedef enum {
  SET_RESULT_OK = 0,
  SET_ERROR_FULL,
  SET_ERROR_NOT_FOUND
} set_result_t;

typedef struct {
  set_size_t size;
  set_key_t *keys;
} set_t;

static inline set_size_t setMakeKey(const set_t *self, const_set_key_t key) {
  uint64_t hash = 14695981039346656037U;
  const uint64_t prime = 1099511628211U;

  for (size_t i = 0; i < strlen(key); i++) {
    hash ^= (uint64_t)(unsigned char)key[i];
    hash *= prime;
  }

  return hash % self->size;
}

static inline set_result_t setGetIndex(const set_t *self, const_set_key_t key,
                                       set_size_t *result) {
  panicif(!self, "set cannot be null");
  const set_size_t index = setMakeKey(self, key);

  for (set_size_t i = 0; i < self->size; i++) {
    set_size_t probed_idx = (index + i) % self->size;
    const set_key_t probed_key = self->keys[probed_idx];

    if (!probed_key) {
      return SET_ERROR_NOT_FOUND;
    }

    // Not a mistake! Tombstones are pointers to the constant string
    if (probed_key == SET_TOMBSTONE) {
      continue;
    }

    if (strcmp(probed_key, key) == 0) {
      *result = probed_idx;
      return SET_RESULT_OK;
    }
  }

  return SET_ERROR_NOT_FOUND;
}

set_t *setCreate(set_size_t size) {
  panicif(size <= 0, "size cannot be null");
  set_t *self = (set_t *)allocate(sizeof(set_t));
  if (!self)
    return NULL;

  self->keys = (set_key_t *)allocate(sizeof(const char *) * size);
  if (!self->keys) {
    deallocate(&self);
    return NULL;
  }

  self->size = size;

  return self;
}

set_result_t setAdd(set_t *self, const_set_key_t key) {
  panicif(!self, "set cannot be null");
  set_size_t index = setMakeKey(self, key);
  set_key_t old_key = self->keys[index];
  int collides_with_old_key =
      !!old_key && strcmp(key, old_key) != 0 && old_key != SET_TOMBSTONE;

  // When there is a collision with another key, look for the next free index
  if (collides_with_old_key) {
    uint8_t i;

    for (i = 1; i < self->size; i++) {
      set_size_t probed_idx = (index + i) % self->size;
      const set_key_t probed_key = self->keys[probed_idx];

      // We write on the index when:
      //  - probed_key is null -> the key was not touched
      //  - probed_key is SET_TOMBSTONE -> the key was written and then deleted
      const int should_write_on_index =
          !probed_key || probed_key == SET_TOMBSTONE;
      if (should_write_on_index) {
        index = probed_idx;
        goto set;
      }

      // The key is already there just return
      if (!strcmp(probed_key, key)) {
        return SET_RESULT_OK;
      }
    }

    if (i == self->size) {
      return SET_ERROR_FULL;
    }
  }

set:
  if (self->keys[index] && self->keys[index] != SET_TOMBSTONE) {
    deallocate(&self->keys[index]);
  }
  self->keys[index] = strdup(key);
  return SET_RESULT_OK;
}

int setHas(const set_t *self, const_set_key_t key) {
  panicif(!self, "set cannot be null");
  set_size_t index;
  return setGetIndex(self, key, &index) == SET_RESULT_OK;
}

void setDelete(set_t *self, const_set_key_t key) {
  panicif(!self, "set cannot be null");
  set_size_t index;
  if (setGetIndex(self, key, &index) == SET_RESULT_OK) {
    set_key_t old_key = self->keys[index];
    deallocate(&old_key);
    self->keys[index] = SET_TOMBSTONE;
  }
  return;
}

set_size_t setUsed(const set_t *self) {
  set_size_t used = 0;
  for (size_t i = 0; i < self->size; i++) {
    set_key_t key = self->keys[i];
    if (key && key != SET_TOMBSTONE) {
      used++;
    }
  }
  return used;
}

void setDestroy(set_t **self) {
  if (!self || !*self)
    return;

  for (size_t i = 0; i < (*self)->size; i++) {
    if ((*self)->keys[i] != SET_TOMBSTONE) {
      deallocate(&(*self)->keys[i]);
    }
  }

  deallocate(&(*self)->keys);
  deallocate(self);
}

#ifdef SET_C_TEST

#include "test.h"

void addHas(void) {
  set_t *set = setCreate(5);
  set_size_t size = 0;
  panicif(!set, "cannot create set");

  set_result_t res;
  res = setAdd(set, "key");
  size = setUsed(set);
  expectEqlu(res, SET_RESULT_OK, "add returns OK");
  expectEqllu(size, 1, "updates used");
  expectTrue(setHas(set, "key"), "finds inserted key");
  expectFalse(setHas(set, "another"), "returns 0 for missing key");

  test("idempotency");
  res = setAdd(set, "key"); // duplicate
  expectEqlu(res, SET_RESULT_OK, "adds existing");
  expectEqllu(setUsed(set), size, "does not update used");
  expectTrue(setHas(set, "key"), "has finds key");

  test("full set and deletion");
  (void)setAdd(set, "key1");
  (void)setAdd(set, "key2");
  (void)setAdd(set, "key3");
  (void)setAdd(set, "key4");

  res = setAdd(set, "key5");
  expectEqlu(res, SET_ERROR_FULL, "does not insert with full set");

  size = setUsed(set);
  setDelete(set, "key1");
  expectFalse(setHas(set, "key1"), "does not find deleted key");
  expectEqllu(setUsed(set), size - 1, "reduces used");

  res = setAdd(set, "key1");
  expectEqlu(res, SET_RESULT_OK, "adds after deletion");
  expectTrue(setHas(set, "key1"), "finds reset key");

  setDestroy(&set);
}

void collisions(void) {
  set_t *set = setCreate(5);
  panicif(!set, "cannot create set");
  set_result_t res;

  // These two strings are known to clash in FNV-1
  const char *key1 = "liquid";
  const char *key2 = "costarring";

  res = setAdd(set, key1);
  panicif(res != SET_RESULT_OK, "add failed");
  res = setAdd(set, key2);
  panicif(res != SET_RESULT_OK, "add failed");

  expectTrue(setHas(set, key1), "has first colliding key");
  expectTrue(setHas(set, key2), "has second colliding key");

  set_t *set2 = setCreate(1);
  res = setAdd(set2, key1);
  panicif(res != SET_RESULT_OK, "add failed");

  test("full set");
  expectEqlu(setAdd(set2, key2), SET_ERROR_FULL, "does not add colliding");
  expectFalse(setHas(set2, key2), "does not contain colliding key");
  expectEqlu(setAdd(set2, key1), SET_RESULT_OK,
             "allows idempotent add with colliding key");
  expectTrue(setHas(set2, key1), "contains previous colliding key");

  test("chained collisions");
  set_t *set3 = setCreate(2);
  (void)setAdd(set3, key1);
  (void)setAdd(set3, key2);
  setDelete(set3, key1);
  expectTrue(setHas(set3, key2),
             "tail remains retrievable after deleting head");

  setDestroy(&set3);
  setDestroy(&set2);
  setDestroy(&set);
}

int main(void) {
  suite(addHas);
  suite(collisions);

  return report();
}

#endif
