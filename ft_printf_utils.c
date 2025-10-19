# include "ft_printf.h"

# include <stdio.h> // printf - remove

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

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_string(char *s)
{
	int len;

	if (!s)
		write(1, "(null)", 6);
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}

int	ft_print_pointer(void *p)
{
	int	len;

	write(1, "0x", 2);
	len = 2;
	len += ft_puthex_fd((unsigned long)p, 'x', 1);
	return (len);
}

int	ft_print_integer(int i)
{
	ft_putnbr_fd(i, 1);
	return ((int)ft_numlen(i, 10));
}

int	ft_print_unsigned_integer(int i)
{
	unsigned int u;
	u = (unsigned int) i;
	ft_putnbr_fd(u, 1);
	return ((int)ft_numlen(u, 10));
}

int	ft_print_hexadecimal(unsigned long x, char specifier)
{
	int len;

	len = ft_puthex_fd(x, specifier, 1);	//lx should print 10 before the value?
	return (len);	
}

int    ft_puthex_fd(unsigned long n, char specifier, int fd)
{
	char	num[20];
	size_t	i;

	i = 20;
	num[i] = '\0';
	while(n)
    {
		if (specifier == 'x')
			num[--i] = LOWER_HEX[n % 16];
		else
			num[--i] = UPPER_HEX[n % 16];
		n /= 16;
    }
	write(fd, num + i, 20 - i);
	return (20 - i);
}

int	ft_print_percent(void)
{
	write(1, "%", 1);
	return (1);
}