Test (v1.0.0)
---

## Getting Started

Compile the test executable returning `report()` to get the number of
failed tests as the status code.

Define FAILED_ONLY to see only failures.

```c
// example.test.c
#include "example.h"
#include "../test/test.h"

void testExample() {
  expectTrue(example(), "returns true");
}

int main(void) {
  suite(testExample);
  return report();
}
```

## Custom assertions

```c
// my_struct.test.c
#include "my_struct.h" // myStruct_eql, myStruct_toString
#include "../test/test.h"

void expectEqlMyType(const MyType* a, const MyType* b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %s to equal %s", myStruct_toString(a),
  myStruct_toString(b));
  expect(myStruct_eql(a, b), name, msg);
}

// define main as above
```

## API Docs

### expect

Asserts a condition and prints the result. Use it to implement custom assertions.

```c
int a = 1;
expect(a == 1, "a is one", "Should be true");
```


### expectTrue

Asserts that a condition is true.

```c
expectTrue(2 > 1, "2 is greater than 1");
```


### expectFalse

Asserts that a condition is false.

```c
expectFalse(0, "zero is false");
```


### expectNotNull

Asserts that a pointer is not NULL.

```c
int x = 5;
expectNotNull(&x, "pointer is not null");
```


### expectNull

Asserts that a pointer is NULL.

```c
int* p = NULL;
expectNull(p, "pointer is null");
```


### expectEqli

Asserts that two integers are equal.

```c
expectEqli(3, 3, "3 equals 3");
```


### expectNeqi

Asserts that two integers are not equal.

```c
expectNeqi(3, 4, "3 does not equal 4");
```


### expectEqlu

Asserts that two unsigned integers are equal.

```c
expectEqlu(3, 3, "3 equals 3");
```


### expectNeqlu

Asserts that two unsigned integers are not equal.

```c
expectNeqlu(3, 4, "3 does not equal 4");
```


### expectEqllu

Asserts that two unsigned long integers are equal.

```c
expectEqllu(3, 3, "3 equals 3");
```


### expectNeqllu

Asserts that two unsigned long integers are equal.

```c
expectNeqllu(3, 4, "3 does not equal 4");
```


### expectEqlf

Asserts that two floats are equal within a threshold.

```c
expectEqlf(1.0f, 1.0f, "floats are equal");
```


### expectNeqf

Asserts that two floats are not equal within a threshold.

```c
expectNeqf(1.0f, 2.0f, "floats are not equal");
```


### expectEqld

Asserts that two doubles are equal within a threshold.

```c
expectEqld(1.0, 1.0, "doubles are equal");
```


### expectNeqd

Asserts that two doubles are not equal within a threshold.

```c
expectNeqd(1.0, 2.0, "doubles are not equal");
```


### expectEqls

Asserts that two strings are equal up to max_size.

```c
expectEqls("foo", "foo", 3, "strings are equal");
```


### expectNeqs

Asserts that two strings are not equal up to max_size.

```c
expectNeqs("foo", "bar", 3, "strings are not equal");
```


### expectIncls

Asserts that first string includes the second.

```c
expectIncls("foobar", "bar", "strings are included");
```


### report

Prints a summary of test results and returns the number of failed tests.

```c
return report();
```


### test

Prints the name of a test case.

```c
test("my test");
```


### suite

Runs a test suite and prints its name.

```c
suite(myTestFunction);
```


