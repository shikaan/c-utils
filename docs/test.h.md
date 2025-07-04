Test (v0.0.1)
---

## Getting Started

Compile the test executable returning `test__report()` to get the number of
failed tests as the status code.

```c
// example.test.c
#include "example.h"
#include "../test/test.h"

void testExample() {
  test__expectTrue(example(), "returns true");
}

int main(void) {
  test__suite(testExample);
  return test__report();
}
```

## Custom assertions

```c
// my_struct.test.c
#include "my_struct.h" // myStruct_eql, myStruct_toString
#include "../test/test.h"

void expectEqlMyStruct(const MyStruct* a, const MyStruct* b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %s to equal %s", myStruct_toString(a), myStruct_toString(b));
  test__expect(myStruct_eql(a, b), name, msg);
}

// define main as above
```

## API Docs

### expect

Asserts a condition and prints the result. Use it to immplement custom assertions.

```c
int a = 1;
test__expect(a == 1, "a is one", "Should be true");
```


### expectTrue

Asserts that a condition is true.

```c
test__expectTrue(2 > 1, "2 is greater than 1");
```


### expectFalse

Asserts that a condition is false.

```c
test__expectFalse(0, "zero is false");
```


### expectNotNull

Asserts that a pointer is not NULL.

```c
int x = 5;
test__expectNotNull(&x, "pointer is not null");
```


### expectNull

Asserts that a pointer is NULL.

```c
int* p = NULL;
test__expectNull(p, "pointer is null");
```


### expectEqlInt

Asserts that two integers are equal.

```c
test__expectEqlInt(3, 3, "3 equals 3");
```


### expectNeqInt

Asserts that two integers are not equal.

```c
test__expectNeqInt(3, 4, "3 does not equal 4");
```


### expectEqlFloat

Asserts that two floats are equal within a threshold.

```c
test__expectEqlFloat(1.0f, 1.0f, "floats are equal");
```


### expectNeqFloat

Asserts that two floats are not equal within a threshold.

```c
test__expectNeqFloat(1.0f, 2.0f, "floats are not equal");
```


### expectEqlDouble

Asserts that two doubles are equal within a threshold.

```c
test__expectEqlDouble(1.0, 1.0, "doubles are equal");
```


### expectNeqDouble

Asserts that two doubles are not equal within a threshold.

```c
test__expectNeqDouble(1.0, 2.0, "doubles are not equal");
```


### expectEqlString

Asserts that two strings are equal up to max_size.

```c
test__expectEqlString("foo", "foo", 3, "strings are equal");
```


### expectNeqString

Asserts that two strings are not equal up to max_size.

```c
test__expectNeqString("foo", "bar", 3, "strings are not equal");
```


### report

Prints a summary of test results and returns the number of failed tests.

```c
return test__report();
```


### report

Prints the name of a test case.

```c
test__case("my test");
```


### suite

Runs a test suite and prints its name.

```c
test__suite(myTestFunction);
```


