Debug (v0.0.1)
---

Convenience functions to easily debug your C code.

```c
void function(void) {
  trace();
  // rest of the function
}
int main(void) {
  int i = 1;
  debugi(i);
}
```

## API Docs

### debugs

Print a debug message with a string value and function name.

```c
const char[] str = "hello";
debugs(str);  // prints "(nameOfTheFunction) str: hello"
```


### debugi

Print a debug message with an integer value and function name.

```c
int i = 42;
debugi(i);  // prints "(nameOfTheFunction) i: 42"
```


### debugf

Print a debug message with a float value and function name.

```c
float f = 3.14f;
debugf(f);  // prints "(nameOfTheFunction) f: 3.14"
```


### debugu

Print a debug message with an unsigned integer value and function name.

```c
size_t u = 123u;
debugu(u);  // prints "(nameOfTheFunction) u: 123"
```


### trace

Print the function name (trace call).

```c
trace();  // prints "nameOfTheFunction()"
```


