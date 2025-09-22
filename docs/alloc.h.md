Alloc (v0.0.1)
---

Functions and macros for safer memory management.

```c
void* result = allocSafe(100);

allocSafe(100); // gives a compiler warning if not checked

deallocSafe(&result);
```

## API Docs

### allocSafe

Allocate memory and force caller to check on the result.

```c
void* result = allocSafe(100);
```


### reallocSafe

Reallocate memory and force caller to check on the result.

```c
void* result = allocSafe(100);
result = reallocSafe(&result, 200);
```


### deallocSafe

Safely deallocate memory and set pointer to nullptr.

```c
char *ptr = allocSafe(100);
deallocSafe(&ptr);  // ptr is now nullptr
```


