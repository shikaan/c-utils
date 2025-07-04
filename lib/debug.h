// Debug (v0.0.1)
// ---
//
// Convenience functions to easily debug your C code.
//
// ```c
// void function(void) {
//   trace();
//   // rest of the function
// }
// int main(void) {
//   int i = 1;
//   debugi(i);
// }
// ```
// ___HEADER_END___

#ifndef DEBUG_H
#define DEBUG_H

/**
  * Print a debug message with a string value and function name.
  * @name debugs
  * @example
  *   const char[] str = "hello";
  *   debugs(str);  // prints "(nameOfTheFunction) str: hello"
  */
#define debugs(string) printf("(%s) %s: %s\n", __func__, #string, string)

/**
  * Print a debug message with an integer value and function name.
  * @name debugi
  * @example
  *   int i = 42;
  *   debugi(i);  // prints "(nameOfTheFunction) i: 42"
  */
#define debugi(num) printf("(%s) %s: %d\n", __func__, #num, num)

/**
  * Print a debug message with a float value and function name.
  * @name debugf
  * @example
  *   float f = 3.14f;
  *   debugf(f);  // prints "(nameOfTheFunction) f: 3.14"
  */
#define debugf(num) printf("(%s) %s: %f\n", __func__, #num, num)

/**
  * Print a debug message with an unsigned integer value and function name.
  * @name debugu
  * @example
  *   size_t u = 123u;
  *   debugu(u);  // prints "(nameOfTheFunction) u: 123"
  */
#define debugu(num) printf("(%s) %s: %zu\n", __func__, #num, num)

/**
  * Print the function name (trace call).
  * @name trace
  * @example
  *   trace();  // prints "nameOfTheFunction()"
  */
#define trace() printf("%s()\n", __func__)

#endif //DEBUG_H
