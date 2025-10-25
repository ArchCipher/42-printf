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
	Parses format string flags, width, precision, and specifier.
	Returns 1 on success, 0 on invalid format.

	Initialised values: all set to 0 except for pad = ' ' and precision = -1
	Precedance: + and ' ' -> sign = '+'
*/

int	parse_fmt(const char **fmt, t_fmt *flag)
{
	ft_memset(flag, 0, sizeof(t_fmt));
	flag->pad = ' ';
	flag->precision = -1;
	while (**fmt && ft_strchr(FLAGS, **fmt))
	{
		if (**fmt == '-')
			flag->align = '-';
		if (**fmt == '0')
			flag->pad = '0';
		if (**fmt == ' ' && flag->sign != '+')
			flag->sign = ' ';
		if (**fmt == '+')
			flag->sign = '+';
		if (**fmt == '#')
			flag->hash = '#';
		(*fmt)++;
	}
	parse_int(fmt, &flag->width);
	if (**fmt == '.')
	{
		flag->dot = '.';
		(*fmt)++;
		parse_int(fmt, &flag->precision);
	}
	return(normalise_fmt(fmt, flag));
}

/*
DESCRIPTION
	Parses an integer from the format string and advances pointer.
*/

void	parse_int(const char **fmt, int *i)
{
	if (ft_isdigit(**fmt))
		*i = ft_atoi(*fmt);
	while(ft_isdigit(**fmt))
		(*fmt)++;
}

/*
DESCRIPTION
	Normalizes flags based on specifier and validates format.
	Returns 1 on valid specifier, 0 otherwise.

	Values overwritten:
		if align = '-' or dot -> pad = ' ' (0 is ignored)
		if dot and precision = -1 -> precision = 0 (except for p)
		if spec = p -> precision = -1 (. is ignored for p)
*/

int	normalise_fmt(const char **fmt, t_fmt *flag)
{
	if (flag->align == '-' || flag->dot)
		flag->pad = ' ';
	if (!ft_strchr(FMT_SPEC, **fmt))
		return (0);
	flag->spec = **fmt;
	(*fmt)++;
	if (flag->dot && flag->precision == -1)
		flag->precision = 0;
	if (flag->spec == 'p')
		flag->precision = -1;
	return (1);
}

/*
DESCRIPTION
	Calls the appropriate print function based on specifier.
	Returns the number of characters printed or -1 on error.
*/

int	handle_spec(va_list ap, t_fmt *flag)
{
	if (flag->spec == 'c')
		return (ft_print_char(va_arg(ap, int), *flag));
	else if (flag->spec == 's')
		return (ft_print_str(va_arg(ap, char *), *flag));
	else if (flag->spec == 'p')
		return (ft_itoa_base((unsigned long long)va_arg(ap, void *), 16, *flag));
	else if (flag->spec == 'd' || flag->spec == 'i')
		return (ft_print_int(va_arg(ap, int), flag));
	else if (flag->spec == 'u')
		return (ft_itoa_base(va_arg(ap, unsigned int), 10, *flag));
	else if (flag->spec == 'x' || flag->spec == 'X')
		return (ft_itoa_base(va_arg(ap, unsigned int), 16, *flag));
	else
		return (ft_print_char('%', *flag));
}
