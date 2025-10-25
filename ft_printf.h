/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:27:51 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/23 18:55:05 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <limits.h> // INT_MAX
# include <stdarg.h> // va_start, va_arg, va_copy, va_end
// # include <stdlib.h> // malloc, free --- not used to be removed
# include <unistd.h> // write

# define FMT_SPEC "cspdiuxX%"
# define FLAGS "-+ 0#"
# define DECIMAL "0123456789"
# define LOWER_HEX "0123456789abcdef"
# define UPPER_HEX "0123456789ABCDEF"
# define OCTAL "01234567"
# define BUF_SIZE 20
# define FD STDOUT_FILENO

typedef struct s_fmt
{
	char    align;    // '-'
	char    pad;      // ' ' or '0'
	char    sign;     // '+' or ' '
	char    hash;
	int     width;     // min field width
	char    dot;
	int     precision; // precision after .
	char	spec;
}		    t_fmt;

// ft_printf
int		ft_printf(const char *fmt, ...);
int		ft_vprintf(const char *fmt, va_list ap);
size_t	ft_strcspn_char(const char *s, int c);

// lexer
int		parse_fmt(const char **fmt, t_fmt *flag);
void	parse_int(const char **fmt, int *i);
int		normalise_fmt(const char **fmt, t_fmt *flag);
int		handle_spec(va_list ap, t_fmt *flag);

// print spec
int		ft_print_char(char c, t_fmt flag);
int		ft_print_str(char *s, t_fmt flag);
int		ft_print_int(int i, t_fmt *flag);
int		max(int a, int b);
int		min(int a, int b);

// print int
int		ft_itoa_base(unsigned long long n, int base, t_fmt flag);
int		print_nbr(char *num, int num_len, int prefix_len, t_fmt flag);
int		print_prefix(t_fmt flag, char *num);
int		print_pad(int pad_len, char pad);

//printf_utils
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);

#endif

// result greater than int max check----- and return -1?

// check overflow for unsigned int conversion for INT_MIN