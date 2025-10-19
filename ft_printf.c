#include "ft_printf.h"

/*
	NAME
		ft_printf
	SYNOPSIS
		#include "ft_printf.h"
	PROTOTYPE
		int ft_printf(const char *, ...);
	DESCRIPTION:
		Prints a formatted string to the standard output.
		Conversions are: cspdiuxX%
	RETURN VALUE
		Returns the number of characters printed.
		The printf utility exits 0 on success, and >0 if an error occurs.
	EXTERNAL FUNC(S)
		malloc, free, write, va_start, va_arg, va_copy, va_end
		ft_libft
*/

/*
	STDARG (3) / va_arg
	stdarg  variable argument lists
	va_list	<variable_name>
			structure used by the following functions / macros

	VARIADIC FUNCTIONS / MACROS
	void	va_start(va_list ap, last);			// initializes ap
	type	va_arg(va_list ap, type);			// explands to an expression that has type and value of the next arg in the call. returns n bytes after 1st parameter (based on the input type specified)
	void	va_copy(va_list dest, va_list src)	//
	void	va_end(va_list ap);					// frees the ap
*/

int ft_printf(const char *format, ...)
{
	va_list	ap;
	int		result;

	va_start(ap, format);
	result = parse_format(format, ap);
	va_end(ap);
	return (result);
}

int parse_format(const char *format, va_list ap)
{
	int result;
	int len;

	result = 0;
	while(*format)
	{
		if(*format != '%')
		{
			len = find_percent(format, '%');
			write(1, format, len);
			result += len;
			format += len;
		}
		else if (*format == '%')
		{
			format++;
			len = handle_format(format, ap);
			result += len;
			format++;
		}
	}
	return (result);
}

int	handle_format(const char *specifier, va_list ap)
{
	if (*specifier == 'c')
		return (ft_print_char(va_arg(ap, int)));
	else if (*specifier == 's')
		return (ft_print_string(va_arg(ap, char *)));
	else if (*specifier == 'p')
		return (ft_print_pointer(va_arg(ap, void *)));
	else if (*specifier == 'd' || *specifier == 'i')	// 'i' does not detect base yet.
		return (ft_print_integer(va_arg(ap, int)));
	else if (*specifier == 'u')
		return (ft_print_unsigned_integer(va_arg(ap, unsigned int)));	// negative integers should be printed as large positive numbers
	else if (*specifier == 'x')	// should it be long?
		return (ft_print_hexadecimal(va_arg(ap, unsigned int), *specifier)); // to LOWER_HEX
	else if (*specifier == 'X')
		return (ft_print_hexadecimal(va_arg(ap, unsigned int), *specifier)); // to UPPER_HEX
	else if (*specifier == '%')
		return (ft_print_percent());
	return (0);
}

# include <stdio.h> // printf - remove

int	main()
{
	int result;
	char *s	= "POINTER";
	long h	= 0x10e407d4e;
	int sh	= 0xe;
	result	= ft_printf("Hello, World!%c %sHello\n%d %i %u\n", 'A', "1234", +123, -123, -123);
	printf(" ft_printf: %d\n", result);
	result = ft_printf("%p %x %X %x %%\n", s, h, h, sh);
	printf("%d\n", result);
	result =    printf("Hello, World!%c %sHello\n%d %i %u\n", 'A', "1234", +123, -123, -123);
	printf("std_printf: %d\n", result);
	result = printf("%p %lx %lX %x %%\n", s, h, h, sh);
	printf("%d\n", result);
}