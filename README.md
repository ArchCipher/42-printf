# <p align="center"> ft_printf - Custom Printf Implementation </p>

**42 Project | Variadic Functions & Format Parsing**  
**Objective:** Recreate the `printf` function from the C standard library, handling format specifiers, flags, width, precision, and various data types.

---

## Overview

**ft_printf** is a wrapper implementation of the `printf` function, built on top of `ft_vdprintf` (the core variadic implementation). This project demonstrates variadic functions and modular library design.

**Note:** `ft_dprintf` is a wrapper around `ft_vdprintf`, which contains the core implementation. See `ft_vdprintf/README.md` for details on the core implementation.

---

## Skills Demonstrated

- **Variadic Functions:** Using `va_list`, `va_start`, `va_arg`, `va_end`
- **Modular Design:** Building `printf` on top of `vdprintf` for code reuse

---

## Project Structure

```
ft_printf/
├── ft_printf.c              # Main printf wrapper function
├── ft_printf.h              # Public interface header
└── Makefile                 # Build configuration

../ft_vdprintf/              # Core implementation (see ft_vdprintf/README.md)
    ├── ft_vdprintf.c        # Main vdprintf function
    ├── ft_vdprintf.h        # Core header with all declarations
    ├── ft_parser.c          # Format string parsing
    ├── ft_print_types.c     # Character and string printing
    ├── ft_print_int.c       # Integer conversion and formatting
    └── ft_printf_utils.c    # Helper functions
```

**Key Files:**
- **ft_printf.c** - Wrapper that calls ft_vdprintf with STDOUT_FILENO
- See `ft_vdprintf/README.md` for core implementation details

---

## Function Prototypes

```c
// Standard printf (writes to stdout)
int ft_printf(const char *fmt, ...);
```

**Returns:**
- Number of characters written
- -1 on error

---

## Supported Features

For detailed information about supported format specifiers, flags, width, precision, platform-specific behavior, and technical implementation, see `ft_vdprintf/README.md`.

---

## Compilation & Usage

```bash
# Build the library
make

# Link with your program
gcc your_program.c -L./ft_printf -lftprintf -o your_program
```

**Example Usage:**
See `main.c` for example usage demonstrating various format specifiers and test cases.

---

## Testing

The project has been tested with:
- **[printfTester](https://github.com/Tripouille/printfTester)** - Comprehensive test suite for all specifiers and flags
- Custom test cases for edge cases and platform-specific behavior
- Integration with minishell project for real-world usage

---

*This project demonstrates advanced C programming skills including variadic functions, complex parsing, and modular library design.*
