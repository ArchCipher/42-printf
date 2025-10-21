#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h> // INT_MAX
# include <stdarg.h> // va_start, va_arg, va_copy, va_end
# include <stdlib.h> // malloc, free
# include <unistd.h> // write
# include "../libft/libft.h"

# define FMT_SPECIFIER  "cspdiuxX%"
// # define FLAGS "-+ 0#."  // '*' Field width. '.' Precision
# define DECIMAL "0123456789"
# define LOWER_HEX "0123456789abcdef"
# define UPPER_HEX "0123456789ABCDEF"
# define OCTAL "01234567"
# define BUF_SIZE 20


// ft_printf
int	ft_printf(const char *, ...);

// ft_printf_utils
int     parse_format(const char *format, va_list ap);
int     handle_format(const char *specifier, va_list ap);

int     ft_print_char(char c);
int     ft_print_string(char *s);
int     ft_print_pointer(void *p);
int     ft_print_integer(int i);
int     ft_print_unsigned_integer(unsigned int u);
int     ft_print_hexadecimal(unsigned int x, char);
int     ft_print_percent(void);

// int	ft_print_hexadecimal_upper(va_list args);

// ft_printf_utils
size_t     strcspn_char(const char *s, int c);
int     ft_u_putnbr_base_fd(unsigned long n, char, int fd);
size_t  ft_l_numlen(long n, int base);

#endif