// Test (v0.1.0)
// ---
//
// ## Getting Started
//
// Compile the test executable returning `report()` to get the number of
// failed tests as the status code.
//
// Define FAILED_ONLY to see only failures.
//
// ```c
// // example.test.c
// #include "example.h"
// #include "../test/test.h"
//
// void testExample() {
//   expectTrue(example(), "returns true");
// }
//
// int main(void) {
//   suite(testExample);
//   return report();
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
// void expectEqlMyType(const MyType* a, const MyType* b, const char* name) {
//   char msg[256];
//   snprintf(msg, 256, "Expected %s to equal %s", myStruct_toString(a),
//   myStruct_toString(b));
//   expect(myStruct_eql(a, b), name, msg);
// }
//
// // define main as above
// ```
// ___HEADER_END___

#pragma once

#include <math.h>   // fabs
#include <stdio.h>  // printf, snprintf
#include <string.h> // strncmp

#define FLOAT_THRESHOOLD 1e-6f
#define DOUBLE_THRESHOOLD 1e-6f

static int total = 0;
static int failed = 0;

/**
 * Asserts a condition and prints the result. Use it to implement custom
 * assertions.
 * @name expect
 * @example
 *   int a = 1;
 *   expect(a == 1, "a is one", "Should be true");
 */
void expect(bool condition, const char *name, const char *message) {
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
 *   expectTrue(2 > 1, "2 is greater than 1");
 */
void expectTrue(bool condition, const char *name) {
  expect(condition, name, "Expected value to be true");
}

/**
 * Asserts that a condition is false.
 * @name expectFalse
 * @example
 *   expectFalse(0, "zero is false");
 */
void expectFalse(bool condition, const char *name) {
  expect(!condition, name, "Expected value to be false");
}

/**
 * Asserts that a pointer is not NULL.
 * @name expectNotNull
 * @example
 *   int x = 5;
 *   expectNotNull(&x, "pointer is not null");
 */
void expectNotNull(const void *a, const char *name) {
  expect(a != NULL, name, "Expected value not to be null");
}

/**
 * Asserts that a pointer is NULL.
 * @name expectNull
 * @example
 *   int* p = NULL;
 *   expectNull(p, "pointer is null");
 */
void expectNull(const void *a, const char *name) {
  expect(a == NULL, name, "Expected value to be null");
}

/**
 * Asserts that two integers are equal.
 * @name expectEqli
 * @example
 *   expectEqli(3, 3, "3 equals 3");
 */
void expectEqli(const int a, const int b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d to equal %d", a, b);
  expect(a == b, name, msg);
}

/**
 * Asserts that two integers are not equal.
 * @name expectNeqi
 * @example
 *   expectNeqi(3, 4, "3 does not equal 4");
 */
void expectNeqi(const int a, const int b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d not to equal %d", a, b);
  expect(a != b, name, msg);
}

/**
 * Asserts that two unsigned integers are equal.
 * @name expectEqlu
 * @example
 *   expectEqlu(3, 3, "3 equals 3");
 */
void expectEqlu(const unsigned int a, const unsigned int b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %u to equal %u", a, b);
  expect(a == b, name, msg);
}

/**
 * Asserts that two unsigned integers are not equal.
 * @name expectNeqlu
 * @example
 *   expectNeqlu(3, 4, "3 does not equal 4");
 */
void expectNeqlu(const unsigned int a, const unsigned int b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %u not to equal %u", a, b);
  expect(a != b, name, msg);
}

/**
 * Asserts that two unsigned long integers are equal.
 * @name expectEqllu
 * @example
 *   expectEqllu(3, 3, "3 equals 3");
 */
void expectEqllu(const size_t a, const size_t b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %lu to equal %lu", a, b);
  expect(a == b, name, msg);
}

/**
 * Asserts that two unsigned long integers are equal.
 * @name expectNeqllu
 * @example
 *   expectNeqllu(3, 4, "3 does not equal 4");
 */
void expectNeqllu(const size_t a, const size_t b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %lu not to equal %lu", a, b);
  expect(a != b, name, msg);
}

/**
 * Asserts that two floats are equal within a threshold.
 * @name expectEqlf
 * @example
 *   expectEqlf(1.0f, 1.0f, "floats are equal");
 */
void expectEqlf(const float a, const float b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f to equal %f", a, b);
  expect(fabsf(a - b) < FLOAT_THRESHOOLD, name, msg);
}

/**
 * Asserts that two floats are not equal within a threshold.
 * @name expectNeqf
 * @example
 *   expectNeqf(1.0f, 2.0f, "floats are not equal");
 */
void expectNeqf(const float a, const float b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f not to equal %f", a, b);
  expect(fabsf(a - b) >= FLOAT_THRESHOOLD, name, msg);
}

/**
 * Asserts that two doubles are equal within a threshold.
 * @name expectEqld
 * @example
 *   expectEqld(1.0, 1.0, "doubles are equal");
 */
void expectEqld(const double a, const double b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f to equal %f", a, b);
  expect(fabs(a - b) < DOUBLE_THRESHOOLD, name, msg);
}

/**
 * Asserts that two doubles are not equal within a threshold.
 * @name expectNeqd
 * @example
 *   expectNeqd(1.0, 2.0, "doubles are not equal");
 */
void expectNeqd(const double a, const double b, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f not to equal %f", a, b);
  expect(fabs(a - b) >= DOUBLE_THRESHOOLD, name, msg);
}

/**
 * Asserts that two strings are equal up to max_size.
 * @name expectEqls
 * @example
 *   expectEqls("foo", "foo", 3, "strings are equal");
 */
void expectEqls(const char *a, const char *b, size_t max_size,
                const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' to equal '%s'", a, b);
  expect(strncmp(a, b, max_size) == 0, name, msg);
}

/**
 * Asserts that two strings are not equal up to max_size.
 * @name expectNeqs
 * @example
 *   expectNeqs("foo", "bar", 3, "strings are not equal");
 */
void expectNeqs(const char *a, const char *b, size_t max_size,
                const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' not to equal '%s'", a, b);
  expect(strncmp(a, b, max_size) != 0, name, msg);
}

/**
 * Asserts that first string includes the second.
 * @name expectIncls
 * @example
 *   expectIncls("foobar", "bar", "strings are included");
 */
void expectIncls(const char *big, const char *small, const char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' to include '%s'", big, small);
  expect(strstr(big, small) != NULL, name, msg);
}

/**
 * Prints a summary of test results and returns the number of failed tests.
 * @name report
 * @example
 *   return report();
 */
int report(void) {
#ifndef FAILED_ONLY
  printf("\n%d assertions, %d failed\n", total, failed);
#else
  printf("%d assertions, %d failed\n", total, failed);
#endif
  return failed;
}

/**
 * Prints the name of a test case.
 * @name case
 * @example
 *    case("my test");
 */
#ifndef FAILED_ONLY
#define case(name) printf("  %s:\n", name)
#else
#define case(name)
#endif

/**
 * Runs a test suite and prints its name.
 * @name suite
 * @example
 *    suite(myTestFunction);
 */
#ifndef FAILED_ONLY
#define suite(name)                                                            \
  {                                                                            \
    printf("\n> %s\n", #name);                                                 \
    name();                                                                    \
  }
#else
#define suite(name)                                                            \
  {                                                                            \
    name();                                                                    \
  }
#endif