Panic (v0.0.1)
---

Functions and macros to deal with unrecoverable errors.

```c
panicif(1 == 1, "one is one"); // panics

panic("this will panic");
```

## API Docs

### panic

Unconditionally panic and abort.

```c
panic("unrecoverable error");
```


### panicif

Panic and abort if a condition is true.

```c
int x = 1;
panicif(x == 1, "x is 1");
```


### panicdbg

Panic and abort if a condition is true, only in debug builds.

```c
int y = 0;
panicdbg(y == 0, "y is 0, only panics in debug");
```


