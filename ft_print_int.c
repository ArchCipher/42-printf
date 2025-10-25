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
	Converts unsigned number to string in given base and prints it with formatting
	(sign/prefix, width, precision, alignment).
	Returns the number of characters printed or -1 on error.

	If precision is 0 and number is 0, the number is not printed (except for p).
*/

int	ft_itoa_base(unsigned long long n, int base, t_fmt flag)
{
	char	num[BUF_SIZE + 1];
	int		i;
	int		prefix_len;
	int		num_len;

	i = BUF_SIZE;
	num[i] = '\0';
	prefix_len = 0;
	if (flag.spec == 'p' || (flag.hash && n != 0 && (flag.spec == 'x' || flag.spec == 'X')))
		prefix_len = 2;
	else if (flag.sign)
		prefix_len = 1;
	if (n == 0)
		num[--i] = '0';
	while (n)
	{
		if (flag.spec == 'x' || flag.spec == 'p')
			num[--i] = LOWER_HEX[n % base];
		else if (flag.spec == 'X')
			num[--i] = UPPER_HEX[n % base];
		else
			num[--i] = DECIMAL[n % base];
		n /= base;
	}
	num_len = BUF_SIZE - i;
	if (flag.dot && flag.precision == 0 && num[i] == '0')
		num_len = 0;
	return (print_nbr(num + i, num_len, prefix_len, flag));
}

/*
DESCRIPTION
	Prints formatted number with prefix, width, and precision padding.
	Handles alignment (left/right) and padding type (space/zero).
	Returns the number of characters printed or -1 on error.

	Right alignment, flag.pad = ' ':
		[width_pad] [prefix] [precision_zeros] [number]
	Right alignment, flag.pad = '0' (no precision):
		[prefix] [width_pad] [number]
	Left alignment:
		[prefix] [precision_zeros] [number] [width_pad]
*/

int print_nbr(char *num, int num_len, int prefix_len, t_fmt flag)
{
	int	pad_len;
	int width_pad;
	int prefix_written;
	int	precision_pad;
	int	num_written;

	width_pad = 0;
	precision_pad = 0;
	num_written = 0;
	pad_len = max (0, flag.width - (prefix_len + max(num_len, flag.precision)));
	if (flag.align != '-' && flag.pad == ' ')
		width_pad = print_pad(pad_len, flag.pad);
	prefix_written = print_prefix(flag, num);
	if (flag.align != '-' && flag.pad == '0')
		width_pad = print_pad(pad_len, flag.pad);
	if (flag.dot && flag.precision > num_len && flag.spec != 'p')
		precision_pad = print_pad(flag.precision - num_len, '0');
	num_written = write(FD, num, num_len);
	if (flag.align == '-')
		width_pad = print_pad(pad_len, flag.pad);
	if (prefix_written < 0 || precision_pad < 0 || num_written < 0 || width_pad < 0)
		return (-1);
	return (width_pad + prefix_written + precision_pad + num_written);
}

/*
DESCRIPTION
	Prints number prefix (0x/0X for hex, +/- for signed).
	Returns the number of characters printed or -1 on error.

	For hexadecimal with # flag, prefix is not printed if value is 0.
*/

int	print_prefix(t_fmt flag, char *num)
{
	if (flag.spec == 'p' || (flag.hash && *num != '0' && flag.spec == 'x'))
		return (write(FD, "0x", 2));
	else if (flag.hash && *num != '0' && flag.spec == 'X')
		return (write(FD, "0X", 2));
	else if (flag.sign)
		return (write(FD, &flag.sign, 1));
	return (0);
}

/*
DESCRIPTION
	Prints padding characters (spaces or zeros).
	Returns the number of characters printed or -1 on error.
*/

int	print_pad(int pad_len, char pad)
{
	char	buf[BUF_SIZE + 1];
	int		written;
	int 	t_written;
	int		buf_len;

	if (pad_len <= 0)
		return (0);
	buf_len = BUF_SIZE;
	if (pad_len < BUF_SIZE)
		buf_len = pad_len;
	ft_memset(buf, pad, buf_len);
	t_written = 0;
	while (t_written < pad_len)
	{
		written = write(FD, buf, buf_len);
		if (written == -1)
			return (-1);
		t_written += written;
		if (t_written < pad_len && buf_len > pad_len - t_written)
			buf_len = pad_len - t_written;
	}
	return(t_written);
}