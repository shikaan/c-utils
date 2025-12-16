TTY (v0.0.1)
---

Macros for styling terminal output with ANSI escape codes.

```c
printf(bold("Bold text\n"));
printf(fg_red("Red text\n"));
printf(bg_green("Green background\n"));
printf(underline(fg_blue("Blue underlined\n")));
```

## API Docs

### dim

Render text dimmed.

```c
printf(dim("Dim text\n"));
```


### bold

Render text bold.

```c
printf(bold("Bold text\n"));
```


### italic

Render text italic.

```c
printf(italic("Italic text\n"));
```


### underline

Render text underlined.

```c
printf(underline("Underlined text\n"));
```


### fg_black

Render text with black foreground.

```c
printf(fg_black("Black text\n"));
```


### fg_red

Render text with red foreground.

```c
printf(fg_red("Red text\n"));
```


### fg_green

Render text with green foreground.

```c
printf(fg_green("Green text\n"));
```


### fg_yellow

Render text with yellow foreground.

```c
printf(fg_yellow("Yellow text\n"));
```


### fg_blue

Render text with blue foreground.

```c
printf(fg_blue("Blue text\n"));
```


### fg_magenta

Render text with magenta foreground.

```c
printf(fg_magenta("Magenta text\n"));
```


### fg_cyan

Render text with cyan foreground.

```c
printf(fg_cyan("Cyan text\n"));
```


### fg_white

Render text with white foreground.

```c
printf(fg_white("White text\n"));
```


### bg_black

Render text with black background.

```c
printf(bg_black("Black background\n"));
```


### bg_red

Render text with red background.

```c
printf(bg_red("Red background\n"));
```


### bg_green

Render text with green background.

```c
printf(bg_green("Green background\n"));
```


### bg_yellow

Render text with yellow background.

```c
printf(bg_yellow("Yellow background\n"));
```


### bg_blue

Render text with blue background.

```c
printf(bg_blue("Blue background\n"));
```


### bg_magenta

Render text with magenta background.

```c
printf(bg_magenta("Magenta background\n"));
```


### bg_cyan

Render text with cyan background.

```c
printf(bg_cyan("Cyan background\n"));
```


### bg_white

Render text with white background.

```c
printf(bg_white("White background\n"));
```


