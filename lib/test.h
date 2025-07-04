// Test (v0.0.1)
// ---
//
// ## Getting Started
//
// Compile the test executable returning `test__report()` to get the number of
// failed tests as the status code.
//
// ```c
// // example.test.c
// #include "example.h"
// #include "../test/test.h"
//
// void testExample() {
//   test__expectTrue(example(), "returns true");
// }
//
// int main(void) {
//   test__suite(testExample);
//   return test__report();
// }
// ```
//
// ## Custom assertions
//
// ```c
// // my_struct.test.c
// #include "my_struct.h" // myStruct_eql, myStruct_toString
// #include "../test/test.h"
//
// void expectEqlMyStruct(const MyStruct* a, const MyStruct* b, const char* name) {
//   char msg[256];
//   snprintf(msg, 256, "Expected %s to equal %s", myStruct_toString(a), myStruct_toString(b));
//   test__expect(myStruct_eql(a, b), name, msg);
// }
//
// // define main as above
// ```

#ifndef TEST_H
#define TEST_H

#include <stdio.h>  // printf, snprintf
#include <math.h>   // fabs
#include <string.h> // strncmp

#define FLOAT_THRESHOOLD 1e-6f
#define DOUBLE_THRESHOOLD 1e-6f

static int total = 0;
static int failed = 0;

/**
  * Asserts a condition and prints the result. Use it to immplement custom assertions.
  * @name expect
  * @example
  *   int a = 1;
  *   test__expect(a == 1, "a is one", "Should be true");
  */
void test__expect(bool condition, const char* name, const char* message) {
  total++;
  if (!condition) {
    failed++;
    printf("  fail - %s: %s\n", name, message);
    return;
  }
  printf("   ok  - %s\n", name);
}

/**
  * Asserts that a condition is true.
  * @name expectTrue
  * @example
  *   test__expectTrue(2 > 1, "2 is greater than 1");
  */
void test__expectTrue(bool condition, const char* name) {
  test__expect(condition, name, "Expected value to be true");
}

/**
  * Asserts that a condition is false.
  * @name expectFalse
  * @example
  *   test__expectFalse(0, "zero is false");
  */
void test__expectFalse(bool condition, const char* name) {
  test__expect(!condition, name, "Expected value to be false");
}

/**
  * Asserts that a pointer is not NULL.
  * @name expectNotNull
  * @example
  *   int x = 5;
  *   test__expectNotNull(&x, "pointer is not null");
  */
void test__expectNotNull(const void* a, const char* name) {
  test__expect(a != NULL, name, "Expected value not to be null");
}

/**
  * Asserts that a pointer is NULL.
  * @name expectNull
  * @example
  *   int* p = NULL;
  *   test__expectNull(p, "pointer is null");
  */
void test__expectNull(const void* a, const char* name) {
  test__expect(a == NULL, name, "Expected value to be null");
}

/**
  * Asserts that two integers are equal.
  * @name expectEqlInt
  * @example
  *   test__expectEqlInt(3, 3, "3 equals 3");
  */
void test__expectEqlInt(const int a, const int b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d to equal %d", a, b);
  test__expect(a == b, name, msg);
}

/**
  * Asserts that two integers are not equal.
  * @name expectNeqInt
  * @example
  *   test__expectNeqInt(3, 4, "3 does not equal 4");
  */
void test__expectNeqInt(const int a, const int b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d not to equal %d", a, b);
  test__expect(a != b, name, msg);
}

/**
  * Asserts that two floats are equal within a threshold.
  * @name expectEqlFloat
  * @example
  *   test__expectEqlFloat(1.0f, 1.0f, "floats are equal");
  */
void test__expectEqlFloat(const float a, const float b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f to equal %f", a, b);
  test__expect(fabsf(a - b) < FLOAT_THRESHOOLD, name, msg);
}

/**
  * Asserts that two floats are not equal within a threshold.
  * @name expectNeqFloat
  * @example
  *   test__expectNeqFloat(1.0f, 2.0f, "floats are not equal");
  */
void test__expectNeqFloat(const float a, const float b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f not to equal %f", a, b);
  test__expect(fabsf(a - b) >= FLOAT_THRESHOOLD, name, msg);
}

/**
  * Asserts that two doubles are equal within a threshold.
  * @name expectEqlDouble
  * @example
  *   test__expectEqlDouble(1.0, 1.0, "doubles are equal");
  */
void test__expectEqlDouble(const double a, const double b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f to equal %f", a, b);
  test__expect(fabs(a - b) < DOUBLE_THRESHOOLD, name, msg);
}

/**
  * Asserts that two doubles are not equal within a threshold.
  * @name expectNeqDouble
  * @example
  *   test__expectNeqDouble(1.0, 2.0, "doubles are not equal");
  */
void test__expectNeqDouble(const double a, const double b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f not to equal %f", a, b);
  test__expect(fabs(a - b) >= DOUBLE_THRESHOOLD, name, msg);
}

/**
  * Asserts that two strings are equal up to max_size.
  * @name expectEqlString
  * @example
  *   test__expectEqlString("foo", "foo", 3, "strings are equal");
  */
void test__expectEqlString(const char* a, const char* b, size_t max_size, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' to equal '%s'", a, b);
  test__expect(strncmp(a, b, max_size) == 0, name, msg);
}

/**
  * Asserts that two strings are not equal up to max_size.
  * @name expectNeqString
  * @example
  *   test__expectNeqString("foo", "bar", 3, "strings are not equal");
  */
void test__expectNeqString(const char* a, const char* b, size_t max_size, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' not to equal '%s'", a, b);
  test__expect(strncmp(a, b, max_size) != 0, name, msg);
}

/**
  * Prints a summary of test results and returns the number of failed tests.
  * @name report
  * @example
  *   return test__report();
  */
int test__report(void) {
  printf("\n%d assertions, %d failed\n", total, failed);
  return failed;
}

/**
  * Prints the name of a test case.
  * @name report
  * @example
  *    test__case("my test");
  */
#define test__case(name) printf("  %s:\n", name)

/**
  * Runs a test suite and prints its name.
  * @name suite
  * @example
  *    test__suite(myTestFunction);
  */
#define test__suite(name) {\
  printf("\n> %s\n", #name);\
  name();\
}

#endif //TEST_H
