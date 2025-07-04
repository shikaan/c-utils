// Test
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
void test__expect(bool condition, const char* name, const char* message) {
  total++;
  if (!condition) {
    failed++;
    printf("  fail - %s: %s\n", name, message);
    return;
  }
  printf("   ok  - %s\n", name);
}

void test__expectTrue(bool condition, const char* name) {
  test__expect(condition, name, "Expected value to be true");
}

void test__expectFalse(bool condition, const char* name) {
  test__expect(!condition, name, "Expected value to be false");
}

void test__expectNotNull(const void* a, const char* name) {
  test__expect(a != NULL, name, "Expected value not to be null");
}

void test__expectNull(const void* a, const char* name) {
  test__expect(a == NULL, name, "Expected value to be null");
}

void test__expectEqlInt(const int a, const int b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d to equal %d", a, b);
  test__expect(a == b, name, msg);
}

void test__expectNeqInt(const int a, const int b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d not to equal %d", a, b);
  test__expect(a != b, name, msg);
}

void test__expectEqlFloat(const float a, const float b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f to equal %f", a, b);
  test__expect(fabsf(a - b) < FLOAT_THRESHOOLD, name, msg);
}

void test__expectNeqFloat(const float a, const float b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f not to equal %f", a, b);
  test__expect(fabsf(a - b) >= FLOAT_THRESHOOLD, name, msg);
}

void test__expectEqlDouble(const double a, const double b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f to equal %f", a, b);
  test__expect(fabs(a - b) < DOUBLE_THRESHOOLD, name, msg);
}

void test__expectNeqDouble(const double a, const double b, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected %f not to equal %f", a, b);
  test__expect(fabs(a - b) >= DOUBLE_THRESHOOLD, name, msg);
}

void test__expectEqlString(const char* a, const char* b, size_t max_size, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' to equal '%s'", a, b);
  test__expect(strncmp(a, b, max_size) == 0, name, msg);
}

void test__expectNeqString(const char* a, const char* b, size_t max_size, const char* name) {
  char msg[256];
  snprintf(msg, 256, "Expected '%s' not to equal '%s'", a, b);
  test__expect(strncmp(a, b, max_size) != 0, name, msg);
}

int test__report(void) {
  printf("\n%d assertions, %d failed\n", total, failed);
  return failed;
}

#define test__case(name) printf("  %s:\n", name)

#define test__suite(name) {\
  printf("\n> %s\n", #name);\
  name();\
}

#endif //TEST_H
