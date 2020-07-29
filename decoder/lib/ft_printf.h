/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:23:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/19 08:47:07 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

enum		e_flag
{
	minus = 0x01,
	plus = 0x02,
	space = 0x04,
	zero = 0x08,
	hash = 0x10
};

typedef enum e_flag			t_flag;

enum		e_type
{
	hh,
	h,
	l,
	ll,
	j,
	z,
	t,
	L
};

typedef enum e_type			t_type;

struct		s_float
{
	long double				nbr;
	int						neg;
	unsigned long long		nbr_integer;
	unsigned long long		nbr_decimal;
};

typedef struct s_float		t_float;

struct		s_formatter
{
	char			character;
	t_flag			flag;
};

typedef struct s_formatter	t_formatter;

struct		s_converter
{
	char			character;
	int				valid_flags;
	void			*(*function_ptr)(va_list *, void *substring, int *attrs);
	void			*(*adjust_width_prediction_ptr)(void *substring);
};

typedef struct s_converter	t_converter;

struct		s_param_type
{
	t_type			type;
	char			*type_string;
	int				length;
};

typedef struct s_param_type	t_param_type;

struct		s_output_string
{
	int		add_null;
	t_list	pre_filler;
	t_list	sign;
	t_list	prefix;
	t_list	zero_filler;
	t_list	parameter;
	t_list	post_filler;
};

typedef struct s_output_string	t_output_string;

struct		s_substring
{
	char			*input_string;
	t_converter		*converter;
	int				flags;
	t_list			**formatter_list;
	t_param_type	*param_type;
	char			*end_ptr;
	int				precision;
	int				width;
	char			filler;
	char			conv_type;
	void			*par_value;
	int				par_value_is_neg;
	t_output_string	o_string;
};

typedef struct s_substring	t_substring;

int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_sprintf(char *str, const char *format, ...);
t_list		**split_string(char *input_string, t_list **converter_array);
t_list		**create_formatters(void);
t_list		**create_converters(void);
t_list		**create_param_type_list(void);
void		add_param_type(t_list **list, t_list **type_list);
void		add_width_and_prediction(t_list **substring_list);
int			convert_substrings(t_list **list, va_list *ap,
							t_list **converter_list, t_list **formatter_list);
char		*ft_lltoa_base(long long nbr, int base);
char		*ft_ulltoa_base(unsigned long long nbr, int base);
void		get_formatters(t_substring *substring, t_list **formatter_list);
void		adjust_character(t_substring *substring);
char		*conv_character(va_list *ap, t_substring *substring, int *attrs);
void		adjust_string(t_substring *substring);
char		*conv_string(va_list *ap, t_substring *substring, int *attrs);
void		adjust_pointer(t_substring *substring);
char		*conv_pointer(va_list *ap, t_substring *substring, int *attrs);
void		adjust_int(t_substring *substring);
char		*conv_int(va_list *ap, t_substring *substring, int *attrs);
void		adjust_unsigned_octal(t_substring *substring);
char		*conv_unsigned_octal(va_list *ap, t_substring *substring,
																int *attrs);
void		adjust_unsigned_int(t_substring *substring);
char		*conv_unsigned_int(va_list *ap, t_substring *substring, int *attrs);
void		adjust_unsigned_hex(t_substring *substring);
char		*conv_unsigned_hex(va_list *ap, t_substring *substring, int *attrs);
char		*conv_unsigned_hex_up(va_list *ap, t_substring *substring,
																int *attrs);
char		*conv_percent_char(va_list *ap, t_substring *substring, int *attrs);
void		adjust_percent_char(t_substring *substring);
long long	read_o_u_x_param(t_type type, va_list *ap);
void		release_memory(t_list **substring_list, t_list **converter_list,
								t_list **formatter_list, t_list **type_list);
void		adjust_float(t_substring *substring);
char		*conv_float(va_list *ap, t_substring *substring, int *attrs);
char		*ft_dtoa_base(long double nbr, size_t base, size_t precision,
																int add_dot);
size_t		ft_numlen(unsigned long long nbr, size_t base);
double		ft_round(double nbr, int base, size_t precision, int neg);
void		set_pre_filler(t_substring *substring);
void		set_post_filler(t_substring *substring);
void		set_sign(t_substring *substring);
void		set_zero_filler(t_substring *substring);
size_t		print_formatted_string(t_list **substring_list, int fd, char *str);
long double	read_f_param(t_type type, va_list *ap);
void		save_parameter(t_substring *substring, char *s);
void		set_prefix(t_substring *substring);
void		ft_putlstr_fd(char *s, size_t string_len, int fd);
void		del_substring(void *substring_elem, size_t size);
void		del_formatter(void *formatter, size_t size);
int			count_num_of_fillers(t_substring *substring, int min_len);

#endif
