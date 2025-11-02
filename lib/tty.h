// TTY (v0.0.1)
// ---
//
// Macros for styling terminal output with ANSI escape codes.
//
// ```c
// printf(bold("Bold text\n"));
// printf(fg_red("Red text\n"));
// printf(bg_green("Green background\n"));
// printf(underline(fg_blue("Blue underlined\n")));
// ```
// ___HEADER_END___
#pragma once

/**
 * Render text dimmed.
 * @name dim
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(dim("Dim text\n"));
 */
#define dim(ConstString) "\x1b[2m" ConstString "\x1b[0m"

/**
 * Render text bold.
 * @name bold
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bold("Bold text\n"));
 */
#define bold(ConstString) "\x1b[1m" ConstString "\x1b[0m"

/**
 * Render text italic.
 * @name italic
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(italic("Italic text\n"));
 */
#define italic(ConstString) "\x1b[3m" ConstString "\x1b[0m"

/**
 * Render text underlined.
 * @name underline
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(underline("Underlined text\n"));
 */
#define underline(ConstString) "\x1b[4m" ConstString "\x1b[0m"

/**
 * Render text with black foreground.
 * @name fg_black
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_black("Black text\n"));
 */
#define fg_black(ConstString) "\x1b[30m" ConstString "\x1b[0m"

/**
 * Render text with red foreground.
 * @name fg_red
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_red("Red text\n"));
 */
#define fg_red(ConstString) "\x1b[31m" ConstString "\x1b[0m"

/**
 * Render text with green foreground.
 * @name fg_green
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_green("Green text\n"));
 */
#define fg_green(ConstString) "\x1b[32m" ConstString "\x1b[0m"

/**
 * Render text with yellow foreground.
 * @name fg_yellow
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_yellow("Yellow text\n"));
 */
#define fg_yellow(ConstString) "\x1b[33m" ConstString "\x1b[0m"

/**
 * Render text with blue foreground.
 * @name fg_blue
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_blue("Blue text\n"));
 */
#define fg_blue(ConstString) "\x1b[34m" ConstString "\x1b[0m"

/**
 * Render text with magenta foreground.
 * @name fg_magenta
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_magenta("Magenta text\n"));
 */
#define fg_magenta(ConstString) "\x1b[35m" ConstString "\x1b[0m"

/**
 * Render text with cyan foreground.
 * @name fg_cyan
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_cyan("Cyan text\n"));
 */
#define fg_cyan(ConstString) "\x1b[36m" ConstString "\x1b[0m"

/**
 * Render text with white foreground.
 * @name fg_white
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(fg_white("White text\n"));
 */
#define fg_white(ConstString) "\x1b[37m" ConstString "\x1b[0m"

/**
 * Render text with black background.
 * @name bg_black
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_black("Black background\n"));
 */
#define bg_black(ConstString) "\x1b[40m" ConstString "\x1b[0m"

/**
 * Render text with red background.
 * @name bg_red
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_red("Red background\n"));
 */
#define bg_red(ConstString) "\x1b[41m" ConstString "\x1b[0m"

/**
 * Render text with green background.
 * @name bg_green
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_green("Green background\n"));
 */
#define bg_green(ConstString) "\x1b[42m" ConstString "\x1b[0m"

/**
 * Render text with yellow background.
 * @name bg_yellow
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_yellow("Yellow background\n"));
 */
#define bg_yellow(ConstString) "\x1b[43m" ConstString "\x1b[0m"

/**
 * Render text with blue background.
 * @name bg_blue
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_blue("Blue background\n"));
 */
#define bg_blue(ConstString) "\x1b[44m" ConstString "\x1b[0m"

/**
 * Render text with magenta background.
 * @name bg_magenta
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_magenta("Magenta background\n"));
 */
#define bg_magenta(ConstString) "\x1b[45m" ConstString "\x1b[0m"

/**
 * Render text with cyan background.
 * @name bg_cyan
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_cyan("Cyan background\n"));
 */
#define bg_cyan(ConstString) "\x1b[46m" ConstString "\x1b[0m"

/**
 * Render text with white background.
 * @name bg_white
 * @param {const char*} ConstString - The string to style
 * @returns {const char*} Styled string
 * @example
 *   printf(bg_white("White background\n"));
 */
#define bg_white(ConstString) "\x1b[47m" ConstString "\x1b[0m"
