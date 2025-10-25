/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:38:21 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/23 18:57:20 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


/*
DESCRIPTION
	Prints a single character with width formatting.
	Returns the number of characters printed or -1 on error.

	Values ignored: precision, dot, sign, hash
*/

int	ft_print_char(char c, t_fmt flag)
{	
	int	space_pad;
	int written;

	space_pad = 0;
	if (flag.align != '-')
	space_pad = print_pad(max(0, flag.width - 1), flag.pad);
	written = write(FD, &c, 1);
	if (flag.align == '-')
	space_pad = print_pad(max(0, flag.width - 1), flag.pad);
	if (space_pad < 0 || written < 0)
		return (-1);
	return (space_pad + written);
}

/*
DESCRIPTION
	Prints a string with width and precision formatting.
	NULL strings are replaced with "(null)". (printf doesn't compile if NULL is passed)
	Returns the number of characters printed or -1 on error.

	Values ignored: sign, hash
*/

int	ft_print_str(char *s, t_fmt flag)
{
	size_t	t_written;
	ssize_t	written;
	int		pad_len;
	int		width_pad;
	size_t	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (flag.dot)
		len = min(len, (size_t)flag.precision);
	pad_len = 0;
	if ((size_t)flag.width > len)
		pad_len = flag.width - len;
	if (flag.align != '-')
		width_pad = print_pad(pad_len, flag.pad);
	t_written = 0;
	while (t_written < len)
	{
		written = write(FD, s + t_written, len - t_written);
		if (written < 0 || written > INT_MAX || (size_t)written > (INT_MAX - t_written))
			return (-1);
		t_written += written;
	}
	if (flag.align == '-')
		width_pad = print_pad(pad_len, flag.pad);
	if (width_pad < 0 || (size_t)width_pad > (INT_MAX - t_written))
		return (-1);
	return (width_pad + t_written);
}

/*
DESCRIPTION
	Converts signed integer to unsigned and prints it.
	Handles negative sign prefix for negative numbers.
	Returns the number of characters printed or -1 on error.
*/

int	ft_print_int(int i, t_fmt *flag)
{
	if (i >= 0)
		return (ft_itoa_base((unsigned int)i, 10, *flag));
	flag->sign = '-';
	return (ft_itoa_base((unsigned int)(0u - (unsigned int)i), 10, *flag));
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}