set (v0.0.1)
---

A simple hashset with owned keys. It handles conflicts through linear
probing and has static size.

```c
set_t* set = setCreate(10);

setAdd(set, "key"); // returns result

setHas(set, "key"); // returns true
setHas(set, "another key"); // returns false

setDelete(set, "key");

setDestroy(&set);
```

## API Docs

### setCreate

Create a new set with the specified size.

```c
set_t* set = setCreate(10);
```


### setAdd

Add a key to the set. The key is copied and owned by the set.

```c
setAdd(set, "key");
```


### setHas

Check if a key exists in the set.

```c
if (setHas(set, "key")) {
// key exists
}
```


### setDelete

Delete a key from the set.

```c
setDelete(set, "key");
```


### setUsed

Get the number of keys currently stored in the set.

```c
set_size_t count = setUsed(set);
```


### setDestroy

Destroy the set and free all allocated memory.

```c
setDestroy(&set);
```


