set (v0.0.1)
---

A simple hashset with owned keys. It handles conflicts through linear
probing and has static size.

```c
set_t* set = setCreate(10);

setAdd("key"); // returns result

setHas("key"); // returns true
setHas("another key"); // returns false

setDelete("key");

setDestroy(&set);
```
