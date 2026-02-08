# Ft_printf-42

A custom re-implementation of the standard C `printf` function using low-level **POSIX syscalls** (like `write`) instead of the standard C library I/O.  
This project is built for learning and understanding how formatted output works under the hood on *UNIX-like systems*. :contentReference[oaicite:1]{index=1}

---

## 📘 About

`Ft_printf-42` is a minimal yet functional version of the C standard library’s **printf**. Instead of relying on `<stdio.h>`, it performs all output using system calls (e.g., `write(2)`), giving you better insight into:

✔ Variadic functions (`stdarg.h`)  
✔ Format string parsing  
✔ Low-level output  
✔ POSIX syscall behavior :contentReference[oaicite:2]{index=2}

This implementation is suitable for educational purposes, learning C internals, and understanding how output functions can be written from scratch.

---

## 🛠️ Features

This implementation currently supports:

- `%c` — character
- `%s` — string
- `%d`, `%i` — signed integers
- Pointer support (`%p`)
- `%u` — unsigned integers
- `%x`, `%X` — hexadecimal (lower/upper case)
- Return of number of characters printed

All output is done using **`write()`**, not standard I/O.

---

## 📁 Project Structure

.
├── ft_printf.c          # Main entrypoint
├── functionalities.c    # Format handlers
├── functions.c          # Helpers (itoa, length, etc.)
├── combination.c        # Dispatcher logic
├── execute.c            # Execution logic per specifier
├── ft_printf.h          # Header + prototypes
├── Makefile
└── tests/               # (optional) Unit tests


---

## 📦 Build

To compile the project and generate the static library:

```sh
make
```

This will produce:

libftprintf.a — static library

(optional) test executable if included

To clean object files:

## Cleaning

To clean object files:

```sh
make clean
```

# Usage

```C
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s, number: %d\n", "world", 42);
    return 0;
}

```
