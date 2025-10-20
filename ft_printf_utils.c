# include "ft_printf.h"

/*
DESCRIPTION
	Locates the first occurrence of the character c in the string s.
	Returns length of string upto byte located or the entire length of the string.
*/

int	find_percent(const char *s, int c)
{
	int	n;

	n = 0;
	while(s[n] && s[n] != (unsigned char)c)
		n++;
	return (n);
}

/*
DESCRIPTION
	Prints a single char and returns the number of characters printed.
*/

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

/*
DESCRIPTION
	Prints a string and returns the number of characters printed.
*/

int	ft_print_string(char *s)
{
	if (!s)
		return(write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

/*
DESCRIPTION
	Prints a void pointer argument in hexadecimal format and returns the number of characters printed.
*/

int	ft_print_pointer(void *p)
{
	return (write(1, "0x", 2) + ft_u_putnbr_base_fd((unsigned long)p, 'x', 1));
}

/*
DESCRIPTION
	%d Prints a signed decimal (base 10) number.
	%i Prints an signed integer (can be base 8 or 16) in base 10.
	Returns the number of characters printed.
*/

int	ft_print_integer(int i)		// should be able to detect base for %i- why does it automatically do that?
{
	return (ft_putnbr_fd(i, 1), (int)ft_numlen(i, 10));
}

int	ft_print_unsigned_integer(unsigned int u)
{
	return (ft_u_putnbr_base_fd(u, 'u', 1));
}

int	ft_print_hexadecimal(unsigned int x, char specifier)
{
	return (ft_u_putnbr_base_fd(x, specifier, 1));	
}

int	ft_print_percent(void)
{
	return (write(1, "%", 1));
}

int    ft_u_putnbr_base_fd(unsigned long n, char specifier, int fd)
{
	char	num[BUF_SIZE];
	size_t	i;
	int	base;

	if (specifier == 'x' || specifier == 'X')
		base = 16;
	else
		base = 10;
	i = BUF_SIZE;
	num[i] = '\0';
	if (n == 0)
		num[--i] = '0';
	while(n)
    {
		if (specifier == 'x')
			num[--i] = LOWER_HEX[n % base];
		else if (specifier == 'X')
			num[--i] = UPPER_HEX[n % base];
		else
			num[--i] = DECIMAL[n % base];
		n /= base;
    }
	return (write(fd, num + i, BUF_SIZE - i));
}
