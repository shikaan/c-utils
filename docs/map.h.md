Map (v0.0.1)
---

A simple hashmap with owned keys and non-owned values. It handles conflicts
through linear probing and has static size.

```c
map_t* map = mapCreate(10);

my_type_t value;
mapSet("key", &value);

my_type_t *resolved;
resolved = mapGet("key");

my_type_t *deleted;
deleted = mapDelete("key");
myTypeDestroy(deleted);    // values are owned by the caller

mapDestroy(&map);
```

## API Docs

### mapCreate

Create a new map with the specified size.

```c
map_t* map = mapCreate(10);
```


### mapSet

Set a key-value pair in the map. The key is copied and owned by the map.

```c
my_type_t value;
mapSet(map, "key", &value);
```


### mapGet

Get a value from the map by its key.

```c
my_type_t* result = mapGet(map, "key");
```


### mapDelete

Delete a key-value pair from the map and return the value.

```c
my_type_t* deleted = mapDelete(map, "key");
myTypeDestroy(deleted);
```


### mapDestroy

Destroy the map and free all allocated memory.

```c
mapDestroy(&map);
```


