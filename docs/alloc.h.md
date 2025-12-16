Alloc (v0.1.0)
---

Functions and macros for safer memory management.

```c
void* result = allocate(100);

allocate(100); // gives a compiler warning if not checked

deallocate(&result);
```

## API Docs

### allocate

Allocate zero-ed memory and force caller to check on the result.

```c
void* result = allocate(100);
```


### reallocate

Reallocate memory and force caller to check on the result.

```c
void* result = allocate(100);
result = reallocate(&result, 200);
```


### deallocate

Safely deallocate memory and set pointer to NULL.

```c
char *ptr = allocate(100);
deallocate(&ptr);  // ptr is now NULL
```


